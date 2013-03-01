
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

int Actions::Guidance(int pack)
{
  std::cout << "Guiding data " << pack << std::endl;

  // Switch a remplacer par une map

  switch(pack)
  {
    case 1 :
      //ping
    break;
    case 2 :
      return(ReqCreateAccount("user:password"));
    case 4 :
      return(ReqConnectUser(0, "password"));
    case 6 :
      return(ReqAddFriend(0, 1));
    case 7 :
      return(AnsFriendReq(0, 1, "1"));
    case 9 :
      return(UsrSentMsg(0, 1, "Coucou"));
    case 11 :
      return(UsrSentMsgGroup(0, 1, "Coucou a tous"));
    case 15 :
      return(UsrStatusMod(0, "Online"));
    case 16 :
      return(UsrReqSendFile(0, 1, "info.txt"));
    case 17 :
      return(UsrRcvAnsSendFile(0, 1, "1"));

  }
}


// 2
int Actions::ReqCreateAccount(char * str)
{
  int userid = 0;
  // Create account

  // Create userid
  return(AnsCreateAccount(userid));
}
// 4
int Actions::ReqConnectUser(int userid, char * passwd)
{
  // Check password

  return(AnsConnectUser(userid));
}
// 6
int Actions::ReqAddFriend(int srcUserid, int dstUserid)
{
  // Check dst valide

  return(ReqSendAddFriend(srcUserid, dstUserid));
}
// 7
int Actions::AnsFriendReq(int srcUserid, int dstUserid, char * str)
{
  // Check str

  return(ReqSendAnsAddFriend(srcUserid, dstUserid));
}
// 9
int Actions::UsrSentMsg(int srcUserid, int dstUserid, char * str)
{
  return(SendMsg(srcUserid, dstUserid, str));
}
// 11
int Actions::UsrSentMsgGroup(int srcUserid, int dstRoom, char * str)
{
  return(SendMsgGroup(srcUserid, dstRoom, str));
}
// 15
int Actions::UsrStatusMod(int userid, char * status)
{
  // Send user status modification to contacts
  return(0);
}
// 16
int Actions::UsrReqSendFile(int srcUserid, int dstUserid, char * file)
{
  return(SendUsrReqSendFile(srcUserid, dstUserid, file));
}
// 17
int Actions::UsrRcvAnsSendFile(int srcUserid, int dstUserid, char * answer)
{
  return(SendUsrAnsReqSendFile(srcUserid, dstUserid, answer));
}

//3
int Actions::AnsCreateAccount(int userid)
{
  int pack = 0;
  // build packet

  return(pack);
}
//5    
int Actions::AnsConnectUser(int userid)
{
  int pack = 0;
  // build packet

  return(pack);
}
//8
int Actions::ReqSendAddFriend(int srcUserid, int dstUserid)
{
  int pack = 0;
  // build packet

  return(pack);
}
//20
int Actions::ReqSendAnsAddFriend(int srcUserid, int dstUserid)
{
  int pack = 0;
  // build packet

  return(pack);
}
//10
int Actions::SendMsg(int srcUserid, int dstUserid, char * str)
{
  int pack = 0;
  // build packet

  return(pack);
}
//12
int Actions::SendMsgGroup(int srcUserid, int dstRoom, char * str)
{
  int pack = 0;
  // build packet

  return(pack);
}
//13
int Actions::UserConnected(int userid)
{
  int pack = 0;
  // build packet

  return(pack);
}
//14
int Actions::UserDisconnected(int userid)
{
  int pack = 0;
  // build packet

  return(pack);
}
//18
int Actions::SendUsrReqSendFile(int srcUserid, int dstUserid, char * file)
{
  int pack = 0;
  // build packet

  return(pack);
}
//19
int Actions::SendUsrAnsReqSendFile(int srcUserid, int dstUserid, char * answer)
{
  int pack = 0;
  // build packet

  return(pack);
}
