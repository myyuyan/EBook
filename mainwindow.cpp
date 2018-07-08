#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile file(":/info.txt");
    if(file.open(QFile::ReadOnly))
    {
        QTextStream toText(&file);
        toText.setCodec("UTF-8");
        QString info = toText.readAll();
        qDebug()<<info;
        QDir dir(info);
        if(dir.exists()){
            QStringList nameFilters;
            QStringList list = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
            QString li=list.join(",");
            qDebug()<<"li";
        }else{
            qDebug()<<"liaaa";
        }
    }
    else
    {
        QMessageBox::warning(NULL, "warning", "Open null", QMessageBox::Yes | QMessageBox::Yes);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
