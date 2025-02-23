/////////////////////////////////////////////////////////////////////////////
//
//   TLCUSER.H
//
//   Copyright (c) 1997  Galacticomm, Inc.        All Rights Reserved
//
//   Teleconference Users
//   Declaration
//                                               - Phil Henning 5/14/97
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __TLCUSER_H
#define __TLCUSER_H
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

const SHORT USR_FORGOT          =0x0001;
const SHORT USR_INVITE          =0x0002;

const ULONG USR_NORMAL          =0x00000001;
const ULONG USR_MODERATOR       =0x00000002;
const ULONG USR_OPERATOR        =0x00000004;
const ULONG USR_SQUELCH         =0x00000008;
const ULONG USR_INVISB          =0x00000010;
const ULONG USR_UNLIST          =0x00000020;
const ULONG USR_INEDIT          =0x00000040;
const ULONG USR_INCHAN          =0x00000080;
const ULONG USR_CHATTING        =0x00000100;
const ULONG USR_INMENU          =0x00000200;
const ULONG USR_INCHNEDT        =0x00000400;
const ULONG USR_INACTEDT        =0x00000800;
const ULONG USR_DBOARD          =0x00001000;
const ULONG USR_NOCHAT          =0x00002000;
const ULONG USR_NOACTIONS       =0x00004000;
const ULONG USR_WEBTELHTML      =0x00008000;
const ULONG USR_WEBTELJAVA      =0x00010000;
const ULONG USR_ENCODETAGS      =0x00020000;
const ULONG USR_CHANCHANGE      =0x00040000;
const ULONG USR_LOGOFF          =0x00080000;

const SHORT USR_TYPE_DEFAULT    =1;
const SHORT USR_TYPE_CS         =USR_TYPE_DEFAULT;
const SHORT USR_TYPE_AHTML      =3;

const SHORT EMSGSIZ             =66;

enum { MSG_CURRENT=1,           MSG_REQUESTED           };
enum { CHANDFT_MAIN=0,          CHANDFT_PRIVATE         };
enum { INTERVAL_TOO_HIGH=-1,    INTERVAL_TOO_LOW=-2     };
enum { INTERVAL_HIGH=9,         INTERVAL_LOW=1          };
enum { LIST_FORGET=1,           LIST_IGNORE             };
enum { CHAT_ACCEPTED=1,         CHAT_START              };
enum { USR_SPEED_OK, USR_SPEED_DROP, USR_SPEED_TOOFAST  };


typedef struct flist {
    ULONG           user;
    USHORT          board;
    USHORT          number;
} FLIST, *LPFLIST;

typedef struct tlcusrdsk {
    CHAR            m_pszUserid[UIDSIZ];
    CHAR            m_pszEntCur[EMSGSIZ];
    CHAR            m_pszExitCur[EMSGSIZ];
    CHAR            m_pszEntReq[EMSGSIZ];
    CHAR            m_pszExitReq[EMSGSIZ];
    CHAR            m_pszPrivateTopic[CHAN_MAX_TOPIC_SIZE];
    SHORT           m_iChanDft;
    SHORT           m_iChatInterval;
    GBOOL           m_bSquelched;
    ULONG           m_fFlags;
} USRDSK, *LPUSRDSK;

#ifndef __cplusplus
typedef struct tlcusrstruct {
    CHAR            m_pszUserid[UIDSIZ];
    CHAR            m_pszEntCur[EMSGSIZ];
    CHAR            m_pszExitCur[EMSGSIZ];
    CHAR            m_pszEntReq[EMSGSIZ];
    CHAR            m_pszExitReq[EMSGSIZ];
    SHORT           m_iChanDft;
    SHORT           m_iChatInterval;
    GBOOL           m_bSquelched;
    ULONG           m_fFlags;
#else
typedef struct tlcusrstruct : public USRDSK {
#endif // __cplusplus
    size_t         m_iSize;
    ULONG          m_ulTlcUnum;
    INT            m_iUsrnum;
    SHORT          m_iTimesSpoken;
    SHORT          m_iType;
    USHORT         m_uiTlcBoardNum;
    CHAR           m_pszName[TLCUIDSIZ];
    CHAR           m_pszChannel[CHAN_MAX_SIZE];
    CHAR           m_strLastWhispered[TLCUIDSIZ];
    CHAR           m_chSex;
    LPFLIST        m_arForgetList;
    LPFLIST        m_arIgnoreList;
    INT            m_pfnacc;
    GBOOL          m_msgchanged;
    GBOOL          m_bBeingDeleted;
    SHORT          m_iAge;
} USRSTRUCT, *LPUSRSTRUCT;

#ifdef __cplusplus
};
#endif // __cplusplus
#endif // __TLCUSER_H
