#include "mainwindowticketer2.h"
#include "ui_mainwindowticketer2.h"


MainWindowTicketer2::MainWindowTicketer2(QWidget *parent, int userID) :
    QMainWindow(parent),
    ui(new Ui::MainWindowTicketer2)
{
    ui->setupUi(this);



    uid = QString::number(userID);
    dgPersonalReport = new DialogPersonalReport(this, userID);

    connect(dgPersonalReport, SIGNAL(onWindowClosed(const QCloseEvent*)), this, SLOT(on_personalWindowClose(const QCloseEvent*)));



    setupMainGUI();
    clearLabels();


    model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM view_timetable2");
    ui->tableViewBusSched->setModel(model);

    ui->tableViewBusSched->hideColumn(0);

    passTypes.insert("Homme","m");
    passTypes.insert("Femme","f");
    passTypes.insert("Enfant","c");

}

MainWindowTicketer2::~MainWindowTicketer2()
{
    delete model;
    delete ui;
}

void MainWindowTicketer2::clearLabels()
{
    ui->labelBusName->clear();
    ui->labelDepTime->clear();
    ui->labelDriversName->clear();
    ui->labelLabelDest->clear();
    ui->labelNumEmptyPlaces->clear();
}

void MainWindowTicketer2::setupMainGUI()
{

    ui->actionRapport->setChecked(false);

    setWindowTitle("Bus Manager - Ticketer Panel");

    setCentralWidget(ui->tableViewBusSched);



    QDockWidget* dwInfos = new QDockWidget;
    QDockWidget* dwMsgs = new QDockWidget;

    dwInfos->setWindowTitle("Info Ticket");
    dwMsgs->setWindowTitle("Messages avec Admin");

    dwInfos->setAllowedAreas(Qt::NoDockWidgetArea | Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    dwMsgs->setAllowedAreas(Qt::NoDockWidgetArea | Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea | Qt::BottomDockWidgetArea);

    dwMsgs->setWidget(ui->widgetMessages);
    dwInfos->setWidget(ui->widgetInfos);

    addDockWidget(Qt::RightDockWidgetArea, dwInfos, Qt::Vertical);
    addDockWidget(Qt::RightDockWidgetArea, dwMsgs, Qt::Vertical);

    dwInfos->setFeatures(QDockWidget::NoDockWidgetFeatures | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    dwMsgs->setFeatures(QDockWidget::NoDockWidgetFeatures | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);



    QLabel *statusLabel = new QLabel("My Ticketer ID : <strong>" + uid + "</strong>");
    statusBar()->addPermanentWidget(statusLabel);

}






void MainWindowTicketer2::on_tableViewBusSched_clicked(const QModelIndex &index)
{
    QMap<QString, QStringList> buses = dbManager->getBusList();
    int idx = index.row();
    QString idxStr = QString::number(idx);

    /*
     * 0 Numero
     * 1 Nom de Bus
     * 2 Nombre de Place
     * 3 Nom Chauffeur
     * 4 Destination
     * 5 Date Depart
     * 6 Heure Depart
     *
    */
    ui->labelBusName->setText(  model->record(index.row()).value(1).toString());
    ui->labelNumEmptyPlaces->setText(  model->record(index.row()).value(2).toString());
    ui->labelDriversName->setText(  model->record(index.row()).value(3).toString());
    ui->labelLabelDest->setText(  model->record(index.row()).value(4).toString());
    ui->labelDepTime->setText(  model->record(index.row()).value(5).toString());
    //ui->label->setText(  model->record(index.row()).value(6).toString());
}

void MainWindowTicketer2::on_actionRapport_triggered()
{
    if(dgPersonalReport->isVisible()){
        dgPersonalReport->setVisible(false);
    }else{
        dgPersonalReport->setVisible(true);
    }

    //ui->actionRapport->setChecked(dgPersonalReport->isVisible());
}

void MainWindowTicketer2::on_actionRapport_toggled(bool arg1)
{
    dgPersonalReport->setVisible(!arg1);
}

void MainWindowTicketer2::on_personalWindowClose(const QCloseEvent *e)
{
    ui->actionRapport->setChecked(false);


}

void MainWindowTicketer2::on_actionSe_Deconnecter_triggered()
{
    int rep = QMessageBox::question(this, "Etes vous sur de vouloir quitter?","Etes vous sur de vouloir vous deconnecter?", QMessageBox::Yes | QMessageBox::No);

    if(rep == QMessageBox::Yes){
        emit deconnexion();
    close();

   }
}

void MainWindowTicketer2::on_pushButtonBuyTicket_clicked()
{
    bool foundError = false;

    QString passName = ui->lineEditPassName->text();
    QString passPhone = ui->lineEditPassPhone->text();
    QString passType = passTypes.value(ui->comboBoxPassType->currentText());
    QString passEmail = ui->lineEditPassEmail->text();

    if(passName.isEmpty()){
        foundError = true;
    }

    if(passPhone.isEmpty()){
        foundError = true;
    }

    if(foundError){
        QMessageBox::warning(this, tr("Erreur veuillez remplir tous les champs obligatoires"), tr("Erreur veuillez remplir tous les champs obligatoires"));
        return;
    }



    qDebug() << "PASS NAME : " << passName;
    qDebug() << "PASS PHONE : " << passPhone;
    qDebug() << "PASS EMAIL : " << passEmail;
    qDebug() << "PASS TYPE : " << passType;


    QSqlQuery q("INSERT INTO ticket (ticketer_id, ticket_date_time, ticket_canc, ticket_pass_name, ticket_pass_type, ticket_pass_phone, ticket_orig, ticket_dest, ticket_price, ticket_email) VALUES (:tktrID, :t_date, :canc, :passName, :passType, :passPhone, :orig, :dest, :price, :email)");


    q.bindValue(":tktrID", uid);
    q.bindValue(":t_date",'2017-04-22 12:59:00');
    q.bindValue(":canc", "0");
    q.bindValue(":passName",passName);
    q.bindValue(":passType",passType);
    q.bindValue(":passPhone",passType);
    q.bindValue(":orig", "Lubumbashi");
    q.bindValue(":dest",'destination');
    q.bindValue(":price","4000");
    q.bindValue(":email", passEmail);


    if(q.exec()){
        QMessageBox::information(this, tr("Le ticket a ete bien ajoute a la base de donnee"), tr("Le ticket a ete bien ajoute a la base de donnee"));

    }else{
       QMessageBox::warning(this, tr("Erreur ajout ticket a la base de donnee"),tr("Erreur ajout ticket a la base de donnee"));
    }


    qDebug() << q.lastError().text();
}

void MainWindowTicketer2::on_pushButtonSendMessage_clicked()
{
    if(!ui->lineEditTicketerMsg->text().isEmpty()){
    ui->textEditMsgBoard->append("<strong>Ticketeur :</strong>" + ui->lineEditTicketerMsg->text());
    ui->lineEditTicketerMsg->clear();
    }
}

void MainWindowTicketer2::on_lineEditTicketerMsg_returnPressed()
{
    on_pushButtonBuyTicket_clicked();
}

void MainWindowTicketer2::on_actionImprimer_Rapport_triggered()
{
    QMessageBox::warning(this,tr("Erreur Imprimante introuvable"), tr("Erreur, aucune imprimante n'a ete trouvee, veuillez connecter une imprimante!"));
}
