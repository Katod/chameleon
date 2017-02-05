#include "dbwrapper.h"

dbWrapper::dbWrapper(QObject *parent) : QObject(parent)
{
    dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("my_db.sqlite");
    if (!dbase.open()) {
        qDebug() << "Что-то пошло не так!";
        //return -1;
    }

    QSqlQuery m_query;
    // DDL query
    QString str = "CREATE TABLE my_table ("
            "number integer PRIMARY KEY NOT NULL, "
            "name VARCHAR(255) NOT NULL , "
            "director VARCHAR(255) NOT NULL ,"
            "year integer NOT NULL ,"
            "rate integer"
            ");";
    bool b = m_query.exec(str);
    if (!b) {
        qDebug() << "Вроде не удается создать таблицу, провертье карманы!";
    }

    // DML



    b = m_query.exec(str);

    if (!b) {
        qDebug() << "Кажется данные не вставляются, проверьте дверь, может она закрыта?";
    }
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
              qDebug() << "Даже селект не получается, я пас."<<select;
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
     QString str_insert = "INSERT INTO my_table(number, name, director,year,rate) "
             "VALUES (%1, '%2', '%3', %4, %5);";
     QString str = str_insert.arg(22)
             .arg(film)
             .arg(director)
             .arg(year.toInt())
             .arg(rate.toInt());

     if (!query.exec(str)) {
                qDebug() << "Кажется данные не вставляются, проверьте дверь, может она закрыта?";
            }

}


void dbWrapper::openDb()
{
    //if (!m_query.exec(select)) {
     //     qDebug() << "Даже селект не получается, я пас.";
    // }
    //else
     //   emit s_selectQueryChange(m_query);
}
