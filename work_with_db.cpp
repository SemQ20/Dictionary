#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "work_with_db.h"

/*Insert words in dictionary*/
void Dbwork::insertToDB(Ui::MainWindow *ui,QSqlQuery query, QString eng_str, QString ru_str)
{
    if(ru_str == NULL && eng_str == NULL){}
    else if(ru_str == NULL || eng_str == NULL){}
    else{
        isENtr = checkStrForEngTranslation(eng_str);
        isRUtr = checkStrForRuTranslation(ru_str);
        if(!isENtr && !isRUtr){
            strCmp = eng_str;
            eng_str = ru_str;
            ru_str = strCmp;
            ui->lineEdit->setText(eng_str);
            ui->lineEdit_2->setText(ru_str);
        }
        query.exec("SELECT * FROM dict");
        while(query.next()){
            if((eng_str == query.value(1).toString()) && ru_str == query.value(2).toString()){
                ui->statusbar->showMessage(eng_str+" already insert to dictionary");
                return;
            }
        }
        query.exec("INSERT INTO dict (engtr,rutr) VALUES ('"+eng_str+"' , '"+ru_str+"');");
    }
}

bool Dbwork::checkForCoincidence(QString eng_str, QString dbStr){
    int i = 0;
    while(i != eng_str.size()){
        if(eng_str[i] == dbStr[i]){
            i++;
        }else{
            return false;
        }
    }
    return true;
}
/*Search one word in database and print another*/
bool Dbwork::serchInDBandShow(Ui::MainWindow *ui, QSqlQuery query, QString eng_str, QString ru_str)
{
    query.exec("SELECT * FROM dict");
    bool found = false;

    isENtr = checkStrForEngTranslation(eng_str);
    isRUtr = checkStrForRuTranslation(ru_str);

    if(!isENtr && eng_str != NULL){
            strCmp = ru_str;
            ru_str = eng_str;
            eng_str = strCmp;
     }else if (!isRUtr && ru_str !=NULL){
            strCmp = eng_str;
            eng_str = ru_str;
            ru_str = strCmp;
      }

    if(ru_str == NULL && eng_str != NULL){
    while(query.next()){
        compareEngStrInDb = nullptr; // clear previous value
        compareEngStrInDb = query.value(1).toString();
        if(eng_str == query.value(1).toString() || checkForCoincidence(eng_str, compareEngStrInDb)){ // Find eng translation in db on russian word or compare substring
            ui->listWidget->addItem(query.value(2).toString());
            found = true;
        }
       }
    }else if(ru_str != NULL && eng_str == NULL){ // Find ru translation in db on english word
        while(query.next()){
            if(ru_str == query.value(2).toString()){
                ui->listWidget->addItem(query.value(1).toString());
                found = true;
            }
        }
    }
    return found;
}


/* Checking function on russian translation one word */
bool Dbwork::checkStrForRuTranslation(QString str)
{
    if(str == NULL){return false;}
    for(int i = 0; i < str.size(); i++){
        if((str[i] >= WRubegin && str[i] <= WRuend) || ((str[i] >= wRubegin && str[i] <= wRuend))){
            return true;
        }
    }
    return false;
}


/* Checking function on english translation one word */
bool Dbwork::checkStrForEngTranslation(QString str)
{
    if(str==NULL){return false;}
    for(int i = 0; i < str.size(); i++){
        if((str[i] >= WEnbegin && str[i] <= WEnend) || (str[i] >= wEnbegin && str[i] <= wEnend)){
            return true;
        }
    }
    return false;
}

Dbwork::~Dbwork()
{
    // maybe for clear allocated memory
}
