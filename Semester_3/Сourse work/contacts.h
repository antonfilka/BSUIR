#ifndef CONTACTS_H
#define CONTACTS_H

#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QPushButton>
#include <QLineEdit>

namespace Ui {
    class contacts;
}

class contacts : public QDialog
{
    Q_OBJECT

public:
    explicit contacts(QString userid ,QWidget *parent = 0);
    QString userid;
    int len;
    ~contacts();

private:
    Ui::contacts *ui;

private slots:
    void on_lineEdit_textChanged(QString );
    void on_pushButton_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_9_clicked();
    void showContacts(QString userid);
};

#endif // CONTACTS_H
