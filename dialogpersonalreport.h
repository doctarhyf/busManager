#ifndef DIALOGPERSONALREPORT_H
#define DIALOGPERSONALREPORT_H

#include <QDialog>
#include <QtDebug>
#include "dbmanager.h"

namespace Ui {
class DialogPersonalReport;
}

class DialogPersonalReport : public QDialog
{
    Q_OBJECT

public:

    explicit DialogPersonalReport(QWidget *parent, int newTicketerID);
    ~DialogPersonalReport();

    int getTicketerID() const;
    void setTicketerID(int value);

private:
    Ui::DialogPersonalReport *ui;
    DBManager *dbManager;
    QSqlQueryModel *model;
    int ticketerID = 0;
    void setup();


protected:
    void closeEvent(QCloseEvent *e);

signals:
    void onWindowClosed(const QCloseEvent*e);
};

#endif // DIALOGPERSONALREPORT_H
