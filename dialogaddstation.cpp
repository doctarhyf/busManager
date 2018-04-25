#include "dialogaddstation.h"
#include "ui_dialogaddstation.h"

DialogAddStation::DialogAddStation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddStation)
{
    ui->setupUi(this);
    setWindowTitle("Ajouter Station");
}

DialogAddStation::~DialogAddStation()
{
    delete ui;
}

void DialogAddStation::accept()
{

    emit addStation(ui->lineEditStationName->text(), ui->lineEditStationCode->text(), ui->checkBoxActive->isChecked());
    QDialog::accept();
}
