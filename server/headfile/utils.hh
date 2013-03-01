#ifndef UTILS_HH
# define UTILS_HH

class Utils
{

  protected:
    Datas * data;

  public:
    void err(std::string location, std::string reason);

    Utils();
    Utils(Datas * d);
    ~Utils();
};

#endif
