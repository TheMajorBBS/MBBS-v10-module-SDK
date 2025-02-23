/***************************************************************************
 *                                                                         *
 *   TCPIP.H                                                               *
 *                                                                         *
 *   Copyright (c) 1994-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   TCP/IP for the Internet Connectivity Option for Worldgroup,           *
 *   based upon Pacific Softworks' Fusion, or Ipswitch's Piper/IP          *
 *   TCP/IP protocol kernel.                                               *
 *                                                                         *
 *   Ipswitch's Piper/IP support          - RNStein  5/25/94               *
 *   Pacific Softworks' Fusion port       - RNStein  4/11/95               *
 *                                                                         *
 ***************************************************************************/

#ifndef __TCPIP_H
#define __TCPIP_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT
#   ifdef __BUILDGALTCPIP
#       define TCPIPEXP           EXPORT
#       define TCPIPEXPV(x)       EXPORT_VARIABLE(x)
#       define TCPIPEXPF(x, y)    EXPORT_FUNCTION(x, y)
#    else
#       define TCPIPEXP           IMPORT
#       define TCPIPEXPV(x)       IMPORT_VARIABLE(x)
#       define TCPIPEXPF(x, y)    IMPORT_FUNCTION(x, y)
#    endif
#else
#       define TCPIPEXP
#       define TCPIPEXPV
#       define TCPIPEXPF
#endif // GCWINNT


#ifdef GCWINNT
//                                    these macros eliminate the need for
//                                    our own version of WINSOCK.H

#ifdef FD_SETSIZE
#undef FD_SETSIZE
#define FD_SETSIZE       512                 // max number of sockets for NT
#endif // FD_SETSIZE

#define EADDRINUSE       WSAEADDRINUSE       // address already in use
#define ECONNRESET       WSAECONNRESET       // connection reset by peer
#define EWOULDBLOCK      WSAEWOULDBLOCK      // operation would block
#define EPROTOTYPE       WSAEPROTOTYPE       // protocol wrong type for socket
#define EINPROGRESS      WSAEINPROGRESS      // operation now in progress
#define ENOTCONN         WSAENOTCONN         // socket is not connected
#define EADDRNOTAVAIL    WSAEADDRNOTAVAIL    // can't assign requested address
#define ENETUNREACH      WSAENETUNREACH      // network is unreachable
#define EHOSTUNREACH     WSAEHOSTUNREACH     // host is unreachable
#endif // GCWINNT


#ifndef GCWINNT
#define INVALID_SOCKET   -1        // to make defines consistant with NT
#define SOCKET_ERROR     -1        // to make defines consistant with NT
#endif // GCWINNT


#define ICO2                       /* for compatibility with ifdef's       */

#ifndef PACSOFT
#ifndef IPSWITCH
//#error Must define either "PACSOFT" or "IPSWITCH" //TODO - CHECK
#endif // !IPSWITCH
#endif // !PACSOFT

#ifdef PACSOFT
#ifdef IPSWITCH
#error Must define either "PACSOFT" or "IPSWITCH" but not both
#endif // IPSWITCH
#endif // PACSOFT

/*--- Pacific Softworks-specific include files that are used for ICO code ---*/
#ifdef PACSOFT
#include "fusion.h"
#include "llconfig.h"
#endif // PACSOFT

/*--- Ipswitch-specific includes, etc., that are used for ICO code ---*/
#ifdef IPSWITCH
#ifdef UNIX
#undef CTRL
#include <sys/types.h>
#ifndef LINUX
#include <sys/uio.h>
#endif                             /* !LINUX                               */
#include <sys/socket.h>
#include <arpa/nameser.h>
#include <net/if.h>
#if defined(OSF1) || defined(LINUX)
#include <sys/ioctl.h>
#elif !defined(SCO)
#include <sys/filio.h>
#include <sys/sockio.h>
#endif                             /* OSF1 || LINUX                        */
#undef NOERROR
#include <netinet/in.h>
#include <arpa/inet.h>
#include <nlist.h>
#include <netdb.h>
#include <errno.h>
#ifdef LINUX
#include <sys/time.h>
#include <unistd.h>
#define  NBBY       8
#endif                             /* LINUX                                */
#ifdef SCO
#include <sys/select.h>
#endif                             /* SCO                                  */
#elif defined(GCWINNT)
#undef FAR
#define _OLE2_H_
#include <windows.h>
#undef FAR
#define FAR
#define  NBBY       8
#else
#include "sys\xdefs.h"
#include "sys\types.h"
#include "sys\uio.h"
#include "sys\socket.h"
#include "sys\mbuf.h"
#include "net\if.h"
#include "arpa\nameser.h"
#include "netinet\in.h"
#include "nlist.h"
#include "netdb.h"
#include "sockprot.h"
#endif                             /* UNIX                                 */

#undef  INADDR_NONE                /* avoid Borland compiler's warning     */
#define INADDR_NONE 0xFFFFFFFFL    /* indeterminate IP address (ipaddrb)   */
#define EIO      5                 /* error codes missing from sys/xdefs.h */
#define ENXIO    6
#define ENOTDIR 20
#define ENOTTY  25
#endif                             /* IPSWITCH                             */

/* datstm.h must always be included, usually via brkthu.h via majorbbs.h   */

/*--- General constants and variables ---*/
#define INET_ADDR_ERR 0xFFFFFFFFL  /* inet_addr() return value: bad syntax */
#if defined(UNIX)
#define tcpip_errno      errno
#define s_ioctl          ioctl
#define socketclose      close
#elif defined(GCWINNT)
#define tcpip_errno      WSAGetLastError()
#define s_ioctl          ioctlsocket
#define socketclose      closesocket
#else
#define tcpip_errno (*perrno)      /* TCP/IP kernel's err number           */
extern int _soisfd;                /* for distinct file/socket handle sets */
extern int h_errno;                /* for gethtbyname() error codes        */
extern int *perrno;                /* pointer to TCP/IP kernel's err number*/
#endif                             /* UNIX                                 */

struct callinf {                   /* accepted call info                   */
     INT socket;                   /* socket for newly accepted connection */
};

struct callque {                   /* queue of accepted connections        */
     INT maxque;                   /* max entries in accept queue          */
     INT numque;                   /* current number of entries in accept q*/
     struct callinf *que;          /* accept queue entries (NULL=no queue) */
};                                 /* [0]=oldest, [numque-1]=newest        */

struct svrinf {                    /* Registered Server information        */
     CHAR *name;                   /* name of svr (eg "FTP") max len 16    */
     struct svrinf *next;          /* link to next server, (NULL=end)      */
     INT port;                     /* TCP port number (e.g. 23=Telnet)     */
     INT backlog;                  /* max # of colliding incoming calls    */
     INT svrskt;                   /* server's bind() & listen() socket #  */
     VOID (*incall)(               /* incoming call handler (socket=clskt) */
          INT gotchn);             /* 1=chan (curusr) assigned, 0=not avail*/
     INT maxstt;                   /* max connections allowed for app      */
     struct callque callque;       /* accepted call queue                  */
};

#define TCPOSZ 128                 /* size of TCP/IP output staging buffer */

struct TCPIPEXP tcpipinf {                  /* channel-specific TCP/IP info         */
     struct bufstm outsnk;         /* output sink (MUST BE FIRST FIELD)    */
     CHAR outstg[TCPOSZ];          /* output staging buffer                */
     struct datstm *cdidst;        /* GSBL's sink for input byte hose      */
     struct svrinf *server;        /* server handling channel (NULL=none)  */
     struct in_addr inaddr;        /* Client's 32-bit internet address     */
     INT port;                     /* Client's remote TCP port number      */
     INT socket;                   /* socket to client (from accept())     */
     INT unum;                     /* user number (sink may need to know)  */
     CHAR flags;                   /* see below                            */
     LONG bytcnt;                  /* extra bytes xferred (eg data port)   */
     ULONG tckcon;                 /* when connection was made             */
     CHAR spare[200-187];          /* (round out structure to 200 bytes)   */
};                                 /* (Structure cannot exceed 255 bytes.) */
                                   /* (Changing size of this structure     */
                                   /* requires all add-ons be recompiled.) */

/*--- tcpip info flags --- */
#define TCPDSC 0x01                /* disconnect in progress               */

TCPIPEXPV(HMCVFILE) tcpmg;          /*--- galtcpip.mcv stuff             ---*/
TCPIPEXPV(CHAR*) ipaddr;            /* this BBS's IP address                */
TCPIPEXPV(ULONG) ipaddrb;           /* IPADDR, binary form, netw byte order */
TCPIPEXPV(ULONG) iproutb;           /* IPROUT, (router IP), netw byte order */
TCPIPEXPV(ULONG) netmaskb;          /* NETMASK, (perh derived from IPADDR)  */
TCPIPEXPV(UINT) netmtu;             /* NETMTU, MTU for your network         */
TCPIPEXPV(CHAR) audinc;             /* Audit Trail record incoming calls?   */
TCPIPEXPV(CHAR) audrej;             /* Audit Trail reject calls due to busy?*/
TCPIPEXPV(CHAR) audtrm;             /* Audit Trail termination of calls?    */
TCPIPEXPV(INT) sndwin;              /* SO_SNDBUF socket option              */
TCPIPEXPV(INT) rcvwin;              /* SO_RCVBUF socket option              */
TCPIPEXPV(CHAR*) hostdeny;          /* file of IP's to deny access          */

                                    /*--- other public vars               ---*/

TCPIPEXPV(struct svrinf*) svrhead;    /* head of linked svr list (NULL=none)  */
TCPIPEXPV(struct tcpipinf*) tcpipinf; /* array[nterms] of TCP/IP-channel info */
TCPIPEXPV(struct sockaddr_in) claddr; /* client address (when incall()'ing)   */

TCPIPEXPV(INT) clskt;               /* socket to client (implicit parameter */
                                    /* to server's incall() routine)        */
TCPIPEXPV(INT) nfyskt;              /* socket you're being notified about   */
TCPIPEXPV(INT) sndact;              /* sndmgr() records no. of bytes sent   */
TCPIPEXPV(CHAR *) tcposb;           /* PACSOFT: global output staging buffer*/
TCPIPEXPV(ULONG) selewb;            /* count select()/nselect() EWOULDBLOCKs*/
TCPIPEXPV(ULONG) accewb;            /* count accept() EWOULDBLOCKS          */
TCPIPEXPV(CHAR) tcpip_kid[];        /* TCP/IP kernel implementation ID     */

/*--- socket event handling map ---*/
struct sktmap {                    /* socket event handlers: RECV & SEND   */
     VOID (*evthdl)(VOID*);        /* event handler routine (NULL=none)    */
     VOID *ptr;                    /* app-specific data pointer            */
};
                                   /* tnftype parm of sktnfy() & sktcnc(): */
#define TNFRECV 0                  /* Notify of recv() opportunity         */
#define TNFSEND 1                  /* Notify of send() opportunity         */
#define TNFACCP 2                  /* Notify of accept() opportunity       */
#define TNFCONN 3                  /* Notify of connect() completion       */
#define TNFQUAN 4                  /* number of possible values of tnftype */

                                   /* inner (1st) index in sktmap array    */
#define TNFRA 0                    /* socket map for RECV and ACCEPT       */
#define TNFSC 1                    /* socket map for SEND and CONNECT      */
#define TNFNUM 2                   /* possible indices in sktmap[][] array */

TCPIPEXPV(INT) tnfidx[TNFQUAN];     /* map tnftype-> inner sktmap[][] index*/

TCPIPEXPV(INT) tnfclosed;           /* notifies event handler of peer close */
                                    /* (set before sktnfy()'s evthdl is     */
                                    /* called, should be 0 all other times) */

TCPIPEXPF(GBOOL, hstalw)(ULONG hostip); /* host allowable vector (TRUE=allowed) */

TCPIPEXPV(INT) ijreas;             /* elaborates on ->incall(0)            */ 
                                   /* reasons why incoming call rejected   */
#define IJRFULL 1                  /*   no room for incoming call          */
#define IJRSHUT 2                  /*   server shutting down               */
#define IJRDENY 3                  /*   (*hstalw)() rejected               */
#define IJRNONE 4                  /*   not rejected: ->incall(1)          */
#define IJRULIM 5                  /*   user licence limit exceeded        */
#define IJRALIM 6                  /*   app limit on connections (maxstt)  */

/* Users of above list of call-reject-reasons should be tolerant of        */
/* additions to this list "without notice" as much as possible.            */

// TODO - CHECK
#ifdef PACSOFT
#define BASE_NOTIFY (EXCEPT_NOTIFY+RSHUTDOWN_NOTIFY+WSHUTDOWN_NOTIFY)
extern INT selflags[TNFQUAN];      /* map tnftype -> nselect()'s flag masks*/
extern INT numnfy;                 /* number of sockets interested in      */
extern struct sel *sktsel;         /* sockets of interest (for nselect())  */
#endif                             /* PACSOFT                              */

/*--- tcpdial() and udpdial() return values ---*/
#define DLERRS -1                  /* socket() error (see tcpip_errno)     */
#define DLERRI -2                  /* ioctl() error (see tcpip_errno)      */
#define DLERRR -3                  /* setsockopt(SO_REUSEADDR) error       */
#define DLERRB -5                  /* bind() error (see tcpip_errno)       */
#define DLCNOW 6                   /* success, socket available now!       */

/*--- more tcpdial() return values (not udpdial()) ---*/
#define DLERRC -7                  /* connect() error (see tcpip_errno)    */
#define DLCING 8                   /* connect() deferred, select for send  */

/*--- GCDI interrupts (candidates for somewhere more general-purpose) ---*/
#define dealwith_cdi_interrupts   int savifl
#define allow_cdi_interrupts      (savifl=__allow_cdi_interrupts())
#define prevent_cdi_interrupts    (savifl=__prevent_cdi_interrupts())
#define restore_cdi_interrupts    (__restore_cdi_interrupts(savifl))

TCPIPEXP VOID
init__tcpip(VOID);                 /* Initialize TCP/IP (ICO add-ons MUST  */
                                   /* call at top of their init__xxx()'s)  */

TCPIPEXP INT
regtcpsvr(                         /* register a TCP server                */
CHAR *name,                        /* name of service (e.g. FTP, Telnet)   */
INT port,                          /* port number (e.g. 23=telnet, 21=ftp) */
INT backlog,                       /* max # of colliding incoming calls    */
VOID (*incall)(INT usrnum));       /* user number (usrnum), or -1=unavail  */
                                   /* returns 1=up ok, 0=can't             */

TCPIPEXP VOID
svrMaxque(                         /* give server an incoming call queue   */
INT maxque);                       /*   max number of calls to queue       */
                                   /*   (call only immed after regtcpsvr() */
                                   /*   returns 1)                         */

TCPIPEXP VOID
svrMaxstt(                         /* impose limit on server connections   */
INT maxstt);                       /*   max number simul server connections*/
                                   /*   (call only immed after regtcpsvr() */
                                   /*   returns 1)                         */

TCPIPEXP VOID
rejinc(                            /* reject an incoming TCP/IP call       */
CHAR *svr,                         /* name of that server                  */
CHAR *why);                        /* reason for rejection                 */

TCPIPEXP USHORT
tcpmit(                            /* TCP/IP moveit(), channel output sink */
struct datstm *dsp,                /* (pointer to sink's datstm structure) */
CHAR *srcloc,                      /* source specifies the location        */
USHORT nwant);                     /* source wants sink to move this many  */

TCPIPEXP USHORT                    /*   returns room in send queue         */
tcpskw(                            /* TCP/IP snkwin() (relies on sendba()) */
struct datstm *dsp);               /*   pointer to sink's datstm structure */

TCPIPEXP VOID
tcpdmv(                            /* TCP/IP didmov() (relies on sendba()) */
struct datstm *dsp,                /*   pointer to sink's datstm structure */
USHORT nactual);                   /*   number of bytes moved to tcposb    */

TCPIPEXP VOID
tcpinc(                            /* read socket data into GCDI channel   */
struct tcpipinf *tip);             /* user's TCP/IP channel info           */
                                   /* application:  sktnfy(,,tcpinc,tip,)  */

TCPIPEXP VOID
tcpsnd(                            /* try to send staging buffer contents  */
struct tcpipinf *tip);             /* TCP/IP session info                  */

TCPIPEXP INT
sndmgr(                            /* manage send()ing from a buffer       */
CHAR *buffer,                      /* buffer address                       */
UINT *bufcnt,                      /* where buffer count is stored         */
INT socket);                       /* socket handle                        */
                                   /* returns 1=not done, 0=done, -1=error */
                                   /* sndact implicit output: # bytes sent */

TCPIPEXP VOID
audtcptfc(                         /* Audit time and traffic for TCP server*/
CHAR *title,                       /* first line of Audit Trail message    */
LONG bytcnt);                      /* number of bytes traffic              */

TCPIPEXP INT
tcpdial(                           /* initiate a TCP connection            */
struct in_addr inaddr,             /* host IP address                      */
UINT port,                         /* port number (network byte order)     */
UINT fromport,                     /* local port number (0=ephemeral)      */
INT *psocket);                     /* where to store socket handle (should */
                                   /* be -1 whenever this socket not open) */
                                   /* see DLXXXX return values in TCPIP.H  */

TCPIPEXP INT
udpdial(                           /* initiate a UDP connection            */
UINT fromport,                     /* local port number (0=ephemeral)      */
INT *psocket);                     /* where to store socket handle (should */
                                   /* be -1 whenever this socket not open) */
                                   /* see DLXXXX return values in TCPIP.H  */

TCPIPEXP VOID
nonblock(                          /* set socket to non-blocking           */
INT skt);                          /* socket descriptor                    */

TCPIPEXP VOID
oobinline(                         /* mix OOB data with regular data       */
INT skt);                          /* socket descriptor                    */

TCPIPEXP ULONG
recvbw(                            /* recv() bytes waiting (ret number of) */
INT skt);                          /* socket descriptor                    */

TCPIPEXP UINT
sendba(                            /* send() bytes able (ret number of)    */
INT skt);                          /* socket descriptor                    */

TCPIPEXP VOID
rwnmgr(                            /* receive window manager               */
INT socket,                        /* socket handle                        */
INT nroom,                         /* max room to advertise (- means 0)    */
INT *curwin);                      /* current advertised window variable   */
                                   /* rwnmgr() can only SHRINK window size.*/

TCPIPEXP INT
rwnadj(                            /* receive window adjuster              */
INT socket,                        /* socket handle                        */
INT bufsiz,                        /* incoming buffer capacity when empty  */
INT bufavl,                        /* incoming buffer capacity now         */
INT hyster,                        /* hysteresis on window adjustment      */
INT *curwin);                      /* current advertised window variable   */
                                   /* returns 1=adjusted, 0=left alone     */
                                   /* An empty buffer means immediately    */
                                   /* advertise max window, else there's   */
                                   /* hysteresis on receive window growth. */
                                   /* rwnadj() can only GROW window size.  */

TCPIPEXP INT
setsndwin(                         /* set socket's send window size        */
INT socket,                        /* socket handle                        */
INT swin);                         /* send window (e.g. sndwin)            */
                                   /* returns 1=ok, 0=error (tcpip_errno)  */

TCPIPEXP INT
setrcvwin(                         /* set socket's receive window size     */
INT socket,                        /* socket handle                        */
INT rwin);                         /* receive window (e.g. rcvwin)         */
                                   /* returns 1=ok, 0=error (tcpip_errno)  */

TCPIPEXP VOID
fd_scanbeg(                        /* expr1 in fd_set scanning for(;;) loop*/
fd_set *fdsp);

TCPIPEXP INT
fd_scanmor(VOID);                  /* expr2 in fd_set scanning for(;;) loop*/

TCPIPEXP VOID
fd_scannxt(VOID);                  /* expr3 in fd_set scanning for(;;) loop*/

TCPIPEXP VOID
fd_setor(                          /* bit-wise OR two fd_set's together    */
struct fd_set *oree,               /* input and output                     */
struct fd_set *orer);              /* input                                */

TCPIPEXP VOID
fd_setand(                         /* bit-wise AND two fd_set's together   */
struct fd_set *andee,              /* input and output                     */
struct fd_set *ander);             /* input                                */

TCPIPEXP INT                       /*   returns 1=valid, 0=non-class A,B,C */
dftnetmask(                        /* default network mask                 */
ULONG ipaddr,                      /*   IP addresss (network byte order)   */
ULONG *netmask);                   /*   where to put netmask (n byte order)*/

TCPIPEXP INT                       /*   returns 1=valid, 0=not             */
chknetmask(                        /* is netmask valid?                    */
ULONG netmask);                    /*   netmask, network byte order        */
                                   /*   Netmask must allow at least 4 hosts*/
                                   /*   and in binary start with 1's and   */
                                   /*   end with 0's.                      */

TCPIPEXP INT
sndop(                             /* send an option string, all or nothing*/
struct tcpipinf *tip,              /* TCP/IP info for channel              */
CHAR *bytes,                       /* binary string of bytes (may incl \0) */
INT nbytes);                       /* number of bytes                      */
                                   /* returns 0=no room, 1=ok              */

TCPIPEXP VOID
sktnfy(                            /* request notification on socket event */
INT tnftype,                       /* TNFRECV, TNFSEND, TNFACCP, TNFCONN   */
INT skt,                           /* socket number                        */
VOID (*evthdl)(),                  /* event handler routine                */
VOID *ptr,                         /* app-specific ptr (passed to evthdl)  */
INT unum);                         /* associated user number (curusr() set */
                                   /* before evthdl) or -1=none            */

/* NOTE:  Do not request notification for both TNFSEND and TNFCONN on the same
socket at the same time, unless the last 3 parameters to sktnfy() are
identical with each request.  (In practice, interest in sendability and
connection-established are mutually exclusive anyway.)  Same goes for TNFRECV
and TNFACCP (which are also mutually exclusive interests).  So, for example,
when switching from TNFCONN interest to TNFSEND interest, be sure to
sktcnc(TNFCONN,...) before you sktnfy(TNFSEND...).  Under the Ipswitch stack,
sendability and connect-done are indistinguishable, as well as receivability
and accept-readiness.  Under Fusion they are distinct conditions.  Failure to
follow the above rules may have different penalties on different stacks.  */

TCPIPEXP VOID
sktcnc(                            /* cancel notification on socket events */
INT tnftype,                       /* TNFRECV, TNFSEND, TNFACCP, TNFCONN   */
INT skt);                          /* socket number                        */

/* All sktnfy() calls must have a corresponding sktcnc() call, except calling
clsskt() implicitly cancels all requests for the socket. */

TCPIPEXP VOID
clssvr(                            /* close a server's socket to his client*/
INT unum,                          /* user number (or -1=not applicable)   */
INT skt,                           /* socket                               */
INT port);                         /* server's port number (for error msg) */

TCPIPEXP INT
clsskt(                            /* close a socket                       */
INT skt);                          /* socket number                        */
                                   /* returns 1=worked 0=failed (see errno)*/

TCPIPEXP VOID
byetcp(                            /* log-off a TCP/IP user w/message      */
INT msgnum,                        /* same parameters as prfmsg()          */
...);                              /* usrnum is an implicit input          */
                                   /* (for backward compatibility only;    */
                                   /* for new code, use byendl())          */

TCPIPEXP INT                       /*   value to pass to iskclose()        */
iskopen(VOID);                     /* permit GCDI channel input sink use   */

TCPIPEXP VOID
iskclose(                          /* end of GCDI channel input sink use   */
INT oldicx);                       /*   from corresponding iskopen()       */

TCPIPEXP INT
__allow_cdi_interrupts(VOID);      /* guts of allow_cdi_interrupts macro   */

TCPIPEXP INT
__prevent_cdi_interrupts(VOID);    /* guts of prevent_cdi_interrupts macro */

TCPIPEXP VOID
__restore_cdi_interrupts(          /* guts of restore_cdi_interrupts macro */
INT savifl);

TCPIPEXP VOID
cdi_dmbufs(                        /* dmbufs() with interrupts enabled     */
struct datstm far *dsp,            /* DataStream structure (inside bufstm) */
USHORT nactual);                   /* this many were moved by the source   */

TCPIPEXP VOID
svrcatast(                         /* system-fatal error with TCP/IP svr   */
CHAR *type,                        /* such as "BIND" or "LISTEN"           */
INT port);                         /* TCP port number                      */

TCPIPEXP VOID
svrfail(                           /* session-fatal error with TCP/IP svr  */
INT unum,                          /* user number (or -1=not applicable)   */
CHAR *type,                        /* such as "SEND" or "RECEIVE"          */
INT port);                         /* TCP port number                      */

TCPIPEXP VOID
tcpfail(                           /* session-fatal error with TCP/IP      */
INT unum,                          /* (see TCPIP.C for parameters)         */
CHAR *fmt,
...);

TCPIPEXP CHAR *                    /*   return pointer to error message    */
tcpErrStg(                         /* convert tcpip_errno to text message  */
INT tcperrno);                     /*   TCP/IP error number                */

TCPIPEXP INT                                /*   return index number of socket      */
addSktIdx(                         /* add socket index to socket array     */
INT skt);                          /*   socket to add to array             */

TCPIPEXP INT                       /*   return index number of socket      */
getSktIdx(                         /* get socket index from socket array   */
INT skt);                          /*   socket number to look up           */

TCPIPEXP INT                       /*   return socket                      */
getIdxSkt(                         /* get socket fron index number         */
INT idx);                          /*   index number to look up            */

TCPIPEXP VOID
rmvSktIdx(                         /* removes socket from socket array     */
INT skt);                          /*   socket to remove from socket array */

#ifdef PACSOFT                     /* intercepted calls                    */

#define accept(a,b,c) gal_accept(a,b,c)
#define bind(a,b,c) gal_bind(a,b,c)
#define connect(a,b,c) gal_connect(a,b,c)
#define getpeername(a,b,c) gal_getpeername(a,b,c)
#define getsockname(a,b,c) gal_getsockname(a,b,c)
#define listen(a,b) gal_listen(a,b)
#define recv(a,b,c,d) gal_recv(a,b,c,d)
#define recvfrom(a,b,c,d,e,f) gal_recvfrom(a,b,c,d,e,f)
#define send(a,b,c,d) gal_send(a,b,c,d)
#define sendto(a,b,c,d,e,f) gal_sendto(a,b,c,d,e,f)
#define socket(a,b,c) gal_socket(a,b,c)
#define hinit(a,b,c) gal_hinit(a,b,c)

int gal_accept(int sd,saddr *addrp,int *addrlen);
int gal_bind(int sd,saddr *addrp,int addrsize);
int gal_connect(int sd,saddr *addrp,int addrlen);
int gal_getpeername(int sd,saddr *addrp,int *lenp);
int gal_getsockname(int sd,saddr *addrp,int *lenp);
int gal_listen(int sd,int backlog);
int gal_recv(int sd,char *buf,int len,int flags);
int gal_recvfrom(int sd,char *buf,int len,int flags,saddr *from,int *fromlen);
int gal_send(int sd,char *msg,int len,int flags);
int gal_sendto(int sd,char *msg,int len,int flags,saddr *to,int tolen);
int gal_socket(int af,int type,int protocol);
void gal_hinit(unsigned long * h_size,int far ** h_base);

#endif // PACSOFT

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* _TCPIP_H                             */
