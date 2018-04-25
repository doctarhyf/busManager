#ifndef DIALOGADDDRIVER_H
#define DIALOGADDDRIVER_H

#include <QDialog>

namespace Ui {
class DialogAddDriver;
}

class DialogAddDriver : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddDriver(QWidget *parent = 0);
    ~DialogAddDriver();

private slots:
    void on_buttonBox_accepted();

signals:
    void addNewDriver(const QString& driverName, const QString& driverPhone);

private:
    Ui::DialogAddDriver *ui;
};

#endif // DIALOGADDDRIVER_H
