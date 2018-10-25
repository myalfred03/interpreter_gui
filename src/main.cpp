#include "mainwindow.h"
#include <QApplication>
#include <ros/ros.h>

int main(int argc, char **argv)
{

  if(!ros::isInitialized())
  {
    ros::init(argc, argv, "Script_robot", ros::init_options::AnonymousName);
  }
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}
