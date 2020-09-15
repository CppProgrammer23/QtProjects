#include "databaseconnection.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

DataBaseConnection::DataBaseConnection(QSqlDatabase d,
                                       QString name,
                                       QString server,
                                       QString user,
                                       QString driver,
                                       QString pass,
                                       bool trustedconnection)
{
    dbD=d;
    dbName=name;
    dbServer=server;
    dbUser=user;
    dbDriver=driver;
    dbPass=pass;
    dbTrustedConnection=trustedconnection;
}
bool DataBaseConnection::OpenDatabase(QString* error)
{
   // dbD.setDatabaseName();
    return true;
}
