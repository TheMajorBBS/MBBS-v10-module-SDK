/***************************************************************************
 *                                                                         *
 *   FTPD.H                                                                *
 *                                                                         *
 *   Copyright (c) 1994-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   File Transfer Protocol client.                                        *
 *                                                                         *
 *                                              - R. Stein  7/11/94        *
 *                                                                         *
 ***************************************************************************/

#ifndef __FTPD_H
#define __FTPD_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT
#   ifdef __BUILDFTPD
#       define FTPDEXP          EXPORT
#       define FTPDEXPV(x)      EXPORT_VARIABLE(x)
#       define FTPDEXPF(x, y)   EXPORT_FUNCTION(x, y)
#    else
#       define FTPDEXP          IMPORT
#       define FTPDEXPV(x)      IMPORT_VARIABLE(x)
#       define FTPDEXPF(x, y)   IMPORT_FUNCTION(x, y)
#    endif
#else
#       define FTPDEXP
#       define FTPDEXPV
#       define FTPDEXPF
#endif // GCWINNT

#define FTPCPRT 21                 /* TCP/IP port for FTP server commands  */
#define FTPDPRT 20                 /* TCP/IP port for FTP server data      */
#define FTPNAME "FTP"              /* name of FTP server                   */
#define FTPBACKLOG 5               /* max # of colliding incoming calls    */

FTPDEXPV(CHAR) ftpcmds[][5];

/*--- FTP command indexes ---*/

/* This list must be in perfect sync with the ftpcmds[][] array in FTPD.C. */
/* It follows the order of commands on page 42 of RFC-1123.                */

#define USER  0
#define PASS  1
#define ACCT  2
#define XCWD  3
#define CWD   4
#define XCUP  5
#define CDUP  6
#define QUIT  7
#define PORT  8
#define PASV  9
#define TYPE 10
#define STRU 11
#define MODE 12
#define RETR 13
#define STOR 14
#define APPE 15
#define RNFR 16
#define RNTO 17
#define ABOR 18
#define DELE 19
#define XRMD 20
#define RMD  21
#define XMKD 22
#define MKD  23
#define XPWD 24
#define PWD  25
#define LIST 26
#define NLST 27
#define STAT 28
#define SYST 29
#define HELP 30
#define NOOP 31
#define MDTM 32
#define SIZE 33
#define ALLO 34

#define NCMD 35                    /* number of commands in above list     */
#define NONE -1                    /* ftpcdi() for none of the above       */

/*--- Auxilliary substate codes ---*/
#define RETRING -1                 /* retrieving a file                    */
#define STORING -2                 /* storing a file                       */
#define APPEING -3                 /* appending to a file                  */
#define STORFRG -4                 /* deleting file fragment after storage */

#define MINSNDSIZ 2048             /* minimum size of data sending buffer  */
#define FTPSNDSIZ (vdasiz-sizeof(struct ftpdusr)+MINSNDSIZ)
                                   /* usable size of data sending buffer   */
#define EMLLEN 80                  /* anonymous email address max length   */

struct FTPDEXP ftpdusr {           /* FTP server channel information       */
     struct vdirscb vdirscb;       /* VDIR session control block (VDIR.H)  */
     struct in_addr inaddr;        /* address from PORT command            */
     USHORT port;                  /* port from PORT command ("n" byte ord)*/
     USHORT sttime;                /* 16Hz timer                           */
     INT flags;                    /* see below                            */
     INT lssock;                   /* socket for PASV listen() for client  */
     INT clsock;                   /* socket for data connection to client */
     UINT bufcnt;                  /* number of FTP data bytes             */
     FILE *fp;                     /* file for RETRing, STORing or APPEing */
     CHAR emladr[EMLLEN+1];        /* anonymous email address              */
     CHAR baduid;                  /* count of bad userids in a row        */
     CHAR badpsw;                  /* count of bad passwords in a row      */
     ULONG numbyt;                 /* bytes transferred                    */
     UINT numfil;                  /* number of files listed               */
     ULONG roombyt;                /* room for new file                    */
     CHAR nlpfix[VDRPFIX+1];       /* relative prefix for NLST listing     */
     LONG bytlon;                  /* bturep(CNTCHR) at logon              */
     CHAR buffer[MINSNDSIZ];       /* \ buffer for sending FTP data        */
};                                 /* / MUST BE LAST ELEMENT OF STRUCTURE! */


#define ftpdptr ((struct ftpdusr *)vdaptr)
#define ftpdunm(unum) ((struct ftpdusr *)vdaoff(unum))

/*--- masks for ftpdptr->flags ---*/
#define XFRFIL  0x0001             /* data transfer now in progress        */
#define ANONYM  0x0002             /* Anonymous FTP caller                 */
#define PASVMD  0x0004             /* Passive mode for data connection     */
#define CYCLED  0x0008             /* CYCLE already in status queue        */

FTPDEXPV(INT) ftpdstt;             /* FTP server module state number       */

FTPDEXP VOID
setftpd(VOID);                     /* prepare for FTP server handling      */
                                   /* curusr() expected to be in effect    */

FTPDEXP CHAR *
slashstg(                          /* stgopt() enforcing beginning slash   */
INT pfxopt);                       /* option from .MSG file                */

FTPDEXP INT
ftpcdi(                            /* FTP command index                    */
CHAR *cmd);                        /* command name                         */
                                   /* returns command index (see FTP.H)    */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __FTPD_H
