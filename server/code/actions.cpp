
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
  std::cout << "Packet received : " << std::endl;

  std::cout << "   - Request type : " << (int)pack->getType() << std::endl;
  std::cout << "   - Request src  : " << pack->getOrigin() << std::endl;
  std::cout << "   - Request dst  : " << pack->getTarget() << std::endl;
  std::cout << "   - Request data : " << pack->getData() << std::endl << std::endl;

  // Switch a remplacer par une map

  switch(pack->getType())
  {
    case 1 :
      return(Ping(0));
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
  Databuilder * tosend = new Databuilder();
  int userid = 0;
  bool created = false;
  User * u = new User(str);

  tosend->setItem("answer", 0);

  if (u->hasItem("nick"))
  {
     userid = Usersmanager::generateUserId();
     u->setItem("id", userid);
     Usersmanager::setUserInfo(userid, u);
     created = true;
     tosend->setItem("answer", 1);
     tosend->setItem("id", userid);
  }

  return(AnsCreateAccount(userid, tosend->build()));
}
// 4
Packet * Actions::ReqConnectUser(const char * str)
{
  int userid = 0;
  Databuilder * db = new Databuilder(str);

  User * u = Usersmanager::findUser(db->getIntItem("id"));
  
  if (db->getStrItem("nick") == u->getStrItem("nick"))
  {
    Databuilder * db = new Databuilder();
    userid = u->getIntItem("id");
    db->setItem("status", "on");
    this->UsrStatusMod(userid, db->build().c_str());
  }
  else
    u = new User();

  return(AnsConnectUser(userid, u->build()));
}
// 6
Packet * Actions::ReqAddFriend(int srcUserid, int dstUserid)
{
  return(ReqSendAddFriend(srcUserid, dstUserid));
}
// 7
Packet * Actions::AnsFriendReq(int srcUserid, int dstUserid, const char * str)
{
  Databuilder * db = new Databuilder(str);

  if (db->getIntItem("answer"))
  {
    User * u1 = Usersmanager::findUser(srcUserid);
    User * u2 = Usersmanager::findUser(dstUserid);

    u1->addFriend(u2->getIntItem("id"));
    u2->addFriend(u1->getIntItem("id"));

    Usersmanager::setUserInfo(u1->getIntItem("id"), u1->build());
    Usersmanager::setUserInfo(u2->getIntItem("id"), u2->build());
  }

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
  User * u = Usersmanager::findUser(userid);

  std::map<int, std::string> flist = u->getFriends();
  std::map<int, std::string>::iterator it;

  for(it = flist.begin(); it != flist.end(); it++)
  {
    if(this->core->isusr(it->first))
    {
      Packet * pack = new Packet (15, userid, it->first, status);
      LPServer::sendpacket(this->core->getusrfd(it->first), (char *)pack->buildPacket(), pack->getPacketSize());
    }
  }

  return(Ping(userid));
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
// 21
Packet * Actions::ReqJoinRoom(int userid, int roomid)
{
  User * room = Usersmanager::findUser(roomid);
  if (!room->getIntItem("room"))
  {
    roomid = Usersmanager::generateUserId();
    room->setItem("room", 1);
    room->setItem("id", roomid);
    room->setItem("nick", "ROOM " + roomid);
    Usersmanager::setUserInfo(roomid, room->build());    
  }
  User * usr = Usersmanager::findUser(userid);
  usr->addFriend(roomid);

  Usersmanager::setUserInfo(userid, usr->build());

  return(Ping(userid));
}
// 22
Packet * Actions::ReqLeaveRoom(int userid, int roomid)
{
  User * usr = Usersmanager::findUser(userid);
  usr->rmvFriend(roomid);

  Usersmanager::setUserInfo(userid, usr->build());

  return(Ping(userid));
}
// 23
Packet * Actions::ReqDelFriend(int srcUserid, int dstUserid)
{
  User * usr = Usersmanager::findUser(srcUserid);
  usr->rmvFriend(dstUserid);

  Usersmanager::setUserInfo(srcUserid, usr->build());

  return(Ping(srcUserid));
}
// 24
Packet * Actions::ReqModUser(int userid, const char * str)
{
  User * usr = Usersmanager::findUser(userid);
  usr->init(str);

  Usersmanager::setUserInfo(userid, usr->build());

  return(Ping(userid));
}
// 13
Packet * Actions::ReqOnFriends(int userid)
{
  User * usr = Usersmanager::findUser(userid);
  User * ret = new User();
  std::map<int, std::string> flist = usr->getFriends();
  std::map<int, std::string>::iterator it;

  for(it = flist.begin(); it != flist.end(); it++)
  {
    if(this->core->isusr(it->first))
      ret->addFriend(it->first);
  }

  return(this->SendOnFriends(userid, ret->build().c_str()));
}
// 25
Packet * Actions::ReqInfos(int userid, int target)
{
  User * usr = Usersmanager::findUser(target);

  return(SendInfos(userid, usr->build().c_str()));
}


//1
Packet * Actions::Ping(int userid)
{
  Packet * pack = new Packet (1, 1, userid, "");
  return(pack);
}
//3
Packet * Actions::AnsCreateAccount(int userid, std::string tosend)
{
  Packet * pack = new Packet (3, 1, userid, tosend.c_str());
  return(pack);
}
//5    
Packet * Actions::AnsConnectUser(int userid, std::string tosend)
{
  Packet * pack = new Packet (5, 1, userid, tosend.c_str());
  return(pack);
}
//8
Packet * Actions::ReqSendAddFriend(int srcUserid, int dstUserid)
{
  Packet * pack = new Packet (8, srcUserid, dstUserid, "");
  int fd = this->core->getusrfd(dstUserid);

  if(this->core->isusr(dstUserid))
  {
    LPServer::sendpacket(fd, (char *)pack->buildPacket(), pack->getPacketSize());
    return(Ping(srcUserid));
  }

  Databuilder * db = new Databuilder();
  db->setItem("answer", 0);

  return(ReqSendAnsAddFriend(dstUserid, srcUserid, db->build().c_str()));
}
//20
Packet * Actions::ReqSendAnsAddFriend(int srcUserid, int dstUserid, const char * answer)
{  
  Packet * pack = new Packet (20, srcUserid, dstUserid, answer);
  int fd = this->core->getusrfd(dstUserid);

  if(this->core->isusr(dstUserid))
    LPServer::sendpacket(fd, (char *)pack->buildPacket(), pack->getPacketSize());

  return(Ping(srcUserid));
}
//10
Packet * Actions::SendMsg(int srcUserid, int dstUserid, const char * str)
{
  Packet * pack = new Packet (10, srcUserid, dstUserid, str);
  int fd = this->core->getusrfd(dstUserid);

  if(this->core->isusr(dstUserid))
    LPServer::sendpacket(fd, (char *)pack->buildPacket(), pack->getPacketSize());

  return(Ping(srcUserid));
}
//12
Packet * Actions::SendMsgGroup(int srcUserid, int dstRoom, const char * str)
{
  Packet * pack = new Packet (12, srcUserid, dstRoom, str);
  int fd = this->core->getusrfd(dstRoom);

  if(this->core->isusr(dstRoom))
    LPServer::sendpacket(fd, (char *)pack->buildPacket(), pack->getPacketSize());

  return(Ping(srcUserid));
}

//18
Packet * Actions::SendUsrReqSendFile(int srcUserid, int dstUserid, const char * file)
{
  Packet * pack = new Packet (18, srcUserid, dstUserid, file);
  int fd = this->core->getusrfd(dstUserid);

  if(this->core->isusr(dstUserid))
  {
    LPServer::sendpacket(fd, (char *)pack->buildPacket(), pack->getPacketSize());
    return(Ping(srcUserid));
  }

  Databuilder * db = new Databuilder();
  db->setItem("answer", 0);

  return(SendUsrAnsReqSendFile(dstUserid, srcUserid, db->build().c_str()));
}
//19
Packet * Actions::SendUsrAnsReqSendFile(int srcUserid, int dstUserid, const char * answer)
{
  Packet * pack = new Packet (19, srcUserid, dstUserid, answer);
  int fd = this->core->getusrfd(dstUserid);

  if(this->core->isusr(dstUserid))
    LPServer::sendpacket(fd, (char *)pack->buildPacket(), pack->getPacketSize());

  return(Ping(srcUserid));
}
//14
Packet * Actions::SendOnFriends(int userid, const char * list)
{
  Packet * pack = new Packet (14, 1, userid, list);

  return(pack);
}
//26
Packet * Actions::SendInfos(int userid, const char * infos)
{
  Packet * pack = new Packet (26, 1, userid, infos);

  return(pack);
}
