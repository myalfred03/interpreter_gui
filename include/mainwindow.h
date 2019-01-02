#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "highlighter.h"
#include <QRegularExpression>
#include <QMessageBox>
#include <QProcess>
#include <QDebug>
#include <stdio.h>
#include <boost/filesystem.hpp>
#include <boost/thread/thread.hpp>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <ros/ros.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <std_msgs/Float32MultiArray.h>
#include <boost/bind.hpp>
//#include <moveit/robot_trajectory/robot_trajectory.h>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

  ros::Publisher joint_pub;
  ros::Subscriber joint_sub_limit;

  ros::NodeHandle nh_;
  std_msgs::Float32MultiArray limit ;
  void runloop();

//  void publishJointStates();

private:
  QIcon runIcon;
  QIcon stopIcon;
  QIcon errorIcon;
  QIcon RerrorIcon;
  Ui::MainWindow *ui;
  Highlighter *highlighter;



//  QProcess process;
  void setUpHighlighter();
  QString fileName;
  QString filePath;
  bool fileSaved;
  bool isRunning;
  bool isloop;
  //bool fileEdited;
  void initFileData();

  //remember Points[i].positions.resize(x)
  //moveit_core/robot_trajectory/src/robottrajectory.cpp
//  moveit_msgs::RobotTrajectory   trajectory;


  trajectory_msgs::JointTrajectory comandos(std::string &comando, int &i);
  trajectory_msgs::JointTrajectory msg1, msgolder;
  std::vector<std::string> split(const std::string &c, char d);
  void trajectory(const trajectory_msgs::JointTrajectory &msg);

  //--------Based on works of Robolegs------------------
  boost::shared_ptr<ros::AsyncSpinner> spinner;
  //----------------------------------------------------

  boost::thread* publisher_thread_;
  boost::mutex state_pub_mutex_;

  std::vector<double> jointvaluesOLD = {0.0,0.0,0.0,0.0,0.0,0.0};
  bool firstLoad;
  //-----------------------------


  //---------code running data---
  QString output;
  QString error;
  //-----------------------------

  //---------Read Data to File for move robot-------
//  std::ifstream file("~/Documents/Untitled.rrun");
  //------------------------------------------------
public slots:
  void changeSaveState(){
    //qDebug()<<"changed";
    if(firstLoad&&fileSaved){
        this->setWindowTitle(tr("Robot Editor Script - ")+fileName);
        firstLoad=false;
        return;
      }
    fileSaved=false;
    this->setWindowTitle(tr("Robot Editor Script - ")+fileName+tr("*"));
  }
  void jointsizeCallback(const std_msgs::Float32MultiArray::ConstPtr &msglimit);
  void newFile();
  void saveFile();
  void openFile();
  void undo();
  void redo();
  void run();

  //------------------------------
  void runFinished(int code);
  void updateOutput(std::string &info);
  void updateError();
  void updateRobot();
  void about();
public:
  void inputData(QString data);
protected:
  void resizeEvent(QResizeEvent* event)override;
  void closeEvent(QCloseEvent* event)override;
};

#endif // MAINWINDOW_H
