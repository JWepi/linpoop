
#ifndef SERVER_HH
# define SERVER_HH

#include "actions.hh"

class LPServer : public Listener
{

  protected:
    Actions * actions;
    int sockfd;
    int acceptfd;
    struct sockaddr_in client;

  public:
    void * golisten(void * val);
    void build();
    void sendpacket(int fd, char * pack);

    LPServer(Actions * a);
    LPServer();
    ~LPServer();
};

#endif
