
#ifndef ACTIONS_HH
# define ACTIONS_HH

class Actions
{

  protected:
    Core * core;

// 2
    int ReqCreateAccount(char * str);
// 4
    int ReqConnectUser(int userid, char * passwd);
// 6
    int ReqAddFriend(int srcUserid, int dstUserid);
// 7
    int AnsFriendReq(int srcUserid, int dstUserid, char * str);
// 9
    int UsrSentMsg(int srcUserid, int dstUserid, char * str);
// 11
    int UsrSentMsgGroup(int srcUserid, int dstRoom, char * str);
// 15
    int UsrStatusMod(int userid, char * status);
// 16
    int UsrReqSendFile(int srcUserid, int dstUserid, char * file);
// 17
    int UsrRcvAnsSendFile(int srcUserid, int dstUserid, char * answer);

  public:
    Actions(Core * c);
    Actions();
    ~Actions();

    Core * getCore();

    int Guidance(int pack);

//3
    int AnsCreateAccount(int userid);
//5    
    int AnsConnectUser(int userid);
//8
    int ReqSendAddFriend(int srcUserid, int dstUserid);
//20
    int ReqSendAnsAddFriend(int srcUserid, int dstUserid);    
//10
    int SendMsg(int srcUserid, int dstUserid, char * str);
//12
    int SendMsgGroup(int srcUserid, int dstRoom, char * str);
//13
    int UserConnected(int userid);
//14
    int UserDisconnected(int userid);
//18
    int SendUsrReqSendFile(int srcUserid, int dstUserid, char * file);
//19
    int SendUsrAnsReqSendFile(int srcUserid, int dstUserid, char * answer);
};

#endif
