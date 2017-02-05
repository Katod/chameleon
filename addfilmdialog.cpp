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

    plblFilmName->setBuddy(m_ptxtFilmName);
    plblDirector->setBuddy(m_ptxtDirector);
    plblYear->setBuddy(m_ptxtYear);
    plblRate->setBuddy(m_ptxtRate);

    pcmdAdd     = new QPushButton("&Добавить");
    pcmdAdd->setEnabled(false);
    pcmdCancel = new QPushButton("&Отмена");

    connect(pcmdAdd, SIGNAL(clicked()), SLOT(accept()));
    connect(pcmdCancel, SIGNAL(clicked()), SLOT(reject()));

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

void addFilmDialog::checkValidData()
{
  if(m_ptxtFilmName->text() != "" && m_ptxtDirector->text() != "" && m_ptxtYear->text() != "")
    pcmdAdd->setEnabled(true);

}
