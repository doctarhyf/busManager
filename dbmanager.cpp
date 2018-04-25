#include "dbmanager.h"
#include "root.h"

DBManager::DBManager()
{



    isAdmin = true;
    //QString dbPath("/Users/rhyfdocta/documents/busmanager_v10/busmanager.db");
    QString dbPath("busmanager.db");
    sqlitePath = dbPath;




    #ifdef SQLITE
    setupSQLITEDB(sqlitePath);
    qDebug() << "================= DB : SQLITE ( " +  sqlitePath + " ) =================";
    #else
    setupMySQLDB();
    qDebug() << "================= DB : MYSQL =================";
    #endif



    modelRoutes = new QStandardItemModel;

    setupModelRoutes();


}

bool DBManager::login(const QString &agentID, const QString &pwd,  int &uid)
{


    QSqlQuery query("SELECT COUNT(*) FROM admin WHERE admin_agent_id='" + agentID + "' AND admin_pwd='" + pwd + "' LIMIT 1");

       while (query.next()) {
           int count = query.value(0).toInt();
           if(count == 1){

               query = QSqlQuery("SELECT * FROM admin WHERE admin_agent_id='" + agentID + "' LIMIT 1");


               while (query.next()) {
                   user_id = query.value(0).toInt();
                   uid = user_id;
               }



               isAdmin = true;
               return true;
           }
       }

       query = QSqlQuery("SELECT COUNT(*) FROM ticketer WHERE ticketer_agent_id='" + agentID + "' AND ticketer_pwd='" + pwd + "' LIMIT 1");

          while (query.next()) {
              int count = query.value(0).toInt();
              if(count == 1){

                  query = QSqlQuery("SELECT * FROM ticketer WHERE ticketer_agent_id='" + agentID + "' LIMIT 1");

                  int i = 0;
                  while (query.next()) {

                      user_id = query.value(0).toInt();
                      uid = user_id;

                  }



                  isAdmin = false;
                  return true;
              }
          }



       return false;
}

bool DBManager::addBus(const QString &busName, int busCap, bool busIsAct,  const QString& busNumPlate)
{
    QSqlQuery query;
    query.prepare("INSERT INTO bus (bus_name, bus_cap, bus_act, bus_number_plate) "
                     "VALUES (:bus_name, :bus_cap, :bus_act, :bus_num_pl)");
       query.bindValue(":bus_name", busName);
       query.bindValue(":bus_cap", busCap);
       query.bindValue(":bus_act", (int)busIsAct);
       query.bindValue(":bus_num_pl", busNumPlate);
       return query.exec();
}

bool DBManager::addTicketer(const QStringList &ticketerData)
{

    QSqlQuery query;
    query.prepare("INSERT INTO ticketer (ticketer_agent_id, ticketer_pwd, ticketer_fname, ticketer_lname, ticketer_name, ticketer_phone, ticketer_dob) "
                      "VALUES (:agent_id, :pwd, :fname, :lname, :name, :phone, :dob)");
    query.bindValue(":agent_id", ticketerData.at(0));
    query.bindValue(":pwd", ticketerData.at(1));
    query.bindValue(":fname", ticketerData.at(2));
    query.bindValue(":lname", ticketerData.at(3));
    query.bindValue(":name", ticketerData.at(4));
    query.bindValue(":phone", ticketerData.at(5));
    query.bindValue(":dob", ticketerData.at(6));
    return query.exec();

}

void DBManager::setupMySQLDB()
{
    QSqlDatabase locdb = QSqlDatabase::addDatabase("QMYSQL");
    db = new QSqlDatabase(locdb);
    db->setHostName("127.0.0.1");
    db->setPort(8889);
    db->setUserName("root");
    db->setPassword("disck12");
    db->setDatabaseName("busmanager");

    if(!db->open()){
        qDebug() << "Error connecting to database";

    }else{
        qDebug() << "The tables" << db->tables();

        if(db->tables().isEmpty()){
            QMessageBox::critical(0, QObject::tr("Erreur connexion a la base de donnee"), QObject::tr("Le serveur n'a pas pu etre atteint, veuillez verifier votre connection"
                                                                                      " internet ou contacter l'admin. SVP!"));
        }else{
            //QMessageBox::information(0, QObject::tr("Connexion a la base de donnee avec success connectee avec success."), QObject::tr("Connexion a la base de donnee avec success connectee avec success."));

        }
    }
}

void DBManager::setupSQLITEDB(const QString& dbPath)
{
    QSqlDatabase locdb = QSqlDatabase::addDatabase("QSQLITE");

    db = new QSqlDatabase(locdb);

    db->setDatabaseName(sqlitePath );

    if(!db->open()){
        qDebug() << "Error sql \ndbpath : " << dbPath;
        //QMessageBox::critical(NULL, "Erreur connexion a la base de donnee", "La base de donnee <strong>" + sqlitePath + "</strong> est introuvable.");
    }else{
        qDebug() << "SQLIte connected!\ndbPath : " << dbPath;
    }


}
QMap<int, QStringList> DBManager::getTicketersData() const
{
    QSqlQuery q("SELECT * FROM ticketer");

    QMap<int, QStringList> ticketersData;

    while (q.next()){

        int ticketer_id = q.value(0).toInt();
        QString ticketer_agent_id = q.value(1).toString();
        QString ticketer_pwd = q.value(2).toString();
        QString ticketer_fname = q.value(3).toString();
        QString ticketer_lname = q.value(4).toString();
        QString ticketer_name = q.value(5).toString();
        QString ticketer_station_id = q.value(6).toString();
        QString ticketer_dob = q.value(7).toString();
        QString ticketer_phone = q.value(8).toString();
        QStringList tickerData;
        tickerData << QString::number(ticketer_id) << ticketer_agent_id << ticketer_pwd << ticketer_fname << ticketer_lname << ticketer_name << ticketer_station_id
                   << ticketer_dob << ticketer_phone;

        ticketersData.insert(ticketer_id, tickerData);



    }

    return ticketersData;
}

QSqlDatabase *DBManager::getDBP()
{
    return db;
}


void DBManager::setupModelRoutes() const
{


    modelRoutes->clear();
    QMap<QString, QStringList> destData = getDestinations();
    QSqlQuery q("SELECT * FROM route WHERE route_active = 1");
    QList<QStringList> data;
    while (q.next()){

        QStringList rowData;

        QString route_id = q.value(0).toString();
        QString route_origine_id = destData.value(q.value(1).toString())[1];
        QString route_dest_id = destData.value(q.value(2).toString())[1];
        QString route_active_id = q.value(3).toString();
        QString route_price_id = q.value(4).toString();

        rowData << route_id << route_origine_id << route_dest_id << route_active_id << route_price_id;
        data << rowData;

    }

    //QMap<int, QStringList> data = getDestinations();
    for(int row = 0; row < data.size(); ++row){
        for(int col = 0; col < 5; ++col){
            modelRoutes->setItem(row,col,new QStandardItem(data[row].at(col)));
        }
    }

    modelRoutes->setHeaderData(1, Qt::Horizontal, "Origine");
    modelRoutes->setHeaderData(2, Qt::Horizontal, "Destination");
    modelRoutes->setHeaderData(4, Qt::Horizontal, "Prix");


}


int DBManager::getUser_id() const
{
    return user_id;
}

QString DBManager::randString(int len)
{
    QString str;
    str.resize(len);
    for(int s = 0; s < len; ++s){
        str[s] = QChar('A' + char(qrand() % ('Z' - 'A')));

    }

    return str;
}

QMap<QString, QStringList> DBManager::getBusList()
{



    QMap<QString, QStringList> busdata;

    QSqlQuery q("SELECT * FROM bus WHERE bus_act = 1");


      while (q.next()) {
          QString bus_id = q.value(0).toString();
          QString bus_name = q.value(1).toString();
          QString bus_cap = q.value(2).toString();
          QString bus_act = q.value(3).toString();
          QString bus_number_plate = q.value(4).toString();
          QStringList data;
          data << bus_id << bus_name << bus_cap << bus_number_plate;
          busdata.insert(bus_id, data);

      }

      //qDebug() << "========= THE BUS DATA FROM INSIDE=======";
      //qDebug() << busdata;

      return busdata;
}


QMap<QString, QStringList> DBManager::getDriversList()
{



    QMap<QString, QStringList> driversData;

    QSqlQuery q("SELECT * FROM bus_drivers");


      while (q.next()) {
          QString driver_id = q.value(0).toString();
          QString driver_full_name = q.value(1).toString();
          QString driver_phone = q.value(2).toString();
          QStringList data;
          data << driver_id << driver_full_name << driver_phone;
          driversData.insert(driver_id, data);

      }

      qDebug() << "========= THE DRIVERS DATA FROM INSIDE=======";
      qDebug() << driversData;

      return driversData;
}








/*
void DBManager::setupTicketersData()
{
    QSqlQuery q("SELECT * FROM ticketer");

    while (q.next()){

        int ticketer_id = q.value(0).toInt();
        QString ticketer_agent_id = q.value(1).toString();
        QString ticketer_pwd = q.value(2).toString();
        QString ticketer_fname = q.value(3).toString();
        QString ticketer_lname = q.value(4).toString();
        QString ticketer_name = q.value(5).toString();
        QString ticketer_station_id = q.value(6).toString();
        QString ticketer_dob = q.value(7).toString();
        QString ticketer_phone = q.value(8).toString();
        QStringList tickerData;
        tickerData << QString::number(ticketer_id) << ticketer_agent_id << ticketer_pwd << ticketer_fname << ticketer_lname << ticketer_name << ticketer_station_id
                   << ticketer_dob << ticketer_phone;

        ticketersData.insert(ticketer_id, tickerData);



    }
}*/


QStandardItemModel *DBManager::getModelRoutes() const
{
    setupModelRoutes();
    return modelRoutes;
}

QSqlDatabase DBManager::getDb() const
{
    return *db;
}

/*QHash<QString, QString> DBManager::getDestinations() const
{

    QHash<QString, QString> dests;

    QSqlQuery q("SELECT * FROM destination WHERE dest_active = 1");


      while (q.next()) {
          QString dest_name = q.value(1).toString();
          QString dest_code = q.value(2).toString();
          dests.insert(dest_code, dest_name);
      }

      return dests;
}*/

QMap<QString, QStringList> DBManager::getDestinations() const
{

    QMap<QString, QStringList> dests;

    QSqlQuery q("SELECT * FROM destination WHERE dest_active = 1");


      while (q.next()) {

          QString dest_id = q.value(0).toString();
          QString dest_name = q.value(1).toString();
          QString dest_code = q.value(2).toString();
          QString dest_active = q.value(3).toString();
          QStringList data;
          data << dest_id << dest_name << dest_code << dest_active;
          dests.insert(dest_id, data);

      }

      return dests;
}




QMap<QString, QStringList> DBManager::getDestinationsWithNamesForKeys() const
{

    QMap<QString, QStringList> dests;

    QSqlQuery q("SELECT * FROM destination WHERE dest_active = 1");


      while (q.next()) {

          QString dest_id = q.value(0).toString();
          QString dest_name = q.value(1).toString();
          QString dest_code = q.value(2).toString();
          QString dest_active = q.value(3).toString();
          QStringList data;
          data << dest_id << dest_name << dest_code << dest_active;
          dests.insert(dest_name, data);

      }

      return dests;
}

QMap<QString, QStringList> DBManager::getAllActiveRoutes() const
{

    QMap<QString, QStringList> routes;

    QSqlQuery q("SELECT * FROM route WHERE route_active = 1");


      while (q.next()) {
          QString route_id = q.value(0).toString();
          QString route_origine_id = q.value(1).toString();
          QString route_dest_id = q.value(2).toString();
          QString route_active = q.value(3).toString();
          QString route_price = q.value(4).toString();
          QStringList data;
          data << route_id << route_origine_id << route_dest_id << route_active << route_price;
          routes.insert(route_id, data);

      }

      return routes;
}

bool DBManager::getIsAdmin() const
{
    return isAdmin;
}

bool DBManager::addStation(const QString &stationName, const QString &stationCode, bool active)
{
    QSqlQuery query;
    query.prepare("INSERT INTO destination (dest_name, dest_code, dest_active) "
                      "VALUES (:name, :code, :act)");
    query.bindValue(":name", stationName);
    query.bindValue(":code", stationCode);
    query.bindValue(":act", (int)active);




    return query.exec();
}

bool DBManager::addRoute(int origine_id, int dest_id, bool active, double price)
{
    QSqlQuery query;
    query.prepare("INSERT INTO route (route_origine_id, route_dest_id, route_active, route_price) "
                      "VALUES (:orig, :dest, :act, :price)");
    query.bindValue(":orig", origine_id);
    query.bindValue(":dest", dest_id);
    query.bindValue(":act", (int)active);
    query.bindValue(":price", price);

    return query.exec();
}

bool DBManager::addBusToTimeTable(int bus_id, int dest_id, int driver_id, const QString &time)
{

    QString date("1999-07-15");

    QSqlQuery query;
    query.prepare("INSERT INTO timetable (bus_id, dest_id, driver_id, trip_date, trip_time ) "
                      "VALUES (:bus_id, :dest_id, :driver_id, :trip_date, :trip_time)");
    query.bindValue(":bus_id", bus_id);
    query.bindValue(":dest_id", dest_id);
    query.bindValue(":driver_id", driver_id);
    query.bindValue(":trip_date", date);
    query.bindValue(":trip_time", time);

    bool res = query.exec();

    qDebug() << "========= ON ADD TO TIME TABLE ===========";

    return res;
}

bool DBManager::addNewDriver(const QString &driverName, const QString &driverPhone)
{
    return false;
}

bool DBManager::delBus(const QString &busID)
{
    QSqlQuery q("DELETE FROM bus WHERE bus_id = " + busID);

    return q.exec();
}




QStringList DBManager::getRouteData(int orig_id, int dest_id, bool &recFound)
{
    qDebug() << "============ GETTING ROUTE DATA ==============";
    QStringList rteData;
    recFound = false;

    QSqlQuery q("SELECT * FROM route WHERE (route_origine_id = " + QString::number(orig_id) + " AND route_dest_id = "+ QString::number(dest_id) +") OR (route_origine_id = "+QString::number(dest_id)+" AND route_dest_id = "+QString::number(orig_id)+")");

    //q.bindValue(":orig_id", orig_id);
    //q.bindValue(":dest_id", dest_id);

    while(q.next()){

        rteData << q.value(0).toString();
        rteData << q.value(1).toString();
        rteData << q.value(2).toString();
        rteData << q.value(3).toString();
        rteData << q.value(4).toString();
        recFound = true;
    }

    qDebug() << "============ END ROUTE DATA ==============";

    return rteData;
}

bool DBManager::sellTicket(const QStringList &ticketData,  int& ticketID)
{





    qDebug() << "============== SELL TICKET ================";

    qDebug() << ticketData;


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


    QSqlQuery query;
    query.prepare("INSERT INTO ticket (ticketer_id, ticket_date_time, ticket_pass_name, ticket_pass_type, ticket_pass_phone,  ticket_orig, ticket_dest, ticket_price, ticket_email) "
                  "VALUES (:ticketer_id, :date_time, :pass_name, :pass_type, :pass_phone, :orig, :dest, :price, :email)");

    query.bindValue(":ticketer_id", ticketData.at(0).toInt());
    query.bindValue(":pass_name", ticketData.at(1));
    query.bindValue(":pass_type", ticketData.at(2));
    query.bindValue(":pass_phone", ticketData.at(3) );
    query.bindValue(":orig", ticketData.at(4));
    query.bindValue(":dest", ticketData.at(5));
    query.bindValue(":date_time", ticketData.at(6));
    query.bindValue(":price", ticketData.at(7).toDouble());
    query.bindValue(":email", ticketData.at(8));
    bool res = query.exec();



    if(res){
        ticketID = query.lastInsertId().toInt();
        return true;
    }else{
        return false;
    }

}


