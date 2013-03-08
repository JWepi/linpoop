
#include "head.hh"

void * LPServer::golisten(void * val)
{
  socklen_t clientaddrlen = 0;
	struct in_addr	addr;

  while(1)
  {
    char ip[INET_ADDRSTRLEN + 1];

    this->acceptfd = accept(this->sockfd, (struct sockaddr *) &this->client, &clientaddrlen);
    inet_ntop(AF_INET, &(this->client.sin_addr), ip, INET_ADDRSTRLEN);
    inet_aton(ip, &addr);
	std::cout << inet_ntoa(addr) << "MESSAGE A COTE" << std::endl;
    if (acceptfd == -1)
      utils->err("Server::golisten", "accept function failed");

    Clientrcv * cr;
    cr = new Clientrcv(this->acceptfd, this->actions, this, ip);
    listen_tome(cr);

  }

  if (close(acceptfd) == -1)
    utils->err("Server::golisten", "close function on acceptfd failed");

  if (close(sockfd) == -1)
    utils->err("Server::golisten", "close function on sockfd failed");
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
  
  if (bind(sockfd, (const struct sockaddr *) &server, sizeof(struct sockaddr_in)) == -1)
    utils->err("Server::build", "bind function failed"); 

  if (listen(sockfd, 0) == -1)
    utils->err("Server::build", "listen function failed"); 

  this->golisten(NULL);
}

void LPServer::sendpacket(int fd, char * pack, int size)
{
  if (send(fd, pack, size, 0) == -1)
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
