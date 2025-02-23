/***************************************************************************
 *                                                                         *
 *   MCVAPI.H                                                              *
 *                                                                         *
 *   Copyright (c) 1992-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Structures and variables for MCVAPI.C and other library utilities     *
 *   for reading .MCV files.  This header file is used internally by       *
 *   those library routines, and for some special purposes by              *
 *   the application program.                                              *
 *                                                                         *
 *                                                                         *
 *                                    - T. Stryker 1992                    *
 *                                    - Robert N. Stein 1/23/93            *
 *                                                                         *
 ***************************************************************************/

#ifndef __MCVAPI_H
#define __MCVAPI_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct msgblk {                    /* named-message file block             */
     FILE *msgfp;                  /*   fopen()-style file block pointer   */
     LONG *msgloc;                 /*   dynam-alloc'd fseek() msg offsets  */
     USHORT *lengths;              /*   dyn 2D array of message lengths    */
     INT *mslidx;                  /*   xlate:  0..nlingo-1 to 0..lngcnt-1 */
     CHAR *filnam;                 /*   message file name for error reports*/
     INT lstmsg;                   /*   last message number since setmbk() */
     LONG lnglist;                 /*   ptr to languages    \              */
     LONG lenlist;                 /*   ptr to length array  \  always last*/
     LONG loclist;                 /*   ptr to location list  > 16 bytes of*/
     SHORT lngcnt;                 /*   count of languages   /  a .MCV file*/
     SHORT msgcnt;                 /*   count of messages   /              */
};

typedef struct msgblk *HMCVFILE;   /* MCV file handle type                 */

#define lclmbk ((struct msgblk *)curmbk)  /* set by setmbk()               */

WGSEXPV(HMCVFILE) curmbk;          /* setmbk() sets, lclmbk is local alias */
WGSEXPV(UINT) mxmssz;              /* maximum message size                 */
WGSEXPV(INT) badlang;              /* to flag undefined languages in .MCVs */
WGSEXPV(INT) starit;               /* flag set by msgseek() if msg too long*/
WGSEXPV(CHAR*) msgbuf;             /* message text buffer                  */

WGSEXP VOID
inimsg(                            /* init msgutl with buffer size         */
UINT maxsiz);                      /*   maximum size of message buffer     */

WGSEXP HMCVFILE                    /*   returns handle to open mcv file    */
opnmsg(                            /* open a message file                  */
const char *mcvfil);               /*   mcv file to open                   */

WGSEXP CHAR *                      /*   returns ptr to message             */
rawmsg(                            /* get a raw message (by number)        */
INT msgnum);                       /*   msgnum to get                      */

WGSEXP UINT                        /*   returns msgnum's size              */
msgseek(                           /* seek to msg and calculate size       */
INT msgnum);                       /*   msgnum to read                     */

WGSEXP VOID
clsmsg(                            /* close message file                   */
HMCVFILE mbptr);                   /*   message file to close              */

WGSEXP VOID
setmbk(                            /* set message block                    */
HMCVFILE mb);                      /*   file to point to                   */

WGSEXP VOID                        /*   restore msg file ptr from before   */
rstmbk(VOID);                      /*   the last setmbk() or opnmsg()      */

WGSEXP LONG                        /*   returns a long value               */
lngopt(                            /* get numeric option from msg file     */
INT msgnum,                        /*   message number to read             */
LONG floor,                        /*   lower allowable limit              */
LONG ceiling);                     /*   upper allowable limit              */

WGSEXP UINT                        /*   returns a hex value                */
hexopt(                            /* get hexadecimal option from msg file */
INT msgnum,                        /*   message number to read             */
UINT floor,                        /*   lower allowable limit              */
UINT ceiling);                     /*   upper allowable limit              */

WGSEXP INT                         /*   returns a numeric value            */
numopt(                            /* get numeric option from msg file     */
INT msgnum,                        /*   message number to read             */
INT floor,                         /*   lower allowable limit              */
INT ceiling);                      /*   upper allowable limit              */

WGSEXP GBOOL                       /*   returns TRUE=yes FALSE=no          */
ynopt(                             /* get yes/no option from msg file      */
INT msgnum);                       /*   message number to read             */

WGSEXP INT                         /*   returns character                  */
chropt(                            /* get single-character option from msg */
INT msgnum);                       /*   message number to read             */

WGSEXP CHAR *                      /*   returns ptr to newly allocated stg */
stgopt(                            /* get a string from a message file     */
INT msgnum);                       /*   message number to read             */

                                   /*   returns ptr to newly allocated path*/
WGSEXP CHAR *                      /*   includes trailing slash            */
pthopt(                            /* get a path from a message file       */
INT msgnum);                       /*   message number to read             */

WGSEXP INT                         /*   returns index to string from list  */
tokopt(                            /* find token in a list                 */
INT msgnum,                        /*   message number to read             */
...);                              /*   list to search                     */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __MCVAPI_H                           */
