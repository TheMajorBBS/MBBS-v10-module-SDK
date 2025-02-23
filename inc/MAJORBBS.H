/***************************************************************************
 *                                                                         *
 *   MAJORBBS.H                                                            *
 *                                                                         *
 *   Copyright (c) 1987-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   This is the main Worldgroup header file.                              *
 *                                                                         *
 *                                            - T. Stryker 6/24/86         *
 *                                                                         *
 ***************************************************************************/

#ifndef __MAJORBBS_H
#define __MAJORBBS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "brkthu.h"
#include "locknkey.h"
#include "usracc.h"
#include "autorip.h"


#define VERSIZ          9          /* size of ASCII rendition of versions  */
#define SBVSIZ         40          /* size of ASCII rendition of sub-ver   */

#include "server.h"

#define MAXNTERM      256          /* maximum allowed value of nterms      */
#define INPSIZ        256          /* input buffer size for each channel   */
#define OUTSIZ     outbsz          /* config param: output buffer size/chan*/
#define MTXSIZ        400          /* maximum message-text string size     */
#define DFTIMX        127          /* default input-char count max per line*/
#define NCOMTY          8          /* number of computer type codes        */
#define NACMTY (NCOMTY-4)          /* # of computer type codes in use      */
#define NAGEBK          5          /* number of age brackets tallied       */
#define AUDSIZ        132          /* (obsolete) size of audit trail recs  */
#define CTNUOS          2          /* screen len code used for "continuous"*/
#define XTRIES         10          /* # of times to inject X's fo "go" cmd */
#define TVRSIZ         16          /* maximum size of a text variable name */
#define MAXSEL         25          /* maximum number of selections per page*/
#define FNMSIZ         80          /* maximum size for file and path       */
#define PNMSIZ         16          /* maximum size for menu page names     */
#define MNMSIZ         25          /* maximum size for module names        */
#define CMDSIZ         60          /* maximum size for command strings     */
#define SHDSIZ         31          /* maximum size for short descriptions  */
#define LNDSIZ         50          /* maximum size for long descriptions   */
#define TITLSZ         43          /* maximum size for menu page titles    */
#define AIDSIZ          9          /* maximum size for C/S appids          */
#define FNSIZE      (8+1)          /* size of filename (w/o ext) w/ NUL    */
#define FNEXSZ  (8+1+3+1)          /* filename and ext, with '.' and NUL   */

#define NUMGRPS        17          /* # of channel groups fm WGSMAJOR.MSG  */
#define TPERSC         18          /* real-time irpts/sec (== Flash rate)  */
#define MAXXRF         16          /* max # of displayed possible uid x-ref*/
#define GENSIZ       8192          /* max size of a generic user dbase rec */
#define ZAPINT          5          /* interval to decrement zaptbl values  */
#define ZAPMAX         60          /* max value of a zaptbl entry          */
#define ANNOSIZE        4          /* reserved size hooked announcement mem*/

#define PAGBUFSIZ     512          /* maximum size for paging buffer       */

                                   /* System editor call                   */
WGSEXPF(INT,bgnedt)(INT,CHAR *,INT,CHAR *,SHORT (*)(SHORT),INT);

                                   /* flags that can be passed to bgnedt() */
#define ED_FILIMP       1          /*   allow importing from DOS files     */
#define ED_READON       2          /*   "read only" mode                   */
#define ED_CLRTOP       4          /*   clear topic buffer upon entry      */
#define ED_CLRTXT       8          /*   clear text buffer upon entry       */
#define ED_FILESD      16          /*   use "file" flavor of editor        */
#define ED_LINEMO      32          /*   force use of the line editor       */
#define ED_FIXTOP      64          /*   don't allow changing of topic field*/

                              /* flags passed to the editor's whndun() rou */
#define ED_QUITEX     256          /*   user quit the editing session      */

                                   /* is this user editing from here?      */
WGSEXPF(INT,inedit)(INT usn,SHORT (*exipnt)(SHORT));

                                   /* editor import hooking routine        */
WGSEXPF(VOID,edtimr)(GBOOL (*imradr)());


WGSEXPF(VOID,edtpfn)(INT pfnlvl); /* editor set pfn level (after bgnedt)  */

#include "paging.h"                /* needs to be here for various #defines*/

struct user {                      /* volatile per-user info maintained    */
#ifndef GCV2
     ULONG flags;                  /*   runtime flags                      */
     ULONG tckrst;                 /*   lngtck when channel reset (rstchn()*/
     ULONG tckonl;                 /*   lngtck when logging on (lonstf())  */
     LONG baud;                    /*   baud rate                          */
#endif // GCV2
     INT usrcls;                   /*   class (offline, or type of online) */
     INT *keys;                    /*   dyn. alloc'd array of key bits     */
     INT state;                    /*   state (module number in effect)    */
     INT substt;                   /*   substt (for convenience of module) */
     INT lofstt;                   /*   state of final lofrou() routine    */
     INT usetmr;                   /*   usage timer (for nonlive timeouts) */
     INT minut4;                   /*   total minutes of use, times 4      */
     INT countr;                   /*   general purpose counter            */
     INT pfnacc;                   /*   profanity accumulator              */
#ifdef GCV2
     ULONG flags;                  /*   runtime flags                      */
     USHORT baud;                  /*   baud rate                          */
     SHORT crdrat;                 /*   credit-consumption rate            */
#endif // GCV2
     INT nazapc;                   /*   no-activity auto-logoff counter    */
     INT linlim;                   /*   "logged in" module loop limit      */
#ifndef GCV2
     INT lingo;                    /*   user lang, 0 to nlingo-1 (LINGO.H) */
     INT entstt;                   /*   entered A/A mode for this state    */
#endif // GCV2
     struct clstab *cltptr;        /*   ptr to guys current class in table */
     VOID (*polrou)();             /*   pointer to current poll routine    */
#ifndef GCV2
     SHORT crdrat;                 /*   credit-consumption rate            */
     USHORT tspxt;                 /*   ticker time when SPX terminated    */
     CHAR col;                     /*   current column for secret char echo*/
     CHAR wid;                     /*   line width for secret char echo    */
     CHAR ech;                     /*   char to echo for secret char echo  */
     CHAR byecnt;                  /*   count-down for byenow() time-out   */
#endif // GCV2
     CHAR lcstat;                  /*   LAN chan state  0=nonlan/nonhdw    */
};

#ifdef GCV2
struct extusr {               /* extra volatile per-user info              */
     SHORT lingo;             /*    user language, 0 to nlingo-1 (LINGO.H) */
     CHAR col;                /*    current column for secret CHAR echo    */
     CHAR wid;                /*    line width for secret CHAR echo        */
     CHAR ech;                /*    character to echo for secret CHAR echo */
     LONG baud;               /*    chan baud rate (obsoletes usrptr->baud)*/
     USHORT tspxt;            /*    ticker time when SPX terminated        */
     ULONG tckrst;            /*    lngtck when channel reset (rstchn())   */
     ULONG tckonl;            /*    lngtck when logging on (lonstf())      */
     CHAR byecnt;             /*    count-down for byenow() time-out       */
     SHORT entstt;            /*    entered A/A mode to go to this state   */
};

WGSEXPV(struct extusr*) extptr;    /* global pointer to extusr             */
WGSEXPV(struct extusr*) othexp;    /* global pointer to other extusr       */

struct extusr *extoff(INT unum);
#endif // GCV2

struct usrmnu {            /* user's menuing-specific variables    */
     CHAR curpag[PNMSIZ];          /*   current menu page                  */
     CHAR parpag[PNMSIZ];          /*   parent menu page                   */
     CHAR selchrs[MAXSEL];         /*   select characters currently avail  */
     CHAR pages[MAXSEL][PNMSIZ];   /*   pages/file names for select chars  */
     CHAR optdsp[MAXSEL];          /*   instructions on how to display opts*/
     INT keyreq[MAXSEL];           /*   key required for each select char  */
     FILE *fp;                     /*   ptr to file currently being viewed */
     CHAR mnuttl[TITLSZ];          /*   menu page title                    */
};

WGSEXPV(struct usrmnu*) mnuusr;

struct pglink {                    /* menu page menu selection data struct */
     SHORT position;               /*   idx of position in WGSMTREE editor */
     CHAR selchr;                  /*   select character for page          */
     CHAR iconame[FNSIZE];         /*   C/S display icon name              */
     CHAR destpage[PNMSIZ];        /*   destination page name              */
     CHAR optdsp;                  /*   instructions on how to display opts*/
     CHAR keyreq[KEYSIZ];          /*   key required for each page         */
     CHAR shortd[SHDSIZ];          /*   selection name                     */
     CHAR longd[LNDSIZ];           /*   longer description of option       */
};

struct mnupag {                    /* menu page data struct (dfa layout)   */
     CHAR menutype[1];             /*   menu page type, "A"=A/A or "C"=C/S */
     CHAR pagnam[PNMSIZ];          /*   menu page name                     */
     CHAR parpag[PNMSIZ];          /*   parent menu page                   */
     CHAR fname[GCSTRPTH];         /*   file name for menus/displayed files*/
     CHAR modnam[MNMSIZ];          /*   module name to enter (module lnk)  */
     CHAR cmdstg[CMDSIZ];          /*   command string for entry to module */
     CHAR golock[KEYSIZ];          /*   lock placed on "go"ing to this page*/
     SHORT flags;                  /*   flags for cond'l/mod pages, etc    */
     CHAR mnuttl[TITLSZ];          /*   menu page title/menu window caption*/
     SHORT npages;                 /*   number of pages stored             */
     LONG ichange;                 /*   time code for menu icon change     */
#ifdef GCV2
     CHAR spare[70];               /*   former spare space                 */
#endif // GCV2
     struct pglink page[MAXSEL];   /*   variable number of pages stored    */
};
WGSEXPV(struct mnupag*) menupg;

                                   /* defines for flags for above struct   */
#define AUTPAG      1              /*   auto-select page                   */
#define MDLPAG      2              /*   module link page                   */
#define FILPAG      4              /*   file display page                  */
#define CNGOTO      8              /*   can "go" to this page              */
#define DFTDSP     16              /*   use default menu display           */
#define DISABL     32              /*   page is currently disabled         */
#define TPOTRE     64              /*   page is top of a menu tree         */
#define NOMPHD    128              /*   no module page hdr if module page  */
#define NOFPHD    256              /*   no file page hdr if file page      */
                                   /*    (c/s mode: launch the file)       */
#define CSMPAG    512              /*   C/S module link page               */

WGSEXPV(GBOOL) globgo;             /* doing a global /go exit chain?       */

WGSEXPV(INT) mnudnl;               /* user# downloading wgsmenu2.dat(or -1)*/

WGSEXPV(DFAFILE*) mnubb;           /* menu information btrieve file pointer*/

WGSEXPV(INT) detflg;               /* shwusr(): called frm here, DETAIL cmd     */

                                   /* user usrcls codes                    */
#define VACANT 0                   /*   vacant, offline                    */
#define ONLINE 1                   /*   online, not logged on              */
#define BBSPRV 2                   /*   online, private class (internal)   */
#define SUPIPG 3                   /*   signup in progress                 */
#define SUPLON 4                   /*   supplemental logon in progress     */
#define SUPLOF 5                   /*   supplemental logoff in progress    */
#define ACTUSR 6                   /*   logged on and active               */

                         /* VACANT usrcls state codes:                     */
#define JSTRST   0       /* just reset, awaiting command confirmation      */
#define EMTATZ  -1       /* emitting ATZ, awaiting completion              */
#define EKLVEC  -2       /* emitting kill-vector, awaiting completion      */
#define W4KILL  -3       /* waiting for kill-system to take effect         */
#define ATZDUN  -4       /* ATZ OK received, waiting 1/10 sec extra        */
#define ESTVEC  -5       /* emitting startup string, awaiting completion   */
#define W4ISOK  -6       /* waiting for OK in response to init string      */
#define AWAITC  -7       /* awaiting call                                  */
#define XERING  -8       /* XE1201/3 phone rang, answered, awaiting carrier*/
#define HARING  -9       /* Hayes-style phone rang, answd, awaiting carrier*/
#define HPAUSE -10       /* Hayes-style post-connect 2-second pause        */
#define AUTSNS -11       /* Auto sensors doing their stuff (AUTSNS.C)      */
#define WAIT29 -20       /* wait to be able to send X.29 string            */
#define W4SPXT -21       /* wait for old SPX session to terminate          */
#define WCDICN -30       /* wait for a GCDI channel to connect to server   */
#define CRESET -31       /* pending channel reset                          */

                                   /* Menuing System's sub-state codes     */
#define JSTLON -1                  /*   just logged on: goto TOP page      */
#define JSTRET 0                   /*   just ret'd from module: goto parent*/
#define SITTIN 1                   /*   user is sitting at a menu prompt   */
#define MNUFIL 2                   /*   a menu file is being displayed     */
#define OTHFIL 3                   /*   a file page is being displayed     */
#define FINDIN 4                   /*   user is trying to "find" a page    */

                                   /* standard profanity thresholds        */
#define WRNPFN 7                   /*   warning level                      */
#define MAXPFN 12                  /*   logoff level                       */

                                   /* user runtime flag bit values         */
#define NOINJO 0x00000001L         /*   unable to receive injoth() msgs    */
#define INJOIP 0x00000002L         /*   injoth() operation in progress     */
#define BYEBYE 0x00000004L         /*   going away, just wait for msg done */
#define NOHDWE 0x00000008L         /*   no hardware, emulation chan only   */
#define OPCHAT 0x00000010L         /*   chatting-with-sysop flag           */
#define ACTIVE 0x00000020L         /*   channel-is-active (gen'ing status) */
#define MASTER 0x00000040L         /*   user has the "master key" flag     */
#define IS2698 0x00000080L         /*   channel-is-2698 (XE2400)           */
#define NOZAP  0x00000100L         /*   don't logoff freeloader flag       */
#define ISRIAL 0x00000200L         /*   channel-is-serial-port             */
#define X2MAIN 0x00000400L         /*   exit-to-main-menu when sysop chat  */
#define CONCEX 0x00000800L         /*   commands concatenated -- exit fast */
#define ISX25  0x00001000L         /*   channel-is-X.25                    */
#define NOGLOB 0x00002000L         /*   don't interpret global commands    */
#define INVISB 0x00004000L         /*   user is "invisible" to others      */
#define ABOIP  0x00008000L         /*   abort output in-progress           */
#define MONALL 0x00010000L         /*   monitor all in progress            */
#define MONINP 0x00020000L         /*   monitor input in progress          */
#define ONEMIN 0x00040000L         /*   got one-min. warning of logoff     */
#define NON550 0x00080000L         /*   real hardware isn't 16550          */
#define IS1201 0x00100000L         /*   Model 16 or 4, using XECOM 1201's  */
#define ISGCDI 0x00200000L         /*   GCDI channel                       */
#define MONHID 0x00400000L         /*   Hide input from the monitor screen */
#define ISGCSU 0x00800000L         /*   user is a C/S client               */
#define WSGCSU 0x01000000L         /*   user was C/S client (now in ASCII) */
#define GCSLON 0x02000000L         /*   C/S logon routines have been called*/
#define GCSDUN 0x04000000L         /*   C/S signup acct info being recorded*/

#define NO_MESSAGE  0              /* param to byenow() for "no message"   */
#define PAMSG  -1                  /* parm to byenow() for, prf()'d already*/

                                   /* special GSBL status codes:           */
#define FSESTS       191           /* FSE status cycle code                */
#define POLSTS       192           /* poll stat code (like CYCLE, but auto)*/

#define CLOX29       230      /* btux29() call produced window-full error  */
#define ERRX29       231      /* btux29() produced some other fatal error  */
#define CYCLE        240      /* cycle-thru-other-users pseudo-status code */
#define RELOG        241      /* re-log-in pseudo-status code              */
#define CDICONN      242      /* custom interface call connected           */

struct module {                    /* module interface block               */
     CHAR descrp[MNMSIZ];          /*   description for main menu          */
     GBOOL (*lonrou)(VOID);        /*   user logon supplemental routine    */
     GBOOL (*sttrou)(VOID);        /*   input routine if selected          */
     VOID (*stsrou)(VOID);         /*   status-input routine if selected   */
     GBOOL (*injrou)(VOID);        /*   "injoth" routine for this module   */
     SHORT (*lofrou)(VOID);        /*   user logoff supplemental routine   */
     VOID (*huprou)(VOID);         /*   hangup (lost carrier) routine      */
     VOID (*mcurou)(VOID);         /*   midnight cleanup routine           */
     VOID (*dlarou)(CHAR *uid);    /*   delete-account routine             */
     VOID (*finrou)(VOID);         /*   finish-up (sys shutdown) routine   */
};

WGSEXPV(struct module**) module;

WGSEXPV(INT) nmods;                /* number of modules currently online   */

WGSEXPV(INT) conhdl;               /* handle to array of connect functions */
WGSEXPV(INT) dschdl;               /* handle to array of disconnect   "    */
WGSEXPV(INT) mcuhdl;               /* handle to array of auto-cleanup "    */
WGSEXPV(INT) hCreateAcctVecs;      /* handle to array of create-acct  "    */
WGSEXPV(INT) dlahdl;               /* handle to array of delete-acct  "    */
WGSEXPV(INT) hStartupVecs;         /* handle to array of startup      "    */
WGSEXPV(INT) finhdl;               /* handle to array of shutdown     "    */
WGSEXPV(INT) ffinhdl;              /* handle to array of final shutdown "  */
WGSEXPV(INT) s2aahdl;              /* handle to array of C/S->A/A       "  */
WGSEXPV(INT) s2cshdl;              /* handle to array of A/A->C/S       "  */
WGSEXPV(INT) annohdl;              /* handle to array of announcement   "  */

WGSEXPV(CHAR*) annomem;            /* per-request logon announcement mem.  */

struct mdstats {                   /* module statistics data structure     */
     CHAR mdname[MNMSIZ];          /*   name of module (key for btrieve)   */
     ULONG seconds;                /*   number of hours consumed in module */
     ULONG creds;                  /*   number of creds consumed in module */
#ifdef GCV2
     CHAR spare[60-33];            /*   former spare space                 */
#endif // GCV2
};

WGSEXPV(struct mdstats*) mdstats;

struct textvar {                   /* text variable structure              */
     CHAR name[TVRSIZ];            /*   name of text variable              */
     CHAR *(*varrou)(VOID);        /*   pointer to text variable function  */
};

WGSEXPV(struct textvar*) txtvars;

WGSEXPV(INT) ntvars;               /* number of text variables in memory   */

struct sysvbl {                    /* system-variable btrieve record layout*/
     CHAR key[4];                  /*   4-character dummy key of "key"     */
     CHAR dspopt[6];               /*   display options by position number */
     LONG calls[8];                /*   number of calls this month/baud rt */
     CHAR lonmsg[MTXSIZ];          /*   log-on message in effect           */
     LONG dwnlds;                  /*   total downloads to date            */
     LONG uplds;                   /*   total uploads to date              */
     LONG msgtot;                  /*   msg (E-mail/Forums) total to date  */
     USHORT emlopn;                /*   E-mail open at the moment          */
     USHORT sigopn;                /*   Forum messages open at the moment  */
     SHORT hisign;                 /*   highest Forum number used to date  */
     CHAR monmal;                  /*   id of screen to display on aux CRT */
     CHAR savmin;                  /*   Minutes to save screen             */
#ifdef GCV2
     LONG oldsec[8][24];           /*    old sec/grp/hr (now in sv3.secghr)*/
     CHAR spare[1300-1230];        /*    former spare space                */
#endif // GCV2
};
WGSEXPV(struct sysvbl) sv;

struct sysvb2 {                    /* second system variable btrieve layout*/
     CHAR ky2[4];                  /*   4-character dummy key of "ky2"     */
     USHORT matrix[NCOMTY][NAGEBK];/*   matrix of accts (computer/age)     */
#ifdef GCV2
     LONG oldcrd[8][24];           /*    old crd/grp/hr (now in sv3.crdghr)*/
#endif // GCV2
     SHORT nliniu[48];             /*   number of lines in use per hlf/hr  */
     SHORT lstzer;                 /*   date of last zeroing of stats      */
     LONG x25kps;                  /*   X.25 kilopackets sent or received  */
     USHORT x25ps;                 /*   fractional X.25 kilopackets        */
     LONG x25mbs;                  /*   X.25 megabytes sent or received    */
     LONG x25bs;                   /*   fractional X.25 megabytes          */
#ifdef GCV2
     USHORT numact;                /*   total number of user accounts      */
     USHORT numfem;                /*   number of female users             */
     USHORT numcor;                /*   number of corporate users          */
     USHORT numans;                /*   number of ANSI users               */
#else
     ULONG numact;                 /*   total number of user accounts      */
     ULONG numfem;                 /*   number of female users             */
     ULONG numcor;                 /*   number of corporate users          */
     ULONG numans;                 /*   number of ANSI users               */
#endif // GCV2
     ULONG paidpst;                /*   credits paid-for so far            */
     ULONG freepst;                /*   credits given away free so far     */
     LONG totcalls;                /*   total calls-to-date                */
     SHORT lastmcu;                /*   date of last midnight cleanup      */
#ifdef GCV2
     CHAR spare[1300-986];         /*   former spare space                 */
#endif // GCV2
};
WGSEXPV(struct sysvb2) sv2;

struct sysvb3 {                    /* third system variable btrieve layout */
     CHAR ky3[4];                  /*   4-character dummy key of "ky3"     */
     LONG secghr[NUMGRPS-1][24];   /*   seconds used (channel grp/hr)      */
     LONG crdghr[NUMGRPS-1][24];   /*   credits consumed (channel grp/hr)  */
};

WGSEXPV(struct sysvb3) sv3;

#define   UIDFND     0             /* hdluid(): found user-id              */
#define   UIDPMT    -1             /* hdluid(): uid not found: re-prompt   */
#define   UIDCAL    -2             /* hdluid(): uid not found: call again  */

WGSEXPV(INT) nterms;          /* this many simultaneous users are supported*/
WGSEXPV(INT) hichp1;          /* highest channel number in use, plus 1     */
WGSEXPV(INT) usrnum;          /* global user-number (channel) in effect    */
WGSEXPV(INT) othusn;          /* general purpose other-user channel number */
WGSEXPV(INT) uisusn;          /* uinsys() other-user channel number        */

WGSEXPV(struct user*) usrptr; /*global pointer to user data in effect      */
WGSEXPV(struct user*) othusp; /*gen purp other-user user structure ptr     */

WGSEXPV(HMCVFILE) mjrmb;      /* executive named-message file block hdl    */
WGSEXPV(HMCVFILE) supmb;      /* signup module message file block handle   */
WGSEXPV(HMCVFILE) acnmb;      /* accounting message file block handle      */

#define AUDITFILE "wgsaudit.adt"   /* audit trail file name                */
WGSEXPV(HAUDFILE) hAuditTrail; /* audit trail file handle                  */

WGSEXPV(INT*) channel;        /* array of channel codes (as displayed)     */

WGSEXPV(ULONG) lngtck;        /* 4-gig second counter (0L=server UP)       */

WGSEXPV(INT*) grpnum;         /* array of group numbers, by channel number */

WGSEXPV(CHAR) chanty[];       /* array of btusdf() codes for LAN chan grps */
WGSEXPV(CHAR) grtype[];       /* array of Group Type codes:                */
WGSEXPV(CHAR*) grtsub[];      /* array of GCDI channel type names          */
WGSEXPV(CHAR) version[];      /* main version code, in form X.YY           */
WGSEXPV(CHAR) subvers[];      /* sub-version info, ext ed rls letters      */
WGSEXPV(CHAR) echtyp[];       /* array of echo options                     */

WGSEXPV(CHAR*) startv[NUMGRPS];/* array of ptrs to startup AT-commands     */
WGSEXPV(CHAR*) mdmatz[NUMGRPS];/* array of ptrs to modem reset strings     */
WGSEXPV(CHAR*) mdmbsy[NUMGRPS];/* array of ptrs to modem busy-out stgs     */
WGSEXPV(CHAR*) mdmnan[NUMGRPS];/* array of ptrs to modem no-answer stgs    */

#define GTNONE   0            /* group type code:  No channels             */
#define GTMODEM  1            /* group type code:  Modem channels          */
#define GTMLOCK  2            /* group type code:  Locked modem channels   */
#define GTSERIAL 3            /* group type code:  Serial channels         */
#define GTX25    4            /* group type code:  X.25 channels           */
#define GTLAN    5            /* group type code:  LAN channels            */
#define GTOTHER  6            /* group type code:  GCDI channels           */

WGSEXPV(CHAR*) chantn[];      /* LAN channel type names                    */

WGSEXPV(CHAR) input[INPSIZ];  /* raw user input data buffer                */
WGSEXPV(CHAR*) margv[INPSIZ/2];/* ptrs to word starts,like argv[]          */
WGSEXPV(CHAR*) margn[INPSIZ/2];/* ptrs to word ends, for rstrin()          */
WGSEXPV(CHAR*) nxtcmd;        /* ptr to next char for command concat       */

WGSEXPV(INT) margc;           /* number of words in margv[], a la argc     */
WGSEXPV(INT) inplen;          /* overall raw input string length           */
WGSEXPV(INT) pfnlvl;          /* profanity level of current input (0-3)    */
WGSEXPV(INT) pfceil;          /* profanity-detection ceiling               */
WGSEXPV(INT) status;          /* raw status from btusts, where appropriate */
WGSEXPV(INT) shortm;          /* display short (0) or long (1) menus on x? */
WGSEXPV(INT) numcat;          /* number of concat'd commands so far        */

#define GLBMAX 50             /* max number of global command handlers     */

WGSEXPV(INT) nglobs;          /* # of global command handlers in operation */
WGSEXPF(INT,globs[GLBMAX])(VOID);/* array to glbl cmd hdlr funcs           */

WGSEXPF(VOID,hdlcon)(VOID);   /* "handle connect" function pointer         */
                              /* -- if calling this rou, don't do anything */
                              /* afterwards.  Save what's in this ptr and  */
                              /* replace it (like an interrupt handler) to */
                              /* do something special at connect time.     */
                              /* ditto for these next three:               */

WGSEXPF(VOID,hdlc25)(VOID);   /* handle incoming X.25 call stg (margv)     */
WGSEXPF(VOID,hdlnrg)(VOID);   /* handle non-RING strings during AWAITC     */
WGSEXPF(VOID,hdlrng)(VOID);   /* hdl RING(non X25)during AWAITC,HARING     */
WGSEXPF(INT,hdlcnc)(VOID);    /* hdl non-RING whatever during HARING       */
WGSEXPF(VOID,hdlrst)(VOID);   /* handle channel reset                      */
WGSEXPF(INT,gomvec)(VOID);    /* vector for cmd stg hdling in gomodl       */
WGSEXPF(VOID,loncdi)(VOID);   /* hdl logon audit trail msg-GCDI chan       */
WGSEXPF(VOID,hdlrlg)(VOID);   /* handle relogging on a new user            */
WGSEXPF(VOID,hdlzap)(VOID);   /* handle zapping an idle channel            */
WGSEXPF(INT,hdlsmp)(VOID);    /* handle sample vs paying channel           */
WGSEXPF(GBOOL,alwsup)(VOID);  /* allow new user account creation           */
WGSEXPF(GBOOL,chkauid)(CHAR *uid);/* allow proposed User-ID?               */
WGSEXPF(INT,hdlbump)(GBOOL logon);/* hdl kicking user @ logon/sup          */
WGSEXPF(VOID,shomal_hook)(VOID);/* replaceable hook into shomal            */
WGSEXPF(GBOOL,iserrf)(INT chan);/* is this channel "error free"?           */
WGSEXPF(VOID,hdlusrson)(VOID);/* terminal mode users online disp           */

WGSEXPV(jmp_buf) eximod;      /* exit-module longjmp save block            */

WGSEXPV(GBOOL) valexi;             /* is eximod currently valid?           */

#define PFBSIZ outbsz              /* size of prfbuf variable              */

WGSEXPV(INT) emubel;               /* emulation bell period                */
WGSEXPV(INT) vdasiz;               /* max size requirement of volatile data*/
WGSEXPV(CHAR*) vdarea;             /* ptr to first vda element(bkwd. comp.)*/

WGSEXPV(CHAR*) vdaptr;             /* user's pointer to volatile data area */
WGSEXPV(CHAR*) vdatmp;             /* general-purpose temp vda-size area   */
WGSEXPV(CHAR*) sysstg[];           /* system type description strings      */
WGSEXPV(CHAR*) ansstg[];           /* ANSI support flavor strings          */

WGSEXPV(UINT) syslod;              /* system loading (1 percent units)     */

WGSEXPV(ULONG) rsptim;           /* avg response time, in 1/65536 sec units*/

WGSEXPF(VOID,hangups)(VOID);       /* always call 1st on hangup vectOR     */

WGSEXPF(VOID,tjoinrou)(USHORT forum); /* teleconference JOINT routine      */
WGSEXPF(VOID,tlcInvisRou)(INT unum);  /* tele invisible chg notify routine */
WGSEXPF(VOID,ntfysopr)(CHAR *audrec); /* notify remote sysop routine       */
WGSEXPF(VOID,emlsdrou)(VOID);         /* Send Email to Sysop/ New User rou */

#define FOROFFSET 0L               // offset for forum channels in tele
#define BRDOFFSET 1000000000L      // offset for board-specific chans in tele

#define FOR2CHAN(n) ((n)+FOROFFSET) // convert forum id to channel #
#define CHAN2FOR(n) ((n)-FOROFFSET) // convert channel # to forum id
#define BRD2CHAN(n) ((n)+BRDOFFSET) // convert WL board # to channel
#define CHAN2BRD(n) ((n)-BRDOFFSET) // convert channel to WL board #

WGSEXPV(INT) nreccl;               /* number of recent calls to record     */
WGSEXPV(INT) sysrec;               /* include MASTERs in /RECENT list?     */

struct recalls {                   /* recent calls data structure          */
     USHORT logon;                 /*   logon time (packed)                */
     USHORT logoff;                /*   logoff time (packed)               */
     CHAR userid[UIDSIZ];          /*   user-id of caller                  */
};

WGSEXPV(struct recalls*) recents;  /* array of most recent callers         */

WGSEXPV(DFAFILE*) genbb;         /* generic user data file btrieve file ptr*/

struct bbsgen {               /* generic user data records for main exec   */
     CHAR userid[UIDSIZ];     /*   User-ID                                 */
     CHAR modnam[MNMSIZ];     /*   Module Name ("Main Executive")          */
     CHAR lngnam[LNGSIZ];     /*   default language name                   */
                              /*   (add fields here, default to all-0's)   */
};
#define BBSGMX "Main Executive" /* 2nd field of all "struct bbsgen" rec'ds */

WGSEXPV(CHAR*) bbsttl;        /* Title of your BBS                         */
WGSEXPV(CHAR*) company;       /* Your company name                         */
WGSEXPV(CHAR*) addres1;       /* Address                                   */
WGSEXPV(CHAR*) addres2;       /* Address                                   */
WGSEXPV(CHAR*) dataph;        /* The first phone line connected to server  */
WGSEXPV(CHAR*) liveph;        /* The first phone line reserved 4 live users*/
WGSEXPV(CHAR*) chghour;       /* Connect time charge per hour              */
WGSEXPV(CHAR*) chgmin;        /* Minimum charge                            */
WGSEXPV(CHAR*) chgtime;       /* Minimum connect time                      */
WGSEXPV(CHAR*) syskey;        /* key distinguishing sysop-types            */
WGSEXPV(CHAR*) glbkey;        /* key for "sysop" power: /l                 */
WGSEXPV(CHAR*) glbkeyi;       /* key for "sysop" power: /invis             */
WGSEXPV(CHAR*) sampky;        /* key required to log on reserved channels  */
WGSEXPV(CHAR*) mmuatr;        /* default attribute for main menu selections*/
WGSEXPV(CHAR*) ansdim;        /* dimmed attribute for main menu selections */

                              /* reset-mode                                */
#define NORMRS 0              /*   normal reset                            */
#define BUSYRS 'B'            /*   busy-out                                */
#define NANSRS 'N'            /*   no-answer                               */

WGSEXPV(INT) outbsz;          /* output buffer size per channel            */
WGSEXPV(INT) sampln;          /* number of "free sample" channels          */
WGSEXPV(INT) mmucrr;          /* Main menu credit consumption rate per min */
WGSEXPV(INT) outata;          /* output ATA to modems when answering?      */
WGSEXPV(INT) csvcrr;          /* C/S credit consumption rate per minute    */
WGSEXPV(INT) rsmode;          /* reset-mode code for channels              */
WGSEXPV(INT*) rsmodes;        /* reset-mode array by channel number        */
WGSEXPV(INT) vispsw;          /* make passwords visible in detail displays?*/
WGSEXPV(INT) maxcat;          /* maximum number of concat'd commands       */
WGSEXPV(INT) svrate;          /* how many seconds between saving sysvbls?  */
WGSEXPV(INT) lonaud;          /* make audit trail entry for each logon?    */
WGSEXPV(INT) kilipg;          /* kill-system command in progress           */

WGSEXPV(CHAR) eurmsk;         /* 0x7F if U.S.A. only, 0xFF if European     */

WGSEXPV(CHAR) btrset[80];     /* parameters we're passing to Btrieve       */

WGSEXPV(INT) multsk;          /* is a multitasker being used?              */
WGSEXPV(INT) mulmth;          /* if multitasking what method is used       */

                              /* methods used when multitasker is used     */
#define TIMER  1              /*   using alternate timer source method     */
#define COMIRP 2              /*   using COM port interrupt method         */

WGSEXPV(struct bbsgen) genbuf;/*reading Main Exec records from BBSGEN.DAT  */

VOID joint(USHORT chan);      /* teleconference entry pt for other modules */

                                   /* Signup question indexes              */
#define TBLLNG 1                   /*   language preference                */
#define TBLANS 2                   /*   can you display ANSI graphics?     */
#define TBLNAM 3                   /*   what's your real name?             */
#define TBLAD1 4                   /*   what's your address? (line 1)      */
#define TBLAD2 5                   /*   what's your address? (line 2)      */
#define TBLAD3 6                   /*   what's your address? (line 3)      */
#define TBLAD4 7                   /*   what's your address? (line 4)      */
#define TBLPHO 8                   /*   what's your phone number?          */
#define TBLSYS 9                   /*   what's your system type?           */
#define TBLBDY 10                  /*   what is your birthday?             */
#define TBLSEX 11                  /*   are you male or female?            */
#define TBLSUP 12                  /*   sysop-configurable signup questions*/
#define TBLUSE 13                  /*   use your real name as your User-ID?*/
#define TBLUID 14                  /*   what User-ID do you want to use?   */
#define ASTSIZ 15                  /*   number of entries in asktbl[]      */

/** NOTE: update these TBLx constants and asktbl[][] in SIGNUP.C in sync  **/
WGSEXPV(INT) asktbl[][3];          /* table of signup question parameters  */

                                   /* user information edit key indexes    */
#define UIEKYNAM 0                 /*   first and last names               */
#define UIEKYCOM 1                 /*   company name                       */
#define UIEKYADR 2                 /*   address                            */
#define UIEKYPHO 3                 /*   phone number                       */
#define UIEKYSYS 4                 /*   system type                        */
#define UIEKYANS 5                 /*   ANSI preference                    */
#define UIEKYSCW 6                 /*   screen width                       */
#define UIEKYSCL 7                 /*   screen height                      */
#define UIEKYEDT 8                 /*   editor preference                  */
#define UIEKYPAU 9                 /*   screen pause setting               */
#define UIEKYSEX 10                /*   sex                                */
#define UIEKYPSW 11                /*   password                           */
#define UIEKYTSZ 12                /*   number of entries in uiekytbl[]    */

/* NOTE: update these UIEKYxxx constants and uiekytbl[] in UINFED.C in sync */
WGSEXPV(CHAR*) uiekytbl[];         /* table of user information edit keys  */

#define HASUIEKEY(i) (uiekytbl[i] != NULL && haskey(uiekytbl[i]))
                   /* wrapper macro to check if user has key in uiekytbl[] */

#define   SUPBEG    0              /* morsup() starting state              */
#define   DUNINS    999            /* morsup() return state for all done   */

WGSEXPV(INT) sgnusz;          /* maximum size of user-ids for new signups  */
WGSEXPV(INT) safpsw;          /* can a User-Id or "password" be a password */
WGSEXPV(INT) digalw;          /* digits allowed in User-IDs?               */
WGSEXPV(INT) fulalw;          /* full names allowed as User-IDs?           */
WGSEXPV(INT) namdft;          /* how do you handle user-ids?               */
WGSEXPV(INT) minuid;          /* minimum allowable User-ID size            */
WGSEXPV(INT) minpwd;          /* minimum allowable users password size     */
WGSEXPV(INT) shwcrd;          /* show user how many credits they have?     */

WGSEXPV(CHAR*) langchg;            /* key required to change language pref */

typedef
GBOOL                              /*   returns TRUE when done             */
AUTOSENSE(                         /* Autosensor routine type              */
UINT snccon,                       /*   since connect, 1/16 sec (see note) */
CHAR *incbuf,                      /*   bytes coming in (not NUL term)     */
INT nbytes);                       /*   number of bytes coming in          */

         /* NOTE: the snccon parameter will always be 0 when initiating an */
         /* autosensing session, and always at least 1 thereafter.         */

typedef
VOID
VOIDFUNC(VOID);                    /* void function type                   */

typedef
VOID
CREATEACCOUNT(                     /* create account notification function */
const struct usracc* pAcct);            /*   completed user account info        */

WGSEXPV(CHAR*) poslng;             /* possible languages autosensed        */
WGSEXPV(USHORT*) austim;           /* array[nterms] of the time of bgnaus()*/
WGSEXPV(INT) numcand;              /* # of candidates -- cntcand() ret val */
WGSEXPV(INT) fstcand;              /* first candidate -- cntcand() ret val */
WGSEXPV(CHAR) maxcand;             /* best candidate  -- cntcand() ret val */
WGSEXPV(USHORT) auswait;           /* master timeout, 1/16 of second units */
WGSEXPV(INT) numaus;               /* number of autosense handlers         */

#define LONOK  0                   /* chkuid(): user can log on, passw next*/
#define LONALR 1                   /* chkuid(): user logged on already     */
#define LONDBT 2                   /* chkuid(): doesn't have SAMPKY key    */
#define LONSUS 3                   /* chkuid(): user suspended             */
#define LONUNK 4                   /* chkuid(): User-ID not on file        */
#define LONAPP 5                   /* chkuid(): app-specific rejection     */
#define LONOCK 6                   /* chkuid(): user log on, knocking other*/

#define CSLONOK     0              /* cschkuid(): user can log on, psw next*/
#define CSLONBYE    1              /* cschkuid(): invalid logon, kick off  */
#define CSLONPASS   2              /* cschkuid(): invalid password, retry  */
#define CSLONKNOCK  3              /* cschkuid(): already online, knock?   */

WGSEXPF(INT,chkuid)(CHAR *userid);/* vector for approving User-ID */
WGSEXPF(INT,chkpsw)(CHAR *psword);/* vector for approving password*/
WGSEXPF(INT,cschkuid)(const CHAR *userid,const CHAR *password);
                                   /* C/S approve User-ID function         */
WGSEXPF(GBOOL,cschkpsw)(const CHAR *password); /* C/S aprv psword */
WGSEXPF(INT,chkacc)(VOID);         /* handle final accounting of logon  */
WGSEXPF(GBOOL,vallon)(VOID);       /* vector for final logon validation */
WGSEXPF(GBOOL,reqpsw)(VOID);       /* password required?              */
WGSEXPF(VOID,greet)(VOID);         /* welcome online                  */
WGSEXPF(VOID,uidpmt)(VOID);        /* send userid prompt              */
WGSEXPF(VOID,setpfn)(CHAR *inp);   /* profanity checker routine    */
WGSEXPF(GBOOL,oesrou)(INT unum);   /* vector for BYEBYE disconnect */

WGSEXPF(VOID,syscyc)(VOID);        /* system-cycle vector (tail is prctask())*/
WGSEXPF(VOID,chncyc)(VOID);        /* channel-cycle vector (tail is dwopr()) */

WGSEXPV(INT) inpolr;               /* usrnum of user in polrou (or -1)     */
WGSEXPV(INT) lstunm;               /* last user-number returned by btuscn()*/
WGSEXPV(INT) newunm;               /* new userno just ret'd by btuscn()    */

WGSEXPV(INT) actdet;               /* activity detected in this chan cycle */

#define sptrak {sftrak=__FILE__;sltrak=__LINE__;} /* tracking source posit */
WGSEXPV(INT) sltrak;               /* source line tracking                 */
WGSEXPV(CHAR*) sftrak;             /* source file tracking                 */

WGSEXPV(LONG) mxbaudl[];           /* max baud rates, by chan grp as longs */

/* return values for incusr() if user is rejected (besides VACANT)         */
#define ISCURU -1                  /* this is the current user             */
#define UIDNGD -2                  /* channel active, but invalid User-ID  */
#define INVSON -3                  /* INVISB flag is on                    */

struct dllmod {                    /* note: structure also in PROTSTUF.C   */
     CHAR filnam[9];               /*   DLL filename (less extension)      */
     INT handle;                   /*   DLL handle (when loaded)           */
};

WGSEXPV(struct dllmod*) dlls;

WGSEXPV(INT) maxdlls;              /* maximum # of dlls without reallocing */
WGSEXPV(INT) numdlls;              /* # of dlls in "dlls" array            */
WGSEXPV(INT) curdlls;              /* # of dlls currently loaded           */


/* MAJORBBS.C */
WGSEXP VOID ckrsch(VOID);
WGSEXP VOID globalcmd(INT (*rouptr)());
WGSEXP VOID rtihdlr(VOID (*rouptr)(VOID));
WGSEXP VOID xltctls(CHAR *txtbuf);
WGSEXP INT usridx(INT chan);
WGSEXP VOID begin_polling(INT unum,VOID (*rouptr)());
WGSEXP VOID stop_polling(INT unum);
WGSEXP VOID hook_connect(VOID (*conrou)(VOID));
WGSEXP VOID hook_disconnect(VOID (*dscrou)(VOID));
WGSEXP VOID hook_cleanup(VOID (*mcurou)(VOID));
WGSEXP VOID hook_createacct(CREATEACCOUNT *crarou);
WGSEXP VOID hook_delacct(VOID (*dlarou)(CHAR *userid));
WGSEXP VOID hook_startup(VOIDFUNC *begrou);
WGSEXP VOID hook_shutdown(VOID (*finrou)(VOID));
WGSEXP VOID hook_finalshutdown(VOID (*ffinrou)(VOID));
WGSEXP VOID hook_swt2aa(VOID (*s2aarou)(VOID));
WGSEXP VOID hook_swt2cs(VOID (*s2csrou)(VOID));
WGSEXP VOID hook_announce(VOID (*annorou)(VOID));
WGSEXP VOID dovecs(INT vechdl);
WGSEXP INT register_textvar(const char *name,CHAR *(*varrou)());
WGSEXP INT findtvar(CHAR *name);
WGSEXP INT register_module(struct module *mod);
WGSEXP INT findmod(CHAR *name);
WGSEXP VOID dclvda(INT size);
WGSEXP VOID alcvda(VOID);
WGSEXP CHAR *vdaoff(INT unum);
WGSEXP VOID rcdbaud(LONG baud);
WGSEXP VOID powprf(VOID);
WGSEXP INT bdspec(VOID);
WGSEXP VOID updcal(VOID);
WGSEXP VOID kiletc(CHAR *legend);
WGSEXP VOID othtrm(VOID);
WGSEXP VOID condex(VOID);
WGSEXP INT dftuid(CHAR *userid);
WGSEXP INT dftpsw(CHAR *psword);
WGSEXP INT dftacc(VOID);
WGSEXP VOID usrflags(VOID);
WGSEXP GBOOL dftlon(VOID);
WGSEXP INT lngswt(VOID);
WGSEXP VOID injacr(VOID);
WGSEXP VOID clrinp(VOID);
WGSEXP INT sampok(VOID);
WGSEXP VOID hdlinp(VOID);
WGSEXP GBOOL uidxst(const CHAR *uid);
WGSEXP CHAR *uidCaps(CHAR *uid);
WGSEXP VOID clrxrf(VOID);
WGSEXP VOID addxrf(CHAR *newuid);
WGSEXP VOID delxrf(CHAR *userid);
WGSEXP INT hdluid(CHAR *stg);
WGSEXP VOID delgen(const CHAR *userid);
WGSEXP INT getgen(struct bbsgen *genbuf,CHAR *userid);
WGSEXP VOID setgen(struct bbsgen *genbuf);
WGSEXP INT onsys(const CHAR *uid);
WGSEXP INT onsysn(const CHAR *uid,GBOOL invis);
WGSEXP INT uinsys(const CHAR *uid);
WGSEXP INT onbbs(const CHAR *uid,GBOOL invis);
WGSEXP INT instat(const CHAR *uid,INT qstate);
WGSEXP INT fmtx3(CHAR *prmstg);

WGSEXP CHAR *                      /*   returns empty string               */
catfix1(VOID);                     /* global default catastro() txt, part 1*/

WGSEXP VOID prepff(VOID);
WGSEXP VOID ckmcu(VOID);
WGSEXP VOID zapdec(VOID);
WGSEXP GBOOL absdtdy(VOID);
WGSEXP VOID midnit(VOID);
WGSEXP VOID mjrdla(CHAR *userid);
WGSEXP CHAR *getin(VOID);
WGSEXP VOID parsin(VOID);
WGSEXP VOID paccin(VOID);
WGSEXP VOID paccit(VOID);
WGSEXP VOID dftpfn(CHAR *inp);
WGSEXP VOID rstrin(VOID);
WGSEXP VOID chkdft(CHAR c);
WGSEXP CHAR getdft(VOID);
WGSEXP VOID byenow(INT msgnum,...);
WGSEXP VOID byendl(INT msgnum,...);
WGSEXP VOID setbbye(VOID);
WGSEXP VOID imdrop(VOID);
WGSEXP LONG lincst(INT unum);
WGSEXP VOID rstchn(VOID);
WGSEXP VOID rstx25(CHAR *dspstg,CHAR dspc);
WGSEXP VOID rstlan(INT ishard);
WGSEXP VOID rstcdi(INT ishard);
WGSEXP INT bbsfvc(CHAR *chtype);
WGSEXP INT numcdi(CHAR *chtype);
WGSEXP INT numliccdi(CHAR *chtype);
WGSEXP INT ningrp(INT group);
WGSEXP INT numonl(INT state);
WGSEXP INT bbscon(INT unum);
WGSEXP VOID bbsdsc(INT unum);
WGSEXP VOID rstrxf(VOID);
//WGSEXP ULONG hrtval(VOID);
WGSEXP INT hpkrou(INT chan,CHAR c);
WGSEXP VOID stansi(VOID);
WGSEXP VOID echon(VOID);
WGSEXP VOID echonu(INT usrnum);
WGSEXP VOID echsec(CHAR ech,INT lwidth);
WGSEXP INT injoth(VOID);
WGSEXP VOID dftinj(VOID);
WGSEXP VOID lonstf(VOID);
WGSEXP VOID nxtlon(VOID);
WGSEXP VOID audlon(VOID);
WGSEXP VOID bgnlof(VOID);
WGSEXP VOID nxtlof(VOID);
WGSEXP GBOOL mainlon(VOID);
WGSEXP GBOOL mainu(VOID);
WGSEXP VOID curusr(INT uno);
WGSEXP VOID usrson(VOID);
WGSEXP INT incusr(INT unum,GBOOL iginv,GBOOL inccur);
WGSEXP INT glorys(VOID);
WGSEXP INT glorec(VOID);
WGSEXP VOID glolok(VOID);
WGSEXP VOID gloinv(VOID);
WGSEXP VOID musthn(VOID);
WGSEXP VOID dfsthn(VOID);
WGSEXP CHAR *getMsgBlk(INT msgnum);
WGSEXP VOID kiloop(VOID);
WGSEXP VOID bootem(CHAR *who);
WGSEXP VOID kilchn(INT num);
WGSEXP VOID loscar(VOID);
WGSEXP VOID addannom(CHAR *message,CHAR *appid,CHAR *cmdstg);
WGSEXP VOID addanno(CHAR *message);
WGSEXP VOID dclanno(INT size);
WGSEXP VOID aschup(VOID);
WGSEXP VOID hupall(VOID);
WGSEXP VOID mjrfin(VOID);

WGSEXP VOID
initmsg(
USHORT size);

WGSEXP VOID
freekey(VOID); /* free usrptr->keys */

#ifdef GCV2
WGSEXPV(struct user*) user;        /* global array of user data            */
#define usroff(n) (&user[n])
#else
WGSEXP struct user *                      /*   returns ptr to user structure      */
usroff(                            /* obtains the user struct at an offset */
INT usrnum);                       /*   offset to use                      */
#endif // GCV2

/* PAGE.C */
WGSEXP VOID initPaging(VOID);
WGSEXP VOID pageLogon(VOID);
WGSEXP VOID pageHup(VOID);
WGSEXP VOID pageDel(CHAR *uid);
WGSEXP VOID pageLoadRecord(const CHAR* userid, struct pageInfo* pageptr);
WGSEXP VOID pageSaveRecord(const CHAR* userid, struct pageInfo* pageptr);

/* MENUING.C */
WGSEXP VOID inimnu(VOID);
WGSEXP INT iniarip(VOID);
WGSEXP INT globalgo(VOID);
WGSEXP GBOOL xitmod(VOID);
WGSEXP VOID enapag(CHAR *pagnam);
WGSEXP VOID dispag(CHAR *pagnam);
WGSEXP VOID bgnfnd(VOID);
WGSEXP VOID cntfnd(VOID);
WGSEXP VOID chk4mtch(VOID);
WGSEXP VOID abtfnd(VOID);
WGSEXP INT gopage(CHAR *pagnam,INT lngmnu,INT reting);
WGSEXP INT gomodl(VOID);
WGSEXP INT entmdl(INT modnum,CHAR *cmdstg);
WGSEXP INT gomutl(VOID);
WGSEXP INT gocond(VOID);
WGSEXP INT gomenu(INT lngmnu);
WGSEXP INT gofile(VOID);
WGSEXP VOID dspmnu(INT lngmnu);
WGSEXP struct usrmnu *mnuoff(INT unum);
WGSEXP VOID redolocks(INT inserted);
WGSEXP INT opnans(CHAR *filnam);
WGSEXP INT opfile(CHAR *filnam);
WGSEXP INT rdfile(VOID);
WGSEXP VOID clfile(VOID);
WGSEXP VOID xltmnu(CHAR *buffer);
WGSEXP CHAR *xlttxv(CHAR *buffer,INT size);
WGSEXP INT grbtxv(CHAR *buffer);
WGSEXP INT selnum(CHAR selchr);
WGSEXP INT pagstt(CHAR *pagnam);
WGSEXP CHAR *pagcstg(CHAR *pagnam);
WGSEXP VOID clsmnu(VOID);
/* OPRLOW.C */
WGSEXP VOID inilopr(INT mxscn,INT auxena);
WGSEXP VOID endlopr(VOID);
WGSEXP CHAR *actvscn(INT scnhdl);
WGSEXP CHAR *actvscnsp(INT scnhdl,INT x1,INT y1,INT x2,INT y2,INT scr);
WGSEXP VOID updbckgnd(VOID);
WGSEXP VOID conupd(VOID);
WGSEXP VOID occhdl(VOID);
WGSEXP UINT keyhit(UINT scan);
WGSEXP VOID scngoaway(INT scnhdl);
WGSEXP VOID scn2mai(INT scnhdl);
WGSEXP VOID scn2aux(INT scnhdl);
WGSEXP VOID mai2aux(VOID);
WGSEXP VOID shobox(INT w,INT sho);
WGSEXP VOID unsavscns(VOID);
WGSEXP VOID savscns(VOID);
WGSEXP VOID memswap(CHAR *source,CHAR *dest,INT length);
#ifdef GCV2S
INT baudat(UINT baud,INT blink);
#define baudat(baud,blink) baudat((UINT)(baud),(blink))
#else
WGSEXP INT baudat(ULONG baud,INT blink);
#endif // GCV2S
WGSEXP VOID cls(CHAR *buf,INT atr);
WGSEXP CHAR *dbytes(ULONG bytes);
/* SIGNUP.C */
WGSEXP VOID inisup(VOID);
WGSEXP INT signup(VOID);
WGSEXP INT uinfok(INT pmtmsn,INT minlen,INT maxsiz,CHAR *stgptr);
WGSEXP INT unumok(INT pmtmsn,INT minnum,INT maxnum,INT *number);
WGSEXP INT udatok(INT pmtmsn,CHAR *stgptr);
WGSEXP INT okbday(CHAR *stg);

WGSEXP INT
calcage(                           /* compute age (in years) as of today   */
const CHAR *birthd);               /*   birth date (YYYYMMDD or MM/DD/YY)  */

WGSEXP GBOOL                       /*   returns TRUE if modified           */
fixBirthdate(                      /* fix date from MM/DD/YY to YYYYMMDD   */
CHAR *strDate);                    /*   birth date string (must be DATSIZ) */

WGSEXP const CHAR *                /*   returns pointer to static buffer   */
strBirthdate(                      /* format birthdate into "MM/DD/YYYY"   */
const CHAR *strDate);              /*   birth date string                  */

WGSEXP INT usexok(VOID);
WGSEXP VOID lnglist(INT all);
WGSEXP VOID lngfoot(INT all);
WGSEXP INT valuid(CHAR *stg);
WGSEXP VOID stripb(CHAR *stg);
WGSEXP VOID makhdl(CHAR *stg);
WGSEXP VOID zonkhl(CHAR *stg);
WGSEXP INT isuplo(CHAR *stg);
WGSEXP INT loadup(VOID);
WGSEXP GBOOL loadacc(const CHAR *userid);
WGSEXP VOID dftans(CHAR dft);
WGSEXP VOID shwusr(struct usracc* usaptr);
WGSEXP VOID finsup(VOID);
WGSEXP GBOOL valpsw(CHAR *psw);
WGSEXP GBOOL valupsw(CHAR *uid,CHAR *psw);
WGSEXP INT issupc(INT c);
WGSEXP VOID supdfts(VOID);
WGSEXP INT morsup(INT supstt);
WGSEXP VOID abosup(INT supstt);
WGSEXP VOID endsup(VOID);
WGSEXP VOID supcyc(VOID);
WGSEXP VOID suphup(VOID);
WGSEXP VOID cntsup(VOID);
/* CNCUTL.C */
WGSEXP VOID bgncnc(VOID);
WGSEXP INT endcnc(VOID);
WGSEXP CHAR cncchr(VOID);
WGSEXP INT cncint(VOID);
WGSEXP LONG cnclon(VOID);
WGSEXP CHAR *cncuid(VOID);
WGSEXP CHAR *cncsig(VOID);
WGSEXP CHAR cncyesno(VOID);
WGSEXP CHAR *cncwrd(VOID);
WGSEXP CHAR *cncbgw(CHAR *buffer,INT sizbuf);
WGSEXP CHAR *cncall(VOID);
WGSEXP CHAR morcnc(VOID);
WGSEXP INT cnchex(VOID);
WGSEXP CHAR *cncnum(VOID);
WGSEXP INT cnclng(VOID);
/* ACCSCN.C */
WGSEXP VOID actrep(VOID);
WGSEXP VOID actdis(VOID);
WGSEXP UINT actkey(UINT scncod);
/* AUDIT.C */
WGSEXP VOID audrep(VOID);
WGSEXP VOID auddis(VOID);
WGSEXP UINT audkey(UINT scncod);

WGSEXP VOID
audFinDisp(VOID);                  /* finish disp of audit trail at startup*/

WGSEXP ULONG                       /*   record # or NOENTRIES              */
audLastRec(VOID);                  /* get # of last record in audit trail  */

WGSEXP VOID
audGetEntry(                       /* read an entry from the audit trail   */
ULONG recNum,                      /*   record number to get               */
struct audOldStyle *buf);          /*   buffer to receive entry            */

/* EMULATE.C */
WGSEXP VOID emulupd(VOID);
WGSEXP UINT emulkey(UINT scncod);
WGSEXP VOID oprmks(INT chr);
WGSEXP VOID emuchn(INT chn2em);
WGSEXP VOID emuset(INT chn2em);
WGSEXP VOID emdisp(CHAR *stg);
WGSEXP VOID lvchat(VOID);
WGSEXP VOID winupdt(VOID);
/* MONITOR.C */
WGSEXP UINT monkey(UINT scncod);
WGSEXP VOID monrep(VOID);
WGSEXP VOID mondis(VOID);
WGSEXP VOID shomal(VOID);
/* SUMMARY.C */
WGSEXP VOID sumocc(VOID);
WGSEXP UINT sumkey(UINT scncod);
WGSEXP VOID softgroup(VOID);
WGSEXP VOID squiet(VOID);
WGSEXP VOID sseldsp(VOID);
WGSEXP VOID smsgdsp(VOID);
WGSEXP VOID sscnsav(VOID);
WGSEXP VOID skill(VOID);
WGSEXP VOID sentmin(VOID);
#ifdef UNIX
VOID sunxscr(VOID);
#else
WGSEXP VOID sauxcrt(VOID);
#endif
WGSEXP VOID scklmod(VOID);
WGSEXP VOID ssndac(VOID);
WGSEXP VOID sentamt(VOID);
WGSEXP VOID sentapf(VOID);
WGSEXP VOID sentuid(VOID);
WGSEXP VOID dwtxte(VOID);
WGSEXP VOID sselpos(VOID);
WGSEXP VOID sinpchn(VOID);
WGSEXP VOID sinpch2(VOID);
WGSEXP VOID sumrep(VOID);
WGSEXP VOID sumdis(VOID);
WGSEXP VOID inisho(VOID);
WGSEXP VOID inisho2(VOID);
WGSEXP VOID finsho(VOID);
WGSEXP VOID dwopr(VOID);
WGSEXP VOID iniaud(VOID);

WGSEXP VOID
shocst(                            /* display text in audit trail          */
const CHAR *brief,                 /*   brief desc. of audit trail entry   */
const CHAR *detail,                /*   detailed description               */
...);                              /*   variable parameters                */

WGSEXP VOID scroat(INT dirct);
WGSEXP VOID shochn(CHAR *legend);
WGSEXP VOID shochb(CHAR *legend,INT blink);
WGSEXP VOID shochl(CHAR *legend,CHAR sing,INT attr);
WGSEXP VOID loadgph(INT min);
WGSEXP INT linsusd(VOID);
WGSEXP VOID doaditbx(VOID);
WGSEXP VOID quiesk(INT blk);
WGSEXP VOID zappo(VOID);
WGSEXP VOID plosk(INT sktnum);
WGSEXP VOID zapskl(VOID);
WGSEXP VOID lblsk(INT sknum,CHAR *lblstg);
WGSEXP VOID acckey(VOID);
WGSEXP VOID bckspc(VOID);
WGSEXP VOID hdlskm(CHAR *echstg,INT opistt);
WGSEXP VOID hdlskc(INT opistt);
WGSEXP VOID hdlsk(CHAR *echstg,INT opistt);
WGSEXP VOID retkey(VOID);
WGSEXP VOID auxups(CHAR snum);
WGSEXP VOID collap(VOID);
WGSEXP VOID fupkil(VOID);
WGSEXP VOID snd2ch(INT chan,CHAR *text);
WGSEXP VOID snd2al(CHAR *text);
WGSEXP VOID dftbel(INT local);
WGSEXP VOID savdisp(VOID);
WGSEXP CHAR *chlpfn(VOID);
WGSEXP VOID psmatm(VOID);
WGSEXP VOID psmatms(CHAR *pagmsg);

WGSEXP VOID
sendSysopPage(                     /* send sysop page to main console      */
const CHAR *user,                  /*  user to send message                */
const CHAR *pagmsg);               /*  message to send                     */

WGSEXP VOID
sendConsole(                       /* send page message DOS style console  */
const CHAR *pagmsg);               /*  formatted message to send           */

/* USERS.C */
WGSEXP UINT usskey(UINT scncod);
WGSEXP VOID ussrep(VOID);
WGSEXP VOID ussocc(VOID);
WGSEXP VOID ussdis(VOID);
WGSEXP VOID updbank(INT bnk);
WGSEXP VOID usrchl(VOID);
WGSEXP VOID usrchan(INT chan);
/* ABOUT.C */
WGSEXP UINT abokey(UINT scncod);
WGSEXP VOID aborep(VOID);
/* LOCAL.C */
WGSEXP VOID lsesupd(VOID);
WGSEXP UINT lseskey(UINT scncod);
WGSEXP VOID oprmk2(INT chr);
WGSEXP VOID entlse(INT chn2em);
/* PLBBS.C */
WGSEXP VOID callinits(VOID);
WGSEXP VOID setbparm(VOID);
/* EMULATE.C */
WGSEXP VOID entcht(VOID);
/* AUTSNS.C */
WGSEXP VOID iniaus(VOID);
WGSEXP VOID regautsns(AUTOSENSE *aushdl);
WGSEXP GBOOL bgnaus(GBOOL foreal);
WGSEXP GBOOL prcaus(VOID);
WGSEXP VOID setbyprot(CHAR *prot,CHAR value);
WGSEXP INT cntcand(VOID);
WGSEXP INT lngposn(INT chc);
/* BBSRIP.C */
WGSEXP VOID inirmdl (VOID);
WGSEXP VOID ripcls (VOID);
/* DBGMEM.C */
WGSEXP VOID dbgohf(VOID);
WGSEXP VOID dbgchf(VOID);
/* MNUUTL.C */
WGSEXP VOID unpack(struct mnupag *menupage);
WGSEXP VOID repack(struct mnupag *menupage);
WGSEXP VOID savepage(struct mnupag *menupage,GBOOL insert);

WGSEXP VOID
updclk(VOID);                      /* updates system clock                 */

EXPGSBL VOID
locchn(                            /* setup local session channel for GCDI */
INT chan);                         /*   channel number for session         */

WGSEXP VOID
aboutos(VOID);                     /* print OS specific data on about scrn */

WGSEXP VOID
wginit(VOID);                      /* OS specific start up routine for WG  */

#ifdef GCWINNT
WGSEXP GBOOL                              /*   returns TRUE if run as a service   */
isRunAsService(VOID);              /* is WGSERVER.EXE running as a service */

WGSEXP VOID
shutdownMainThread(VOID);          /* shuts down main thread and WG Server */

#endif // GCWINNT

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __MAJORBBS_H                         */
