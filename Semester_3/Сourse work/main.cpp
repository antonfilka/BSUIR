#include <QApplication>
#include "diary.h"
#include "login.h"
#include "dbcon.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login l;
    dbcon *db = new dbcon ;
    if(db->createConnection())
    {
    l.show();
    }
    return a.exec();
}
