
#include "head.hh"

Actions::Actions(Core * c)
{
  this->core = c;
}

Actions::Actions()
{
  this->core = new Core();
}

Actions::~Actions()
{

}

Core * Actions::getCore()
{
  return (this->core);
}

Packet * Actions::Guidance(Packet * pack)
{
  std::cout << "Guiding data " << pack << std::endl;

  // Switch a remplacer par une map

  switch(pack->getType())
  {
    case 1 :
      //ping
    break;
    case 2 :
      return(ReqCreateAccount(pack->getData()));
    case 4 :
      return(ReqConnectUser(pack->getData()));
    case 6 :
      return(ReqAddFriend(pack->getOrigin(), pack->getTarget()));
    case 7 :
      return(AnsFriendReq(pack->getOrigin(), pack->getTarget(), pack->getData()));
    case 9 :
      return(UsrSentMsg(pack->getOrigin(), pack->getTarget(), pack->getData()));
    case 11 :
      return(UsrSentMsgGroup(pack->getOrigin(), pack->getTarget(), pack->getData()));
    case 15 :
      return(UsrStatusMod(pack->getOrigin(), pack->getData()));
    case 16 :
      return(UsrReqSendFile(pack->getOrigin(), pack->getTarget(), pack->getData()));
    case 17 :
      return(UsrRcvAnsSendFile(pack->getOrigin(), pack->getTarget(), pack->getData()));

  }
}


// 2
Packet * Actions::ReqCreateAccount(const char * str)
{
  int userid = Datas::GetNewId();

  // Create account

  return(AnsCreateAccount(userid));
}
// 4
Packet * Actions::ReqConnectUser(const char * str)
{
  int userid = Datas::CheckUser((char *)str);
  // Check password

  return(AnsConnectUser(userid));
}
// 6
Packet * Actions::ReqAddFriend(int srcUserid, int dstUserid)
{
  // Check dst valide

  return(ReqSendAddFriend(srcUserid, dstUserid));
}
// 7
Packet * Actions::AnsFriendReq(int srcUserid, int dstUserid, const char * str)
{
  // Check str

  return(ReqSendAnsAddFriend(srcUserid, dstUserid, str));
}
// 9
Packet * Actions::UsrSentMsg(int srcUserid, int dstUserid, const char * str)
{
  return(SendMsg(srcUserid, dstUserid, str));
}
// 11
Packet * Actions::UsrSentMsgGroup(int srcUserid, int dstRoom, const char * str)
{
  return(SendMsgGroup(srcUserid, dstRoom, str));
}
// 15
Packet * Actions::UsrStatusMod(int userid, const char * status)
{
  // Send user status modification to contacts
  return(NULL);
}
// 16
Packet * Actions::UsrReqSendFile(int srcUserid, int dstUserid, const char * file)
{
  return(SendUsrReqSendFile(srcUserid, dstUserid, file));
}
// 17
Packet * Actions::UsrRcvAnsSendFile(int srcUserid, int dstUserid, const char * answer)
{
  return(SendUsrAnsReqSendFile(srcUserid, dstUserid, answer));
}

//3
Packet * Actions::AnsCreateAccount(int userid)
{
  
  Packet * pack = new Packet (3, 1, userid, "");

  return(pack);
}
//5    
Packet * Actions::AnsConnectUser(int userid)
{

  Packet * pack = new Packet (5, 1, userid, "0");

  return(pack);
}
//8
Packet * Actions::ReqSendAddFriend(int srcUserid, int dstUserid)
{

  Packet * pack = new Packet (8, srcUserid, dstUserid, "");

  return(pack);
}
//20
Packet * Actions::ReqSendAnsAddFriend(int srcUserid, int dstUserid, const char * answer)
{
  
  Packet * pack = new Packet (20, srcUserid, dstUserid, answer);

  return(pack);
}
//10
Packet * Actions::SendMsg(int srcUserid, int dstUserid, const char * str)
{
  Packet * pack = new Packet (10, srcUserid, dstUserid, str);

  return(pack);
}
//12
Packet * Actions::SendMsgGroup(int srcUserid, int dstRoom, const char * str)
{
  Packet * pack = new Packet (12, srcUserid, dstRoom, str);

  return(pack);
}
//13
Packet * Actions::UserConnected(int userid)
{
  Packet * pack;

  // Parcourir users en ligne et envoyer la notif

  return(pack);
}
//14
Packet * Actions::UserDisconnected(int userid)
{
  Packet * pack;

  // Parcourir users en ligne et envoyer la notif

  return(pack);
}
//18
Packet * Actions::SendUsrReqSendFile(int srcUserid, int dstUserid, const char * file)
{
  Packet * pack = new Packet (18, srcUserid, dstUserid, file);

  return(pack);
}
//19
Packet * Actions::SendUsrAnsReqSendFile(int srcUserid, int dstUserid, const char * answer)
{
  Packet * pack = new Packet (19, srcUserid, dstUserid, answer);

  return(pack);
}
