/***************************************************************************
 *                                                                         *
 *   RESERVE.H                                                             *
 *                                                                         *
 *   Copyright (c) 1994-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   File Reservations Kernel, for avoiding read/write and write/write     *
 *   conflicts.                                                            *
 *                                                                         *
 *                                        - RNStein  7/6/94                *
 *                                                                         *
 ***************************************************************************/

#ifndef __RESERVE_H
#define __RESERVE_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT
#   ifdef __BUILDGALFIL
#       define FILEXP           EXPORT
#       define FILEXPV(x)       EXPORT_VARIABLE(x)
#       define FILEXPF(x,y)     EXPORT_FUNCTION(x, y)
#   else
#       define FILEXP           IMPORT
#       define FILEXPV(x)       IMPORT_VARIABLE(x)
#       define FILEXPF(x,y)     IMPORT_FUNCTION(x, y)
#   endif // __BUILDWGSERVER
#else
#   define FILEXP
#   define FILEXPV
#   define FILEXPF
#endif // __GCWINNT

#define NOCONFLICT -1              /* meaning:  nobody else has reserved   */

struct reserve {                   /* reservations domain                  */
     INT nusers;                   /* number of users (e.g. nterms)        */
     INT *iuser;                   /* ptr to user-index var (e.g. &usrnum) */
     INT lkpusr;                   /* write locks per user                 */
     INT grpsiz;                   /* size of group strings (incl NUL)     */
     INT filsiz;                   /* size of file strings (incl NUL)      */
     CHAR *writloks;               /* alcmem of write-lock structures      */
     INT (*amreading)(             /* vector for resolving who's reading   */
          CHAR *grp,               /* group name (e.g. Library name)       */
          CHAR *fil);              /* file name (or "*"=any file in group) */
};

FILEXPV(struct reserve *) reserve; /* current (only) reserv. domain   */

struct reserve *
inireserve(                        /* initialize a new reservations domain */
INT nusers,                        /* number of users (e.g. nterms)        */
INT *iuser,                        /* ptr to user-index var (e.g. &usrnum) */
INT lkpusr,                        /* write locks per user                 */
INT grpsiz,                        /* size of group strings (incl NUL)     */
INT filsiz,                        /* size of file strings (incl NUL)      */
INT (*amrhdl)(CHAR *grp,CHAR *fil));/* default "amreading()" resolver      */
                                   /* (or NULL=assume NOCONFLICT)          */
                                   /* returns ptr to reservations domain   */

FILEXP VOID
setrsv(                            /* set reservations domain              */
struct reserve *rsv);              /* return value from inireserve()       */

FILEXP INT
w2writ(                            /* "I want to write (modify) this file" */
CHAR *grp,                         /* group name (e.g. Library name)       */
CHAR *fil,                         /* file name (or "*"=any file in group) */
INT lkn);                          /* lock number, 0 to lkpusr-1           */
                                   /* returns NOCONFLICT=reserved for you  */
                                   /*         else=who writes or reads     */

FILEXP VOID
donewrit(                          /* "I'm done writing the file"          */
INT lkn);                          /* lock number, 0 to lkpusr-1, or -1=all*/
                                   /* (un-write-reserve)                   */

FILEXP INT
w2read(                            /* "I want to read this file"           */
CHAR *grp,                         /* group name (e.g. Library name)       */
CHAR *fil);                        /* file name (or "*"=any file in group) */
                                   /* to read-reserve,intercept amreading()*/
                                   /* return NOCONFLICT=ok, else=who writes*/

FILEXP INT
whouse(                            /* Who is using this group?             */
CHAR *grp);                        /* group name (e.g. Library name)       */
                                   /* return NOCONFLICT=nobody, else=who   */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __RESERVE_H                          */