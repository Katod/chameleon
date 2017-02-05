#ifndef ADDFILMDIALOG_H
#define ADDFILMDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>

class addFilmDialog : public QDialog {
    Q_OBJECT
private:
    QLineEdit* m_ptxtFilmName;
    QLineEdit* m_ptxtDirector;
    QLineEdit* m_ptxtYear;
    QLineEdit* m_ptxtRate;
    QPushButton* pcmdAdd;
    QPushButton* pcmdCancel;
    QMessageBox msgBox;
public:
    addFilmDialog(QWidget* pwgt = 0);
    QString getFilmName() const;
    QString getDirector () const;
    QString getYear() const;
    QString getRate () const;
signals:
    s_checkInputData(QString film,QString director,QString year,QString rate,bool isFinally);
private slots:
  void checkValidData();
  void acceptAndCheck();
  void warningExistFilm();
  void dialogNewDirector();
};


#endif // ADDFILMDIALOG_H
