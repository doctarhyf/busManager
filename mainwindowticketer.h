#ifndef MAINWINDOWTICKETER_H
#define MAINWINDOWTICKETER_H

#include <QMainWindow>
#include <QtCore>
#include <QtDebug>
#include <QtGui>
#include <QtDebug>
#include <QLabel>
#include <QMessageBox>
#include <QtPrintSupport>
#include "dbmanager.h"

namespace Ui {
class MainWindowTicketer;
}

class MainWindowTicketer : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowTicketer(QWidget *parent = 0);
    ~MainWindowTicketer();

    int getTicketer_id() const;
    void setTicketer_id(int value);

private slots:
    void on_actionDeconnexion_triggered();

    void on_actionVendre_Ticket_triggered();

    void on_pushButtonToday_clicked();



    void on_pushButtonNewTicket_clicked();

    void on_pushButtonSellTicket_clicked();

    void on_actionNouveau_Ticket_triggered();

    void on_comboBoxOrigine_currentIndexChanged(const QString &arg1);

    void on_comboBoxDest_currentIndexChanged(const QString &arg1);



    void on_radioButtonTypeH_clicked(bool checked);

    void on_radioButtonPassengerTypeF_clicked(bool checked);

    void on_radioButtonPassengerTypeC_clicked(bool checked);

    void on_pushButtonSendMsgToAdmin_clicked();



    void on_pushButtonPrintTicket_clicked();

signals:
    void deconnexion();

private:
    void hideUnsuedWidgets();
    void showSoldTicket(const QStringList& ticketData);
    int ticketer_id;
    bool routeExists;
    QString priceLabelCss;
    Ui::MainWindowTicketer *ui;
    QLabel *labelStatus;
    DBManager *dbManager;
    void setupTicketsDetsGUI();

    void toggleTicketGUI(bool toggle);
    void updateRouteStatusAndPrice(const QString& statusMessage, const QStringList &rteData = QStringList(), bool toggle = true);
    void setPassengerType(const QString& passType);
    void clearAllFields();
    QStringList adminRobotMessages;


protected:
    void timerEvent(QTimerEvent *e);

};

#endif // MAINWINDOWTICKETER_H
