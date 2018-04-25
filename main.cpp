
#include <QApplication>
#include "formlogin.h"
#include "mainwindowticketer2.h"
#include <QInputDialog>
#include <QtCore>
#include <QtGui>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("mulikap");
    QCoreApplication::setOrganizationDomain("mulikap.com");
    QCoreApplication::setApplicationName("mlkp");


    //QInputDialog dg;
    //dg.setTextValue("127.0.0.1");
    //dg.show();

    //QString add = QInputDialog::getText(0, "Address Serveur", "Veuillez entrer l'address serveur SVP");

    //qDebug() << add;

    FormLogin fLogin;//(0, add);
    fLogin.show();




    return a.exec();
}
