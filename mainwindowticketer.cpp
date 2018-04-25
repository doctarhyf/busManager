#include "mainwindowticketer.h"
#include "ui_mainwindowticketer.h"

MainWindowTicketer::MainWindowTicketer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowTicketer)
{
    ui->setupUi(this);



    adminRobotMessages << "<strong>Admin :</strong>J'ai besoin du rapport des ventes SVP!";
    adminRobotMessages << "<strong>Admin :</strong>Ne pas oublier de se deconnecter avant de quitter la machine SVP!";
    adminRobotMessages << "<strong>Admin :</strong>Eviter des erreurs betes SVP!";

    routeExists= false;
    dbManager = new DBManager;
    updateRouteStatusAndPrice("");

    priceLabelCss = QString(" {font:18pt bold}");

    auto flags = windowFlags();
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);

    setWindowTitle(tr("Ticketer Panel - Bus Manager V1.0"));
    QSettings set;

    labelStatus = new QLabel;
    statusBar()->addPermanentWidget(labelStatus);


    startTimer(1);

    setupTicketsDetsGUI();

    toggleTicketGUI(false);

    hideUnsuedWidgets();

    qDebug() << "Myticketer id is " << ticketer_id;

}

void MainWindowTicketer::hideUnsuedWidgets()
{
    ui->label_13->hide();
    ui->label_14->hide();
    ui->dateEditTicketDate->hide();
    ui->timeEditTicketTime->hide();
}

MainWindowTicketer::~MainWindowTicketer()
{
    delete ui;
    delete dbManager;
}

void MainWindowTicketer::on_actionDeconnexion_triggered()
{
    int rep = QMessageBox::question(this, "Etes vous sur de vouloir quitter?","Etes vous sur de vouloir vous deconnecter?", QMessageBox::Yes | QMessageBox::No);

    if(rep == QMessageBox::Yes){
        emit deconnexion();
    close();

   }
}

void MainWindowTicketer::on_actionVendre_Ticket_triggered()
{

}

void MainWindowTicketer::on_pushButtonToday_clicked()
{
    qDebug() << "Today ...";
}

void MainWindowTicketer::setupTicketsDetsGUI()
{
    ui->dateEditTicketDate->setDate(QDate::currentDate());
    ui->timeEditTicketTime->setTime(QTime::currentTime());

    int i = 0;
    foreach(QStringList destd, dbManager->getDestinations()){
        ui->comboBoxDest->insertItem(i,destd.at(1));
        ui->comboBoxOrigine->insertItem(i,destd.at(1));
        i++;
    }

    ui->labelRoutePrice->setStyleSheet(" {font:18pt bold}");
}

void MainWindowTicketer::toggleTicketGUI(bool toggle)
{
    ui->groupBoxInfoPassenger->setVisible(toggle);
    ui->groupBoxInfoTicket->setVisible(toggle);
    ui->groupBoxEmail->setVisible(toggle);
    //ui->groupBoxMessageBoard->setVisible(!toggle);
    //ui->groupBoxTicketDetails->setVisible(toggle);

    ui->pushButtonSellTicket->setVisible(toggle);
    ui->pushButtonNewTicket->setVisible(!toggle);
    ui->actionNouveau_Ticket->setEnabled(!toggle);



}

void MainWindowTicketer::updateRouteStatusAndPrice(const QString &statusMessage, const QStringList& rteData, bool toggle)
{
    ui->labelRouteStatus->setText(statusMessage);
    ui->labelRouteStatus->setVisible(toggle);
    if(rteData.size() > 4){
        ui->labelRoutePrice->setText(rteData.at(4));
        //ui->labelRoutePrice->setStyleSheet(priceLabelCss);
    }
    qDebug() << "============= updateRouteStatusAndPrice ===============";
    qDebug() << rteData;
}

void MainWindowTicketer::setPassengerType(const QString &passType)
{
    qDebug() << "Passenger type : " << passType;
}

void MainWindowTicketer::clearAllFields()
{
    ui->lineEditPassengerName->clear();
    ui->lineEditPassengerPhone->close();
    ui->lineEditTicketEmail->clear();
    ui->lineEditTicketSearch->clear();
}

void MainWindowTicketer::timerEvent(QTimerEvent *e)
{
    ui->labelCurDateTime->setText(QDate::currentDate().toString() + ", " + QTime::currentTime().toString());
    labelStatus->setText(ui->labelCurDateTime->text());



/*
    if(time % 3 == 0){
        ui->textEditMsgBoard->append("<strong>Admin :</strong> " + adminRobotMessages.at(msgID));
        if(msgID == 2){
            msgID = 0;
        }
    }

    msgID ++;
    time ++;*/

}



void MainWindowTicketer::on_pushButtonNewTicket_clicked()
{
    toggleTicketGUI(true);
}

void MainWindowTicketer::on_pushButtonSellTicket_clicked()
{

    if(ui->lineEditPassengerName->text() == ""){

        QMessageBox::critical(this, "Nom du passager manquant", "Veuillez entrer le nom du passager SVP!");
        return;

    }

    if(routeExists == false){
        QMessageBox::critical(this, "Trajet non existant", "Choisissez un trajet existant!");
        return;
    }

    toggleTicketGUI(false);

    QStringList ticketData;
    QString passType("m");
    if(ui->radioButtonPassengerTypeF->isChecked()) passType = "f";
    if(ui->radioButtonPassengerTypeC->isChecked()) passType = "c";
    int orig_id = -1;
    int dest_id = -1;
    //Ticket Data
    /*
     * Ticketer id
     * Nom
     * Passenger Type
     * Passenger Phone
     * orig
     * dest
     * date_time
     * price
     * email

    */

    ticketData << QString::number(ticketer_id);
    ticketData << ui->lineEditPassengerName->text();
    ticketData << passType;
    ticketData << ui->lineEditPassengerPhone->text();
    ticketData << ui->comboBoxOrigine->currentText();
    ticketData << ui->comboBoxDest->currentText();
    ticketData << "0000-00-00 00:00:00";//ui->dateEditTicketDate->date().toString() + " " + ui->timeEditTicketTime->time().toString();
    ticketData << ui->labelRoutePrice->text();
    ticketData << ui->lineEditTicketEmail->text();

    int tid = -1;



    if(dbManager->sellTicket(ticketData, tid)){
        QMessageBox::information(this, "Ticket vendu!", "Le ticket a ete vendu correctement");

        ticketData << QString::number(tid);
        showSoldTicket(ticketData);

        clearAllFields();

    }else{
        QMessageBox::critical(this, "Erreur ajout ticket", "Erreu ajout ticket a la base de donnee!");
    }



    qDebug() << ticketData;

}

void MainWindowTicketer::on_actionNouveau_Ticket_triggered()
{
    toggleTicketGUI(true);
}

void MainWindowTicketer::on_comboBoxOrigine_currentIndexChanged(const QString &arg1)
{


    int orig_id = dbManager->getDestinationsWithNamesForKeys().value(arg1).at(0).toInt();
    int dest_id = dbManager->getDestinationsWithNamesForKeys().value(ui->comboBoxDest->currentText()).at(0).toInt();
    //qDebug() << " =========>>>>>>>>> " << orig_id << " " << dest_id;

    bool routeFound;
    QStringList rteData = dbManager->getRouteData(orig_id, dest_id, routeFound);
    routeExists = routeFound;
    if(routeFound == false){
        qDebug() << "Route doesnt exist orig : " << orig_id << " dest : " << dest_id;
        updateRouteStatusAndPrice("Ce trajet n'existe pas!");
    }else{
        updateRouteStatusAndPrice("",rteData, false);

    }
}

void MainWindowTicketer::on_comboBoxDest_currentIndexChanged(const QString &arg1)
{
    int dest_id = dbManager->getDestinationsWithNamesForKeys().value(arg1).at(0).toInt();
    int orig_id;
    QString key = ui->comboBoxOrigine->currentText();
    QStringList station = dbManager->getDestinationsWithNamesForKeys().value(key);
    QMap<int, QString> stationData;
    for(int i = 0; i < station.length(); ++i){
        if(i == 0){
            orig_id = station.at(i).toInt();
        }
    }
    //qDebug() << " =========>>>>>>>>> " << orig_id << " " << dest_id;
    bool routeFound;
    QStringList rteData = dbManager->getRouteData(orig_id, dest_id, routeFound);
    this->routeExists = routeFound;
    if(routeFound == false){
        qDebug() << "Route doesnt exist orig : " << orig_id << " dest : " << dest_id;
        updateRouteStatusAndPrice("Ce trajet n'existe pas!");
    }else{

        updateRouteStatusAndPrice("", rteData, false);
    }


}

void MainWindowTicketer::showSoldTicket(const QStringList &ticketData)
{

    qDebug() << "========= SHOW SOLD TICKET =========";
    //Ticket Data
    /*
     * 0: Ticketer id
     * 1: Nom
     * 2: sex
     * 3: enfant?
     * 4: orig
     * 5: dest
     * 6: date_time
     * 7: price
     * 8: email
     * 9: lastInsertID

    */
    QString ticketStr("----------------------------------\r\n");
    ticketStr.append("Ticket number : " + ticketData.at(9));

    ui->textEdit->setText(ticketStr);

}
int MainWindowTicketer::getTicketer_id() const
{
    return ticketer_id;
}

void MainWindowTicketer::setTicketer_id(int value)
{
    ticketer_id = value;
}




void MainWindowTicketer::on_radioButtonTypeH_clicked(bool checked)
{
    setPassengerType("h");
}

void MainWindowTicketer::on_radioButtonPassengerTypeF_clicked(bool checked)
{
    setPassengerType("f");
}

void MainWindowTicketer::on_radioButtonPassengerTypeC_clicked(bool checked)
{
    setPassengerType("c");
}

void MainWindowTicketer::on_pushButtonSendMsgToAdmin_clicked()
{
    ui->textEditMsgBoard->append("<strong>Ticketeur :</strong>" + ui->lineEditTicketerText->text());
}



void MainWindowTicketer::on_pushButtonPrintTicket_clicked()
{
    QMessageBox::information(this, tr("Print not yet suported"), tr("Print not yet supported"));
}
