
#ifndef CORE_HH
# define CORE_HH

# include "user.hh"

class Core
{

  protected:
    std::map<int, int> usersfd;

  public:

    void adduser(int userid, int fd);
    void rmvuser(int userid);
    int getusrfd(int userid);
    bool isusr(int userid);
    std::map<int, int> getUsers();

    Core();
    ~Core();
};

#endif
