#include "dialogaddroute.h"
#include "ui_dialogaddroute.h"

DialogAddRoute::DialogAddRoute(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddRoute)
{
    ui->setupUi(this);
    setWindowTitle("Ajouter Trajet");

    QMap<QString, QStringList> dests = dbManager.getDestinations();
    QList<QString> dest_keys = dests.keys();
    QList<QStringList> dest_vals = dests.values();

    for(int i = 0; i < dest_keys.size(); ++i){
        ui->comboBoxOrigine->insertItem(i, dest_vals[i][1]);
        ui->comboBoxDest->insertItem(i, dest_vals[i][1]);
    }


}

DialogAddRoute::~DialogAddRoute()
{
    delete ui;
}

void DialogAddRoute::accept()
{
    int origine_id = QString(dbManager.getDestinationsWithNamesForKeys().value(ui->comboBoxOrigine->currentText()).at(0)).toInt();
    int dest_id = QString(dbManager.getDestinationsWithNamesForKeys().value(ui->comboBoxDest->currentText()).at(0)).toInt();

    if(origine_id == dest_id){
        QMessageBox::critical(this, "Origine and destination cant be the same", "Origine and destination cant be the same");
        return;
    }

    if(ui->lineEditPrice->text() == ""){
        QMessageBox::critical(this, "Put some price", "Price cant be empty, enter a price!");
        return;
    }

    emit addRoute(origine_id, dest_id, true, (double)ui->lineEditPrice->text().toDouble());
    QDialog::accept();

}
