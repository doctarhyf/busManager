#include "mainwindowadmin.h"
#include "ui_mainwindowadmin.h"

MainWindowAdmin::MainWindowAdmin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowAdmin)
{
    ui->setupUi(this);

    auto flags = windowFlags();
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);

    currentTicketerID = -1;

    setWindowTitle(tr("Admin Panel - Bus Manager V1.0"));
    setupModelsNViews();

    dgAddBus.setModal(true);
    dgAddRoute.setModal(true);
    dgAddStation.setModal(true);
    dgAddTicketer.setModal(true);
    dgAddBusTotimeTable.setModal(true);
    dgAddDriver.setModal(true);

    connect(&dgAddBus, SIGNAL(ajouterBus(QString,int,bool, QString)), this, SLOT(onAddBus(QString,int,bool, QString)));
    //connect(&dgAddRoute, SIGNAL(ajouterBus(QString,int,bool)), this, SLOT(onAjouterBus(QString,int,bool)));

    connect(&dgAddBusTotimeTable, SIGNAL(ajouterBusALhoraire(int,int, int,QString)), this, SLOT(onAjouterBusALhoraire(int, int,int,QString))
);
    connect(&dgAddTicketer, SIGNAL(addNewTicketer(QStringList)), this, SLOT(onAddNewTicketer(QStringList)));
    connect(&dgAddStation, SIGNAL(addStation(QString,QString,bool)), this, SLOT(onAddStation(QString,QString,bool)));
    connect(&dgAddRoute, SIGNAL(addRoute(int,int,bool,double)), this, SLOT(onAddRoute(int,int,bool,double)));
    connect(&dgAddDriver, SIGNAL(addNewDriver(QString,QString)), this, SLOT(on_AddNewDriver(QString,QString)));

    startTimer(1);

    ui->tabWidgetAdminPanel->setCurrentIndex(0);

    QSettings set;

    labelStatus = new QLabel;
    statusBar()->addPermanentWidget(labelStatus);

    startTimer(1);



}

MainWindowAdmin::~MainWindowAdmin()
{
    delete ui;
}

void MainWindowAdmin::on_pushButtonAddBus_clicked()
{
    showAddDialog(DialogAddTypeBus);

}

void MainWindowAdmin::on_actionAjouter_Station_triggered()
{
    showAddDialog(DialogAddTypeStation);

}


void MainWindowAdmin::onAddBus(const QString &busName, int busCap, bool busAvail,  const QString& busNumPlate)
{
    if(dbManager->addBus(busName, busCap, busAvail, busNumPlate)){
        QMessageBox::information(this, tr("Bus ajoute avec succes"), tr("Le bus a ete ajoute avec succes"));
        modelBus->select();
    }else{
        QMessageBox::critical(this, tr("Erreur ajout bus"), tr("Le bus n as pas ete ajoute"));
    }

     ui->tabWidgetAdminPanel->setCurrentIndex(0);
}

void MainWindowAdmin::showAddDialog(MainWindowAdmin::DialogAddType dialogAdd)
{

    dgAddBus.hide();
    //dgAddRoute.hide();
    dgAddStation.hide();

    switch (dialogAdd) {
    case DialogAddTypeBus:
        dgAddBus.show();
        break;
    case DialogAddTypeStation:
        dgAddStation.show();
        break;
    case DialogAddTypeRoute:
        dgAddRoute.show();
        break;

    case DialogAddTypeTicketer:
        dgAddTicketer.show();
        break;
    default:
        break;
    }
}


void MainWindowAdmin::setupModelsNViews()
{
    dbManager = new DBManager;


    ui->tableViewBusList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewBusList->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableViewRoutes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewRoutes->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableViewStations->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewStations->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableViewTicketers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewTicketers->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableViewTimeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewTimeTable->setSelectionMode(QAbstractItemView::SingleSelection);


    modelBusDrivers = new QSqlQueryModel;
    modelBusDrivers->setQuery("SELECT * FROM bus_drivers");
    ui->tableViewBusDrivers->setModel(modelBusDrivers);

    modelTimeTable = new QSqlQueryModel;

    modelTimeTable->setQuery("SELECT * FROM view_timetable2");

    qDebug() << "DB ERROR : " << dbManager->getDb().lastError().text();

    ui->tableViewTimeTable->setModel(modelTimeTable);

    modelBus = new QSqlTableModel(this, *dbManager->getDBP());

    modelBus->setTable("bus");
    modelBus->select();
    ui->tableViewBusList->setModel(modelBus);


    modelBus->setHeaderData(1,Qt::Horizontal, "Nom Bus");
    modelBus->setHeaderData(2,Qt::Horizontal, "Capacite");
    modelBus->setHeaderData(3,Qt::Horizontal, "Actif");
    modelBus->setHeaderData(4,Qt::Horizontal, "No Plaque");






    modelStations = new QSqlTableModel(this,db);
    modelStations->setTable("destination");
    modelStations->select();

    modelStations->setHeaderData(1,Qt::Horizontal, "Nom de Station");
    modelStations->setHeaderData(2,Qt::Horizontal, "Code de Station");

    ui->tableViewStations->setModel(modelStations);

    modelRoutes = dbManager->getModelRoutes();
    ui->tableViewRoutes->setModel(modelRoutes);

    modelTicketers = new QSqlTableModel(this,db);
    modelTicketers->setTable("ticketer");
    modelTicketers->select();

    modelTicketers->setHeaderData(3,Qt::Horizontal, "Nom");
    modelTicketers->setHeaderData(4,Qt::Horizontal, "Postnom");
    ui->tableViewTicketers->setModel(modelTicketers);

    strecthTableView(ui->tableViewTicketers);
    strecthTableView(ui->tableViewBusList);
    strecthTableView(ui->tableViewRoutes);
    strecthTableView(ui->tableViewStations);

    ui->tableViewBusList->hideColumn(0);

    ui->tableViewStations->hideColumn(0);
    ui->tableViewStations->hideColumn(3);

    ui->tableViewTicketers->hideColumn(0);
    ui->tableViewTicketers->hideColumn(1);
    ui->tableViewTicketers->hideColumn(2);
    ui->tableViewTicketers->hideColumn(5);
    ui->tableViewTicketers->hideColumn(6);
    ui->tableViewTicketers->hideColumn(7);
    ui->tableViewTicketers->hideColumn(8);

    ui->tableViewRoutes->hideColumn(0);
    ui->tableViewRoutes->hideColumn(3);


}

void MainWindowAdmin::timerEvent(QTimerEvent *e)
{
    //ui->labelCurDateTime->setText(QDate::currentDate().toString() + ", " + QTime::currentTime().toString());
    //labelStatus->setText(ui->labelCurDateTime->text());
}

void MainWindowAdmin::closeEvent(QCloseEvent *e)
{
    emit deconnexion();

}


FormLogin *MainWindowAdmin::getFormLogin() const
{
    return formLogin;
}

void MainWindowAdmin::setFormLogin(FormLogin *value)
{
    formLogin = value;
}


void MainWindowAdmin::on_actionAjouter_Bus_triggered()
{
    showAddDialog(DialogAddTypeBus);
}

void MainWindowAdmin::on_actionDeconnexion_triggered()
{

    int rep = QMessageBox::question(this, "Etes vous sur de vouloir quitter?","Etes vous sur de vouloir vous deconnecter?", QMessageBox::Yes | QMessageBox::No);

    if(rep == QMessageBox::Yes){
        emit deconnexion();
        close();

   }


}


void MainWindowAdmin::on_actionAjouter_Trajet_triggered()
{
    showAddDialog(DialogAddTypeRoute);
}

void MainWindowAdmin::on_actionAjouter_Ticketeur_triggered()
{
    showAddDialog(DialogAddTypeTicketer);
}

void MainWindowAdmin::on_pushButtonShowTicketerSells_clicked()
{

    formTicketSells = new FormTicketSells;
    formTicketSells->setTicketer_id(currentTicketerID);
    formTicketSells->show();
}

void MainWindowAdmin::onAddNewTicketer(QStringList ticketerData)
{


    if(dbManager->addTicketer(ticketerData)){
        QMessageBox::information(this, "Ticketeur ajoute avec success", "Le ticketer a ete ajoute avec succes a la base de donnee");
         modelTicketers->select();
    }else{
        QMessageBox::critical(this, "Erreur ajout ticketeur", "Erreur ajout ticketeur");

    }



    ui->tabWidgetAdminPanel->setCurrentIndex(4);
}



void MainWindowAdmin::on_pushButtonShowWholeSells_clicked()
{
    formWholeTicketSells = new FormWholeTicketSells;

    //connect(this, SIGNAL(ticketerChanged(QStringList)), formTicketSells, SLOT(onTicketerChanged(QStringList)));
    formWholeTicketSells->show();
    //ui->pushButtonShowWholeSells->setEnabled(false);
}

void MainWindowAdmin::on_listViewTicketeurs_clicked(const QModelIndex &index)
{
    qDebug() << modelTicketers->data(index, Qt::DisplayRole);
    qDebug() << index.row();
}

void MainWindowAdmin::on_tableViewTicketers_clicked(const QModelIndex &index)
{
    int r = index.row();
    int ticketerID = modelTicketers->record(r).value(0).toInt();

    currentTicketerID = ticketerID;
    //r += 1;
    currentTicketerData = dbManager->getTicketersData().value(ticketerID);


    ui->labelTicketerDataFnameLname->setText("<strong>" + currentTicketerData.at(3) + " " + currentTicketerData.at(4) + "</strong>");
    ui->labelTicketerDataName->setText("<strong>" + currentTicketerData.at(5) + "</strong>");
    ui->labelTicketerDataPhone->setText("<strong>" + currentTicketerData.at(8) + "</strong>");
    ui->labelTicketerDataDOB->setText("<strong>" + currentTicketerData.at(7) + "</strong>");
    ui->labelTicketerDataAgentID->setText("<strong>" + currentTicketerData.at(1) + "</strong>");
    ui->labelTicketerDataPWD->setText("<strong>" + currentTicketerData.at(2) + "</strong>");
    ui->pushButtonShowTicketerSells->setEnabled(true);
    emit ticketerChanged(currentTicketerData);
}

void MainWindowAdmin::onAddStation(const QString &stationName, const QString &stationCode, bool active)
{
    if(dbManager->addStation(stationName, stationCode, active)){

        QMessageBox::information(this, "Station ajoute avec succes", "La station <strong>" + stationName + "</strong> a ete ajoute avec succes a la base de donnee.");
        modelStations->select();
        ui->tabWidgetAdminPanel->setCurrentIndex(1);
    }else{
       QMessageBox::critical(this, "Erreur ajout station", "Erreur ajout station");

    }

}

void MainWindowAdmin::onAddRoute(int origine_id, int dest_id, bool active, double price)
{
    if(dbManager->addRoute(origine_id, dest_id, active, price)){

        QMessageBox::information(this, "Trajet ajoute avec succes", "La trajet  a ete ajoute avec succes a la base de donnee.");
        //modelRoutes->select();
        ui->tableViewRoutes->setModel(dbManager->getModelRoutes());
        ui->tabWidgetAdminPanel->setCurrentIndex(2);
    }else{
       QMessageBox::critical(this, "Erreur ajout trajet", "Erreur ajout trajet");

    }

}

void MainWindowAdmin::strecthTableView(QTableView *tv)
{
    for(int c = 0; c < tv->horizontalHeader()->count(); ++c){
        tv->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
}

void MainWindowAdmin::on_actionRapport_Ventes_triggered()
{
    on_pushButtonShowWholeSells_clicked();
}

void MainWindowAdmin::on_pushButtonDelStation_clicked()
{

}

void MainWindowAdmin::on_pushButtonAddBusTimeTable_clicked()
{
    dgAddBusTotimeTable.show();
}

void MainWindowAdmin::onAjouterBusALhoraire(int bus_id, int route_id, int driver_id, const QString &time)
{
    if(dbManager->addBusToTimeTable(bus_id, route_id, driver_id, time))
    {

        modelTimeTable->setQuery(modelTimeTable->query().lastQuery());


        QMessageBox::information(this, tr("Bus added to timetable"), tr("Bus successfully added to timetable!"));

    }else{
        QMessageBox::critical(this, tr("Error adding bus to timetable"), tr("Error adding bus to timetable"));
    }
}

void MainWindowAdmin::on_pushButtonDelBusFromTimeTable_clicked()
{

}

void MainWindowAdmin::on_pushButtonAddStation_clicked()
{
    on_actionAjouter_Station_triggered();
}

void MainWindowAdmin::on_pushButtonAddRoute_clicked()
{
    on_actionAjouter_Trajet_triggered();
}

void MainWindowAdmin::on_pushButtonAddDriver_clicked()
{
    //
}

void MainWindowAdmin::on_pushButtonAddTicketer_clicked()
{
    on_actionAjouter_Ticketeur_triggered();
}

void MainWindowAdmin::on_AddNewDriver(const QString &driverName, const QString &driverPhone)
{
    if(dbManager->addNewDriver(driverName, driverPhone)){
        QMessageBox::information(this, tr("Driver Added Successfully"), tr("Driver Added Successfully"));

    }else{
        QMessageBox::critical(this, tr("Error adding driver"), tr("Error adding driver"));
    }
}

void MainWindowAdmin::on_tableViewBusList_clicked(const QModelIndex &index)
{

    ui->pushButtonDelBus->setEnabled(true);
    int r = index.row();
    QMap<QString, QStringList> buses = dbManager->getBusList();
    curBusData = buses.values().at(r);

    qDebug() << "CUR BUS DATA : " << curBusData;



}

void MainWindowAdmin::on_pushButtonDelBus_clicked()
{
    int rep = QMessageBox::question(this, tr("Are you sure?"), tr("Are you sure that you want to procede with the operation?"), QMessageBox::Yes | QMessageBox::No);

    if(rep == QMessageBox::Yes){
        if(!curBusData.isEmpty()){

            if(dbManager->delBus(curBusData.at(0))){
                QMessageBox::information(this, tr("Bus deleted successfully"), tr("Bus deleted successfully"));
                modelBus->select();
            }else{
                QMessageBox::critical(this,tr("Error deleting bus"), tr("Error dleting bus"));
            }

        }
    }
}
