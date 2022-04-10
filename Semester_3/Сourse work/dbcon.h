#ifndef DBCON_H
#define DBCON_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QtSql>
#include <QMessageBox>
class dbcon
{
public:
    dbcon();
    bool createConnection();
};

#endif // DBCON_H
