#include "mainwindow.h"
#include <QApplication>
#include "QMessageBox"





int main(int argc, char *argv[])
{

  //  AccountList AccList;
  //  bool isLoggedIn = false;

    QApplication a(argc, argv);
    MainWindow w;
    w.resize(300,450);
    w.show();
    return a.exec();
}
