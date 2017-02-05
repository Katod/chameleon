#include "mainwindow.h"
#include "ui_mainwindow.h"



void MainWindow::fillTableView(QSqlQuery query)
{
    qDebug() << "fillTableView";
    QSqlRecord rec = query.record();
    int number = 0 ,
            year = 0;

    QVariant rate ;

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

        ui->tableWidget->setItem(coloum,0,new QTableWidgetItem(name));
        ui->tableWidget->setItem(coloum,1,new QTableWidgetItem(director));
        ui->tableWidget->setItem(coloum,2,new QTableWidgetItem(QString::number(year)));

        rate = query.value(rec.indexOf("rate"));
        if ( rate == NULL)
            ui->tableWidget->setItem(coloum,3,new QTableWidgetItem("No rate"));
        else
        {
            ui->tableWidget->setItem(coloum,3,new QTableWidgetItem(QString::number(rate.toInt())));
        }

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
   QObject::connect(&Db,SIGNAL(s_selectQueryChange(QSqlQuery)),this,SLOT( fillTableView(QSqlQuery)));

   emit s_searchRequest(ui->filmEdit->text(),ui->yearEdit->text(),ui->rateEdit->text());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_searchButton_clicked()
{
    emit s_searchRequest(ui->filmEdit->text(),ui->yearEdit->text(),ui->rateEdit->text());
}

void MainWindow::on_resetButton_clicked()
{
    ui->filmEdit->clear();
    ui->yearEdit->clear();
    ui->rateEdit->clear();

    emit s_searchRequest(ui->filmEdit->text(),ui->yearEdit->text(),ui->rateEdit->text());
}

void MainWindow::on_informationButton_clicked()
{
 qDebug() << "on_informationButton_clicked";
 int row = ui->tableWidget->currentRow();
 if(row == -1)
 {
    QMessageBox::information(0, "Информация", "Не выбран элемент");
 }
 else
 {
     QMessageBox::information(0, "Информация", "Название: "+ui->tableWidget->item(row,0)->text()+
                              "\nРежиссер: "+ui->tableWidget->item(row,1)->text()+
                              "\nГод: "+ui->tableWidget->item(row,2)->text()+
                              "\nРейтинг: "+ui->tableWidget->item(row,3)->text());
 }
}

void MainWindow::on_addButton_clicked()
{
    qDebug() << "on_addButton_clicked";
    addFilmDialog* pFilmDialog = new addFilmDialog;

    QObject::connect(pFilmDialog,SIGNAL(s_checkInputData(QString,QString,QString,QString,bool)),&Db,SLOT(addNewItem(QString ,QString ,QString ,QString,bool)));
    QObject::connect(&Db,SIGNAL(s_warning()),pFilmDialog,SLOT(warningExistFilm()));
    QObject::connect(&Db,SIGNAL(s_newDirector()),pFilmDialog,SLOT(dialogNewDirector()));
    pFilmDialog->exec();



    if (pFilmDialog->exec() == QDialog::Accepted) {
               QMessageBox::information(0,
                                        "Information",
                                        "First Name: "+pFilmDialog->getFilmName()
                                       );
           }
           delete pFilmDialog;
}
