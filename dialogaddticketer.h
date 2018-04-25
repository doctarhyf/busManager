#ifndef DIALOGADDTICKETER_H
#define DIALOGADDTICKETER_H

#include <QDialog>
#include <QFileDialog>
#include <QtDebug>
#include <QtSql>
#include <QMessageBox>
#include "dbmanager.h"


namespace Ui {
class DialogAddTicketer;
}

class DialogAddTicketer : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddTicketer(QWidget *parent = 0);

    ~DialogAddTicketer();

private slots:
    void on_toolButtonLoadPicture_clicked();

private:
    Ui::DialogAddTicketer *ui;


signals:
    void addNewTicketer(const QStringList& ticketerData);

protected:
    void accept();
};

#endif // DIALOGADDTICKETER_H
