
#include "user.hh"

User::User(std::string str) : Databuilder()
{
  this->init(str);
}

User::User() : Databuilder()
{
  
}

User::~User()
{

}

void User::init(std::string str)
{
  this->intItems.clear();
  this->strItems.clear();
  this->friends.clear();

  this->setRawItems(str);
}

void User::addFriend(int userid, std::string nick)
{
  if (this->friends.find(userid) == this->friends.end())
  {
    this->friends.insert(std::pair<int, std::string>(userid, nick));
  }
}

std::string User::getFriendNick(int userid)
{
  std::string ret = ""; 
  if (this->friends.find(userid) != this->friends.end())
    ret = this->friends.find(userid)->second;
  return(ret);
}

void User::rmvFriend(int userid)
{
  if (this->friends.find(userid) != this->friends.end())
    this->friends.erase(userid);
}

void User::setRawItems(std::string str)
{
  char split = 1;
  char delim = 2;
  char equal = 3;

  std::istringstream press(str);
  std::string splitstr;

  std::getline(press, splitstr, split);

  std::istringstream ss(splitstr);

  while(!ss.eof())
  {
    std::string extr;
    std::getline(ss, extr, delim);

    std::istringstream iss(extr);
    std::string first, second;

    std::getline(iss, first, equal);
    std::getline(iss, second, equal);

    int val;
    std::istringstream check(second);

    check >> val;
    if(val == 0)
      this->setItem(first, second);
    else
      this->setItem(first, val);
  }

  std::getline(press, splitstr, split);

  std::istringstream friendss(splitstr);

  while(!friendss.eof())
  {
    std::string extr;
    std::getline(friendss, extr, delim);
    if (extr.size() > 0)
    {
      std::istringstream iss(extr);
      std::string first, second;

      std::getline(iss, first, equal);
      std::getline(iss, second, equal);

      int val;
      std::istringstream check(first);

      check >> val;
      this->addFriend(val, second);
    }
  }
}

std::string User::build()
{
  char split = 1;
  char delim = 2;
  char equal = 3;

  std::stringstream ret;
  std::map<std::string, std::string>::iterator strit;
  std::map<std::string, int>::iterator intit;
  std::map<int, std::string>::iterator frit;

  for(strit = this->strItems.begin(); strit != this->strItems.end(); ++strit)
  {
    if (strit != this->strItems.begin())
      ret << delim;
    ret << strit->first << equal << strit->second;
  }

  for(intit = this->intItems.begin(); intit != this->intItems.end(); ++intit)
  {
    if (intit != this->intItems.begin() || ret.rdbuf()->in_avail() > 0)
      ret << delim;
    ret << intit->first << equal << intit->second;
  }

  ret << split;

  for(frit = this->friends.begin(); frit != this->friends.end(); ++frit)
  {
    if (frit != this->friends.begin())
      ret << delim;
    ret << frit->first << equal << frit->second;
  }

  return(ret.str());
}

std::map<int, std::string> User::getFriends()
{
  return(this->friends);
}
