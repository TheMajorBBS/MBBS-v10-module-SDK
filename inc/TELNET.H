/***************************************************************************
 *                                                                         *
 *   TELNET.H                                                              *
 *                                                                         *
 *   Copyright (c) 1994-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Telnet client for Worldgroup                                          *
 *                                                                         *
 *                                        - RNStein  6/12/94               *
 *                                                                         *
 ***************************************************************************/

#ifndef __TELNET_H
#define __TELNET_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT
#   ifdef __BUILDTELNET
#       define TELNETEXP        EXPORT
#       define TELNETEXPV(x)    EXPORT_VARIABLE(x)
#       define TELNETEXPF(x, y) EXPORT_FUNCTION(x, y)
#    else
#       define TELNETEXP        IMPORT
#       define TELNETEXPV(x)    IMPORT_VARIABLE(x)
#       define TELNETEXPF(x, y) IMPORT_FUNCTION(x, y)
#    endif
#else
#       define TELNETEXP
#       define TELNETEXPV
#       define TELNETEXPF
#endif // GCWINNT

#define TNCBSIZ 256                /* max size of send-to-server buffer    */
#define TNCTSIZ (1+8+1)            /* max room (inc NUL) for terminal-type */
#define TNCREND 16                 /* how many recv()=0's mean a hang up?  */

struct TELNETEXP tncinf {          /* Telnet client channel info (in VDA)  */
     struct tnoscb tnoscb;         /* TNO session control block  \ keep to-*/
     CHAR stgrem[TNCTSIZ-1];       /* rest of tncinf.tnoscb.stg[]/ gether! */
     CHAR buffer[TNCBSIZ];         /* send-to-server buffer (IAC encoded)  */
     UINT bufcnt;                  /* number of bytes in buffer[]          */
     INT socket;                   /* socket for connection to server      */
     INT port;                     /* server's port (Intel byte order)     */
     UINT abtclk;                  /* time measure for abort string        */
     INT abtcnt;                   /* # of abort chars received            */
     USHORT sttime;                /* 16Hz timing of connect()             */
     struct dns dns;               /* DNS resolution information           */
     ULONG tckonl;                 /* lngtck when connected                */
     ULONG byttfc;                 /* bytes traffic (either direction)     */
     INT rcvwin;                   /* currently advertised receive window  */
     INT bntmax;                   /* binary negotiation, max number tries */
     INT bntccnt;                  /* bin client negotiation # tries so far*/
     INT bntscnt;                  /* bin server negotiation # tries so far*/
     INT flags;                    /* see below                            */
};

/*--- tncinf->flags masks ---*/
#define TFLASC 0x0001              /* -A ascii mode enabled                */
#define TFLINJ 0x0002              /* asynch message/reprompt in progress  */
#define TFLBKS 0x0004              /* -BS alt backspace (BS -> DEL) enabled*/
#define TFLKYR 0x0008              /* -KR alt keystroke return (^M -> ^J)  */
#define TFLSCR 0x0010              /* -SR alt screen return (^M^J <- ^J)   */
#define TFLCRB 0x0020              /* last block from host ended in <CR>   */
#define TFLNOB 0x0040              /* no binary negotiations at connect    */

/*--- tnoscb->flags masks ---*/
#define TNCECH 0x0001              /* server echo state 1=server will echo */
#define TNCSBN 0x0002              /* 1=server in binary                   */
#define TNCCBN 0x0004              /* 1=client in binary                   */
#define TNCCSG 0x0008              /* 1=client in SGA (rare, but must ack) */

#define tncptr ((struct tncinf *)vdaptr) /* TNC info for current user      */
#define tncusr(u) ((struct tncinf *)vdaoff(u)) /* TNC inf for specific user*/

TELNETEXPV(INT) tncstt;             /* Telnet client module state number    */

TELNETEXP VOID
tncrcv(                            /* Telnet client receive-from-server    */
struct tncinf *tnc);               /* user's telnet client info            */

TELNETEXP VOID
tncsnd(                            /* try to send staging buffer contents  */
struct tncinf *tnc);               /* Telnet client session info           */

TELNETEXP INT
sndopc(                            /* Telnet client sends an option string */
CHAR *bytes,                       /* binary string of bytes (may incl \0) */
INT nbytes);                       /* number of bytes                      */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __FINGERD_H
