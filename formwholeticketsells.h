#ifndef FORMWHOLETICKETSELLS_H
#define FORMWHOLETICKETSELLS_H

#include <QWidget>
#include <QtDebug>
#include <QtCore>
#include <QtGui>
#include <QtSql>
#include <QTableView>

namespace Ui {
class FormWholeTicketSells;
}

class FormWholeTicketSells : public QWidget
{
    Q_OBJECT

public:
    explicit FormWholeTicketSells(QWidget *parent = 0);
    ~FormWholeTicketSells();
    void strecthTableView(QTableView *tv);


private slots:
    void on_pushButtonPrintWholeSells_clicked();

private:
    Ui::FormWholeTicketSells *ui;
    QSqlQueryModel *model;

protected:
    void keyReleaseEvent(QKeyEvent *e);
};

#endif // FORMWHOLETICKETSELLS_H
