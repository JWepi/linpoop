
#include "head.hh"

int main(int ac, char** av)
{
  int i = 0;
  int index;

  col->cout(Colors::GREEN);
  printf("[Main] Activity : Program started !\n\n");
  col->cend();

  Core * core = new Core();
  Actions * actions = new Actions(core);
  LPServer * serv = new LPServer(actions);
  serv->build();

  listen_tome(0, serv);

  wait_threads_end();

  usleep(1000);
  delete(data);

  col->cout(Colors::GREEN);
  printf("[Main] Activity : Program correctly finished !\n");
  col->cend();
  return (0);
}

// index -> indicates which thread shall be started in the thread array
//
// this functions creates and starts a new thread
pthread_t listen_tome(int index, Listener * listener)
{
  int val = 0;

  val = pthread_create(&data->my_threads[index], NULL, (void *(*)(void *))listener->golisten(NULL), (void *)val);
  if (val != 0)
    utils->err("listen_tome", "pthread create error");

  return(data->my_threads[index]);
}

// this function makes the program wait the end of all threads to terminate
void wait_threads_end()
{
  int i;

  i = -1;
  col->cend();
  while (data->my_threads[++i] != Datas::NBTHREAD)
  {
    if (data->my_threads[i] != (pthread_t)NULL)
      pthread_join(data->my_threads[i], NULL);
  }
}
