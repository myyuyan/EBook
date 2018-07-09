#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(mystyle);
    QFile filel(":/hei.qss");
    if(filel.open(QFile::ReadWrite))
    {
        QString styleSheet = QLatin1String(filel.readAll());
        a.setStyleSheet(styleSheet);
    }
    else
    {
        QMessageBox::warning(NULL, "warning", "Open failed", QMessageBox::Yes | QMessageBox::Yes);
    }
    filel.close();
    MainWindow w;
    w.show();

    return a.exec();
}
