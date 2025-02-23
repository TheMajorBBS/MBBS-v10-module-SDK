/***************************************************************************
 *                                                                         *
 *   SCRIPT.H                                                              *
 *                                                                         *
 *   Copyright (c) 1995-1997 Galacticomm, Inc.      All Rights Reserved.   *
 *                                                                         *
 *   This is the header file for the routine suite that supports Dial-     *
 *   Out-like scripting for online sessions.                               *
 *                                                                         *
 *                                                   - C. Robert  9/9/95   *
 *                                                   - R. Stein  1/26/96   *
 *                                                                         *
 ***************************************************************************/

#ifndef __SCRIPT_H
#define __SCRIPT_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


#ifdef GCWINNT
#   ifdef __BUILDSCR
#       define SCREXP           EXPORT
#       define SCREXPV(x)       EXPORT_VARIABLE(x)
#       define SCREXPF(x, y)    EXPORT_FUNCTION(x, y)
#    else
#       define SCREXP           IMPORT
#       define SCREXPV(x)       IMPORT_VARIABLE(x)
#       define SCREXPF(x, y)    IMPORT_FUNCTION(x, y)
#    endif
#else
#       define SCREXP
#       define SCREXPV
#       define SCREXPF
#endif // GCWINNT

#define NUMWAT      8              /* max # of watches                     */

                                   /* look-for strings: watches and waitfor*/
#define NUMLFS      (NUMWAT+1)     /*   max # of look-for strings          */
#define LFSSIZ      30             /*   max length of look-for strings     */
#define LFLSIZ      30             /*   max length of associated labels    */
#define LOGTFN      "SCR*.LOG"     /*   template for temp log file name    */
#define MAXELN      21             /*   max length of screrr() message     */

#define WFOIDX      NUMWAT         /* waitfor index in look-for stg arrays */
                                   /* (watches are indexes 0 to NUMWAT-1)  */

struct SCREXP scrinf {             /* information about ongoing script     */
     FILE *scrfp;                  /*   file pointer (NULL == script over) */
     VOID (*svrp)(                 /*   server / remote system output      */
          struct scrinf *scrptr,   /*     ptr to this structure            */
          UINT len,                /*     number of bytes                  */
          CHAR *bytes);            /*     bytes to output (NULs ok)        */
     VOID (*clip)(                 /*   client / user output               */
          struct scrinf *scrptr,   /*     ptr to this structure            */
          UINT len,                /*     number of bytes                  */
          CHAR *bytes);            /*     bytes to output (NULs ok)        */
     VOID (*devp)(                 /*   device / modem control commands    */
          struct scrinf *scrptr,   /*     ptr to this structure            */
          CHAR *stg);              /*     commands (NUL-term, ala btucmd())*/
     VOID (*admp)(                 /*   administrative / error output      */
          struct scrinf *scrptr,   /*     ptr to this structure            */
          CHAR *stg);              /*     error message (NUL-terminated)   */
     UINT lin;                     /*   script file line number (start w/1)*/
     CHAR inplin[INPSIZ];          /*   last line read from script file    */
     UINT tosecs;                  /*   # of secs until disconnect (or 0)  */
     ULONG tostart;                /*   when disconnect time-out started   */
     UINT pausecs;                 /*   # of secs until continuing (or 0)  */
     ULONG paustart;               /*   when pause started                 */
     CHAR lfstgs[NUMLFS][LFSSIZ];  /*   look-for strings (0-len if !in use)*/
     INT lfcnts[NUMLFS];           /*   match-so-far count on look-for stgs*/
     CHAR lflbls[NUMLFS][LFLSIZ];  /*   labels 2 goto when l4stgs are found*/
     UINT flags;                   /*   see below                          */
     FILE *logfp;                  /*   log file (NULL=off)                */
     CHAR logpth[GCMAXPTH];        /*   file name of log file              */
     CHAR logtmp[GCMAXPTH];        /*   temporary file name for log file   */
     INT chan;                     /*   app-specific use (e.g. usrnum)     */
     CHAR spare[50];               /*   (for future expansion)             */
};

#define SCFUSR 0x0001              /* USER setting is ON (vs OFF)          */
#define SCFTRC 0x0002              /* TRACE setting is ON (vs OFF)         */
#define SCFCIG 0x0004              /* CASE setting is IGNORE (vs MATTERS)  */

#define SCMSIZ      32             /* max len of script command (no params)*/

                                   /*   CNTPSCR, ENDPSCR, or KILCHAN       */
SCREXPF(INT, scrpvec)(             /* pump script interceptable vector     */
struct scrinf *scrptr);            /*   pointer to script info structure   */

                                   /* script processing return values      */
#define CNTPSCR     0              /*   continue processing of script      */
#define ENDPSCR     1              /*   end processing of script           */
#define KILCHAN     2              /*   kill script session (and ENDPSCR)  */

SCREXP VOID
init__galscr(VOID);                /* initialize the scripting API         */

SCREXP GBOOL
begscr(                            /* begin the processing of a script file*/
struct scrinf *scrptr,             /*   pointer to script info structure   */
CHAR *scrfil,                      /*   script file to process             */
VOID (*svrp)(                      /*   server output (can't be NULL)      */
     struct scrinf *scrptr,        /*     ptr to this structure            */
     UINT len,                     /*     number of bytes                  */
     CHAR *bytes),                 /*     bytes to output (NULs ok)        */
VOID (*clip)(                      /*   client / user output (NULL=none)   */
     struct scrinf *scrptr,        /*     ptr to this structure            */
     UINT len,                     /*     number of bytes                  */
     CHAR *bytes),                 /*     bytes to output (NULs ok)        */
VOID (*devp)(                      /*   device / modem command (NULL=none) */
     struct scrinf *scrptr,        /*     ptr to this structure            */
     CHAR *stg),                   /*     commands (NUL-term, ala btucmd())*/
VOID (*admp)(                      /*   admin / error output (NULL=none)   */
     struct scrinf *scrptr,        /*     ptr to this structure            */
     CHAR *stg));                  /*     error message (NUL-terminated)   */

/* Note:  When (*admp)() vector is called, last script line is in input[]. */

SCREXP INT                         /*   CNTPSCR, ENDPSCR, or KILCHAN       */
pumpscr(                           /* pump the processing of a script      */
struct scrinf *scrptr);            /*   pointer to script info structure   */

SCREXP VOID
scrinp(                            /* handle input from script session     */
struct scrinf *scrptr,             /*   pointer to script info structure   */
UINT len,                          /*   length of input to handle          */
CHAR *inp);                        /*   pointer to input to handle         */

SCREXP GBOOL
endscr(                            /* end the processing of a script file  */
struct scrinf *scrptr);            /*   pointer to script info structure   */

SCREXP GBOOL
abtscr(                            /* abort the script (toss log if any)   */
struct scrinf *scrptr);            /*   pointer to script info structure   */

SCREXP VOID
register_scrcmd(                   /* register a script command            */
CHAR *cmd,                         /*   script command                     */
INT (*crou)(                       /*   script command handling routine    */
     struct scrinf *scrptr));      /*     script session info              */

SCREXP VOID
screrr(                            /* report a script error                */
struct scrinf *scrptr,             /*   pointer to script info structure   */
CHAR *errmsg);                     /*   error msg (max length is MAXELN)   */

SCREXP GBOOL
go2lbl(                            /* goto a label in the script file      */
struct scrinf *scrptr,             /*   pointer to script info structure   */
CHAR *lbl);                        /*   label to goto                      */

SCREXP VOID
psnstg(                            /* prepare string for send              */
CHAR *stgptr);                     /*   pointer to string to prepare       */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __SCRIPT_H
