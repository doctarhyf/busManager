#ifndef DIALOGADDBUS_H
#define DIALOGADDBUS_H

#include <QDialog>
#include <QtDebug>

namespace Ui {
class DialogAddBus;
}

class DialogAddBus : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddBus(QWidget *parent = 0);
    ~DialogAddBus();

private:
    Ui::DialogAddBus *ui;

protected:

    void accept();

signals:
    void ajouterBus(const QString& busName, int busCap, bool busAvail, const QString& busNumPlate);

};

#endif // DIALOGADDBUS_H
