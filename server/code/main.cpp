
#include "head.hh"

int main(int ac, char** av)
{
  col->cout(Colors::GREEN);
  printf("[Main] Activity : Program started !\n\n");
  col->cend();

  Core * core = new Core();
  Actions * actions = new Actions(core);
  LPServer * serv = new LPServer(actions);
  serv->build();

  usleep(1000);
  delete(data);

  col->cout(Colors::GREEN);
  printf("[Main] Activity : Program correctly finished !\n");
  col->cend();
  return (0);
}


pthread_t listen_tome(Clientrcv * crcv)
{
  int i = -1;
  int val = 0;

  while (++i < Datas::NBTHREAD)
  {
    if (data->my_threads[i] == (pthread_t)NULL)
    {
      val = pthread_create(&data->my_threads[i], NULL, &client_listener, (void *)crcv);
      if (val != 0)
        utils->err("listen_tome", "pthread create error");
      return(data->my_threads[i]);
    }
  }

  return((pthread_t)NULL);
}

void * client_listener(void * cli)
{
  Clientrcv * crcv = (Clientrcv *)cli;

  crcv->golisten(NULL);
}
