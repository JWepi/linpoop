
#ifndef USERSMANAGER_HH
# define USERSMANAGER_HH

#include "user.hh"

class Usersmanager
{

  public:
    static void setUserInfo(int userid, std::string infos);
    static void setUserInfo(int userid, User * u);
    static void deleteUser(int userid);
    static User * findUser(int userid);    
    static int generateUserId();

    Usersmanager();
    ~Usersmanager();
};

#endif
