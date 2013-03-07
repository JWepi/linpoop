
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
  std::cout << "bite1" << std::endl;
  std::string infos;
  std::cout << "bite2" << std::endl;
  std::stringstream filename;
  std::cout << "bite3" << std::endl;

  filename << "data/users/" << userid << ".data";
  std::cout << "bite4" << std::endl;
  std::string tmp = filename.str();
  std::cout << "bite5" << std::endl;

  std::ifstream userfile(tmp.c_str());
  std::cout << "bite6" << std::endl;

  getline(userfile, infos);
  std::cout << "bite7" << std::endl;
  userfile.close();
  std::cout << "bite8" << std::endl;
  std::cout << infos << std::endl;

	User *uu = new User(infos);
  std::cout << "bite9" << std::endl;
  if (infos.size() > 0)
	  return (uu);
  std::cout << "bitex" << std::endl;
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
