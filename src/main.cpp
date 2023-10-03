#include <QApplication>

#include "mainwindow.h"
#include "myglwidget.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QCoreApplication::setOrganizationName("21shcool21");

  QCoreApplication::setApplicationName("3D_VIEWER_S");

  MainWindow w;
  w.show();

  return a.exec();
}
