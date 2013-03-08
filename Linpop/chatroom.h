#ifndef CHATROOM_H
#define CHATROOM_H

#include <QWidget>

namespace Ui {
class ChatRoom;
}

class ChatRoom : public QWidget
{
    Q_OBJECT
    
public:
    explicit ChatRoom(QWidget *parent = 0);
    ~ChatRoom();

    void setIds(QString, QString, QString);
    void setMyIds(QString, QString, QString);

signals:
    void closeChatRoom(QString);
    void sending(QString, QString);
    
public slots:
    void msgRecv(std::string, int);

private slots:
    void on_closeButton_clicked();
    void on_sendButton_clicked();

public:
    Ui::ChatRoom *ui;
    QString nickName, id, ip;
    QString myNickName, myId, myIp;

};

#endif // CHATROOM_H
