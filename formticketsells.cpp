#include "formticketsells.h"
#include "ui_formticketsells.h"

FormTicketSells::FormTicketSells(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTicketSells)
{
    ui->setupUi(this);
    setWindowTitle(tr("Details de ventes ticketeur - NOM TICKETEUR"));

    ui->labelSellsDate->setText("<strong>" + QDate::currentDate().toString() + "</strong>");

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

}

FormTicketSells::~FormTicketSells()
{
    delete ui;
}

void FormTicketSells::onTicketerChanged(const QStringList &ticketerData)
{
    qDebug() << "FORM SELLS TICKETER CHANGED" << ticketerData;

    ui->labelSellsDate->setText("<strong>" + QDate::currentDate().toString() + "</strong>");
    ui->labelTicketerFullName->setText("<strong>" + ticketerData.at(3) + " " + ticketerData.at(4) + " " +ticketerData.at(5) + "</strong>");
}
void FormTicketSells::setTicketer_id(int value)
{
    ticketer_id = value;

    //QSqlQueryModel q("SELECT * FROM ticket WHERE ticketer_id = " + QString::number(ticketer_id));

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM ticket WHERE ticketer_id = " + QString::number(ticketer_id));
        //model->setHeaderData(0, Qt::Horizontal, tr("Name"));
        //model->setHeaderData(1, Qt::Horizontal, tr("Salary"));

        QTableView *view = ui->tableView;
        view->setModel(model);

        //strecthTableView(ui->tableView);
        //view->show();

}

void FormTicketSells::strecthTableView(QTableView *tv)
{
    for(int c = 0; c < tv->horizontalHeader()->count(); ++c){
        tv->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
}

