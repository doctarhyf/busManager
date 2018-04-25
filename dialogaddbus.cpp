#include "dialogaddbus.h"
#include "ui_dialogaddbus.h"

DialogAddBus::DialogAddBus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddBus)
{
    ui->setupUi(this);

    setWindowTitle(tr("Ajouter Bus"));
}

DialogAddBus::~DialogAddBus()
{
    delete ui;
}

void DialogAddBus::accept()
{
    if(ui->lineEditBusName->text() != ""){
        emit ajouterBus(ui->lineEditBusName->text(), ui->spinBoxBusCap->value(), ui->checkBoxBusIsActive->isChecked(), ui->lineEditBusNumPlate->text());

        //qDebug() << ui->lineEditBusNumPlate->text();

        QDialog::accept();
    }
}
