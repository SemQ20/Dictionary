#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "work_with_db.h"
#include <QLineEdit>

Dbwork dbw; // Class for work with SQLite database

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db= QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dictionary.db"); //connect db
    if(db.open()){
        query = QSqlQuery(db);
        ui->statusbar->showMessage("Driver load, db open");
    }else{
        ui->statusbar->showMessage("Driver not load, db not open");
    }
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(refreshNumberWords()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshNumberWords()
{
    query.exec("SELECT max(id) id FROM dict");
    query.first();
    resID = query.value(0).toString();
    curMessage = "Word not found in dictionary";
    if(!ifFound){
        ui->statusbar->showMessage(curMessage +". Dictionary containing "+resID+" words");
    }else{
        ui->statusbar->showMessage("Dictionary containing "+resID+" words");
    }
}


void MainWindow::on_pushButton_clicked()
{
    QString engtr;
    QString rutr;

    engtr=ui->lineEdit->text();
    rutr=ui->lineEdit_2->text();
    dbw.insertToDB(ui,query,engtr,rutr);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString engtr = ui->lineEdit->text();
    QString rutr = ui->lineEdit_2->text();
    ui->listWidget->clear();
    ifFound = dbw.serchInDBandShow(ui ,query , engtr, rutr);
    if(!ifFound){
        ui->statusbar->showMessage("Word not found in dictionary");
    }
}
