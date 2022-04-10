#include "diary.h"
#include "ui_diary.h"

Diary::Diary(QString userid, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Diary)
{
    ui->setupUi(this);
     this->setWindowTitle(tr("Travel - Guide"));
    QSqlQuery query;
    QString name;
    this->current_date=QDate::currentDate();

    this->userid=userid;
    this->Cur_date=QDate::currentDate().toString("dd-MM-yyyy");

    this->current_date.getDate(&this->year,&this->month,&this->day);

    query.exec("Select * from users where userid='"+this->userid+"'");
    query.next();

    name=query.value(3).toString();

    QString show_date=QDate::currentDate().toString("ddd dd-MMM-yyyy");

     ui->label->setText("<b><font color=blue>WELCOME TO TRAVEL GUIDE "+name+"</b></font>");
     ui->label_4->setText("<b><font color=red>'"+show_date+"'</b></font>");

/* Setting the GUI */

    ui->dateEdit->setDate(this->current_date);
    ui->dateEdit_2->setDate(this->current_date);
    ui->dateEdit_3->setDate(this->current_date);


    this->showMaximized();
    ui->pushButton_6->hide();

    /* Setting Dates for B'day dropdowns*/
    ui->label_10->clear();
    int z;
        for(z=1;z<32;z++)
            ui->comboBox->addItem(QString::number(z));

        for(z=1;z<13;z++)
            ui->comboBox_2->addItem(QString::number(z));

        for(z=1950;z<this->year;z++)
            ui->comboBox_3->addItem(QString::number(z));

        this->show_bdaylist(this->userid,ui->listWidget_2);

        ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
        QTimer *timer = new QTimer(this);
        ui->lcdNumber->connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
        timer->start(1000);
        showTime();

} //====> end of constructor



Diary::~Diary()
{
    delete ui;
}


void Diary::on_calendarWidget_clicked(const QDate &date)
{
    ui->dateEdit->setDate(date);
}

void Diary::on_calendarWidget_selectionChanged()
{

}

void Diary::on_calendarWidget_currentPageChanged(int year, int month)
{

}
void Diary::on_dateEdit_editingFinished()
{
    QDate d = ui->dateEdit->date();
    ui->calendarWidget->setSelectedDate(d);
}

void Diary::on_pushButton_clicked() ////-----------ADD BUTTON-------
{

    QSqlQuery query;

    QString note, noteid;

    note = ui->plainTextEdit->toPlainText().trimmed();
    if(note=="")
        ui->label_2->setText("<font color=red>Note Empty</font>");
    else
    {
    QDate date = ui->dateEdit->date();
    QString dr = date.toString("dd-MM-yyyy");


    query.exec("select count(*) as counter from notes where userid='"+this->userid+"'and dt='"+dr+"'");
    query.next();

    int flag = query.value(0).toString().toInt();

    if(flag==1){

        ui->label_2->setText("<font color=red>You have already added a note for this date. You must edit that.</font>");
    return ;

    }
    int notenum;

    noteid = query.value(1).toString();
    notenum = noteid.toInt();
    notenum++;
    noteid=noteid.setNum(notenum);

            if(!query.exec("INSERT INTO notes VALUES('"+this->userid+"','"+noteid+"','"+note+"','"+dr+"')"))

            {
                QMessageBox::information(this,"Error","Database Error. Note wasn't Saved");
            }
            else
            {
                ui->label_2->setText("<font color=green>Note Succedfully Saved.</font>");
                ui->plainTextEdit->clear();
            }
    }
}


void Diary::on_pushButton_3_clicked()  ////-----------SHOW SINGLE BUTTON---------------
{
    QDate date = ui->dateEdit->date();
    QString dr = date.toString("dd-MM-yyyy");
    //QMessageBox::information(this,"Date",dr);
    QString note;
    QSqlQuery query;

    query.exec("select count(*) as counter from notes where userid='"+this->userid+"' and dt='"+dr+"'");
    query.next();
    int num=query.value(0).toString().toInt();
    if(num==0){
        ui->label_2->setText("<font color=red>No note for this date has been added yet.</font>");
          ui->plainTextEdit->clear();
    return;}
    query.exec("select * from notes where userid='"+this->userid+"' and dt='"+dr+"'");
    query.next();
    note=query.value(2).toString();
    ui->plainTextEdit->setPlainText(note);
    ui->pushButton_6->show();


}

void Diary::on_pushButton_5_clicked()  ///----------SHOW ALL BUTTON-------------
{
    QSqlQuery query;
    QString note,date;

    QStringList sl;

    ui->listWidget->clear();
    if(query.exec("select count(*) from notes where userid='"+this->userid+"'"))
        query.next();
    if(query.value(0).toString()=="0")
    {ui->label_3->setText("<font color=red>You don't have any notes</font>");
        return ;
    }

    if(query.exec("select * from notes where userid='"+this->userid+"'"))
    {
        ui->label_3->setText("<font color=green>Your all notes are shown below</font>");
    while(query.next()){
                QString itm=query.value(3).toString()+"  "+query.value(2).toString();
        ui->listWidget->addItem(itm);

       }
    }
    else
    {
        ui->label_3->setText("<font color=red>Database Error. Notes can't be shown</font>");
        return ;
    }

}

void Diary::on_pushButton_6_clicked()   ////-----UPDATE BUTTON--------------
{
    QDate date = ui->dateEdit->date();
    QString dr = date.toString("dd-MM-yyyy");
    // QMessageBox::information(this,"Date",dr);
    QString note=ui->plainTextEdit->toPlainText().trimmed();
   // QMessageBox::information(this,"Date",note);
    if(note=="")
    {
        ui->label_2->setText("<font color=red>Empty notes can't be saved.You should delete them.</font>");
        confirm *obj =new confirm(this->userid,dr,this);
        obj->setModal(true);
        obj->show();

        return;
    }
    QSqlQuery query;
    if(query.exec("update notes set note='"+note+"' where userid='"+this->userid+"' and dt='"+dr+"'"))
    {   ui->plainTextEdit->clear();
        ui->label_2->setText("<font color=green>Note Succedfully Updated.</font>");
        ui->pushButton_6->hide();
    }
    else
        ui->label_2->setText("<font color=red>Database Error.Note Not Updated. Please Try Again</font>");

}

void Diary::on_pushButton_4_clicked() //---------------SEARCH BUTTON--------------
{QSqlQuery query;
    ui->listWidget->clear();
    QString search=ui->lineEdit->text().trimmed();
    if(search==""){
        ui->label_3->setText("<font color=red>Enter Some keywords to match with your notes.</font>");
    return ;
    }
       if(query.exec("select count(*) from notes where userid='"+this->userid+"' and note like '%"+search+"%'"))
       {
           query.next();
           if(query.value(0).toString()=="0")
           {ui->label_3->setText("<font color=red>No Matching Notes.</font>");
           return ;}
         }
       else
        {   ui->label_3->setText("<font color=red>Database Error in searching.</font>");return ;}


    if(query.exec("select * from notes where userid='"+this->userid+"' and note like '%"+search+"%'"))
    {   ui->label_3->setText("<font color=green>Your notes containing these keywords are shown below.</font>");
        while(query.next())
        {
            ui->listWidget->addItem(query.value(3).toString()+"  "+query.value(2).toString());
        }
    }
    else
        ui->label_3->setText("<font color=red>Database Error in searching.</font>");
        return;
}

void Diary::on_pushButton_2_clicked() //--------DELETE BUTTON------------
{
    if(ui->listWidget->count()==0 || ui->listWidget->selectedItems().size()==0)
    {
        ui->label_3->setText("<font color=red>No Note has been selected to delete</font>");
        return;
    }
    QString note=ui->listWidget->currentItem()->text();
    QString d=note.midRef(0,10).toString();
    note=note.remove(0,12);

    if(note=="")
    {
          ui->label_3->setText("<font color=red>Select a note from the list shown below</font>");
          return;
    }
    QSqlQuery query;
    int num=ui->listWidget->currentRow();
    if(query.exec("delete from notes where userid='"+this->userid+"' and dt='"+d+"'"))
    {
                  ui->label_3->setText("<font color=green>Note Succesfully Deleted.</font>");
                  ui->listWidget->takeItem(num);

    }
    else
                  ui->label_3->setText("<font color=red>Database Error.Note not deleted.</font>");

}

void Diary::on_pushButton_7_clicked()  //------------SHOW SOME BUTTON
{

    QSqlQuery query;
    QString note,start_date,end_date,q;


    QStringList sl;
    start_date=ui->dateEdit_2->date().toString("dd-MM-yyyy");
    end_date=ui->dateEdit_3->date().toString("dd-MM-yyyy");
    QDate sd,ed;
    sd=sd.fromString(start_date,"dd-MM-yyyy");
    ed=ed.fromString(end_date,"dd-MM-yyyy");
    if(sd > ed)
    {ui->label_3->setText("<font color=red>Start date should be less than end date.</font>");
    return ;}
    ui->listWidget->clear();
    q="select count(*) from notes where userid='"+this->userid+"'"+"and date between '"+start_date+"' and '"+end_date+"'";
    if(query.exec(q))
        query.next();
    if(query.value(0).toString()=="0")
    {ui->label_3->setText("<font color=red>You don't have any notes in this range</font>");
        return ;
    }

    if(query.exec("select * from notes where userid='"+this->userid+"'"+"and dt between '"+start_date+"' and '"+end_date+"'") )
    while(query.next()){
        ui->listWidget->addItem(query.value(3).toString()+"  "+query.value(2).toString());

       }
}

void Diary::on_pushButton_8_clicked()
{

    Login *l= new Login ;
    l->show();

    this->close();

}

void Diary::on_pushButton_9_clicked()
{
    int dd,mm,yy,bnum;
    QString d,m,y,name,bdayid;
    d=ui->comboBox->currentText();
    m=ui->comboBox_2->currentText();
    y=ui->comboBox_3->currentText();
    name=ui->lineEdit_2->text().simplified().toUpper();
    dd=d.toInt();
    mm=m.toInt();
    yy=y.toInt();

    if( (d=="Date") || (m=="Month") || (y=="Year") )
            {ui->label_10->setText("<font color=red>Set the date</font>");
            return ;}
    if( (name=="") )
                {ui->label_10->setText("<font color=red>Enter the name.</font>");
                return ;}
    if(!(QDate::isValid(yy,mm,dd)))
    {
        ui->label_10->setText("<font color=red>Date is not valid</font>");
        return ;
    }

QSqlQuery query;
if(query.exec("select count(*) as counter from birthday where userid='"+userid+"'and  name = '"+name+"'"))
{

query.next();
QString namecount=query.value(0).toString();
if(namecount=="1")
   {
     ui->label_10->setText("<font color=red>This name is already Present.</font>");
     return ;
    }
}

 if(query.exec("select MAX(bdayid) from birthday where userid='"+this->userid+"'")){
 query.next();
bdayid=query.value(0).toString();
bnum=bdayid.toInt();
bnum++;
bdayid=bdayid.setNum(bnum);
            if(!query.exec("insert into birthday values('"+this->userid+"','"+bdayid+"','"+name+"','"+d+"','"+m+"','"+y+"')"))
            {
            QMessageBox::information(this,"Error","Database Error. Trip wasn't Saved");

             }
            else
            {
    ui->label_10->setText("<font color=green>Birthday Succesfully added.</font>");
    this->show_bdaylist(this->userid,ui->listWidget_2);
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox_3->setCurrentIndex(0);
    ui->lineEdit_2->clear();

            }
}
 else
 {
     QMessageBox::information(this,"Error","Database Error. Trip wasn't Saved");
 }

}


void Diary::show_bdaylist(QString userid,QListWidget  *list)
{
    list->clear();
    QSqlQuery query;
    int dd,mm,yy;
    QString name;
    QDate d;
    //where userid='"+this->userid+"' order by month, date
    if(query.exec("select * from birthday "))
    {
       while(query.next())
        {

            dd=query.value(3).toInt();
            mm=query.value(4).toInt();
            yy=this->year;
            d.setDate(yy,mm,dd);
            if(d>=this->current_date)
                break;
        }
        query.previous();

        while(query.next())
        {
            name=query.value(2).toString();
            dd=query.value(3).toInt();
            mm=query.value(4).toInt();
            yy=this->year;
            d.setDate(yy,mm,dd);
            list->addItem(d.toString("dd-MM-yyyy")+"  "+name);
        }

        if(query.exec("select * from birthday"))
            // where userid='"+this->userid+"' order by month,date
        {

            while(query.next())
        {

            name=query.value(2).toString();
            dd=query.value(3).toInt();
            mm=query.value(4).toInt();
            yy=this->year;
            d.setDate(yy,mm,dd);
            if(d>=this->current_date)
               break;
            else
               d= d.addYears(1);

            list->addItem(d.toString("dd-MM-yyyy")+"  "+name);
        }

        }
        else
        {
            ui->label_10->setText("<font color=red>Database error. Upcoming trips list is not full.</font>");
        }

    }
    else
    {
        ui->label_10->setText("<font color=red>Database error. Upcoming trips can't be shown.</font>");
    }
}



void Diary::on_pushButton_10_clicked() //----------DELETE Trip-----------
{
    if(ui->listWidget_2->count()==0 || ui->listWidget_2->selectedItems().size()==0)
    {
       ui->label_10->setText("<font color=red>No Entry has been selected to delete</font>");
        return;
    }
    QString name=ui->listWidget_2->currentItem()->text();
    name=name.remove(0,12);

    if(name=="")
    {
          ui->label_10->setText("<font color=red>Select an entry from the list shown below.</font>");
          return;
    }
    QSqlQuery query;

    if(query.exec("delete from birthday where userid='"+this->userid+"' and name='"+name+"'"))
    {
                  ui->label_10->setText("<font color=green>Entry Succesfully Deleted.</font>");
                  this->show_bdaylist(this->userid,ui->listWidget_2);

    }
    else
                  ui->label_10->setText("<font color=red>Database Error.Note not deleted.</font>");

}



 void Diary::clear_diary(QString userid, QString year)

 {

     QSqlQuery query;

     if ( query.exec("delete from notes where userid='"+userid+"'") &&
     query.exec("update users set year='"+year+"' where userid='"+userid+"'") )
        {
            QMessageBox::information(NULL,"Information","All of your notes has been deleted to reset your diary.");

            return ;
        }

     QMessageBox::information(NULL,"Warning","Daily Diary was trying to clear after new year but because of some technical issues it was not done properly. You may have lost some information.");


 }


void Diary::on_actionCalculator_triggered()
{
    Calculator *calc = new Calculator;
    calc->setModal(false);
    calc->setWindowTitle("Calculator");
    calc->show();
}


void Diary::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    ui->lcdNumber->display(text);
}

void Diary::on_actionTetris_triggered()
{
    TetrixWindow *tet = new TetrixWindow;
    tet->show();
}

void Diary::on_actionContacts_triggered()
{
    contacts *con = new contacts(this->userid,this);
    con->setModal(true);
    con->setWindowTitle("Contacts");
    con->show();

}

void Diary::on_pushButton_11_clicked()
{
    QSqlQuery query;
    query.exec("DROP TABLE notes;");
}

void Diary::on_pushButton_12_clicked()
{
    QSqlQuery query;
    query.exec("DROP TABLE birthday;");
}
