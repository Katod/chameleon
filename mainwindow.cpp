#include "mainwindow.h"
#include "ui_mainwindow.h"



void MainWindow::fillTableView(QSqlQuery query)
{
    QSqlRecord rec = query.record();
    int number = 0 ,
            year = 0,
            rate = 0;
    QString
            name = "",
            director = "";

     int numberOfRows = 0;
     if(query.last())
     {
         numberOfRows =  query.at() + 1;
         query.first();
         query.previous();
     }

     ui->tableWidget->setRowCount(numberOfRows);

    for (int coloum = 0; query.next(); coloum++)
    {
        number = query.value(rec.indexOf("number")).toInt();
        name = query.value(rec.indexOf("name")).toString();
        director = query.value(rec.indexOf("director")).toString();
        year = query.value(rec.indexOf("year")).toInt();
        rate = query.value(rec.indexOf("rate")).toInt();

        ui->tableWidget->setItem(coloum,0,new QTableWidgetItem(name));
        ui->tableWidget->setItem(coloum,1,new QTableWidgetItem(director));
        ui->tableWidget->setItem(coloum,2,new QTableWidgetItem(QString::number(year)));
        ui->tableWidget->setItem(coloum,3,new QTableWidgetItem(QString::number(rate)));
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->tableWidget->setHorizontalHeaderLabels(QString("Название ;Режиссер ;Год ;Рейтинг").split(";"));
    ui->tableWidget->setItemDelegateForColumn(0, new NonEditTableColumnDelegate());
    ui->tableWidget->setItemDelegateForColumn(1, new NonEditTableColumnDelegate());
    ui->tableWidget->setItemDelegateForColumn(2, new NonEditTableColumnDelegate());

   ui->yearEdit->setValidator( new QIntValidator(0, 9999, this) );
   ui->rateEdit->setValidator( new QIntValidator(0, 100, this) );

   QObject::connect(this,SIGNAL(s_searchRequest(QString,QString,QString)),&Db,SLOT( generateSelectQueryByFilter(QString,QString,QString)));

    dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("my_db.sqlite");
    if (!dbase.open()) {
        qDebug() << "Что-то пошло не так!";
        //return -1;
    }

    QSqlQuery a_query;
    // DDL query
    QString str = "CREATE TABLE my_table ("
            "number integer PRIMARY KEY NOT NULL, "
            "name VARCHAR(255) NOT NULL , "
            "director VARCHAR(255) NOT NULL ,"
            "year integer NOT NULL ,"
            "rate integer"
            ");";
    bool b = a_query.exec(str);
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


    b = a_query.exec(str);

    if (!b) {
        qDebug() << "Кажется данные не вставляются, проверьте дверь, может она закрыта?";
    }
    //.....
    if (!a_query.exec("SELECT * FROM my_table")) {
        qDebug() << "Даже селект не получается, я пас.";
        //return -2;
    }
    QSqlRecord rec = a_query.record();
    int number = 0 ,
            year = 0,
            rate = 0;
    QString
            name = "",
            director = "";


   // while (a_query.next()) {



     int numberOfRows = 0;
     if(a_query.last())
     {
         numberOfRows =  a_query.at() + 1;
         a_query.first();
         a_query.previous();
     }

     ui->tableWidget->setRowCount(numberOfRows);

    for (int coloum = 0; a_query.next(); coloum++)
    {
        number = a_query.value(rec.indexOf("number")).toInt();
        name = a_query.value(rec.indexOf("name")).toString();
        director = a_query.value(rec.indexOf("director")).toString();
        year = a_query.value(rec.indexOf("year")).toInt();
        rate = a_query.value(rec.indexOf("rate")).toInt();

        ui->tableWidget->setItem(coloum,0,new QTableWidgetItem(name));
        ui->tableWidget->setItem(coloum,1,new QTableWidgetItem(director));
        ui->tableWidget->setItem(coloum,2,new QTableWidgetItem(QString::number(year)));
        ui->tableWidget->setItem(coloum,3,new QTableWidgetItem(QString::number(rate)));

        qDebug() << "number is " << number
                 << ". name is " << name
                 << ". director" << director
                 << ". year" << year
                 << ". rate" << rate;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_searchButton_clicked()
{
      // QSqlQuery a_query;
       //if (!a_query.exec(generateSelectQuery(ui->filmEdit->text(),ui->yearEdit->text(),ui->rateEdit->text()))) {
       //     qDebug() << "Даже селект не получается, я пас.";
       //}
    emit s_searchRequest(ui->filmEdit->text(),ui->yearEdit->text(),ui->rateEdit->text());
   // fillTableView(a_query);
}

void MainWindow::on_resetButton_clicked()
{
    ui->filmEdit->clear();
    ui->yearEdit->clear();
    ui->rateEdit->clear();

    QSqlQuery a_query;

    if (!a_query.exec("SELECT * FROM my_table")) {
        //return -2;
    }

    fillTableView(a_query);
}
