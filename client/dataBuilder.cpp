#include	"dataBuilder.hh"

Databuilder::Databuilder(std::string str)
{
  this->init(str);
}

Databuilder::Databuilder()
{

}

Databuilder::~Databuilder()
{

}

void Databuilder::setItem(std::string item, std::string value)
{
  if (this->strItems.find(item) != this->strItems.end())
    this->strItems.find(item)->second = value;
  else
    this->strItems.insert(std::pair<std::string, std::string>(item, value));
}

void Databuilder::setItem(std::string item, int value)
{
  if (this->intItems.find(item) != this->intItems.end())
    this->intItems.find(item)->second = value;
  else
    this->intItems.insert(std::pair<std::string, int>(item, value));
}

std::string Databuilder::getStrItem(std::string item)
{
  if (this->strItems.find(item) != this->strItems.end())
    return(this->strItems.find(item)->second);
  return("");
}

int Databuilder::getIntItem(std::string item)
{
  if (this->intItems.find(item) != this->intItems.end())
    return(this->intItems.find(item)->second);
  return(0);
}

void Databuilder::rmvItem(std::string item)
{
  if (this->strItems.find(item) != this->strItems.end())
    this->strItems.erase(item);
  if (this->intItems.find(item) != this->intItems.end())
    this->intItems.erase(item);
}

void Databuilder::init(std::string str)
{
  this->intItems.clear();
  this->strItems.clear();
  
  this->setRawItems(str);
}

void Databuilder::setRawItems(std::string str)
{
  char delim = 2;
  char equal = 3;

  std::istringstream ss(str);

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
}

std::string Databuilder::build()
{
  char delim = 2;
  char equal = 3;

  std::stringstream ret;
  std::map<std::string, std::string>::iterator strit;
  std::map<std::string, int>::iterator intit;

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

  return(ret.str());
}

std::map<std::string, std::string> Databuilder::getStrItems()
{
  return(this->strItems);
}

std::map<std::string, int> Databuilder::getIntItems()
{
  return(this->intItems);
}
