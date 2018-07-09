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
        QString info = toText.readAll();
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
                QStringList lt;
                lt<<tmp;
                QTreeWidgetItem *items = new QTreeWidgetItem(ui->treeWidget,lt);
            }
            qDebug()<<li;
        }
    }
    else
    {
        QMessageBox::warning(NULL, "warning", "Open null1", QMessageBox::Yes | QMessageBox::Yes);
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
    qDebug()<<index;
}
