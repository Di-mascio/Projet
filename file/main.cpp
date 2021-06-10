#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.showFullScreen();
    //w.delete_record();
    w.show();
    return a.exec();
}
