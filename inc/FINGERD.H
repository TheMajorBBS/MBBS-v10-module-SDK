/***************************************************************************
 *                                                                         *
 *   FINGERD.H                                                             *
 *                                                                         *
 *   Copyright (c) 1995-1997 Galacticomm, Inc.  All Rights Reserved        *
 *                                                                         *
 *   Finger server for access to user information as stored in the         *
 *   Registry of Users, and also for finding out who is online.            *
 *                                                                         *
 *                               2/20/95 - Bob Stein & Mahesh Neelakanta   *
 *                                                                         *
 ***************************************************************************/

#ifndef __FINGERD_H
#define __FINGERD_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT
#   ifdef __BUILDFNGD
#       define FNGDEXP          EXPORT
#       define FNGDEXPV(x)      EXPORT_VARIABLE(x)
#       define FNGDEXPF(x, y)   EXPORT_FUNCTION(x, y)
#    else
#       define FNGDEXP          IMPORT
#       define FNGDEXPV(x)      IMPORT_VARIABLE(x)
#       define FNGDEXPF(x, y)   IMPORT_FUNCTION(x, y)
#    endif
#else
#       define FNGDEXP
#       define FNGDEXPV
#       define FNGDEXPF
#endif // GCWINNT

#define FNGPORT 79                 /* TCP port for Finger server           */
#define FNGNAME "Finger"           /* name of Finger server                */
#define FNGBACKLOG 5               /* listen() backlog                     */

struct FNGDEXP fngdusr {                   /* Finger server channel information    */
     INT unum;                     /* used when fingering online list      */
     INT nusers;                   /* count of online users listed         */
     USHORT sttime;                /* 16 Hz activity timer                 */
};

#define fngdptr ((struct fngdusr *)vdaptr)

FNGDEXPF(VOID, hdlfrq)(VOID);      /* Finger request handler vector        */
                                   /* request: margv[0],...,margv[margc-1] */
FNGDEXPF(VOID, usrrpt)(            /* Finger user report vector            */
     CHAR *usrnam);                /* user name                            */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __FINGERD_H
