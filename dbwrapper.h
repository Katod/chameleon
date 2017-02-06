#ifndef DBWRAPPER_H
#define DBWRAPPER_H

#include <QObject>
#include <QtSql>

class dbWrapper : public QObject
{
    Q_OBJECT
public:   
    explicit dbWrapper(QObject *parent = 0);
private:
    QSqlDatabase dbase;
    QString selectQueryString;
signals:
    s_selectQueryChange(QSqlQuery);
    s_warning();
    s_newDirector();
    s_successAddNewItem();
public slots:
    void generateSelectQueryByFilter(QString name,QString year,QString rate);
    void addNewItem(QString film,QString director,QString year,QString rate,bool isFinally);
    void updateRating(QString film, QString rate);
};

#endif // DBWRAPPER_H
