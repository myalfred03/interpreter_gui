#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QFileDialog>
#include <QFile>
#include <QTextStream>
#include <ros/package.h>
double ToG    = 57.295779513;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  firstLoad=true;
  ui->setupUi(this);
  setUpHighlighter();
  //init status bar
  ui->outputText->parentWindow=this;
  ui->statusBar->showMessage(tr("Ready"));
  //--------init toolbar------------
  //ui->statusBar->setStyleSheet("QStatusBar{background:rgb(50,50,50);}");
  ui->mainToolBar->setMovable(false);
  ui->mainToolBar->setStyleSheet("QToolButton:hover {background-color:darkgray} QToolBar {background: rgb(179, 204, 204);border: none;}");
  //--------------------------------

  runIcon.addPixmap(QPixmap(":/img/run.png"));
  stopIcon.addPixmap(QPixmap(":/img/stop.png"));
  errorIcon.addPixmap(QPixmap(":/img/error.png"));
  RerrorIcon.addPixmap(QPixmap(":/img/error_red.png"));


  QPalette windowPalette=this->palette();
  windowPalette.setColor(QPalette::Active,QPalette::Window,QColor(82,82,82));
  windowPalette.setColor(QPalette::Inactive,QPalette::Window,QColor(82,82,82));
  this->setPalette(windowPalette);
  //--------------------------------
  initFileData();
  this->updateRobot();
  QObject::connect(this,      SIGNAL(setvaluesSubs()),            this, SLOT(updatevalues()));
  connect(ui->actionInfoR,    SIGNAL(triggered(bool)),            this, SLOT(updatevalues()));
  connect(ui->actionNewFile,  SIGNAL(triggered(bool)),            this, SLOT(newFile()));
  connect(ui->actionOpen,     SIGNAL(triggered(bool)),            this, SLOT(openFile()));
  connect(ui->actionSave_File,SIGNAL(triggered(bool)),            this, SLOT(saveFile()));
  connect(ui->actionUndo,     SIGNAL(triggered(bool)),            this, SLOT(undo()));
  connect(ui->actionRedo,     SIGNAL(triggered(bool)),            this, SLOT(redo()));
  connect(ui->editor,         SIGNAL(textChanged()),              this, SLOT(changeSaveState()));
  connect(ui->actionRun,      SIGNAL(triggered(bool)),            this, SLOT(run()));
  connect(ui->actionAbout,    SIGNAL(triggered(bool)),            this, SLOT(about()));

  connect(ui->pushButton,     SIGNAL(clicked()),                  this, SLOT(pid_value()));
  

  fileSaved=true;
//  msg1.points.resize(1);
//  msg1.points[0].positions.resize(6);
//  msg1.points[1].positions.resize(6);

    startTime = ros::Time::now();
    joint_1_plot = 0.0;
    joint_2_plot = 0.0;
    joint_3_plot = 0.0;
    joint_4_plot = 0.0;
    joint_5_plot = 0.0;
    joint_6_plot = 0.0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGraph()));
    timer->start(5);

    this->initializeGraph();
    connect(ui->graph_canvas, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMoved(QMouseEvent*)));
    connect(ui->graph_canvas, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(removeAllGraphs()));

    connect(ui->comboBox,      SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBox_currentIndexChanged(int)));


  msgolder.points.resize(1);
  msgolder.points[0].positions.resize(6);

   joint_pub =       nh_.advertise<trajectory_msgs::JointTrajectory>("set_joint_trajectory", 10);
   joint_sub_limit = nh_.subscribe("/joint_limits",10,&MainWindow::jointsizeCallback, this);
   pid_value_pub   = nh_.advertise<std_msgs::Float32MultiArray>("pid_value", 10);
   joint_sub_gazebo= nh_.subscribe("/gazebo_client/joint_values_gazebo",10,&MainWindow::joint_Gz_Callback, this);



   spinner = boost::shared_ptr<ros::AsyncSpinner>(new ros::AsyncSpinner(1));
   spinner->start();
//   boost::thread* publisher_thread_;
   isloop=false;
   limit.data.resize(12);
   limit.data.push_back(0);
   publisher_thread_ = new boost::thread(boost::bind(&MainWindow::runloop, this));



}

MainWindow::~MainWindow()
{
  if(publisher_thread_ != NULL)
    {
      publisher_thread_->interrupt();
      publisher_thread_->join();

      delete publisher_thread_;
    }
  delete ui;
}


void MainWindow::initializeGraph() {
    //Make legend visible
    //ui.graph_canvas->legend->setVisible(true);
    //ui.graph_canvas->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignRight|Qt::AlignBottom);

    //Add the graphs
    ui->graph_canvas->addGraph();
    ui->graph_canvas->graph(0)->setName("Joint_1");
    QPen blueDotPen;
    blueDotPen.setColor(QColor(30, 40, 255, 150));
    blueDotPen.setStyle(Qt::DotLine);
    blueDotPen.setWidthF(4);
    ui->graph_canvas->graph(0)->setPen(blueDotPen);

    ui->graph_canvas->addGraph();
    ui->graph_canvas->graph(1)->setName("Joint_2");
    QPen redDotPen;
    redDotPen.setColor(Qt::red);
    redDotPen.setStyle(Qt::DotLine);
    redDotPen.setWidthF(4);
    ui->graph_canvas->graph(1)->setPen(redDotPen);

    ui->graph_canvas->addGraph();
    ui->graph_canvas->graph(2)->setName("Joint_3");
    QPen yellowDotPen;
    yellowDotPen.setColor(Qt::yellow);
    yellowDotPen.setStyle(Qt::DotLine);
    yellowDotPen.setWidthF(4);
    ui->graph_canvas->graph(2)->setPen(yellowDotPen);

    ui->graph_canvas->addGraph();
    ui->graph_canvas->graph(3)->setName("Joint_4");
    QPen blackDotPen;
    blackDotPen.setColor(Qt::black);
    blackDotPen.setStyle(Qt::DotLine);
    blackDotPen.setWidthF(4);
    ui->graph_canvas->graph(3)->setPen(blackDotPen);

    ui->graph_canvas->addGraph();
    ui->graph_canvas->graph(4)->setName("Joint_5");
    QPen greenDotPen;
    greenDotPen.setColor(Qt::green);
    greenDotPen.setStyle(Qt::DotLine);
    greenDotPen.setWidthF(4);
    ui->graph_canvas->graph(4)->setPen(greenDotPen);

    ui->graph_canvas->addGraph();
    ui->graph_canvas->graph(5)->setName("Joint_6");
    QPen otherDotPen;
    otherDotPen.setColor(QColor(115,182,209));
    otherDotPen.setStyle(Qt::DotLine);
    otherDotPen.setWidthF(4);
    ui->graph_canvas->graph(5)->setPen(otherDotPen);

    // give the axes some labels:
    ui->graph_canvas->xAxis->setLabel("Time (s)");
    ui->graph_canvas->yAxis->setLabel("Joint move (°)");
    ui->graph_canvas->legend->setVisible(true);


    //For user interaction
    // main_window_ui_->graph_canvas->setInteraction(QCP::iRangeDrag, true);
    // main_window_ui_->graph_canvas->setInteraction(QCP::iRangeZoom, true);
    ui->graph_canvas->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                  QCP::iSelectLegend | QCP::iSelectPlottables);

    connect(ui->graph_canvas, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMoved(QMouseEvent*)));

    x_org = 0;

    //Plot the graph
    ui->graph_canvas->replot();
}

void MainWindow::mouseMoved(QMouseEvent *event) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3);

    double x = ui->graph_canvas->xAxis->pixelToCoord(event->x());
    double y = ui->graph_canvas->yAxis->pixelToCoord(event->y());

    oss << "Graph values: x: " << x << "\ty: " << y ;
    ui->label_4->setText(QString::fromStdString(oss.str()));
}

void MainWindow::removeAllGraphs()
{
   // main_window_ui_->graph_canvas->clearGraphs();
   ui->graph_canvas->graph(0)->data()->clear();
   ui->graph_canvas->graph(1)->data()->clear();
   ui->graph_canvas->graph(2)->data()->clear();
   ui->graph_canvas->graph(3)->data()->clear();
   ui->graph_canvas->graph(4)->data()->clear();
   ui->graph_canvas->graph(5)->data()->clear();

   ui->graph_canvas->replot();
}

void MainWindow::updateGraph() {
    double x_val = (ros::Time::now() - startTime).toSec();

    // double x_org1 = x_org;
    // if (x_val - x_org1 > 20) {
    //     main_window_ui_->graph_canvas->graph(0)->removeDataBefore(x_org1 + 1);
    //     main_window_ui_->graph_canvas->graph(1)->removeDataBefore(x_org1 + 1);
    //     x_org++;
    // }

    ui->graph_canvas->graph(0)->addData(x_val, joint_1_plot);//Set Point
    ui->graph_canvas->graph(1)->addData(x_val, joint_2_plot);//Output
    ui->graph_canvas->graph(2)->addData(x_val, joint_3_plot);
    ui->graph_canvas->graph(3)->addData(x_val, joint_4_plot);
    ui->graph_canvas->graph(4)->addData(x_val, joint_5_plot);
    ui->graph_canvas->graph(5)->addData(x_val, joint_6_plot);
    ui->graph_canvas->rescaleAxes();
    ui->graph_canvas->replot();
}

void MainWindow::mouseWheel()
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed
  
  if (ui->graph_canvas->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->graph_canvas->axisRect()->setRangeZoom(ui->graph_canvas->xAxis->orientation());
  else if (ui->graph_canvas->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->graph_canvas->axisRect()->setRangeZoom(ui->graph_canvas->yAxis->orientation());
  else
    ui->graph_canvas->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void MainWindow::on_comboBox_currentIndexChanged(int index=0)
{
  switch (index){

   case 0:
 {
    ui->graph_canvas->graph(0)->setVisible(true);
    ui->graph_canvas->graph(1)->setVisible(true);
    ui->graph_canvas->graph(2)->setVisible(true);
    ui->graph_canvas->graph(3)->setVisible(true);
    ui->graph_canvas->graph(4)->setVisible(true);
    ui->graph_canvas->graph(5)->setVisible(true);
   break;
 }
   case 1:
  {
    ui->graph_canvas->graph(0)->setVisible(true);
    ui->graph_canvas->graph(1)->setVisible(false);
    ui->graph_canvas->graph(2)->setVisible(false);
    ui->graph_canvas->graph(3)->setVisible(false);
    ui->graph_canvas->graph(4)->setVisible(false);
    ui->graph_canvas->graph(5)->setVisible(false);

   break;
  }
   case 2:
 {
    ui->graph_canvas->graph(0)->setVisible(false);
    ui->graph_canvas->graph(1)->setVisible(true);
    ui->graph_canvas->graph(2)->setVisible(false);
    ui->graph_canvas->graph(3)->setVisible(false);
    ui->graph_canvas->graph(4)->setVisible(false);
    ui->graph_canvas->graph(5)->setVisible(false);
   break;
 }

    case 3:
 {
    ui->graph_canvas->graph(0)->setVisible(false);
    ui->graph_canvas->graph(1)->setVisible(false);
    ui->graph_canvas->graph(2)->setVisible(true);
    ui->graph_canvas->graph(3)->setVisible(false);
    ui->graph_canvas->graph(4)->setVisible(false);
    ui->graph_canvas->graph(5)->setVisible(false);
   break;
 }

    case 4:
 {
    ui->graph_canvas->graph(0)->setVisible(false);
    ui->graph_canvas->graph(1)->setVisible(false);
    ui->graph_canvas->graph(2)->setVisible(false);
    ui->graph_canvas->graph(3)->setVisible(true);
    ui->graph_canvas->graph(4)->setVisible(false);
    ui->graph_canvas->graph(5)->setVisible(false);
   break;
 }
    case 5:
 {
    ui->graph_canvas->graph(0)->setVisible(false);
    ui->graph_canvas->graph(1)->setVisible(false);
    ui->graph_canvas->graph(2)->setVisible(false);
    ui->graph_canvas->graph(3)->setVisible(false);
    ui->graph_canvas->graph(4)->setVisible(true);
    ui->graph_canvas->graph(5)->setVisible(false);
   break;
 }
    case 6:
 {
    ui->graph_canvas->graph(0)->setVisible(false);
    ui->graph_canvas->graph(1)->setVisible(false);
    ui->graph_canvas->graph(2)->setVisible(false);
    ui->graph_canvas->graph(3)->setVisible(false);
    ui->graph_canvas->graph(4)->setVisible(false);
    ui->graph_canvas->graph(5)->setVisible(true);
   break;
 }

  }
}

void MainWindow::pid_value(){
  std_msgs::Float32MultiArray send_val;
  send_val.data.resize(3);

  send_val.data[0] = ui->doubleSpinBox->   value();
  send_val.data[1] = ui->doubleSpinBox_2-> value();
  send_val.data[2] = ui->doubleSpinBox_3-> value();
  pid_value_pub.publish(send_val);

}

void MainWindow::setUpHighlighter(){
  QFont font;
  font.setFamily("Courier");
  font.setFixedPitch(true);
  font.setPointSize(14);
  font.setBold(true);
  ui->editor->setFont(font);
  ui->editor->setTabStopWidth(fontMetrics().width(QLatin1Char('9'))*4);
  highlighter=new Highlighter(ui->editor->document());
}

void MainWindow::resizeEvent(QResizeEvent *event){
  QMainWindow::resizeEvent(event);
  ui->editor->setGeometry(10,0,width()-20,height()-ui->statusBar->height()-ui->mainToolBar->height()-80-15);
  ui->outputText->setGeometry(10,ui->editor->height()+10,this->width()-20,80);
}
void MainWindow::initFileData(){
  fileName=tr("Untitled.rrun");
  filePath=QString::fromUtf8( ros::package::getPath("interpreter_gui").c_str()) + "/Script/Untitled.rrun"; //QDir::homePath()+"/ros_qtc_plugin/src/interpreter_gui/Script";//tr("/home/yesser/ros_qtc_plugin/src/interpreter_gui"); //QCoreApplication::applicationDirPath()
  fileSaved=true;
  isRunning=false;
}
void MainWindow::undo(){
  ui->editor->undo();
}
void MainWindow::redo(){
  ui->editor->redo();
}
void MainWindow::saveFile(){
  QString savePath=QFileDialog::getSaveFileName(this,tr("Elija la ruta y nombre del archivo a guardar"),filePath,tr("Rrun File(*.rrun)"));
  if(!savePath.isEmpty()){
      QFile out(savePath);
      out.open(QIODevice::WriteOnly|QIODevice::Text);
      QTextStream str(&out);
      str<<ui->editor->toPlainText();
      out.close();
      fileSaved=true;
      QRegularExpression re(tr("(?<=\\/)\\w+\\.rrun"));
      fileName=re.match(savePath).captured();
      filePath=savePath;
      this->setWindowTitle(tr("Robot Script Editor - ")+fileName);
    }
  ui->actionError_Datos->setIcon(errorIcon);

}
void MainWindow::newFile(){
  MainWindow *newWindow=new MainWindow();
  QRect newPos=this->geometry();
  newWindow->setGeometry(newPos.x()+10,newPos.y()+10,newPos.width(),newPos.height());
  newWindow->show();
  ui->actionError_Datos->setIcon(errorIcon);
}
void MainWindow::openFile(){
  if(!fileSaved){
      if(QMessageBox::Save==QMessageBox::question(this,tr("Archivo no guardado"),tr("Guardar Archivo Actual"),QMessageBox::Save,QMessageBox::Cancel))
        saveFile();
    }
  QString openPath=QFileDialog::getOpenFileName(this,tr("Seleccione el archivo para abrir"),filePath,tr("Rrun File(*.rrun)"));
  if(!openPath.isEmpty()){
      QFile in(openPath);
      in.open(QIODevice::ReadOnly|QIODevice::Text);
      QTextStream str(&in);
      ui->editor->setPlainText(str.readAll());
      QRegularExpression re(tr("(?<=\\/)\\w+\\.rrun"));
      fileName=re.match(openPath).captured();
      this->setWindowTitle(tr("Robot Script Editor - ")+fileName);
      filePath=openPath;
      fileSaved=true;
    }
  ui->actionError_Datos->setIcon(errorIcon);
}
void MainWindow::run(){
  //    trajectory_point1.positions.clear();

  trajectory_msgs::JointTrajectory msg;
  msg.points.resize(1);
  msg.points[0].positions.resize(6);
  isloop =false;
  std::cout<< "step1" << std::endl;

  int it=0;
//       for (int j = 0; j < 6; j++) {
        msg1.points.clear();
        msg1.joint_names.clear();
        msg1.points.resize(1);
        msg1.points[0].positions.resize(6);
        msg1.points[0].velocities.resize(6);
        msg1.points[0].velocities[0] = 70;
        msg1.points[0].velocities[1] = 70;
        msg1.points[0].velocities[2] = 70;
        msg1.points[0].velocities[3] = 70;
        msg1.points[0].velocities[4] = 70;
        msg1.points[0].velocities[5] = 70;

//       } //for
//       joint_pub.publish(msg1) ; //publish nodo


  if(isRunning){
//      process.terminate();
      ui->actionRun->setIcon(runIcon);
      return;
    }
  if(!fileSaved){
//      if(QMessageBox::Save==QMessageBox::question(this,tr("Archivo no guardado"),tr("Guardar Archivo Actual？"),QMessageBox::Save,QMessageBox::Cancel))
//        saveFile();
    QFile out(filePath);
    out.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream str(&out);
    str<<ui->editor->toPlainText();
    out.close();
    fileSaved=true;

    }
  if(fileSaved){
    //if(process!=nullptr)delete process;
    isRunning=true;
    ui->statusBar->showMessage(tr("Programa En Ejecucion..."));
    ui->outputText->clear();
    output.clear();
    error.clear();
    QString buildPath;
    QRegularExpression re(tr(".*(?=\\.rrun)"));
    buildPath=re.match(filePath).captured();
//    qDebug()<<filePath;
//    process.start("bash", QStringList() << "-c" << QString(tr("g++ ")+filePath+tr(" -o ")+buildPath+tr(";")+buildPath));
//    process.waitForStarted();

    ui->outputText->setFocus();
    ui->actionRun->setIcon(stopIcon);

    std::ifstream streamcount(filePath.toStdString()); // OR "/home/yesser/ros_qtc_plugin/src/interpreter_gui/Script/firstScript.rrun"

    int points = std::count(std::istreambuf_iterator<char>(streamcount),std::istreambuf_iterator<char>(),'\n');
    std::cout<< "\n points in trajectory " << points << std::endl;

    std::ifstream stream(filePath.toStdString());
    if(stream.good()){
      std::string linea;
      while(!stream.eof()&&isRunning){
        linea.clear();
        std::getline(stream, linea);
        ROS_INFO("Proceso %s",linea.c_str());
        it++;
        msg = this->comandos(linea,it);
      }

      std::cout << "\n point = " << msg.points.size() << " " << msg  <<std::endl;
      joint_pub.publish(msg) ; //publish nodo
    }

    this->runFinished(0);


//    if (!isloop){
//    }

   } //file save
}

void MainWindow::jointsizeCallback(const std_msgs::Float32MultiArray::ConstPtr &msglimit) //Valores de los limtes de los joints
{
  std::cout<<"DATAOK"<< std::endl;

//  limit.data.resize(12);

    limit = *msglimit;

    Q_EMIT setvaluesSubs();


}

void MainWindow::joint_Gz_Callback(const trajectory_msgs::JointTrajectory &msg) //Valores de los limtes de los joints
{
  std::cout<<"gazebo joints"<< std::endl;

    joint_1_plot = msg.points[0].positions[0]*ToG;
    joint_2_plot = msg.points[0].positions[1]*ToG;
    joint_3_plot = msg.points[0].positions[2]*ToG;
    joint_4_plot = msg.points[0].positions[3]*ToG;
    joint_5_plot = msg.points[0].positions[4]*ToG;
    joint_6_plot = msg.points[0].positions[5]*ToG;
  std::cout<<joint_1_plot<<"\n"<<joint_2_plot<<std::endl;

     // joint_positions_["joint_1"]= msg.points[0].positions[0]/ToG;
     // joint_positions_["joint_2"]= msg.points[0].positions[1]/ToG;
     // joint_positions_["joint_3"]= msg.points[0].positions[2]/ToG;
     // joint_positions_["joint_4"]= msg.points[0].positions[3]/ToG;
     // joint_positions_["joint_5"]= msg.points[0].positions[4]/ToG;
     // joint_positions_["joint_6"]= msg.points[0].positions[5]/ToG;


}

void MainWindow::updatevalues(){
  std::cout<<"Signal is OK"<< std::endl;
  std::string info;
  ui->outputText->clear();
  info = std::string("Valores en Grados de Cada Joint de el Robot Cargado a ROS \n");
  this->updateOutput(info);
  for (int i =0; i<6;i++)
  {
    info = std::string(">>  Joint_" + std::to_string(i+1) + "   " + std::to_string(limit.data[i]) + " Grados (°)    " + " +" + std::to_string(limit.data[i+6]) + " Grados (°) ");

    this->updateOutput(info);
  }


}


trajectory_msgs::JointTrajectory MainWindow::comandos(std::string &comando, int &ii){
  int i =ii;
  std::string info;
  std::vector<double> jointvalues(6);
  trajectory_msgs::JointTrajectoryPoint comandoP;
  comandoP.positions.resize(6);
  comandoP.velocities.resize(6);


 //Full Zero (Core Dumped)
//      for (int j = 0; j < 6; j++) {
//      msg1.points[0].positions[j] = 0.00;
//      } //for


  std::cout << "\n I have iterator " << i <<std::endl;

  std::vector<std::string> partes=split(comando, ' ');

  if(partes.size()==0){
    std::cout<< "Line empty"<< std::endl;
//    msg1.points[0].positions[0] = 0.00;
      }else if (partes[1] == std::string("G") && partes[3] == std::string("V")){
        comandoP.velocities[0] = 101 - std::stod(partes[4]);
        comandoP.velocities[1] = 101 - std::stod(partes[4]);
        comandoP.velocities[2] = 101 - std::stod(partes[4]);
        comandoP.velocities[3] = 101 - std::stod(partes[4]);
        comandoP.velocities[4] = 101 - std::stod(partes[4]);
        comandoP.velocities[5] = 101 - std::stod(partes[4]);
        switch(partes[0][6]){
          case '1':
            if(partes.size()>1){
              std::cout << "I have it 1 " << partes[2]  <<std::endl;

              info =std::string(">>  Ejecutando Moviento del Joint 1  a  " +partes[2] + " Grados (°)");
              this->updateOutput(info);

              comandoP.positions[0] = std::stod(partes[2]);

              if(comandoP.positions[0]>limit.data[0] && comandoP.positions[0]<limit.data[6] ){
                std::cout<< "is ok for now"<< std::endl;
                comandoP.positions[1] = msg1.points[i-1].positions[1];
                comandoP.positions[2] = msg1.points[i-1].positions[2];
                comandoP.positions[3] = msg1.points[i-1].positions[3];
                comandoP.positions[4] = msg1.points[i-1].positions[4];
                comandoP.positions[5] = msg1.points[i-1].positions[5];
                msg1.joint_names.push_back("joint_1");
                msg1.points.push_back(comandoP);
              }
              else {
                comandoP.positions[0] = 0.00;
                comandoP.velocities[0] = 0.00;
                msg1.joint_names.push_back("joint_1");
                msg1.points.push_back(comandoP);
                this->updateError();
                   }
            }
            break;
          case '2':
            if(partes.size()>1){
              std::cout << "I have it  2 " << partes[2]  <<std::endl;
              info =std::string(">>  Ejecutando Moviento del Joint 2  a  " +partes[2] + " Grados (°)");
              this->updateOutput(info);

              comandoP.positions[1] = std::stod(partes[2]);
//              comandoP.velocities[0] = std::stod(partes[4]);
//              comandoP.velocities[1] = std::stod(partes[4]);
//              comandoP.velocities[2] = std::stod(partes[4]);
//              comandoP.velocities[3] = std::stod(partes[4]);
//              comandoP.velocities[4] = std::stod(partes[4]);
//              comandoP.velocities[5] = std::stod(partes[4]);

//              msg1.points[i-1].positions[1]. = std::stod(partes[1]);

              if(comandoP.positions[1]>limit.data[1] && comandoP.positions[1]<limit.data[7] ){
                std::cout<< "is ok for now"<< std::endl;
                comandoP.positions[0] = msg1.points[i-1].positions[0];
                comandoP.positions[2] = msg1.points[i-1].positions[2];
                comandoP.positions[3] = msg1.points[i-1].positions[3];
                comandoP.positions[4] = msg1.points[i-1].positions[4];
                comandoP.positions[5] = msg1.points[i-1].positions[5];
                msg1.joint_names.push_back("joint_2");
                msg1.points.push_back(comandoP);
              }
              else {
                comandoP.positions[1] = 0.00;
                comandoP.velocities[0] = 0.00;
                msg1.joint_names.push_back("joint_2");
                msg1.points.push_back(comandoP);
//                msg1.points[i-1].positions[1] = 0.00;
                this->updateError();
                   }
            }
            break;

        case '3':
          if(partes.size()>1){
            std::cout << "I have it  3 " << partes[1]  <<std::endl;

            info =std::string(">>  Ejecutando Moviento del Joint 3  a  " +partes[2] + " Grados (°)");
            this->updateOutput(info);

            comandoP.positions[2] = std::stod(partes[2]);

            if(comandoP.positions[2]>limit.data[2] && comandoP.positions[2]<limit.data[8] ){
              std::cout<< "is ok for now"<< std::endl;
              comandoP.positions[0] = msg1.points[i-1].positions[0];
              comandoP.positions[1] = msg1.points[i-1].positions[1];
              comandoP.positions[3] = msg1.points[i-1].positions[3];
              comandoP.positions[4] = msg1.points[i-1].positions[4];
              comandoP.positions[5] = msg1.points[i-1].positions[5];
              msg1.joint_names.push_back("joint_3");
              msg1.points.push_back(comandoP);
              }
            else {
              comandoP.positions[2] = 0.00;
              comandoP.velocities[0] = 0.00;
              msg1.joint_names.push_back("joint_3");
              msg1.points.push_back(comandoP);
              this->updateError();
                 }
          }
          break;

        case '4':
          if(partes.size()>1){
            std::cout << "I have it  4 " << partes[1]  <<std::endl;

            info =std::string(">>  Ejecutando Moviento del Joint 4  a  " +partes[2] + " Grados (°)");
            this->updateOutput(info);

            comandoP.positions[3] = std::stod(partes[2]);

            if(comandoP.positions[3]>limit.data[3] && comandoP.positions[3]<limit.data[9] ){
              std::cout<< "is ok for now"<< std::endl;
              comandoP.positions[0] = msg1.points[i-1].positions[0];
              comandoP.positions[1] = msg1.points[i-1].positions[1];
              comandoP.positions[2] = msg1.points[i-1].positions[2];
              comandoP.positions[4] = msg1.points[i-1].positions[4];
              comandoP.positions[5] = msg1.points[i-1].positions[5];
              msg1.joint_names.push_back("joint_4");
              msg1.points.push_back(comandoP);
              }
            else {
              comandoP.positions[3] = 0.00;
              comandoP.velocities[0] = 0.00;
              msg1.joint_names.push_back("joint_4");
              msg1.points.push_back(comandoP);
              this->updateError();
                 }
          }
          break;

        case '5':
          if(partes.size()>1){
            std::cout << "I have it  5 " << partes[1]  <<std::endl;

            info =std::string(">>  Ejecutando Moviento del Joint 5  a  " +partes[2] + " Grados (°)");
            this->updateOutput(info);

            comandoP.positions[4] = std::stod(partes[2]);

            if(comandoP.positions[4]>limit.data[4] && comandoP.positions[4]<limit.data[10] ){
              std::cout<< "is ok for now"<< std::endl;
              comandoP.positions[0] = msg1.points[i-1].positions[0];
              comandoP.positions[1] = msg1.points[i-1].positions[1];
              comandoP.positions[2] = msg1.points[i-1].positions[2];
              comandoP.positions[3] = msg1.points[i-1].positions[3];
              comandoP.positions[5] = msg1.points[i-1].positions[5];
              msg1.joint_names.push_back("joint_5");
              msg1.points.push_back(comandoP);
              }
            else {
              comandoP.positions[4] = 0.00;
              comandoP.velocities[0] = 0.00;
              msg1.joint_names.push_back("joint_5");
              msg1.points.push_back(comandoP);
              this->updateError();
                 }
          }
          break;

        case '6':
          if(partes.size()>1){
            std::cout << "I have it  6 " << partes[1]  <<std::endl;

            info =std::string(">>  Ejecutando Moviento del Joint 6  a  " +partes[2] + " Grados (°)");
            this->updateOutput(info);

            comandoP.positions[5] = std::stod(partes[2]);

            if(comandoP.positions[5]>limit.data[5] && comandoP.positions[5]<limit.data[11] ){
              std::cout<< "is ok for now"<< std::endl;
              comandoP.positions[0] = msg1.points[i-1].positions[0];
              comandoP.positions[1] = msg1.points[i-1].positions[1];
              comandoP.positions[2] = msg1.points[i-1].positions[2];
              comandoP.positions[3] = msg1.points[i-1].positions[3];
              comandoP.positions[4] = msg1.points[i-1].positions[4];
              msg1.joint_names.push_back("joint_6");
              msg1.points.push_back(comandoP);
              }
            else {
              comandoP.positions[5] = 0.00;
              comandoP.velocities[0] = 0.00;
              msg1.joint_names.push_back("joint_6");
              msg1.points.push_back(comandoP);
              this->updateError();
                 }
          }
          break;

          case 'm':
            //m union posicion_radianes
            //Mueve la unión hasta la posición en radianes indicada
            if(partes.size()>2){
//              robot->mover(partes[1],std::stod(partes[2]));
            }
            break;

          case 'w':
            //w [union]
            //Espera hasta que la unión halla llegado a su destino. Si no se indica la unión se espera hata terminar todas
            ROS_INFO("eseparndo");
            break;
          case 's':
            //s milisegundos
            //Duerme los milisegundos indicados.

            //de momento nos dormimos durante el tiempo indicado.
            std::string tiempo(partes[1]);
            ROS_INFO("durmiendo %d",std::stoi(tiempo));
            boost::this_thread::sleep(boost::posix_time::milliseconds(std::stoi(tiempo)));
            //usleep(std::stoi(tiempo));
            ROS_INFO("despierto");
            break;/**/
        }
      }

  if(partes.size()==0){
    std::cout<< "Line empty"<< std::endl;
  }else{
        if(partes[0]== std::string("wait()"))
        {
          std::cout<< "I have wait()"<< std::endl;
//          isloop =true;
          info =std::string(">>  Instrucción wait() a  " + partes[1] + " ms");
          this->updateOutput(info);
          comandoP.velocities[0] = std::stod(partes[1])/20;
//          comandoP.velocities[1] = std::stod(partes[1]);
//          comandoP.velocities[2] = std::stod(partes[1]);
//          comandoP.velocities[3] = std::stod(partes[1]);
//          comandoP.velocities[4] = std::stod(partes[1]);
//          comandoP.velocities[5] = std::stod(partes[1]);
          comandoP.positions[0] = msg1.points[i-1].positions[0];
          comandoP.positions[1] = msg1.points[i-1].positions[1];
          comandoP.positions[2] = msg1.points[i-1].positions[2];
          comandoP.positions[3] = msg1.points[i-1].positions[3];
          comandoP.positions[4] = msg1.points[i-1].positions[4];
          comandoP.positions[5] = msg1.points[i-1].positions[5];
          msg1.joint_names.push_back("wait");
          msg1.points.push_back(comandoP);
        }
        else {
          std::cout<< "I don't have wait()"<< std::endl;
             }
          }

  if(partes.size()==0){
    std::cout<< "Line empty"<< std::endl;
  }else{
        if(partes[0]== std::string("loop()"))
        {
          std::cout<< "I have loop()"<< std::endl;
          isloop =true;
          info =std::string(">>  Ejecutando todos los movimientos con Comportamiento Ciclico \nDesactiva la instrucción loop() para detener");
          this->updateOutput(info);
          // trajectory_msgs::JointTrajectory msg;
          // msg.points.push_back(comandoP);
        }
        else {
          std::cout<< "I don't have loop()"<< std::endl;
             }
          }




//  for (int k = 0; k < 6; k++) {
//   msg1.points[0].positions[k] =jointvalues[k]; //array [i]
//                              }
//  msgolder = msg1;
return msg1;
}

void MainWindow::runloop(){
  boost::mutex::scoped_lock state_pub_lock(state_pub_mutex_);
  ros::Rate loop_rate(10);

//  msgolder.points.resize(1);
//  msgolder.points[0].positions.resize(6);

  while (true){

//    for (int j = 0; j < 6; j++) {
//    msgolder.points[0].positions[j] = 0.0;
//    joint_pub.publish(msgolder);
//    } //for
    if(isloop)
    {
    std::cout<< "I'm alive"<< std::endl;
    joint_pub.publish(msg1);
    }
//  for (int i = 0; i < 6; i++) {
//  msgolder.points[0].positions[i] = msg1.points[0].positions[i];
//  joint_pub.publish(msgolder);
//  } //for
    try {
      boost::this_thread::interruption_point();
    } catch(const boost::thread_interrupted& o) {
      break; // quit the thread's loop
    }

  loop_rate.sleep();

  }//while
}


std::vector<std::string> MainWindow::split(const std::string &c, char d){
  std::vector<std::string> resultado;

  std::stringstream cs(c);
  std::string parte;
  while(std::getline(cs, parte, d)){
    resultado.push_back(parte);
  }

  return resultado;
}

void MainWindow::runFinished(int code){
  ui->actionRun->setIcon(runIcon);
  isRunning=false;
  qDebug()<<tr("exit code=")<<code;
  ui->statusBar->showMessage(tr("Ready"));

}
void MainWindow::updateOutput(std::string &info)
{
  output=QString::fromLocal8Bit(info.c_str());
  //ui->outputText->setPlainText(output+tr("\n")+error);
  ui->outputText->setPlainText(ui->outputText->toPlainText()+output+tr("... \n"));//+tr("\n"));
}
void MainWindow::updateError(){
  error=QString("Valores Fuera del espacio de trabajo \n Regresando Robot a su estado Inicial");
//  //ui->outputText->setPlainText(output+tr("\n")+error);
  ui->outputText->setPlainText(ui->outputText->toPlainText()+error);//+tr("\n"));
//  ui->actionError_Datos->isEnabled();
  ui->actionError_Datos->setIcon(RerrorIcon);
  isRunning=false;
}

void MainWindow::updateRobot(){
  error=QString("Por Favor cargue un modelo de Robot a ROS");
  ui->outputText->setPlainText(ui->outputText->toPlainText()+error);//+tr("\n"));
  ui->actionError_Datos->setIcon(errorIcon);
  isRunning=false;
}

void MainWindow::inputData(QString data){
//  if(isRunning)process.write(data.toLocal8Bit());
}
void MainWindow::closeEvent(QCloseEvent *event){
  if(!fileSaved){
      if(QMessageBox::Save==QMessageBox::question(this,tr("¿Salir sin guardar?"),tr("El archivo actual no se ha guardado"),QMessageBox::Save,QMessageBox::Cancel))
        saveFile();
      fileSaved=true;
    }
}
void MainWindow::about(){
  QMessageBox::information(this,tr("About"),tr(" Yeser M. v1.1 \n Universidad Nacional de Ingenieria \nmyalfredo03@ieee.org"),QMessageBox::Ok);
}

//CODE Heuristic
//    msg1.points.resize(points+1);
//    for (std::size_t k=0; k==points; ++k){
//      if(true){
//    msg1.points[k].positions.resize(6);
//    }
//    }
//msg1.points[i-1].positions[2] = std::stod(partes[1]);
