#include "dialogaddticketer.h"
#include "ui_dialogaddticketer.h"

DialogAddTicketer::DialogAddTicketer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddTicketer)
{
    ui->setupUi(this);
    setWindowTitle("Ajouter Ticketeur");

    ui->lineEditPwd->setText(DBManager::randString(10));
}

DialogAddTicketer::~DialogAddTicketer()
{
    delete ui;
}

void DialogAddTicketer::on_toolButtonLoadPicture_clicked()
{
    QString fname = QFileDialog::getOpenFileName(this, "Ouvrir photo", QDir::homePath(), "Images (*.jpg *.png *.jpeg)");
    QPixmap pm(fname);

    pm = pm.scaled(ui->labelTicketerPhoto->size());

    ui->labelTicketerPhoto->setPixmap(pm);
    qDebug() << "file name : " << fname;
}

void DialogAddTicketer::accept()
{

    QString dob = ui->comboBoxDOBYear->itemText(ui->comboBoxDOBYear->currentIndex()) + "-" +
            ui->comboBoxDOBMonth->itemText(ui->comboBoxDOBMonth->currentIndex()) + "-" +
            ui->comboBoxDOBDay->itemText(ui->comboBoxDOBDay->currentIndex());


    QStringList ticketerData;
    ticketerData << ui->lineEditAgentID->text() << ui->lineEditPwd->text() << ui->lineEditFName->text()
                 << ui->lineEditLName->text() << ui->lineEditName->text() << ui->lineEditPhone->text()
                 << dob;

    emit addNewTicketer(ticketerData);

    QDialog::accept();
}



