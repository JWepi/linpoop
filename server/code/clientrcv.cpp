
#include "head.hh"

void Clientrcv::hasLeft(int userid)
{
  Databuilder * db = new Databuilder();
  db->setItem("status", "offline");
  this->actions->UsrStatusMod(userid, db->build().c_str());
}

void * Clientrcv::golisten(void * val)
{
  char buff[Datas::BUFF];
  ssize_t bytesreceived = 0;
  int userid = 0;

  while (1)
  {
    memset(buff, 0, Datas::BUFF);

    bytesreceived = recv(this->acceptfd, buff, Datas::BUFF, 0);

    if (bytesreceived == -1)
      utils->err("Clientrcv::golisten", "recv function failed");
    
    if (bytesreceived == 0)
    {
      std::cout << "Client disconnected with ip " << this->ip << std::endl;
      this->hasLeft(userid);
      this->actions->getCore()->rmvuser(userid);
      
      return(NULL);
    }

    std::cout << "I received : " << buff << std::endl << std::endl;

    Packet * recvpacket = new Packet((void *)buff);
    
    Packet * sendpacket = this->actions->Guidance(recvpacket);

    if (sendpacket->getType() == 5 && sendpacket->getTarget() != 0)
    {
      userid = sendpacket->getTarget();
      User * u = Usersmanager::findUser(userid);
      u->setItem("ip", this->ip);
      Usersmanager::setUserInfo(userid, u);
      sendpacket = new Packet(sendpacket->getType(), sendpacket->getOrigin(),
      sendpacket->getTarget(), u->build().c_str());
      this->actions->getCore()->adduser(sendpacket->getTarget(), this->acceptfd);
    }

    if (Datas::DEBUG)
    {
      std::cout << "Created packet : " << std::endl;

      std::cout << "   - Request type : " << sendpacket->getType() << std::endl;
      std::cout << "   - Request src  : " << sendpacket->getOrigin() << std::endl;
      std::cout << "   - Request dst  : " << sendpacket->getTarget() << std::endl;
      std::cout << "   - Request data : " << sendpacket->getData() << std::endl << std::endl;

      std::cout << " --- Verification --- " << std::endl << std::endl;

      Packet * verifpacket = new Packet(sendpacket->buildPacket());

      verifpacket = this->actions->Guidance(verifpacket);

      std::cout << " --- Verification --- " << std::endl << std::endl;
    }

    this->serv->sendpacket(this->acceptfd, (char *)sendpacket->buildPacket(),
    sendpacket->getPacketSize());
  }

  this->actions->getCore()->rmvuser(userid);
  this->hasLeft(userid);

  return(NULL);
}

Clientrcv::Clientrcv(int afd, Actions * a, LPServer * s, std::string myip) : Listener()
{
  this->acceptfd = afd;
  this->actions = a;
  this->serv = s;
  this->ip = myip;
}

Clientrcv::Clientrcv() : Listener()
{
  this->acceptfd = 1;
  this->actions = new Actions();
  this->serv = new LPServer();
}

Clientrcv::~Clientrcv()
{

}
