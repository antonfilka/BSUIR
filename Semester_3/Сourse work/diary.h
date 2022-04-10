#ifndef DIARY_H
#define DIARY_H

#include <QMainWindow>
#include <QString>
#include <QSqlQuery>
#include<QPushButton>
#include<QLineEdit>
#include<QWidget>
#include<QGridLayout>
#include<QDate>
#include<QMessageBox>
#include<QStringList>
#include<QTableView>
#include<QModelIndex>
#include<QTableWidget>
#include<QHeaderView>
#include<QListWidget>
#include<QTimer>
#include <QLCDNumber>

#include"confirm.h"
#include"login.h"
#include"calculator.h"
#include"contacts.h"
#include"button.h"
#include"tetrixboard.h"
#include"tetrixpiece.h"
#include"tetrixwindow.h"

namespace Ui {
    class Diary;
}

class Diary : public QMainWindow
{
    Q_OBJECT

public:
    explicit Diary(QString userid, QWidget *parent = 0);
    void show_bdaylist(QString userid,	QListWidget  *list);
    void clear_diary(QString userid, QString year);

    QString userid;
    QString Cur_date;
    QDate current_date;
    int day;
    int month;
    int year;

    ~Diary();

private slots:
    void on_actionContacts_triggered();
    void on_actionTetris_triggered();
    void on_actionCalculator_triggered();

    void on_calendarWidget_clicked(const QDate &date);

    void on_calendarWidget_selectionChanged();

    void on_calendarWidget_currentPageChanged(int year, int month);

    void on_pushButton_clicked();

    void on_dateEdit_editingFinished();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void showTime();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::Diary *ui;
};

#endif // DIARY_H

