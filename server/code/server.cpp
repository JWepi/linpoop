
#include "head.hh"

void * LPServer::golisten(void * val)
{
  socklen_t clientaddrlen = 0;

  while(1)
  {
    this->acceptfd = accept(this->sockfd, (struct sockaddr *) &this->client, &clientaddrlen);

    if (acceptfd == -1)
      utils->err("Server::listen", "accept function failed");

    Clientrcv * cr;
    cr = new Clientrcv(this->acceptfd, this->actions, this);
    cr->golisten(NULL);
  }

  if (close(acceptfd) == -1)
    utils->err("Server::listen", "close function on acceptfd failed");

  if (close(sockfd) == -1)
    utils->err("Server::listen", "close function on sockfd failed");
}

void LPServer::build()
{
  int forceRebind = 1;
  struct sockaddr_in server;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd == -1)
    utils->err("Server::build", "socket function failed");

  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &forceRebind, sizeof(int)) == -1)
    utils->err("Server::build", "setsockopt function failed");

  memset((void *) &server, 0, sizeof(struct sockaddr_in));
  server.sin_family = AF_INET;
  server.sin_port = htons(8008);
  server.sin_addr.s_addr = INADDR_ANY;
  
  if (-1 == bind(sockfd, (const struct sockaddr *) &server, sizeof(struct sockaddr_in)))
    utils->err("Server::build", "bind function failed"); 

  if (-1 == listen(sockfd, 0))
    utils->err("Server::build", "listen function failed"); 



/*
 if (-1 == send(acceptfd, "lala", (size_t) strlen(reply) + 1, 0))
 { 
perror("send parent"); 
return 1;
 }
*/

}

void LPServer::sendpacket(int fd, char * pack)
{
  if (send(fd, pack, strlen(pack) + 1, 0) == -1)
    utils->err("Server::sendpacket", "send function failed");
}

LPServer::LPServer(Actions * a) : Listener()
{
  this->actions = a;
}

LPServer::LPServer() : Listener()
{
  this->actions = new Actions();
}

LPServer::~LPServer()
{

}
