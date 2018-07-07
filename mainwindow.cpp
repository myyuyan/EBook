#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSettings *info = new QSettings(":/info.ini", QSettings::IniFormat);
    QString ifo=info->value("/info/adress").toString();
    info->setValue("/info/adress", "192.168.0.1");
    delete info;
    QMessageBox::warning(NULL, ifo, ifo, QMessageBox::Yes | QMessageBox::Yes);
}

MainWindow::~MainWindow()
{
    delete ui;
}
