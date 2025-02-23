/***************************************************************************
 *                                                                         *
 *   DNS.H                                                                 *
 *                                                                         *
 *   Copyright (c) 1994-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Domain Name Service for Worldgroup.                                   *
 *                                                                         *
 *                                        - RNStein  7/13/94               *
 *                                                                         *
 ***************************************************************************/
#ifndef _DNS_H
#define _DNS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "tcpip.h"

#ifdef GCWINNT
#   ifdef __BUILDDNS
#       define DNSEXP           EXPORT
#       define DNSEXPV(x)       EXPORT_VARIABLE(x)
#       define DNSEXPF(x, y)    EXPORT_FUNCTION(x, y)
#    else
#       define DNSEXP           IMPORT
#       define DNSEXPV(x)       IMPORT_VARIABLE(x)
#       define DNSEXPF(x, y)    IMPORT_FUNCTION(x, y)
#    endif
#else
#       define DNSEXP
#       define DNSEXPV
#       define DNSEXPF
#endif // GCWINNT

                                   /*--- constants from RFC-1035 ----------*/
#define DNSPORT 53                 /* TCP/IP port for DNS servers          */
#define INCLASS 1                  /* Class for Internet domain space      */
#define TYPENONE 0                 /* no lookup in progress                */
#define TYPEA 1                    /* address type resource records        */
#define TYPECNAME 5                /* canonical name type resource records */
#define TYPEMX   15                /* mail exchanger type resource records */
#define DNSNSZ (255+1)             /* domain name storage space (incl NUL) */

                                   /*--- DNS header flags from RFC-1035 ---*/
#define DNSFQR 0x8000              /* QR: 1=response, 0=query              */
#define DNSFOP 0x7800              /* opcode:  0=standard                  */
#define DNSFAA 0x0400              /* AA: authoritative answer             */
#define DNSFTC 0x0200              /* TC: truncated datagram               */
#define DNSFRD 0x0100              /* RD: recursion desired                */
#define DNSFRA 0x0080              /* RA: recursion available              */
#define DNSFRC 0x000F              /* rcode:  0=no error, 3=name error     */
#define DNSFNE 0x0003              /* name error: rcode=3                  */

struct DNSEXP dns {                       /* DNS information, allocated by appl   */
     CHAR name[DNSNSZ];            /* domain name, supplied by application */
     CHAR *dmnsfx;                 /* where domain suffix was added to name*/
     VOID (*callbk)(               /* app call-back vector (w/curusr() set)*/
          struct dns *dnsptr);     /* pointer to this structure            */
     INT status;                   /* status codes, see below (>=0 is ok)  */
     CHAR atm;                     /* attempt to send, 0..NUMATM-1         */
     INT atmsec;                   /* seconds til we give up this attempt  */
     INT numaddr;                  /* total number of in_addr's to record  */
     struct in_addr inaddr[1];     /* first (or only) address to record    */
};                                 /* (follow with in_addr[numaddr-1])     */

#define MAXHSTS 16                 /* max host names stored in 'dnshstex'  */

struct DNSEXP dnshstex {                  /* extended DNS info, allocated.by appl */
     CHAR *buf;                    /* buffer to store host names           */
     UINT bufsiz;                  /* buffer size                          */
     UINT maxofhst;                /* max number of hosts == MAXHSTS       */
     UINT numofhst;                /* actual humber of hosts               */
     struct {
          UINT prefval;            /* preference value for MX lookup       */
          CHAR *hostname;          /* host name                            */
     } host[MAXHSTS];
};
                                   /*--- status codes (-error codes) ------*/
#define DNSQRY  5                  /* need to send query, wait on select() */
#define DNSANS  4                  /* query sent, expecting an answer      */

#define DNSLOK  3                  /* address same as "LAST" address       */
#define DNSNOK  2                  /* address is literal numeric           */
#define DNSHOK  1                  /* address retrieved from HOSTS file!   */
#define DNSSOK  0                  /* address retrieved from DNS server!   */

#define DNSNOX -1                  /* nonexistant domain name              */
#define DNSUNK -2                  /* unknown domain name                  */

#define DNSRNA -3                  /* server recursion not available       */
#define DNSTNC -4                  /* server response truncated            */
#define DNSTMO -5                  /* timeout - server down / unresponsive */
#define DNSERR -6                  /* communications error with recvfrom() */
#define DNSERS -7                  /* communications error with sendto()   */
#define DNSOVL -8                  /* overlapping DNS calls                */
#define DNSABT -9                  /* search aborted by operator           */
#define DNSSTX -10                 /* syntax error in name                 */

/*--- public variables ---*/
DNSEXPV(CHAR) dnsemg[];            /* Error msg for error callbk (status<0)*/
DNSEXPV(CHAR) svronl;              /* replies accepted from DNS server only*/
DNSEXPV(INT) isdns;                /* Name server being used?              */
DNSEXPV(CHAR*) domain;             /* this Worldgroup's domain name        */
DNSEXPV(CHAR*) hostnam;            /* this WGS's host name within domain   */
DNSEXPV(CHAR*) hdsufx;             /* domain suffix: ".domain"             */
DNSEXPV(CHAR*) hstdom;             /* host and domain comb:  "host.domain" */
DNSEXPV(struct sockaddr_in) dnsaddr; /* DNS server address, for sendto()   */

DNSEXP VOID
dnshelp(VOID);                     /* display help host name help message  */

DNSEXP INT
dnsn2a(                            /* DNS:  convert name to address        */
struct dns *dnsptr);               /* app fills in name, callbk, & numaddr */
                                   /* returns 1=immediate callbk 0=deferred*/
                                   /* expects curusr() to be in effect     */
                                   /* uses vdatmp                          */

DNSEXP VOID
dnsabt(VOID);                      /* Abort DNS lookup                     */
                                   /* expects curusr() to be in effect     */

DNSEXP VOID
dnsfre(                            /* release "extra" usrnum               */
INT unum);

DNSEXP INT
dnsn2at(                           /* extended DNS lookup with svc type    */
struct dns *dnsptr,
SHORT type);                       /* service type (TYPECNAME,TYPEA,TYPEMX)*/

DNSEXP INT
dnsn2ex(                           /* extended DNS lookup (svc type + hosts)*/
struct dns *dnsptr,
SHORT type,                        /* service type (TYPECNAME,TYPEA,TYPEMX)*/
struct dnshstex *dnsexptr);        /* host names                           */

DNSEXP INT
dnsfvc(VOID);                      /* DNS find vacant channel              */

DNSEXP GBOOL                       /*  TRUE if valid domain name           */
dnsValidDomain(                    /* Check for valid domain name          */
const CHAR* Domain);               /*  Domain name to check                */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* _DNS_H                               */
