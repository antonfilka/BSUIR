#include "dbcon.h"

dbcon::dbcon()
{
}
bool dbcon::createConnection()
{

     QSqlDatabase db1 = QSqlDatabase::addDatabase("QSQLITE");

          db1.setHostName("localhost");
          db1.setDatabaseName("users");
          db1.setPort(5433);
          db1.setUserName("postgres");
          db1.setPassword("postgres");
          QSqlQuery query;

    if (!db1.open())
    {
        QMessageBox::critical(0,"Database Connection Failed","Unable to establish a database connection.\nClick Cancel to exit.", QMessageBox::Cancel);
      return false;
    }
    else
    {
        query.exec("CREATE TABLE users(uid INT, username TEXT, pass1 TEXT, name TEXT, dob TEXT, cur_year TEXT);");

        query.exec("CREATE TABLE notes(userid INT, noteid INT, note TEXT, dt BLOB);");

        query.exec("CREATE TABLE contacts(cid INT, userid INT, name TEXT, phone TEXT, email TEXT);");

        query.exec("CREATE TABLE birthday(userid INT, bdayid INT, name TEXT, d INT, m INT, y INT);");



        //QMessageBox::critical(0,"Database","Connected.", QMessageBox::Cancel);
      return true;
    }
}



