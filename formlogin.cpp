#include "formlogin.h"
#include "ui_formlogin.h"

FormLogin::FormLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormLogin)
{

    ui->setupUi(this);



    QString audioIntroFilePath("/Users/rhyfdocta/desktop/intro.mp3");


    player = new QMediaPlayer;
    //connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player->setMedia(QUrl::fromLocalFile(audioIntroFilePath));
    player->setVolume(100);



    setupBG();

    /*admin = new MainWindowAdmin;
    ticketer = new MainWindowTicketer;

    admin->setFormLogin(this);

    connect(admin, SIGNAL(deconnexion()), this, SLOT(onDeconnexion()));
    connect(ticketer, SIGNAL(deconnexion()), this, SLOT(onDeconnexion()));*/

    dbManager = new DBManager;

}

/*FormLogin::FormLogin(QWidget *parent, const QString &serverAdd)
{

}*/

FormLogin::~FormLogin()
{
    delete ui;
    //delete dbManager;

}

void FormLogin::on_pushButtonSeConnecter_clicked()
{
    login();

}

void FormLogin::onDeconnexion()
{
    QSettings set;
    set.clear();
    show();
}

void FormLogin::positionChanged(qint64 pos)
{
    //qDebug() << "pos changed ...";
}



void FormLogin::setupBG()
{
    QPixmap pm(":/img/img/bs_spl.png");

    pm = pm.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    QBrush b(pm);
    p.setBrush(QPalette::Window, b);
    setPalette(p);
}

void FormLogin::login()
{
    QString welcomeMsg("Veuillez entrer votre ID et mot de passe pour commencer");
    ui->labelConnexionInfo->setText(tr("Connexion ..."));

    QString agentID = ui->lineEditIDAgent->text();
    QString pwd = ui->lineEditMotDePasse->text();
    int user_id;
    if(dbManager->login(agentID, pwd, user_id)){




        if(dbManager->getIsAdmin()){
            admin = new MainWindowAdmin;
            admin->show();
            connect(admin, SIGNAL(deconnexion()), this, SLOT(onDeconnexion()));

        }else{


            /*
            ticketer = new MainWindowTicketer;
            ticketer->setTicketer_id(user_id);
            ticketer->show();
            connect(ticketer, SIGNAL(deconnexion()), this, SLOT(onDeconnexion()));*/

            ticketer2 = new MainWindowTicketer2(0, user_id);

            ticketer2->show();
            connect(ticketer2, SIGNAL(deconnexion()), this, SLOT(onDeconnexion()));


        }

         close();




    }else{
        QMessageBox::critical(this, tr("Erreur de connexion"),
                              tr("Erreur de connexion, verifiez votre connexion internet ou contacter l'administrateur de la base de donnee."));
        ui->labelConnexionInfo->setText(welcomeMsg);
    }

    ui->labelConnexionInfo->setText(welcomeMsg);
}

void FormLogin::showEvent(QShowEvent *e)
{
    qDebug() << "Show event";

    QSettings sets;
    bool playIntroSound = sets.value("playIntroSound").toBool();

    ui->checkBoxMuteIntroSound->setChecked(playIntroSound);

    if(playIntroSound){
        player->play();
    }

    qDebug() << e;
}



void FormLogin::on_lineEditIDAgent_returnPressed()
{
    login();
}

void FormLogin::on_lineEditMotDePasse_returnPressed()
{
    login();
}

void FormLogin::on_checkBoxMuteIntroSound_clicked()
{

}

void FormLogin::on_checkBoxMuteIntroSound_clicked(bool checked)
{
    QSettings sets;
    sets.setValue("playIntroSound", checked);
}
