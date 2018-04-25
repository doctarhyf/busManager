#include "formwholeticketsells.h"
#include "ui_formwholeticketsells.h"

FormWholeTicketSells::FormWholeTicketSells(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormWholeTicketSells)
{
    ui->setupUi(this);

    setWindowTitle("Rapport de toutes les ventes");

    ui->dateEditStart->setDate(QDate::currentDate());
    ui->dateEditEnd->setDate(QDate::currentDate());



    /*
    modelWholeSell = new QSqlTableModel;
    modelWholeSell->setTable("ticket");
    modelWholeSell->select();*/

    model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM report_wholesell");


    ui->tableView->setModel(model);
    ui->tableView->setGridStyle(Qt::DotLine);



    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

FormWholeTicketSells::~FormWholeTicketSells()
{
    delete ui;
}

void FormWholeTicketSells::on_pushButtonPrintWholeSells_clicked()
{

}

void FormWholeTicketSells::keyReleaseEvent(QKeyEvent *e)
{
    qDebug() << e;

}

void FormWholeTicketSells::strecthTableView(QTableView *tv)
{
    for(int c = 0; c < tv->horizontalHeader()->count(); ++c){
        tv->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
}
