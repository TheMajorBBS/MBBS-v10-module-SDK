/***************************************************************************
 *                                                                         *
 *   TELNETD.H                                                             *
 *                                                                         *
 *   Copyright (c) 1994-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Telnet daemon for Worldgroup.                                         *
 *                                                                         *
 *                                        - RNStein  5/31/94               *
 *                                                                         *
 ***************************************************************************/

#ifndef __TELNETD_H
#define __TELNETD_H

#include "crnul.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define TNTPORT 23                 /* TCP/IP port for Telnet servers       */
#define TNTNAME "Telnet"           /* name of Telnet server                */
#define TNTBACKLOG 5               /* max # of colliding incoming calls    */
#define TNMSIZ (1+8+1)             /* max room (inc NUL) for terminal-type */

struct tntinf {                    /* Telnet/channel info                  */
     struct tnoscb tnoscb;         /* TNO session control block  \ keep    */
     CHAR stgrem[TNMSIZ-1];        /* rest of tntinf.tnoscb.stg[]/ together*/
     CHAR flags;                   /* see flags below                      */
     LONG bytlon;                  /* bturep(CNTCHR) at logon              */
     struct crnul crnul;           /* non-BINARY decoding (see CRNUL.H)    */
};

                                   /*--- masks for tntinf->flags ----------*/
#define TNTCHN 0x01                /* 1=Telnet daemon controlling this chan*/

TNTDEXPV(struct tntinf*) tntinf;   /* array of user/telnet info            */

                                   /*--- masks for tntinf->tnoscb->flags --*/
#define TNTECH 0x0001              /* 1=server responsible for client echo */
#define TNTSBN 0x0002              /* 1=server in binary                   */
#define TNTCBN 0x0004              /* 1=client in binary                   */
#define TNTCSG 0x0008              /* 1=client in SGA (rare, but must ack) */
#define TNTSSG 0x0010              /* 1=server in SGA (expected, must ack) */

TNTDEXPV(INT) tntunm;              /* tnordt() & subs: user number         */
TNTDEXPV(struct tcpipinf*) tiptr;  /* tnordt() & subs: tcpip info for user */
TNTDEXPV(INT) rdtact;              /* set by tnordt(), actual # bytes recd */
TNTDEXPV(CHAR) tntonl;             /* 1=Telnet daemon online, 0=not        */
TNTDEXPV(CHAR) tntrej;             /* (tntonl=0) 1=reject, 0=ignore calls  */

TNTDEXP VOID
init__galtntd(VOID);               /* initialize telnet server module      */

TNTDEXP VOID
tntincall(                         /* begin incoming Telnet session        */
INT gotchn);                       /* 1=chan (curusr) assigned, 0=not avail*/
                                   /* implicit:  clskt=socket to client    */

TNTDEXP INT
tntdcnt(VOID);                     /* count of telnet server connections   */

TNTDEXP VOID
tnordt(                            /* read Telnet-coded data to GCDI chan  */
struct tcpipinf *tip);             /* user's TCP/IP channel info           */
                                   /* application:  sktnfy(,,tntrdt,tiptr) */
                                   /* rdtact set to number of bytes read   */

TNTDEXP INT
ftsops(                            /* Monitor Telnet ops using FTSCOPE     */
INT code,                          /* see TNCXXXX codes in TNO.H           */
INT parm);                         /* see TNCXXXX codes in TNO.H           */
                                   /* tnoscb, tntunm are implicit inputs   */
                                   /* (returns -1 for passing to tnoini()) */

TNTDEXP USHORT
tntskw(                            /* snkwin() for Telnet sessions         */
struct datstm *dsp);               /* DataStream structure                 */
                                   /* returns 1/2 room in buffer (leaving  */
                                   /* room to double IAC's if necessary)   */

TNTDEXP VOID
tntdmv(                            /* didmov() for Telnet sessions         */
struct datstm *dsp,                /* DataStream structure                 */
USHORT nactual);                   /* this many were moved by the source   */

TNTDEXP USHORT
tntmit(                            /* moveit() for Telnet sessions         */
struct datstm *dsp,                /* (pointer to sink's datstm structure) */
CHAR *srcloc,                      /* source specifies the location        */
USHORT nwant);                     /* source wants sink to move this many  */

TNTDEXP INT
iacdec(                            /* Decode Telnet <IAC>-prefixed codes   */
CHAR *buffer,                      /* input encoded data, output decoded   */
INT nchars);                       /* number of encoded bytes input        */
                                   /* returns num bytes after decoding     */
                                   /* tnoscb is implicit input             */
                                   /* calls tnoini()-designated handler    */

TNTDEXP INT
iacenc(                            /* Encode IAC -> <IAC IAC> in place     */
CHAR *buffer,                      /* input unencoded data, output encoded */
INT nchars,                        /* number of unencoded bytes input      */
INT size);                         /* max room in buffer (precautionary)   */
                                   /* returns actual number of bytes moved */

TNTDEXP INT
decanp(                            /* decode addr & port h1,h2,h3,h4,p1,p2 */
CHAR *anp,                         /* address & port (destroyed in process)*/
struct in_addr *inaddr,            /* address where to put host address    */
USHORT *port);                     /* address where to put port            */
                                   /* output is in "n"=network byte order  */
                                   /* returns 1=ok, 0=bad format           */

TNTDEXP CHAR*
encanp(                            /* encode address & port for PORT cmd   */
ULONG naddr,                       /* IP address, network order            */
USHORT nport);                     /* TCP port, network order              */
                                   /* returns formatted string             */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __TELNETD_H                          */
