
#ifndef CLIENTRCV_HH
# define CLIENTRCV_HH

class Clientrcv : public Listener
{

  protected:
    int acceptfd;
    Actions * actions;
    LPServer * serv;

  public:

    void * golisten(void * val);
    Clientrcv(int afd, Actions * a, LPServer * s);
    Clientrcv();
    ~Clientrcv();
};

#endif
