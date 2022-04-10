#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
     this->setWindowTitle(tr("New Catalogue"));
}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_3_clicked()
{
    this->close();
}

void Register::on_pushButton_4_clicked()
{
    Login *user = new Login;
    user->show();
    this->close();
}

void Register::on_pushButton_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->label_7->clear();
    ui->label_8->clear();
    ui->label_9->clear();
    ui->label_10->clear();
}

void Register::on_calendarWidget_clicked(const QDate &date)
{
   ui->dateEdit->setDate(date);
}

void Register::on_dateEdit_dateChanged(const QDate &date)
{
}

void Register::on_calendarWidget_selectionChanged()
{
}

void Register::on_pushButton_2_clicked()
{
    ui->label_7->setText("");
    ui->label_8->setText("");
    ui->label_9->setText("");
    ui->label_10->setText("");
    int error=0,pass=0;
    int uname=0,error_name=0,error_username=0,error_pass1=0,error_pass2=0;
    QString name = ui->lineEdit->text();
    QString username =ui->lineEdit_2->text();
    QString pass1 =ui->lineEdit_3->text();
    QString pass2 =ui->lineEdit_4->text();
    name=name.simplified();
    username=username.simplified();
    pass1=pass1.simplified();
    pass2=pass2.simplified();
    name=name.toUpper();
    username=username.toLower();


    QString count;
    QString uid;

    QDate date = ui->dateEdit->date();
    QString dob = date.toString("dd-MM-yyyy");


    QSqlQuery query;

        //error = -1 used if any field is empty
    if(name=="")
       { error_name=1; error=-1;}
    if(username=="")
      {  error_username=1;error=-1;}
    if(pass1=="")
      {  error_pass1=1; error=-1;}
    if(pass2=="")
       { error_pass2=1; error=-1;}
    if(error==0)
    {       // All Fields Entered
        query.exec("select count(*) as counter from users where username = '"+username+"'");
        query.next();
        count=query.value(0).toString();

        if(count=="0")
       {
           uname=1;     //Username available
       }
        else if ( count =="1")
           {
                error=1;        // error = 1 used for non availability of username
           }

    if(pass1==pass2)
     {   pass=1;  }       //Passwords Matched
    else
      {  error=2;   }     // error = 2 sed for passwords not matching

    }
    // All Fields Entered

    if(error==-1)
    {
        if(error_name==1)
            ui->label_7->setText(tr("<font color=red>Enter The Name</font>"));
        if(error_username==1)
            ui->label_8->setText(tr("<font color=red>Enter The Username</font>"));
        if(error_pass1==1)
            ui->label_9->setText(tr("<font color=red>Enter The Password</font>"));
        if(error_pass2==1)
            ui->label_10->setText(tr("<font color=red>Re-Enter The Password</font>"));
    }
    else if(error==1)
        ui->label_8->setText(tr("<font color=red>Username Already Exists. Choose a different one.</font>"));
    else if(error==2)
        ui->label_10->setText(tr("<font color=red>Passwords Do Not Match</font>"));


    if(uname==1 && pass==1 && error==0) // Register The Person
    {   int uno;
        query.exec("SELECT MAX(userid) as total FROM users");

        uid = query.value(0).toString();
        uno = uid.toInt();

        uno++;
        uid.setNum(uno);
        QString cur_year=QDate::currentDate().toString("yyyy");

        query.next();

        if ( query.exec("INSERT INTO users VALUES('"+uid+"','"+username+"','"+pass1+"','"+name+"','"+dob+"','"+cur_year+"')") )
        {

            QMessageBox::information(this,"Registered","You have succesfully created your diary.");
            Diary *user = new Diary(uid);
            user->show();
            this->close();
        }
        else
            QMessageBox::information(this,"Error","Your diary was not created because of database error.");


    }
}

void Register::on_calendarWidget_currentPageChanged(int year, int month)
{
}

void Register::on_dateEdit_editingFinished()
{
    QDate d = ui->dateEdit->date();
    ui->calendarWidget->setSelectedDate(d);
}
