
#ifndef DATAS_HH
# define DATAS_HH

class Datas
{

  protected:
    // this function initializes the different variables of the program
    void init(void);
    // this function is called at the end of the program to clean what has to be cleaned    
    static void endofprogram(void);  

  public:
    //STATIC DATAS

    // Number of protocol listeners
    static const int NBTHREAD = 1000;
    // Maximum number of loops
    static const int NBLOOPS = 20;
    // If set at 1, loops will last forever, if set at 0 they will loop NBLOOPS times
    static const bool INFINITE = true;
    // If enabled, the program may stop on some encountered errors
    static const bool STRICT = true;
    // If enabled, will display debug messages when launched
    static const bool DEBUG = false;
    // If enabled, colors will appear in the program
    static const bool SHOW = true;
    // Usual size of the buffer
    static const int BUFF = 4096;

    static int GetNewId();
    static int CheckUser(char * str);

    void (* listners[Datas::NBTHREAD + 1])(void);
    pthread_t my_threads[Datas::NBTHREAD + 1];
    time_t now;

    Datas();
    ~Datas();
};

#endif
