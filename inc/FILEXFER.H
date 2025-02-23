/***************************************************************************
 *                                                                         *
 *   FILEXFER.H                                                            *
 *                                                                         *
 *   Copyright (c) 1988-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   This is the header for the Worldgroup interface into the FTF file     *
 *   transfer routines.                                                    *
 *                                                                         *
 *                                                 - Bob Stein, 3/18/92    *
 *                                                                         *
 ***************************************************************************/

 #ifndef __FILEXFER_H
 #define __FILEXFER_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "ftf.h"
#include "ftg.h"
#include "fup.h"

struct ftuser {                    /* file transfer user structure         */
     FILE *fp;                     /*   pointer to the current file        */
     struct ftfpsp *ftfpsp;        /*   pointer to protocol specs          */
     CHAR flags;                   /*   general flag variable              */
     CHAR filid;                   /*   view file id (see FTFVIEW.H)       */
     INT numftg;                   /*   number of tagspecs                 */
     struct ftg *ftgptr;           /*   current tag in ftgusr array        */
     struct ftg ftg;               /*   local sub-tagspec                  */
     INT stchg;                    /*   time of state change               */
                                   /*   (also used by SPCXIT path)         */
     INT oubsiz;                   /*   output buffer size (for ftfomt)    */
     VOID (*retrou)(VOID);         /*   return to caller routine (ftgdnl())*/
     INT (*fuphdl)(INT fupcod);    /*   file upload handler                */
     CHAR msgbuf[TSHLEN+1];        /*   record recoverable file xmit error */
                                   /*   record FUPBEG reported abort msg   */
                                   /*   record File Import path            */
     struct ffblk fb;             /*   for breaking down wildcard filespec*/
     FILE *fiep;                   /*   file for importing or exporting    */
     INT savetags;                 /*   # of saved tagspecs at array's end */
};

                                   /* ftuptr->flags bit definitions        */
#define FTFBYE  0x01               /*   byebye detected & reported         */
#define VIATAG  0x02               /*   file transfer was via tagging menu */
#define FUPMUL  0x04               /*   multi-file upload                  */
#define FTBANG  0x08               /*   automatic logoff after transfer    */
#define FTFREF  0x10               /*   "F" upload can be by reference     */
#define ASEARCH 0x20               /*   \ ASCII search mode     (download) */
#define FUPAFN  0x20               /*   / abort will be final     (upload) */
#define TSHIPG  0x40               /*   Tagspec'd download ses in progress */
#define FUPIPG  0x80               /*   Upload session in progress         */

extern struct ftuser *ftuser;      /* FILEXFER.C array x nterms            */
WGSEXPV(struct ftuser*) ftuptr;    /* FILEXFER.C stuff for current user    */
WGSEXPV(INT) maxtags;              /* max number of tagged files per user  */
WGSEXPV(CHAR) alwait;              /* auto log-off waiting period          */

WGSEXPV(CHAR) pmcare;              /* globals for prtmnu(), hdlpmu()       */
WGSEXPV(CHAR) pmvalu;              /* and subordinates                     */

WGSEXPF(VOID,hdlpmu)(VOID);        /* Handler chain for protocol menu      */
WGSEXPV(CHAR*) fprlock;            /* "F" protocol lock                   */

WGSEXP VOID
iniftf1(VOID);            /* FTF initialization, phase 1 (before alcvda()) */

WGSEXP VOID
iniftf2(VOID);             /* FTF initialization, phase 2 (after alcvda()) */

WGSEXP VOID
setftu(VOID);                  /* set up lots of globals for file transfer */

WGSEXP INT
ispvis(                            /* is protocol visible?                 */
struct ftfpsp *ftp);               /* protocol                             */
                             /* (call only from within a hdlpmu() routine) */

WGSEXP VOID
listing(                        /* list an ASCII file to the user's screen */
CHAR *path,            /* path of the file (WARNING: must be non-volatile) */
VOID (*whndun)());            /* restore state & substate, prompt the user */
    /* optional argument to whndun routine: 1=list completed 0=interrupted */
/* IMPORTANT - path must remain valid,e.g. literal, vdaptr, malloc(nterms) */

WGSEXP VOID
listingq(          /* E-Z-Quick ASCII file listing, with prompt & substate */
CHAR *path,            /* path of the file (WARNING: must be non-volatile) */
INT msgno);             /* msg number, under curmbk, for prompt & substate */
/* IMPORTANT - path must remain valid,e.g. literal, vdaptr, malloc(nterms) */

WGSEXP VOID
ftfzer(VOID);                /* zero out FTF user structure (numftg, etc.) */
                                                   /* (usrnum is implicit) */

WGSEXPV(struct flddef) filheadFDA[];
WGSEXPV(struct flddef) dirheadFDA[];
WGSEXPV(struct flddef) endcdrFDA[];
WGSEXPV(struct flddef) archeadFDA[];
WGSEXPV(struct flddef) iceheadFDA[];
WGSEXPV(struct flddef) zooheadFDA[];

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __FILEXFER_H                         */
