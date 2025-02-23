/***************************************************************************
 *                                                                         *
 *   GALTCPAT.H                                                            *
 *                                                                         *
 *   Copyright (c) 1995-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   TCP/IP outdialing module, emulating the ATDT command over a Telnet    *
 *   connection.                                                           *
 *                                                                         *
 *                                        - RNStein  3/13/95               *
 *                                                                         *
 ***************************************************************************/

#ifndef __GALCTPAT_H
#define __GALTCPAT_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT
#   ifdef __BUILDTCPAT
#       define TCPATEXP         EXPORT
#       define TCPATEXPV(x)     EXPORT_VARIABLE(x)
#       define TCPATEXPF(x, y)  EXPORT_FUNCTION(x, y)
#    else
#       define TCPATEXP         IMPORT
#       define TCPATEXPV(x)     IMPORT_VARIABLE(x)
#       define TCPATEXPF(x, y)  IMPORT_FUNCTION(x, y)
#    endif
#else
#       define TCPATEXP
#       define TCPATEXPV
#       define TCPATEXPF
#endif // GCWINNT

#define TNATSIZ 8+1                /* max length for incoming terminal name*/

struct TCPATEXP tatusr {           /* user-specific TCP/IP AT dialing info */
     UINT port;                    /* server's port (host byte order)      */
     INT flags;                    /* option flags (see TFLXXX in TELNET.H)*/
     INT flags2;                   /* see below                            */
     INT unum;                     /* user number                          */
     INT rcvwin;                   /* receive window, last advertised      */
     INT rbempt;                   /* max receive buffer room (btuoba())   */
     INT rbhyst;                   /* hysteresis for widening window       */
     USHORT lsctim;                /* sampled time of "lost carrier" (16Hz)*/
     struct tnoscb tnoscb;         /* TNO session control block \ keep     */
     CHAR stgrem[TNATSIZ-1];       /* rest tatusr.tnoscb.stg[]  / together!*/
};

                                   /*--- masks for tatusr->flags2       ---*/
#define TATLSC 0x0001              /* lost carrier detected, allow input...*/

                                   /*--- masks for tatusr->tnoscb->flags --*/
#define TNAECH 0x0001              /* 1=server responsible for client echo */
#define TNASBN 0x0002              /* 1=server in binary                   */
#define TNACBN 0x0004              /* 1=client in binary                   */
#define TNACSG 0x0008              /* 1=client in SGA (rare, but must ack) */

/* Note:  GALTCPAT uses a few fields in tcpipinf[usrnum] (e.g. socket,     */
/* which is NULL while GALTCPAT has control)                               */

TCPATEXPV(struct tatusr**) tatusr; /* pointers to tatusrs (TCP/IP only)    */
TCPATEXPV(CHAR*) tatpfx1;          /* outdialing prefix #1                 */
TCPATEXPV(CHAR*) tatpfx2;          /* outdialing prefix #2                 */
TCPATEXPV(INT) tatdnu;             /* user number using *tatdns (-1=none)  */
TCPATEXPV(struct dns*) tatdns;     /* DNS resolver (one at a time)         */
TCPATEXPV(INT) tatrng;             /* display RING CALLING <ipaddr>?       */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __GALTCPAT_H
