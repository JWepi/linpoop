
#include "head.hh"

void * Listener::golisten(void * val)
{
  int i = 5;
  while(--i)
  {
    std::cout << "Listening" << std::endl;
    usleep(1);
  }
}

Listener::Listener()
{

}

Listener::~Listener()
{

}
