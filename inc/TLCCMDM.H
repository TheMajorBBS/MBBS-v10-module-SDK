
/* RECV_TYPE_SWITCHCHAN */
#define SCMSG_CHAN_DELETE 281 // CHNDELD2
#define SCMSG_USER_LOGOFF 175 // HKICKO3
#define SCMSG_CHAN_FORUPD 1

#define WHMSG_WHIS_SEND   105 // WHSTO2
#define DIMSG_DIR_SEND    109 // DIRTO2
#define MIMSG_MSG_TOPIC   147 // NOWTHE2

#define ENMSG_ENTR1       244 // EXISKL2
#define ENMSG_ENT_TELE    75  // ENTTLC2
#define ENMSG_ENT_CAMEIN  84  // CAMEIN2

#define EXMSG_EXTR1       244 // EXISKL2
#define EXMSG_EXT_LEFTC   83  // LEFTCH2
#define EXMSG_EXT_LEAVE   82  // LVITLC2
#define EXMSG_EXT_HUP     125 // TLCHUP2
#define EXMSG_EXT_KICK    172 // KICKDO2

#define ACTMSG_OUT        0   // public message to anyone
#define ACTMSG_OUT_SECRET 1   // secret message to recipient
#define ACTMSG_RES        2   // normal response to sender
#define ACTMSG_RES_SECRET 3   // response to sender for secret action
