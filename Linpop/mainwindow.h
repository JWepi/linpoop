#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QStringListModel>
#include "client.h"
#include "chatroom.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString getSection(QString, int);
    void addFriend(int, std::string, std::string);
    void newChatRoom(QString);

public slots:
    void setId(int);
    void displayFriend();
    void closeChatRoom(QString);
    void sending(QString, QString);

private slots:
    void on_connectionButton_clicked();
    void on_avatarButton_clicked();
    void on_listView_doubleClicked(const QModelIndex &index);
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Client *client;
    QString avatarPath;
    QStringList *ipList;
    QStringListModel *model;
    QMap<QString, ChatRoom*> map;
};

#endif // MAINWINDOW_H
