/***************************************************************************
 *                                                                         *
 *   GALFILH.H                                                             *
 *                                                                         *
 *   Copyright (c) 1993-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   File Libraries - Header for interface into the File Libraries         *
 *                                                                         *
 *                                                 - D. Pitchford  9/28/93 *
 *                                                                         *
 ***************************************************************************/

#ifndef __GALFILH_H
#define __GALFILH_H

#include "reserve.h"
#include "filexfer.h"

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
#   define FILEXPV(x)           extern x           
#   define FILEXPF(x,y)         extern x (* y)
#endif // __GCWINNT

#define FLNAMESZ    9              /* size of Library names                */
#define FLDESCSZ   41              /* size of Library descriptions         */
#define FLLDESCS   80              /* size of long Library descriptions    */
#define FLFILENM   13              /* size of filenames                    */
#define FLKEYSIZ   13              /* size of keywords                     */
#define FLKEYLST   79              /* size of keyword string               */
#define FLNMCATS   10              /* number of top-level libs joinable    */
#define PATHSIZE   50              /* size of directory path               */

#ifdef GCV2
#define FLFILREC  105              /* record size of struct flfile & data  */
#else
#define FLFILREC fldoff(flfile,desc)/* record size of struct flfile & data */
#endif // GCV2

#define FLKEYREC   35              /* record size of keyword data          */
#define DATESZ      8              /* size of date, "srt" format           */
#define DESCSIZ   902              /* size of long description of a file   */
#define NLISTER    17              /* number of files to list on screen    */
#define NDESCLN    15              /* number of description lines [fsd]    */
#define SDESCLN    50              /* size of desc line incl. nul term.    */
#define MAXKWDS   200              /* number of keywords per file          */
#define NUMSZ       8              /* size of char array for # of d/ls     */
#define NUMSZP      "%07ld"        /* number of downloads, sprintf template*/
#define NOTAPPED    "0000000"      /* "srt" format date of unapproved file */
#define FLOWSTS    10              /* number of btuchi() calls to stack up */
#define NLDLIN      5              /* number of lines in long description  */
#define ULDAYS      7              /* number of days to count new files    */
#define MISCSIZE   80              /* size of flmisc text variable         */
#define NVIEWS    100              /* number of custom view extensions     */
#define SIZKWBUF   60              /* size of buffer for keyword data      */
#define ALPHALC    50              /* incremental allocation for **alphlibs*/

                                   /* insfile() return codes               */
#define INS_DONE    1              /*   done with file, continue processing*/
#define INS_MOVE    2              /*   need to move file (cycled)         */
#define INS_RENAME  (-1)           /*   query to rename file               */
#define INS_ERROR   (-2)           /*   I/O error trying to move file      */
#define INS_BADNAME (-3)           /*   invalid file name (not DOS 8.3 fmt)*/

struct fluser {                    /* structure for saved user data        */
     CHAR lib[FLNAMESZ];           /* last Library a user was in           */
     CHAR proto[3];                /* default download transfer protocol   */
     SHORT askme;                  /* ask to logoff after default transfer */
     SHORT mytyp;                  /* user preference: search parameters   */
     SHORT mylib;                  /* user preference: current/all libs    */
     SHORT cdayin;                 /* cofdat() date of last Library access */
     CHAR newdate[DATESZ];         /* date user last did the L list option */
#ifdef GCV2
     char spare[22];               /* former spare space                   */
#endif // GCV2
};

struct flusave {                   /* structure for saving user data       */
     CHAR userid[UIDSIZ];          /* User-Id of user data belongs to      */
     CHAR modnam[MNMSIZ];          /* "File Library" module key            */
     struct fluser udata;          /* data to save on above user           */
};

struct fllib {                     /* structure for Library data           */
     CHAR libname[FLNAMESZ];       /* Library name                         */
     LONG flags;                   /* various saved bit flags              */
     SHORT day;                    /* day this Library was created         */
     SHORT time;                   /* time of day this Library was created */
     CHAR libdesc[FLDESCSZ];       /* Library short description            */
     SHORT appwait;                /* number of files awaiting approval    */
     CHAR keyreq[KEYSIZ];          /* key to see files at all              */
     CHAR libop[KEYSIZ];           /* key to be a Lib-Op (blank is OK)     */
     CHAR autoap[KEYSIZ];          /* key to auto-approve uploaded files   */
     CHAR dlkey[KEYSIZ];           /* key to download files                */
     CHAR ulkey[KEYSIZ];           /* key to upload files                  */
     CHAR overw[KEYSIZ];           /* key to overwrite files               */
     CHAR cat[FLNMCATS][FLNAMESZ]; /* top-level Libraries a member of      */
#ifdef GCV2
     CHAR path[PATHSIZE];          /* name of alternate path, if any       */
#else
     CHAR path[GCSTRPTH];          /* name of alternate path, if any       */
#endif // GCV2
     LONG dlchge;                  /* per-file charge for downloads        */
     LONG kdlchge;                 /* per-K charge for downloads           */
     LONG numfiles;                /* number of files in Library           */
     LONG totfiles;                /* number of files in Library + joined  */
     SHORT royal;                  /* royalty percentage                   */
     SHORT libs;                   /* number of joined Libraries           */
     LONG maxfil;                  /* maximum number of files in Library   */
     LONG maxbyt;                  /* maximum number of bytes in Library   */
     LONG maxbup;                  /* maximum upload size to Library       */
     CHAR primary[UIDSIZ];         /* user who is primary Lib-Op           */
     SHORT newfiles[ULDAYS];       /* added files in last x days, [0]=today*/
     LONG totbytes;                /* total number of bytes in Library     */
     USHORT cluster;               /* cluster size of Library drive        */
};

                                   /* a Library's various saved bit flags  */
#define FLGCBD 0x00000001L         /* ...copy-before-download              */
#define FLGRDO 0x00000002L         /* ...read-only lib                     */
#define FLGAUL 0x00000004L         /* ...audit uploads                     */
#define FLGADL 0x00000008L         /* ...audit downloads                   */
#define FLGFDL 0x00000010L         /* ...free downloads                    */
#define FLGFUL 0x00000020L         /* ...free uploads                      */
#define FLGDOS 0x00000040L         /* ...DOS-ONLY Library                  */
#define FLGHID 0x00000080L         /* ...hidden, join-only Library         */
#define LIBCHN 0x00000100L         /* ...Library changed, update soon      */
#define LIBONG 0x00000200L         /* ...ongoing change, update whenever   */

struct libdisk {                   /* structure for saving Library data    */
     struct fllib lib;             /* structure to save                    */
#ifdef GCV2
     char spare[240];              /* former spare space                   */
#endif // GCV2
     CHAR ldesc[NLDLIN][FLLDESCS]; /* long description                     */
};

struct flfile {                    /* structure for individual file data   */
     CHAR libname[FLNAMESZ];       /* Library the file is in               */
     CHAR filname[FLFILENM];       /* the file name of the file            */
     CHAR udate[DATESZ];           /* approval date, in "srt" format       */
     CHAR numdls[NUMSZ];           /* number of downloads, NUMSZP format   */
     CHAR fdate[DATESZ];           /* file date, "srt" format              */
     LONG siz;                     /* file size                            */
     USHORT tim;                   /* file time                            */
     CHAR ulby[UIDSIZ];            /* uploaded by                          */
     USHORT utime;                 /* time of day file was approved        */
#ifdef GCV2
     char spare[FLFILREC-84];      /* former spare space                   */
#endif // GCV2
     CHAR desc[DESCSIZ];           /* variable-length description field    */
};

struct taglib {                    /* structure for file tagging           */
     INT status;                   /* state of this tagged file, see below */
     INT usrnum;                   /* usrnum of tagging user               */
     CHAR libname[FLNAMESZ];       /* actual Library name of tagged file   */
     CHAR filname[FLFILENM];       /* file name of tagged file             */
     CHAR udate[DATESZ];           /* approval date of file, "srt" format  */
     CHAR reflib[FLNAMESZ];        /* reference Library of tagged file     */
     CHAR wldspc[FLFILENM];        /* tag specification for wildcard tags  */
     LONG tagtime;                 /* time(NULL) the file was tagged       */
     LONG size;                    /* size of tagged file                  */
     LONG copied;                  /* amount copied so far                 */
     INT nwld;                     /* number of wildcard files tagged      */
};

                                   /* status values, struct taglib         */
#define TGEMPTY  0                 /* ...empty and ready for new tag       */
#define TGLOCAL  1                 /* ...ready for d/l direct from storage */
#define TGINWAIT 2                 /* ...waiting to be copied              */
#define TGCOPY   3                 /* ...being copied to temp directory    */
#define TGDLTMP  4                 /* ...ready for d/l from temp directory */
#define TGOTHER  5                 /* ...waiting for outside control       */
#define TGSERVER 6                 /* ...under outside control             */
/* a negative value of one of the above definitions indicates completion   */

struct modeview {                  /* structure for file viewing modes     */
     CHAR ext[4];                  /* extension to store view mode for     */
     INT mode;                     /* view mode to use                     */
     VOID (*rouptr)();             /* view routine, if needed              */
};

/* seven structures for composite keys within the union in struct fluson,  */
/* and their corresponding btrieve key numbers                             */

struct key0 {                      /* LIBNAME/UDATE/FILNAME composite key  */
     CHAR libname[FLNAMESZ];
     CHAR udate[DATESZ];
     CHAR filname[FLFILENM];
};
#define COMPLUF  0                 /* btrieve key for above structure      */

struct key1 {                      /* LIBNAME/FILNAME composite key        */
     CHAR libname[FLNAMESZ];
     CHAR filname[FLFILENM];
};
#define COMPLF   1                 /* btrieve key for above structure      */

struct key2 {                      /* KEYWORD/FILNAME/LIBNAME composite key*/
     CHAR keyword[FLKEYSIZ];
     CHAR filname[FLFILENM];
     CHAR libkey[FLNAMESZ];
     CHAR origkey[FLKEYSIZ];       /* reference, not part of key           */
     CHAR libname[FLNAMESZ];       /* reference, not part of key           */
};
#define COMPKFL  0                 /* btrieve key for above structure      */

struct key3 {                      /* UDATE/FILNAME composite key          */
     CHAR udate[DATESZ];
     CHAR filname[FLFILENM];
     CHAR libkey[FLNAMESZ];
     CHAR libname[FLNAMESZ];       /* reference, not part of key           */
};
#define COMPUF   2                 /* btrieve key for above structure      */

struct key4 {                      /* FILNAME/LIBNAME composite key        */
     CHAR filname[FLFILENM];
     CHAR libkey[FLNAMESZ];
     CHAR libname[FLNAMESZ];       /* reference, not part of key           */
     CHAR exactfn[FLFILENM];       /* reference, not part of key           */
};
#define COMPFL   3                 /* btrieve key for above structure      */
#define COMPFL_K 1                 /* btrieve key for above structure(kwd) */

struct key5 {                      /* NUMDLS/LIBNAME/FILNAME composite key */
     CHAR numdls[NUMSZ];
     CHAR libkey[FLNAMESZ];
     CHAR filname[FLFILENM];
     CHAR libname[FLNAMESZ];       /* reference, not part of key           */
};
#define COMPNLF  4                 /* btrieve key for above structure      */

struct key6 {                      /* reference for DOS-Only Libraries     */
     CHAR filname[FLFILENM];
     SHORT date[NLISTER];
     SHORT time[NLISTER];
     LONG size[NLISTER];
};

struct key7 {                      /* structure for keyword insertion      */
     CHAR keyword[FLKEYSIZ];
     CHAR filname[FLFILENM];
     CHAR libname[FLNAMESZ];
};

union srch {                       /* joined Library search key union      */
     struct key0 key0;             /* libname/udate/filname                */
     struct key1 key1;             /* libname/filname                      */
};

union combo {                      /* the file key union                   */
     struct key0 key0;             /* libname/udate/filname                */
     struct key1 key1;             /* libname/filname                      */
     struct key2 key2;             /* keyword/filname/libname              */
     struct key3 key3;             /* udate/filname                        */
     struct key4 key4;             /* filname/libname                      */
     struct key5 key5;             /* numdls/libname/filname               */
     struct key6 key6;             /* DOS-Only reference                   */
};

struct zvdat {                     /* C/S compressed file viewing context  */
     INT state;                    /*   state within, 0=not being used now */
     CHAR libname[FLNAMESZ];       /*   Library name of file being viewed  */
     CHAR filname[FLFILENM];       /*   file name of file being viewed     */
     LONG size;                    /*   size of file being viewed          */
     FILE *fp;                     /*   open file pointer of file viewed   */
     CHAR filid;                   /*   type of compression used           */
     LONG pos;                     /*   current file position              */
};

struct fluson {                    /* "user online" structure              */
     VOID (*rouptr)(struct taglib *);/* miscellaneous function pointer     */
     INT keymeth;                  /* key method used                      */
     INT styp;                     /* search type selected                 */
     LONG flags;                   /* various online bit flags             */
     CHAR miscfil[FLFILENM];       /* miscellaneous file name              */
     CHAR misclib[FLNAMESZ];       /* miscellaneous Library name           */
     CHAR keylist[FLKEYLST];       /* keyword list string                  */
     INT tagcnt;                   /* temporary tag counter                */
     LONG pos;                     /* file position for unzipping files    */
     LONG filen;                   /* file length for unzipping files      */
     INT savetags;                 /* number of tagspecs saved during d/l  */
     CHAR tagk;                    /* display key                          */
     INT cursor;                   /* online tagbar                        */
     INT miscflag;                 /* miscellaneous index or flag          */
     INT kcount;                   /* keyword count                        */
     INT nlibaxs;                  /* number of libs user has access to    */
     INT index;                    /* miscellaneous index integer          */
     INT force;                    /* lib select mode: top-level lib only? */
     INT retstt;                   /* return or flag substate              */
     INT pflg;                     /* asking state, download selection     */
     INT hold;                     /* tag while viewing                    */
     INT crdrat;                   /* saved for free upload/download       */
     INT nozap;                    /* saved for free upload/download       */
     struct ffblk fb;             /* for miscellaneous fnd1st(), etc. use */
     INT autol;                    /* auto login or approve all in prog.   */
     INT dodesc;                   /* descriptions during login, see below */
     INT atend;                    /* listing scroll flags, see below      */
     CHAR lrange[FLNAMESZ];        /* searching what lib range             */
     LONG tot;                     /* amt. of file copy done               */
     CHAR srcpath[GCMAXPTH];       /* miscellaneous file path number 1     */
     CHAR destpath[GCMAXPTH];      /* miscellaneous file path number 2     */
     FILE *fsrc;                   /* miscellaneous file pointer number 1  */
     FILE *fdst;                   /* miscellaneous file pointer number 2  */
     INT state;                    /* state for unzipping files            */
     CHAR fdate[DATESZ];           /* DOS file date (FSD use)              */
     CHAR udate[DATESZ];           /* upload date (FSD use)                */
     LONG siz;                     /* file size (FSD use)                  */
     INT ftim;                     /* file time (FSD use)                  */
     LONG numdls;                  /* file number of downloads (FSD use)   */
     CHAR ulby[UIDSIZ];            /* file uploader (FSD use)              */
     INT timeul;                   /* upload time (FSD use)                */
     INT prop;                     /* propellor spinner state (/-\|)       */
     INT wtnum;                    /* wildcard tagging: number of files    */
     LONG wtsiz;                   /* wildcard tagging: cumulative size    */
     CHAR savprot[3];              /* protocol saved for concatenation     */
     CHAR newdate[DATESZ];         /* date for L list option, newest files */
     INT tdline[NLISTER];          /* line number and tag status (+/-)     */
     struct key0 tags[NLISTER];    /* displayed tagged files, libs, dates  */
     struct key1 key1;             /* miscellaneous key, mostly Lib-Op use */
     struct key2 kwdy;             /* miscellaneous keyword data file key  */
     union combo u;                /* composite key collection             */
     INT movstt;                   /* stat of move or copy of files        */
     CHAR cskwds[FLKEYLST];        /* keyword list for c/s searches        */
     struct zvdat cszview;         /* c/s view-zipfile memory              */
     LONG csidx;                   /* c/s search index, dos & keyword      */
};

                                   /* flags for struct fluson              */
#define OFTGMAN 0x00000001L        /* ...entered tag manager from filefind */
#define ABOUPRF 0x00000002L        /* ...neutralize user/system prefs CNC  */
#define RETUOPM 0x00000004L        /* ...return to operator menu from u/l  */
#define LISTALL 0x00000008L        /* ...listing all libs to offline list  */
#define DATESRC 0x00000010L        /* ...listing by user range of dates    */
#define COMFILE 0x00000020L        /* ...file is viewable inside (ascii)   */
#define LONGDSC 0x00000040L        /* ...display long Library description  */
#define DBLCLCK 0x00000080L        /* ...detect double-clicking of files   */
#define REVSRCH 0x00000100L        /* ...searching files in reverse order  */
#define USRANSI 0x00000200L        /* ...searching files in ansi mode      */
#define STOPLST 0x00000400L        /* ...stop listing files for a moment   */
#define TLSTDSP 0x00000800L        /* ...element has been displayed on list*/
#define FULLTAG 0x00001000L        /* ...prevent more interactive tagging  */
#define AXSUSER 0x00002000L        /* ...user has created u/l subdirectory */
#define XDLBEEP 0x00004000L        /* ...user warned about download access */
#define MOVFLAG 0x00008000L        /* ...copy (as opposed to move) flag    */
#define NXTEQUL 0x00010000L        /* ...get next value equal to key       */
#define REUPLOD 0x00020000L        /* ...user is re-uploading a file       */
#define UNOINJO 0x00040000L        /* ...user is busy, before searching    */
#define ENTRCNC 0x00080000L        /* ...user is using cnc facility ("&")  */
#define WLDRSLV 0x00100000L        /* ...resolving wildcard sysop operation*/
#define ISEDLIB 0x00200000L        /* ...user is editing a library now     */
#define APPTHEM 0x00400000L        /* ...approve files as they are added   */
#define DELTHEM 0x00800000L        /* ...delete files as they are unlogged */
#define OFFUPLD 0x01000000L        /* ...log off after upload to Library   */
#define INMVCPY 0x02000000L        /* ...sysop is in process of move/copy  */
#define FILCONT 0x04000000L        /* ...a c/s context has been secured    */

                                   /* values for dodesc in struct fluson   */
#define ASKDESC -1                 /* ...ask whether to enter a file desc. */
#define NEVRASK  0                 /* ...just log in all the files         */
#define DOADESC  1                 /* ...do the next file description      */
#define NIXDESC  2                 /* ...don't do the next file description*/

                                   /* values for atend in struct fluson    */
#define LSTFILS  0                 /* ...scrolling in either direction ok  */
#define LSTBACK  1                 /* ...at end, no scrolling forward      */
#define LSTFORE  2                 /* ...at beginning, no scrolling back   */
#define LSTONLY  3                 /* ...may not scroll in either direction*/
#define LSTNONE  4                 /* ...no files found in search/list     */

                                   /* values for submit() and viewing files*/
#define NOTVIEW  0                 /* ...tag file for download             */
#define DOWNLOD  1                 /* ...download file now                 */
#define CMPVIEW  2                 /* ...view with "V" protocol            */
#define LSTVIEW  3                 /* ...view with "L" protocol            */
#define ANSVIEW  4                 /* ...view with "A" protocol            */
#define CSTVIEW  5                 /* ...custom view routine, flo->rouptr  */

struct srcs {                      /* information for ongoing searches     */
     INT nlibs;                    /*   number of Libraries in keys, or 0  */
     INT nloaded;                  /*   number of Libraries loaded so far  */
     union srch *tn;               /*   "to next" unions of keys           */
     union srch *tp;               /*   "to previous" unions of keys       */
     union srch *fn;               /*   "from next" unions of keys         */
     union srch *fp;               /*   "from previous" unions of keys     */
     CHAR unions[1];               /*   var-length data for above unions   */
};

#define NUINRS 4                   /* # of union arrays in above data area */

struct libcsfil {                  /* files being d/l'ed by c/s users      */
     CHAR libname[FLNAMESZ];       /*   Library name of file               */
     CHAR filname[FLFILENM];       /*   file name of file, * for all       */
     INT status;                   /*   file copy status, see below        */
     LONG time;                    /*   time value for CD copying          */
     LONG charge;                  /*   credits user was charged for d/l   */
};

FILEXPV(struct libcsfil *) lcsu;   /* pointer, and per-user arrays    */
FILEXPV(struct libcsfil *) lcsarr;
FILEXPV(struct libcsfil *) viewarr;

#define FREADY 1                   /* lcsarr status, file ready to d/l     */
#define CDFILE 2                   /* lcsarr status, CD file waiting       */
#define CDCOPY 3                   /* lcsarr status, CD file copying       */
#define CDDONE 4                   /* lcsarr status, copied file ready     */
#define CDDLOD 5                   /* lcsarr status, d/l of copied file    */
#define EXTCDF 6                   /* lcsarr status, special file copy     */
#define EXTCDC 7                   /* lcsarr status, external control      */

/* External CD management programs can work with C/S users also, they need */
/* to watch lcsarr[] (using setlcsu()) for files showing up as EXTCDF.     */
/* Then they must set lcsu->status to EXTCDC until the file has been       */
/* retrieved.  Afterwards, set to CDDONE telling the system that the file  */
/* is in the proper copydir ready for d/l.                                 */

FILEXPV(struct fluser *) flu;       /* current user pointed to (disk)       */
FILEXPV(struct fluser *) fluarr;    /* memory array                    */

FILEXPV(struct fluson *) flo;       /* online user pointed to          */

FILEXPV(struct flusave) flusmem;    /* memory for loading/saving fluser*/

FILEXPV(struct fllib *) curlib;     /* current Library in use          */
FILEXPV(struct fllib **) alphlibs;  /* alphabetical ptrs to Libraries  */

FILEXPV(struct libdisk *) libupd;   /* memory for loading/saving Libs  */
FILEXPV(struct libdisk *) libedt;   /* memory for editing Libraries    */

FILEXPV(struct taglib *) ftag;      /* current tagged file             */

FILEXPV(struct modeview) mvarr[NVIEWS];/* custom viewing routines     */

FILEXPV(struct key0) countkey;     /* key for counting uploads in Libs*/

FILEXPV(struct key7 *) kwbuf;      /* buffer for keyword insertion    */

FILEXPV(INT) srcpool;              /* handle to pool of search structs     */
FILEXPV(INT *) srcharr;            /* array of search handles, one per user*/
FILEXPV(struct srcs *) srcu;       /* ptr to cur (srcoff()'d) search struct*/

FILEXPV(union srch) srcactive;     /* active, found record for speed-search*/

FILEXPV(INT) curfusr;         /* cur (fluoff()'d) file library user   */

FILEXPV(HMCVFILE) flmsg;      /* handle for .msg file                 */
FILEXPV(FILE *) csrc;         /* pointer for general copying of files */
FILEXPV(FILE *) cdst;         /* pointer for general copying of files */
FILEXPV(FILE *) movs;         /* pointer for sysop copying of files   */
FILEXPV(FILE *) movd;         /* pointer for sysop copying of files   */

FILEXPV(DFAFILE *) flldat;    /* data file for Libraries              */
FILEXPV(DFAFILE *) flfdat;    /* data file for files                  */
FILEXPV(DFAFILE *) flkdat;    /* data file for keywords               */

FILEXPV(CHAR *) arrower;      /* cursor key detection flag            */
FILEXPV(CHAR *) tempdir;      /* default user upload temp directory   */
FILEXPV(CHAR *) nochgkey;     /* key to never be charged to d/l       */
FILEXPV(CHAR *) listkey;      /* key to be able to d/l file lists     */
FILEXPV(CHAR *) nonkwds;      /* non-keywords                         */
FILEXPV(CHAR *) flsysop;      /* key required to be Library sysop     */
FILEXPV(CHAR *) defplop;      /* default primary Lib-Op               */
FILEXPV(CHAR *) copydir;      /* destination directory, copied files  */
FILEXPV(CHAR *) defdesc;      /* default description for a Library    */
FILEXPV(CHAR *) deflname;     /* name of default Library              */
FILEXPV(CHAR *) descedit;     /* memory for file descriptions         */
FILEXPV(CHAR *) dargv[MAXKWDS];/* points to defdesc, as margv to input*/
FILEXPV(CHAR *) defproto;     /* default d/l protocol for all users   */
FILEXPV(CHAR) flmisc[MISCSIZE];/* array for misc. test variable       */
FILEXPV(CHAR) movflib[FLNAMESZ];/* array for moving files from Library*/
FILEXPV(CHAR) movtlib[FLNAMESZ];/* array for moving files to Library  */
FILEXPV(CHAR) movfnam[FLFILENM];/* array for moving files file name   */
FILEXPV(CHAR) countlib[FLNAMESZ];/* Library currently being counted   */
FILEXPV(CHAR) tagtmpp[TSHLEN+1];/* memory for temporary wild file path*/
FILEXPV(CHAR) tagtmpf[FLFILENM];/* memory for temporary wild file name*/

FILEXPV(VOID *) libmem;       /* memory for Libraries                 */
FILEXPV(VOID *) libmem2;      /* more memory for adding Libraries     */
FILEXPV(VOID *) flomem;       /* memory for users online              */
FILEXPV(VOID *) ftagmem;      /* memory for tagged files              */

FILEXPV(INT) numlib;          /* number of libs memory allocated for  */
FILEXPV(INT) numladd;         /* max. number of libs to possibly add  */
FILEXPV(INT) movstt;          /* state of file move                   */
FILEXPV(INT) flstt;           /* state for the File Libraries         */
FILEXPV(INT) longsrch;        /* require brute force searches         */
FILEXPV(INT) vdd;             /* half of the vda declaration          */
FILEXPV(INT) freeuls;         /* if true, never charge while uploading*/
FILEXPV(INT) dargc;           /* count of parsed words by darsdesc()  */
FILEXPV(INT) notifsys;        /* if true, notify sysops of unapp files*/
FILEXPV(INT) notiflop;        /* if true, notify libops of unapp files*/
FILEXPV(INT) numoflib;        /* actual number of Libraries           */
FILEXPV(INT) comeff;          /* estimated communications efficiency  */
FILEXPV(INT) ncatlibs;        /* actual number of top-level Libraries */
FILEXPV(INT) auditall;        /* if true, audit all file transfers    */
FILEXPV(INT) unifile;         /* if true, require unique file names   */
FILEXPV(INT) clfits;          /* if true, use cluster sizes for libs  */
FILEXPV(INT) pfnceil;         /* profanity ceiling for File Libraries */
FILEXPV(INT) chgabt;          /* if true, charge for aborted downloads*/
FILEXPV(INT) defallib;        /* search all Libraries from d/l prompt */
FILEXPV(INT) systags;         /* number of ftagmem to allocate        */
FILEXPV(INT) defstyp;         /* default search/list mode             */
FILEXPV(INT) defslib;         /* default search/list range, one/all   */
FILEXPV(INT) movflag;         /* flag for move/copy files, to copy?   */
FILEXPV(INT) stplist;         /* strip ansi always in file listings   */
FILEXPV(INT) countuls[ULDAYS];/* counter of Library files added daily */
FILEXPV(INT) clnlevel;        /* level of cleanup to run              */
FILEXPV(INT) kwaut;           /* flag, keywords being written now     */
FILEXPV(INT) maxjoin;         /* # of joined libs max for fast search */
FILEXPV(INT) srcindex;        /* index for found record in speed-srch */
FILEXPV(INT) fltagf;          /* is current file tag a Library tag    */
FILEXPV(INT) htmldesc;        /* use live HTML in descriptions?       */

FILEXPV(LONG) byteroom;       /* bytes free for uploading to a Library*/
FILEXPV(LONG) thresh;         /* bytes assured free, copydir's drive  */

FILEXPV(struct reserve *) librsv;/* File Libraries reservations domain*/

FILEXPV(CHAR) libedits[];     /* FSD utility strings                  */
FILEXPV(CHAR) filedits[];
FILEXPV(CHAR) libeditf[];
FILEXPV(CHAR) fileditf[];

FILEXPV(GBOOL) newjoins;      /* are there new libraries joined?      */

FILEXP VOID init_galfiluz(VOID);          /* initialize unzip submodule           */
FILEXP INT openzip(VOID);                 /* open zip file (unzip submodule)      */
FILEXP INT dizread(CHAR *b);              /* read description file (unzip submod) */

#define flf ((struct flfile *)(flfdat->data))          /* macro: cur file  */
#define spc (*((struct taglib **)(ftgptr->tagspc)))    /* macro: cur tag   */
#define kyd ((struct key2 *)(flkdat->data))            /* macro: cur kwd   */
#define totags (ftuptr->numftg+flo->tagcnt)            /* macro: # tagged  */
#define nextrec(rev,e,x,y,z)  (rev ? (e ? dfaAcqLE(x,y,z) : dfaAcqLT(x,y,z)) : \
                                     (e ? dfaAcqGE(x,y,z) : dfaAcqGT(x,y,z)))
#define nextqrec(rev,x,y,z) (rev ? dfaAcqLE(x,y,z) : dfaAcqGE(x,y,z))
#define DESCSNON "<please type a description here>"
#define DESCLNON "<please type more descriptive text here>"
#define DESCFNON "<Enter description, including keywords>"
#define DESCFNO2 "<The first line acts as a short description>"

                                   /* utilties for interface to the FSD    */
#define FLDDATE  0
#define FLDTIME  1
#define FLDNAME  2
#define FLDDOSO  3
#define FLDDESC  4
#define FLDDESC0 5
#define FLDDESC1 6
#define FLDDESC2 7
#define FLDDESC3 8
#define FLDDESC4 9
#define FLDPATH 10
#define FLDHID  11
#define FLDCBD  12
#define FLDRDO  13
#define FLDAUL  14
#define FLDADL  15
#define FLDFUL  16
#define FLDFDL  17
#define FLDCDF  18
#define FLDCDK  19
#define FLDROY  20
#define FLDMFL  21
#define FLDMBT  22
#define FLDMUP  23
#define FLDVIS  24
#define FLDDLD  25
#define FLDULD  26
#define FLDOVW  27
#define FLDAPU  28
#define FLDLOP  29
#define FLDPLOP 30
#define FLDEXIT 31

#define FFDNAME  0
#define FFDLIB   1
#define FFDDATE  2
#define FFDTIME  3
#define FFDSIZE  4
#define FFDDL    5
#define FFDULD   6
#define FFDULT   7
#define FFDDLT   8
#define FFDCHG   9
#define FFDUSER  10
#define FFDTXT00 11
#define FFDTXT01 12
#define FFDTXT02 13
#define FFDTXT03 14
#define FFDTXT04 15
#define FFDTXT05 16
#define FFDTXT06 17
#define FFDTXT07 18
#define FFDTXT08 19
#define FFDTXT09 20
#define FFDTXT10 21
#define FFDTXT11 22
#define FFDTXT12 23
#define FFDTXT13 24
#define FFDTXT14 25
#define FFDEXIT  26

/* GALFIL.C 26/01/94 16.36.56 */
FILEXP VOID init__galfil(VOID);
FILEXP VOID initlibrsv(VOID);
FILEXP VOID iniopts(VOID);
FILEXP GBOOL psislibop(INT unum,const CHAR *lock);
FILEXP CHAR *cnclib(VOID);
FILEXP INT isflop(struct fllib *libptr);
FILEXP INT scanlib(INT user,struct fllib *libptr);
FILEXP INT wldgetag(VOID);
FILEXP INT dlbgnwld(VOID);
FILEXP INT tshlist(INT tshcod);
FILEXP INT tshlib(INT tshcod);
FILEXP LONG dnlprc(LONG siz,struct fllib *libptr);
FILEXP VOID fluoff(INT unum);
FILEXP VOID srcoff(VOID);
FILEXP VOID scanlibs(VOID);
FILEXP struct fllib *libfind(const CHAR *libname);
FILEXP struct fllib *liboff(INT libnum);
FILEXP struct fllib *setuaxs(VOID);
FILEXP INT makwdlst(const CHAR *stg,const CHAR *filname);
FILEXP INT submit(CHAR *libname,CHAR *filname,CHAR *reflib,INT view,INT quiet);
FILEXP INT updusr(struct fluser *fluptr);
FILEXP CHAR *userdir(INT which);
FILEXP INT valname(CHAR *libname);
FILEXP INT fileditv(INT fldno,CHAR *answer);
FILEXP GBOOL lsinp(VOID);
FILEXP VOID deresume(VOID);
FILEXP GBOOL lslon(VOID);
FILEXP VOID genlon(VOID);
FILEXP INT srcincx(VOID);
FILEXP INT srcgood(VOID);
FILEXP INT srcnext(VOID);
FILEXP union srch *nextsrc(INT nxteq);
FILEXP VOID resetkey(CHAR *libname,CHAR *filname);
FILEXP VOID rset(VOID);
FILEXP INT tryMove(VOID);
FILEXP INT insfile(struct fllib *libptr,CHAR *path,const struct ffblk *f,
            const CHAR *appdate,const CHAR *u,const CHAR *desc);
FILEXP INT keywordy(VOID);
FILEXP INT libeditv(INT fldno,CHAR *answer);
FILEXP INT valpath(CHAR *path);
FILEXP INT taglist(VOID);
FILEXP INT zapcrd(INT yes,LONG siz,struct fllib *dlib);
FILEXP struct fllib *keylib(CHAR *libfound,CHAR *libname,INT *retval);
FILEXP struct fllib *nxtlib(VOID);
FILEXP VOID optiprf(VOID);
FILEXP VOID bgnfiled(INT display);
FILEXP INT uwaitcpy(INT unum);
FILEXP VOID notifu(VOID);
FILEXP INT ntagged(CHAR *uid);
FILEXP VOID checkoth(VOID);
FILEXP VOID ulcount(VOID);
FILEXP VOID inicount(CHAR *libname);
FILEXP INT addkwnow(VOID);
FILEXP VOID addkw(const CHAR *keyword,const CHAR *filname,const CHAR *libname);
FILEXP VOID keywdaut(INT taskid);
FILEXP INT delkw(const CHAR *keyword,const CHAR *filname,const CHAR *libname);
FILEXP VOID copyaut(INT taskid);
FILEXP VOID doalr(VOID);
FILEXP VOID dsearch(INT which,INT x);
FILEXP VOID fileditd(SHORT save);
FILEXP VOID fileditp(INT msgno,INT amode,INT display);
FILEXP VOID lsclean(VOID);
FILEXP VOID lsdel(CHAR *uid);
FILEXP VOID lsend(VOID);
FILEXP VOID purgecpy(INT rmvdirs);
FILEXP VOID lshang(VOID);
FILEXP VOID genhup(VOID);
FILEXP LONG flclfit(LONG filsiz,USHORT cluster);
FILEXP VOID cfilmova(VOID);
FILEXP VOID movecyc(VOID);
FILEXP GBOOL cycdelib(INT *stt,CHAR *libname,CHAR *filname);
FILEXP VOID cdellib(VOID);
FILEXP VOID crencyc(VOID);
FILEXP INT dupefile(VOID);
FILEXP VOID autogone(VOID);
FILEXP VOID doneLog(GBOOL prfNow);
FILEXP VOID cautolog(VOID);
FILEXP VOID cunapp(VOID);
FILEXP VOID capp(VOID);
FILEXP VOID cbigcpy(VOID);
FILEXP VOID csearch(VOID);
FILEXP VOID cfildel(VOID);
FILEXP VOID cflist(VOID);
FILEXP VOID entrdesc(VOID);
FILEXP VOID ccopying(VOID);
FILEXP VOID cdizzy(VOID);
FILEXP VOID cliblst(VOID);
FILEXP VOID ckeyword(VOID);
FILEXP VOID cwldsrch(VOID);
FILEXP VOID cwldsys(VOID);
FILEXP VOID cresolve(VOID);
FILEXP VOID clstcyc(VOID);
FILEXP VOID lssta(VOID);
FILEXP VOID flagit(INT fldspec,LONG flag);
FILEXP CHAR *dprfm(INT msgno);
FILEXP VOID srcdrec(INT redisplay);
FILEXP VOID unprop(VOID);
FILEXP VOID srcinit(INT mode,CHAR *lib);
FILEXP CHAR *wldstuff(CHAR *stg);
FILEXP VOID srcpaus(INT rebuild);
FILEXP VOID srcukey(VOID);
FILEXP VOID gosearch(VOID);
FILEXP VOID libeditd(SHORT save);
FILEXP GBOOL savelib(struct libdisk *sav);
FILEXP VOID libeditp(INT msgno,INT amode);
FILEXP VOID libkick(VOID);
FILEXP VOID prfopt(INT optno,INT tot,INT ctr);
FILEXP VOID prfups(VOID);
FILEXP VOID mainmenu(VOID);
FILEXP VOID opmenu(VOID);
FILEXP VOID promptin(VOID);
FILEXP VOID retmenu(INT opermenu);
FILEXP VOID buildview(INT item);
FILEXP VOID retoin(VOID);
FILEXP VOID retoinx(VOID);
FILEXP VOID retoinl(VOID);
FILEXP VOID rstcrd(VOID);
FILEXP VOID setbusy(VOID);
FILEXP VOID statstrt(VOID);
FILEXP INT getaufil(INT wipe,INT unapp);
FILEXP INT candlnow(CHAR *libname,CHAR *filname);
FILEXP INT chjoined(struct fllib *libptr,CHAR *check);
FILEXP INT chjoin(struct fllib *libptr,struct fllib *newlib,INT unjoin);
FILEXP VOID listjoin(VOID);
FILEXP INT profane(const CHAR *stg);
FILEXP INT wldmatch(CHAR *wild,CHAR *sfnm);
FILEXP INT compwild(CHAR *wildfile,CHAR *filename);
FILEXP INT space(VOID);
FILEXP VOID dncfin(INT endok,LONG bytxfer,struct fllib *libptr);
FILEXP INT weirddir(CHAR *dirpath);
FILEXP INT isansiu(VOID);
FILEXP VOID touch(CHAR *src,CHAR *dest);
FILEXP VOID untagall(CHAR *libname,CHAR *filname);
FILEXP INT exfile(struct fllib *libptr,struct key0 *key);
FILEXP VOID cleanit(INT total);
FILEXP CHAR *manytims(LONG howmany);
FILEXP struct taglib *tagoff(INT index);
FILEXP CHAR *isedtlib(VOID);
FILEXP VOID countupl(VOID);
FILEXP VOID chuldate(struct fllib *libptr,const CHAR *date,INT add);
FILEXP INT dlfrom(CHAR *libname);
FILEXP INT dlfroml(struct fllib *libptr);
FILEXP VOID dlcant(VOID);
FILEXP VOID setmisc(CHAR *stg);
FILEXP INT viewmode(CHAR *ext);
FILEXP INT register_modeview(CHAR *ext,INT mode,VOID (*rouptr)());
FILEXP VOID cycinp(VOID);
FILEXP INT totnlibs(CHAR *libname,INT index);
FILEXP GBOOL initsrc(VOID);
FILEXP GBOOL ccycidx(VOID);
FILEXP VOID newpage(VOID);
/* GALFILUT.C 26/01/94 15.21.00 */
FILEXP CHAR *checkdir(CHAR *path);
FILEXP CHAR *fixpath(CHAR *path);
FILEXP CHAR *compkey(const CHAR *libname,const CHAR *filname);
FILEXP CHAR *rcompkey(const CHAR *libname,const CHAR *filname);
FILEXP CHAR *cutpunc(CHAR *stg);
FILEXP CHAR *dat2srt(const CHAR *dt);
FILEXP CHAR *ddat2srt(USHORT dosDate);
FILEXP LONG dnlchg(LONG siz,CHAR *libname);
FILEXP CHAR *dnlmin(LONG siz);
FILEXP CHAR *fzer(LONG num);
FILEXP CHAR *protocol(VOID);
FILEXP CHAR *srt2dat(const CHAR *dt);
FILEXP CHAR *srt2datl(const CHAR *dt);
FILEXP CHAR *tvcomeff(VOID);
FILEXP CHAR *tvctim(VOID);
FILEXP CHAR *tvdesc(VOID);
FILEXP CHAR *tvdesc0(VOID);
FILEXP CHAR *tvdesc1(VOID);
FILEXP CHAR *tvdesc2(VOID);
FILEXP CHAR *tvdesc3(VOID);
FILEXP CHAR *tvdesc4(VOID);
FILEXP CHAR *tvdnlmin(VOID);
FILEXP CHAR *tvfapp(VOID);
FILEXP CHAR *tvfdate(VOID);
FILEXP CHAR *tvfdates(VOID);
FILEXP CHAR *tvfname(VOID);
FILEXP CHAR *tvflib(VOID);
FILEXP CHAR *tvfnum(VOID);
FILEXP CHAR *tvfsize(VOID);
FILEXP CHAR *filsize(LONG size,LONG kval);
FILEXP CHAR *tvfsizek(VOID);
FILEXP CHAR *tvftimes(VOID);
FILEXP CHAR *tvfulby(VOID);
FILEXP CHAR *tvinit(VOID);
FILEXP CHAR *tvmisc(VOID);
FILEXP CHAR *tvname(VOID);
FILEXP CHAR *tvtagk(VOID);
FILEXP CHAR *tagk(VOID);
FILEXP CHAR *tvtags(VOID);
FILEXP CHAR *tvtshmsg(VOID);
FILEXP CHAR *tvudate(VOID);
FILEXP CHAR *tvbytu(VOID);
FILEXP CHAR *tvbytt(VOID);
FILEXP CHAR *tvbyto(VOID);
FILEXP CHAR *tvfilt(VOID);
FILEXP INT alrtag(CHAR *libname,CHAR *filname);
FILEXP INT amrlib(CHAR *grp,CHAR *fil);
FILEXP INT countc(CHAR *stg,CHAR chr);
FILEXP INT deparse(CHAR *p);
FILEXP INT dotags(INT quiet);
FILEXP VOID setfull(INT isfull);
FILEXP INT findbest(INT stt);
FILEXP INT visilib(struct fllib *libptr);
FILEXP CHAR *visxlib(struct fllib *libptr,CHAR *libmatch);
FILEXP INT keyfig(VOID);
FILEXP INT keyin(CHAR *key);
FILEXP INT keysin(INT start);
FILEXP INT kwdout(VOID);
FILEXP INT nlibtagd(VOID);
FILEXP INT okfname(const CHAR *filename);
FILEXP INT readline(FILE *ptr);
FILEXP INT srch1(VOID);
FILEXP INT srch2(VOID);
//FILEXP GBOOL strsrep(CHAR *stg,CHAR *from,CHAR *to);
FILEXP INT ulfileq(INT flag);
FILEXP LONG dnlsec(LONG siz);
FILEXP LONG dnlsecl(LONG siz,struct fllib *libptr);
FILEXP struct fllib *nexthigh(const CHAR *oldlib);
FILEXP struct fllib *nextlow(const CHAR *oldlib);
FILEXP VOID bubkwds(VOID);
FILEXP VOID sortlibs(VOID);
FILEXP VOID darsdesc(INT limit,CHAR chr);
FILEXP CHAR *lrange(CHAR *libname);
FILEXP VOID dispfhdr(INT resetcur);
FILEXP VOID dlcharge(LONG charge,struct fllib *l);
FILEXP VOID dnlcount(CHAR *libname,CHAR *filname,LONG ct);
FILEXP INT maintainFile(VOID);
FILEXP VOID dofiler(CHAR *desc);
FILEXP VOID gather(VOID);
FILEXP VOID loadlibs(VOID);
FILEXP VOID mopitup(VOID);
FILEXP VOID moploop(VOID);
FILEXP INT notify(INT logon);
FILEXP VOID readin(INT lines,FILE *fptr,CHAR *stg);
FILEXP VOID regtvars(VOID);
FILEXP VOID removetg(INT n);
FILEXP VOID strcrep(CHAR *stg,CHAR from,CHAR to);
FILEXP VOID unbreak(VOID);
FILEXP VOID iflstyp(CHAR c);
FILEXP VOID iflslib(CHAR c);
FILEXP VOID iaskword(CHAR *stg);
FILEXP VOID iaskname(CHAR *stg);
FILEXP INT ifdesced(CHAR *stg);
FILEXP VOID iprefers(CHAR c);
FILEXP VOID imanmnu(CHAR c);
FILEXP VOID ibigcopy(CHAR *stg);
FILEXP VOID iwarnmrk(CHAR *stg);
FILEXP VOID idelfil(CHAR *stg);
FILEXP INT isellib(CHAR *stg);
FILEXP INT othrsin(CHAR *libname);
FILEXP INT idellibn(CHAR *stg);
FILEXP INT itagman(CHAR *stg);
FILEXP INT ientdl(CHAR *stg);
FILEXP INT fspex(CHAR *stg,CHAR *lib,INT sub);
FILEXP INT ioverw(CHAR c);
FILEXP INT ientul(CHAR *stg);
FILEXP INT iulmod(CHAR *stg);
FILEXP INT ucanmod(VOID);
FILEXP INT ucanovw(struct fllib * pLib,struct flfile * pFile);
FILEXP VOID exitview(VOID);
FILEXP VOID dcurs(INT und);
FILEXP INT curspos(INT set);
FILEXP VOID clstags(VOID);
FILEXP INT ientret(CHAR *stg);
FILEXP INT iviewasc(CHAR chr);
FILEXP VOID ifilistx(CHAR *stg);
FILEXP INT ifilist(CHAR *stg);
FILEXP VOID itranspr(CHAR chr);
FILEXP VOID irename(CHAR *stg);
FILEXP VOID ichain(CHAR chr);
FILEXP VOID ijoin(CHAR *stg);
FILEXP VOID iflblist(CHAR chr);
FILEXP INT inpfunc(VOID);
FILEXP INT editgo(CHAR *filen);
FILEXP INT writable(struct fllib *libptr);
FILEXP INT lsmenu(VOID);
FILEXP INT fupfil(INT code);
FILEXP INT fparsrch(CHAR *stg);
FILEXP VOID retoin2(VOID);
FILEXP VOID dnlstart(INT logoff);
FILEXP VOID rebuild(INT cls);
FILEXP VOID prtbuild(INT start,INT run);
FILEXP VOID iappmenu(CHAR chr);
FILEXP VOID iunapp(CHAR chr);
FILEXP VOID idelmenu(CHAR chr);
FILEXP VOID imovmenu(CHAR chr);
FILEXP VOID imovpath(CHAR *stg);
FILEXP VOID ienuadnm(CHAR *stg);
FILEXP VOID idoso(CHAR chr);
FILEXP VOID iclibnam(CHAR *stg);
FILEXP INT oprmenu(VOID);
FILEXP CHAR *inmvcpy(VOID);
FILEXP VOID loadldsc(struct libdisk *libdptr);
FILEXP VOID bgnlibed(VOID);
FILEXP VOID cdsptags(VOID);
FILEXP VOID wipetag(VOID);
FILEXP INT libchg(VOID);
FILEXP VOID spinner(VOID);
FILEXP VOID locsysfl(CHAR *filname);
FILEXP VOID notidl(VOID);
FILEXP INT notapped(const CHAR *udate);
FILEXP LONG libroom(struct fllib *libptr);
FILEXP CHAR *libpath(struct fllib *libptr);
FILEXP INT haslibkey(struct fllib *libptr,CHAR *keyname);
FILEXP INT usrupd(struct fllib *libptr,CHAR *filname);
FILEXP VOID chkjoin(VOID);
/* GALFILCS.C 13/09/94 10.00.00 */
FILEXP VOID init_cslib(VOID);
FILEXP INT vewctn(VOID);
FILEXP INT csfbest(INT mode,LONG time);
FILEXP VOID csclean(INT unum);
FILEXP VOID sendres(CHAR *restg);
FILEXP VOID sendjoin(VOID);
FILEXP VOID setlcsu(INT unum);

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __GALFILH_H                          */
