/***************************************************************************
 *                                                                         *
 *   GCSPSRV.H                                                             *
 *                                                                         *
 *   Copyright (C) 1993 Consensus Systems, Inc.  All rights reserved.      *
 *   Copyright (c) 1993-1997 Galacticomm, Inc.   All rights reserved.      *
 *                                                                         *
 *   This is the include file for the Galacticomm Client/Server Protocol   *
 *   server-side handler for Worldgroup.  .                                *
 *                                                                         *
 *                                                - T. Stryker 8/5/93      *
 *                                                  C. Robert              *
 *                                                  B. Love                *
 *                                                                         *
 ***************************************************************************/

#ifndef __GCSPSRV_H
#define __GCSPSRV_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "gcsp.h"
#include "gendpk.h"
#include "cvtapi.h"
#include "galfda.h"

struct agent {                     /* agent information structure          */
     CHAR appid[AIDSIZ];
     VOID (*read)(INT direction,struct saunam *dpknam);
     VOID (*write)(struct saunam *dpknam,USHORT length,VOID *value);
     VOID (*xferdone)(VOID);
     VOID (*abort)(VOID);
};

WGSEXPV(struct agent*) agents;

WGSEXPV(INT) clisrv;               /* support client/server logons?        */

WGSEXPV(CHAR) msysid[SIDSIZ];      /* master sysid for this system         */
WGSEXPV(CHAR*) supappid;           /* signup agent's appid                 */
WGSEXPV(CHAR*) mmappid;            /* main menu agent's appid              */

#define FINFPTR ((struct filinf *)value)/* file info ptr (for read vector) */

struct reqdat {                    /* engine's internal per-request data   */
     struct saunam saunam;         /*   dynapak name                       */
     CHAR priority;                /*   priority from client               */
     CHAR state;                   /*   state used for tracking request    */
     VOID (*cycaddr)(VOID);        /*   "cycle me" address (or NULL)       */
     FILE *fp;                     /*   curr file pointer (file dynapaks)  */
     union {
          LONG crc[GLCSIZ];        /*   crc from client (dpk read only)    */
          LONG fbytes;             /*   # file bytes left (dpk write only) */
     } u;
     signed char direction;        /*   direction for lt/gt requests       */
     UINT askcnt;                  /*   count for lt/gt requests           */
     CHAR minmat;                  /*   saunam minimum byte match required */
     CHAR flags;                   /*   various per-request flags          */
};

WGSEXPV(struct reqdat*) rqdptr;    /* global ptr to engine's current reqdat*/

                                   /* per-request flags                    */
#define ACKRES      1              /*   acknowledge d/l resume next block  */

struct usrdat {                    /* engine's internal per-user C/S data  */
     CHAR sysid[SIDSIZ];           /*   this channel's default 's' value   */
     CHAR usrid[UIDSIZ];           /*   this channel's default 'u' value   */
     INT apierr;                   /*   API layer error code => disconnect */
     INT ncyclers;                 /*   number of cyclers for this channel */
     INT rrobin;                   /*   round-robin counter for cycling    */
     INT ndowners;                 /*   number of downloads on this channel*/
     INT rrobdl;                   /*   round-robin counter for downloading*/
     INT ngtlters;                 /*   number of gt/lt reqs needing svc   */
     INT rrobgl;                   /*   round-robin counter for gt/lt svc  */
     UINT filechnk;                /*   chunk size for downloading         */
     INT nintbl;                   /*   # of agents in server app table    */
     INT flags;                    /*   various per-user flags             */
};
WGSEXPV(struct usrdat*) usrdat;    /* pointer to per-user C/S data array   */
WGSEXPV(struct usrdat*) usdptr;    /* pointer to current user's C/S data   */
                                   /* usdptr->flags bit definitions        */
#define SENTSAP     1              /*   user was sent server app table     */
#define USRISUP     2              /*   user up-and-running with app layer */

WGSEXPV(INT) mrqsiz;               /* size of per-request memory area      */
WGSEXPV(CHAR*) mrqptr;             /* ptr to per-request memory for agents */
WGSEXPV(INT) greqid;               /* global copy of request id underway   */

#define srvrqid(u,r) ((u)*MAXREQS+(r)) /* get server reqid from client one */
#define clirqid(r) ((r)%MAXREQS)   /* get client reqid from server one     */
#define rqidunm(r) ((r)/MAXREQS)   /* get server user # from server reqid  */

WGSEXPV(CHAR*) rsptmp;             /* buffer for agents to store responses */
WGSEXPV(struct saunam*) namtmp;    /* temp buffer for agents to store names*/
WGSEXPV(INT) nagents;              /* number of agents                     */
WGSEXPV(CHAR) erraid[AIDSIZ];      /* appid that generated API error       */

#define APRMXERR    401            /* reqid received from client > MAXREQS */
#define APAVLERR    402            /* reqid not available                  */
#define APTYPERR    403            /* bad header type received             */
#define APR2RERR    404            /* agent called rsp2read() for no reason*/
#define APR2WERR    405            /* agent called rsp2write() "  "    "   */
#define APSHORTP    406            /* received packet too short            */
#define APWRFERR    407            /* received file packet out of sequence */
#define APNOFILR    408            /* agent failed to handle file dynapak  */
#define APOK2ERR    409            /* agent called ok2write() for no reason*/
#define APOK2WNG    410            /* ok2write() couldn't fopen() filespec */
#define APFWRERR    411            /* disk I/O error on upload-file write  */
#define APFRDERR    412            /* disk I/O error on download-file read */
#define APF2SHRT    413            /* received file shorter than expected  */
#define APF2LONG    414            /* received file longer than expected   */
#define APFINFNG    415            /* received file info header bad length */
#define APR2RNAM    416            /* agent gave rsp2read() bad dpk name   */
#define APR2RFNM    417            /* agent gave rsp2read() !existent file */
#define APC2SERR    418            /* incoming dpk name formatting error   */
#define APCSUOOS    419            /* incoming change "su" cmd out of seq  */

#define MAXTASK       1            /* max # of EXE's active at once        */
#define DMSINOB    1000            /* dft. ms of data to keep in outbuf buf*/

#define samepat(sau1,sau2) samepatu(sau1,sau2,TRUE)
#define samepato(shorts,longs) samepatu(shorts,longs,FALSE)

WGSEXP VOID inigcsp(VOID);
WGSEXP VOID sndsap(INT chan);
WGSEXP GBOOL apinid(INT chan);
WGSEXP VOID gcsasc(VOID);
WGSEXP VOID gcs2cs(VOID);
WGSEXP CHAR *rnosid(CHAR *regno);
WGSEXP VOID inisysagt(VOID);
WGSEXP VOID gcsplon(VOID);
WGSEXP VOID gcsphup(VOID);
WGSEXP VOID gcsprst(VOID);
WGSEXP VOID gcspnl(INT naklim);
WGSEXP GBOOL gcspaus(UINT snccon,CHAR *incbuf,INT nbytes);
WGSEXP GBOOL gcsplas(CHAR *stg);

WGSEXP VOID register_agent(struct agent *agdptr);
WGSEXP VOID curcsu(INT chan);
WGSEXP VOID curreq(INT reqid);
WGSEXP GBOOL forreal(VOID);
WGSEXP GBOOL iswrite(VOID);
WGSEXP GBOOL ismyreq(INT reqid,CHAR *appid);
WGSEXP VOID ok2write(CHAR *filespec);
WGSEXP GBOOL qroom(INT chan,INT priority);
WGSEXP VOID dclmrq(INT minsiz);
WGSEXP CHAR *mrqoff(INT reqid);
WGSEXP VOID cycleme(VOID (*cycaddr)(VOID));

#ifdef GCV2

VOID rsp2read(struct saunam *name,USHORT length,VOID *value);
VOID rsp2write(GBOOL ok,USHORT length,VOID *data);
VOID senddpk(INT chan,CHAR *dstapp,INT priority,struct saunam *dpknam,
          USHORT length,VOID *value);

#define rsp2read(nam,len,val,fda) rsp2read(nam,len,val)
#define rsp2write(ok,len,dat,fda) rsp2write(ok,len,dat)
#define senddpk(chn,dst,pri,dpk,len,val,fda) senddpk(chn,dst,pri,dpk,len,val)

#else

WGSEXP VOID rsp2read(struct saunam *name,USHORT length,VOID *value,struct flddef *fda);
WGSEXP VOID rsp2write(GBOOL ok,USHORT length,VOID *data,struct flddef *fda);
WGSEXP VOID senddpk(INT chan,CHAR *dstapp,INT priority,struct saunam *dpknam,
          USHORT length,VOID *value,struct flddef *fda);

#endif // GCV2

 /* GAUTLSRV.C prototypes */

WGSEXP GBOOL
stdchk(                            /* does current C/S user have key?      */
CHAR *key);                        /*   key name                           */

WGSEXP GBOOL
stdmchk(                           /* does cur user have key in message?   */
INT mnum);                         /*   message number with key name       */

WGSEXP VOID
rejectreq(VOID);                   /* reject current request               */

WGSEXP VOID
r2rgdp(                            /* respond to read with generic dynapak */
INT direction,                     /*   read direction: 0=eq, 1=gt, -1=lt  */
struct saunam *dpknam);            /*   dynapak name to respond to read of */

WGSEXP void
r2rprf(                            /* respond to read with prfbuf contents */
struct saunam *name);              /*   dynapak name to respond to read of */

WGSEXP VOID
r2wprf(                            /* respond to write w/ prfbuf contents  */
GBOOL ok);                         /*   TRUE/FALSE, write succeeded?       */

WGSEXP CHAR *                             /*   returns dev form dpk               */
cnvs2d(                            /* convert dpk from struct to dev form  */
struct saunam *saunam);            /*   structure form dynapak name        */

WGSEXP GBOOL                              /*   returns whether successful         */
cnvd2s(                            /* convert dpk from dev to struct form  */
CHAR *saustg,                      /*   dynapak name in developer form     */
struct saunam *saunam);            /*   (dest) dpk name in structure form  */

WGSEXP CHAR *
stp4cs(                            /* strip buffer for C/S output          */
CHAR *buf);                        /*   buffer to strip, returns also      */

WGSEXP VOID
reflow(                            /* re-flow buffer for C/S output        */
CHAR *buf);                        /*   buffer to re-flow                  */

WGSEXP struct saunam *
saunmu(                            /* return WGM-specific unsol dpk struct */
CHAR *suffix);                     /*   suffix to use                      */

WGSEXP GBOOL
vtmsndok(                          /* ok to send to this channel?          */
INT tochan);                       /*   c/s user's usrnum                  */

WGSEXP VOID                               /*   call right after vtmsndok() == TRUE*/
vtmsend(                           /* send data to the channel             */
INT srcid,                         /*   source identifier (hwnd)           */
INT length,                        /*   length of data                     */
VOID *value);                      /*   data to send                       */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __GCSPSRV_H                          */
