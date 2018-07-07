#include "mainwindow.h"
#include <QApplication>
#include<QFile>
#include<QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(mystyle);
    QFile file(":/hei.qss");
    if(file.open(QFile::ReadOnly))
    {
        QString styleSheet = QLatin1String(file.readAll());
        a.setStyleSheet(styleSheet);
    }
    else
    {
        QMessageBox::warning(NULL, "warning", "Open failed", QMessageBox::Yes | QMessageBox::Yes);
    }
    file.close();
    MainWindow w;
    w.show();

    return a.exec();
}
