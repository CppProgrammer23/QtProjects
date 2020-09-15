#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QtSql/QSqlDatabase>

class DataBaseConnection
{
public:
    DataBaseConnection(QSqlDatabase d,
                       QString name,
                       QString server,
                       QString user,
                       QString driver,
                       QString pass,
                       bool trustedconnection);
    bool OpenDatabase(QString* error);
private:
    QSqlDatabase dbD;
    QString dbName;
    QString dbServer;
    QString dbUser;
    QString dbDriver;
    QString dbPass;
    bool dbTrustedConnection=true;
};

#endif // DATABASECONNECTION_H
