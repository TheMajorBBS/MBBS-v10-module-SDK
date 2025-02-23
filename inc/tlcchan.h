/////////////////////////////////////////////////////////////////////////////
//
//   TLCCHAN.H
//
//   Copyright (c) 1997 Galacticomm, Inc.         All Rights Reserved
//
//   Teleconference Channel
//   Declaration
//                                               - Phil Henning 5/14/97
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __TLCCHAN_H
#define __TLCCHAN_H
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

const SHORT TLCUIDSIZ                   =UIDSIZ+65;
const SHORT CHAN_MAX_SIZE               =TLCUIDSIZ+2;
const SHORT CHAN_MAX_TOPIC_SIZE         =41;

// Channel Type
const SHORT CHAN_TYPE_DEFAULT           =0x0000;
const SHORT CHAN_TYPE_LOCAL             =0x0001;
const SHORT CHAN_TYPE_PRIVATE           =0x0002;
const SHORT CHAN_TYPE_PUBLIC            =0x0004;
const SHORT CHAN_TYPE_NOEDIT            =0x0008;
const SHORT CHAN_TYPE_FORUM             =0x0010;

// Channel flags
const SHORT CHAN_FLAG_NOACTION          =0x0001;
const SHORT CHAN_FLAG_AUTOSQUELCH       =0x0002;
const SHORT CHAN_FLAG_NOWHISPER         =0x0004;
const SHORT CHAN_FLAG_NODIRECTED        =0x0008;
const SHORT CHAN_FLAG_NOPAGE            =0x0010;
const SHORT CHAN_FLAG_NOLIST            =0x0020;
const SHORT CHAN_FLAG_NOSCAN            =0x0040;
const SHORT CHAN_FLAG_ANONYMOUS         =0x0080;
const SHORT CHAN_FLAG_ALIAS             =0x0100;
const SHORT CHAN_FLAG_NOENTMESSAGE      =0x0200;
const SHORT CHAN_FLAG_NONOTIFY          =0x0400;
const SHORT CHAN_FLAG_CLOSED            =0x0800;
const SHORT CHAN_FLAG_PROFOK            =0x1000;
const SHORT CHAN_FLAG_NOBROADCAST       =0x2000;

// Moderator flags
const SHORT MOD_FLAG_CHANGETOPIC        =0x0001;
const SHORT MOD_FLAG_KICKOUT            =0x0002;
const SHORT MOD_FLAG_POST               =0x0004;
const SHORT MOD_FLAG_EDITCHAN           =0x0008;

const SHORT LISTSIZ     =16;

// return values from CTlcChannel::Create
const SHORT CHAN_CREATE_OK              =0x0001;
const SHORT CHAN_CHNTOOLONG             =0x0002;
const SHORT CHAN_VISTOOLONG             =0x0004;
const SHORT CHAN_JOINTOOLONG            =0x0008;
const SHORT CHAN_SPEAKTOOLONG           =0x0010;
const SHORT CHAN_BYPASSTOOLONG          =0x0020;
const SHORT CHAN_MODTOOLONG             =0x0040;
const SHORT CHAN_TOPTOOLONG             =0x0080;
const SHORT CHAN_API_NOT_INIT           =0x0100;
const SHORT CHAN_API_CREATE_ERR         =0x0200;

// CTlcChannel::AddUser retvals
const SHORT CHAN_JOIN_OK                =1;
const SHORT CHAN_JOIN_NOMEM             =-1;
const SHORT CHAN_JOIN_ALREADY           =0;

// CTlcChannel::RemoveUser retvals
const SHORT CHAN_UNJOIN_OK              =0x0001;
const SHORT CHAN_UNJOIN_NOTHERE         =0x0002;

// CTlcChannel::OnSendWhisper retvals
const SHORT CHAN_WHISPER_OK             =0x0001;
const SHORT CHAN_WHISPER_FAIL_NOUSER    =0x0002;

// Params to CanAccess
enum {
      CHAN_AXS_SEE=0,     CHAN_AXS_JOIN,      CHAN_AXS_SPEAK,
      CHAN_AXS_SUPER,     CHAN_AXS_MODERATOR
};

const SHORT LEAVE_CHANNEL       =1;
const SHORT LEAVE_TLC           =2;
const SHORT LEAVE_LOGOFF        =3;
const SHORT LEAVE_PRIV_KICK     =4;

#include "tlcuser.h"

typedef struct chandsk {
     CHAR m_strName[CHAN_MAX_SIZE];
     CHAR m_strTopic[CHAN_MAX_TOPIC_SIZE];
     USHORT m_flags;
     USHORT m_modflags;
     CHAR m_keyVis[KEYSIZ];
     CHAR m_keyJoin[KEYSIZ];
     CHAR m_keySpeak[KEYSIZ];
     CHAR m_keyByPass[KEYSIZ];
     CHAR m_keyMod[KEYSIZ];
     CHAR m_actList1[LISTSIZ];
     CHAR m_actList2[LISTSIZ];
} CHANDSK, *LPCHANDSK;

#ifndef __cplusplus
typedef struct chaninfo {
     CHAR m_strName[CHAN_MAX_SIZE];
     CHAR m_strTopic[CHAN_MAX_TOPIC_SIZE];
     USHORT m_flags;
     USHORT m_modflags;
     CHAR m_keyVis[KEYSIZ];
     CHAR m_keyJoin[KEYSIZ];
     CHAR m_keySpeak[KEYSIZ];
     CHAR m_keyByPass[KEYSIZ];
     CHAR m_keyMod[KEYSIZ];
     CHAR m_actList1[LISTSIZ];
     CHAR m_actList2[LISTSIZ];
#else
typedef struct chaninfo : public CHANDSK {
#endif // __cplusplus
     size_t m_iSize;
     SHORT m_type;
     INT m_count;
     VOID* m_pCustom;
     GBOOL m_bUnlSpeak;
     SHORT m_iCrConsumptionRate;
} CHANINFO, *LPCHANINFO;

extern VOID (*chanActionUpdateHook)(LPCHANINFO);

VOID
dftchanActionUpdateHook(
LPCHANINFO);

#ifdef __cplusplus
};
#endif // __cplusplus
#endif //__TLCCHAN_H

