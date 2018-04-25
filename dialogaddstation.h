#ifndef DIALOGADDSTATION_H
#define DIALOGADDSTATION_H

#include <QDialog>
#include <QtCore>
#include <QtDebug>

namespace Ui {
class DialogAddStation;
}

class DialogAddStation : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddStation(QWidget *parent = 0);
    ~DialogAddStation();

private:
    Ui::DialogAddStation *ui;

protected:
    void accept();

signals:
    void addStation(const QString &stationName, const QString &stationCode, bool active);
};

#endif // DIALOGADDSTATION_H
