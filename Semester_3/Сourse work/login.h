#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "dbcon.h"
#include "register.h"
#include "diary.h"
#include <QtSql>
# include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
    class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
