#include "contacts.h"
#include "ui_contacts.h"

contacts::contacts(QString userid ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::contacts)
{
    this->userid=userid;
    ui->setupUi(this);
    this->len=40;
    this->showContacts(this->userid);


}

contacts::~contacts()
{
    delete ui;
}

void contacts::on_pushButton_9_clicked()
{
    ui->label_10->setText("");

    QString name = ui->lineEdit_1->text();
    QString phone =ui->lineEdit_2->text();
    QString email =ui->lineEdit_3->text();

    name=name.simplified();
    phone=phone.simplified();
    email=email.simplified();
    name=name.toUpper();


        // ----------------- error = -1 --- used if any field is empty------with the distinct flag-----
    if(name=="")
    {
        ui->label_10->setText(tr("<font color=red>Enter The Name</font>"));
        return;
    }
    if(name.length()>30)
    {
        ui->label_10->setText(tr("<font color=red>Enter shorter name</font>"));
        return;
    }
    if(phone=="" && email =="")
    {
        ui->label_10->setText(tr("<font color=red>Enter The Phone or Email</font>"));
        return;
    }
    if(phone.length()>30)
    {
        ui->label_10->setText(tr("<font color=red>Enter shorter phone</font>"));
        return;
    }
    if(email.length()>30)
    {
        ui->label_10->setText(tr("<font color=red>Enter shorter email</font>"));
        return;
    }
    QSqlQuery query;
    if(query.exec("select count(*) as counter from contacts where userid='"+userid+"' and name ='"+name+"'"))
    {

    query.next();
    QString namecount=query.value(0).toString();
    if(namecount=="1")
       {
         ui->label_10->setText("<font color=red>This name is already Present.</font>");
         return ;
       }
    }



    // All Details correct ... Add the contact

    QString cid;

    int cno;
    query.exec("SELECT MAX(contactid) as total FROM contacts");
    query.next();
    cid = query.value(0).toString();
    cno = cid.toInt();
    cno++;
    cid.setNum(cno);


    if ( query.exec("INSERT INTO contacts VALUES('"+cid+"','"+this->userid+"','"+name+"','"+phone+"','"+email+"')"))
    {
        ui->label_10->setText(tr("<font color=green>You have added the contact successfully.</font>"));
        this->showContacts(this->userid);
        this->on_pushButton_clicked();
    }
    else
        ui->label_10->setText(tr("<font color=red>Your contact was not added because of database error.</font>"));


}

void contacts::showContacts(QString userid)
{
    ui->list->clear();
    QSqlQuery query;
    QString name="NAME",phone="PHONE",email="EMAIL",text;
    name=name.leftJustified(this->len,' ',true);
    phone=phone.leftJustified(this->len,' ',true);
    email=email.leftJustified(this->len,' ',true);;
    text=name+phone+email;
    ui->list->addItem(text);

    if(query.exec("select * from contacts where userid='"+userid+"' order by name"))
    {
        while(query.next())
        {

            name=query.value(2).toString().leftJustified(this->len,' ',true);
            phone=query.value(3).toString().leftJustified(this->len,' ',true);
            email=query.value(4).toString().leftJustified(this->len,' ',true);;
            text=name+phone+email;
            ui->list->addItem(text);
        }

    }
    else
    {
        ui->label_10->setText("<font color=red>Database error. Contacts can't be shown.</font>");
    }
}

void contacts::on_pushButton_10_clicked()    // ------ DELETE CONTACT------
{

    if(ui->list->count()==0 || ui->list->selectedItems().size()==0)
    {
       ui->label_10->setText("<font color=red>No Entry has been selected to delete</font>");
        return;
    }
    QString name=ui->list->currentItem()->text();
    name=name.remove(this->len,2*this->len);
    name=name.simplified();
    //QMessageBox::information(this,"Error",name);
    if(name=="")
    {
          ui->label_10->setText("<font color=red>Select an entry from the list shown below.</font>");
          return;
    }
    QSqlQuery query;

    if(query.exec("delete from contacts where userid='"+this->userid+"' and name='"+name+"'"))
    {
                  ui->label_10->setText("<font color=green>Entry Succesfully Deleted.</font>");
                  this->showContacts(this->userid);

    }
    else
                  ui->label_10->setText("<font color=red>Database Error.Note not deleted.</font>");

}

void contacts::on_pushButton_clicked()
{
    ui->lineEdit_1->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_1->setFocus();
}



void contacts::on_lineEdit_textChanged(QString search)
{
    ui->list->clear();
    QSqlQuery query;
    QString name="NAME",phone="PHONE",email="EMAIL",text;
    name=name.leftJustified(this->len,' ',true);
    phone=phone.leftJustified(this->len,' ',true);
    email=email.leftJustified(this->len,' ',true);
    text=name+phone+email;
    ui->list->addItem(text);

    if(query.exec("select * from contacts where userid='"+userid+"'  and name like '%"+search+"%' order by name "))
    {
        while(query.next())
        {

            name=query.value(2).toString().leftJustified(this->len,' ',true);
            phone=query.value(3).toString().leftJustified(this->len,' ',true);
            email=query.value(4).toString().leftJustified(this->len,' ',true);;
            text=name+phone+email;
            ui->list->addItem(text);
        }

    }
    else
    {
        ui->label_10->setText("<font color=red>Database error. Contacts can't be shown.</font>");
    }

}
