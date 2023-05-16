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



    QFile stylesheet("asset/Dark_style.qss");
    stylesheet.open(QFile::ReadOnly);
    application.setStyleSheet(QLatin1String(stylesheet.readAll()));


    application.show();

    return app.exec();



}
