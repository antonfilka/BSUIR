#include "confirm.h"
#include "ui_confirm.h"

confirm::confirm(QString userid ,QString date,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::confirm)
{

    ui->setupUi(this);
    this->userid=userid;
    this->date=date;
}

confirm::~confirm()
{
    delete ui;
}

void confirm::on_pushButton_clicked()
{
    QSqlQuery query;
    if(query.exec("delete from notes where userid='"+this->userid+"' and date='"+this->date+"'"))
      {  QMessageBox::information(this,"Deleted","Note for this date has been deleted.");

    this->close();
      }
    else

       QMessageBox::information(this,"Error","Database Error, Note for this date has not been deleted.");
}

void confirm::on_pushButton_2_clicked()
{
    this->close();
}
