/***************************************************************************
 *                                                                         *
 *   VDIR.H                                                                *
 *                                                                         *
 *   Copyright (c) 1994-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Virtual Directory API.                                                *
 *                                                                         *
 *                                        - RNStein  7/11/94               *
 *                                                                         *
 ***************************************************************************/

#ifndef __VDIR_H
#define __VDIR_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT
#   ifdef __BUILDVDIR
#       define VDIREXP          EXPORT
#       define VDIREXPV(x)      EXPORT_VARIABLE(x)
#       define VDIREXPF(x, y)   EXPORT_FUNCTION(x, y)
#    else
#       define VDIREXP          IMPORT
#       define VDIREXPV(x)      IMPORT_VARIABLE(x)
#       define VDIREXPF(x, y)   IMPORT_FUNCTION(x, y)
#    endif
#else
#       define VDIREXP
#       define VDIREXPV
#       define VDIREXPF
#endif // GCWINNT

#ifdef UNIX
#define VDRFNAME  256              /* VDIR file name length                */
#define VDRPFIX   1024             /* VDIR path prefix length              */
#else
#define VDRFNAME  (8+1+3)          /* VDIR file name length (8.3 format)   */
#define VDRPFIX   60               /* VDIR path prefix length              */
#endif
#define VDRFSPEC  (VDRPFIX+VDRFNAME) /* len of full path with file name    */

#define DOSSL '\\'              /* DOS-style backward slash             */
#define UNIXSL '/'              /* Unix-style forward slash             */

struct VDIREXP vdirsvc {           /* VDIRserver information               */
     struct vdirsvc *next;         /* next link in list of VDIRservers     */
     CHAR *dirpfx;                 /* directory prefix (must begin w/slash)*/
     INT (*vdsdir)(VOID);          /* select new subdir (vdirscb->trgdir)  */
     INT (*vds1st)(                /* 1=found 1st file or subdir, 2=call   */
          CHAR *fspec);            /* vdsnxt, or 0=none (wildcards usu ok) */
     INT (*vdsnxt)(VOID);          /* 1=next, 2=call again, 0=no more      */
     CHAR *(*vdsinf)(INT type);    /* information (see VDFXXX/VDDXXX codes)*/
     CHAR *(*vdspth)(VOID);        /* DOS path for file from vds1st/nxt=1  */
     VOID (*vdsrcd)(               /* record reading of file               */
          INT nml,                 /* 1=normal 0=aborted                   */
          LONG numbyt);            /* if nml == 0, number of bytes read    */
     INT (*vdslog)(                /* log in new file after vds1st=0       */
          CHAR *desc);             /* description, or ""                   */
     INT (*vdsdel)(VOID);          /* delete file from vds1st/nxt=1        */
     INT (*vdsrnm)(                /* rename file from vds1st/nxt=1        */
          CHAR *newnam);           /* new name, no path prefix             */
     INT (*vdsmkd)(VOID);          /* make dir from recent vds1st=0        */
     INT (*vdsrmd)(VOID);          /* remove dir from recent vdsdir=1      */
     INT credat;                   /* creation date                        */
     INT cretim;                   /* creation time                        */
};

/* return values for vds1st() and vdsnxt():  1=found one
                                             2=not yet, but call again
                                             0=done, no more               */

/*--- VDIR file seeking flags ---*/
/* usage for VDIRclients:  second parameter to vds1st() */
/* usage for VDIRservers:  vdflags global variable      */
#define VDSAWE 0x0001              /* Auto wild extens: FNAME -> FNAME.*   */
#define VDSASD 0x0002              /* Auto subdirectory: DIR -> DIR\*.*    */
#define VDSWLD 0x0004              /* Allow wildcard characters '*' '?'    */
#define VDSITW 0x0008              /* Intend to write (lock if possible)   */

/*--- VDIR file information type codes ---*/
#define VDFDSC 0                   /* 1-line text description of file      */
#define VDFWHO 1                   /* Owner / contributor of file          */
#define VDFGRP 2                   /* Group name for file                  */

/*--- VDIR directory information type codes ---*/
#define VDDNAM 101                 /* 1-line text name of directory        */
#define VDDDSC 102                 /* 1-line text description of directory */

VDIREXPV(struct vdirsvc*) vdshead; /* VDIR server linked-list head         */

VDIREXPV(struct vdirsvc) vdirroot; /* "root" server (can list VDIRservers) */

struct VDIREXP vdirscb {           /* VDIR session control block           */
     CHAR curdir[VDRPFIX+1];       /* current selected directory           */
     CHAR trgdir[VDRPFIX+1];       /* target directory                     */
     LONG curnum;                  /* server-specific info for current dir */
     LONG trgnum;                  /* server-specific info for target dir  */
     struct vdirsvc *cursvc;       /* current server (assoc with curdir[]) */
     struct vdirsvc *trgsvc;       /* target server (assoc with trgdir[])  */
     struct ffblk fb;              /* set by vds1st() & vdsnxt()           */
     union junk {                  /* additional misc. info                */
          struct vdirsvc *ll;      /* linked list member                   */
          INT misc;                /* misc. value                          */
     } j;
     CHAR flags;                   /* set by vds1st() & vdsnxt(), see below*/
};

/*-- Virtual Directory privilege flags ---*/
#define VDPEXIS 0x01               /* File exists already                  */
#define VDPVSBL 0x02               /* File is visible to user              */
#define VDPREAD 0x04               /* File contents are readable to the    */
#define VDPWRIT 0x08               /* File is writeable                    */

VDIREXPV(struct vdirscb*) vdirscb; /* current session being serviced       */
                                   /* (global to all routines exc regvds() */
VDIREXPV(INT) vdflags;             /* set by vds1st(), see VDSXXX above    */
                                   /* global to VDIRserver vds1st & vdsnxt */

/*--- vds1st() implicit output ---*/
VDIREXPV(INT) vdirbad;             /* when vds1st() returns 0, vdirbad     */
                                   /* is 1=bad directory, 0=no files       */
VDIREXPV(ULONG) vdirroom;          /* when vds1st() sets VDPWRIT, this is  */
                                   /* max room (or add'l room) for file    */
#define MAXROOM 0xFFFFFFFFUL       /* max for vdirroom (also default)      */

/*--- special application-settable VDIR options ---*/
VDIREXPV(INT) vdircase;            /*  1=convert all names to upper case   */
                                   /*  0=leave alone                       */
                                   /* -1=convert to lower case             */

/*--- standard VDIR API routines ---*/
VDIREXP VOID
regvds(                            /* Register a Virtual Directory Server  */
struct vdirsvc *vds);              /* VDIRserver info                      */

VDIREXP INT
vdsdir(                            /* Change current directory             */
CHAR *dir);                        /* relative or absolute directory spec  */
                                   /* returns 1=valid, 0=not               */
VDIREXP INT
vds1st(                            /* find the first file or subdirectory  */
CHAR *fspec,                       /* may change slash in place            */
INT flags);                        /* see VDSXXX flags above               */
                                   /* implicit output when returning 0:    */
                                   /* vdirbad: 1=bad directory, 0=no files */

VDIREXP INT
vdsnxt(VOID);                      /* 1=next file or subdir, 0=no more     */

VDIREXP CHAR*
vdsinf(                            /* other information on file or dir     */
INT type);                         /* type code (see VDFXXX/VDDXXX above)  */

VDIREXP CHAR*
vdspth(VOID);                      /* get DOS path of a VDIR file          */
                                   /* returns full path with file name     */

VDIREXP VOID
vdsrcd(                            /* record reading of file               */
INT nml,                           /* 1=normal 0=aborted                   */
LONG numbyt);                      /* if nml == 0, number of bytes read    */

VDIREXP INT
vdslog(                            /* log in new file after vds1st=0       */
CHAR *desc);                       /* description or ""                    */
                                   /* returns 1=could, 0=couldn't          */

VDIREXP INT
vdsdel(VOID);                      /* delete file from recent vds1st/nxt=1 */
                                   /* returns 1=could, 0=couldn't, 2=trying*/

VDIREXP INT
vdsrnm(                            /* rename file from recent vds1st/nxt=1 */
CHAR *newnam);                     /* new name (no path prefix)            */
                                   /* returns 1=could, 0=couldn't          */

VDIREXP INT
vdsmkd(VOID);                      /* make dir from recent vds1st=0        */
                                   /* returns 1=could, 0=couldn't          */

VDIREXP INT
vdsrmd(VOID);                      /* remove dir from recent vdsdir=1      */
                                   /* returns 1=could, 0=couldn't          */
                                   /* leaves you at parent directory       */

/*--- utilities ---*/

VDIREXP CHAR*
samsls(                            /* convert slashes to the same type     */
CHAR *stg,                         /* returns same value as passed         */
CHAR slash);                       /* slash to use (one of SLES)        */

VDIREXP CHAR*
direduce(                          /* reduce "." and ".." in dir name      */
CHAR *stg);                        /* returns same value as passed         */

VDIREXP CHAR*
caseset(                           /* set string's case acc to vdircase    */
CHAR *pth);                        /* string converted in-place (if at all)*/

VDIREXP CHAR*
autwex(                            /* automatically wild-ize extension     */
CHAR* fspec);                      /* file spec (no path prefix)           */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __VDIR_H
