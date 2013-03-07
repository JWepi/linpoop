
#ifndef USER_HH
# define USER_HH

#include "dataBuilder.hh"

class User : public Databuilder
{
  protected:
    std::map<int, std::string> friends;

  public:
    User(std::string str);
    User();
    ~User();

    void addFriend(int userid);
    void setRawItems(std::string str);
    
    std::string getFriendNick(int userid);

    void rmvFriend(int userid);
    
    void init(std::string str);
    std::string build();

    std::map<int, std::string> getFriends();
};

#endif
