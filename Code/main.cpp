#include "Ui/mainwindow.h"
#include <iostream>
#include <QApplication>
#include <QByteArray>
#include <QLabel>
#include <QFile>




int main(int argc , char *argv[])
{
    QApplication app(argc,argv);

    MainWindow application;
    application.resize(1250,800);
    application.setMinimumSize(1250,800);
    application.setMaximumSize(1250,800);
    application.show();

    return app.exec();

}
