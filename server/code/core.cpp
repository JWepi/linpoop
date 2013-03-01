
#include "head.hh"

void Core::adduser(int userid, int fd)
{
  if (!this->isusr(userid))
    this->usersfd.insert(std::pair<int, int>(userid, fd)); 
}

void Core::rmvuser(int userid)
{
  if (this->isusr(userid))
    this->usersfd.erase(userid);
}

int Core::getusrfd(int userid)
{
  if (this->isusr(userid))
    return (this->usersfd.find(userid)->second);
  return (1);
}

bool Core::isusr(int userid)
{
  if (this->usersfd.find(userid) != this->usersfd.end())
    return (true);
  return (false);
}

std::map<int, int> Core::getUsers()
{
  return (this->usersfd);
}

Core::Core()
{

}

Core::~Core()
{

}
