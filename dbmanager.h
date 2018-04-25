#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql>
#include <QtDebug>
#include <QtNetwork>
#include <QMessageBox>
#include <QtCore>
#include <QFileInfo>
#include <QMap>
#include <QStandardItemModel>
#include <QSqlQuery>




class DBManager
{



public:
    DBManager();

    bool login(const QString & agentID, const QString & pwd,  int &uid );
    bool addBus(const QString& busName, int busCap, bool busIsAct, const QString &busNumPlate);
    bool addTicketer(const QStringList& ticketerData);
    bool getIsAdmin() const;
    bool addStation(const QString& stationName, const QString& stationCode, bool active);
    bool addRoute(int origine_id, int dest_id, bool active, double price);
    bool addBusToTimeTable(int bus_id, int dest_id, int driver_id, const QString &time);
    bool addNewDriver(const QString& driverName, const QString& driverPhone);
    bool delBus(const QString& busID);

    QStringList getRouteData(int orig_id, int dest_id, bool &recFound);
    bool sellTicket(const QStringList& ticketData,  int &ticketID );

    QSqlDatabase getDb() const;
    QMap<QString, QStringList> getDestinations() const;
    QMap<QString, QStringList> getDestinationsWithNamesForKeys() const;


    QStandardItemModel *getModelRoutes() const;

    QMap<int, QStringList> getTicketersData() const;
    QSqlDatabase *getDBP();
    int getUser_id() const;
    static QString randString(int len);
    QMap<QString, QStringList> getBusList();
    QMap<QString, QStringList> getDriversList();
    QMap<QString, QStringList> getAllActiveRoutes() const;





private:
    void setupMySQLDB();
    void setupSQLITEDB(const QString& dbPath);
    QString sqlitePath;
    bool isAdmin;
    QSqlDatabase *db;
    //QMap<int, QStringList> ticketersData;
    QStandardItemModel *modelRoutes;
    void setupModelRoutes() const;
    void setupTicketersData();
    int user_id;

};

#endif // DBMANAGER_H
