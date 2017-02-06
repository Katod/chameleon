#include "dbwrapper.h"


dbWrapper::dbWrapper(QObject *parent) : QObject(parent)
{
    dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("my_db.sqlite");

    dbase.open();

    QSqlQuery query;

    QString str = "CREATE TABLE my_table ("
            "name VARCHAR(255)  PRIMARY KEY NOT NULL , "
            "director VARCHAR(255) NOT NULL ,"
            "year integer NOT NULL ,"
            "rate integer"
            ");";

    query.exec(str);
}


void dbWrapper::generateSelectQueryByFilter(QString name, QString year, QString rate)
{
    QString select = "";
    bool isFirstArg = true;
    select = "SELECT * FROM my_table";
    if(name != "")
    {
            if(isFirstArg == true)
            {
                select += " WHERE ";
                isFirstArg = false;
            }
        select += "name = '" + name+"'";
     }
    if(year != "")
    {
            if(isFirstArg == true)
            {
                select += " WHERE ";
                isFirstArg = false;
            }
            else
                select +=" AND ";

        select+= "year = "+year;
    }
    if(rate != "")
    {
        if(isFirstArg == true)
            {
               select += " WHERE ";
               isFirstArg = false;
            }
            else
               select +=" AND ";

       select+= "rate = "+rate;
    }

    QSqlQuery m_query;

    if (!m_query.exec(select)) {
              qDebug() << "Cant select Data"<<select;
         }

    s_selectQueryChange(m_query);

}

void dbWrapper::addNewItem(QString film,QString director,QString year,QString rate,bool isFinally)
{
    QSqlQuery query;
    qDebug()<<" check Name";

    if (!query.exec("SELECT * FROM my_table WHERE name = '"+film+"'")) {
              qDebug() << "cant select film";
         }

     if(query.first())
     {
         qDebug()<<"WArning already exist";
         emit s_warning();
         return;
     }


    qDebug()<<" check director";

    if (!query.exec("SELECT * FROM my_table WHERE director = '"+director+"'")) {
              qDebug() << "cant select director";
         }

     if(!query.first() && isFinally == false)
     {
         qDebug()<<"NEW director in db";
         emit s_newDirector();
         return;
     }

     // DML
     QString str_insert = "INSERT INTO my_table(name, director,year,rate) "
             "VALUES ('%1', '%2', %3, %4);";
     QString str = "";
     if (rate == "")
         str = str_insert.arg(film)
                .arg(director)
                .arg(year.toInt())
                .arg("NULL");
     else
     {
      str = str_insert.arg(film)
             .arg(director)
             .arg(year.toInt())
             .arg(rate.toInt());
      }
     if (!query.exec(str)) {
                qDebug() << "Can`t input data";
            }
     else
         emit s_successAddNewItem();

}

void dbWrapper::updateRating(QString film, QString rate)
{
    QSqlQuery query;
    QString exec = " UPDATE my_table SET rate ="+rate+" WHERE name ='"+film+"'";

    if (! query.exec(exec)) {
             qDebug() << "Can`t update data";
         }
    else
        emit s_successAddNewItem();
}

