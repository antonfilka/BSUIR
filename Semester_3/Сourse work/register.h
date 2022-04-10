#ifndef REGISTER_H
#define REGISTER_H
#include <QDate>
#include <QDialog>
#include <QString>
#include <QMessageBox>
#include "login.h"

namespace Ui {
    class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_dateEdit_dateChanged(const QDate &date);

    void on_calendarWidget_selectionChanged();

    void on_pushButton_2_clicked();

    void on_calendarWidget_currentPageChanged(int year, int month);

    void on_dateEdit_editingFinished();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
