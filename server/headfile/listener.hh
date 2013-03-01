#ifndef LISTENER_HH
# define LISTENER_HH

class Listener
{

  public:

    virtual void * golisten(void * val) {};
    Listener();
    ~Listener();
};

#endif
