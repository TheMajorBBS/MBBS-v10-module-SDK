/***************************************************************************
 *                                                                         *
 *   FINGER.H                                                              *
 *                                                                         *
 *   Copyright (c) 1995-1997 Galacticomm, Inc. All Rights Reserved         *
 *                                                                         *
 *   Finger client for access to system and user information on the        *
 *   Internet.                                                             *
 *                                                                         *
 *                               2/23/95 - Bob Stein & Mahesh Neelakanta   *
 *                                                                         *
 ***************************************************************************/

#ifndef __FINGER_H
#define __FINGER_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define FNGOSIZ 256                /* max size of send-to-server buffer    */
#define FNGISIZ 2048               /* max size of recv chunks fm server    */

struct fnginf {                    /* Telnet client channel info (in VDA)  */
     CHAR sndbuf[FNGOSIZ];         /* send-to-server buffer                */
     UINT sbfcnt;                  /* number of bytes in buffer[]          */
     struct in_addr inaddr;        /* address of server (netw byte order)  */
     INT socket;                   /* socket for connection to server      */
     USHORT sttime;                /* 16Hz timing of connect()             */
     struct dns dns;               /* DNS resolution information           */
     ULONG tckonl;                 /* lngtck when connected                */
     ULONG byttfc;                 /* bytes traffic (either direction)     */
     INT rcvwin;                   /* currently advertised receive window  */
     INT lstoba;                   /* last btuoba() (output room)          */
};

#define fngptr ((struct fnginf *)vdaptr) /* Finger info for current user   */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __FINGER_H
