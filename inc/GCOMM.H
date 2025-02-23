/***************************************************************************
 *                                                                         *
 *   GCOMM.H                                                               *
 *                                                                         *
 *   Copyright (c) 1987-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   This is the header file for all Galacticomm C source development.     *
 *   It defines standard symbols for file-open modes, console              *
 *   keystroke codes, and many other standard coding items, including      *
 *   prototypes for most of the functions in GCOMM.LIB.                    *
 *                                                                         *
 *                                            - T. Stryker 2/3/92          *
 *                                                                         *
 ***************************************************************************/

#ifndef __GCOMM_H
#define __GCOMM_H

#ifdef GCWINNT
#   ifdef __BUILDWGSERVER
#       define WGSEXP           EXPORT
#       define WGSEXPV(x)       EXPORT_VARIABLE(x)
#       define WGSEXPF(x,y)     EXPORT_FUNCTION(x, y)
#   else
#       define WGSEXP           IMPORT
#       define WGSEXPV(x)       IMPORT_VARIABLE(x)
#       define WGSEXPF(x,y)     IMPORT_FUNCTION(x, y)
#   endif // __BUILDWGSERVER
#else
#   define WGSEXP               EXPORT
#   define WGSEXPV(x)           extern x
#   define WGSEXPF(x,y)         extern x (* y)              
#endif // __GCWINNT

#if !defined(GCDOSL)  && !defined(GCDOSP)  && !defined(GCTNT86)            \
 && !defined(GCWIN3X) && !defined(GCWINNT) && !defined(UNIX) && !defined(_MSC_VER)
#   error YOU SHOULD IDENTIFY THE OPERATING SYSTEM!
#endif

#define CHAR_BUFFER(name, size, lit)    \
    CHAR name[size] = lit

#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include <setjmp.h>
#include <time.h>
#include <sys/stat.h>
#include "stdio.h"

#if defined(GCWIN3X)
#   include <windows.h>
#endif // GCWIN3X

#include "gctypdef.h"

#ifdef UNIX
#   include <dirent.h>
#   include "strdecl.h"
#   include <errno.h>
#   include <unistd.h>
#   ifdef GCSCO30
#       include <sys/timeb.h>
#   endif // GCSCO30

CHAR *strupr(CHAR *);              /* make string uppercase                */
CHAR *strlwr(CHAR *);
INT gstricmp(CHAR *,CHAR *);
INT stricmp(CHAR *,CHAR *);
INT strcmpi(CHAR *,CHAR *);
INT creattemp(CHAR *,INT);
INT memicmp(CHAR *,CHAR *,size_t);

#else // UNIX
#   ifdef _MSC_VER
#       include <direct.h>
#       include <memory.h>
#   else
#       include <dir.h>
#       include <mem.h>
#   endif

#   include <dos.h>
#   include <io.h>
#   include <string.h>

#   if defined(GCDOS) || defined(GCWIN3X)
#       define GCPACKED                   // operating environment uses packed structs
#       undef fileno
#       define fileno(f)       ((UCHAR)(f)->fd)
#       define getml(ln)        farmalloc(ln)
#   else // defined(GCDOS) || defined(GCWIN3X)
#       define getml(ln)        alcmem(ln)
#   endif // defined(GCDOS) || defined(GCWIN3X)

#   if defined(GCWIN3X)
#       define VBASIC FAR PASCAL _export
#   endif // GCWIN3X

#   ifdef GCDOSP
#       include "phapi.h"
#   endif // GCDOSP
#endif // UNIX

#ifndef GCV2
#   include "gccuros.h"
#endif // GCV2

#include "fioapi.h"
#include "vidapi.h"
#include "cvtapi.h"
#include "dntapi.h"
#include "kbdapi.h"
#include "mcvapi.h"
#include "dfaapi.h"
#include "audapi.h"
#include "cfgapi.h"

#include "tfscan.h"
#include "lingo.h"
#include "msgrdr.h"
#include "vbdatim.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#if defined(GCWINNT) || defined(UNIX)
VOID
ctrlbrk(                           /* stub Ctrl+Break handler              */
INT (*handler)(VOID));             /*   new Ctrl+Break function            */
#endif // GCWINNT || UNIX

#ifndef NOGCMINMAX

#ifndef abs
#define abs(a)          (((a) < 0) ? -(a) : (a))
#endif

#ifndef min
#define min(a,b)        (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a,b)        (((a) > (b)) ? (a) : (b))
#endif

#endif // NOGCMINMAX
                                   /* function redefinitions for compat.   */
#define sstatr(a)  setatr(a)       /* redirected for monochrome CRT support*/
#define ltoa(a)    l2as(a)         /* redirected to ensure compatibility   */
#ifndef setmem
#define setmem(p,n,c)  memset(p,c,n)
#endif

#if defined(GCDOS) || defined(GCWIN3X)
LONG farcoreleft(VOID);
CHAR *farmalloc(ULONG size);
VOID farfree(VOID *p);
#endif // GCDOS || GCWIN3X

#ifdef GCDOSP
#ifdef movmem
#undef movmem
#endif // movmem
#ifdef memmove
#undef memmove
#endif // memmove

#ifndef GCV2
                                   /* MOVMEM(), C-callable version (4 byte */
                                   /* moves if possible)                   */
VOID
galmovmem(VOID *src,VOID *dst,USHORT nbytes);

#define movmem(s,d,n)  galmovmem(s,d,n)
#define memmove(d,s,n) galmovmem(s,d,n)

#endif // GCV2

#else // GCDOSP
#ifndef movmem
#define movmem(s,d,n)  memmove(d,s,n)
#endif // movmem
#endif // GCDOSP

#ifdef GCDOS
#ifdef movmemb
#undef movmemb
#endif // movmemb
                                   /* MOVMEMB(), C-callable version (byte  */
                                   /* moves only)                          */
                                   /*  Handy for moving memory to and from */
                                   /*  the screen for some video cards.    */
VOID
galmovmemb(VOID *src,VOID *dst,USHORT nbytes);

#define movmemb(s,d,n) galmovmemb(s,d,n)
#else // GCDOS
#ifndef movmemb
#define movmemb(s,d,n) memmove(d,s,n)
#endif // movmemb
#endif // GCDOS

#define getmsg         getMsgBlk   /* avoid Unix name space collision      */


#define nelems(x) (sizeof(x)/sizeof(x[0]))   /* # of elements in an array  */
#define VBTRUE  ((GBOOL)(0xFFFF))  /* Visual Basic TRUE                    */
#define VBOOL2C(x) if (x != FALSE) x=TRUE
#define CSTRLEN(stringConstant) (sizeof(stringConstant)-1)
#define NULSTR(s) ((s) == NULL || *(s) == '\0')
#define MARKSOURCE(filename) VOID EXPORT __##filename(VOID){}

#define CHAN_NUL  -1               /* "no channel" value                   */

WGSEXPV(jmp_buf) disaster;         /* master longjmp() block, for catastro */

WGSEXPV(INT) explodem;             /* yes/no controlling exploding windows */
WGSEXPV(INT) edtvalc;              /* last char accepted by edtval()       */

                                   /* flags for edtval() routine           */
#define MCHOICE     1              /*   multi-choice question, hide cursor */
#define ALLCAPS     2              /*   convert chars to capital letters   */
#define USEPOFF     4              /*   use proff() x,y base coord offsets */
#define MULTIEX     8              /*   allow multi field-exit conditions  */

WGSEXP GBOOL                       /*   FALSE if ESC hit; TRUE otherwise   */
edtval(                            /* edit a string value field            */
INT sx,                            /*   starting x coord (0-based)         */
INT sy,                            /*   starting y coord (0-based)         */
INT maxlen,                        /*   max len of field (incl. '\0')      */
CHAR *sval,                        /*   value edit and return-buffer       */
GBOOL (*valrou)(CHAR, CHAR*),       /*   validation routine address         */
INT flags);                        /*   option flags (see gcomm.h)         */

                                   /* RTKICK.C prototypes                  */
WGSEXP VOID
rtkick(                            /* real-time kicktable handler          */
INT delay,                         /*   time to delay between calls        */
VOID (*dstrou)());                 /*   routine to call after delays       */

WGSEXP VOID
prcrtk(VOID);                      /* call an rtkick's specified routine   */

WGSEXP INT                         /*   returns the index to string        */
findstg(                           /* find a string in a body of text      */
CHAR *stg,                         /*   string to search for               */
CHAR *body);                       /*   text to be searched                */

WGSEXP CHAR *                      /*   returns ptr to first word          */
firstwd(                           /* find first word of a string          */
CHAR *string);                     /*   returns a copy of it, or "" if none*/

WGSEXP CHAR *                      /*   returns word or "" when done       */
nextwd(VOID);                      /* find next word in string             */

WGSEXP CHAR *                      /*   returns ptr to last word           */
lastwd(                            /* find last word of a string           */
CHAR *string);                     /*   string to be searched              */

WGSEXP CHAR *                      /*   returns ptr to newly allocated stg */
alcdup(                            /* allocate mem for stg and copy to it  */
const CHAR *stg);                  /*   string to duplicate                */

WGSEXP VOID *                      /*   returns ptr to newly allocated mem */
alcmem(                            /* allocate dynamic memory              */
UINT size);                        /*   requested memory size              */

WGSEXP VOID *                      /*   returns ptr to allocated block     */
alcblok(                           /* allocate > 64K blocked memory region */
USHORT qty,                        /*   number of blocks                   */
USHORT size);                      /*   size of each block                 */

WGSEXP VOID
freblok(                           /* free region allocated with alcblok() */
VOID *bigptr);                     /*   alcblok() return value             */

WGSEXP VOID *                      /*   returns ptr to requested element   */
ptrblok(                           /* get address of blok in blocked region*/
VOID *bigptr,                      /*   alcblok() return value             */
USHORT idx);                       /*   index of the blok, 0..qty-1        */

WGSEXP VOID *                      /*   returns ptr to newly allocated mem */
alczer(                            /* allocate memory and zero it out      */
UINT nbytes);                      /*   requested memory size              */

WGSEXP VOID *                      /*   newly reallocated block            */
alcrsz(                            /* resize previously allocated memory   */
VOID *mptr,                        /*   allocated block (NULL if none yet) */
UINT oldsize,                      /*   old size to carry over (or 0=none) */
UINT newsize);                     /*   requested memory size              */

WGSEXPF(VOID,catrpt)(CHAR *filnam);
WGSEXPV(SHORT) catact;

WGSEXP VOID
catastro(                          /* catastrophe message display utility  */
const char *string,                /*   conversion string                  */
...);                              /*   variable arguments                 */

WGSEXP VOID
memcata(VOID);                     /* out of memory catastro               */

WGSEXP VOID
cataexit(VOID);                    /* catastrophe-exit utility             */

WGSEXP INT                         /*   0 if ESC hit; otherwise 1          */
edtchc(                            /* edit a string value field            */
INT sx,                            /*   starting x coord (0-based)         */
INT sy,                            /*   starting y coord (0-based)         */
CHAR *sval,                        /*   value edit and return-buffer       */
CHAR *chcs[],                      /*   possible choices for value         */
INT flags);                        /*   option flags (see gcomm.h)         */

WGSEXP VOID
explode(                           /* explode a shadowed window to CRT     */
CHAR *sctptr,                      /*   screen image w/source graphic      */
INT wulx,                          /*   src/dest window upper left x-coord */
INT wuly,                          /*   src/dest window upper left y-coord */
INT wlrx,                          /*   src/dest window lower right x-coord*/
INT wlry);                         /*   src/dest window lower right y-coord*/

WGSEXP VOID
explodeto(                         /* explode a shadowed window to x,y     */
CHAR *sptr,                        /*   screen image w/source graphic      */
INT fux,                           /*   "from" window upper left x-coord   */
INT fuy,                           /*   "from" window upper left y-coord   */
INT flx,                           /*   "from" window lower right x-coord  */
INT fly,                           /*   "from" window lower right y-coord  */
INT tux,                           /*   "to" window upper left x-coord     */
INT tuy);                          /*   "to" window upper left y-coord     */

WGSEXP VOID
nsexploto(                         /* explode a window (no shadow)         */
CHAR *sptr,                        /*   screen image w/source graphic      */
INT fux,                           /*   "from" window upper left x-coord   */
INT fuy,                           /*   "from" window upper left y-coord   */
INT flx,                           /*   "from" window lower right x-coord  */
INT fly,                           /*   "from" window lower right y-coord  */
INT tux,                           /*   "to" window upper left x-coord     */
INT tuy);                          /*   "to" window upper left y-coord     */

WGSEXP GBOOL                       /*   returns TRUE=valid FALSE=invalid   */
isselc(                            /* is c a valid menu select character?  */
INT c);                            /*   character to check                 */

WGSEXP GBOOL                       /*   returns TRUE=valid FALSE=invalid   */
istxvc(                            /* is this a valid text variable char   */
INT c);                            /*   character to check                 */

WGSEXP GBOOL                       /*   returns TRUE=valid FALSE=invalid   */
isuidc(                            /* is c part of a valid user-ID?        */
INT c);                            /*   character to check                 */

WGSEXP GBOOL                       /*   returns TRUE=valid FALSE=invalid   */
isfiln(                            /* is c/stg a valid file character/stg  */
INT c,                             /*   character to check                 */
CHAR *stg);                        /*   string to check                    */

WGSEXP CHAR *                      /*   returns converted string           */
l2as(                              /* long-to-ASCII conversion utility     */
LONG longin);                      /*   long to convert                    */

WGSEXP CHAR *                      /*   returns converted string           */
ul2as(                             /* unsigned long-to-ASCII conv utility  */
ULONG ulongin);                    /*   unsigned long to convert           */

WGSEXP CHAR *                      /*   returns ptr to buf                 */
mdfgets(                           /* server flavor of fgets()             */
CHAR *buf,                         /*   buffer to store line in            */
INT size,                          /*   size of buffer (just in case)      */
FILE *fp);                         /*   file pointer                       */

WGSEXP VOID
repmem(                            /* replicate what into where for totsiz */
VOID *where,                       /*   buffer to do replication           */
CHAR *what,                        /*   pattern to replicate               */
INT totsiz);                       /*   total size of "where" buffer       */

WGSEXP GBOOL                       /*   returns TRUE=same FALSE=different  */
sameas(                            /* are strings identical? (ignores case)*/
const CHAR *stg1,                  /*   first string to compare            */
const CHAR *stg2);                 /*   second string to compare           */

WGSEXP GBOOL                       /*   returns TRUE=short matches         */
sameto(                            /* compare short string to long string  */
const CHAR *shorts,                /*   short string to compare            */
const CHAR *longs);                /*   long string to compare             */

WGSEXP GBOOL                       /*   returns TRUE=short in long found   */
samein(                            /* find short string in long string     */
const CHAR *shorts,                /*   short string to find               */
const CHAR *longs);                /*   long string to search through      */

WGSEXP GBOOL                       /*   returns TRUE=stg ends with pattern */
samend(                            /* comp end of long stg with a short stg*/
const CHAR *longs,                 /*   long string to compare             */
const CHAR *ends);                 /*   end pattern to search for          */

WGSEXP CHAR *                      /*   returns buffer to converted string */
spr(                               /* galacticomm flavor of sprintf()      */
const CHAR *ctlstg,                /*   control string                     */
...);                              /*   variable arguments                 */

WGSEXP CHAR *                      /*   returns ptr to destination         */
stzcpy(                            /* copy a string with limit and zero fil*/
CHAR *dst,                         /*   destination buffer                 */
const CHAR *src,                   /*   source buffer                      */
UINT num);                         /*   # of bytes in dest, includes '\0'  */

WGSEXP CHAR *                      /*   returns ptr to destination buffer  */
stzcat(                            /* concatenate on a string, same limits */
CHAR *dst,                         /*   destination buffer                 */
const CHAR *src,                   /*   source buffer                      */
UINT num);                         /*   # of bytes in dest, includes '\0'  */

WGSEXP CHAR *                      /*   returns ptr to destination buffer  */
stlcpy(                            /* copy a string with limit             */
CHAR *dst,                         /*   destination buffer                 */
const CHAR *src,                   /*   source buffer                      */
UINT num);                         /*   # of bytes in dest, includes '\0'  */

WGSEXP CHAR *                      /*   returns ptr to destination buffer  */
stlcat(                            /* concatenate on a string, with limits */
CHAR *dst,                         /*   destination buffer                 */
const CHAR *src,                   /*   source buffer                      */
UINT num);                         /*   # of bytes in dest, includes '\0'  */

WGSEXP GBOOL                       /*   returns TRUE if string was found   */
strsrep(                           /* replace a stg in a stg w/ a stg      */
CHAR *stg,                         /*   the string to search               */
CHAR *from,                        /*   the string to be replaced          */
CHAR *to);                         /*   the string to replace with         */

WGSEXP VOID
b2ccpy(                            /* copies a VB-basic string to C format */
CHAR *dest,                        /*   destination buffer, C format       */
const CHAR *src,                   /*   source buffer, VB format           */
UINT length);                      /*   length to copy plus trailing '\0'  */

WGSEXP VOID
c2bcpy(                            /* copy C format string to VB format    */
CHAR *dest,                        /*   destination buffer, VB format      */
const CHAR *src,                   /*   source buffer, C format            */
UINT length);                      /*   length of destination string buffer*/

WGSEXP CHAR *                      /*   returns pointer to string          */
b2ccvt(                            /* cvt VB string to C format string     */
CHAR *str,                         /*   string to convert                  */
INT bufsiz);                       /*   size of string buffer              */

WGSEXP CHAR *                      /*   returns a pointer to string        */
c2bcvt(                            /* cvt C format string to a VB format   */
CHAR *str,                         /*   pointer to string to convert       */
INT bufsiz);                       /*   size of string buffer              */

WGSEXP GBOOL                       /*   returns TRUE=valid digit           */
validig(                           /* is c a valid decimal digit?          */
INT c);                            /*   character to check                 */

WGSEXP GBOOL                       /*   always returns FALSE               */
validyn(                           /* validate c as yes/no (for edtval())  */
INT c,                             /*   character to check for 'y' or 'n'  */
CHAR *stg);                        /*   display string to put the new stg  */

WGSEXP CHAR *                      /*   returns ptr to word                */
skpwht(                            /* skip spaces                          */
const CHAR *cp);                   /*   buffer to work on                  */

WGSEXP CHAR *                      /*   returns ptr to next char after word*/
skpwrd(                            /* skip non-blanks                      */
CHAR *cp);                         /*   buffer to work on                  */

WGSEXP VOID
iniscn(                            /* initialize a screen from screen file */
CHAR *filnam,                      /*   filename to load                   */
VOID *where);                      /*   buffer to place file image         */

WGSEXP CHAR *                      /*   returns ptr to where               */
cvtscn(                            /* cvt a screen image, ret its address  */
VOID *where);                      /*   buffer to convert                  */

WGSEXP GBOOL                       /*   returns TRUE=all digits            */
alldgs(                            /* is string all digits                 */
const CHAR *string);               /*   string to check                    */

WGSEXP GBOOL                       /*   returns TRUE=all hexidecimal digits*/
allhex(                            /* is string all hex digits             */
const CHAR *string);               /*   string to check                    */

                                   /*   rets # contiguous non-target bytes */
                                   /*   rets 0 to limit-1 => byte found    */
WGSEXP UINT                        /*   rets limit => byte not found       */
scanch(                            /* fast scan a byte string for a byte   */
const CHAR *bytes,                 /*   byte string                        */
CHAR target,                       /*   target byte                        */
INT limit);                        /*   max number of bytes to scan        */

                                   /*   returns index of 1st occurrence    */
WGSEXP UINT                        /*   or returns limit if none found     */
scanstg(                           /* scan block of bytes for a string     */
const CHAR *bytes,                 /*   bytes to scan                      */
const CHAR *target,                /*   string sought ('\0' terminated)    */
INT limit);                        /*   number of bytes to scan            */

                                   /*   returns index of 1st occurrence    */
WGSEXP UINT                        /*   or returns limit if none found     */
scanmem(                           /* scan one block of bytes for another  */
const CHAR *bytes,                 /*   bytes to scan                      */
const CHAR *target,                /*   bytes sought                       */
INT limit,                         /*   number of bytes to scan            */
INT ntarget);                      /*   number of bytes sought             */

WGSEXP VOID
rmvwht(                            /* remove all white space from a string */
CHAR *string);                     /*   string to operate on               */

WGSEXP CHAR *                      /*   returns ptr to buff                */
ibm2ans(                           /* cvt IBM color disp attr to ansi seq  */
CHAR attr,                         /*   IBM display attribute 00-FF        */
CHAR *buff);                       /*   max lgth of output: 14 bytes + term*/

WGSEXP CHAR *                      /*   returns ptr to message buffer      */
getasc(                            /* like getmsg() but cvts EOLs to \r\n  */
INT msgnum);                       /*   message number to read             */

WGSEXP VOID
prfasc(                            /* prints msg with EOLs cvt'd to \r\n   */
INT msgnum,                        /*   message number to read             */
...);                              /*   variable arguments                 */

WGSEXP SHORT                       /*   returns number of blanks removed   */
depad(                             /* strip trailing whitespace & ^Z       */
CHAR *string);                     /*   string to depad                    */

WGSEXP CHAR *                      /*   returns pointer to original string */
unpad(                             /* strip trailing white space           */
CHAR *cp);                         /*   string to unpad                    */

WGSEXP CHAR *                      /*   return NULL if vblnam not found    */
msgscan(                           /* scan for vblnam in msgfil, no 'T'/'S'*/
CHAR *msgfil,                      /*   .MSG file to scan (w/ .MSG ext.)   */
CHAR *vblnam);                     /*   variable name to scan for          */

WGSEXP CHAR *                      /*   return NULL if vblnam not found    */
mstscan(                           /* 'S' and 'T' type compatible msgscan  */
CHAR *msgfil,                      /*   .MSG file to scan (w/ .MSG ext.)   */
CHAR *vblnam,                      /*   variable name to scan for          */
INT maxsiz);                       /*   maximum buffer size for option     */

WGSEXP VOID
setcnf(                            /* set a CNF option equal to a value    */
CHAR *optnam,                      /*   option name                        */
CHAR *optval);                     /*   option value to set it to          */

WGSEXP VOID
applyem(                           /* apply prior setcnf()'s to a MSG file */
CHAR *filnam);                     /*   filename (including .MSG) to write */

VOID WGSEXP
padfld(                            /* pad stg with blanks for len          */
CHAR *stg,                         /*   string to pad                      */
INT len);                          /*   length to pad                      */

WGSEXP INT                         /*   returns length of string           */
strpln(                            /* computes len of stg w/o spaces or ^Z */
const CHAR *string);               /*   string to examine                  */

WGSEXP CHAR *                      /*   returns ptr to string              */
stpans(                            /* strip ANSI sequences from a string   */
CHAR *str);                        /*   string to strip ANSI from          */

WGSEXP CHAR*                       /*   returns ptr to destination buffer  */
stpcpy(                            /* copy a string with limit             */
CHAR* dst,                         /*   destination buffer                 */
CHAR const* src);                  /*   source buffer                      */

WGSEXP CHAR *                      /*   returns ptr to string              */
strstp(                            /* strip a character from a string      */
CHAR *str,                         /*   stg to strip from, NUL-terminated  */
CHAR ch);                          /*   character to strip (0x01 to 0xFF)  */

WGSEXP CHAR *                      /*   returns ptr to string              */
strrpl(                            /* replace characters in a string       */
CHAR *str,                         /*   string to do replacing in, NUL-term*/
CHAR och,                          /*   character to replace (0x01 to 0xFF)*/
CHAR nch);                         /*   new character (0x01 to 0xFF)       */

WGSEXP INT                         /*   returns number of remaining bytes  */
memstp(                            /* strip a byte from a block of bytes   */
CHAR *block,                       /*   block to strip from                */
INT nbytes,                        /*   number of bytes in block           */
CHAR byt);                         /*   byte to strip (0x00 to 0xFF)       */

WGSEXP VOID *                      /*   returns ptr to buffer              */
memrpl(                            /* replace bytes in a buffer            */
VOID *buf,                         /*   buffer to do replacing in          */
CHAR oldByte,                      /*   byte to replace                    */
CHAR newByte,                      /*   new byte                           */
size_t bufSiz);                    /*   size of buffer                     */

WGSEXP INT                         /*   ret the actual non-ANSI len of stg */
noalen(                            /* calculate non-ANSI length            */
CHAR *stg);                        /*   ANSI string to get length of       */

WGSEXP CHAR *                      /*   returns ptr to string              */
skpans(                            /* ret a ptr to the first non-ANSI byte */
CHAR *stg);                        /*   string to skip ANSI in             */

WGSEXP INT                         /*   rets 1=read string, 0=no room/ EOF */
fgetstg(                           /* read a NUL-terminated stg from a file*/
CHAR *stg,                         /*   dest (always NUL-terminated)       */
INT n,                             /*   max # of bytes to write, incl NUL  */
FILE *stream);                     /*   file pointer                       */

WGSEXP VOID
sortstgs(                          /* quick shell-sort of strings          */
CHAR **stgs,                      /*   array of strings to sort           */
INT num);                          /*   number of strings to sort          */

VOID
setcrit(VOID);                     /* critical error handler               */

WGSEXP VOID
pascrit(VOID);                     /* crit error handler (passive flavor)  */

WGSEXP INT                         /*   returns index of character in stg  */
stgidx(                            /* find occur of a character in a stg   */
CHAR *string,                      /*   string to search                   */
CHAR ch);                          /*   character to search for            */

WGSEXP GBOOL                       /*   returns TRUE=under windows         */
undwin(VOID);                      /* are we under Windows?                */

WGSEXPV(SHORT) selatr;             /* attr for currently selected choice   */
WGSEXPV(SHORT) nslatr;             /* attr for other choices on the screen */
WGSEXPV(SHORT) curchc;             /* choice number currently selected     */
WGSEXPV(SHORT) fstchc;             /* 1st choice currently shown in window */

WGSEXP SHORT                       /*   returns choice num or -ESC for ESC */
choose(                            /* have user pick one of the choices    */
SHORT n,                           /*   number of choices offered user     */
CHAR *chcs[],                      /*   text of choices offered to user    */
SHORT upx,                         /*   upper-left x coordinate            */
SHORT upy,                         /*   upper-left y coordinate            */
SHORT lox,                         /*   lower-right x coordinate           */
SHORT loy,                         /*   lower-right y coordinate           */
GBOOL escok);                      /*   accept an ESCAPE to quit?          */

WGSEXP SHORT                       /*   returns choice num or -ESC for ESC */
choowd(                            /* choose one -- with a default         */
CHAR *chcs[],                      /*   choices offered (NULL-term'ed)     */
SHORT fc,                          /*   initial (default) choice index     */
SHORT upx,                         /*   upper-left x coordinates           */
SHORT upy,                         /*   upper-left y coordinates           */
SHORT lox,                         /*   lower-right x coordinates          */
SHORT loy,                         /*   lower-right y coordinate           */
GBOOL escok);                      /*   accept an ESCAPE to quit?          */

WGSEXP SHORT                       /*   returns choice num or -ESC for ESC */
choout(VOID);                      /* choose-an-option utility             */

WGSEXP VOID
supchc(                            /* set-up to offer choices to user      */
SHORT n,                           /*   number of choices offered user     */
CHAR *chcs[],                      /*   text of choices offered to user    */
SHORT upx,                         /*   upper-left x coordinate            */
SHORT upy,                         /*   upper-left y coordinate            */
SHORT lox,                         /*   lower-right x coordinate           */
SHORT loy,                         /*   lower-right y coordinate           */
GBOOL escok);                      /*   accept an ESCAPE to quit?          */

WGSEXP SHORT                       /*   returns choice num or -ESC for ESC */
hdlchc(                            /* handle keystroke from user           */
SHORT c);                          /*   input character                    */

WGSEXP VOID
dspchc(VOID);                      /* display current list of choices      */

WGSEXP VOID
jmp2chc(                           /* jump to a choice, with "centering"   */
SHORT fc);                         /*   choice to jump to                  */

WGSEXPV(SHORT) bgperc;             /* 0-100% of the most recent bargph()   */
WGSEXPV(SHORT) bgpos;              /* char offset of bar from last bargph()*/

WGSEXP CHAR *                      /*   returns ptr to bar                 */
bargph(                            /* compute a bar graph string           */
SHORT width,                       /*   character width (1 to 80)          */
LONG num,                          /*   numerator                          */
LONG den);                         /*   denominator                        */

WGSEXP CHAR *                      /* returns pointer to destination buffer*/
gcitoa(                            /*   converts integer to string         */
INT value,                         /*   value to be converted              */
CHAR *dstbuf);                     /*   destination buffer                 */

WGSEXP VOID
gcdelay(                           /* sleeps for msecs milliseconds        */
ULONG msecs);                      /*   number of milliseconds to sleep    */

WGSEXP VOID
bgnlog(                            /* begin debug logging                  */
CHAR *filnam);                     /*   filename to write to               */

WGSEXP VOID
clslog(VOID);                      /* closes debug log                     */

WGSEXP VOID
inform(                            /* write to debug log                   */
CHAR *fmt,                         /*   control string                     */
...);                              /*   variable arguments                 */

WGSEXP VOID                        /*   first prints as hex, then as chars */
infbyt(                            /* print detailed info about a string   */
CHAR *str,                         /*   identifier string                  */
CHAR *buf,                         /*   buffer to print                    */
INT len);                          /*   length of buffer                   */

WGSEXP ULONG                       /*   returns amount of memory available */
sizmem(VOID);                      /* gets available memory                */

WGSEXP VOID
opnsysinf(VOID);                   /* open system information file/memory  */

WGSEXP VOID
clssysinf(VOID);                   /* close system information file/memory */

WGSEXP GBOOL                       /*   returns TRUE=prognam is found      */
isrunpgm(                          /* find a runnable program by name      */
struct ffblk *fb,                  /*   ffblk structure to fill in        */
CHAR *prognam);                    /*   program name to look for w/o ext   */

WGSEXP VOID
bbshome(VOID);                     /* change to server home directory      */

WGSEXP GBOOL                       /* return TRUE=case insens. filenames   */
needupc(VOID);                     /*   i.e. use uppercase file names      */

GBOOL                              /* return TRUE=big endian machine       */
isbigend(VOID);                    /*   is this machine big endian?        */

WGSEXP CHAR *                      /*   returns ptr to value of option     */
getoption(                         /* get opt from wgserv.cfg/environment  */
CHAR *option);                     /*   option to examine                  */

//WGSEXP ULONG
//hrtval(VOID);                      /* get btuhrt in a safe manner (dsairp) */

                                   /* debug checking declarations section  */
#if defined (DEBUG) || defined (GCWINNT)
#define malloc      galmalloc
#define free        galfree
#endif // DEBUG || GCWINNT

#ifdef DEBUG
#define ASSERT(cnd) ((cnd) ? ((VOID)0) \
               : galastfail(__FILE__" "FILREV,__LINE__,#cnd));

#define ASSERTM(cnd,msg) ((cnd) ? ((VOID)0) \
                 : galastfail(__FILE__" "FILREV,__LINE__,msg));

#else // DEBUG
#define ASSERT(c)    ((VOID)0)
#define ASSERTM(c,m) ((VOID)0)
#endif // DEBUG

WGSEXPV(ULONG) nmfree;             /* count free()'s                       */
WGSEXPV(ULONG) nmalloc;            /* count malloc()'s                     */

#ifdef GCDOSP
WGSEXPV(GBOOL) memdbg;             /* set FALSE to disable special sel dbg */
WGSEXPV(GBOOL) alcdbg;             /* (memdbg) FALSE= low on selectors     */
WGSEXPV(ULONG) nmskip;             /* skip this many initial malloc's      */
WGSEXPV(ULONG) nmsctr;             /* counter up to nmskip                 */
WGSEXPV(ULONG) nmspec;             /* count of special malloc() sel's      */
WGSEXPV(ULONG) nmbust;             /* count special sel's averted          */
WGSEXPV(ULONG) nmlinr;             /* number of linear conv errors         */
#endif // GCDOSP

WGSEXP VOID *                             /*   returns ptr to newly alloc'd space */
galmalloc(                         /* Galacticomm's malloc() for debugging */
UINT size);                        /*   size to malloc()                   */

WGSEXP VOID
galfree(                           /* Galacticomm's free() for debugging   */
VOID *block);                      /*   ptr to block to free()             */

WGSEXP VOID
galastfail(                        /* assertion failure                    */
CHAR *filinf,                      /*   source file name and revision      */
ULONG linnum,                      /*   source file line number            */
CHAR *message);                    /*   ad hoc message (no %-parms allowed)*/

WGSEXP VOID
memdbgrpt(                         /* report on special memory debugging   */
FILE *fp);                         /*   open file to report to             */

                                   /* defines for assertion failure mode   */
#define ASTIGN 1                   /*   ignore                             */
#define ASTRPT 2                   /*   make report to disk (see astrptfil)*/
#define ASTCAT 3                   /*   call catastro(), shut down immed.  */

WGSEXPV(SHORT) astmode;            /* assertion failure mode:              */
WGSEXPV(CHAR*) astrptfil;          /* ASTRPT: assertion failure report file*/

WGSEXPV(CHAR*) prfbuf;             /* output buffer staging area           */
WGSEXPV(CHAR*) prfptr;             /* pointer to prf buffer                */

WGSEXP VOID
iniprf(                            /* initialize prf buffer                */
CHAR *pbuf,                        /*   ptr to dest of prf buffer          */
INT psiz);                         /*   size of prf buffer                 */

WGSEXP VOID
outprf(                            /* output prfbuf to usrnum              */
INT usrnum);                       /*   usrnum to send data to             */

WGSEXP VOID
prf(                               /* puts data into prfbuf                */
const char *fmt,                   /*   control string                     */
...);                              /*   variable arguments                 */

WGSEXP VOID
prfmsg(                            /* puts data into prfbuf using msg block*/
INT msgnum,                        /*   message number to use              */
...);                              /*   variable arguments                 */

WGSEXP VOID
clrprf(VOID);                      /* clears prfbuf and reset pointer      */

WGSEXP VOID
dsairp(VOID);                      /* disable interrupts on some platforms */

WGSEXP VOID
enairp(VOID);                      /* enable interrupts on some platforms  */

WGSEXP INT                         /*   returns odd byte                   */
odd(                               /* makes parity of byte passed odd      */
CHAR byt);                         /*   byte to be made odd parity         */

WGSEXP CHAR                        /*   returns 'Y' or 'N' based on clingo */
lingyn(                            /* translate input to Yes/No            */
CHAR c);                           /*   character to translate             */

WGSEXPV(VOID*) prfbuffers;         /* tiled array of prf() output buffers  */
WGSEXPV(CHAR**) prfpointers;       /* array of ptrs into the prfbuffers[]  */
WGSEXPV(CHAR*) linuse;             /* return array of cklonl()             */

WGSEXPV(INT) mltflg;               /* which prfbuffer to use               */

WGSEXP VOID
inimlt(                            /* initialize multilingual prf-stuff    */
UINT pbsize);                      /*   size of each buffer                */

WGSEXP VOID
clrmlt(VOID);                      /* clear all buffers and pointers       */

WGSEXP VOID
cklonl(VOID);                      /* check languages represented online   */

WGSEXP VOID
outmlt(                            /* output multilingual message to a user*/
INT chan);                         /*   channel number to output to        */

WGSEXP VOID
prfmlt(                            /* multilingual version of prfmsg()     */
INT msgnum,                        /*   message number to use              */
...);                              /*   variable arguments                 */

WGSEXP VOID
pmlt(                              /* multilingual version of prf()        */
CHAR *fmt,                         /*   control string                     */
...);                              /*   variable arguments                 */

WGSEXP GBOOL                       /*   returns TRUE=good stg              */
goodstg(                           /* checks to see if the stg ptr is good */
const CHAR *ptr);                  /*   ptr to check                       */

WGSEXPV(CHAR*) pinstd;             /* ptr error message string for bad ptrs*/

WGSEXP GBOOL                       /*   returns TRUE=good ptr              */
goodptr(                           /* checks to see if the ptr is good     */
VOID *ptr);                        /*   ptr to check                       */

WGSEXP GBOOL                       /*   returns TRUE=good function ptr     */
goodcptr(                          /* checks for valid function ptr        */
const VOID *ptr);                  /*   function ptr to check              */

WGSEXP UINT                        /*   returns readable bytes <= nbytes   */
goodblk(                           /* is blk of memory addressable w/o GP? */
const VOID *ptr,                   /*   pointer to block of bytes          */
UINT nbytes);                      /*   number of bytes                    */

WGSEXP CHAR *                      /*   returns ptr to intstg              */
commas(                            /* add commands to integer of any length*/
CHAR *intstg);                     /*   string to convert in-place         */

WGSEXP INT                         /*   returns taskid                     */
initask(                           /* start up a new task                  */
VOID (*tskaddr)(INT taskid));      /*   function address to invoke         */

WGSEXP VOID
mfytask(                           /* modify the function addr of a task   */
INT taskid,                        /*   taskid to modify                   */
VOID (*tskaddr)(INT taskid));      /*   new function address to invoke     */

WGSEXP VOID
prctask(VOID);                     /* process the next task (round robin)  */

WGSEXP SHORT                       /*   returns next 'x' position          */
bigdigit(                          /* display a great big digit            */
const CHAR *font,                  /*   one of the digitNxN font stuctures */
SHORT dig,                         /*   digit 0-9 or '0' through '9'       */
SHORT x,                           /*   left of 3 columns, 0 to 78         */
SHORT y);                          /*   top of 3 rows, 0 to 22             */

WGSEXPV(CHAR) digit2x3[];          /* digits 2 chars wide, 3 chars high    */
WGSEXPV(CHAR) digit2x3b[];         /* bold digits 2 chars wd, 3 chars high */
WGSEXPV(CHAR) digit3x3[];          /* digits 3 chars wide, 3 chars high    */
WGSEXPV(CHAR) digit2x5[];          /* digits 2 chars wide, 5 chars high    */

WGSEXPF(VOID,hdlgpr)(CHAR *);      /* GP report interceptible vector       */

WGSEXP INT                         /*   returns num of arrs in use just now*/
newarr(                            /* create a new array, return a handle  */
INT incsiz,                        /*   increment size within the new array*/
UINT elemsiz);                     /*   size of each element in the array  */

WGSEXP VOID *                      /*   returns ptr to your array element  */
add2arr(                           /* add array element, return ptr to it  */
INT arrhdl,                        /*   handle of the array to add to      */
VOID *newelem);                    /*   new element (NULL to set it to 0)  */

WGSEXP VOID *                      /*   rets ptr to base address of array  */
arrbas(                            /* get the base address of an array     */
INT arrhdl);                       /*   handle of the array desired        */

WGSEXP INT                         /*   returns number of elements in array*/
ninarr(                            /* get the number of elements in array  */
INT arrhdl);                       /*   handle of the array desired        */

WGSEXP VOID *                      /*   rets ptr to desired array element  */
arrelem(                           /* get a ptr to an array element        */
INT arrhdl,                        /*   handle of the array in question    */
INT index);                        /*   index of the element desired       */

WGSEXP CHAR *                      /*   return any-delim'd string's substg */
itemidxd(                          /* search for any delim'd stg's substg  */
const CHAR *ctlstg,                /*   string to search                   */
INT index,                         /*   index of substring to return       */
const CHAR *delim);                /*   string to search for               */

WGSEXP CHAR *                      /*   return tab-delim'd string's substg */
itemidx(                           /* search for tab-delim'd stg's substg  */
const CHAR *ctlstg,                /*   string to search                   */
INT index);                        /*   index of substring to return       */

WGSEXP INT                         /*   # of occurences of delim'd substg  */
itemcntd(                          /* instances of delimited substrings    */
const CHAR *ctlstg,                /*   string to search                   */
const CHAR *delim);                /*   string to search for               */

WGSEXP INT                         /*   # of occurences tab-delim'd substg */
itemcnt(                           /* instances of TAB delim'd substrings  */
const CHAR *ctlstg);               /*   string to search                   */

WGSEXP CHAR *                      /*   returns ptr to name of module      */
gmdnam(                            /* get a module's name from .MDF file   */
const char *mdfnam);               /*   name of module's .MDF file         */

WGSEXP INT                         /*   returns number of dynamic Btrieve f*/
gnumdb(                            /* get # of dynamic Btrieve files       */
CHAR *mdfnam);                     /*   .MDF file to get number from       */

WGSEXP VOID
snumdb(                            /* set # of dynamic Btrieve files       */
CHAR *mdfnam,                      /*   .MDF file to set number in         */
INT ndbfils);                      /*   # of dynamic Btrieve files to set  */

WGSEXP CHAR *                      /*   returns ptr to value of option     */
scnmdf(                            /* low-level .MDF scanner utility       */
CHAR *mdfnam,                      /*   .MDF file to scan                  */
CHAR *linpfx);                     /*   for this line prefix               */

WGSEXP CHAR *                      /*  rets module name from MDF/DMD file  */
mdfodmd(                           /* get .MDF or .DMD name from .MDF name */
CHAR *mdfnam);                     /*   .MDF file name to get name for     */

WGSEXP GBOOL                       /*   returns FALSE if str not numeric   */
isfxval(                           /* convert numeric dpk suffix to int    */
UINT *result,                      /*   buffer to place result             */
CHAR *str);                        /*   numeric portion of suffix string   */
                                   /*   (takes olthan/ogthan into account) */

WGSEXP GBOOL                       /*   returns FALSE if str not numeric   */
lsfxval(                           /* convert numeric dpk suffix to long   */
ULONG *result,                     /*   buffer to place result             */
CHAR *str);                        /*   numeric portion of suffix string   */
                                   /*   (takes olthan/ogthan into account) */

WGSEXP VOID
inipool(                           /* initialize dynamic pool API          */
CHAR *swpfil);                     /*   swap file for on-disk memory areas */

WGSEXP INT                         /*   pool handle                        */
newpool(                           /* create a new pool of memory areas    */
UINT areasiz,                      /*   size of each area within pool      */
INT nareas,                        /*   number of areas within pool        */
INT ninmem);                       /*   number of areas in memory at once  */

WGSEXP INT                         /*   handle to area, or -1 if none avail*/
rsvarea(                           /* reserve a memory area within pool    */
INT poolhdl);                      /*   handle to the pool (from newpool())*/

WGSEXP VOID *                      /*   returns ptr to reserved mem area   */
areaptr(                           /* get pointer to a reserved mem area   */
INT poolhdl,                       /*   handle to the pool (from newpool())*/
INT areahdl);                      /*   handle to the area (from rsvarea())*/

WGSEXP VOID
unrarea(                           /* unreserve a memory area within pool  */
INT poolhdl,                       /*   handle to the pool (from newpool())*/
INT areahdl);                      /*   handle to the area (from rsvarea())*/

WGSEXP VOID
clspool(VOID);                     /* close down dynamic pool API          */

WGSEXP CHAR *                      /*   return pointer to registration no. */
getrno(VOID);                      /* gets system registration number      */

WGSEXP CHAR *                      /*   returns dststg                     */
strins(                            /* insert a string before another       */
CHAR *dststg,                      /*   original and destination string    */
CHAR *insstg,                      /*   string to insert                   */
INT sizdst);                       /*   room at dststg, including '\0'     */

WGSEXP USHORT                      /*   returns 16-bit CRC                 */
crc16(                             /* compute 16-bit CRC                   */
const CHAR *stg,                   /*   byte array                         */
UINT nbytes);                      /*   number of bytes                    */

WGSEXP ULONG                       /*   returns 32-bit CRC                 */
crc32(                             /* compute 32-bit CRC                   */
const CHAR *stg,                   /*   byte array                         */
UINT nbytes);                      /*   number of bytes                    */

#define CRC32GOOD 0xDEBB20E3L

/*
         for generating 16-bit CRC:  store    crc16(stg,nbytes)
for testing validity of 16-bit CRC:  compare  crc16(stg,nbytes) == 0
         for generating 32-bit CRC:  store   ~crc32(stg,nbytes)
for testing validity of 32-bit CRC:  compare  crc32(stg,nbytes) == CRC32GOOD
*/

/* The following low-level CRC computation macros and the tables they use  */
/* come from Omen Technology's CRCTAB.H source file.                       */

#define updcrc(cp,crc) (crctab[((crc>>8)&255)]^(crc<<8)^cp)
#define UPDC32(b,c) (cr3tab[((short)c^b)&0xff]^((c>>8)&0x00FFFFFFL))

WGSEXPV(USHORT) crctab[];          /* crctab calculated by Mark G. Mendel  */
WGSEXPV(LONG) cr3tab[];            /* CRC polynomial 0xedb88320            */

WGSEXP CHAR                        /*   returns 8-bit checksum             */
cksum8(                            /* compute 8-bit checksum of byte array */
CHAR *stg,                         /*   byte array                         */
INT nbytes);                       /*   number of bytes                    */

WGSEXP USHORT                      /*   returns 16-bit checksum            */
cksum16(                           /* compute 16-bit checksum of word array*/
USHORT *stg,                       /*   word array                         */
INT nwords);                       /*   number of words (nbytes/2)         */

WGSEXP GBOOL
wcmatch(                           /* wild-card match input against picstg */
CHAR *inpstr,                      /*   candidate literal string           */
CHAR *picstg);                     /*   picture (wild-card) string         */

WGSEXP CHAR *                      /*   return pointer to modified string  */
skptwht(                           /* skip true preceding whitespace       */
const CHAR *string);               /*   string to process                  */

WGSEXP CHAR *                      /*   returns copy of ptr to dest        */
strmove(                           /* move string w/overlapping src/dest   */
CHAR *dst,                         /*   destination                        */
const CHAR *src);                  /*   source                             */

WGSEXP CHAR *                      /*   ptr to first char on line or NULL  */
nextLine(                          /* find next line in a string           */
const CHAR *str,                   /*   string to search                   */
const CHAR *eol);                  /*   end-of-line marker string          */

WGSEXP INT
hexval(                            /* get hexadecimal value from digit     */
CHAR dig);                         /*   hexadecimal digit to convert       */

WGSEXP CHAR
hexdig(                            /* get hexadecimal value from digit     */
UINT val);                         /*   value to convert                   */

WGSEXP INT                         /*   Integer value to return            */
xtoi(                              /* Convert Hex string to Integer        */
const CHAR* pszHex);               /*   Hex string to convert              */

WGSEXP LONG                        /*   Long value to return               */
xtol(                              /* Convert Hex string to Long           */
const CHAR* pszHex);               /*   Hex string to convert              */

#define PFN_MAXALC 65520U          /* max size of profanity list buffer    */
#define PFNLISTFILE "galpfn.dta"   /* default profanity list data file     */

                                   /* readpfn() return codes               */
#define RDPFN_OK       0           /*   list read successfully             */
#define RDPFN_OVERFLOW 1           /*   buffer too small                   */
#define RDPFN_EOF      2           /*   unexpected end of file             */
#define RDPFN_INVALID  3           /*   invalid list file                  */
#define RDPFN_FOPEN    4           /*   unable to open list file           */

WGSEXPV(CHAR*) pfnptr;             /* ptr to the profanity                 */
WGSEXPV(CHAR*) pfnlst;             /* pointer to compiled profanity list   */

WGSEXP INT                         /*   error code                         */
readpfn(                           /* read profanity data file             */
const CHAR *filnam,                /*   profanity data file path+name      */
CHAR **pfnbuf);                    /*   ptr to pfn list buffer (or NULL)   */

WGSEXP INT                         /*   returns level of profanity         */
profan(                            /* checks level of profanity in string  */
CHAR *stg);                        /*   string to check                    */


#include "server.h"

#define NOPROCEED "\nUnable to proceed, another " SVR_NAME " process is active."

#ifdef GCWINNT

WGSEXP GBOOL                       /*   return TRUE if it is WinNT         */
isWinNT(VOID);                     /* checks for Windows NT                */

WGSEXP CHAR *                      //   return error message
getErrorText(                      // converts error code into text
ULONG errorCode,                   //   error code
CHAR *pBuf,                        //   message buffer
ULONG bufSize);                    //   buffer size

WGSEXP CHAR *                      //   return error message
getLastErrorText(                  // converts "Lasr Error" code into text
CHAR *pBuf,                        //   message buffer
ULONG bufSize);                    //   buffer size

WGSEXP GBOOL                       //   return TRUE - can run the program
canRunWGS(VOID);                   // can run WGSERVER.EXE

WGSEXP GBOOL                       //   return TRUE - can run the program
canRunGroup(VOID);                 // can run "group" exe (former .BAT)

WGSEXP GBOOL                       //   return TRUE - can run the program
canRunUtil(VOID);                  // can run an offline utility

WGSEXP GBOOL                       //   return TRUE - can run WGSINT.EXE
canRunWGSINT(VOID);                // can run an WGSINT utility

WGSEXP GBOOL                       //   return TRUE-Ok
allowWGSINT(VOID);                 // close WGSINT's event to allow it to run

WGSEXP GBOOL                       //   return TRUE - can run WGSCNF.EXE
canRunWGSCNF(VOID);                // can run WGSCNF.EXE

#endif // GCWINNT

typedef                                                                      \
INT                                /*   > 0 = target > test, etc.          */\
(*binSearchComp)(                  /* binary search util comparison func   */\
const VOID *target,                /*   target object                      */\
const VOID *array,                 /*   array object                       */\
ULONG index);                      /*   index of array element to test     */

WGSEXP ULONG                       /*   index or numElems if not found     */
binSearch(                         /* generic binary search utility        */
const VOID *target,                /*   target object to find              */
const VOID *array,                 /*   array object                       */
ULONG numElems,                    /*   number of elements in array object */
binSearchComp compFunc);           /*   comparison function                */

WGSEXP ULONG                       /*   index where element should be      */
binFindNear(                       /* generic binary find nearest utility  */
INT *lastComp,                     /*   result of last comparison          */
const VOID *target,                /*   target object                      */
const VOID *array,                 /*   array object                       */
ULONG numElems,                    /*   number of elements in array object */
binSearchComp compFunc);           /*   comparison function                */

/*  This function was created to mask problems in the Borland Runtime      */
/*  Library.  The mktemp() function would only return 26 unique file names */
WGSEXP CHAR*                       /*  Pointer to Template or NULL         */
gmktemp(                           /* Create temporary file                */
CHAR* Template);                   /*  Path to create file.  Ends "XXXXXX" */

#define mktemp(x)        gmktemp(x)


/* Wrappers for Standard C Library functions */

WGSEXP CHAR*                        /*  returns ptr to copied string        */
gstrcpy(                            /* copy a string                        */
CHAR* destination,                  /*  destination string buffer           */
const CHAR* source);                /*  source string to copy               */


#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __GCOMM_H
