
#ifndef ACTIONS_HH
# define ACTIONS_HH

class Actions
{

  protected:
    Core * core;

// 2
    Packet * ReqCreateAccount(const char * str);
// 4
    Packet * ReqConnectUser(const char * str);
// 6
    Packet * ReqAddFriend(int srcUserid, int dstUserid);
// 7
    Packet * AnsFriendReq(int srcUserid, int dstUserid, const char * str);
// 9
    Packet * UsrSentMsg(int srcUserid, int dstUserid, const char * str);
// 11
    Packet * UsrSentMsgGroup(int srcUserid, int dstRoom, const char * str);
// 16
    Packet * UsrReqSendFile(int srcUserid, int dstUserid, const char * file);
// 17
    Packet * UsrRcvAnsSendFile(int srcUserid, int dstUserid, const char * answer);
// 21
    Packet * ReqJoinRoom(int userid, int roomid);
// 22
    Packet * ReqLeaveRoom(int userid, int dstRoom);
// 23
    Packet * ReqDelFriend(int srcUserid, int dstUserid);
// 24
    Packet * ReqModUser(int userid, const char * str);
// 13
    Packet * ReqOnFriends(int srcUserid);
// 25
    Packet * ReqInfos(int userid, int target);

  public:
    Actions(Core * c);
    Actions();
    ~Actions();

    Core * getCore();

    Packet * Guidance(Packet * pack);

//1
    Packet * Ping(int userid);
//3
    Packet * AnsCreateAccount(int userid, std::string tosend);
//5    
    Packet * AnsConnectUser(int userid, std::string tosend);
//8
    Packet * ReqSendAddFriend(int srcUserid, int dstUserid);
//20
    Packet * ReqSendAnsAddFriend(int srcUserid, int dstUserid, const char * answer);    
//10
    Packet * SendMsg(int srcUserid, int dstUserid, const char * str);
//12
    Packet * SendMsgGroup(int srcUserid, int dstRoom, const char * str);
//18
    Packet * SendUsrReqSendFile(int srcUserid, int dstUserid, const char * file);
//19
    Packet * SendUsrAnsReqSendFile(int srcUserid, int dstUserid, const char * answer);
//14
    Packet * SendOnFriends(int userid, const char * list);
//26
    Packet * SendInfos(int userid, const char * infos);
// 15
    Packet * UsrStatusMod(int userid, const char * status);
};

#endif
