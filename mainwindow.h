#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include<QFile>
#include<QDir>
#include<qdebug.h>
#include <QTreeWidgetItem>
#include <QInputDialog>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_treeWidget_clicked(const QModelIndex &index);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
    QString info;
    QList<QTreeWidgetItem *> rootList;
    void init(QString la,QString li,QTreeWidgetItem *items);
};

#endif // MAINWINDOW_H
