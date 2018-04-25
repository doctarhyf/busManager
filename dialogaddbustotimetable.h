#ifndef DIALOGADDBUSTOTIMETABLE_H
#define DIALOGADDBUSTOTIMETABLE_H

#include <QDialog>
#include <QDebug>
#include "dbmanager.h"
#include <QtDebug>

namespace Ui {
class DialogAddBusToTimeTable;
}

class DialogAddBusToTimeTable : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddBusToTimeTable(QWidget *parent = 0);
    ~DialogAddBusToTimeTable();

private:
    Ui::DialogAddBusToTimeTable *ui;
    void  setupComboBoxes();
    DBManager dbManager;


protected:
    void accept();

signals:
    void ajouterBusALhoraire(int bus_id, int dest_id, int driver_id, const QString &time);
private slots:
    void on_comboBoxBus_currentIndexChanged(int index);
    void on_comboBoxRoutes_currentIndexChanged(int index);
    void on_comboBoxDrivers_currentIndexChanged(int index);

    void on_comboBoxDests_currentIndexChanged(int index);
};

#endif // DIALOGADDBUSTOTIMETABLE_H
