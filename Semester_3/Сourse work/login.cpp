#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Login"));

}
Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_3_clicked()
{
    this->close();
}

void Login::on_pushButton_4_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->label_3->clear();
}

void Login::on_pushButton_2_clicked()
{
    Register *newuser = new Register;
    newuser->show();
    this->close();
}

void Login::on_pushButton_clicked()
{
    QString username=ui->lineEdit->text();
    QString password=ui->lineEdit_2->text();
    QString userid;
    QString count;
    QSqlQuery query;
    username=username.simplified();
    password=password.simplified();
    username=username.toLower();
    int login=0;
    int error=0;
    if(username=="" || password=="")
    {        error= -1;
    }
    else {  // ----------------------USERNAME NOT NULL AND PASSWORD NOT NULL----------
    query.exec("Select count(*) as counter from users where username='"+username+"'");
    query.next();
    count = query.value(0).toString();
    if(count=="0")
       {
           error=1;
       }
    else if ( count=="1")
    {

        query.exec("Select * from users where username='"+username+"'");
        query.next();
        userid = query.value(0).toString();
        if(password == query.value(2).toString())
         {
             login=1;
         }
        else
        {

            error=2;

        }
    }
        } // ----------------------USERNAME NOT NULL AND PASSWORD NOT NULL----------
    if(login==1)
    {
        Diary *user = new Diary(userid);
        user->show();
        this->close();
    }
    else if (error==-1) {

        ui->label_3->setText(tr("<font color=red>Enter Username and Password</font>"));
        ui->label_3->setAlignment(Qt::AlignCenter);
    }
    else if(error==2)
    {
        ui->label_3->setText(tr("<font color=red>Username and Password Do Not Match</font>"));
        ui->label_3->setAlignment(Qt::AlignCenter);

    }

    else if(error==1)
    {
        ui->label_3->setText(tr("<font color=red>Username Doesn't Exist. Make Yourself a new Diary</font>"));
        ui->label_3->setAlignment(Qt::AlignCenter);
    }

}
