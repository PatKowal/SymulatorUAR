#include "mainwindow.h"
#include "Manager.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Manager manager;
    MainWindow w(&manager);
    w.showMaximized();
    return a.exec();
}
