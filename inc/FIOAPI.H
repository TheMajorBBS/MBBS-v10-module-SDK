/***************************************************************************
 *                                                                         *
 *   FIOAPI.H                                                              *
 *                                                                         *
 *   Copyright (c) 1996-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   File I/O API subsystem.                                               *
 *                                                                         *
 *                                        - Craig Yap        01/15/96      *
 *                                        - Richard Skurnick 01/15/96      *
 *                                        - Ilya Minkin      01/15/96      *
 *                                                                         *
 ***************************************************************************/

#ifndef __FIOAPI_H
#define __FIOAPI_H

#ifdef UNIX
#include <sys/types.h>
#include <dirent.h>
#else
#ifdef _MSC_VER
#include <direct.h>
#include <wtypes.h>
#else
#include <dir.h>
#endif
#include <io.h>
#include <share.h>
#endif // UNIX

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef _FFBLK_DEF
#define _FFBLK_DEF
struct  ffblk   {
    long            ff_reserved;
    long            ff_fsize;
    unsigned long   ff_attrib;
    unsigned short  ff_ftime;
    unsigned short  ff_fdate;
    char            ff_name[260];
};
#endif

#ifndef _FFBLK_EXTRA_DEF
#define _FFBLK_EXTRA_DEF
struct xffblk {
    struct ffblk*   fbptr;
    HANDLE          ff_handle;
    UINT            s_attrib;
    WIN32_FIND_DATA nfblock;
};
#endif
                                   // OS defines
#ifdef UNIX
#define SL            '/'
#define SLS           "/"
#define STAR          "*"
#define STR_EOL       "\n"
#define CHR_EOL       '\n'
#define MKDIR(dir)    mkdir(dir, 0700)
#else
#define SL            '\\'
#define SLS           "\\"
#define STAR          "*.*"
#define STR_EOL       "\r\n"
#define CHR_EOL       '\r'
#define MKDIR(dir)    mkdir(dir)
#endif //UNIX

                                   /* fopen() 2nd parameter                */
#ifdef UNIX
#   define FOPRA   "r"                /* read ASCII mode                      */
#   define FOPWA   "w"                /* write ASCII mode                     */
#   define FOPRWA  "r+"               /* read/write ASCII mode                */
#   define FOPWRA  "w+a"              /* write/read ASCII mode                */
#   define FOPAA   "a"                /* append ASCII mode                    */
#else
#   define FOPRA  "rt"                /* read ASCII mode                      */
#   define FOPWA  "wt"                /* write ASCII mode                     */
#   define FOPRWA "r+t"               /* read/write ASCII mode                */
#   define FOPWRA "w+t"               /* write/read ASCII mode                */
#   define FOPAA  "at"                /* append ASCII mode                    */
#endif // UNIX

#define FOPRB  "rb"                /* read binary mode                     */
#define FOPWB  "wb"                /* write binary mode                    */
#define FOPRWB "r+b"               /* read/write binary mode               */
#define FOPWRB "w+b"               /* write/read binary mode               */
#define FOPAB  "ab"                /* append binary mode                   */

#ifdef _MSC_VER
#   define MAXPATH     _MAX_DRIVE+_MAX_DIR+_MAX_FNAME+_MAX_EXT
#   define DRIVE       0x01
#   define DIRECTORY   0x02
#   define FILENAME    0x04
#   define EXTENSION   0x08
#endif // _MSC_VER

#ifdef GCV2
#   define GCSTRPTH MAXPATH           /* For storage in databases of path+file*/
#else
#   define GCSTRPTH 261               /* For storage in databases of path+file*/
#endif // GCV2
#ifdef GCDOS
#   define GCMAXPTH MAXPATH           /* For data entry                       */
#else
#   define GCMAXPTH 261               /* For data entry                       */
#endif // GCDOS
#ifdef GCV2
#   define GCSTRFNM 13                /* For storage in databases             */
#else
#   define GCSTRFNM 64                /* For storage in databases             */
#endif // GCV2
/*
#ifndef GCTNT86
#define GCMAXFNM 64                   For non-TNT OS's (for future revs.)  */
#define GCMAXFNM 13                /* in use for WG 2.0 only               */

#define GCMAXFILE 8                /* max file name w/o extension and dot  */
#define GCMAXEXT  3                /* max extension w/o dot                */

                                   /* File Attr Masks  (used by fnd1st())  */
#define FAMRON 0x01                /* read only                            */
#define FAMHID 0x02                /* hidden                               */
#define FAMSYS 0x04                /* system                               */
#define FAMVID 0x08                /* volume id                            */
#define FAMDIR 0x10                /* sub-directory                        */
#define FAMARC 0x20                /* archive                              */

WGSEXPV(CHAR) deldirerr[GCMAXPTH+40];/* error message when deldir() != 0     */

                                   /*   for filxxxlst() functions          */
#define MAXFLL 60                  /*   max length of download file list   */
#define MAXFLP 60                  /*   max length of fll1st() path        */

#define BLKSIZ 512                 /* maximum copy block size              */
#define CPBSIZ 16384               /* maximum size for copy buffer (DOS)   */

struct filblklst { /* fil1stlst()/filnxtlst() file-list scanning structure */
     struct ffblk fb;             /*   structure used by fnd1st()/fndnxt()*/
     CHAR list[MAXFLL+1];          /*   list of files                      */
     CHAR pathpf[MAXFLP+1];        /*   path prefix for each file          */
};


WGSEXPV(LONG) ztzone;              /* Seconds between GMT and local time   */

                                   /* global vars set by cntdir()/cntdirs()*/
WGSEXPV(LONG) numfils;             /* total number of files                */
WGSEXPV(LONG) numbyts;             /* total number of bytes                */
WGSEXPV(LONG) numbytp;             /* # bytes + wasted part of last cluster*/
WGSEXPV(LONG) numdirs;             /* total number of subdirectories       */

                                   /* defines for the fileparts() function */
#define GCPART_PATH 0              /*   drivespec and path                 */
#define GCPART_FNAM 1              /*   filename w/ ext                    */
#define GCPART_FILE 2              /*   filename w/o ext                   */
#define GCPART_EXTN 3              /*   extension only                     */
#define GCPART_DRVS 4              /*   drivespec only                     */

WGSEXP CHAR *                      /*   returns pointer to dstbuf or ""    */
fileparts(                         /* grab required part of a full filename*/
SHORT filpart,                     /*   part to be returned                */
const CHAR *fullname,              /*   full filename to be worked on      */
CHAR *dstbuf,                      /*   destination buffer for data        */
SHORT dstsiz);                     /*   destination buffer size            */

WGSEXP GBOOL                       /*   returns TRUE=copy successful       */
cpyutl(                            /* copy file utility                    */
const CHAR *src,                   /*   source file name                   */
const CHAR *dst,                   /*   destination file names             */
const CHAR *srcmod,                /*   source fopen() mode                */
const CHAR *dstmod);               /*   destination fopen() mode           */

WGSEXP GBOOL                       /*   returns TRUE if one found          */
filspclst(                         /* any files in the first filespec?     */
struct filblklst *flp);            /*   path and file list to search       */

WGSEXP GBOOL                       /*   returns TRUE if found              */
fil1stlst(                         /* find first file in a list            */
struct filblklst *flp,             /*   struct for continuing w/ filnxtlst */
const CHAR *prefix,                /*   path prefix                        */
const CHAR *list);                 /*   list of files/path                 */

WGSEXP GBOOL                       /*   returns TRUE if one found          */
filnxtlst(                         /* find next file in list               */
struct filblklst *flp);            /*   previous filblklst to cont. search */

WGSEXP VOID
cntdir(                            /* count bytes and files in a directory */
const CHAR *path);                 /*   path name of the directory contents*/

WGSEXP VOID
cntdirs(                           /* count bytes/files in dir & its subdir*/
const CHAR *path);                 /*   path name of the directory contents*/

WGSEXP LONG                        /*  returns total file size             */
clfit(                             /* figure size of file including waste  */
LONG size,                         /*   file size in bytes                 */
USHORT clsiz);                     /*   size of clusters on this drive     */

#ifdef GCV2S
#define clsize v3clsize
#endif // GCV2S
WGSEXP UINT                        /*   returns size or 0 for error        */
clsize(                            /* get cluster size in bytes            */
const CHAR *path);                 /*   path to drive to check             */

WGSEXP GBOOL                       /*   returns TRUE=file updated          */
setFileTm(                         /* set file time & date                 */
const CHAR *fname,                 /*   file name                          */
USHORT dtim,                       /*   time to set                        */
USHORT ddat);                      /*   date to set                        */

WGSEXP GBOOL                       /*   returns TRUE=file updated          */
setFileGMT(                        /* set file time and date               */
const CHAR *fname,                 /*   file name                          */
ULONG gmt70);                      /*   time in sec since 00:00 1/1/70 GMT */

#ifdef GCV2S
#define getFileTm v3getFileTm
#endif // GCV2S
WGSEXP VOID
getFileTm(                         /* get time and date for file           */
const CHAR *fname,                 /*   file name                          */
USHORT *dtim,                      /*   time to get                        */
USHORT *ddat);                     /*   date to get                        */

#ifdef GCV2S
#define getFileGMT v3getFileGMT
#endif // GCV2S
WGSEXP ULONG                       /*   returns time and date in GMT format*/
getFileGMT(                        /* get GMT file time and date           */
const CHAR *fname);                /*   file name                          */

#ifdef GCV2S
#define dskfre v3dskfre
#endif // GCV2S
WGSEXP LONG                        /*   returns kbytes free or -1 for error*/
dskfre(                            /* number of kbytes free on a drive     */
const CHAR *path);                 /*   path on drive to check,NULL=default*/

WGSEXP GBOOL                       /*   returns TRUE=found a file          */
fnd1st(                            /* find file matching filspc and attr   */
struct ffblk *fbptr,               /*   ptr to data storage area           */
const CHAR *filspc,                /*   file spec to match                 */
INT attr);                         /*   attribute to match                 */

WGSEXP GBOOL                       /*   returns TRUE=found a file          */
fndnxt(                            /* find next file matching filspc & attr*/
struct ffblk *fbptr);              /*   ptr to data storage area           */

#ifdef _MSC_VER

WGSEXP INT
findfirst(
CHAR const* filspc,
struct ffblk* fbptr,
UINT attr);

WGSEXP INT
findnext(
struct ffblk* fbptr);

#endif // _MSC_VER

WGSEXP GBOOL                       /*   TRUE if dir matching dname exists  */
isdir(                             /* check whether a directory exists     */
const CHAR *dname);                /*   directory name to search for       */

WGSEXP GBOOL                       /*   TRUE if matching file exists       */
isfile(                            /* check for existence of file(s)       */
const CHAR *fname);                /*   filename or wildcard to check      */

#ifdef GCV2S
#define fndfile(fb,fn,a) fnd1st(fb,fn,a)
#else
WGSEXP GBOOL                       /*   TRUE if matching file found        */
fndfile(                           /* check file's existence and stats     */
struct ffblk *fb,                  /*   file info (CLOSED after findfirst) */
const char *fname,                 /*   filespec we're searching for       */
INT attr);                         /*   attribute(s) to match              */
#endif // GCV2S

WGSEXP GBOOL                       /*   TRUE if found file & converted name*/
getShortName(                      /* get DOS 8.3 version of file name     */
CHAR *shortBuf,                    /*   buffer to receive short name       */
const CHAR *filePath,              /*   complete path of file to get for   */
size_t bufSiz);                    /*   size of buffer                     */

WGSEXP CHAR *                      /*   returns converted file name        */
mkdosn(                            /* convert string to DOS file name      */
const CHAR *string);               /*   file name to convert to DOS format */

WGSEXP VOID
fixpth(                            /* add a backslash to string if needed  */
CHAR *path);                       /*   path to append                     */

WGSEXP CHAR *                      /*   copy of pointer to destination     */
makePath(                          /* combine directory and file name      */
CHAR *dst,                         /*   destination buffer                 */
const CHAR *dir,                   /*   directory name                     */
const CHAR *file,                  /*   file name                          */
size_t dstSiz);                    /*   size of destination buffer         */

WGSEXP GBOOL                       /*   TRUE=ok FALSE=err, see deldirerr[] */
deldir(                            /* delete a subdirectory & all contents */
const CHAR *dirpath);              /*   name of a directory                */

WGSEXP CHAR *                      /*   returns unique file name           */
uniqfn(                            /* create a unique filespec             */
CHAR *fspec);                      /*   original file specification        */

#ifdef GCV2S
#define ll_uniqfn(cat,fn) uniqfn(fn)
#else
WGSEXP CHAR *                      /*   returns unique file name           */
ll_uniqfn(                         /* low-level routine for unique fspec   */
GBOOL cataonerr,                   /*   catastro() on errors?              */
CHAR *fspec);                      /*   original file specification        */
#endif // GCV2S

WGSEXP CHAR *                      /*   copy of pointer to dest            */
normspec(                          /* normalize filespec to complete path  */
CHAR *dest,                        /*   dest buffer (must be GCMAXPTH long)*/
const CHAR *src);                  /*   path+file name to normalize        */

WGSEXP VOID
gmkdir(                            /* recursive version of mkdir()         */
const CHAR *dirnam);               /*   directory name to create           */

#ifdef GCV2S
#define fnmcse(s) (s)
#else
WGSEXP CHAR *                      /*   returns ptr to cvt'd fname         */
fnmcse(                            /* handles filenames before use in code */
CHAR *fname);                      /*   filename to work on                */
#endif // GCV2S

WGSEXP GBOOL                       /*   return TRUE=reserved               */
rsvnam(                            /* is a name reserved by OS for a device*/
const CHAR *name);                 /*   name to check                      */

WGSEXP GBOOL                       /*   returns TRUE=file moved            */
movefile(                          /* move file(s) from src to dest        */
const CHAR *src,                   /*   source file spec                   */
const CHAR *dest);                 /*   destination file spec              */

WGSEXP GBOOL                       /*   returns TRUE=file copied           */
copyfile(                          /* copy file(s) from src to dest        */
const CHAR *src,                   /*   source file spec                   */
const CHAR *dest);                 /*   destination file spec              */

#ifdef UNIX
LONG                               /*   returns the length of the file     */
filelength(                        /* determines length of a file          */
INT fd);                           /*   file descriptor of open file       */
#endif // UNIX

                                   /* defines for access() function        */
#ifdef UNIX
#define GCF_OK  F_OK               /*   file exists                        */
#define GCX_OK  X_OK               /*   execute or search permission       */
#define GCW_OK  W_OK               /*   write permission                   */
#define GCR_OK  R_OK               /*   read permission                    */
#define GCRW_OK (GCR_OK|GCW_OK)    /*   read/write permission              */
#else
#define GCF_OK  0x0                /*   file exists                        */
#define GCX_OK  0x01               /*   execute or search permission       */
#define GCW_OK  0x02               /*   write permission                   */
#define GCR_OK  0x04               /*   read permission                    */
#define GCRW_OK 0x06               /*   read/write permission              */
#endif // UNIX

                                   /* defines for gcfsopen                 */
#ifdef UNIX
#define  GSH_COMPAT    0           /* sets compatiblity mode               */
#define  GSH_DENYRW    1           /* deny read/write access               */
#define  GSH_DENYWR    2           /* deny write access                    */
#define  GSH_DENYRD    3           /* deny read access                     */
#define  GSH_DENYNONE  4           /* permits read/write access            */
#define  GSH_DENYNO    5           /* permits read/write access            */
#else
#define  GSH_COMPAT    SH_COMPAT   /* sets compatiblity mode               */
#define  GSH_DENYRW    SH_DENYRW   /* deny read/write access               */
#define  GSH_DENYWR    SH_DENYWR   /* deny write access                    */
#define  GSH_DENYRD    SH_DENYRD   /* deny read access                     */
#define  GSH_DENYNONE  SH_DENYNONE /* permits read/write access            */
#define  GSH_DENYNO    SH_DENYNO   /* permits read/write access            */
#endif // UNIX

WGSEXP FILE *                      /*   returns FILE pointer or NULL       */
gcfsopen(                          /* opens a file in shared mode          */
const CHAR *filename,              /*   file name to open                  */
const CHAR *mode,                  /*   mode to open with                  */
USHORT shflag);                    /*   shared mode flags                  */

WGSEXP GBOOL                       /*   return TRUE if separator character */
isvalds(                           /* is this char. a file path separator  */
CHAR c);                           /*   character to test                  */

WGSEXP GBOOL                       /*   returns TRUE=valid file name char  */
isvalfc(                           /* is this a valid file name character? */
CHAR c);                           /*   character to check                 */

WGSEXP GBOOL                       /*   returns TRUE=valid file name       */
isvalfn(                           /* check for valid file name            */
const CHAR *filnam);               /*   string to check                    */

WGSEXP GBOOL                       /*   returns TRUE=valid directory       */
isvaldn(                           /* verify directory name is ok for OS   */
const CHAR *dirnam);               /*   directory name to check            */

WGSEXP LONG                        /*   returns # of bytes copied          */
xfrfil(                            /* copy from one open file to another   */
FILE *fromfp,                      /*   source file pointer                */
FILE *tofp,                        /*   destination file pointer           */
LONG nbytes);                      /*   max bytes to transfer              */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __FIOAPI_H
