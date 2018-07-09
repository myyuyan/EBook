#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bool choose=true;
    while(choose){
    QFile file(":/info.txt");
    if(file.open(QFile::ReadWrite))
    {
        QTextStream toText(&file);
        toText.setCodec("UTF-8");
        QString info = toText.readAll();
        file.close();
        qDebug()<<info;
        QDir dir(info);
        if(dir.exists()){
            choose=false;
            QStringList li;
            li.clear();
            foreach(QFileInfo fullDir, dir.entryInfoList())
            {
                if(fullDir.fileName() == "." || fullDir.fileName() == "..") continue;
                li.push_back(fullDir.fileName());
            }
            for(int i = 0; i< li.size();i++)
            {
                QString tmp = li.at(i);
                qDebug()<<tmp;
                QStringList lt;
                lt<<tmp;
                QTreeWidgetItem *items = new QTreeWidgetItem(ui->treeWidget,lt);
            }
            qDebug()<<li;
        }else{
            QFile out(":/info.txt");
            if(out.open(QFile::WriteOnly))
            {
                bool isok;
                QString text = QInputDialog::getText(NULL,QStringLiteral("错误"),QStringLiteral("请输入数据库正确路径！"),QLineEdit::Normal,QStringLiteral("把路径复制到这里！"),&isok);
                if(!isok){
                    choose=false;
                }
                std::string tex = text.toStdString();
                out.write(tex.c_str(),sizeof(tex.c_str()));
            }else{
                QMessageBox::warning(NULL, "warning", "Open null2", QMessageBox::Yes | QMessageBox::Yes);
                choose=false;
            }
            out.close();
        }
    }
    else
    {
        QMessageBox::warning(NULL, "warning", "Open null1", QMessageBox::Yes | QMessageBox::Yes);
        choose=false;
        file.close();
    }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
