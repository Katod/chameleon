#include "dbwrapper.h"

dbWrapper::dbWrapper(QObject *parent) : QObject(parent)
{


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

    //if (!m_query.exec(select)) {
     //     qDebug() << "Даже селект не получается, я пас.";
    // }
    //else
     //   emit s_selectQueryChange(m_query);
}
