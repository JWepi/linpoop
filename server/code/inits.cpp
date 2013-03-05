
#include "head.hh"

int Datas::GetNewId()
{

  return(666);
}

int Datas::CheckUser(char * str)
{

  return(666);
}

void Datas::init(void)
{
  int i;

  i = -1;
  signal(SIGINT, killed);

  while (++i < NBTHREAD)
  {
      my_threads[i] = (pthread_t)NULL;
  }

  my_threads[i] = 0;
}

void Datas::endofprogram(void)
{
  int i;

  i = -1;

}

Datas::Datas()
{
  this->init();
}

Datas::~Datas()
{
  this->endofprogram();
}

Datas * data = new Datas();
Utils * utils = new Utils(data);
Colors * col = new Colors();

// sig -> type of signal handled
//
// this function is used as a signal handling function and ends the program
void killed(int sig)
{
  col->cout(Colors::RED);
  std::cout << "[Killed] The program has just been manually killed" << std::endl;
  col->cend();
  delete(data);
  exit(sig);
}
