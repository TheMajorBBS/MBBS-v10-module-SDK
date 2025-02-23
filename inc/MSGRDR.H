/***************************************************************************
 *                                                                         *
 *   MSGRDR.H                                                              *
 *                                                                         *
 *   Copyright (c) 1993-1997 Galacticomm, Inc.   All rights reserved.      *
 *                                                                         *
 *   Utilities for reading and writing multilingual .MSG files (header).   *
 *                                                                         *
 *                                               - R. Stein  1/21/93       *
 *                                                                         *
 ***************************************************************************/

#ifndef __MSGRDR_H
#define __MSGRDR_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define MOPTLEN 8                  /* Maximum option name length           */
#define MAXOPTS 4800               /* maximum number of messages           */
#define OPTSIZE 16384              /* abs max contents of options, incl NUL*/
#define MAXLANG 100                /* max number of languages possible     */
#define HLPLEN 1000                /* max length of option help message    */
#define OPNMSG '{'                 /* opening character of an option       */
#define CLSMSG '}'                 /* closing character of an option       */
#define OPNHNG '('                 /* opening character of a hinge         */
#define HNGEQ  '='                 /* hinge operator:  equals              */
#define HNGNE  '#'                 /* hinge operator:  not-equals          */
#define HNGDLM ','                 /* hinge value list delimeter           */
#define HNGEXC '*'                 /* hinge operator: exclude option always*/
#define CLSHNG ')'                 /* closing character of a hinge         */

struct altlng {                    /* alternate language information       */
     CHAR altered;                 /*   this version was altered           */
     union {
          CHAR *ptr;               /*   value in .MSG                      */
          LONG fsk;                /*   fseek pos of value in .MSG         */
     } value;
};

                                                   /*--- rdmsg() inputs ---*/
WGSEXPV(const CHAR*) curfn;        /* filename of current MSG file         */

WGSEXPV(FILE*) rdfp;               /* file to rdmsg() or rdopt() from      */
                                                  /*--- rdmsg() outputs ---*/
WGSEXPV(LONG) cmtptr;              /* pointer to comment preceding message */
WGSEXPV(INT) cmtlen;               /* length of that comment               */
WGSEXPV(CHAR) msgnam[MOPTLEN+1];   /* message name                         */
WGSEXPV(CHAR*) txtbuf;             /* Text buffer for 'T' vbls             */
WGSEXPV(CHAR) hlpbuf[HLPLEN+1];    /* buffer for option help message       */

WGSEXPV(struct altlng*) altlnm;    /* array of alternate lang info         */
                                   /* altlnm[0] is output by rdmsg()       */
                    /* altlnm[1]..altlnm[salingo-1] is output by scanalt() */

WGSEXPV(UINT) bufsize;        /* size of txtbuf, including NUL terminator  */
WGSEXPV(INT) salingo;      /* scanalt() reports # alternates (incl lingo 0)*/
WGSEXPV(INT) sachar;          /* last character (or EOF) read by scanalt() */
WGSEXPV(INT) sachar;       /* last char (or EOF) rd by scanalt()/litopts() */
WGSEXPV(INT) valsiz;          /* getvalbuf() output (not incl '\0')        */
WGSEXPV(INT) valsiz;  /* char read by getvalbuf(),getval(),loadtv()(no NUL)*/
WGSEXPV(INT) sincebl;         /* chars since last \n -- set by nxtink()    */
WGSEXPV(INT) gvbust;    /* set to 1 by getval() to indicate option too big */
WGSEXPV(INT) tdremv;         /* should getvalbuf(), etc. remove '~' tildes?*/

#define LOBMAX 128                 /* size of lobuf[], not including NUL   */
WGSEXPV(CHAR) lobuf[LOBMAX+1];     /* buffer output for litopts()          */

VOID
inimsgrdr(                         /* initialize msg reader/text buffers   */
UINT siz);                         /* size of text buffers                 */

INT                                /*   returns 0 if EOF reached           */
rdmsg(VOID);                       /* reads msg from file rdfp             */

             /* salingo is number of alternates read, including language 0 */
                     /* salingo is never allowed to get larger than nlingo */
                    /* altlnm[1..salingo-1].value are the implicit outputs */
                            /* 1 extra character will be read and returned */
                                  /* implicit inputs:  rdfp, msgnam, curfn */
INT
scanalt(VOID);  /* scan alternate language version(s) of getval()'d option */


VOID
litopts(VOID);                     /* read specs line into lobuf[] stg     */

CHAR
lotype(VOID);                      /* opt type, per recent litopts() call  */

VOID
loadtv(                            /* put 'T' option value in txtbuf       */
FILE *msgfp,                       /*   .MSG file                          */
struct altlng *alptr);             /*   ptr to info for appropriate lang   */

                                   /*   puts result in txtbuf              */
INT                                /*   returns 1=ok 0=EOF                 */
getval(                            /* reads in current 'T' option from file*/
FILE *msgfp);                      /*   file ptr to read from              */

INT                                /*   returns 1=ok 0=EOF                 */
getvalbuf(                         /* reads in current 'T' option from file*/
FILE *msgfp,                       /*   file ptr to read from              */
CHAR *buf);                        /*   where to put it (NULL=nowhere)     */

VOID                               /*   uses txtbuf as input               */
putval(                            /* writes the current 'T' opt to a file */
FILE *msgfp);                      /*   file to write to                   */

INT                                /*   returns next CHAR                  */
nxtink(VOID);                      /* fnd nxt non-white char from .MSG file*/

VOID
clsmsgrdr(VOID);                   /* close down msg reader/text buffers   */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __MSGRDR_H                           */
