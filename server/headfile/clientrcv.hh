
#ifndef CLIENTRCV_HH
# define CLIENTRCV_HH

class Clientrcv : public Listener
{

  protected:
    int acceptfd;
    Actions * actions;
    LPServer * serv;
    std::string ip;

  public:

    void hasLeft(int userid);
    void * golisten(void * val);
    Clientrcv(int afd, Actions * a, LPServer * s, std::string myip);
    Clientrcv();
    ~Clientrcv();
};

#endif
