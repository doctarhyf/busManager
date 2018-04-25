#ifndef FORMLOGIN_H
#define FORMLOGIN_H

#include <QWidget>
#include <QtDebug>
#include <QtNetwork>
#include <QtSql>
#include <QMessageBox>
#include <QMediaPlayer>

#include "mainwindowadmin.h"
#include "mainwindowticketer.h"
#include "dbmanager.h"
#include "mainwindowticketer2.h"


namespace Ui {
class FormLogin;
}

class FormLogin : public QWidget
{
    Q_OBJECT

public:
    explicit FormLogin(QWidget *parent = 0);
    //void FormLogin(QWidget *parent = 0, const QString& serverAdd = QString("127.0.0.1"));
    ~FormLogin();

private slots:
    void on_pushButtonSeConnecter_clicked();
    void onDeconnexion();
    void positionChanged(qint64 pos);
    void on_lineEditIDAgent_returnPressed();

    void on_lineEditMotDePasse_returnPressed();

    void on_checkBoxMuteIntroSound_clicked();

    void on_checkBoxMuteIntroSound_clicked(bool checked);

private:
    Ui::FormLogin *ui;
    QSqlDatabase db;
    void setupBG();
    MainWindowAdmin* admin;
    MainWindowTicketer* ticketer;
    MainWindowTicketer2* ticketer2;
    DBManager *dbManager;
    QMediaPlayer *player;
    void login();
protected:
    void showEvent(QShowEvent *e);

};

#endif // FORMLOGIN_H
