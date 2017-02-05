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
    QString str_insert = "INSERT INTO my_table(number, name, director,year,rate) "
            "VALUES (%1, '%2', '%3', %4, %5);";
    str = str_insert.arg("13")
            .arg("Sleeper")
            .arg("Stiven King")
            .arg("2005")
            .arg("5");


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

void dbWrapper::openDb()
{
    //if (!m_query.exec(select)) {
     //     qDebug() << "Даже селект не получается, я пас.";
    // }
    //else
     //   emit s_selectQueryChange(m_query);
}
