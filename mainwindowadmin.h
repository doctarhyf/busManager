#ifndef MAINWINDOWADMIN_H
#define MAINWINDOWADMIN_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QCalendarWidget>
#include "dialogaddbus.h"
#include "dbmanager.h"
#include "dialogaddstation.h"
#include "dialogaddroute.h"
#include "dialogaddticketer.h"
#include "formticketsells.h"
#include "dialogadddriver.h"
#include "formwholeticketsells.h"
#include <QStandardItemModel>
#include <QtPrintSupport>
#include <QLCDNumber>
#include <QTableView>
#include <QCloseEvent>
#include "dialogaddbustotimetable.h"


class DialogAddBus;

class FormLogin;

namespace Ui {
class MainWindowAdmin;
}

class MainWindowAdmin : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowAdmin(QWidget *parent = 0);
    ~MainWindowAdmin();

    FormLogin *getFormLogin() const;
    void setFormLogin(FormLogin *value);

private slots:
    void on_pushButtonAddBus_clicked();
    void onAddBus(const QString& busName, int busCap, bool busAvail, const QString &busNumPlate);
    void on_actionAjouter_Bus_triggered();

    void on_actionDeconnexion_triggered();

    void on_actionAjouter_Station_triggered();

    void on_actionAjouter_Trajet_triggered();

    void on_actionAjouter_Ticketeur_triggered();

    void on_pushButtonShowTicketerSells_clicked();

    void onAddNewTicketer(QStringList ticketerData);

    void on_pushButtonShowWholeSells_clicked();

    void on_listViewTicketeurs_clicked(const QModelIndex &index);

    void on_tableViewTicketers_clicked(const QModelIndex &index);

    void onAddStation(const QString &stationName, const QString &stationCode, bool active);

    void onAddRoute(int origine_id, int dest_id, bool active, double price);

    void on_actionRapport_Ventes_triggered();

    void on_pushButtonDelStation_clicked();

    void on_pushButtonAddBusTimeTable_clicked();
    void onAjouterBusALhoraire(int bus_id, int route_id, int driver_id,const QString& time);

    void on_pushButtonDelBusFromTimeTable_clicked();

    void on_pushButtonAddStation_clicked();

    void on_pushButtonAddRoute_clicked();

    void on_pushButtonAddDriver_clicked();

    void on_pushButtonAddTicketer_clicked();

    void on_AddNewDriver(const QString& driverName, const QString& driverPhone);

    void on_tableViewBusList_clicked(const QModelIndex &index);

    void on_pushButtonDelBus_clicked();

private:
    enum DialogAddType {
        DialogAddTypeBus = 0x01,
        DialogAddTypeTicketer = 0x10,
        DialogAddTypeRoute = 0x11,
        DialogAddTypeStation = 0x100
    };
    QLabel *labelStatus;
    void strecthTableView(QTableView *tv);
    Ui::MainWindowAdmin *ui;
    QSqlDatabase db;
    QSqlTableModel *modelBus, *modelStations, *modelTicketers;
    QSqlQueryModel *modelTimeTable, *modelBusDrivers;
    QStandardItemModel *modelRoutes;
    DialogAddBus dgAddBus;
    void showAddDialog(DialogAddType dialogAdd);
    void setupModelsNViews();
    DBManager *dbManager;
    FormLogin* formLogin;
    DialogAddStation dgAddStation;
    DialogAddDriver dgAddDriver;
    DialogAddRoute dgAddRoute;
    DialogAddBusToTimeTable dgAddBusTotimeTable;
    DialogAddTicketer dgAddTicketer;
    FormTicketSells *formTicketSells;
    FormWholeTicketSells * formWholeTicketSells;
    QStringList currentTicketerData;
    int currentTicketerID;
    QStringList curBusData;

protected:
    void timerEvent(QTimerEvent*e);
    void closeEvent(QCloseEvent*e);


signals:
    void deconnexion();
    void ticketerChanged(QStringList ticketerData);

};

#endif // MAINWINDOWADMIN_H
