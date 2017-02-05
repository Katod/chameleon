#ifndef ADDFILMDIALOG_H
#define ADDFILMDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

class addFilmDialog : public QDialog {
    Q_OBJECT
private:
    QLineEdit* m_ptxtFilmName;
    QLineEdit* m_ptxtDirector;
    QLineEdit* m_ptxtYear;
    QLineEdit* m_ptxtRate;
    QPushButton* pcmdAdd;
    QPushButton* pcmdCancel;

public:
    addFilmDialog(QWidget* pwgt = 0);

    QString getFilmName() const;
    QString getDirector () const;
    QString getYear() const;
    QString getRate () const;
private slots:
  void checkValidData();
};


#endif // ADDFILMDIALOG_H
