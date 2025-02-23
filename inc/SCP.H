/***************************************************************************
 *                                                                         *
 *   SCP.H                                                                 *
 *                                                                         *
 *   Copyright (c) 1995-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   SLIP/CSLIP/PPP services for users.                                    *
 *                                                                         *
 *                                              - R. Stein  9/1/95         *
 *                                                                         *
 ***************************************************************************/

#ifndef __SCP_H
#define __SCP_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT
#ifdef __BUILDSCP
#define SCPEXP __export
#else
#define SCPEXP __import
#endif
#else
#define SCPEXP
#endif // GCWINNT

                                   /*--- indexes of SLIP types          ---*/
#define SLPIDX   0                 /* plain SLIP                           */
#define CSLIDX   1                 /* VJ compressed SLIP                   */
#define PPPIDX   2                 /* PPP                                  */
#define NSTYPES  3                 /*--- total number of SLIP types     ---*/

#define BBGSCP_SPARE (80-sizeof(ULONG)-MNMSIZ-UIDSIZ)
struct bbgscp {                    /* BBSGEN record for dedicated IP addrs */
     CHAR userid[UIDSIZ];          /* User-ID                              */
     CHAR modnam[MNMSIZ];          /* Module name (always scpnam)          */
     ULONG ipaddr;                 /* Assigned IP address (network order)  */
     CHAR spare[BBGSCP_SPARE];     /* spare space (80 bytes total)         */
};
#define genbbscp    ((struct bbgscp *)genbb->data)

struct scpinf {                    /* non-VDA storage for GALSCP, per chan */
     INT idx;                      /* SLPIDX, CSLIDX, or PPPIDX            */
     INT flags;                    /* see SCPXXX masks below               */
};                                 /* (zeroed out by scpclear())           */

                                   /*--- scpinf->flags masks            ---*/
#define SCPQLN 0x0001              /* quick log-on suffix supplied         */
#define SCPKAL 0x0002              /* keepalive (inhibit IDLZAP)           */
#define SCPPRX 0x0004              /* proxy mode   \ both clear when       */
#define SCPDYN 0x0008              /* dynamic mode / assigned IP in use    */
#define SCPALV 0x0010              /* SCP session begun                    */

extern
struct scpinf * SCPEXP scpinf;     /* array of per-user non-VDA storage    */
extern
CHAR * SCPEXP nametbl[];           /* SLIP type names                      */
extern
ULONG SCPEXP scpipb;               /* base IP address, network byte order  */
extern
ULONG SCPEXP scpmkb;               /* [sub]network mask, network byte order*/
extern
UINT SCPEXP scpmtu;                /* Maximum Transmission Unit, SLIP users*/
extern
GBOOL SCPEXP userips;              /* user assigned & dynamic IP addresses?*/
extern
ULONG SCPEXP numip;                /* number of possible IP addresses      */
extern
UINT * SCPEXP ipused;              /* bit-array of assigned IP addresses   */
#define IPUWRDS ((UINT)((numip+sizeof(UINT)*8-1)/ \
                                       sizeof(UINT)*8))
                                   /* number of words in ipused array      */

struct scpvda {                    /* VDA storage for LIVE SLIP, per chan  */
     CHAR realuid[UIDSIZ];         /* User-ID using SLIP/CSLIP/PPP         */
     USHORT sttime;                /* state change time, 1/16 sec units    */
     ULONG tckstt;                 /* time started SLIP/CSLIP/PPP          */
     ULONG nbytes;                 /* bytes exchanged (S/C/P-encoded form) */
     CHAR *whyend;                 /* static description why session ended */
     LONG chgdue;                  /* credit charges pending (tfc+time)    */
     LONG timdue;                  /* phantom user accumulates time today  */
     LONG lclbytes;                /* local traffic already charged for    */
     LONG rembytes;                /* remote traffic already charged for   */
     INT mvtimer;                  /* secs since last credit/class sync-up */
     CHAR buffer[1];               /* scpsiz-byte     \ keep these         */
};                                 /* buffer for CMAN / lines together!    */
#define scpptr     ((struct scpvda *)vdaptr)
#define scpusr(un) ((struct scpvda *)vdaoff(un))


struct scpcvda {                   /* VDA storage for CONFIGURATION        */
     LONG bbgpos;                  /* position of record in BBSGEN database*/
     struct bbgscp bbgscp;         /* User database record                 */
};
#define scpcptr     ((struct scpcvda *)vdaptr)
#define scpcusr(un) ((struct scpcvda *)vdaoff(un))


INT
numscp(                            /* num of a users in SLIP/CSLIP/PPP     */
INT excchn);                       /* exception user number (-1=no except) */

INT
numscpuid(                         /* qty of a User-ID in SLIP/CSLIP/PPP   */
INT excchn,                        /* exception user number (-1=no except) */
CHAR *uid);                        /* User-ID                              */

GBOOL                              /*   1=yes 0=no                         */
inscp(                             /* is channel in SLIP/CSLIP/PPP mode?   */
INT chn);                          /*   user number, 0 to nterms-1         */

GBOOL                              /*   TRUE=in SCPMASK-specified range    */
ipvalid(                           /* is IP address valid assignable?      */
ULONG ipadr);                      /*   IP address, network byte order     */

GBOOL                              /*   TRUE=in range and in database      */
ipassigned(                        /* is IP address available for use?     */
ULONG ipadr);                      /*   IP address, network byte order     */

VOID
ipassign(                          /* flag an IP address as assigned       */
ULONG ipadr);                      /*   IP address, network byte order     */

VOID
ipunassign(                        /* flag an IP address as not assigned   */
ULONG ipadr);                      /*   IP address, network byte order     */

ULONG                              /*   IP address, netw order, CHNOIP=none*/
ipdynamic(VOID);                   /* find unused IP address for dynamic   */
                                   /* assignment to a user (rotating scan) */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __SCP_H
