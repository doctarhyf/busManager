#include "dialogaddbustotimetable.h"
#include "ui_dialogaddbustotimetable.h"

DialogAddBusToTimeTable::DialogAddBusToTimeTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddBusToTimeTable)
{
    ui->setupUi(this);

    setWindowTitle("Ajouter Bus A l'Horaire");

    setupComboBoxes();



}

DialogAddBusToTimeTable::~DialogAddBusToTimeTable()
{

    delete ui;
}

void DialogAddBusToTimeTable::setupComboBoxes()
{
    ui->comboBoxHrs->clear();
    ui->comboBoxMins->clear();

    for(int h = 6; h < 22; ++h){

        QString hrs;
        if(h < 10) {
            hrs = "0" + QString::number(h);
        }else{
            hrs = QString::number(h);
        }
        ui->comboBoxHrs->addItem(hrs);
    }

    for(int m = 0; m < 60; m +=15){

        QString mins;
        if(m < 10) { mins = "0" + QString::number(m); }
                else { mins = QString::number(m); }
        ui->comboBoxMins->addItem(mins);
    }

    QMap<QString, QStringList> map = dbManager.getBusList();

    foreach (QStringList value, map){

        int index = value.at(0).toInt();
        QString text = value.at(1);
        QVariant variant = QVariant(value);

        ui->comboBoxBus->insertItem(index, text, variant);
    }

    map = dbManager.getDriversList();

    foreach (QStringList value, map){

        int index = value.at(0).toInt();
        QString text = value.at(1);
        QVariant variant = QVariant(value);

        ui->comboBoxDrivers->insertItem(index, text, variant);
    }

    map  = dbManager.getDestinations();

    foreach (QStringList value, map){

        int index = value.at(0).toInt();
        QString text = value.at(1);
        QVariant variant = QVariant(value);

        ui->comboBoxDests->insertItem(index, text, variant);
    }

}



void DialogAddBusToTimeTable::accept()
{
    bool noError = true;


    int bus_id =  QString(ui->comboBoxBus->currentData().toStringList().at(0)).toInt();
    int dest_id =  QString(ui->comboBoxDests->currentData().toStringList().at(0)).toInt();
    int driver_id = QString(ui->comboBoxDrivers->currentData().toStringList().at(0)).toInt();
    QString time = ui->comboBoxHrs->currentText() + ":" + ui->comboBoxMins->currentText();

    if(noError){

        emit ajouterBusALhoraire(bus_id, dest_id, driver_id, time);

    }

    //QComboBox

    QDialog::accept();
}





void DialogAddBusToTimeTable::on_comboBoxBus_currentIndexChanged(int index)
{
    QStringList data = qobject_cast<QComboBox*>(sender())->currentData().toStringList();
    int dbIndex = QString(data.at(0)).toInt();


    qDebug() << "Data : " << data;
    qDebug() << "BD Index : " << dbIndex;
}

void DialogAddBusToTimeTable::on_comboBoxRoutes_currentIndexChanged(int index)
{
    QStringList data = qobject_cast<QComboBox*>(sender())->currentData().toStringList();
    int dbIndex = QString(data.at(0)).toInt();


    qDebug() << "Data : " << data;
    qDebug() << "BD Index : " << dbIndex;
}

void DialogAddBusToTimeTable::on_comboBoxDrivers_currentIndexChanged(int index)
{
    QStringList data = qobject_cast<QComboBox*>(sender())->currentData().toStringList();
    int dbIndex = QString(data.at(0)).toInt();


    qDebug() << "Data : " << data;
    qDebug() << "BD Index : " << dbIndex;
}


void DialogAddBusToTimeTable::on_comboBoxDests_currentIndexChanged(int index)
{
    QStringList data = qobject_cast<QComboBox*>(sender())->currentData().toStringList();
    int dbIndex = QString(data.at(0)).toInt();


    qDebug() << "Data : " << data;
    qDebug() << "BD Index : " << dbIndex;
}
