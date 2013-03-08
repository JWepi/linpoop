#include <iostream>
#include "client.h"
#include "dataBuilder.hh"
#include "user.hh"

Client::Client(QObject *parent) : QObject(parent)
{
    id     = 0;
    QObject::connect(&soc, SIGNAL(connected()), this, SLOT(connectionOk()));
    QObject::connect(&soc, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(connectionFail(QAbstractSocket::SocketError)));
    QObject::connect(&soc, SIGNAL(readyRead()), this, SLOT(read()));
}

Client::~Client()
{
    std::cout << "closing socket..." << std::endl;
    soc.close();
}



void Client::getFriendIp(int friendId)
{
    Packet p(25, id, friendId, "");
    send(&p);
}

void Client::sendMsg(QString msg, QString to)
{
    Databuilder d;
    std::string s;

    std::cout << "envoi : " << msg.toStdString() << std::endl;

    d.setItem("msg", msg.toStdString());
    s = d.build();

    Packet p(9, id, to.toInt(), s.c_str());
    send(&p);
}



void Client::getIp(QString IP2)
{
    Databuilder d;
    std::string s;

    ip      = IP2;
    std::cout << "connecting to : " << qPrintable(ip) << std::endl;
    soc.connectToHost(ip, 8008);

    d.setItem("nick", nickName.toStdString());
    s = d.build();

    Packet p(2, id, 1, s.c_str());
    send(&p);
}

void Client::addFriend(QString friendId)
{
    Databuilder d;
    std::string s;

    d.setItem("target", friendId.toInt());
    s = d.build();

    Packet p(6, id, friendId.toInt(), s.c_str());
    send(&p);
}

void Client::read()
{
    std::string s;
    void *buff;
    int tmp;

    buff = malloc(1000);
    soc.read((char*)buff, 1000);
    Packet *p = new Packet(buff);
    Databuilder d(p->getData());
    User u(p->getData());

    std::cout << "recved \tpacket #" << (int)p->getType() << std::endl;

    switch (p->getType())
    {
        case 3:
            id = d.getIntItem("id");
            emit setId(id);
            d.setItem("nick", nickName.toStdString());
            s = d.build();
            delete p;
            p = new Packet(4, id, 1, s.c_str());
            send(p);
        break;

        case 8:
            d.setItem("answer", 1);
            s = d.build();
            tmp = p->getOrigin();
            delete p;
            p = new Packet(7, id, tmp, s.c_str());
            send(p);
        break;

        case 10:
            tmp = p->getOrigin();
            s = (char*)p->getData();
            emit msgFrom(s.substr(4, (s.size() - 4)), tmp);
        break;

        case 14:
            friendList = u.getFriends();
            emit displayFriend();
        break;

        case 20:
            delete p;
            p = new Packet(13, id, 1, "");
            send(p);
        break;

        case 26:
            tmp = d.getIntItem("id");
            s = d.getStrItem("ip");
            friendIp.insert(std::pair<int, std::string>(tmp, s));
        break;

        default:
            std::cout << "-" << endl;
    }
}

void Client::send(Packet *p)
{
    std::cout << "sending\tpacket #" << (int)p->getType() << std::endl;
    soc.write((char *)p->getPacket(), p->getPacketSize());
}



void Client::connectionOk()
{
    std::cout << "connected" << std::endl;
}

void Client::connectionFail(QAbstractSocket::SocketError)
{
    std::cerr << "server not found" << std::endl;
}

