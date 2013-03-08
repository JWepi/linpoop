#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "Packet.hh"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    ~Client();

    void getFriendIp(int);
    void sendMsg(QString, QString);
    
public slots :
    void getIp(QString);
    void read();
    void send(Packet*);
    void addFriend(QString);

private slots :
    void connectionOk();
    void connectionFail(QAbstractSocket::SocketError);

signals :
    void setId(int);
    void displayFriend();
    void msgFrom(std::string, int);

public :
    QTcpSocket  soc;
    QString     nickName;
    QString     ip;
    int         id;
    std::map<int, std::string> friendList;
    std::map<int, std::string> friendIp;
    
};

#endif // CLIENT_H
