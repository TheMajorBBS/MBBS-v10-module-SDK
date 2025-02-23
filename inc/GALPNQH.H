/***************************************************************************
 *                                                                         *
 *   GALPNQH.H                                                             *
 *                                                                         *
 *   Copyright (c) 1993-1997 Galacticomm, Inc.  All Rights Reserved.       *
 *                                                                         *
 *   This is the Polls and Questionnaires header file.                     *
 *                                                                         *
 *                                 - M. Timothy Stark 10/01/93             *
 *                                                                         *
 ***************************************************************************/

#ifndef __GALPNQH_H
#define __GALPNQH_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT
#   ifdef __BUILDGALPNQ
#       define PNQEXP           EXPORT
#       define PNQEXPV(x)       EXPORT_VARIABLE(x)
#       define PNQEXPF(x,y)     EXPORT_FUNCTION(x, y)
#   else
#       define PNQEXP           IMPORT
#       define PNQEXPV(x)       IMPORT_VARIABLE(x)
#       define PNQEXPF(x,y)     IMPORT_FUNCTION(x, y)
#   endif // __BUILDWGSERVER
#else
#   define PNQEXP
#   define PNQEXPV(x)           extern x           
#   define PNQEXPF(x,y)         extern x (* y)
#endif // __GCWINNT

#define PQAPPID   "GALPNQ"    /* polls and questionnaires App-ID           */
#define PNAMELEN        26    /* poll name length                          */
#define PDESCLEN        40    /* poll description length                   */
#define KEYLEN          16    /* key field length                          */
#define VALLEN           4    /* dynapak value length for copy buffer      */
#define STRSIZ         240    /* string size for temporary string area     */
#define POLLSPERPG      16    /* number of polls to list per page          */
#define ANSPERPG        15    /* number of answers per page in answer list */
#define TXTSIZ        2000    /* size of text buffer for questions         */
#define PTHFILSIZ       50    /* size of text buffer for path and file name*/
#define FILESIZ         13    /* size of a file                            */
#define MSGSIZ        1024    /* max size of message area                  */
#define ANSSIZ        1000    /* size of text buffer for answer            */
#define MAXASTGS        16    /* maximum number of answer strings          */
#define ANSSTGLEN       65    /* answer string length                      */
#define MAXQUES        100    /* maximum number of questions per poll      */
#define MAXCYCS          3    /* maximum QEQ's per cycle for listing       */
#define MXLWID          80    /* maximum label width                       */
#define MAXWHEEL         7    /* maximum frames in wheel animation         */
#define MAXPARAM        16    /* maximum number of answer parameters       */
#define RESUSRS2        -1    /* substate place holder                     */
#define MAXLENCC        20    /* maximum length of a credit card entry     */
#define MINLENCC        13    /* minimum length of a credit card entry     */
#define PFNTSTY "|Y00000100"  /* poll font style                           */
#define PBUTSTY "|1B00000201EQ010E000F080700000F07000000" /* button style  */
#define QFNTSTY "|Y000002LD"  /* question font style                       */
#define QBUTSTY "|1B0P0I0201EQ01010F0F080700000F0700000P" /* button style  */

/* question types                                                          */
#define CREDIT           1    /* credit card number question type          */
#define DATE             2    /* date question type                        */
#define DISONLY          3    /* display only question type                */
#define MULTICHC         4    /* multiple choice question                  */
#define NUMERIC          5    /* numeric question type                     */
#define OPEN_ENDED       6    /* open ended response question type         */
#define TRUEFALSE        7    /* true/false question type                  */
#define YESNO            8    /* yes/no question type                      */
#define USERACCT         9    /* user account question type                */

#define OK2TALLY(qt) ((qt) == MULTICHC || (qt) == TRUEFALSE || (qt) == YESNO)
                              /* is it ok to tally this question?          */
                              /* to support case where Sysop creates a
                                 questionnaire and then makes it a poll    */

#define SHOW             1    /* show poll to user regardless of key       */
#define DIM              2    /* dim poll to user without proper key       */
#define HIDE             3    /* hide poll from user without proper key    */

#define SKIP             1    /* skip logon process altogether             */
#define ANNOUNCE         2    /* announce new poll to user                 */
#define ASK              3    /* ask user to take this poll now            */
#define INSIST           4    /* insist user takes this poll               */

/* define poll types                                                       */
#define POLL             1    /* tallies results (doesn't allow open-ended */
                              /*   answer types though)                    */
#define QUEST            2    /* doesn't tally results (although it can    */
                              /*   save a user's answers for lookup) and   */
                              /*   allows all answer types                 */

/* define temp user flags                                                  */
#define LONMODE          1    /* user is in the logon input handler rou.   */
#define MORELIST         2    /* RETURN will continue listing display      */
#define INSISTDUN        4    /* during logon, no more insist polls        */
#define ASKDUN           8    /* during logon, no more ask polls           */
#define HASSLE          16    /* was user hassled during logon process?    */
#define REVERSE         32    /* search in reverse mode                    */
#define FNDFIRST        64    /* have found the first results record       */
#define ADDRESP        128    /* insert open ended response data           */

/* poll flags                                                              */
#define   DISBRANCH      1    /* discard branching answers                 */
#define   SPARE          2    /* spare flag (reserved for future use)      */
#define   EDITP          4    /* poll is currently being edited            */
#define   ADDP           8    /* poll is currently being added             */
#define   CLRDFLT       16    /* default all questions to clear screen?    */
#define   DELETEP       32    /* poll has been tagged for deletion         */

/* question flags                                                          */
#define   BRANCH         1    /* this question contains branching          */
#define   EXMPT          2    /* exempt answer from data storage           */
#define   EDITQ          4    /* question is being edited                  */
#define   CLRSCN         8    /* clear screen before this question         */

/* data storage type definitions                                           */
#define BTRIEVE          1    /* store answers to BTRIEVE data file        */
#define ASCII            2    /* store answers to an ASCII file            */
#define BOTH             3    /* store answers to both ASCII and BTRIEVE   */
#define DISCARD          4    /* do not store answers                      */

#define ONCE             1    /* only allow user to answer once            */
#define REPLACE          2    /* replace previous answers                  */
#define ACCUMULATE       3    /* accumulate answers                        */

#define UACSYS           1    /* user has sysop access                     */
#define UACPO            2    /* user has poll-op access                   */

struct timedata {                  /* time/date poll mod structure         */
     CHAR pname[PNAMELEN];         /* Name of the poll                     */
     USHORT cofdat;                /* Compressed format date               */
     USHORT now;                   /* time of last mod                     */
};

struct polldata {                  /* master poll data structure           */
     CHAR pname[PNAMELEN];         /* poll name                            */
     CHAR pdesc[PDESCLEN];         /* poll description                     */
     SHORT polltype;               /* poll type POLL=1 QUES=2              */
     SHORT priority;               /* poll priority 0=SKIP 1=ANNOUNCE      */
                                   /* 2=ASK 3=INSIST                       */
     SHORT data;                   /* data storage method array element    */
                                   /* 0/1=BTRIEVE 2=ASCII 3=BOTH 4=NONE    */
     SHORT answer;                 /* 0/1=ONCE 2=REPLACE 3=ACCUMULATE      */
     USHORT createdate;            /* date poll was created                */
     USHORT closedate;             /* date to close this poll              */
     CHAR lookup_key[KEYLEN];      /* key required to look up answers      */
     CHAR logon_key[KEYLEN];       /* key required to get logon option     */
     CHAR acc_key[KEYLEN];         /* key required to answer poll          */
     SHORT acc_attr;               /* access display attribute             */
     CHAR res_key[KEYLEN];         /* key required to view results         */
     CHAR grant_key[KEYLEN];       /* key to grant users that complete     */
     CHAR grant_class[KEYLEN];     /* class to grant users that complete   */
     LONG grant_crd;               /* credits to grant users that complete */
     CHAR grant_file[GCSTRPTH];    /* file to grant users that complete    */
     SHORT flags;                  /* poll flags                           */
};

struct vbpdata {                   /* VB style poll data structure         */
     CHAR pname[PNAMELEN];         /* poll name                            */
     CHAR pdesc[PDESCLEN];         /* poll description                     */
     SHORT polltype;               /* poll type POLL=1 QUES=2              */
     SHORT priority;               /* poll priority 0=SKIP 1=ANNOUNCE      */
                                   /* 2=ASK 3=INSIST                       */
     SHORT data;                   /* data storage method array element    */
                                   /* 0/1=BTRIEVE 2=ASCII 3=BOTH 4=NONE    */
     SHORT answer;                 /* 0/1=ONCE 2=REPLACE 3=ACCUMULATE      */
     DOUBLE createdate;            /* date poll was created                */
     DOUBLE closedate;             /* date to close this poll              */
     CHAR lookup_key[KEYLEN];      /* key required to look up answers      */
     CHAR logon_key[KEYLEN];       /* key required to get logon option     */
     CHAR acc_key[KEYLEN];         /* key required to answer poll          */
     SHORT acc_attr;               /* access display attribute             */
     CHAR res_key[KEYLEN];         /* key required to view results         */
     CHAR grant_key[KEYLEN];       /* key to grant users that complete     */
     CHAR grant_class[KEYLEN];     /* class to grant users that complete   */
     LONG grant_crd;               /* credits to grant users that complete */
     CHAR grant_file[PTHFILSIZ];   /* file to grant users that complete    */
     SHORT flags;                  /* poll flags                           */
};

extern struct flddef vbpdataFDA[];

struct quesdata {                  /* poll question data structure         */
     SHORT qnum;                   /* question identification number       */
     CHAR pollname[PNAMELEN];      /* poll name this question is related to*/
     SHORT qtype;                  /* question type                        */
     CHAR ansstg[MAXASTGS][ANSSTGLEN]; /* array of answer strings          */
     SHORT branch[MAXASTGS];       /* branching designators                */
     SHORT prev;                   /* previous question                    */
     SHORT next;                   /* default next question                */
     LONG max;                     /* maximum value/length of answer       */
     LONG min;                     /* minimum value/length of answer       */
     SHORT field;                  /* field array element for usracc struct*/
     SHORT flags;                  /* question flags                       */
     SHORT ansparam;               /* number of answer parameters to allow */
     CHAR txtmsg[TXTSIZ];          /* question/text display message        */
};

extern struct flddef quesdataFDA[];

struct ansrdata {                  /* poll answer data structure           */
     SHORT qnum;                   /* question number for this answer      */
     CHAR pollname[PNAMELEN];      /* poll name this answer is related to  */
     CHAR uid[UIDSIZ];             /* userid of owner of this data         */
     CHAR answer[ANSSIZ];          /* variable length answer string        */
};

struct pollstat {                  /* current poll status for this user    */
     CHAR uid[UIDSIZ];             /* userid                               */
     CHAR pname[PNAMELEN];         /* poll name                            */
};

/* construct composite key for question acquisition                        */
struct quescomp {                  /* composite key for question           */
     CHAR pollname[PNAMELEN];      /* pollname of poll to acquire          */
     SHORT qnum;                   /* question number of ques to acquire   */
};

/* construct composite key for answer acquisition                          */
struct ansrcomp {                  /* composite key for answer             */
     CHAR pollname[PNAMELEN];      /* pollname of poll to acquire          */
     CHAR uid[UIDSIZ];             /* userid of owner of this data         */
     SHORT qnum;                   /* question number of this answer       */
};

/* construct composite key for answer acquisition                          */
struct cupacomp {                  /* composite key for cleanup answers    */
     SHORT qnum;                   /* question number of this answer       */
     CHAR pollname[PNAMELEN];      /* pollname of poll to acquire          */
};

/* construct composite key for finding user status of polls                */
struct statcomp {
     CHAR uid[UIDSIZ];             /* userid                               */
     CHAR pname[PNAMELEN];         /* poll name                            */
};

/* construct composite key for logon poll acquisition                      */
struct usercomp {
     CHAR uid[UIDSIZ];             /* userid to acuire                     */
     SHORT prior;                  /* priority to acquire                  */
     SHORT status;                 /* status to acquire                    */
};

struct polltemp {                  /* temporary storage area for user      */
     CHAR tstr[STRSIZ];            /* genaral purpose storage area         */
     CHAR tans[ANSSIZ];            /* temporary answer storage area        */
     CHAR tmpid[UIDSIZ];           /* used for stat lookup                 */
     INT flags;                    /* temporary user flags                 */
     INT ques;                     /* place holder for listing in cycle    */
     INT fques;                    /* first question for viewing results   */
     INT ans;                      /* answer counter for cycle             */
     INT cur;                      /* current question for auto-inc        */
     INT wheel;                    /* spinning wheel place holder          */
     LONG pos;                     /* position holder for CYCLING          */
     LONG oldpos;                  /* position holder for current page     */
     CHAR dftinp;                  /* default input character              */
     CHAR select[POLLSPERPG][PNAMELEN]; /* poll selection array            */
     struct polldata pdata;        /* poll data structure                  */
     struct quesdata qdata;        /* question data structure              */
     struct ansrdata adata;        /* answer data structure                */
     LONG :0;                      /* field alignment only (not used)      */
     CHAR fsdbuf[1];               /* share VDA buffer area with FSD       */
};

struct polltally {                 /* survey answer tally structure        */
     CHAR pollname[PNAMELEN];      /* tally for what pollname              */
     SHORT answer[MAXQUES][MAXASTGS];   /* tallies by question number      */
};

extern struct flddef polltallyFDA[];

/* flags for reading poll status */
#define QUESDN 0x01                /* done seeking question info           */
#define ANSRDN 0x02                /* done seeking answer info             */

struct rqinfo {                    /* per-request information              */
     SHORT idx;                    /* index number for cycling             */
     SHORT status;                 /* current poll status - work area      */
     SHORT highques;               /* high question number - work area     */
     SHORT totques;                /* total number of questions - work area*/
     SHORT highansr;               /* high question answered - work area   */
     SHORT totansr;                /* total number of questions answered   */
     LONG abs;                     /* absolute address for cycling         */
     LONG auxabs;                  /* auxillary absolute address for cyc   */
     CHAR pname[PNAMELEN];         /* poll name for cycling                */
     struct quescomp qcomp;        /* composite ques key structure for cyc */
     struct ansrcomp acomp;        /* composite ansr key structure for cyc */
     SHORT cycflgs;                /* flags used when cycling (see above)  */
     struct saunam dpknam;         /* sau structure information            */
};

struct rstat {                     /* poll status structure                */
     SHORT status;                 /* current poll status                  */
     SHORT highques;               /* high question number                 */
     SHORT totques;                /* total number of questions            */
     SHORT highansr;               /* last question answered               */
     SHORT totansr;                /* total number of questions answered   */
};

extern struct flddef rstatFDA[];

struct vbplist {                   /* VB poll listing information structure*/
     CHAR pname[PNAMELEN];         /* poll name                            */
     CHAR pdesc[PDESCLEN];         /* poll description                     */
     SHORT polltype;               /* poll or questionnaire type           */
     SHORT answer;                 /* poll answer status                   */
     SHORT flags;                  /* poll flags                           */
     SHORT data;                   /* data storage method                  */
};

extern struct flddef vbplistFDA[];

struct vbqlist {                   /* VB question listing info sturcture   */
     SHORT qnum;                   /* question number                      */
     SHORT qtype;                  /* question type                        */
     SHORT prev;                   /* previous question number             */
     SHORT next;                   /* next question number                 */
     GBOOL branch;                 /* branch designator                    */
     CHAR ques[PDESCLEN];          /* brief of question                    */
};

extern struct flddef vbqlistFDA[];

struct gcspoll {                   /* GCS user current poll tracking info  */
     CHAR pname[PNAMELEN];         /* poll name currently in use           */
};

/* poll status flags                                                       */
#define POLLTYPE         1         /* Listing is a Poll                    */
#define QUESTYPE         2         /* Listing is a Questionnaire           */
#define GRNCHK           4         /* User has completed this p/q          */
#define YELCHK           8         /* User has partially complete this p/q */
#define BLUEBOX         16         /* This is a new poll for this user     */
#define REDX            32         /* User does not have access to this p/q*/
#define REDM            64         /* p/q is currently undergoing maint    */

#define rqiptr ((struct rqinfo *)mrqptr)     /* ptr to information prm     */
#define rqsptr ((struct rqstat *)mrqptr)     /* ptr to status prm          */
#define pptr ((struct polldata *)(pbb->data))     /* poll data area        */
#define qptr ((struct quesdata *)(qbb->data))     /* question data area    */
#define aptr ((struct ansrdata *)(abb->data))     /* answer data area      */
#define eptr(h,x)   ((struct edpoll *)(arrelem(h,x))   /* edpoll pointer   */

#define tp          ((struct polltemp *)vdaptr)    /* define vdaptr        */
#define otp(x)      ((struct polltemp *)vdaoff(x)) /* define other vdaptr  */
#define atp         ((struct polltemp *)vdatmp)    /* define for cleanup   */

extern
struct message filmsg;             /* message header for grantstf()        */

PNQEXPV(CHAR *) supkey;       /* super user key for granting stuff    */
PNQEXPV(CHAR *) pllopkey;     /* Poll-Op key                          */

/* GALPNQA.C (C/S prototypes) */
PNQEXP VOID inicspq(VOID);
PNQEXP VOID addpanno(LONG ppos);
PNQEXP VOID polread(INT direction,struct saunam *dpknam);
PNQEXP VOID polwrite(struct saunam *dpknam,USHORT length,VOID *value);
PNQEXP VOID polxdone(VOID);
PNQEXP VOID polabort(VOID);
PNQEXP VOID poldsc(VOID);
PNQEXP GBOOL plist(INT direction,struct saunam *dpknam);
PNQEXP GBOOL rdques(INT type,INT direction,struct saunam *dpknam);
PNQEXP VOID skpdonly(VOID);
PNQEXP VOID sndqdpk(struct saunam *dpknam,INT type,struct quesdata *qdata);
PNQEXP GBOOL aread(INT direction,struct saunam *dpknam);
PNQEXP VOID findans(VOID);
PNQEXP VOID sndadpk(struct saunam *dpknam,struct ansrdata *adata);
PNQEXP VOID qcheck(INT direction,struct saunam *dpknam);
PNQEXP VOID plstat(VOID);
PNQEXP VOID sread(struct saunam *dpknam);
PNQEXP VOID cycsread(VOID);
PNQEXP CHAR *cvt4tb(CHAR *stg);
PNQEXP CHAR *cfrmtb(CHAR *stg);
PNQEXP VOID gcsudca(struct polldata *polptr);
PNQEXP VOID cycplist(VOID);
PNQEXP VOID gcsrst(struct polldata *pdp);
PNQEXP VOID gcsdel(struct polldata *pdp);
PNQEXP INT pedit(INT direction, struct saunam *dpknam);
PNQEXP INT mresult(INT direction, struct saunam *dpknam);
PNQEXP GBOOL qresstat(struct saunam *dpknam);
PNQEXP VOID cycqrs(VOID);
PNQEXP GBOOL uidpoll(struct saunam *dpknam);
PNQEXP CHAR *cvt4tb(CHAR *stg);
PNQEXP INT qlist(struct saunam *dpknam);
PNQEXP VOID cscycres(VOID);
PNQEXP VOID cscycres2(VOID);
PNQEXP GBOOL csremtally(VOID);
PNQEXP VOID cscyctally(VOID);
PNQEXP VOID csgrantstf(VOID);
PNQEXP VOID pqerror(CHAR *pFormat,...);
PNQEXP GBOOL pollvis(struct polldata *polptr,INT unum,GBOOL igndel);
/* GALPNQ.C (ANSI prototypes) */
PNQEXP INT ispollop (VOID);
PNQEXP INT isysop (VOID);
PNQEXP GBOOL dunques (SHORT flags);
PNQEXP INT listpolls (VOID);
PNQEXP INT chk4poll (VOID);
PNQEXP INT polmain (VOID);
PNQEXP VOID addprp (INT msgno, INT amode);
PNQEXP CHAR *polrft (VOID);
PNQEXP INT polvfy (INT fldno, CHAR *answer);
PNQEXP VOID poldun (SHORT save);
PNQEXP VOID polptc (VOID);
PNQEXP VOID quesprp (INT msgno, INT amode);
PNQEXP CHAR *quesrft (VOID);
PNQEXP INT quesvfy (INT fldno, CHAR *answer);
PNQEXP VOID quesdun (SHORT save);
PNQEXP VOID quesptc (VOID);
PNQEXP VOID astgprp (INT msgno, INT amode);
PNQEXP CHAR *astgrft (VOID);
PNQEXP INT astgvfy (INT fldno, CHAR *answer);
PNQEXP VOID astgdun (SHORT save);
PNQEXP VOID astgptc (VOID);
PNQEXP INT checkscn (VOID);
PNQEXP VOID setptrs (VOID);
PNQEXP VOID initdata (VOID);
PNQEXP INT listquest (VOID);
PNQEXP INT fndpoll (VOID);
PNQEXP INT fndstat (VOID);
PNQEXP VOID cyc_inc (VOID);
PNQEXP VOID qtypevfy (VOID);
PNQEXP VOID saveques (INT mode);
PNQEXP VOID gettake (VOID);
PNQEXP VOID getres (VOID);
PNQEXP VOID loadnext (VOID);
PNQEXP VOID loadprev (VOID);
PNQEXP INT chknext (VOID);
PNQEXP INT chkprev (VOID);
PNQEXP VOID setinplen (VOID);
PNQEXP CHAR *questxt (VOID);
PNQEXP VOID editqtype (INT mode);
PNQEXP VOID editmult (INT mode);
PNQEXP VOID loadquestxt (VOID);
PNQEXP VOID showmult (INT mode);
PNQEXP INT ismult (VOID);
PNQEXP VOID cyc_tally (VOID);
PNQEXP INT remove_tally (VOID);
PNQEXP VOID add_tally (INT qnum, CHAR *pname, CHAR *answer);
PNQEXP INT chk_answer (CHAR *stg);
PNQEXP VOID results (VOID);
PNQEXP VOID getlook (VOID);
PNQEXP VOID shwrslt (VOID);
PNQEXP VOID duppoll (VOID);
PNQEXP VOID nonpoll (VOID);
PNQEXP VOID takepoll (VOID);
PNQEXP VOID getpoll (VOID);
PNQEXP VOID editpoll (VOID);
PNQEXP VOID addques (VOID);
PNQEXP VOID getques (VOID);
PNQEXP VOID quesopts (VOID);
PNQEXP VOID getlup (VOID);
PNQEXP VOID disstats (VOID);
PNQEXP VOID cyc_ques (VOID);
PNQEXP VOID cyc_rslt (VOID);
PNQEXP VOID cyc_lup (VOID);
PNQEXP VOID cyc_disstats (VOID);
PNQEXP VOID cyc_logon (VOID);
PNQEXP VOID cyc_resusrs (VOID);
PNQEXP VOID cyc_resusrs2 (VOID);
PNQEXP INT gopoll (VOID);
PNQEXP VOID nxtpoll (VOID);
PNQEXP VOID pollask (VOID);
PNQEXP VOID pollins (VOID);
PNQEXP INT notexp (VOID);
PNQEXP VOID cycwheel (VOID);
PNQEXP INT chkpoll (VOID);
PNQEXP VOID apendasc (INT qnum, CHAR *pname, CHAR *answer);
PNQEXP VOID grantstf (VOID);
PNQEXP VOID upaccfld (INT field, CHAR *answer);
PNQEXP VOID delconf (VOID);
PNQEXP VOID cyc_delques (VOID);
PNQEXP VOID dundelq (VOID);
PNQEXP VOID prf2tx (VOID);
PNQEXP VOID poldft (INT msg);
PNQEXP INT okdate (CHAR *stg);
PNQEXP INT chk_clearance (VOID);
PNQEXP VOID resconf (VOID);
PNQEXP CHAR *rsltper (INT num, INT tot);
PNQEXP VOID initasc (VOID);
PNQEXP VOID rstflgs (VOID);
PNQEXP VOID pnachng (VOID);
PNQEXP VOID qnachng (VOID);
PNQEXP VOID anachng (VOID);
PNQEXP INT polstat (VOID);
PNQEXP GBOOL duntake (SHORT flags);
PNQEXP VOID saveresp (CHAR *ansstg);
PNQEXP INT usrinpoll(INT unum,CHAR *poll);
PNQEXP VOID init__galpnq (VOID);
PNQEXP VOID chkmodacc(struct saunam *dpknam);
PNQEXP VOID chk4dups(struct saunam *dpknam);
PNQEXP VOID qresacc(struct saunam *dpknam);
PNQEXP VOID polchg(VOID);
PNQEXP VOID timeup(VOID);

WGSEXP INT oldbgnedt();

// Added for dynamic updated of map in AH Polls
PNQEXPF(VOID, pollModified)(const struct polldata pdata);

//
PNQEXPV(CHAR *) qtypes[];
PNQEXPV(CHAR *) uaflds[];
PNQEXPV(CHAR *) stypes[];
PNQEXPV(CHAR *) stypes[];
PNQEXPV(CHAR *) types[];
PNQEXPV(CHAR *) atts[];
PNQEXPV(CHAR *) priors[];
PNQEXPV(CHAR *) yesno[];
PNQEXPV(CHAR *) truefalse[];
PNQEXPV(CHAR *) atypes[];
PNQEXPV(CHAR *) pstat[];
PNQEXPV(HMCVFILE) polmb;
PNQEXPV(DFAFILE *) sbb;
PNQEXPV(DFAFILE *) pbb;
PNQEXPV(DFAFILE *) qbb;
PNQEXPV(DFAFILE *) abb;
PNQEXPV(DFAFILE *) tbb;
PNQEXPV(DFAFILE *) timebb;

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __GALPNQH_H                          */
