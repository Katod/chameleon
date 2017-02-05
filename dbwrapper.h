#ifndef DBWRAPPER_H
#define DBWRAPPER_H

#include <QObject>
#include <QtSql>

class dbWrapper : public QObject
{
    Q_OBJECT
public:   
    explicit dbWrapper(QObject *parent = 0);
    void openDb();
   // bool checkInputData(QString film,QString director,int year,int rate);
private:
    QSqlDatabase dbase;
    QString selectQueryString;
signals:
    s_selectQueryChange(QSqlQuery);
public slots:
    void generateSelectQueryByFilter(QString,QString,QString);
   // void addNewItem(QString film,QString director,int year,int rate);
};

#endif // DBWRAPPER_H
