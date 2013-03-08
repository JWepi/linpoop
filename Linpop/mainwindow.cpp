#include <QFileDialog>
#include <sstream>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    client = new Client;
    connect(client, SIGNAL(setId(int)), this, SLOT(setId(int)));
    connect(client, SIGNAL(displayFriend()), this, SLOT(displayFriend()));

    ipList = new QStringList();
    model = new QStringListModel(*ipList, NULL);
    ui->listView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete client;
    delete ui;
}



QString MainWindow::getSection(QString line, int index)
{
   return line.section('\t', index);
}

void MainWindow::addFriend(int id, std::string nickname, std::string ip)
{
    std::ostringstream oss;
    oss << id;
    std::string tmp = oss.str();

    nickname.append("\t");
    nickname.append(tmp);
    nickname.append("\t");
    nickname.append(ip);

    QString str = QString::fromUtf8(nickname.c_str());

    ipList->append(str);
    model->setStringList(*ipList);
}

void MainWindow::newChatRoom(QString line)
{
    QString id = getSection(line, 1);

    if (!map.contains(id))
    {
        std::cout << "opening chatroom #" << qPrintable(id) << std::endl;
        map.insert(id, new ChatRoom());
        map[id]->setIds(getSection(line, 0), id, getSection(line, 2));
        map[id]->setMyIds(client->nickName, QString::number(client->id), client->ip);
        connect(map[id], SIGNAL(closeChatRoom(QString)), this, SLOT(closeChatRoom(QString)));
        connect(map[id], SIGNAL(sending(QString, QString)), this, SLOT(sending(QString, QString)));
        connect(client, SIGNAL(msgFrom(std::string, int)), map[id], SLOT(msgRecv(std::string, int)));
        map[id]->show();
    }
    else
        std::cerr << "window already opened" << std::endl;
}



void MainWindow::setId(int id)
{
    ui->idLabel->setText(QString::number(id));
}

void MainWindow::displayFriend()
{
    ipList->clear();
    for (std::map<int, std::string>::iterator it = client->friendList.begin(); it != client->friendList.end(); ++it)
        client->getFriendIp(it->first);
    for (std::map<int, std::string>::iterator it = client->friendList.begin(); it != client->friendList.end(); ++it)
        addFriend(it->first, it->second, client->friendIp[it->first]);
}

void MainWindow::closeChatRoom(QString ip)
{
    map.remove(ip);
}


void MainWindow::sending(QString text, QString id)
{
    client->sendMsg(text, id);
}

void MainWindow::on_connectionButton_clicked()
{
    if (!ui->ipLineEdit->text().isEmpty())
    {
        if (!ui->nickNameLineEdit->text().isEmpty())
        {
            client->nickName = ui->nickNameLineEdit->text();
            client->ip = ui->ipLineEdit->text();
            client->getIp(ui->ipLineEdit->text());
        }
        else
            ui->nickNameLineEdit->setText("Anonymous");
    }
    else
        std::cerr << "you must choose a server" << std::endl;
}

void MainWindow::on_avatarButton_clicked()
{

    avatarPath = QFileDialog::getOpenFileName(
        this,
        tr("Choose your avatar"),
        "",
        tr("Image Files (*.png *.jpg *.bmp)")
    );

    ui->avatarButton->setIcon(QIcon(avatarPath));
    ui->avatarButton->setIconSize(QSize(95, 95));
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    QVariant value = model->data(index, 0);

    if (value.isValid())
        newChatRoom(value.toString());
    else
        std::cerr << "value invalid" << std::endl;
}

void MainWindow::on_pushButton_clicked()
{
    client->addFriend(ui->idLineEdit->text());
    ui->idLineEdit->setText("");
}
