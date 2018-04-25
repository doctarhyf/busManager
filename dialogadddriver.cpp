#include "dialogadddriver.h"
#include "ui_dialogadddriver.h"

DialogAddDriver::DialogAddDriver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddDriver)
{
    ui->setupUi(this);
}

DialogAddDriver::~DialogAddDriver()
{
    delete ui;
}

void DialogAddDriver::on_buttonBox_accepted()
{

    if(ui->lineEditDriverFullName->text().isEmpty())
        return;
    emit addNewDriver(ui->lineEditDriverFullName->text(), ui->lineEditDriverPhoneNumber->text());

    QDialog::accept();
}
