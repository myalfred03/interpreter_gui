#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QFileDialog>
#include <QFile>
#include <QTextStream>
#include <ros/package.h>
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
  ui->mainToolBar->setStyleSheet("QToolButton:hover {background-color:darkgray} QToolBar {background: rgb(82,82,82);border: none;}");
  //--------------------------------

  runIcon.addPixmap(QPixmap(":/img/run.png"));
  stopIcon.addPixmap(QPixmap(":/img/stop.png"));

  QPalette windowPalette=this->palette();
  windowPalette.setColor(QPalette::Active,QPalette::Window,QColor(82,82,82));
  windowPalette.setColor(QPalette::Inactive,QPalette::Window,QColor(82,82,82));
  this->setPalette(windowPalette);
  //--------------------------------
  initFileData();
  connect(ui->actionNewFile,SIGNAL(triggered(bool)),this,SLOT(newFile()));
  connect(ui->actionOpen,SIGNAL(triggered(bool)),this,SLOT(openFile()));
  connect(ui->actionSave_File,SIGNAL(triggered(bool)),this,SLOT(saveFile()));
  connect(ui->actionUndo,SIGNAL(triggered(bool)),this,SLOT(undo()));
  connect(ui->actionRedo,SIGNAL(triggered(bool)),this,SLOT(redo()));
  connect(ui->editor,SIGNAL(textChanged()),this,SLOT(changeSaveState()));
  connect(ui->actionRun,SIGNAL(triggered(bool)),this,SLOT(run()));
//  connect(&process,SIGNAL(finished(int)),this,SLOT(runFinished(int)));
//  connect(&process,SIGNAL(readyReadStandardOutput()),this,SLOT(updateOutput()));
//  connect(&process,SIGNAL(readyReadStandardError()),this,SLOT(updateError()));
  connect(ui->actionAbout,SIGNAL(triggered(bool)),this,SLOT(about()));
  fileSaved=true;
  msg1.points.resize(1);
  msg1.points[0].positions.resize(6);
  msgolder.points.resize(1);
  msgolder.points[0].positions.resize(6);
   joint_pub = nh_.advertise<trajectory_msgs::JointTrajectory>("set_joint_trajectory", 10);
}

MainWindow::~MainWindow()
{
  delete ui;
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
  filePath=QString::fromUtf8( ros::package::getPath("interpreter_gui").c_str()) + "/Script"; //QDir::homePath()+"/ros_qtc_plugin/src/interpreter_gui/Script";//tr("/home/yesser/ros_qtc_plugin/src/interpreter_gui"); //QCoreApplication::applicationDirPath()
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
}
void MainWindow::newFile(){
  MainWindow *newWindow=new MainWindow();
  QRect newPos=this->geometry();
  newWindow->setGeometry(newPos.x()+10,newPos.y()+10,newPos.width(),newPos.height());
  newWindow->show();
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
}
void MainWindow::run(){
  trajectory_msgs::JointTrajectory msg;
  if(isRunning){
//      process.terminate();
      ui->actionRun->setIcon(runIcon);
      return;
    }
  if(!fileSaved){
      if(QMessageBox::Save==QMessageBox::question(this,tr("Archivo no guardado"),tr("Guardar Archivo Actual？"),QMessageBox::Save,QMessageBox::Cancel))
        saveFile();
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


    std::ifstream stream(filePath.toStdString()); // "/home/yesser/ros_qtc_plugin/src/interpreter_gui/Script/firstScript.rrun"
    if(stream.good()){
      std::string linea;
      while(!stream.eof()){
        linea.clear();
        std::getline(stream, linea);
        ROS_INFO("Proceso %s",linea.c_str());
        msg = this->comandos(linea);
        std::cout << msg <<std::endl;

        joint_pub.publish(msg) ; //publish nodo

//        this->trajectory(msg);
      }
    }

    this->runFinished(0);


    }

}

trajectory_msgs::JointTrajectory MainWindow::comandos(std::string &comando){

  std::vector<double> jointvalues(6);

  std::vector<std::string> partes=split(comando, ' ');
  if(partes.size()==0){
        //gzerr<<"No se ha indicado un comando válido."<<"\r\n";
      }else{
        switch(partes[0][6]){
          case '1':
            if(partes.size()>1){
              std::cout << "I have it 1 " << partes[1]  <<std::endl;
              this->updateOutput(partes[1]);
              msg1.points[0].positions[0] = std::stod(partes[1]);
            }
            break;
          case '2':
            if(partes.size()>1){
              std::cout << "I have it  2 " << partes[1]  <<std::endl;
              this->updateOutput(partes[1]);
              msg1.points[0].positions[1] = std::stod(partes[1]);
            }
            break;

        case '3':
          if(partes.size()>1){
            std::cout << "I have it  3 " << partes[1]  <<std::endl;
            this->updateOutput(partes[1]);
            msg1.points[0].positions[2] = std::stod(partes[1]);
          }
          break;

        case '4':
          if(partes.size()>1){
            std::cout << "I have it  4 " << partes[1]  <<std::endl;
            this->updateOutput(partes[1]);
            msg1.points[0].positions[3] = std::stod(partes[1]);
          }
          break;

        case '5':
          if(partes.size()>1){
            std::cout << "I have it  5 " << partes[1]  <<std::endl;
            this->updateOutput(partes[1]);
            msg1.points[0].positions[4] = std::stod(partes[1]);
          }
          break;

          case 'm':
            //m union posicion_radianes
            //Mueve la unión hasta la posición en radianes indicada
            if(partes.size()>2){
//              robot->mover(partes[1],std::stod(partes[2]));
            }
            break;
//          case 'e':
//            //e fichero
//            //Ejecuta un fichero
//            {
//            if( ruta==""){
//              //Aún no tenemos una ruta. La cogemos del fichero
//              ROS_INFO("Estas en %s",boost::filesystem::initial_path().string().c_str());
//              boost::filesystem::path p=boost::filesystem::complete(partes[1]);
//              ruta=p.parent_path().string();
//              ROS_INFO("Ruta fija %s",ruta.c_str());
//              ROS_INFO("Fichero: %s",partes[1].c_str());
//              /*ROS_INFO("Ruta 1: %s", p.relative_path().string().c_str());
//              ROS_INFO("Ruta 2: %s", p.parent_path().string().c_str());
//              ROS_INFO("Ruta 3: %s", p.root_path().string().c_str());/**/
//            }else{
//              //Como tenemos una ruta se la añadimos al contenido
//              partes[1]=ruta+"/"+partes[1];
//            }/**/


//            std::ifstream stream(partes[1]);
//            if(stream.good()){
//              std::string linea;
//              while(!stream.eof()){
//                linea.clear();
//                std::getline(stream, linea);
//                ROS_INFO("Proceso %s",linea.c_str());
//                Comandos::procesar(linea, robot);
//              }

//            }else{
//              ROS_INFO("No se ha podido abrir el fichero %s",partes[1].c_str());

//            }
//            stream.close();
//            }
//            break;
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
//  for (int k = 0; k < 6; k++) {
//   msg1.points[0].positions[k] =jointvalues[k]; //array [i]
//                              }
//  msgolder = msg1;
return msg1;
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
  ui->outputText->setPlainText(ui->outputText->toPlainText()+tr("Ejecutando Movimiento ")+output+tr("... \n"));//+tr("\n"));
}
void MainWindow::updateError(){
//  error=QString::fromLocal8Bit(process.readAllStandardError());
//  //ui->outputText->setPlainText(output+tr("\n")+error);
//  ui->outputText->setPlainText(ui->outputText->toPlainText()+error);//+tr("\n"));
//  process.terminate();
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
