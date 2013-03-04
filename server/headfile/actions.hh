
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
// 15
    Packet * UsrStatusMod(int userid, const char * status);
// 16
    Packet * UsrReqSendFile(int srcUserid, int dstUserid, const char * file);
// 17
    Packet * UsrRcvAnsSendFile(int srcUserid, int dstUserid, const char * answer);

  public:
    Actions(Core * c);
    Actions();
    ~Actions();

    Core * getCore();

    Packet * Guidance(Packet * pack);

//3
    Packet * AnsCreateAccount(int userid);
//5    
    Packet * AnsConnectUser(int userid);
//8
    Packet * ReqSendAddFriend(int srcUserid, int dstUserid);
//20
    Packet * ReqSendAnsAddFriend(int srcUserid, int dstUserid, const char * answer);    
//10
    Packet * SendMsg(int srcUserid, int dstUserid, const char * str);
//12
    Packet * SendMsgGroup(int srcUserid, int dstRoom, const char * str);
//13
    Packet * UserConnected(int userid);
//14
    Packet * UserDisconnected(int userid);
//18
    Packet * SendUsrReqSendFile(int srcUserid, int dstUserid, const char * file);
//19
    Packet * SendUsrAnsReqSendFile(int srcUserid, int dstUserid, const char * answer);
};

#endif
