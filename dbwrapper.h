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
    QString selectQueryString;
   // QSqlQuery m_query;
signals:
    s_selectQueryChange(QSqlQuery);
public slots:
    void generateSelectQueryByFilter(QString,QString,QString);
};

#endif // DBWRAPPER_H
