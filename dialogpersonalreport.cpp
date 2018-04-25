#include "dialogpersonalreport.h"
#include "ui_dialogpersonalreport.h"



DialogPersonalReport::DialogPersonalReport(QWidget *parent, int newTicketerID) :
    QDialog(parent),
    ui(new Ui::DialogPersonalReport)
{
    ticketerID = newTicketerID;

    ui->setupUi(this);

    setWindowTitle("Mon Rapport de Vente");

    dbManager = new DBManager;

    model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM ticket WHERE ticketer_id = " + QString::number(ticketerID));
    ui->tableView->setModel(model);

    //setup();

    qDebug() << "PERS REP TKTR ID : " << ticketerID;





}

void DialogPersonalReport::setup()
{



}



DialogPersonalReport::~DialogPersonalReport()
{
    delete ui;
}
int DialogPersonalReport::getTicketerID() const
{
    return ticketerID;
}

void DialogPersonalReport::setTicketerID(int value)
{
    ticketerID = value;
}




void DialogPersonalReport::closeEvent(QCloseEvent *e)
{

    //qDebug() << "emited ... signal closeevent";
    emit onWindowClosed(e);



}
