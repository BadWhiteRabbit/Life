#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "molecule.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


 //   qDebug() << "X = " << w.x() << "Y = " << w.y();


    w.show();
    return a.exec();
}
