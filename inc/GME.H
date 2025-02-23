/***************************************************************************
 *                                                                         *
 *   GME.H                                                                 *
 *                                                                         *
 *   Copyright (c) 1994-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   This is the Galacticomm Messaging Engine's public variables,          *
 *   functions, etc.                                                       *
 *                                                                         *
 *                                            - J. Alvrus   6/5/94         *
 *                                                                         *
 ***************************************************************************/

#ifndef __GME_H
#define __GME_H

#include "majorbbs.h"
#include "gcomm.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT
#   ifdef __BUILDGME
#       define GMEEXP           EXPORT
#	    define GMEEXPV(x)       EXPORT_VARIABLE(x)
#		define GMEEXPF(x, y)    EXPORT_FUNCTION(x, y)
#    else
#       define GMEEXP           IMPORT
#       define GMEEXPV(x)       IMPORT_VARIABLE(x)
#       define GMEEXPF(x, y)    IMPORT_FUNCTION(x, y)
#	 endif
#else
#       define GMEEXP
#       define GMEEXPV
#       define GMEEXPF
#endif // GCWINNT


#ifdef GCDOS
#define GMEWRKSZ 518               /* memory required for GME work area    */
#else
#define GMEWRKSZ 1536              /* memory required for GME work area    */
#endif // GCDOS
#define FORNSZ   16                /* forum name size                      */
#define MAXADR   256               /* message address size                 */
#define TPCSIZ   51                /* message (and forum) topic size       */
#define HSTSIZ   57                /* message history size                 */
#define MAXSKWD  80                /* size of scan keyword string          */
#define MAXNQSF  2400              /* max # forums in a user's quickscan   */
#define MAXQSR   qsrlen(MAXNQSF)   /* max size of a user's quickscan record*/
#define MAXGRPF  1000              /* maximum # forums in a group          */
#define DLNMSZ   10                /* sysop dist list name size            */
#define MINLCH   0                 /* minimum sysop dist list surcharge    */
#define MAXLCH   32000             /* maximum sysop dist list surcharge    */
#define MAXBLK   65530U            /* largest allocable memory block       */
#define BIGBLK   256               /* # items to alloc in an array @ once  */
#define SMLBLK   16                /* # items to alloc in small array      */

#define MAXPARSZ (MAXBLK/sizeof(VOID *)) /* max # ptrs in a pointer array  */

#define MAXGMERQ 65535L            /* max # simultaneous GME requests      */
#define MAXBTV   5                 /* max # btrieve acquires per cycle     */
#define EMLID    0U                /* E-mail destination ID                */
#define ROOTGRP  0U                /* root group ID                        */
#define FIRSTM   0L                /* "first message" code, for searches   */
#define LASTM    0x7FFFFFFFL       /* "last message" code, for searches    */
#define FORIDC   '/'               /* E-mail directed to a forum prefix    */
#define NOIDX    -1                /* valid index not found return value   */
#define ALLINF    "** ALL **"      /* "to all in forum" string             */

struct GMEEXP qscfg {                     /* quickscan/config per-user data       */
     CHAR userid[UIDSIZ];          /*   master key for lookups             */
     CHAR fwdee[MAXADR];           /*   auto-forwardee for E-mail (if any) */
     USHORT fwdate;                /*   date that forwardee was chosen     */
     CHAR kwds[MAXSKWD];           /*   quickscan keywords                 */
     USHORT curfor;                /*   current forum ID                   */
     SHORT nforums;                /*   number of forums in quickscan      */
     SHORT flags;                  /*   preference and quickscan flags     */
     LONG stmsg;                   /*   quickscan starting message ID      */
#ifdef GCV2
     CHAR spare[26];               /*   former spare space                 */
#endif
     CHAR accmsg[1];               /*   start of variable-len accmsg stuff */
};                                 /*   2 arrays: forumID+msgID, acclvl    */
                                   /*   msgID > 0 == "real" quickscan forum*/

                                   /* preference-related flag definitions  */
#define CLARPL  0x0001             /*   clear messages after replied to?   */
#define P4NEWM  0x0002             /*   pause at logon for new mail?       */
#define GORTIN  0x0004             /*   if pause, go right into E-mail?    */
#define FORUM2  0x0008             /*   consider forum mail E-mail "to"?   */
#define MSGQUO  0x0010             /*   use message quoting at all?        */
#define ALWQUO  0x0020             /*   always use message message quoting?*/
#define USRSET  0x0040             /*   user has set preferences           */
#define QWKATT  0x0080             /*   include attachments in QWK-Mail?   */
#define CMBHDR  0x0100             /*   combine header and body of messages*/
#define NEWMSG  0x0200             /*   new messages only in quickscan?    */
#define WATONL  0x0400             /*   msgs w/atts only in quickscan?     */
#define TOMEONL 0x0800             /*   msgs to me only in quickscan?      */
#define FRMEONL 0x1000             /*   msgs from me only in quickscan?    */
#define CFWCMT  0x2000             /*   comment when copy/fwding at all?   */
#define ALWCMT  0x4000             /*   always comment when copy/fwding    */

GMEEXPV(INT qssiz);           /* size of in-memory quickscan          */
GMEEXPV(INT _maxqsf);         /* use MAXQSF, not this                 */
#define MAXQSF _maxqsf             /* max forums in a user's quickscan     */

typedef ULONG GMEUSERHANDLE;       /* handle for referencing user data     */

                                   /* message reading sequence codes       */
#define ESQTOU 1                   /*   E-mail to user sequence            */
#define ESQFRU 2                   /*   E-mail from user sequence          */
#define ESQTHR 3                   /*   E-mail thread sequence             */
#define FSQFOR 4                   /*   Forum normal sequence              */
#define FSQTHR 5                   /*   Forum thread sequence              */
#define FSQSCN 6                   /*   Forum one-time scan sequence       */

                                   /* message read direction codes         */
#define RDLEGT 0                   /*   get near, less/equal then greater  */
#define RDLTGE 1                   /*   get near, less then greater/equal  */
#define RDGELT 2                   /*   get near, greater/equal then less  */
#define RDGTLE 3                   /*   get near, greater then less/equal  */
#define RDNEXT 4                   /*   get next message                   */
#define RDPREV 5                   /*   get previous message               */
#define RDEXCT 6                   /*   get exact message number           */

                                   /* old read near message "style" codes  */
#define LEGT RDLEGT                /*   try less/equal then greater        */
#define LTGE RDLTGE                /*   try less then greater/equal        */
#define GELT RDGELT                /*   try greater/equal then less        */
#define GTLE RDGTLE                /*   try greater then less/equal        */

struct otscan {                    /* one-time scan setup structure        */
     CHAR keywds[MAXSKWD];         /*   keywords                           */
     LONG stmsgid;                 /*   starting message ID (0 for none)   */
     CHAR flags;                   /*   search flags                       */
     SHORT nforums;                /*   number of forums in list           */
     USHORT forlst[1];             /*   list of forums to scan             */
};

                                   /* one-time scan flags                  */
#define SCNEW  0x01                /*   include "new" messages only        */
#define SCATT  0x02                /*   include msgs w/attachments only    */
#define SCTOU  0x04                /*   include msgs to user only          */
#define SCFRU  0x08                /*   include msgs from user only        */
#define SCALL  0x10                /*   include all Forums not in list     */

struct globid {                    /* global message identifier            */
     LONG sysid;                   /*   system ID of originating system    */
     LONG msgid;                   /*   message ID on originating system   */
};

struct message {                   /* in-memory message structure          */
#ifdef GCV2
     USHORT forum;                 /*   ID of forum message belongs to     */
#endif // GCV2
     LONG msgid;                   /*   unique message identifier          */
#ifdef GCV2
     struct globid gmid;           /*   unique global message identifier   */
     LONG thrid;                   /*   ID of thread message is part of    */
#else
     LONG thrid;                   /*   ID of thread message is part of    */
     struct globid gmid;           /*   unique global message identifier   */
     USHORT forum;                 /*   ID of forum message belongs to     */
#endif // GCV2
     CHAR from[MAXADR];            /*   originator                         */
     CHAR to[MAXADR];              /*   recipient                          */
     CHAR topic[TPCSIZ];           /*   main topic, editable, carried over */
     CHAR history[HSTSIZ];         /*   history/routing (reply to #88888,  */
                                   /*     fw by Aaaaaaaaa, cc: of #99999)  */
     CHAR attname[GCMAXFNM];       /*   attached file name                 */
     USHORT crdate;                /*   message creation date              */
     USHORT crtime;                /*   message creation time of day       */
     struct globid rplto;          /*   message that this is a reply to    */
     SHORT nrpl;                   /*   number of times replied to         */
     LONG flags;                   /*   message/attachment flag bits       */
};

                                   /* message flag bits                    */
#define NONSYSF 0x0000FFFFL        /*   non-system flag bits               */
#define SYSFLGS 0xFFFF0000L        /*   system-only flag bits              */
#define PRIMSG  0x00000001L        /*   message is "priority"              */
#define EXEMPT  0x00000002L        /*   message is exempt from auto-delete */
#define RECREQ  0x00000010L        /*   return-receipt requested when read */
#define FILIND  0x00000020L        /*   "indirect" att, direct has filespec*/
#define FILATT  0x00000040L        /*   file is attached to this message   */
#define FILAPV  0x00000080L        /*   file attached is ok to download    */
#define NODEL   0x00000100L        /*   sender can't delete                */
#define NOMOD   0x00000200L        /*   sender can't modify                */
#define GMFERR  0x00000400L        /*   message is an error-notification   */
#define ISMPTR  0x00010000L        /*   message header points to other msg */
#define ISTCPY  0x00020000L        /*   message is complete alias of other */
#define FRCLR   0x00040000L        /*   from field of message "cleared"    */
#define TOCLR   0x00080000L        /*   to field of message "cleared"      */

GMEEXPV(UINT _txtlen);        /* use TXTLEN, not this                 */
#define TXTLEN _txtlen             /* message text buffer size             */

struct fordef {                    /* in-memory forum definition struct    */
     USHORT forum;                 /*   unique forum identifier            */
     CHAR name[FORNSZ];            /*   forum name                         */
     CHAR topic[TPCSIZ];           /*   short description/topic            */
     CHAR forop[UIDSIZ];           /*   User-ID of Forum-Op                */
     INT dfnum;                    /*   index of forum's data file in array*/
     CHAR *attpath;                /*   path where attachments are stored  */
     USHORT nthrs;                 /*   number of threads in forum         */
     USHORT nmsgs;                 /*   number of messages in forum        */
     USHORT nfiles;                /*   number of files in forum           */
     USHORT nw4app;                /*   number of files waiting for apprvl */
     CHAR forlok[KEYSIZ];          /*   key required for privileged access */
     CHAR dfnpv;                   /*   default non-priv access setting    */
     CHAR dfprv;                   /*   default priviledged access setting */
     CHAR mxnpv;                   /*   maximum non-priv access setting    */
     SHORT msglif;                 /*   message lifetime (days)            */
     SHORT chgmsg;                 /*   charge per message posted          */
     SHORT chgrdm;                 /*   charge per message read            */
     SHORT chgatt;                 /*   charge per file attachment uploaded*/
     SHORT chgadl;                 /*   charge per file attachment download*/
     SHORT chgupk;                 /*   charge per-kbyte for upload        */
     SHORT chgdpk;                 /*   charge per-kbyte for download      */
     SHORT ccr;                    /*   credit consumption rate            */
     CHAR pfnlvl;                  /*   profanity suppression level        */
     USHORT crdate;                /*   forum creation date                */
     USHORT crtime;                /*   forum creation time of day         */
     USHORT seqid;                 /*   number of forum in list of forums  */
     SHORT necho;                  /*   number of echo addresses           */
     CHAR *echoes;                 /*   pointer to echo address array      */
};

struct fordsk {                    /* on-disk forum definition structure   */
     USHORT forum;                 /*   unique forum identifier            */
     CHAR name[FORNSZ];            /*   forum name                         */
     CHAR topic[TPCSIZ];           /*   short description/topic            */
     CHAR forop[UIDSIZ];           /*   forum-op                           */
     CHAR datfil[GCSTRPTH];        /*   path+file name of forum data file  */
#ifdef GCV2
     CHAR attpath[MAXDIR];         /*   path where attachments are stored  */
#else
     CHAR attpath[GCSTRPTH];       /*   path where attachments are stored  */
#endif // GCV2
     USHORT nthrs;                 /*   number of threads in forum         */
     USHORT nmsgs;                 /*   number of messages in forum        */
     USHORT nfiles;                /*   number of files in forum           */
     USHORT nw4app;                /*   number of files waiting for apprvl */
     CHAR forlok[KEYSIZ];          /*   key required for privileged access */
     SHORT dfnpv;                  /*   default non-privileged access      */
     SHORT dfprv;                  /*   default privileged access setting  */
     SHORT mxnpv;                  /*   maximum non-privileged access      */
     SHORT msglif;                 /*   message lifetime (days)            */
     SHORT chgmsg;                 /*   charge per message posted          */
     SHORT chgrdm;                 /*   charge per message read            */
     SHORT chgatt;                 /*   charge per file attachment uploaded*/
     SHORT chgadl;                 /*   charge per file attachment download*/
     SHORT chgupk;                 /*   charge per-kbyte for upload        */
     SHORT chgdpk;                 /*   charge per-kbyte for download      */
     SHORT ccr;                    /*   credit consumption rate            */
     SHORT pfnlvl;                 /*   profanity suppression level        */
     USHORT crdate;                /*   forum creation date                */
     USHORT crtime;                /*   forum creation time of day         */
     SHORT  necho;                 /*   number of echo addresses           */
     USHORT seqid;                 /*   number of forum in list of forums  */
#ifdef GCV2
     char spare[8];                /*   former spare space                 */
#endif // GCV2
     CHAR info[1];                 /*   variable-length forum info         */
                                   /*   echo addresses (if any)            */
                                   /*   description/help message           */
};

struct foracc {                    /* forum access info structure          */
     SHORT dfnpv;                  /*   default non-privileged access      */
     SHORT dfprv;                  /*   default privileged access setting  */
     SHORT mxnpv;                  /*   maximum non-privileged access      */
     CHAR forlok[KEYSIZ];          /*   key required for privileged access */
};

                                   /* forum access codes                   */
#define NOAXES 0                   /*   no access                          */
#define RDAXES 2                   /*   read access                        */
#define DLAXES 4                   /*   download access                    */
#define WRAXES 6                   /*   write access                       */
#define ULAXES 8                   /*   upload access                      */
#define COAXES 10                  /*   Co-Op access                       */
#define OPAXES 12                  /*   (ret from foracc() when Forum-Op)  */
#define SYAXES 14                  /*   (ret from foracc() when Sysop)     */
#define NOTSET 15                  /*   not set yet (use default)          */
#define DFTPFN 4                   /* use pfceil for profanity check       */

                                   /* max variable part of forum definition*/
#define MAXFDV (16384-fldoff(fordsk,info))

#define MAXFDESC MAXFDV            /* max forum description length         */
#define MAXECHO (MAXFDV/MAXADR)    /* max number of echoes/forum           */

typedef CHAR adr_t[MAXADR];        /* for accessing echo address array     */

struct fmidky {                    /* forumID/msgID composite structure    */
     USHORT forum;
     LONG msgid;
};

struct forgrp {                    /* forum group record structure         */
     USHORT grpid;                 /*   group ID                           */
     USHORT parid;                 /*   group ID of this group's parent    */
     CHAR name[FORNSZ];            /*   group name                         */
     CHAR topic[TPCSIZ];           /*   group topic                        */
     CHAR key[KEYSIZ];             /*   key required to use this group     */
     SHORT flags;                  /*   group flags                        */
     SHORT nforums;                /*   number of forums in group          */
     USHORT forarr[1];             /*   list of forum IDs in group         */
};
#define grprlen(n) (fldoff(forgrp,forarr)+(n)*sizeof(USHORT))
                                   /* macro to compute group info rec len  */

#define MAXQIK 40                  /* max entries in a !QUICK list         */
struct qikdat {                    /* !QUICK list records structure        */
     CHAR userid[UIDSIZ];          /*   key value for look-up              */
     SHORT idx[MAXQIK];            /*   array of entry indexes             */
     CHAR list[1];                 /*   variable-length entry data         */
};
#define MAXQKR (fldoff(qikdat,list)+MAXQIK*MAXADR) /* max !QUICK rec len   */

#define PFXSIZ 4                   /* max exporter prefix size             */
#define EXPNSZ 16                  /* max exporter name size               */
#define EXPDSZ 51                  /* max exporter description size        */

struct exporter {                  /* message exporter control block       */
     CHAR prefix[PFXSIZ];          /*   address prefix for this exporter   */
     CHAR name[EXPNSZ];            /*   name of exporter (e.g., "Internet")*/
     CHAR desc[EXPDSZ];            /*   description of exporter            */
     CHAR exmp[MAXADR];            /*   example address to this exporter   */
     CHAR wrtkey[KEYSIZ];          /*   key required to use this exporter  */
     SHORT wrtchg;                 /*   per-message surcharge              */
     CHAR attkey[KEYSIZ];          /*   key required for file attachments  */
     SHORT attchg;                 /*   attachment surcharge               */
     SHORT apkchg;                 /*   attachment per-kbyte surcharge     */
     CHAR rrrkey[KEYSIZ];          /*   key required to request return recp*/
     SHORT rrrchg;                 /*   return receipt request surcharge   */
     CHAR prikey[KEYSIZ];          /*   key required to send priority msg  */
     SHORT prichg;                 /*   priority surcharge                 */
     SHORT flags;                  /*   supported features flags           */

     const CHAR *                  /*     returns internal buffer          */
     (*helpmsg)(VOID);             /*   get help message for this exporter */

     GBOOL                         /*     return TRUE if valid             */
     (*valadr)(                    /*   is this a valid address vector     */
     const CHAR *addr);            /*     address to check                 */

     const CHAR *                  /*     returns internal buffer          */
     (*attspc)(                    /*   get path+file name for attachment  */
     const CHAR *to,               /*     to address of message            */
     const struct message *msg);   /*     message header                   */

     INT                           /*     return GME status code           */
     (*sndmsg)(                    /*   send message vector                */
     const CHAR *to,               /*     address to send to               */
     const struct message *msg,    /*     message header                   */
     const CHAR *text,             /*     message text                     */
     const CHAR *filatt);          /*     attachment path+file name        */
};

struct expinfo {                   /* info about exporter for interface    */
     CHAR prefix[PFXSIZ];          /*   address prefix for this exporter   */
     CHAR name[EXPNSZ];            /*   name of exporter (e.g., "Internet")*/
     CHAR desc[EXPDSZ];            /*   description of exporter            */
     CHAR exmp[MAXADR];            /*   example address to this exporter   */
     CHAR wrtkey[KEYSIZ];          /*   key required to use this exporter  */
     SHORT wrtchg;                 /*   per-message surcharge              */
     CHAR attkey[KEYSIZ];          /*   key required for file attachments  */
     SHORT attchg;                 /*   attachment surcharge               */
     SHORT apkchg;                 /*   attachment per-kbyte surcharge     */
     CHAR rrrkey[KEYSIZ];          /*   key required to request return recp*/
     SHORT rrrchg;                 /*   return receipt request surcharge   */
     CHAR prikey[KEYSIZ];          /*   key required to send priority msg  */
     SHORT prichg;                 /*   priority surcharge                 */
     SHORT flags;                  /*   supported features flags           */
};

                                   /* exporter flags                       */
#define EXPATT   0x0001            /*   support attachments?               */
#define EXPRRR   0x0002            /*   support return receipts?           */
#define EXPPRI   0x0004            /*   support priority msgs?             */
#define EXPFMT   0x0008            /*   support formatted text?            */

                                   /* GME request status codes             */
#define GMEAGAIN 0                 /*   GME still processing request       */
#define GMEOK    1                 /*   generic "finished OK" status       */
#define GMEAFWD  2                 /*   message was auto-forwarded         */
#define GMERRG   3                 /*   return receipt generated           */
#define GMEERR  -1                 /*   generic "error" status             */
#define GMEDUP  -2                 /*   unique name or ID exists           */
#define GME2MFR -3                 /*   too many forums error              */
#define GMENFID -4                 /*   no available forum IDs error       */
#define GMENFND -5                 /*   generic "not found" error          */
#define GMENDEL -6                 /*   generic "can't delete" error       */
#define GMENMOD -7                 /*   generic "can't modify" error       */
#define GMEFDV  -8                 /*   variable part of forum def too long*/
#define GMECRD  -9                 /*   not enough credits for operation   */
#define GMEMEM  -10                /*   not enough memory for operation    */
#define GMEIVA  -11                /*   invalid attachment to message      */
#define GMENOAT -12                /*   unable to attach file to message   */
#define GMEACC  -13                /*   user doesn't have access           */
#define GMENRGM -14                /*   couldn't re-get message            */
#define GMENCFL -15                /*   can't copy/fwd to a dist list      */
#define GMERST  -16                /*   E-mail message pointer reset       */
#define GMEUSE  -17                /*   message in use, can't modify or del*/
#define GMENAPV -18                /*   attachment not approved for dnload */
#define GME2MFL -19                /*   too many forum data files error    */
#define GMENSRC -20                /*   source not found                   */
#define GMENDST -21                /*   destination not found              */

                                   /* feature validation codes             */
#define VALYES   1                 /*   feature is available               */
#define VALNO   -1                 /*   feature is not available           */
#define VALACC  -2                 /*   user doesn't have access           */
#define VALCRD  -3                 /*   user doesn't have enough credits   */

                                   /* setgmecb() callback event codes      */
#define EVTSTRT  0                 /*   starting to send a message         */
#define EVTDONE  1                 /*   done sending a message             */
#define EVTCCST  2                 /*   starting to send carbon copies     */
#define EVTDSTS  3                 /*   starting distribution              */
#define EVTDSTD  4                 /*   done with distribution             */
#define EVTCPYS  5                 /*   starting to copy a file            */
#define EVTCPYD  6                 /*   done copying a file                */
#define EVTNEWF  7                 /*   starting to scan a new forum       */
#define EVTNEWM  8                 /*   starting to scan a new message     */

                                   /* hook_gme() hook type codes           */
#define GMEHOOK_NONE        0      /*   no hook set (internal use only)    */
#define GMEHOOK_NOT_NEWMSG  1      /*   notification of new messages       */
#define GMEHOOK_NOT_NEWMSGL 2      /*   low-level new message notification */
#define GMEHOOK_NOT_NEWFOR  3      /*   notification of forum creation     */
#define GMEHOOK_NOT_UPDMSG  4      /*   notification of message update     */
#define GMEHOOK_NOT_UPDFOR  5      /*   notification of forum update       */
#define GMEHOOK_NOT_DELMSG  6      /*   notification of message deleted    */
#define GMEHOOK_NOT_DELMSGL 7      /*   low-level msg deleted notification */
#define GMEHOOK_NOT_DELFOR  8      /*   notification of forum deleted      */
#define GMEHOOK_NOT_DELFORL 9      /*   low-level forum delete notification*/
#define GMEHOOK_NOT_NEWGRP  10     /*   group created notification         */
#define GMEHOOK_NOT_UPDGRP  11     /*   group modified notification        */
#define GMEHOOK_NOT_DELGRP  12     /*   notification of group deleted      */
#define GMEHOOK_NOT_DELGRPL 13     /*   low-level group delete notification*/
#define GMEHOOK_NOT_INIUSR  14     /*   user-initialized notification      */
#define GMEHOOK_NOT_CLSUSR  15     /*   user-closed notification           */
#define GMEHOOK_NOT_INIUSRL 16     /*   low-lvl user-init notification     */
#define GMEHOOK_NOT_CLSUSRL 17     /*   low-lvl user-closed notification   */
#ifdef DEBUG
#define GMEHOOK_MAX 17             /*   largest hook type code             */
#endif

                                   /* prioritized hook codes (hook_gme_p)  */
#define GMEHOOK_PRIBASE     10000  /*   prioritized hook base code         */
#define GMEHOOK_HDL_AUTOFWD 10001  /*   auto-forward handler               */
#if defined(DEBUG)
#define GMEHOOK_PRIMAX      10001  /*   largest prioritized hook code      */
#endif

                                   /* standard hook priority codes         */
#define GMEHOOKPRI_HIGHEST  0      /*   highest possible priority          */
#define GMEHOOKPRI_HIGH     64     /*   high priority                      */
#define GMEHOOKPRI_NORMAL   128    /*   normal priority                    */
#define GMEHOOKPRI_LOW      192    /*   low priority                       */
#define GMEHOOKPRI_LOWEST   255    /*   lowest possible priority           */

                                   /* new message type codes               */
#define NEWMSG_WRITE 0             /*   new message written                */
#define NEWMSG_REPLY 1             /*   reply written                      */
#define NEWMSG_IMPRT 2             /*   message imported                   */
#define NEWMSG_DISTR 3             /*   message written as part of dist.   */
#define NEWMSG_CCOPY 4             /*   message carbon copied              */
#define NEWMSG_COPY  5             /*   message copied                     */
#define NEWMSG_FORWD 6             /*   message forwarded                  */
#define NEWMSG_RTRCP 7             /*   return receipt generated           */

                                   /* message update type codes            */
#define UPDMSG_MODFY 0             /*   message modified                   */
#define UPDMSG_REPLY 1             /*   message replied to                 */
#define UPDMSG_APINF 2             /*   app-defined info modified          */
#define UPDMSG_EXMT  3             /*   message exempted                   */
#define UPDMSG_APRV  4             /*   message attachment approved        */

                                   /* message deletion type codes          */
#define DELMSG_NORM  0             /*   normal deletion of message         */
#define DELMSG_FORWD 1             /*   message forwarded                  */
#define DELMSG_CLNUP 2             /*   message deleted during cleanup     */

/* function typedefs */

typedef
VOID (*voidfunc)(VOID);            /* generic function pointer             */

typedef
GBOOL                              /*   returns TRUE if there is a conflict*/
(*cflfunc)(                        /* check-for-conflict function          */
VOID *pWork,                       /*   work area being used for operation */
USHORT forum,                      /*   forum ID with conflict             */
LONG msgid);                       /*   message ID with conflict           */

typedef
VOID
(*gmehook_not_newmsg)(             /* new message hook                     */
INT newtype,                       /*   how new message was generated code */
const struct message *msg,         /*   new message header                 */
const CHAR *text);                 /*   new message text                   */

typedef
VOID
(*gmehook_not_newmsgl)(            /* low-level new message hook           */
const struct message *msg,         /*   new message header                 */
const CHAR *TEXT);                 /*   new message text                   */

typedef
VOID
(*gmehook_not_newfor)(             /* forum has been created hook          */
const struct fordsk *newdef,       /*   new forum definition structure     */
const CHAR *desc,                  /*   descriptive text                   */
const CHAR *echoes);               /*   pointer to array of echo addresses */

typedef
VOID
(*gmehook_not_grpchg)(             /* group information changed hook       */
const struct forgrp *grpbuf);      /*   new forum group structure          */
                                   /* used for new, modify, and delete ntfy*/

typedef
VOID
(*gmehook_not_updmsg)(             /* message update hook                  */
INT updtype,                       /*   how message was updated code       */
const struct message *msg,         /*   message header                     */
const CHAR *text);                 /*   message text                       */

typedef
VOID
(*gmehook_not_updfor)(             /* forum has been updated hook          */
const struct fordef *newdef,       /*   forum definition structure         */
const CHAR *desc,                  /*   descriptive text                   */
const CHAR *echoes);               /*   pointer to array of echo addresses */
                                   /*(desc & echoes may be NULL if no chng)*/
typedef
VOID
(*gmehook_not_delmsg)(             /* message has been deleted hook        */
INT deltype,                       /*   how new message was deleted code   */
const struct message *msg,         /*   new message header                 */
const CHAR *text);                 /*   new message text                   */

typedef
VOID
(*gmehook_not_delmsgl)(            /* low-level message deleted hook       */
USHORT forum,                      /*   forum ID message deleted from      */
LONG msgid);                       /*   message ID of deleted message      */

typedef
VOID
(*gmehook_not_delfor)(             /* forum has been deleted hook          */
const struct fordsk *def,          /*   forum definition structure         */
const CHAR *desc,                  /*   descriptive text                   */
const CHAR *echoes);               /*   pointer to array of echo addresses */

typedef
VOID
(*gmehook_not_delforl)(            /* low-level forum deleted hook         */
USHORT forum);                     /*   forum ID of deleted forum          */

typedef
VOID
(*gmehook_not_delgrpl)(            /* low-level group deleted hook         */
USHORT grpid);                     /*   group ID of deleted group          */

typedef
VOID
(*gmehook_not_iniclsu)(            /* init/close user hook function type   */
const CHAR *userid);               /*   User-ID being initialized          */

typedef
INT                                /*   TRUE=handled, don't call others    */
(*gmehook_hdl_autofwd)(            /* autoforward handler function type    */
CHAR * fwdee,                      /*   buf containing proposed forwardee  */
struct message const * pMsg);      /*   message being sent                 */

                                   /* forum CNF options                    */
GMEEXPV(SHORT forccr);        /* def forum credit consumption rate    */
GMEEXPV(SHORT forlif);        /* def lifetime of a forum message(days)*/
GMEEXPV(SHORT fmschg);        /* def credit charge to write forum msg */
GMEEXPV(SHORT fmrchg);        /* def credit charge to read forum msg  */
GMEEXPV(SHORT fulchg);        /* def credit charge per file upload    */
GMEEXPV(SHORT fkuchg);        /* def per-kbyte charge per file upload */
GMEEXPV(SHORT fdlchg);        /* def credit charge per file download  */
GMEEXPV(SHORT fkdchg);        /* def per-kbyte charge per file dnld   */

GMEEXPV(GBOOL fopmfd);        /* allow forum-ops to modify forum defs?*/
GMEEXPV(GBOOL fdnaud);        /* audit trail entry for each forum dnld?*/
GMEEXPV(GBOOL fupaud);        /* audit trail entry for each forum upld?*/

GMEEXPV(CHAR * forsys);       /* Sysop privileged forum usage key     */
GMEEXPV(CHAR * forprv);       /* privileged forum usage key           */

GMEEXPV(USHORT dftfor);       /* default forum ID                     */

                                   /* E-mail CNF options                   */
GMEEXPV(GBOOL e2urrr);        /* ret. rec. on new-user E-Mail if enabled*/

GMEEXPV(SHORT emllif);        /* lifetime of an E-Mail message, in days*/
GMEEXPV(SHORT emschg);        /* credit charge per E-Mail msg written */
GMEEXPV(SHORT eatchg);        /* additional charge for attachment     */
GMEEXPV(SHORT epkchg);        /* additional per-kbyte charge/attachment*/
GMEEXPV(SHORT rrrchg);        /* additional charge for return receipt */
GMEEXPV(SHORT prichg);        /* additional charge for priority message*/
GMEEXPV(SHORT lstchg);        /* cred charge for using distribution list*/
GMEEXPV(SHORT emrchg);        /* credit charge per E-Mail msg read    */
GMEEXPV(SHORT edachg);        /* charge for attachment download       */
GMEEXPV(SHORT edkchg);        /* per-kbyte charge for attachment download*/
GMEEXPV(SHORT dfpref);        /* default user preferences             */

GMEEXPV(GBOOL alweat);        /* allow E-mail file attachments?       */
GMEEXPV(GBOOL alwrrr);        /* allow E-mail return receipts?        */
GMEEXPV(GBOOL alwpri);        /* allow priority E-Mail messages?      */
GMEEXPV(GBOOL chgfwd);        /* charge recip. for auto-forward charges*/
GMEEXPV(GBOOL ednaud);        /* audit trail entry for each E-mail dnld?*/
GMEEXPV(GBOOL eupaud);        /* audit trail entry for each E-mail upld?*/

GMEEXPV(CHAR * emlkey);       /* key required to write E-mail         */
GMEEXPV(CHAR * eatkey);       /* key required to upl. E-Mail attachments*/
GMEEXPV(CHAR * rrrkey);       /* key required to request return receipts*/
GMEEXPV(CHAR * prikey);       /* key required to send priority messages*/
GMEEXPV(CHAR * qikkey);       /* key required to use !QUICK list      */
GMEEXPV(CHAR * massky);       /* key required to use !MASS list       */
GMEEXPV(CHAR * edstky);       /* key required to edit sysop-defined lists*/

/* special function hooks */
GMEEXPF(GBOOL,                  /*   return TRUE if handled             */
    hdlimphook)(                /* redirect imported message hook       */
struct message *msg,            /*   message header                     */
const CHAR *text,               /*   message text                       */
const CHAR *filatt);            /*   attachment path+file name          */

GMEEXPF(VOID,
    newmsghook)(                   /* new message notification hook        */
const CHAR *msgtyp,                /*   type of message                    */
const struct message *msg,         /*   message header                     */
const CHAR *fwdee);                /*   forwardee (if autoforwarded)       */

                                   /* notification type strings            */
#define WRITENOT "WRITE"           /*   new message written                */
#define REPLYNOT "REPLY"           /*   reply written                      */
#define IMPRTNOT "IMPORT"          /*   message imported                   */
#define DISTRNOT "DISTRIBUTE"      /*   message written as part of dist.   */
#define CCOPYNOT "CARBON COPY"     /*   message carbon copied              */
#define MCOPYNOT "COPY"            /*   message copied                     */
#define FORWDNOT "FORWARD"         /*   message forwarded                  */
#define RTRCPNOT "RETURN RECEIPT"  /*   return receipt generated           */

/* function-like macros                 */
#define isforum(s) (*(s) == FORIDC)
#define isdlst(s) (*(s) == '!' || *(s) == '@')
#define inqs(qsc,fid) (qsidx((qsc),(fid)) != NOIDX)
#define qsrlen(n) (fldoff(qscfg,accmsg)                                    \
                  +sizeof(struct fmidky)*(n)+sizeof(CHAR)*((n)+1)/2)
#define qsonsys(uid) (onsqsp(uid) != NULL)
#define noatt(msg) ((msg)->flags&=~(FILATT|FILAPV|FILIND))
#define fidxst(fid) ((fid) != EMLID && fididx(fid) != NOIDX)
#define fnmxst(name) (fnmidx(name) != NOIDX)
#define fidok(fid) ((fid) == EMLID || fididx(fid) != NOIDX)
#define forAdrXst(foradr) (getAdrForID(foradr) != EMLID)
#define alcpar(p,n,b) alcarr((VOID **)(p),sizeof(VOID *),(n),(b))/* ptr arr*/
#define alciar(p,n,b) alcarr((VOID **)(p),sizeof(INT),(n),(b))/* int array */

#define readmsgf(wrk,msg,txt) frdmsg((wrk),RDEXCT,(msg),(txt))
#define nextmsgf(wrk,msg,txt) frdmsg((wrk),RDNEXT,(msg),(txt))
#define prevmsgf(wrk,msg,txt) frdmsg((wrk),RDPREV,(msg),(txt))
#define nearmsgf frdmsg
#define nextseqf(wrk,seq,msg,txt) frdseq((wrk),RDNEXT,(seq),(msg),(txt))
#define prevseqf(wrk,seq,msg,txt) frdseq((wrk),RDPREV,(seq),(msg),(txt))

/* general utility functions            */

GMEEXP VOID
init__galme(VOID);                 /* GME initialization function          */

GMEEXP UINT                        /*   returns max message text length    */
txtlen(VOID);                      /* init__ callable get-text-length      */

GMEEXP INT                         /*   returns max # forums allowed in qs */
maxqsf(VOID);                      /* init__ callable get-max-qscan-forums */

GMEEXP GBOOL                       /*   returns TRUE if hook set           */
hook_gme(                          /* set a GME function hook              */
INT hooktype,                      /*   type of hook to set                */
voidfunc hookfunc);                /*   hook function pointer              */

GMEEXP GBOOL                       /*   returns TRUE if hook set           */
hook_gme_p(                        /* set a prioritized GME function hook  */
INT hooktype,                      /*   type of hook to set                */
voidfunc hookfunc,                 /*   hook function pointer              */
INT priority);                     /*   priority (0=highest, 255=lowest)   */

GMEEXP INT                         /*   returns GME status code            */
inigmeu(VOID);                     /* initialize GME/user stuff at logon   */
                                   /*   (must be called by user interface) */

GMEEXP VOID                        /* (must be called by user interface)   */
clsgmeu(VOID);                     /* close GME/user stuff at logoff       */

GMEEXP INT                         /*   returns GME status code            */
gmeUserOpen(                       /* open user in non-channel mode        */
struct usracc* pAcct,              /*   account of user to open            */
GMEUSERHANDLE * phUsr);            /*   buffer to receive user handle      */

GMEEXP INT                         /*   returns GME status code            */
gmeUserReference(                  /* get reference to already-loaded user */
CHAR const * uid,                  /*   User-ID of user to reference       */
GMEUSERHANDLE * phUsr);            /*   buffer to receive user handle      */

GMEEXP struct qscfg *              /*   returns NULL if invalid handle     */
gmeUserGetQS(                      /* get pointer to non-channel quickscan */
GMEUSERHANDLE hUsr);               /*   user handle                        */

GMEEXP VOID
gmeUserClose(                      /* close a non-channel user             */
GMEUSERHANDLE hUsr);               /*   user handle                        */

GMEEXP VOID
inigmerq(                          /* initialize GME request               */
VOID *pWork);                      /*   work area to be used for request   */

GMEEXP VOID
clsgmerq(                          /* close a GME request                  */
VOID *pWork);                      /*   work area being used for request   */

GMEEXP GBOOL
gmerqopn(                          /* is this request open?                */
VOID *pWork);                      /*   pointer to work area               */

GMEEXP VOID
setgmecb(                          /* set handler for GME status reports   */
VOID *pWork,                       /*   work area being used for request   */
VOID (*callback)(INT,INT));        /*   pointer to callback handler        */

GMEEXP const CHAR *
gmexinf(VOID);                     /* get extended return information      */

GMEEXP GBOOL                              /*   returns TRUE if able to add to list*/
setcfl(                            /* set cooperative conflict checker     */
cflfunc cflchk);                   /*   function to check                  */

GMEEXP GBOOL                              /*   returns TRUE if a conflict         */
chkcfl(                            /* chk others for conflict w/my cur msg */
VOID *pWork);                      /*   work area being used to read       */

GMEEXP GBOOL                              /*   returns TRUE if a conflict         */
chkmycfl(                          /* check my current message for conflict*/
VOID *pWork,                       /*   my work area being used to read    */
USHORT forum,                      /*   forum ID w/possible conflict       */
LONG msgid);                       /*   message ID w/possible conflict     */

GMEEXP GBOOL                              /*   returns TRUE if a conflict         */
gencfl(                            /* generic conflict checker             */
VOID *pWork,                       /*   work area in use                   */
USHORT forum,                      /*   forum ID to check                  */
LONG msgid);                       /*   msg ID to check (0L for forum only)*/

GMEEXP LONG
gmeSysID(VOID);                    /* get current GME System-ID            */

GMEEXP LONG
gmeReg2SysID(                      /* get GME System-ID from reg #         */
const CHAR *regno);                /*   system registration number         */

GMEEXP CHAR *                             /*   returns pointer to destination     */
gmeSysID2Reg(                      /* get reg # from GME System-ID         */
LONG sysid,                        /*   GME System-ID to convert           */
CHAR *regno);                      /*   buffer for reg # (size >= 9)       */

GMEEXP const CHAR *
gmeEmlSysUID(VOID);                /* get E-mail Sysop (default) User-ID   */

GMEEXP VOID
setscan(                           /* set the scan context                 */
VOID *pWork,                       /*   for this work space                */
struct otscan *newscn);            /*   to this scan buffer                */

GMEEXP struct otscan *
getscan(                           /* get the current scan context buffer  */
VOID *pWork);                      /*   for this work space                */

GMEEXP VOID
addf2ots(                          /* add forum to scan list in seq order  */
struct otscan *ots,                /*   one-time scan structure to update  */
USHORT forum);                     /*   forum to add                       */

GMEEXP INT                                /*   returns NOIDX if not found         */
scnfidx(                           /* get index of forum in search list    */
const struct otscan *ots,          /*   in this scan                       */
USHORT forum);                     /*   forum ID to find                   */

GMEEXP USHORT                             /*   returns EMLID if no forums         */
fstscnf(                           /* get first forum ID                   */
const CHAR *userid,                /*   User-ID doing scan                 */
const struct otscan *ots);         /*   in this search                     */

GMEEXP LONG
fstscnm(                           /* get first message ID                 */
const CHAR *userid,                /*   User-ID doing scan                 */
const struct otscan *ots,          /*   in this scan                       */
USHORT forum);                     /*   in this forum (in scan)            */

GMEEXP GBOOL
adrxst(                            /* does this address exist              */
const CHAR *adr);                  /*   address to check                   */

GMEEXP GBOOL                              /*   returns TRUE if address exists     */
fixadr(                            /* fix up an address                    */
const CHAR *from,                  /*   User-ID of sender (NULL for any)   */
CHAR *adr);                        /*   address to fix up                  */

GMEEXP GBOOL
islocal(                           /* is this a valid local address        */
const CHAR *adr);                  /*   address to check                   */

GMEEXP INT                                /*   (returns NOIDX if not found)       */
fnmidx(                            /* get index of named forum in def array*/
const CHAR *name);                 /*   forum name                         */

GMEEXP INT                                /*   (returns NOIDX if not found)       */
fididx(                            /* get index of forum ID in def array   */
USHORT fid);                       /*   forum ID                           */

GMEEXP USHORT                             /*   returns EMLID if doesn't exist     */
getfid(                            /* get forum ID                         */
const CHAR *name);                 /*   given forum name                   */

GMEEXP USHORT
getAdrForID(                       /* get forum ID given forum address     */
const CHAR *faddr);                /*   forum-style address                */

GMEEXP const CHAR *                       /*   returns pointer to static buffer   */
extAdrForNam(                      /* extract forum name from address      */
const CHAR *faddr);                /*   forum-style address                */

GMEEXP const CHAR *                       /*   returns NULL if doesn't exist      */
getfnm(                            /* get forum name                       */
USHORT fid);                       /*   given forum ID                     */

GMEEXP const CHAR *                       /*   returns NULL if doesn't exist      */
getftpc(                           /* get forum topic                      */
USHORT fid);                       /*   given forum ID                     */

GMEEXP GBOOL
valfornm(                          /* is this a valid forum name?          */
const CHAR *name);                 /*   name to check                      */

GMEEXP GBOOL                              /*   TRUE if access > NOAXES            */
faccok(                            /* current user has access to Forum?    */
USHORT forum);                     /*   forum ID to get topic for          */

GMEEXP INT                                /*   returns standard GME status codes  */
setaxes(                           /* set access for a user                */
USHORT fid,                        /*   forum to set access for            */
const CHAR *uid,                   /*   user to set access for             */
INT acc);                          /*   access to set to                   */

GMEEXP INT                                /*   returns standard GME status codes  */
cpyaxes(                           /* copy forum access                    */
const CHAR *dstusr,                /*   to this User-ID                    */
const CHAR *srcusr);               /*   from this User-ID                  */

GMEEXP struct qscfg *                     /*   returns NULL if not found          */
onsqsp(                            /* get online user's quickscan          */
const CHAR *uid);                  /*   given User-ID                      */

GMEEXP struct qscfg *
uqsptr(                            /* get online user's quickscan          */
INT unum);                         /*   given user number                  */

GMEEXP struct qscfg *
myqsptr(VOID);                     /* get current user's quickscan         */

GMEEXP VOID
gmeLoadQS(                         /* load a user's quickscan              */
struct qscfg *qsc,                 /*   pointer to quickscan buffer        */
const CHAR *uid);                  /*   User-ID to load                    */

GMEEXP VOID
gmeSaveQS(                         /* save a quickscan                     */
const struct qscfg *qsc);          /*   quickscan to save                  */

GMEEXP VOID
initqs(                            /* initialize a new user's quickscan    */
struct qscfg *qsc,                 /*   pointer to quickscan buffer        */
const CHAR *uid);                  /*   User-ID to initialize              */

GMEEXP GBOOL                              /*   returns FALSE if unable to add     */
sfinqs(                            /* set forum in quickscan               */
struct qscfg *qsc,                 /*   quickscan record                   */
USHORT fid,                        /*   forum to set                       */
GBOOL turnon);                     /*   TRUE = make forum "in" quickscan   */

GMEEXP struct otscan *                    /*   returns copy of pointer to dest    */
qsc2ots(                           /* copy quickscan to a one-time scan buf*/
const struct qscfg *qsc,           /*   quickscan to copy                  */
struct otscan *ots);               /*   one-time scan buffer               */

GMEEXP INT                                /*   index of new entry (NOIDX if error)*/
absadqs(                           /* add forum to qs, del others for room */
struct qscfg *qsc,                 /*   quickscan record                   */
USHORT fid);                       /*   forum ID to add                    */

GMEEXP INT                                /*   index in qs arrays (NOIDX if err)  */
qsidx(                             /* get index of forum in quickscan      */
const struct qscfg *qsc,           /*   quickscan record                   */
USHORT fid);                       /*   forum ID to get                    */

GMEEXP INT                                /*   index in qs arrays (NOIDX if err)  */
add2qs(                            /* add slot for forum to quickscan      */
struct qscfg *qsc,                 /*   quickscan record                   */
USHORT fid);                       /*   forum ID to add                    */

GMEEXP VOID
delqs(                             /* delete an entry from the quickscan   */
struct qscfg *qsc,                 /*   pointer to quickscan               */
USHORT forum);                     /*   forum ID to remove from quickscan  */

GMEEXP GBOOL                              /*   returns TRUE if able to set        */
sethi(                             /* set hi message in quickscan          */
struct qscfg *qsc,                 /*   pointer to quickscan               */
USHORT forum,                      /*   forum ID to set for                */
LONG msgid);                       /*   message ID to set as high message  */

GMEEXP GBOOL                              /*   returns TRUE if able to set        */
setac(                             /* set forum acc in quickscan           */
struct qscfg *qsc,                 /*   pointer to quickscan               */
USHORT forum,                      /*   forum ID to set for                */
INT acc);                          /*   access level to set                */

GMEEXP LONG
gethi(                             /* get hi message in quickscan          */
const struct qscfg *qsc,           /*   pointer to quickscan               */
USHORT forum);                     /*   forum ID to get for                */

GMEEXP VOID
idelqs(                            /* delete an entry from the quickscan   */
struct qscfg *qsc,                 /*   pointer to quickscan               */
INT idx);                          /*   index of entry to delete           */

GMEEXP VOID
isethi(                            /* set hi message in quickscan (w/index)*/
struct qscfg *qsc,                 /*   pointer to quickscan               */
INT idx,                           /*   index of forum to set              */
LONG msgid);                       /*   message ID to set as high message  */

GMEEXP VOID
isetac(                            /* set forum acc in quickscan (w/index) */
struct qscfg *qsc,                 /*   pointer to quickscan               */
INT idx,                           /*   index of forum to set              */
INT acc);                          /*   access level to set                */

GMEEXP USHORT
igetfid(                           /* get forum ID in quickscan (w/index)  */
const struct qscfg *qsc,           /*   pointer to quickscan               */
INT idx);                          /*   index of forum to get              */

GMEEXP LONG
igethi(                            /* get hi message in quickscan (w/index)*/
const struct qscfg *qsc,           /*   pointer to quickscan               */
INT idx);                          /*   index of forum to get              */

GMEEXP INT
igetac(                            /* get forum acc in quickscan (w/index) */
const struct qscfg *qsc,           /*   pointer to quickscan               */
INT idx);                          /*   index of forum to get              */

GMEEXP INT                                /*   returns index or NOIDX if none     */
qsdelf(                            /* get first non-existent forum         */
const struct qscfg *qsc);          /*   pointer to quickscan               */

GMEEXP INT                                /*   returns index or NOIDX if none     */
qsoldm(                            /* get oldest "marker" entry            */
const struct qscfg *qsc);          /*   pointer to quickscan               */

GMEEXP INT                                /*   returns index or NOIDX if none     */
qsoldr(                            /* get oldest "real" entry              */
const struct qscfg *qsc);          /*   pointer to quickscan               */

const GMEEXP CHAR *                /*   returns NULL if none               */
tpcfnm(                            /* extract file name from topic         */
const CHAR *tpc);                  /*   topic string                       */

GMEEXP GBOOL                              /*   was able to allocate?              */
alcarr(                            /* alloc another item in array in blocks*/
VOID **ppar,                       /*   pointer to pointer to array        */
UINT itmsiz,                       /*   size of individual array items     */
UINT nitems,                       /*   # items currently in array         */
UINT blksiz);                      /*   # items in each block              */
                                   /*   (assumes ++nitems after each call) */

GMEEXP CHAR *                             /*   returns pointer to string          */
zpad(                              /* zero pad a string                    */
CHAR *s,                           /*   pointer to string                  */
UINT len);                         /*   length of string buffer            */

GMEEXP CHAR *                             /*   ptr to next entry (NULL if done)   */
parscc(                            /* parse next cc: from list             */
CHAR *addr,                        /*   buffer to put cc: address into     */
const CHAR *list);                 /*   ';'-delimited cc: list             */

GMEEXP GBOOL                              /*   returns TRUE if directory exists   */
fmdir(                             /* find or make directory               */
const CHAR *dirname);              /*   directory name                     */

GMEEXP GBOOL                              /*   returns TRUE if successful         */
makedir(                           /* make nested directories              */
const CHAR *dirname);              /*   directory name(s)                  */

GMEEXP GBOOL                              /*   returns TRUE if directory exists   */
dexist(                            /* check if directory exists            */
const CHAR *dirname);              /*   name of directory (no trailing \)  */

GMEEXP GBOOL                              /*   returns TRUE if file exists        */
fexist(                            /* check if file exists                 */
const CHAR *name);                 /*   path+file name to find             */

GMEEXP GBOOL                              /*   returns TRUE if a valid file name  */
valfnm(                            /* check for valid file name            */
const CHAR *name);                 /*   string to check                    */

GMEEXP CHAR *                             /*   returns pointer to file name       */
tmpanam(                           /* create temp attachment file name     */
CHAR *dest);                       /*   dest. buf or NULL for internal buf */

GMEEXP GBOOL
istmp(                             /* is this a temporary attachment file  */
const CHAR *fname);                /*   path+file name to check            */

GMEEXP GBOOL
dlstxst(                           /* does dist list exist?                */
const CHAR *name);                 /*   complete list name (incl @ or !)   */

GMEEXP INT                                /*   returns standard GME status codes  */
nxtslst(                           /* get name of next sysop dist list     */
CHAR *lstnam,                      /*   buffer for list name               */
CHAR *lstkey,                      /*   buffer for list key                */
SHORT *surchg);                    /*   buffer for list surcharge          */

GMEEXP INT                                /*   returns standard GME status codes  */
getslst(                           /* get info on sysop dist list          */
const CHAR *lstnam,                /*   list name                          */
CHAR *lstkey,                      /*   buffer for list key                */
SHORT *surchg);                    /*   buffer for list surcharge          */

GMEEXP INT                                /*   returns standard GME status codes  */
slstfil(                           /* get info about sysop list            */
const CHAR *lstnam,                /*   list name                          */
CHAR *lstpath);                    /*   buffer for list path & file name   */

GMEEXP INT                                /*   returns standard GME status codes  */
newslst(                           /* create a new sysop distribution list */
VOID *pWork,                       /*   GME work space                     */
const CHAR *lstnam,                /*   name for new list                  */
const CHAR *lstkey,                /*   key required to use list           */
SHORT surchg);                     /*   surcharge to use list              */

GMEEXP INT                                /*   returns standard GME status codes  */
delslst(                           /* delete a sysop dist list             */
const CHAR *lstnam);               /*   name of list                       */

GMEEXP INT                                /*   returns standard GME status codes  */
edtslst(                           /* open a sysop dist list for editing   */
VOID *pWork,                       /*   work area to initialize            */
const CHAR *lstnam);               /*   name of list                       */

GMEEXP INT                                /*   returns standard GME status codes  */
addslst(                           /* add an address to a sysop list       */
VOID *pWork,                       /*   GME work space                     */
const CHAR *addr);                 /*   address to add to list             */

GMEEXP INT                                /*   returns standard GME status codes  */
rstlstp(                           /* set sysop list pointer to top of list*/
VOID *pWork);                      /*   GME work space                     */

GMEEXP const CHAR *                       /*   returns pointer to temporary buffer*/
udlnam(VOID);                      /* path & file name to upload new list  */

GMEEXP INT                                /*   returns standard GME status codes  */
setslst(                           /* import file to replace existing list */
const CHAR *lstnam,                /*   name for new list                  */
const CHAR *lstfil);               /*   file containing new list           */

GMEEXP GBOOL
nxtsys(                            /* get next entry in sysop list         */
VOID *pWork,                       /*   work area to use                   */
CHAR *addr);                       /*   buffer for address                 */

GMEEXP struct qikdat *                    /*   copy of pointer to buffer          */
getqik(                            /* get a !QUICK list from disk          */
struct qikdat *qikbuf,             /*   pointer to !QUICK buffer           */
const CHAR *userid);               /*   user ID to use                     */

GMEEXP VOID
savqik(                            /* save a !QUICK list to disk           */
const struct qikdat *qikbuf);      /*   pointer to !QUICK buffer           */

GMEEXP struct qikdat *                    /*   copy of pointer to buffer          */
iniqik(                            /* initialize !QUICK record for cur user*/
struct qikdat *qikbuf,             /*   pointer to !QUICK buffer           */
const CHAR *userid);               /*   user ID to use                     */

GMEEXP VOID
insqik(                            /* insert entry into !QUICK buffer      */
INT pos,                           /*   position to insert at              */
const CHAR *entry,                 /*   new entry for position             */
struct qikdat *qikbuf);            /*   pointer to !QUICK buffer           */

GMEEXP VOID
delqik(                            /* delete an entry from !QUICK buffer   */
INT pos,                           /*   position to delete                 */
struct qikdat *qikbuf);            /*   pointer to !QUICK buffer           */

GMEEXP GBOOL
valslnm(                           /* is this a valid sysop dist list name?*/
const CHAR *name);                 /*   complete name (including @)        */

GMEEXP GBOOL
dlstxst(                           /* does dist list exist?                */
const CHAR *name);                 /*   complete list name (incl @ or !)   */

GMEEXP VOID
gmePlainText(                      /* cvt fmtted to plain text if necessary*/
CHAR *text);                       /*   text buffer (must be TXTLEN long)  */

GMEEXP VOID
gmeSetAppInfo(                     /* set app-defined info (when sending)  */
VOID *pWork,                       /*   for this work area                 */
const CHAR *appinf);               /*   to this buffer                     */

GMEEXP const CHAR *                       /*   returns pointer to temp buffer     */
gmeGetAppInfo(VOID);               /* get app-defined info (after reading) */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeModAppInfo(                     /* modify app-defined info (after read) */
VOID *pWork,                       /*   work area in use                   */
const CHAR *appinf);               /*   app-defined info buffer            */

GMEEXP CHAR *                             /*   returns pointer to destination     */
gmeGetAppSect(                     /* extract an app-defined info section  */
char *dst,                         /*   destination buffer                 */
const CHAR *src,                   /*   source buffer                      */
const CHAR *sect);                 /*   section name                       */

GMEEXP GBOOL                              /*   returns TRUE if update successful  */
gmeSetAppSect(                     /* set contents of app info section     */
CHAR *dst,                         /*   destination buffer                 */
const CHAR *src,                   /*   new contents ("" to remove)        */
const CHAR *sect);                 /*   section name                       */

/* user interface interface functions */

GMEEXP INT                                /*   returns standard GME status codes  */
inifdef(                           /* initialize forum def w/defaults      */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct fordsk *newdef);            /*   memory area to initialize          */

GMEEXP VOID
gmeGetForDft(                      /* get default forum configuration      */
struct fordsk *newdef,             /*   new forum definition structure     */
const CHAR *forop);                /*   Forum-Op to initialize with        */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeRecommend(                      /* recommend a forum data file          */
VOID *pWork,                       /*   GME work space (provided by caller)*/
CHAR *datfil);                     /*   data file path+file name buffer    */

GMEEXP INT                                /*   returns standard GME status codes  */
creatfor(                          /* create a new forum                   */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct fordsk *newdef,             /*   new forum definition structure     */
const CHAR *desc,                  /*   descriptive text                   */
const CHAR *echoes);               /*   pointer to array of echo addresses */
                                   /*   (may be NULL if no echoes)         */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeGCreateFor(                     /* create a new forum (no access check) */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct fordsk *newdef,             /*   new forum definition structure     */
const CHAR *desc,                  /*   descriptive text                   */
const CHAR *echoes);               /*   pointer to array of echo addresses */
                                   /*   (may be NULL if no echoes)         */

GMEEXP LONG
himsgid(VOID);                     /* get current highest message ID       */

GMEEXP INT
numforums(VOID);                   /* get number of forums                 */

GMEEXP const struct fordef *              /*   pointer to temporary buffer        */
getdefp(                           /* get pointer to forum definition      */
USHORT forum);                     /*   forum ID of def to get             */

GMEEXP struct fordef *                    /*   pointer to destination buffer      */
getdefb(                           /* copy forum def into a work buffer    */
USHORT forum,                      /*   forum ID of def to get             */
struct fordef *workdef);           /*   pointer to work buffer             */

GMEEXP const struct fordef *              /*   pointer to temporary buffer        */
fiddefp(                           /* ptr to forum def in forum ID order   */
INT idx);                          /*   index of forum ID                  */

GMEEXP struct fordef *                    /*   pointer to destination buffer      */
fiddefb(                           /* get forum def in forum ID order      */
INT idx,                           /*   index of forum ID                  */
struct fordef *workdef);           /*   pointer to work buffer             */

GMEEXP const struct fordef *              /*   pointer to temporary buffer        */
seqdefp(                           /* get pointer to forum def in sequence */
USHORT seqid);                     /*   sequence ID of forum               */

GMEEXP struct fordef *                    /*   pointer to destination buffer      */
seqdefb(                           /* get forum def into buffer in sequence*/
USHORT seqid,                      /*   sequence ID of forum               */
struct fordef *workdef);           /*   pointer to work buffer             */

GMEEXP const struct fordef *              /*   pointer to temporary buffer        */
nxtdefp(                           /* get ptr to next forum definition     */
const CHAR *name);                 /*   given name to start with           */

GMEEXP struct fordef *                    /*   pointer to destination buffer      */
nxtdefb(                           /* copy next forum def into a work buf  */
const CHAR *name,                  /*   given name to start with           */
struct fordef *workdef);           /*   pointer to work buffer             */

GMEEXP const struct fordef *              /*   pointer to temporary buffer        */
prvdefp(                           /* get ptr to prev forum definition     */
const CHAR *name);                 /*   given name to start with           */

GMEEXP struct fordef *                    /*   pointer to destination buffer      */
prvdefb(                           /* copy prev forum def into a work buf  */
const CHAR *name,                  /*   given name to start with           */
struct fordef *workdef);           /*   pointer to work buffer             */

GMEEXP VOID
getecho(                           /* copy forum's echoes into work buffer */
USHORT forum,                      /*   forum ID to get                    */
CHAR *echoes);                     /*   pointer to work buffer             */

GMEEXP VOID
getdesc(                           /* copy forum's desc into work buffer   */
USHORT forum,                      /*   forum ID to get                    */
CHAR *desc);                       /*   pointer to work buffer             */

GMEEXP VOID
getallf(                           /* get all info about a forum           */
USHORT forum,                      /*   forum ID to get                    */
struct fordsk *workdef,            /*   on-disk forum definition format    */
CHAR *desc,                        /*   buffer for description             */
CHAR *echoes);                     /*   buffer for echoes                  */

GMEEXP INT                                /*   returns standard GME status codes  */
cfgfacc(                           /* configure default access             */
USHORT forum,                      /*   for this forum                     */
const struct foracc *acc);         /*   forum access structure             */

GMEEXP INT                                /*   returns standard GME status codes  */
modfor(                            /* modify a forum                       */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct fordef *newdef,             /*   modified forum description         */
const CHAR *desc,                  /*   descriptive text                   */
const CHAR *echoes);               /*   pointer to array of echo addresses */
                                   /*(desc & echoes may be NULL if no chng)*/

GMEEXP INT                                /*   returns standard GME status codes  */
gmeGModifyFor(                     /* modify a forum (no access check)     */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct fordef *newdef,             /*   modified forum description         */
const CHAR *desc,                  /*   descriptive text                   */
const CHAR *echoes);               /*   pointer to array of echo addresses */
                                   /*(desc & echoes may be NULL if no chng)*/

GMEEXP INT                                /*   returns standard GME status codes  */
delfor(                            /* delete a forum                       */
VOID *pWork,                       /*   GME work space (provided by caller)*/
USHORT forum);                     /*   forum ID to delete                 */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeGDeleteFor(                     /* delete a forum (no access check)     */
void *pWork,                       /*   GME work space (provided by caller)*/
USHORT forum);                     /*   forum ID to delete                 */

GMEEXP INT
gmeMaxGrpFor(VOID);                /* get max # of forums per group        */

GMEEXP GBOOL
gmeGrpExist(                       /* does the specified group exist?      */
USHORT grpid);                     /*   group ID to check for              */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeCreateGrp(                      /* create a new forum group             */
VOID *workb,                       /*   GME work space (provided by caller)*/
struct forgrp *crtbuf);            /*   group information structure        */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeGCreateGrp(                     /* create a forum group (no access chk) */
VOID *workb,                       /*   GME work space (provided by caller)*/
struct forgrp *crtbuf);            /*   group information structure        */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeModifyGrp(                      /* modify a forum group                 */
VOID *workb,                       /*   GME work space (provided by caller)*/
struct forgrp *grpbuf);            /*   group information structure        */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeGModifyGrp(                     /* modify a forum group (no access chk) */
VOID *workb,                       /*   GME work space (provided by caller)*/
struct forgrp *grpbuf);            /*   group information structure        */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeModGrpHdr(                      /* modify group header (not forums)     */
VOID *workb,                       /*   GME work space (provided by caller)*/
struct forgrp *grpbuf);            /*   group information structure        */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeGModGrpHdr(                     /* modify group header (no access chk)  */
VOID *workb,                       /*   GME work space (provided by caller)*/
struct forgrp *grpbuf);            /*   group information structure        */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeModGrpFor(                      /* modify forums in group               */
VOID *workb,                       /*   GME work space (provided by caller)*/
USHORT grpid,                      /*   group ID to modify                 */
INT nforums,                       /*   number of forums in list           */
const USHORT *forlst);             /*   new list of forums                 */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeGModGrpFor(                     /* modify forums in group (no acc chk)  */
VOID *workb,                       /*   GME work space (provided by caller)*/
USHORT grpid,                      /*   group ID to modify                 */
INT nforums,                       /*   number of forums in list           */
const USHORT *forlst);             /*   new list of forums                 */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeAddGrpFor(                      /* add a forum to a group               */
VOID *workb,                       /*   GME work space (provided by caller)*/
USHORT grpid,                      /*   group ID to modify                 */
USHORT forum);                     /*   forum ID to add                    */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeGAddGrpFor(                     /* add a forum to a group (no acc chk)  */
VOID *workb,                       /*   GME work space (provided by caller)*/
USHORT grpid,                      /*   group ID to modify                 */
USHORT forum);                     /*   forum ID to add                    */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeDelGrpFor(                      /* delete a forum from a group          */
VOID *workb,                       /*   GME work space (provided by caller)*/
USHORT grpid,                      /*   group ID to modify                 */
USHORT forum);                     /*   forum ID to delete                 */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeGDelGrpFor(                     /* del a forum from a group (no acc chk)*/
VOID *workb,                       /*   GME work space (provided by caller)*/
USHORT grpid,                      /*   group ID to modify                 */
USHORT forum);                     /*   forum ID to delete                 */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeDeleteGrp(                      /* delete a group                       */
VOID *workb,                       /*   GME work space (provided by caller)*/
USHORT grpid);                     /*   group ID to delete                 */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeGDeleteGrp(                     /* delete a group (no access check)     */
VOID *workb,                       /*   GME work space (provided by caller)*/
USHORT grpid);                     /*   group ID to delete                 */

GMEEXP USHORT                             /*   returns ROOTGRP on failure         */
gmeGetGrpID(                       /* get group ID from path               */
const CHAR *path);                 /*   group path to trace                */

GMEEXP const struct forgrp *              /*   pointer to temporary buffer        */
gmeGetGrpP(                        /* get pointer to group info            */
USHORT grpid);                     /*   group ID to get                    */

GMEEXP struct forgrp *                    /*   pointer to destination buffer      */
gmeGetGrpB(                        /* copy group info into a buffer        */
USHORT grpid,                      /*   group ID to get                    */
struct forgrp *grpbuf);            /*   pointer to buffer                  */

GMEEXP const struct forgrp *              /*   pointer to temporary buffer        */
gmeNamedGrpP(                      /* get next group in a group            */
USHORT pargrp,                     /*   parent group ID                    */
const CHAR *name);                 /*   name of group to get after         */

GMEEXP struct forgrp *                    /*   pointer to destination buffer      */
gmeNamedGrpB(                      /* get next group in a group            */
USHORT pargrp,                     /*   parent group ID                    */
const CHAR *name,                  /*   name of group to get after         */
struct forgrp *grpbuf);            /*   pointer to buffer                  */

GMEEXP const struct forgrp *              /*   pointer to temporary buffer        */
gmeNextGrpP(                       /* get next group in a group            */
USHORT pargrp,                     /*   parent group ID                    */
const CHAR *name);                 /*   name of group to get after         */

GMEEXP struct forgrp *                    /*   pointer to destination buffer      */
gmeNextGrpB(                       /* get next group in a group            */
USHORT pargrp,                     /*   parent group ID                    */
const CHAR *name,                  /*   name of group to get after         */
struct forgrp *grpbuf);            /*   pointer to buffer                  */

GMEEXP const struct forgrp *              /*   pointer to temporary buffer        */
gmePrevGrpP(                       /* get previous group in a group        */
USHORT pargrp,                     /*   parent group ID                    */
const CHAR *name);                 /*   name of group to get before        */

GMEEXP struct forgrp *                    /*   pointer to destination buffer      */
gmePrevGrpB(                       /* get previous group in a group        */
USHORT pargrp,                     /*   parent group ID                    */
const CHAR *name,                  /*   name of group to get before        */
struct forgrp *grpbuf);            /*   pointer to buffer                  */

GMEEXP const struct fordef *              /*   pointer to temporary buffer        */
gmeGetGrpFDefP(                    /* get def of named forum in a group    */
USHORT grpid,                      /*   group ID forum is in               */
const CHAR *name);                 /*   name of forum to find              */

GMEEXP struct fordef *                    /*   copy of pointer to buffer          */
gmeGetGrpFDefB(                    /* get def of named forum in a group    */
USHORT grpid,                      /*   group ID forum is in               */
const CHAR *name,                  /*   name of forum to find              */
struct fordef *defbuf);            /*   pointer to buffer                  */

GMEEXP const struct fordef *              /*   pointer to temporary buffer        */
gmeNextGrpFDefP(                   /* get def of next forum in a group     */
USHORT grpid,                      /*   group ID forum is in               */
const CHAR *name);                 /*   name of forum to find after        */

GMEEXP struct fordef *                    /*   copy of pointer to buffer          */
gmeNextGrpFDefB(                   /* get def of next forum in a group     */
USHORT grpid,                      /*   group ID forum is in               */
const CHAR *name,                  /*   name of forum to find after        */
struct fordef *defbuf);            /*   pointer to buffer                  */

GMEEXP const struct fordef *              /*   pointer to temporary buffer        */
gmePrevGrpFDefP(                   /* get def of previous forum in a group */
USHORT grpid,                      /*   group ID forum is in               */
const CHAR *name);                 /*   name of forum to find before       */

GMEEXP struct fordef *                    /*   copy of pointer to buffer          */
gmePrevGrpFDefB(                   /* get def of previous forum in a group */
USHORT grpid,                      /*   group ID forum is in               */
const CHAR *name,                  /*   name of forum to find before       */
struct fordef *defbuf);            /*   pointer to buffer                  */

GMEEXP INT                                /*   (returns NOIDX if not found)       */
gmeGetGrpFIdx(                     /* get index of named forum in group    */
const struct forgrp *grpbuf,       /*   group info buffer to find in       */
const CHAR *name);                 /*   before this forum name             */

GMEEXP INT                                /*   (returns NOIDX if not found)       */
gmePrevGrpFIdx(                    /* get index of previous forum in group */
const struct forgrp *grpbuf,       /*   group info buffer to find in       */
const CHAR *name);                 /*   before this forum name             */

GMEEXP INT                                /*   (returns NOIDX if not found)       */
gmeNextGrpFIdx(                    /* get index of next forum in group     */
const struct forgrp *grpbuf,       /*   group to find in                   */
const CHAR *name);                 /*   after this forum name              */

GMEEXP INT                                /*   returns VAL code                   */
valadr(                            /* validate address                     */
VOID *pWork,                       /*   GME work space                     */
const CHAR *from,                  /*   User-ID writing the message        */
CHAR *to,                          /*   to address (may be modified)       */
USHORT forum);                     /*   forum message being written in     */

GMEEXP INT                                /*   returns VAL code                   */
valatt(                            /* validate file attachments            */
VOID *pWork,                       /*   GME work space                     */
const CHAR *from,                  /*   User-ID writing the message        */
const CHAR *to,                    /*   to address                         */
USHORT forum);                     /*   forum message being written in     */

GMEEXP INT                                /*   returns VAL code                   */
valrrr(                            /* validate return receipt request      */
VOID *pWork,                       /*   GME work space                     */
const CHAR *from,                  /*   User-ID writing the message        */
const CHAR *to,                    /*   to address                         */
USHORT forum);                     /*   forum message being written in     */

GMEEXP INT                                /*   returns VAL code                   */
valpri(                            /* validate priority messaging          */
VOID *pWork,                       /*   GME work space                     */
const CHAR *from,                  /*   User-ID writing the message        */
const CHAR *to,                    /*   to address                         */
USHORT forum);                     /*   forum message being written in     */

GMEEXP INT                                /*   returns VAL code                   */
vfwdadr(                           /* validate address for forwarding      */
VOID *pWork,                       /*   GME work space                     */
const CHAR *from,                  /*   User-ID doing the forwarding       */
CHAR *to,                          /*   to address (may be modified)       */
USHORT forum);                     /*   forum message being written in     */

GMEEXP INT                                /*   returns VAL code                   */
vfwdatt(                           /* validate attachment for forwarding   */
VOID *pWork,                       /*   GME work space                     */
const CHAR *from,                  /*   User-ID writing the message        */
const CHAR *to,                    /*   to address                         */
USHORT forum);                     /*   forum message being written in     */

GMEEXP INT                                /*   returns VAL code                   */
vfwdpri(                           /* validate priority message for fwding */
VOID *pWork,                       /*   GME work space                     */
const CHAR *from,                  /*   User-ID writing the message        */
const CHAR *to,                    /*   to address                         */
USHORT forum);                     /*   forum message being written in     */

GMEEXP INT                                /*   returns standard GME status code   */
val2gme(                           /* convert a VAL code to status code    */
INT valcode);                      /*   VAL code to convert                */

GMEEXP const CHAR *                       /*   path & file name to place file in  */
ulname(                            /* path & file name to upload att to    */
const struct message *msg);        /*   header of message to attach to     */

GMEEXP const CHAR *                       /*   path & file name of attachment     */
dlname(                            /* path & file name to dnload att from  */
const struct message *msg);        /*   header of message with attachment  */

GMEEXP LONG
sendchg(                           /* total charges to send a message      */
VOID *pWork,                       /*   work area in use                   */
const struct message *msg,         /*   new message structure              */
LONG attsiz);                      /*   attachment size                    */

GMEEXP INT                                /*   returns standard GME status codes  */
simpsnd(                           /* simple send msg (non-user specific)  */
struct message *msg,               /*   message header structure           */
const CHAR *text,                  /*   message body text                  */
const CHAR *filatt);               /*   path+file name of att (if any)     */

GMEEXP INT                                /*   returns standard GME status codes  */
gsndmsg(                           /* send message (non-user specific)     */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct message *msg,               /*   new message structure              */
const CHAR *text,                  /*   message body text                  */
const CHAR *filatt);               /*   path+file name of att (if any)     */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeSendMsg(                        /* send a new message from a user       */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct message *msg,               /*   new message structure              */
const CHAR *text,                  /*   message body text                  */
const CHAR *filatt,                /*   path+file name of att (if any)     */
const CHAR *cclist);               /*   list of cc: addresses (if any)     */

GMEEXP INT                                /*   returns standard GME status codes  */
reply(                             /* reply to current message in context  */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct message *msg,               /*   message header structure           */
const CHAR *text,                  /*   new message text                   */
const CHAR *filatt,                /*   path+file name of att (if any)     */
const CHAR *cclist);               /*   list of cc: addresses (if any)     */

GMEEXP INT                                /*   returns standard GME status codes  */
copymsg(                           /* send copy of current msg in context  */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct message *msg,               /*   message header structure           */
const CHAR *text);                 /*   message text                       */

GMEEXP INT                                /*   returns standard GME status codes  */
fwdmsg(                            /* forward current message in context   */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct message *msg,               /*   message header structure           */
const CHAR *text);                 /*   message text                       */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeGForward(                       /* forward a message (not user-specific)*/
VOID *pWork,                       /*   GME work space (provided by caller)*/
GBOOL delorig,                     /*   delete original (forward vs. copy) */
struct message *msg,               /*   message header buffer              */
const CHAR *text);                 /*   message text buffer                */

GMEEXP INT                                /*   returns standard GME result codes  */
tagatt(                            /* create tag for message attachment    */
VOID *pWork,                       /*   GME work space (provided by caller)*/
const struct message *msg,         /*   message header structure           */
CHAR *tag);                        /*   file tag buffer to use             */

GMEEXP LONG
msgintg(                           /* what's the message ID associated     */
const CHAR *tag);                  /*   with this tag?                     */

GMEEXP USHORT
forintg(                           /* what's the forum ID associated       */
const CHAR *tag);                  /*   with this tag?                     */

GMEEXP GBOOL                              /*   ok to start download?              */
dlstart(                           /* current user starts tagged att dnload*/
CHAR *tag);                        /*   file tag structure in use          */

GMEEXP VOID
dlabt(                             /* current user aborted att download    */
CHAR *tag);                        /*   file tag structure in use          */

GMEEXP VOID
dldone(                            /* current user finished att download   */
CHAR *tag);                        /*   file tag structure in use          */

GMEEXP GBOOL                              /*   ok to start download?              */
gdlstart(                          /* user starts tagged att dnload        */
CHAR const * userid,               /*   User-ID doing download             */
CHAR * tag);                       /*   file tag structure in use          */

GMEEXP VOID
gdlabt(                            /* user aborted attachment download     */
CHAR const * userid,               /*   User-ID doing download             */
CHAR * tag);                       /*   file tag structure in use          */

GMEEXP VOID
gdldone(                           /* user finished attachment download    */
CHAR const * userid,               /*   User-ID doing download             */
CHAR * tag);                       /*   file tag structure in use          */

GMEEXP GBOOL                              /*   ok to download?                    */
gdlatt(                            /* tagged attachment downloaded for user*/
const CHAR *userid,                /*   User-ID attachment downloaded for  */
CHAR *tag);                        /*   file tag structure in use          */

GMEEXP const struct message *             /*   pointer to temporary msg struct    */
tagmsg(                            /* get tagged message                   */
CHAR *tag);                        /*   file tag structure in use          */

GMEEXP LONG
firstnew(                          /* get first new message #              */
const CHAR *userid,                /*   for this user ID                   */
USHORT forum);                     /*   in this forum                      */
                                   /*   NOTE: modifies othusn,othusp,etc.  */

GMEEXP VOID
inormrd(                           /* initialize "normal" read context     */
VOID *pWork,                       /*   work area to initialize            */
const CHAR *userid,                /*   user ID doing reading              */
USHORT forum,                      /*   forum to read from                 */
LONG msgid);                       /*   message to start at                */

GMEEXP VOID
forctx(                            /* change forum of read context         */
VOID *pWork,                       /*   work area in use                   */
USHORT forum,                      /*   forum to change to                 */
INT sequence);                     /*   new sequence to establish          */

GMEEXP VOID
seqctx(                            /* change sequence of read context      */
VOID *pWork,                       /*   work area in use                   */
INT sequence);                     /*   sequence to change to              */

GMEEXP VOID
msgctx(                            /* change cur message of read context   */
VOID *pWork,                       /*   work area in use                   */
LONG msgid);                       /*   message ID to change to            */

GMEEXP VOID
thrctx(                            /* change thread of read context        */
VOID *pWork,                       /*   work area in use                   */
LONG thrid);                       /*   thread ID to change to             */

GMEEXP VOID
inictx(                            /* initialize read context              */
VOID *pWork,                       /*   work area to initialize            */
const CHAR *userid,                /*   user ID doing reading              */
INT sequence,                      /*   sequence to use                    */
USHORT forum,                      /*   forum to read from                 */
LONG msgid,                        /*   message to start at                */
LONG thrid);                       /*   thread to use (if any)             */

GMEEXP INT                                /*   returns standard GME status codes  */
readpar(                           /* read parent of message               */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct message *msg,               /*   message header structure buffer    */
CHAR *text);                       /*   message body text buffer           */

GMEEXP INT                                /*   returns standard GME status codes  */
thrinfo(                           /* read info on a thread (orig message) */
VOID *pWork,                       /*   GME work space (provided by caller)*/
INT direct,                        /*   direction (0=same, 1=next, -1=prev)*/
USHORT *nmsgs,                     /*   number of messages in thread       */
struct message *msg,               /*   message header structure buffer    */
CHAR *text);                       /*   message body text buffer           */

GMEEXP int                                /*   returns standard GME status codes  */
gmeGThreadInfo(                    /* read thread info (not user-specific) */
VOID *pWork,                       /*   GME work space (provided by caller)*/
INT direct,                        /*   direction (0=same, 1=next, -1=prev)*/
USHORT *nmsgs,                     /*   number of messages in thread       */
struct message *msg,               /*   message header structure buffer    */
CHAR *text);                       /*   message body text buffer           */

GMEEXP INT                                /*   returns standard GME status codes  */
readmsg(                           /* read current message in context      */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct message *msg,               /*   message header structure buffer    */
CHAR *text);                       /*   message body text buffer           */

GMEEXP INT                                /*   returns standard GME status codes  */
nearmsg(                           /* read nearest to cur msg in context   */
VOID *pWork,                       /*   GME work space (provided by caller)*/
INT nearop,                        /*   get near "style" to use            */
struct message *msg,               /*   message header structure buffer    */
CHAR *text);                       /*   message body text buffer           */

GMEEXP INT                                /*   returns standard GME status codes  */
nextmsg(                           /* read next message in context         */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct message *msg,               /*   message header structure buffer    */
CHAR *text);                       /*   message body text buffer           */

GMEEXP INT                                /*   returns standard GME status codes  */
prevmsg(                           /* read previous message in context     */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct message *msg,               /*   message header structure buffer    */
CHAR *text);                       /*   message body text buffer           */

GMEEXP INT                                /*   returns standard GME status codes  */
nextseq(                           /* read next message a sequence         */
VOID *pWork,                       /*   GME work space (provided by caller)*/
INT sequence,                      /*   sequence to use                    */
struct message *msg,               /*   message header structure buffer    */
CHAR *text);                       /*   message body text buffer           */

GMEEXP INT                                /*   returns standard GME status codes  */
prevseq(                           /* read previous message in a sequence  */
VOID *pWork,                       /*   GME work space (provided by caller)*/
INT sequence,                      /*   sequence to use                    */
struct message *msg,               /*   message header structure buffer    */
CHAR *text);                       /*   message body text buffer           */

GMEEXP INT                                /*   returns standard GME status codes  */
frdmsg(                            /* read message in context (keep format)*/
VOID *pWork,                       /*   GME work space (provided by caller)*/
INT direct,                        /*   read direction code                */
struct message *msg,               /*   message header structure buffer    */
CHAR *text);                       /*   message body text buffer           */

GMEEXP INT                                /*   returns standard GME status codes  */
frdseq(                            /* read message in a sequence           */
VOID *pWork,                       /*   GME work space (provided by caller)*/
INT direct,                        /*   read direction code                */
INT sequence,                      /*   sequence to use                    */
struct message *msg,               /*   message header structure buffer    */
CHAR *text);                       /*   message body text buffer           */

GMEEXP INT                                /*   returns standard GME status codes  */
readparf(                          /* read parent of message (keep format) */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct message *msg,               /*   message header structure buffer    */
CHAR *text);                       /*   message body text buffer           */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeGReadGlob(                      /* read forum msg given global ID       */
VOID *pWork,                       /*   GME work space (provided by caller)*/
const struct globid *globid,       /*   global ID to read                  */
struct message *msg,               /*   message header structure buffer    */
CHAR *text);                       /*   message body text buffer           */

GMEEXP INT                                /*   returns standard GME status codes  */
grdmsg(                            /* generic read message in context      */
VOID *pWork,                       /*   GME work space (provided by caller)*/
INT direct,                        /*   read direction code                */
struct message *msg,               /*   message header structure buffer    */
CHAR *text);                       /*   message body text buffer           */

GMEEXP INT                                /*   returns standard GME status codes  */
markread(                          /* mark a message as read               */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct message *msg,               /*   message header structure buffer    */
CHAR *text);                       /*   message body text buffer           */

GMEEXP INT                                /*   returns standard GME status codes  */
markreadf(                         /* mark a message as read (keep format) */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct message *msg,               /*   message header structure buffer    */
CHAR *text);                       /*   message body text buffer           */

GMEEXP INT                                /*   returns standard GME status codes  */
delmsg(                            /* delete current message in context    */
VOID *pWork);                      /*   GME work space (provided by caller)*/

GMEEXP INT                                /*   returns standard GME status codes  */
gmeGDeleteMsg(                     /* delete current msg (non-user spec)   */
VOID *pWork);                      /*   GME work space (provided by caller)*/

GMEEXP INT                                /*   returns standard GME status codes  */
modmsg(                            /* modify current message in context    */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct message *msg,               /*   message header structure buffer    */
const CHAR *text);                 /*   message body text buffer           */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeGModifyMsg(                     /* modify current msg (not user-spec)   */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct message *msg,               /*   message header structure buffer    */
const CHAR *text);                 /*   message body text buffer           */

GMEEXP INT                                /*   returns standard GME status codes  */
aprvmsg(                           /* approve/unapprove current message    */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct message *msg,               /*   message header structure buffer    */
const CHAR *text,                  /*   message body text buffer           */
GBOOL approve);                    /*   TRUE=approve, FALSE=unapprove      */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeGApprove(                       /* approve/unapprove msg (not user-spec)*/
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct message *msg,               /*   message header structure buffer    */
GBOOL approve);                    /*   TRUE=approve, FALSE=unapprove      */

GMEEXP INT                                /*   returns standard GME status codes  */
exmtmsg(                           /* exempt/unexempt current message      */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct message *msg,               /*   message header structure buffer    */
const CHAR *text,                  /*   message body text buffer           */
GBOOL exempt);                     /*   TRUE=exempt, FALSE=unexempt        */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeGExempt(                        /* exempt/unexempt msg (not user-spec)  */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct message *msg,               /*   message header structure buffer    */
GBOOL exempt);                     /*   TRUE=exempt, FALSE=unexempt        */

GMEEXP INT                                /*   returns VAL code                   */
setafwd(                           /* set auto-forwardee for current user  */
CHAR *newfwde);                    /*   new auto-forwardee (modified)      */

GMEEXP INT                                /*   returns VAL code                   */
wrtany(VOID);                      /* can current user E-mail anyone       */
                                   /*   (other than Sysop)                 */

GMEEXP INT                                /*   returns standard access level code */
foracc(                            /* get current user's forum access level*/
USHORT fid);                       /*   given forum ID                     */

GMEEXP INT                                /*   returns standard access level code */
gforac(                            /* get a user's forum access level      */
const CHAR *uid,                   /*   given any User-ID                  */
USHORT fid);                       /*   and forum ID                       */

GMEEXP INT                                /*   returns standard access level code */
qforac(                            /* get a user's forum access level      */
const struct qscfg *qsc,           /*   given quickscan                    */
USHORT fid);                       /*   and forum ID                       */

GMEEXP const CHAR *
accstr(                            /* string describing forum access level */
INT acclvl);                       /*   access level to describe           */

GMEEXP INT                                /*   returns new number of echoes       */
addecho(                           /* add an echo to list                  */
CHAR *echoes,                      /*   echo list buffer                   */
const CHAR *newadr,                /*   echo address to add                */
INT necho);                        /*   current number of echoes           */

GMEEXP INT                                /*   returns new number of echoes       */
delecho(                           /* delete an echo from list             */
CHAR *echoes,                      /*   echo list buffer                   */
INT echonum,                       /*   index of echo address to delete    */
INT necho);                        /*   current number of echoes           */

/* importer/exporter interface functions */

GMEEXP VOID
gmeForceEcho(                      /* force imported message to be echoed  */
VOID *pWork);                      /*   work space to be used for impmsg() */

GMEEXP INT                                /*   returns standard GME status codes  */
impmsg(                            /* import a message                     */
VOID *pWork,                       /*   GME work space (provided by caller)*/
struct message *msg,               /*   new message structure              */
const CHAR *text,                  /*   message body text                  */
const CHAR *filatt);               /*   path+file name of att (if any)     */

GMEEXP INT                                /*   returns standard GME status codes  */
gmeGExportMsg(                     /* send a message directly to exporter  */
const CHAR *to,                    /*   address to send message to         */
struct message *msg,               /*   new message structure              */
const CHAR *text,                  /*   message body text                  */
const CHAR *filatt);               /*   path+file name of att (if any)     */

GMEEXP const CHAR *                       /*   temporary buffer containing spec   */
expasp(                            /* get exporter attachment file spec    */
const CHAR *to,                    /*   address message is being sent to   */
const struct message *msg);        /*   given message header structure     */

GMEEXP VOID
register_exp(                      /* register an exporter                 */
struct exporter *exp);             /*   pointer to exporter control block  */

GMEEXP GBOOL
valpfx(                            /* is this a valid exporter prefix?     */
const CHAR *prefix);               /*   prefix to check                    */

GMEEXP GBOOL
expavl(VOID);                      /* are any exporters available?         */

GMEEXP GBOOL
isexpa(                            /* is this an exporter-style address    */
const CHAR *adr);                  /*   address to check                   */

GMEEXP CHAR *
skppfx(                            /* skip over exporter prefix (if any)   */
const CHAR *adr);                  /*   address with prefix                */

GMEEXP INT
numexp(VOID);                      /* get number of available exporters    */

GMEEXP INT                                /*   returns NOIDX if not found         */
expidx(                            /* index of exporter in handler array   */
const CHAR *to);                   /*   address containing prefix          */

GMEEXP const struct expinfo *             /*   returns pointer to static buffer   */
expinf(                            /* get info on an exporter              */
INT idx);                          /*   given exporter index               */

GMEEXP const CHAR *                       /*   ptr to temp area (may be msgbuf)   */
exphlp(                            /* get help message for an exporter     */
INT idx);                          /*   given exporter index               */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __GME_H                              */
