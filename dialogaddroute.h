#ifndef DIALOGADDROUTE_H
#define DIALOGADDROUTE_H

#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include "dbmanager.h"

namespace Ui {
class DialogAddRoute;
}

class DialogAddRoute : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddRoute(QWidget *parent = 0);
    ~DialogAddRoute();

private:
    Ui::DialogAddRoute *ui;
    DBManager dbManager;

protected:
    void accept();

signals:
    void addRoute(int orig_id, int dest_id, bool active, double price);
};

#endif // DIALOGADDROUTE_H
