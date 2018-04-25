#ifndef MAINWINDOWTICKETER2_H
#define MAINWINDOWTICKETER2_H

#include <QMainWindow>
#include <QDockWidget>
#include <QtDebug>
#include "dbmanager.h"
#include <QtSql>
#include "dialogpersonalreport.h"

namespace Ui {
class MainWindowTicketer2;
}

class MainWindowTicketer2 : public QMainWindow
{
    Q_OBJECT

public:
    //explicit MainWindowTicketer2(QWidget *parent = 0);
    explicit MainWindowTicketer2(QWidget *parent = 0, int userID = -1);
    ~MainWindowTicketer2();



private slots:
    void on_tableViewBusSched_clicked(const QModelIndex &index);

    void on_actionRapport_triggered();

    void on_actionRapport_toggled(bool arg1);

    void on_personalWindowClose(const QCloseEvent*e);

    void on_actionSe_Deconnecter_triggered();

    void on_pushButtonBuyTicket_clicked();

    void on_pushButtonSendMessage_clicked();

    void on_lineEditTicketerMsg_returnPressed();

    void on_actionImprimer_Rapport_triggered();

private:
    Ui::MainWindowTicketer2 *ui;
    void clearLabels();
    void setupMainGUI();
    QLabel *labelStatus;
    DBManager *dbManager;
    QSqlQueryModel *model;
    QMap<QString, QString> udata;
    QString uid;
    DialogPersonalReport* dgPersonalReport;
    QMap<QString, QString> passTypes;


signals:
    void deconnexion();
};

#endif // MAINWINDOWTICKETER2_H
