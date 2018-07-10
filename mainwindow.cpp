#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
    ui->textEdit->setText(QStringLiteral("欢迎使用EBook!"));
    bool choose=true;
    while(choose){
    ui->treeWidget->clear();
    QFile file("info.txt");
    if(file.open(QFile::ReadOnly))
    {
        QTextStream toText(&file);
        toText.setCodec("UTF-8");
        info = toText.readAll();
        file.close();
        qDebug()<<info;
        QDir dir(info);
        QString title=info.right(info.length()-info.lastIndexOf("\\")-1);
        qDebug()<<title;
        if(!(dir.exists())||((title.compare(QString::fromLocal8Bit("古文书籍-文件版"))))){
            QFile out("info.txt");
            if(!out.open(QFile::WriteOnly|QFile::Truncate)){
                out.close();
                continue;
            }
            QTextStream to(&out);
            to.setCodec("UTF-8");
            bool isok;
            QString text = QInputDialog::getText(NULL, QStringLiteral("错误"),
                                                                QStringLiteral("把数据库正确路径粘贴至此"),
                                                                QLineEdit::Normal,
                                                                QStringLiteral(""),
                                                                &isok);
            if(!isok){
                choose=false;
                continue;
            }
            to<<text;
            out.close();
        }else{
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
                QTreeWidgetItem *items = new QTreeWidgetItem();
                items->setText(0,tmp);
                rootList.append(items);
            }
            ui->treeWidget->insertTopLevelItems(0,rootList);
            qDebug()<<li;
        }
    }
    else
    {
        QMessageBox::warning(NULL, "warning", "Open null", QMessageBox::Yes | QMessageBox::Yes);
        choose=false;
    }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeWidget_clicked(const QModelIndex &index)
{
    qDebug()<<index.row()<<index.column();
    QString zifu=index.data().toString();
    QString in=info+"\\"+index.data().toString();
    qDebug()<<zifu;
    if((zifu.contains(".",Qt::CaseSensitive))){
        QString zi=zifu.right(zifu.length()-zifu.lastIndexOf(".")-1);
        qDebug()<<zi;
        if(!zi.compare(QString::fromLocal8Bit("txt"))){
            QFile fu(in);
            if(fu.open(QFile::ReadOnly)){
                QTextStream toT(&fu);
                toT.setCodec("ANSI");
                QString text = toT.readAll();
                ui->textEdit->setText(text);
            }else{
                QMessageBox::warning(NULL, "warning", "Open warning", QMessageBox::Yes | QMessageBox::Yes);
            }
            fu.close();
        }else{
            QMessageBox::warning(NULL, "warning", QStringLiteral("文件格式不支持！"), QMessageBox::Yes | QMessageBox::Yes);
        }
    }else{
        QDir dirs(in);
        if(dirs.exists()){
            QStringList lis;
            lis.clear();
            foreach(QFileInfo fullDir, dirs.entryInfoList())
            {
                if(fullDir.fileName() == "." || fullDir.fileName() == "..") continue;
                lis.push_back(fullDir.fileName());
            }
            for(int i = 0; i< lis.size();i++)
            {
                QString tmp = lis.at(i);
                qDebug()<<tmp;
                QStringList lt;
                lt<<tmp;
                QTreeWidgetItem *item=rootList.at(index.row());
                item->removeChild(item);
                QTreeWidgetItem *items = new QTreeWidgetItem(item,lt);
            }
        }
    }
}
