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
        QDir dir(info);
        QString title=info.right(info.length()-info.lastIndexOf("\\")-1);
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
            QStringList li,la;
            li.clear();
            la.clear();
            foreach(QFileInfo fullDir, dir.entryInfoList())
            {
                if(fullDir.fileName() == "." || fullDir.fileName() == "..") continue;
                li.push_back(fullDir.fileName());
                la.push_back(fullDir.filePath());
            }
            for(int i = 0; i< li.size();i++)
            {
                QString tmp = li.at(i);
                QTreeWidgetItem *items = new QTreeWidgetItem();
                items->setText(0,tmp);
                init(la.at(i),li.at(i),items);
                rootList.append(items);
            }
            ui->treeWidget->insertTopLevelItems(0,rootList);
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
    QString zifu=index.data().toString();
    QString in=info+"\\"+index.data().toString();
    if((zifu.contains(".",Qt::CaseSensitive))){
        QString zi=zifu.right(zifu.length()-zifu.lastIndexOf(".")-1);
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

    }
}
void MainWindow::init(QString la,QString li,QTreeWidgetItem *items){
    if((li.contains(".",Qt::CaseSensitive))){
    }else{
        QDir dir(la);
        if(dir.exists()){
            QStringList name,path;
            name.clear();
            path.clear();
            foreach(QFileInfo fullDir, dir.entryInfoList())
            {
                if(fullDir.fileName() == "." || fullDir.fileName() == "..") continue;
                name.push_back(fullDir.fileName());
                path.push_back(fullDir.filePath());
                QTreeWidgetItem *item = new QTreeWidgetItem();
                item->setText(0,fullDir.fileName());
                init(fullDir.filePath(),fullDir.fileName(),item);
                items->addChild(item);
            }
        }else{
            QMessageBox::warning(NULL, "warning", "Open null", QMessageBox::Yes | QMessageBox::Yes);
        }
    }
}
