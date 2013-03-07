
#include "head.hh"

void Usersmanager::setUserInfo(int userid, std::string infos)
{
  std::stringstream filename;
  filename << "data/users/" << userid << ".data";
  std::string tmp = filename.str();

  std::ofstream userfile(tmp.c_str());

  userfile << infos;
  userfile.close();
}

void Usersmanager::setUserInfo(int userid, User * u)
{
  std::stringstream filename;
  filename << "data/users/" << userid << ".data";
  std::string tmp = filename.str();

  std::ofstream userfile(tmp.c_str());

  userfile << u->build();
  userfile.close();
}

void Usersmanager::deleteUser(int userid)
{
  std::stringstream filename;
  filename << "data/users/" << userid << ".data";
  std::string tmp = filename.str();

  remove(tmp.c_str());
}

User * Usersmanager::findUser(int userid)
{
  std::string infos;
  std::stringstream filename;

  filename << "data/users/" << userid << ".data";
  std::string tmp = filename.str();

  std::ifstream userfile(tmp.c_str());

  getline(userfile, infos);
  userfile.close();
  std::cout << infos << std::endl;

	User *uu = new User(infos);
  if (infos.size() > 0)
	  return (uu);
  return(new User());
}

int Usersmanager::generateUserId()
{
  std::string maxidstr;
  std::ifstream maxidfile("data/maxid.data");
  int maxid;

  getline(maxidfile, maxidstr);
  std::istringstream conv(maxidstr);
  conv >> maxid;

  std::ofstream maxidup("data/maxid.data");
  maxidup << maxid + 1;

  return (maxid);
}

Usersmanager::Usersmanager()
{

}

Usersmanager::~Usersmanager()
{

}
