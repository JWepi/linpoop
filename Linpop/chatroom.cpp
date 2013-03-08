#include <iostream>
#include "chatroom.h"
#include "ui_chatroom.h"

ChatRoom::ChatRoom(QWidget *parent) : QWidget(parent), ui(new Ui::ChatRoom)
{
    ui->setupUi(this);
}

ChatRoom::~ChatRoom()
{
    emit closeChatRoom(ip);
    delete ui;
}


void ChatRoom::setIds(QString _nickName, QString _id, QString _ip)
{
    ui->nickNameLabel->setText(nickName = _nickName);
    ui->idLabel->setText(id = _id);
    ui->ipLabel->setText(ip = _ip);
}

void ChatRoom::setMyIds(QString _myNickName, QString _myId, QString _myIp)
{
    ui->myNickNameLabel->setText(myNickName = _myNickName);
    ui->myIdLabel->setText(myId = _myId);
    ui->myIpLabel->setText(myIp = _myIp);
}


void ChatRoom::msgRecv(std::string msg, int _id)
{
    if (_id == id.toInt())
    {
        ui->chatTextEdit->append("Recv : ");
        ui->chatTextEdit->append(QString::fromUtf8(msg.c_str()));
    }
}


void ChatRoom::on_sendButton_clicked()
{
    emit sending(ui->writeTextEdit->toPlainText(), id);
    ui->chatTextEdit->append("You : ");
    ui->chatTextEdit->append(ui->writeTextEdit->toPlainText());
    ui->writeTextEdit->setText("");
}

void ChatRoom::on_closeButton_clicked()
{
    delete this;
}
