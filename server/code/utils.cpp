
#include "head.hh"

/*
  This file is a custom utilitary file.
*/

Utils::Utils()
{
  this->data = new Datas();
}

Utils::Utils(Datas * d)
{
  this->data = d;
}


// location -> function where an error occured
// reason -> the kind of error encountered
//
// this is a custom error diplaying function which also kills the program
void Utils::err(std::string location, std::string reason)
{
  col->cout(Colors::RED);
  std::cout << "[Error] Location : " << location << " -> Reason : " << reason << std::endl << std::endl;
  std::cout << "[Error] The program is being killed" << std::endl << std::endl;  
  col->cend();
  delete(data);
  exit(0);
}

