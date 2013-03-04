
#include "head.hh"

void * Clientrcv::golisten(void * val)
{
  char buff[Datas::BUFF];
  ssize_t bytesreceived = 0;

  while (1)
  {
    memset(buff, 0, Datas::BUFF);

    bytesreceived = recv(this->acceptfd, buff, Datas::BUFF, 0);

    if (bytesreceived == -1)
      utils->err("LPServer::listen", "recv function failed");
    
    if (bytesreceived == 0)
    {
      // Action a definir
      return(NULL);
    }

    std::cout << "I received : " << buff << std::endl << std::endl;

    Packet * packet = new Packet((void *)buff);

    this->serv->sendpacket(this->acceptfd, (char*)this->actions->Guidance(packet));
  }
  return(NULL);
}

Clientrcv::Clientrcv(int afd, Actions * a, LPServer * s) : Listener()
{
  this->acceptfd = afd;
  this->actions = a;
  this->serv = s;
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
