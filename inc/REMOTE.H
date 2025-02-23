/***************************************************************************
 *                                                                         *
 *   REMOTE.H                                                              *
 *                                                                         *
 *   Copyright (c) 1991-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Header file for use with Remote Sysop stuff                           *
 *                                                                         *
 *                               - S. Brinker & R. Skurnick 3/29/91        *
 *                                                                         *
 *                               (based upon Functions and Utilities by    *
 *                                A. Von Gauss, R. Skurnick, & S. Brinker) *
 *                                                                         *
 ***************************************************************************/

#ifndef __REMOTE_H
#define __REMOTE_H

#include "FIOAPI.H"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT
#   ifdef __BUILDREMSYS
#       define RSYEXP           EXPORT
#       define RSYEXPV(x)       EXPORT_VARIABLE(x)
#       define RSYEXPF(x,y)     EXPORT_FUNCTION(x, y)
#   else
#       define RSYEXP           IMPORT
#       define RSYEXPV(x)       IMPORT_VARIABLE(x)
#       define RSYEXPF(x,y)     IMPORT_FUNCTION(x, y)
#   endif // __BUILDWGSERVER
#else
#   define RSYEXP
#   define RSYEXPV(x)           extern x           
#   define RSYEXPF(x,y)         extern x (* y)
#endif // __GCWINNT

#ifdef GCDOS
#define FNDSIZE     64
#else
#define FNDSIZE     GCMAXPTH
#endif

#ifndef UNIX
#include <sys/stat.h>
#endif                             /* UNIX                                 */

RSYEXPV(INT) rmsyst;               /* remote sysop state number            */

WGSEXPV(INT) kilipg;               /* kill-system command in progress      */
WGSEXPV(INT) errcod;               /* MS-DOS exit codes (for batch files)  */
WGSEXPV(INT) kilsrc;               /* kill-command source (-1=cons, -2=MCU,*/
                                   /* -3=timed event, >=0=chan #)          */
WGSEXPV(INT) kilctr;               /* kill-system in this many minutes     */
WGSEXPV(INT) rsetop;               /* reset option: busy=B; no-answer=N    */
WGSEXPV(INT) chnemd;               /* channel currently being emulated     */
WGSEXPV(INT) rmtsys;               /* remote sysop emul channel (-1 if no) */

RSYEXPV(HMCVFILE) rsymb;           /* Exported Message Block pointer       */
RSYEXPV(INT) rsykil;               /* Export kill timer                    */
RSYEXPV(ULONG) trkflgs;            /* Export tracking flags                */

struct rsysop {                    /* "remote Sysop" data structure        */
     FILE *sfp;                    /*   DOS functions source file pointer  */
     FILE *dfp;                    /*   DOS functions dest. file pointer   */
     LONG fpos;                    /*   DOS functions file position        */
     INT chan;                     /*   scratch channel number             */
     INT rkilctr;                  /*   kilctr for this remote sysop       */
     INT flags;                    /*   bit flags for remote sysop         */
     INT genctr;                   /*   general purpose counter            */
     CHAR dftinp;                  /*   default character handler input    */
     struct usracc acc;                 /*   scratch userid buffer              */
     struct ffblk dirblk;          /*   structure used for directory lists */
     CHAR sfname[FNDSIZE];         /*   file name 1 for general use        */
     CHAR dfname[FNDSIZE];         /*   file name 2 for general use        */
     struct clstab *cltptr;        /*   pointer to class table element     */
     CHAR text[MTXSIZ];            /*   general purpose text area          */
};

#define CRTCLS      1              /*   remote sysop is creating a class   */
#define EDTCLS      2              /*   remote sysop is editing a class    */
#define EDTKYR      4              /*   remote sysop is editing a keyring  */

#define rsyptr ((struct rsysop *)vdaptr)
#define remoff(u) ((struct rsysop *)vdaoff(u))

/* REMSYS.C 23/05/92 14.20.58 */
RSYEXP VOID init__remsys(VOID);
RSYEXP GBOOL account(VOID);
RSYEXP VOID rcpydat(VOID);
RSYEXP VOID dspsts(VOID);
RSYEXP VOID dspmdu(VOID);
RSYEXP VOID dspsaa(VOID);
RSYEXP VOID dspcus(VOID);
RSYEXP VOID acsthn(VOID);
RSYEXP VOID emuinp(INT hangup);
RSYEXP VOID clremu(INT unum);
RSYEXP VOID updaxs(VOID);
RSYEXP VOID bgnmon(INT msg,ULONG wch);
RSYEXP VOID rblwof(INT msg);
RSYEXP VOID sisokq(VOID);
RSYEXP VOID dsponl(VOID);
RSYEXP VOID chkdat(INT date);
RSYEXP VOID chkcrd(LONG credits);
RSYEXP VOID xltescp(VOID);
RSYEXP VOID prfaxs(struct usracc* uacptr);
RSYEXP VOID clsfils(VOID);
RSYEXP INT fnamchk(CHAR *touse);
RSYEXP VOID shwdft(VOID);
RSYEXP VOID dspcll(VOID);

/* REMSYS2.C 23/05/92 13.56.52 */
RSYEXP VOID rsop62(VOID);
RSYEXP VOID rsop62a(VOID);
RSYEXP VOID rsop71(VOID);
RSYEXP VOID acczero(VOID);
RSYEXP INT acconex(VOID);
RSYEXP VOID clsrsy(VOID);
RSYEXP extern INT rsyevt(VOID);
RSYEXP INT emuinu(VOID);
RSYEXP INT wrdlen(CHAR *str);
RSYEXP INT anyaxs(struct usracc* uacptr);
RSYEXP VOID zaprsy(VOID);
RSYEXP INT ckfnams(CHAR *touse,CHAR *test);
RSYEXP SHORT dwedt11(SHORT flags);
RSYEXP SHORT dwedt12(SHORT flags);
RSYEXP SHORT dwedt13(SHORT flags);
RSYEXP SHORT dwedtj5(SHORT flags);
RSYEXP SHORT dwedtjj(SHORT flags);
RSYEXP VOID ntfysop(CHAR *audrec);
RSYEXP VOID init__galrsy(VOID);
RSYEXP VOID rsprom(INT msg);
/* C/S function declarations */
RSYEXP VOID inicsrsy(VOID);

RSYEXP CHAR * stpname(CHAR *fname);
RSYEXP  CHAR * makpath(CHAR *fname);
RSYEXP  CHAR * stppath(CHAR *fname);
RSYEXP  CHAR * fixfil(CHAR *fname);
RSYEXP  GBOOL iswild(CHAR *fname);
RSYEXP  CHAR * rtmfmt(ULONG ntval);

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __REMOTE_H                           */
