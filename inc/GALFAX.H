/***************************************************************************
 *                                                                         *
 *   GALFAX.H                                                              *
 *                                                                         *
 *   Copyright (c) 1992-1995 GALACTICOMM, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   This is the header for the Worldgroup Class 2/2.0 FAX API suite.      *
 *                                                                         *
 *                                - C. Robert and B. Stephens  12/1/92     *
 *                      class 2.0 compatibility - J. Delekto  10/12/95     *
 *                                                                         *
 ***************************************************************************/

#ifndef __GALFAX_H
#define __GALFAX_H

#include "gcomm.h"
#include "majorbbs.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#if defined(GCWINNT)
#ifdef __BUILDFAX
#define FAXEXP __export
#else
#define FAXEXP __import
#endif // __BUILDFAX
#else
#define FAXEXP
#endif // GCWINNT

#define   FAXDIR    "fax"          /* fax API working directory            */
#define   FAXPSZ    25             /* fax phone number string size         */
#define   WNMSIZ    50             /* whndun stg size ("dllnam: funcname") */
#define   FTPSIZ    50             /* fax topic string max size            */
#define   TONSIZ    30             /* fax "to name" field max size         */
#define   LPERPG    60             /* number of text lines per page        */
#define   CPERLN    80             /* number of text characters per line   */
#define   TABLEN    5              /* number of spaces to expand a tab     */
#define   MXQSIZ    8096           /* maximum size for a fax queue entry   */
#define   BARSIZ    4096           /* bit array size for text->fax (*2)    */
#define   RBFSIZ    4              /* processing buffer size (bit array)   */
#define   LBFSIZ    4096           /* single scan line buffer size         */
#define   BFNSIZ    256*16         /* size of "big char" font array        */
#define   SFNSIZ    256*8          /* size of "small char" font array      */
#define   INDENT    110            /* number of PELs to indent text        */
#define   HDRSIZ    64             /* # of scan lines in page hdr (fine)   */
#define   RETINC    20             /* increment for expanding retry table  */
#define   WTSECS    600            /* number of seconds to wait for a call */
#define   CHKSIZ    512            /* size of chunks when cnc'ing files    */
#define   CYCDLY    2              /* # of cycles to skip while building   */
#define   LNPCYC    1              /* # of text lines to convert per cycle */
#define   PRCHNK    512            /* size of chunks when processing faxes */
#define   PCYDLY    2              /* # of cycles to skip while processing */
#define   FXCSIZ    2048           /* size of chunks when faxing files     */
#define   VRTRES    2              /* vertical resolution for text -> fax  */
#define   HORRES    2              /* horizontal resolution for text -> fax*/
#define   FORMFD    12             /* form feed character definition       */
#define   FAXDLE    0x10           /* fax DLE character definition         */
#define   REVDLE    0x08           /* reversed fax DLE character def       */
#define   FAXSUB    0x1A           /* fax SUB character definition         */
#define   EOPMRK    0xFF           /* end of page marker (FAXDLE,EOPMRK)   */
#define   XONCHR    0x11           /* XON software flow control character  */
#define   XOFCHR    0x13           /* XOFF software flow control character */
#define   NOTALW    "<not allowed>"/* this prefix isn't allowed string     */
#define   EOPSTG    "ÿ"           /* end of page string (0x10,0xFF)       */
#define   DLEETX    ""           /* end of data string (0x10,0x03)       */
#define   ETXCHR    ''            /* ETX (end of data when following DLE) */
#define   DC2STG    ""            /* DC2 (commence receiving) stg (0x12)  */
#define   DLEMPS    ","           /* end of page, more to follow          */
#define   DLEEOP    "."           /* end of document and session          */
#define   FXCMSZ    10             /* generic fax command size             */
#define   CLASS2    "2"            /* fax class 2 ID string                */
#define   CLSS20    "2.0"          /* fax class 2.0 ID string              */
#define   RTCSTR    "\x00\x08\x80" /* fax class 2.0 EOL string (for RTC)   */

struct faxque {                    /* fax queue data structure format      */
     SHORT bldsnd;                 /*   build queue=0  send queue=1        */
     LONG faxnum;                  /*   unique message-#-like fax number   */
     CHAR phonum[FAXPSZ];          /*   phone number to send to (whndun)   */
     CHAR userid[UIDSIZ];          /*   user-id sending fax (for refund)   */
     CHAR toname[TONSIZ];          /*   who this fax is to (for ret rcpt)  */
     CHAR topic[FTPSIZ];           /*   topic of this fax (for ret rcpt)   */
     LONG crdchg;                  /*   credit cost for fax (for refund)   */
     CHAR whndun[WNMSIZ];          /*   whndun rou name (dllnam: rounam)   */
     CHAR fillst[1];               /*   list of files (bq) filnam (sq)     */
};



extern struct faxque * FAXEXP bldtmp; /* temp "build queue" storage area   */
extern struct faxque * FAXEXP sndtmp; /* temp "send queue" storage area    */

                                   /* fillst file-oriented flag definitions*/
#define   TXTFIL    0x01           /*   text file identifier flag          */
#define   FAXFIL    0x02           /*   fax file identifier flag           */
#define   DELFIL    0x04           /*   delete this file identifier flg    */
#define   EMLNOT    0x08           /*   e-mail notify whndun? (snd only)   */

struct retque {                    /* retry queue structure definition     */
     LONG faxnum;                  /*   fax id num to try again            */
     INT timout;                   /*   time to try again? 0=Yes >0=No     */
     INT tsofar;                   /*   number of retries so far           */
};

extern struct retque * FAXEXP retlst; /*   list of faxes to try again      */

struct faxchn {                    /* send/build fax structure (vda)       */
     LONG faxnum;                  /*   fax number being worked on         */
     FILE *infp;                   /*   file pointer for input             */
     FILE *outfp;                  /*   file pointer for output            */
     INT numpps;                   /*   number of pages (as building)      */
     INT filnum;                   /*   current file # (as building)       */
     INT numlin;                   /*   number of lines counter            */
     INT cyccnt;                   /*   cycle counter for building         */
     GBOOL stdmod;                 /*   standard mode=1, fine mode=0       */
     struct sfaxcmds *fc;          /*   pointer to fax modem command set   */
     CHAR input[INPSIZ];           /*   input buffer for ASCII mode        */
     CHAR fillst[1];               /*   list of files (one file in sq)     */
};

#define   faxusr    ((struct faxchn *)vdaptr)
#define   othfax(x) ((struct faxchn *)vdaoff(x))

struct recblk {                    /* receive fax info structure (vda)     */
     FILE *outfp;                  /*   file pointer for receive           */
     FILE *infp;                   /*   file pointer for processing        */
     CHAR tmpnam[GCMAXPTH];        /*   temp. file name for receive        */
     CHAR filnam[GCMAXPTH];        /*   file to save final fax image       */
     INT numpps;                   /*   number of pages received           */
     GBOOL stdmod;                 /*   standard mode=1, fine mode=0       */
     GBOOL gotdle;                 /*   just got a DLE character? (1/0)    */
     INT nbits;                    /*   number of valid bits in prcbuf     */
     CHAR prcbuf[RBFSIZ];          /*   processing buffer (bit array)      */
     INT nbyts;                    /*   number of valid bytes in linbuf    */
     CHAR linbuf[LBFSIZ];          /*   scan line buffer for doubling      */
     UINT nlines;                  /*   # of scan lines so far this page   */
     INT cyccnt;                   /*   cycle counter for processing       */
     CHAR input[INPSIZ];           /*   input buffer for ASCII mode        */
     VOID (*recdun)(GBOOL ok);     /*   when done routine for receive      */
     struct sfaxcmds *fc;          /*   pointer to fax modem command set   */
};

#define   recusr    ((struct recblk *)vdaptr)
#define   othrec(x) ((struct recblk *)vdaoff(x))

struct ttofax {                    /* text -> fax work structure (vdatmp)  */
     CHAR line[CPERLN+1];          /*   line to be read in from disk       */
     UINT bsofar;                  /*   bits so far held in bitary         */
     USHORT bitary[BARSIZ];        /*   bit array for building fax image   */
};

#define   txtfax    ((struct ttofax *)vdatmp)

struct faxpfx {                    /* fax prefix data structure format     */
     CHAR prefix[FAXPSZ];          /*   prefix for this entry              */
     CHAR rplcwt[FAXPSZ];          /*   replace prefix with this string    */
     CHAR keyreq[KEYSIZ];          /*   key required to use this prefix    */
     LONG baschg;                  /*   base (1st page) chg 4 this pfx     */
     LONG addchg;                  /*   additional page chg 4 this pfx     */
};

extern struct faxpfx * FAXEXP pfxlst;/* in-memory list of fax prefixes     */

struct sfaxcmds {                  /* fax modem command/response set       */
     CHAR ft[FXCMSZ];              /*   fax modem type this set is for     */
     CHAR fcl[FXCMSZ];             /*   fax modem class command            */
     CHAR fdt[FXCMSZ];             /*   begin sending page command         */
     CHAR fdr[FXCMSZ];             /*   begin receiving page command       */
     CHAR fet[FXCMSZ];             /*   report post-page msgs command      */
     CHAR fcon[FXCMSZ];            /*   connection made response           */
     CHAR fdcs[FXCMSZ];            /*   report DCS frame info response     */
     CHAR fhng[FXCMSZ];            /*   connection gone response           */
     CHAR flid[FXCMSZ];            /*   set local ID string command        */
     CHAR fdcc[FXCMSZ];            /*   set DCE capabilities command       */
     CHAR fcr[FXCMSZ];             /*   set receive capability command     */
};

extern DFAFILE * FAXEXP quebb;     /* fax queue database file              */
extern HMCVFILE FAXEXP quemb;

extern LONG FAXEXP dftbas;         /* default 1st-page charge for faxing N */
extern LONG FAXEXP dftadd;         /* default charge for each add. page  N */
extern LONG FAXEXP intbas;         /* default 1st-page charge for faxing I */
extern LONG FAXEXP intadd;         /* default charge for each add. page  I */

extern INT FAXEXP faxstt;          /* fax engine's module state code       */
extern INT FAXEXP faxspd[NUMGRPS]; /* max fax baud rate for channel grp x  */
extern INT FAXEXP maxfax;          /* maximum number of outgoing faxes     */
extern INT FAXEXP faxmod;          /* mode to send faxes (0=std, 1=fine)   */
extern INT FAXEXP faxsec;          /* number of seconds between rtkick()s  */
extern INT FAXEXP bghour;          /* hour to begin sending faxes          */
extern INT FAXEXP sthour;          /* hour to stop sending faxes           */
extern INT FAXEXP vrtres;          /* vertical resolution (VRTRES or 1)    */
extern INT FAXEXP usedch;          /* channels now being used for faxing   */
extern INT FAXEXP faxret;          /* number of times to retry a bad fax   */
extern INT FAXEXP rettim;          /* seconds between re-sending a bad fax */
extern INT * FAXEXP timout;        /* general time out ticker for each user*/

extern GBOOL FAXEXP faxcap[NUMGRPS];/* channel group x support fax? 1=Y 0=N*/
extern GBOOL FAXEXP fixpup;        /* fix up user-entered phone numbers?   */
extern GBOOL FAXEXP tndial;        /* touch tone dialing supported?        */
extern GBOOL FAXEXP audsuc;        /* record successful faxes to audit?    */
extern GBOOL FAXEXP audabt;        /* record unsuccessful faxes to audit?  */

extern CHAR FAXEXP intlid;         /* character denoting international #   */
extern CHAR * FAXEXP faxkey;       /* key required to send faxes           */
extern CHAR * FAXEXP faxfid;       /* fax id string (up to 20 chars long)  */
extern CHAR * FAXEXP bigfnt;       /* "big chars" in-memory font chars     */
extern CHAR * FAXEXP smlfnt;       /* "small chars" in-memory font chars   */

extern CHAR FAXEXP revtbl[];       /* reverse table characters for fax cnv.*/
extern USHORT FAXEXP whtmak[];     /* white make-up codes for fax image    */
extern USHORT FAXEXP blkmak[];     /* black make-up codes for fax image    */
extern USHORT FAXEXP whttrm[];     /* white terminating codes for image    */
extern USHORT FAXEXP blktrm[];     /* black terminating codes for image    */

GBOOL faxavl(VOID);
GBOOL valpho(CHAR *phonum);
GBOOL accpho(CHAR *phonum,CHAR *userid);
VOID stppho(CHAR *phonum);
GBOOL fixpho(CHAR *phonum);
LONG baschg(CHAR *phonum);
LONG addchg(CHAR *phonum);
LONG totchg(LONG fstchg,LONG nxtchg,INT totpps);
INT txtpps(CHAR *filnam);
INT faxpps(CHAR *filnam);
INT puttxt(CHAR *txtbuf,CHAR *pthpre,CHAR *filnam);
VOID begin_submit(CHAR *userid,LONG crdchg);
VOID submit_cover(INT totpps,CHAR *toname,CHAR *frname,CHAR *ftopic);
VOID submit_text(CHAR *filnam,INT flags);
VOID submit_fax(CHAR *filnam,INT flags);
LONG end_submit(CHAR *phonum,CHAR *whndun);
LONG send_fax(CHAR *filnam,CHAR *phonum,CHAR *userid,LONG totchg,
              CHAR *toname,CHAR *topic,CHAR *whndun,INT flags);
GBOOL receive_fax(INT chan,CHAR *filnam,VOID (*whndun)(GBOOL ok));
VOID abort_receive(INT chan);
GBOOL fileiu(CHAR *filnam);
struct faxpfx *fndpfx(CHAR *phonum);
INT frefch(VOID);
INT frebch(VOID);
GBOOL addfil(CHAR *lststg,CHAR *newfil,INT fstchr,UINT maxsiz);
CHAR *getfil(CHAR *lststg,INT filnum);
INT getflg(CHAR *lststg,INT filnum);
VOID modflg(CHAR *lststg,INT filnum,INT fstchr);
UINT lstlen(CHAR *lststg);
GBOOL calwdn(CHAR *wdnstg,CHAR *param1,LONG param2,GBOOL ok);
VOID faxnot(LONG faxnum,CHAR *fidfrom,CHAR *toname,CHAR *topic,GBOOL ok);
CHAR *xltnln(CHAR *buf);

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __GALFAX_H
