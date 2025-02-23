////////////////////////////////////////////////////////////////////////////
//
//   TLCDCMD.H
//
//   Copyright (c) 1997 Galacticomm, Inc.         All Rights Reserved
//
//   Default Command Handlers
//   result codes/structures
//                                               - Phil Henning 6/4/97
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __TLCDCMD_H
#define __TLCDCMD_H

enum {
        CMD_JOIN=1,     CMD_SCAN,       CMD_LIST,       CMD_DIRECT,
        CMD_HELP,       CMD_UNLIST,     CMD_EDIT,       CMD_TOPIC,
        CMD_MENU,       CMD_INVITE,     CMD_UNINVITE,   CMD_FORGET,
        CMD_REMEMBER,   CMD_SQUELCH,    CMD_UNSQUELCH,  CMD_CHANNEL,
        CMD_ACTION,     CMD_CHAT,       CMD_CLOSE,      CMD_OPEN,
        CMD_ECHO,       CMD_ZAPPO,      CMD_IGNORE,     CMD_NOTICE,
        CMD_GENERIC,
        CMD_SPEAK=98,   CMD_WHISPER=99
};

// CMD_JOIN status codes

enum {
        CMD_JOIN_NOCHAN=1,      CMD_JOIN_AMBIG,         CMD_JOIN_ALREADY,
        CMD_JOIN_NOACS,         CMD_JOIN_NOT_INVITED,   CMD_JOIN_PRIV_ALREADY,
        CMD_JOIN_CANTLFORUM,    CMD_JOIN_CANTJFORUM,    CMD_JOIN_TOOFAST
};

// CMD_LIST status codes

enum {
        CMD_LIST_DONE=1,        CMD_LIST_START,         CMD_LIST_ITEM
};

// CMD_SCAN status codes

enum {
        CMD_SCAN_DONE=1,        CMD_SCAN_START,         CMD_SCAN_ITEM,
        CMD_SCAN_NOSUCH,        FULL,                   UNLIST,
        CHANUN,                 PARA
};


// CMD_DIRECT status codes

enum {
        CMD_DIRECT_NOONE=1,     CMD_DIRECT_NOSUCH,      CMD_DIRECT_AMBIG,
        CMD_DIRECT_DAMBIG,      CMD_DIRECT_FGT,         CMD_DIRECT_SQ
};

// CMD_WHISPER status codes

enum {
        CMD_WHISPER_NOONE=1,    CMD_WHISPER_NOSUCH,     CMD_WHISPER_AMBIG,
        CMD_WHISPER_REFAILED,   CMD_WHISPER_PAMBIG,     CMD_WHISPER_PAGATT,
        CMD_WHISPER_FGT
};

// CMD_HELP status codes

enum {
        CMD_HELP_ALL=1
};

// CMD_EDIT status codes

enum {
        CMD_EDIT_ENTER=1
};

// CMD_TOPIC status codes

enum {
        CMD_TOPIC_CLEARED=1,    CMD_TOPIC_CHANGED,      CMD_TOPIC_NOACCESS,
        CMD_TOPIC_TOOLONG
};

// CMD_INVITE status codes

enum {
        CMD_INVITE_NOACS=1,     CMD_INVITE_NOONE,       CMD_INVITE_AMBIG,
        CMD_INVITE_NOSUCH,      CMD_INVITE_ALRDY,       CMD_INVITE_NOTIFY,
        CMD_INVITE_NOSELF,      CMD_INVITE_TOOMANY,     CMD_INVITE_FGT,
        CMD_INVITE_CANT
};

// CMD_UNINVITE status codes

enum {
        CMD_UNINVITE_NOONE=1,   CMD_UNINVITE_AMBIG,     CMD_UNINVITE_NOSUCH,
        CMD_UNINVITE_NOTINV,    CMD_UNINVITE_KICK,      CMD_UNINVITE_UNINV,
        CMD_UNINVITE_MYKICK,    CMD_UNINVITE_MYUNINV,   CMD_UNINVITE_NOSELF,
        CMD_UNINVITE_MODERATOR
};

// CMD_FORGET status codes

enum {
        CMD_FORGET_NOACS=1,     CMD_FORGET_NOONE,       CMD_FORGET_AMBIG,
        CMD_FORGET_NOSUCH,      CMD_FORGET_NOSELF,      CMD_FORGET_MODERATOR,
        CMD_FORGET_NOFORGET,    CMD_FORGET_ALRDY,       CMD_FORGET_TOOMANY
};

// CMD_REMEMBER status codes

enum {
        CMD_REMEMBER_NOONE=1,   CMD_REMEMBER_AMBIG,     CMD_REMEMBER_NOSUCH,
        CMD_REMEMBER_NOSELF,    CMD_REMEMBER_NOTFGT
};

// CMD_SQUELCH status codes

enum {
        CMD_SQUELCH_NOONE=1,    CMD_SQUELCH_AMBIG,      CMD_SQUELCH_NOSUCH,
        CMD_SQUELCH_NOSELF,     CMD_SQUELCH_MODERATOR,  CMD_SQUELCH_ALRDY
};

// CMD_UNSQUELCH status codes

enum {
        CMD_UNSQUELCH_NOONE=1,  CMD_UNSQUELCH_AMBIG,    CMD_UNSQUELCH_NOSUCH,
        CMD_UNSQUELCH_NOTSQ,

};

// CMD_CHANNEL status codes

enum {
         CMD_CHANNEL_ENTER_SYS=1,                       CMD_CHANNEL_ENTER_MOD
};

// CMD_ACTION status codes

enum {
        CMD_ACTION_HELP=1,      CMD_ACTION_EDITOR,      CMD_ACTION_LIST,
        CMD_ACTION_NOSUCHLIST,  CMD_ACTION_LISTHEADER,  CMD_ACTION_NEXTLINE,
        CMD_ACTION_NONE,        CMD_ACTION_ON,          CMD_ACTION_OFF
};

// CMD_SPEAK status codes

enum {
        CMD_SPEAK_INVIS=1,      CMD_SPEAK_SQUEL,        CMD_SPEAK_LIMITED,
        CMD_SPEAK_TOOFAST
};

// CMD_CHAT status codes

enum {
        CMD_CHAT_CAMBIG=1,      CMD_CHAT_NOSUCH,        CMD_CHAT_AMBIG,
        CMD_CHAT_ALREADY,       CMD_CHAT_SELF,          CMD_CHAT_NOCHAT,
        CMD_CHAT_CANTCHAT,      CMD_CHAT_TOOSOON,       CMD_CHAT_CANT,
        CMD_CHAT_NOACCESS,      CMD_CHAT_HELP,          CMD_CHAT_NOTIFY,
        CMD_CHAT_NOTIFIED,      CMD_CHAT_ACCEPTED,      CMD_CHAT_BEGIN,
        CMD_CHAT_FGT,           CMD_CHAT_HANGUP,        CMD_CHAT_STOPCHATTING,
        CMD_CHAT_NOCHATU,       CMD_CHAT_BUSY,          CMD_CHAT_YOUALREADY
};

// CMD_OPEN status codes

enum {
        CMD_OPEN_PRIVATE=1,     CMD_OPEN_ALREADY
};

// CMD_CLOSE status codes

enum {
        CMD_CLOSE_PRIVATE=1,    CMD_CLOSE_ALREADY
};

// CMD_ECHO status codes

enum {
        CMD_ECHO_ON=1,          CMD_ECHO_OFF,           CMD_ECHO_PX,
        CMD_ECHO_HELP
};

// CMD_ZAPPO status codes

enum {
        CMD_ZAPPO_NOUSR=1,      CMD_ZAPPO_DELETED,      CMD_ZAPPO_NODELETE,
        CMD_ZAPPO_SUSPENDED,    CMD_ZAPPO_NOUSRON
};

// CMD_IGNORE status codes

enum {
        CMD_IGNORE_NOACS=1,     CMD_IGNORE_NOONE,       CMD_IGNORE_AMBIG,
        CMD_IGNORE_NOSUCH,      CMD_IGNORE_ALRDY,       CMD_IGNORE_NOSYS,
        CMD_IGNORE_NOSELF,      CMD_IGNORE_TOOMANY
};

// CMD_NOTICE status codes

enum {
        CMD_NOTICE_NOONE=1,     CMD_NOTICE_AMBIG,       CMD_NOTICE_NOSUCH,
        CMD_NOTICE_NOSELF,      CMD_NOTICE_NOTIGN
};


// CMD_JOIN tlcwrk structure

struct CTlcJoinInf {
    CHAR m_strName[CHAN_MAX_SIZE];
};

// CMD_LIST tlcwrk structure

struct CTlcListInf {
    CHAR m_strName[CHAN_MAX_SIZE];
    CHAR m_strTopic[CHAN_MAX_TOPIC_SIZE];
    INT m_iUsers;
};

// CMD_SCAN tlcwrk structure

struct CTlcScanInf {
    CHAR m_strUserid[TLCUIDSIZ];
    CHAR m_strChan[CHAN_MAX_SIZE];
    SHORT m_fFlags;
};

// CMD_WHISPER tlcwrk structure
struct CTlcWhisInf {
    CHAR m_strName[TLCUIDSIZ];
};

// CMD_ACTION tlcwrk structure
struct CTlcActInf {
    CHAR m_listname[LISTSIZ];
    CHAR m_act[ACTSIZ];
};

#endif // __TLCDCMD_H



