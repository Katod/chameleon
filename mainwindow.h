#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "dbwrapper.h"
#include "addfilmdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    s_searchRequest(QString,QString,QString);
private slots:
    void on_searchButton_clicked();
    void on_resetButton_clicked();
    void fillTableView(QSqlQuery);

    void on_informationButton_clicked();

    void on_addButton_clicked();

private:
    Ui::MainWindow *ui;
    dbWrapper Db;
    QString generateSelectQuery(QString,QString,QString);
};

class NonEditTableColumnDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    NonEditTableColumnDelegate(QObject * parent = 0) : QItemDelegate(parent) {}
    virtual QWidget * createEditor ( QWidget *, const QStyleOptionViewItem &,
                                     const QModelIndex &) const
    {
        return 0;
    }
};



#endif // MAINWINDOW_H
