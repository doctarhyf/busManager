#ifndef FORMTICKETSELLS_H
#define FORMTICKETSELLS_H

#include <QWidget>
#include <QtDebug>
#include <QtCore>
#include <QtSql>
#include <QTableView>

namespace Ui {
class FormTicketSells;
}

class FormTicketSells : public QWidget
{
    Q_OBJECT

public:
    explicit FormTicketSells(QWidget *parent = 0);
    ~FormTicketSells();

    void setTicketer_id(int value);

public slots:
    void onTicketerChanged(const QStringList& ticketerData);

private:
    Ui::FormTicketSells *ui;
    int ticketer_id;
    void strecthTableView(QTableView *tv);
};

#endif // FORMTICKETSELLS_H
