/***************************************************************************
 *                                                                         *
 *   RLOGIND.H                                                             *
 *                                                                         *
 *   Copyright (c) 1995-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Rlogin daemon for Worldgroup.                                         *
 *                                                                         *
 *                                        - Craig Yap  5/23/95             *
 *                                                                         *
 ***************************************************************************/

#ifndef __RLOGIND_H
#define __RLOGIND_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT
#   ifdef __BUILDRLOGIND
#       define RLGNDEXP         EXPORT
#       define RLGNDEXPV(x)     EXPORT_VARIABLE(x)
#       define RLGNDEXPF(x, y)  EXPORT_FUNCTION(x, y)
#    else
#       define RLGNDEXP         IMPORT
#       define RLGNDEXPV(x)     IMPORT_VARIABLE(x)
#       define RLGNDEXPF(x, y)  IMPORT_FUNCTION(x, y)
#    endif
#else
#       define RLGNDEXP
#       define RLGNDEXPV
#       define RLGNDEXPF
#endif // GCWINNT

//#define LGNPORT 513                /* TCP/IP port for Rlogin servers       */
#define LGNNAME "Rlogin"           /* name of server                       */
#define LGNBACKLOG 5               /* max # of colliding incoming calls    */
#define TNMLEN  6                  /* max length for incoming terminal name*/
#define NNULSR  4                  /* number of required NULs to begin     */
#define MAXB4N  512                /* max bytes before all NULs received   */

struct RLGNDEXP lgndinf {          /* Rlogin/channel info                  */
     INT nnuls;                    /* number of NULs received so far       */
     INT nbsofar;                  /* number of bytes read so far          */
     UCHAR flags;                  /* see LGNXXX flags below               */
     LONG bytlon;                  /* bturep(CNTCHR) at logon              */
};

RLGNDEXPV(struct lgndinf*) lgndinf;/* array of user/rlogin info            */
RLGNDEXPV(INT) errcod;             /* error code used for connect refuse   */

                                   /*--- flag bits for lgndinf->flags -----*/
#define LGNCHN 0x01                /*   rlogin daemon controlling this chan*/

RLGNDEXPV(INT) rdtact;             /* set by tnordt(), actual # bytes recd */

RLGNDEXP VOID
lgnincall(                         /* begin incoming Rlogin session        */
INT gotchn);                       /* 1=chan (curusr) assigned, 0=not avail*/
                                   /* implicit:  clskt=socket to client    */

RLGNDEXP INT
lgndcnt(VOID);                     /* count of rlogin server connections   */

RLGNDEXP USHORT
lgnskw(                            /* snkwin() for Rlogin sessions         */
struct datstm *dsp);               /* DataStream structure                 */
                                   /* returns room in buffer               */

RLGNDEXP VOID
lgndmv(                            /* didmov() for Rlogin sessions         */
struct datstm *dsp,                /* DataStream structure                 */
USHORT nactual);                   /* this many were moved by the source   */

RLGNDEXP USHORT
lgnmit(                            /* moveit() for Rlogin sessions         */
struct datstm *dsp,                /* (pointer to sink's datstm structure) */
UCHAR *srcloc,                     /* source specifies the location        */
USHORT nwant);                     /* source wants sink to move this many  */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __RLOGIND_H
