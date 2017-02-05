#include <QtGui>
#include "addfilmdialog.h"


addFilmDialog::addFilmDialog(QWidget* pwgt/*= 0*/)
     : QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
    m_ptxtFilmName = new QLineEdit();
    m_ptxtDirector  = new QLineEdit();
    m_ptxtYear = new QLineEdit();
    m_ptxtRate  = new QLineEdit();


    QLabel* plblFilmName    = new QLabel("&Название");
    QLabel* plblDirector    = new QLabel("&Режиссер");
    QLabel* plblYear        = new QLabel("&Год");
    QLabel* plblRate        = new QLabel("&Рейтинг");

    m_ptxtYear->setValidator( new QIntValidator(0, 9999, this) );
    m_ptxtRate->setValidator( new QIntValidator(0, 100, this) );

    plblFilmName->setBuddy(m_ptxtFilmName);
    plblDirector->setBuddy(m_ptxtDirector);
    plblYear->setBuddy(m_ptxtYear);
    plblRate->setBuddy(m_ptxtRate);

    pcmdAdd     = new QPushButton("&Добавить");
    pcmdAdd->setEnabled(false);
    pcmdCancel = new QPushButton("&Отмена");

    connect(pcmdAdd, SIGNAL(clicked()), this,SLOT(acceptAndCheck()));
    connect(pcmdCancel, SIGNAL(clicked()),this,SLOT(reject()));


    connect(m_ptxtFilmName,SIGNAL(editingFinished()),this,SLOT(checkValidData()));
    connect(m_ptxtDirector,SIGNAL(editingFinished()),this,SLOT(checkValidData()));
    connect(m_ptxtYear,SIGNAL(editingFinished()),this,SLOT(checkValidData()));
    connect(m_ptxtRate,SIGNAL(editingFinished()),this,SLOT(checkValidData()));

    //Layout setup
    QGridLayout* ptopLayout = new QGridLayout;
    ptopLayout->addWidget(plblFilmName, 0, 0);
    ptopLayout->addWidget(plblDirector, 1, 0);
    ptopLayout->addWidget(plblYear, 2, 0);
    ptopLayout->addWidget(plblRate, 3, 0);

    ptopLayout->addWidget(m_ptxtFilmName, 0, 1);
    ptopLayout->addWidget(m_ptxtDirector, 1, 1);
    ptopLayout->addWidget(m_ptxtYear, 2, 1);
    ptopLayout->addWidget(m_ptxtRate, 3, 1);

    ptopLayout->addWidget(pcmdAdd, 4,0);
    ptopLayout->addWidget(pcmdCancel, 4, 1);
    setLayout(ptopLayout);
}

QString addFilmDialog::getFilmName() const
{
    return m_ptxtFilmName->text();
}

QString addFilmDialog::getDirector() const
{
    return m_ptxtDirector->text();
}

QString addFilmDialog::getYear() const
{
    return m_ptxtYear->text();
}

QString addFilmDialog::getRate() const
{
    return m_ptxtRate->text();
}


void addFilmDialog::acceptAndCheck()
{
    qDebug() << "accept";
    emit s_checkInputData(m_ptxtFilmName->text(),
                          m_ptxtDirector->text(),
                          m_ptxtYear->text(),
                          m_ptxtRate->text(),
                          false
                          );
    //addFilmDialog::close();

}


void addFilmDialog::checkValidData()
{
  if(m_ptxtFilmName->text() != "" && m_ptxtDirector->text() != "" && m_ptxtYear->text() != "")
    pcmdAdd->setEnabled(true);
  else
    pcmdAdd->setEnabled(false);

}

void addFilmDialog::warningExistFilm()
{
    QMessageBox::warning(0,"Предупреждение", "Фильм с таким названием уже есть в базе");
}

void addFilmDialog::dialogNewDirector()
{
    msgBox.setText("Режиссер не найден в БД. Добавить его и закончить добавление фильма?");
    msgBox.setWindowFlags(windowFlags()^Qt::WindowCloseButtonHint);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    int ret = msgBox.exec();
    // Собственно вот этот case и отвечает за обработку событий
    switch (ret) {
    case QMessageBox::Cancel:
         qDebug()<<" QMessageBox::Cancel:";
         break;
      case QMessageBox::Ok:
        emit s_checkInputData(m_ptxtFilmName->text(),
                              m_ptxtDirector->text(),
                              m_ptxtYear->text(),
                              m_ptxtRate->text(),
                              true
                              );
         break;
      default:
         // Сюда пишем обработку события по умолчанию
         break;
    }
}



