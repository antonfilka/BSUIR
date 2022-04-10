#ifndef CONFIRM_H
#define CONFIRM_H

#include <QDialog>
#include<QMessageBox>
#include<QString>
#include<QSqlQuery>
#include<QLabel>
namespace Ui {
    class confirm;
}

class confirm : public QDialog
{
    Q_OBJECT

public:
    explicit confirm(QString userid ,QString date, QWidget *parent = 0);
    ~confirm();
    QString userid,date;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::confirm *ui;
};

#endif // CONFIRM_H
