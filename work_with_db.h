#ifndef WORK_WITH_DB_H
#define WORK_WITH_DB_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "mainwindow.h"
#include "ui_mainwindow.h"

class Dbwork{
    //Q_OBJECT
public:
    void insertToDB(Ui::MainWindow *ui, QSqlQuery query, QString eng_str, QString ru_str);
    bool serchInDBandShow(Ui::MainWindow *ui, QSqlQuery query, QString eng_str, QString ru_str);
    bool checkStrForRuTranslation(QString str);
    bool checkStrForEngTranslation(QString str);
    bool checkForCoincidence(QString eng_str, QString dbStr);
    ~Dbwork();
private:
    QString WRubegin = "А"; // begin diapason in russian dictionary (High register)
    QString WRuend = "Я"; // end diapason in russian dictionary (High register)
    QString wRubegin = "а"; // begin diapason in russian dictionary (Low register)
    QString wRuend = "я"; // end diapason in russian dictionary (Low register)

    QString WEnbegin = "A"; // begin diapason in english dictionary (High register)
    QString WEnend = "Z"; // end diapason in english dictionary (High register)
    QString wEnbegin = "a"; // begin diapason in english dictionary (Low register)
    QString wEnend = "z"; // end diapason in english dictionary (Low register)

    QString strCmp;
    QString compareEngStrInDb = nullptr; // variable like cmp for compare word in lineEdit with word in database

    bool isRUtr; // return true if word is russian
    bool isENtr; // return true if word is english
};

#endif // WORK_WITH_DB_H
