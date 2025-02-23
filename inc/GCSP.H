/***************************************************************************
 *                                                                         *
 *   GCSP.H                                                                *
 *                                                                         *
 *   Copyright (c) 1993 Consensus Systems, Inc.  All rights reserved.      *
 *   Copyright (c) 1993-1997 Galacticomm, Inc.   All rights reserved.      *
 *                                                                         *
 *   This is the header file for client/server side-independent logic.     *
 *                                                                         *
 *                                                - T. Stryker 8/5/93      *
 *                                                  C. Robert              *
 *                                                  B. Love                *
 *                                                                         *
 ***************************************************************************/

#ifndef __GCSP_H
#define __GCSP_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define STGLEN  ((USHORT)0xFFFF)   /* pass as length for implicit length   */

#define SIDSIZ   5                 /* sysid size                           */
#define AIDSIZ   9                 /* appid size                           */
#define UIDSIZ  30                 /* usrid size                           */
#define FLGSIZ   1                 /* flags for file and local             */
#define SFXSIZ  40                 /* suffix size                          */

#define DNAMSIZ (3+SIDSIZ-1+3+AIDSIZ-1+3+UIDSIZ-1+FLGSIZ+1+1+SFXSIZ)
#define CNAMSIZ (2+AIDSIZ-1+1+SIDSIZ-1+1+UIDSIZ+1+SFXSIZ)

                                   /* Physical Layer                       */

                                   /* network connection types for phneto()*/
#define TYPSPX  0                  /*   Novell's SPX protocol              */
#define TYPTEL  1                  /*   Telnet                             */
                                   /* non-network connection types         */
#define TYPSER  10                 /*   serial (or modem) connection       */

                                   /* statuses while opening network port  */
#define OPENIP  1                  /*   open still in progress             */
#define OPENOK  0                  /*   connection is up                   */
#define OPENNS -1                  /*   open failed: couldn't find server  */
#define OPENNC -2                  /*   open failed: couldn't connect to " */

WGSEXP VOID phsini(VOID);
WGSEXP VOID phises(INT contyp);
WGSEXP VOID phinap(INT taskid);
WGSEXP GBOOL phopen(INT chan,INT comport);
WGSEXP CHAR *phsrvl(INT netype);
WGSEXP GBOOL phneto(INT chan,INT netype,CHAR *srvnam);
WGSEXP INT phnost(INT chan);
WGSEXP GBOOL phsetb(INT chan,UINT baudcd);
WGSEXP GBOOL pherrf(INT chan);
WGSEXP UINT phavai(INT chan);
WGSEXP UINT phosiz(INT chan);
WGSEXP VOID phclro(INT chan);
WGSEXP UINT phinbw(INT chan);
WGSEXP VOID phclri(INT chan);
WGSEXP GBOOL phoutp(INT chan,UINT length,CHAR *outbuf);
WGSEXP INT phpump(INT chan);
WGSEXP GBOOL phstat(INT chan);
WGSEXP UINT phinpu(INT chan,UINT length,CHAR *inpbuf);
WGSEXP VOID phclap(INT taskid);
WGSEXP GBOOL phclos(INT chan);
WGSEXP ULONG phtckr(VOID);
WGSEXP VOID phfses(VOID);
WGSEXP VOID phfin(VOID);

                                   /* Cross-layer codes                    */

#define DLTYPCTL    1              /* datalink linkstart packet            */
#define DLTYPDSN    2              /* datastream negotiation packet        */

#define TRTYPTBC   10              /* transport packet to-be-continued     */
#define TRTYPEND   11              /* end of transport packet              */

#define APTYPCSU   20              /* change default 's' and 'u' values    */

#define APTYPREQ   30              /* read specific dynapak                */
#define APTYPRGL   31              /* read greater-than/less-than w/count  */
#define APTYPWRT   32              /* write specific dynapak               */
#define APTYPWRF   33              /* write dynapak, file continuation     */
#define APTYPSTS   34              /* status/length check                  */
#define APTYPABO   35              /* abort request by reqid               */
#define APTYPDNR   36              /* download of file not required        */
#define APTYPRES   37              /* download can be resumed              */
#define APTYPSGL   38              /* directional status/length check      */

#define APTYPSAP   59              /* server apps table download           */

#define APTYPROK   60              /* read data CRC is OK                  */
#define APTYPRDI   61              /* read data download w/implied name    */
#define APTYPXOK   62              /* read data CRC is OK w/index          */
#define APTYPRDX   63              /* read data download w/explicit name   */
#define APTYPRDF   64              /* read dynapak, file continuation      */
#define APTYPRDN   65              /* read denied                          */
#define APTYPWRR   66              /* write response                       */
#define APTYPEVT   67              /* "event": unsolicited dpk received    */
#define APTYPLEN   68              /* dynapak length for APTYPSTS          */
#define APTYPDNC   69              /* download-not-required confirmation   */
#define APTYPABC   70              /* abort confirmation                   */
#define APTYPSLN   71              /* dynapak length for APTYPSGL          */
#define APTYPSDN   72              /* directional status read denied       */

#define NPRIOS      6              /* total number of request priorities   */

                                   /* priority levels (-1 for file reqs)   */
#define BACKGND     1              /*   background priority                */
#define NORMAL      3              /*   normal priority (user waiting)     */
#define CRASH       5              /*   ultra-urgent priority              */

#define ZLNCRC      (0xFFFFFFFFL)  /* CRC of zero-length string            */

                                   /* Datalink Layer                       */

#define DLDESYNC   101             /* other guy ACK'ed a packet not sent   */
#define DLCTLERR   102             /* link-start control out of sequence   */
#define DLNAKLIM   103             /* too many NAKs in a row to continue   */
#define DLLNKSIZ   104             /* link-start packet too short          */
#define DLINVLNK   105             /* invalid link-start packet            */

#define MINWCT   2                 /* minimum window packet count          */
#define MAXWCT  32                 /* maximum window packet count          */
#define MAXPSZ 275                 /* maximum packet size (w/o overhead)   */
#define PAKOVH   7                 /* minimum packet overhead              */
#define MAXPZO (MAXPSZ*2+PAKOVH*2) /* maximum packet size (w/ overhead)    */

struct rtxarr {                    /* structure for retransmission array   */
     UINT length;                  /*   length of packet                   */
     CHAR data[MAXPSZ];            /*   packet contents                    */
};

struct dldata {                    /* datalink layer per-channel structure */
     INT state;                    /*   state of datalink for this channel */
     UINT paksiz;                  /*   negotiated packet size             */
     UINT bytthr;                  /*   output buffer transmit threshold   */
     INT rtxhdl;                   /*   hdl for retransmit array or window */
     INT rtxaix;                   /*   retransmission array ahead index   */
     INT rtxbix;                   /*   retransmission array behind index  */
     INT rtxkix;                   /*   ACK'd-so-far packet index          */
     UINT winpct;                  /*   negotiated window packet count     */
     INT rnakct;                   /*   received NAK counter               */
     CHAR rcvdok;                  /*   last packet number received OK     */
     INT gotsyn;                   /*   got the <SYN> part of <DLE><SYN>?  */
     INT gotdle;                   /*   got the <DLE> part of <DLE><SYN>?  */
     INT mstsnd;                   /*   do we need to send something now?  */
     INT mstrcv;                   /*   need to receive something now?     */
     GBOOL locked;                 /*   is our output currently locked?    */
     LONG __dummy__;               /*   align 'rpkbuf' on 4 byte boundary  */
     CHAR rpkbuf[MAXPZO];          /*   buffer to receive packets into     */
     CHAR *rpkptr;                 /*   current pointer into rpkbuf[]      */
     ULONG time;                   /*   time of last action req'ing resp   */
     INT dlerr;                    /*   datalink error code                */
     INT dsohead;                  /*   datastream layer overhead (bytes)  */
     GBOOL log;                    /*   log all interactions for channel?  */
};

                                   /* datalink channel state codes         */
#define DLDOWN      0              /*   channel down                       */
#define DLSING      1              /*   channel starting up                */
#define DLNING      2              /*   channel negotiating                */
#define DLUPOK      3              /*   channel up and ok                  */

WGSEXP VOID dlsini(INT nchans,INT ncperw,LONG id);
WGSEXP VOID dlinit(INT chan,ULONG cpsrat,UINT moutms,UINT winsiz,GBOOL log);
WGSEXP VOID dlrini(INT chan);
WGSEXP VOID dlclos(INT chan);
WGSEXP INT dlpump(INT chan);
WGSEXP VOID dlrecv(INT chan,UINT len,CHAR *buf);
WGSEXP VOID dllock(INT chan);
WGSEXP GBOOL dllokd(INT chan);
WGSEXP VOID dlunlk(INT chan);
WGSEXP UINT dlavai(INT chan);
WGSEXP VOID dloutp(INT chan,UINT length,CHAR *outbuf);
WGSEXP VOID dlfin(VOID);
WGSEXP VOID dlnaklim(INT newlim);
WGSEXP UINT dlNegAvai(INT chan);
WGSEXP VOID dlNegOutp(INT chan,UINT length,CHAR *outbuf);
WGSEXP VOID dlNegDone(INT chan);

/* Datastream Layer (a sub-layer of Datalink) */

#define DSNSIZ      9              /* datastream module name length        */

struct dsModule {                  /* datastream module interface struct   */
     CHAR name[DSNSIZ];            /*   short, unique name                 */
     INT version;                  /*   3-digit version (like 100; never 0)*/
     VOID                          /*     (no return value)                */
     (*initdsm)(                   /*   initialize datastream module       */
     INT nchans);                  /*     total number of channels         */
     UINT                          /*     number of bytes put in buf       */
     (*add2ls)(                    /*   maybe add to outbound linkstart    */
     INT chan,                     /*     channel number                   */
     UINT maxlen,                  /*     max number of bytes to add       */
     VOID *buf);                   /*     linkstart buffer to add bytes to */
     INT                           /*     how to continue (codes below)    */
     (*startup)(                   /*   datastream start-up query          */
     INT chan,                     /*     channel number                   */
     LONG id,                      /*     id of other side (0 or reg#)     */
     INT othsver,                  /*     0 or ver of this dsm on oth side */
     INT lsilen,                   /*     length of add'l info in linkstart*/
     VOID *lsinfo);                /*     NULL or add'l info in linkstart  */
     VOID                          /*     (no return value)                */
     (*gotneg)(                    /*   got negotiation packet in          */
     INT chan,                     /*     channel number                   */
     UINT length,                  /*     length of negotiation packet     */
     VOID *buf);                   /*     negotiation packet buffer        */
     INT                           /*     overhead (in bytes) per packet   */
     (*getpoh)(                    /*   get datastream module's overhead   */
     INT chan);                    /*     for this channel number          */
     VOID                          /*     (no return value)                */
     (*pumpit)(                    /*   ds module pump (when dsm not idle) */
     INT chan);                    /*     channel number                   */
     VOID                          /*     (no return value)                */
     (*datain)(                    /*   incoming data packet hook          */
     INT chan,                     /*     channel number                   */
     UINT *paklen,                 /*     length of packet                 */
     CHAR **pakptr);               /*     ptr to buffer holding packet     */
     VOID                          /*     (no return value)                */
     (*dataout)(                   /*   outgoing data packet hook          */
     INT chan,                     /*     channel number                   */
     UINT *paklen,                 /*     length of packet                 */
     CHAR **pakptr);               /*     ptr to buffer holding packet     */
     INT                           /*     true if dsm active false if not  */
     (*active)(                    /*   check to see if module active      */
     INT chan);                    /*      channel number                  */
     VOID                          /*     (no return value)                */
     (*dsquery)(                   /*   query the module for about info    */
     CHAR *buf,                    /*     buffer to fill with about info   */
     USHORT length);               /*     maximum length of buffer to fill */
     VOID                          /*     (no return value)                */
     (*closedown)(                 /*   connection down (when dsm not idle)*/
     INT chan);                    /*     channel number                   */
     VOID                          /*     (no return value)                */
     (*sysdown)(VOID);             /*   complete system shutdown           */
};

#define MAXBUF 256                 /* maximum size of query descripton buf */

#define DSCRYPT   1                /* datastream encrypted return value    */
#define DSACTIVE  2                /* datastream active return value       */

                                   /* start-up query return values         */
#define SUUPOK 1                   /*   interested, up and running         */
#define SUWNEG 2                   /*   interested, need to negotiate      */
#define SUNOTI 3                   /*   not interested in this connection  */

     /* side independent: shared between client and server            */
/* called by datastream modules    */
WGSEXP INT registerDSModule(struct dsModule *dsm);
WGSEXP GBOOL dsNegOut(INT dsmnum,INT chan,UINT length,VOID *outbuf);
WGSEXP VOID dsNegDone(INT dsmnum,INT chan,GBOOL upok);
/* called by datalink layer   */
WGSEXP VOID dssini(INT nchans,GBOOL iscli);
WGSEXP VOID dsinit(INT chan,ULONG cpsrat);
WGSEXP INT dspump(INT chan);
WGSEXP VOID dsclos(INT chan);
WGSEXP VOID dsfin(VOID);
WGSEXP UINT dsLSOut(INT chan,UINT maxlen,CHAR *buf);
WGSEXP GBOOL dsLSIn(INT chan,LONG id,UINT len,CHAR *buf);
WGSEXP INT dsGetOHead(INT chan);
WGSEXP VOID dsNegIn(INT chan,UINT paklen,CHAR *pakbuf);
WGSEXP VOID dsHookIn(INT chan,UINT *paklen,CHAR **pakptr);
WGSEXP VOID dsHookOut(INT chan,UINT *paklen,CHAR **pakptr);
     /* side dependent: implemented differently for client and server */
WGSEXP VOID dssiniSD(VOID);
WGSEXP VOID dsfinSD(VOID);

                                   /* Transport Layer                      */

#define   TRSHORTP  201            /* received packet too short            */
#define   TROVRFLO  202            /* transport buffer overflow            */
#define   TRBADPRI  203            /* bad priority passed to troutp()      */
#define   TRBADLEN  204            /* bad length passed to troutp()        */
#define   TRQUEFUL  205            /* output queue full                    */
#define   TRRPBPRI  206            /* received packet had bad priority     */

#define   MAXQUE    200            /* max # of packets queued per priority */
#define   MAXDPKV   16384          /* maximum dynapak blob-value size      */
#define   TREXTRA   104            /* extra > 16K in MAXTPSZ for API overhd*/
// value of TREXTRA should be evenly divisible  by malloc() granularity
#define   MAXTPSZ   (MAXDPKV+TREXTRA) /* maximum raw transport buffer size */
#define   ZSPACE    1              /* # of '\0' chars after in-mem record  */
#define   TRKEYSZ   4              /* Btrieve key size in swap file        */
#define   TRNVLSZ   5              /* non-volatile size of Btrieve record  */

#define   RECVIN    0              /* sndrcv value for inbound buffer      */
#define   SNDOUT    1              /* sndrcv value for outbound buffer     */

struct trbrec {                    /* structure for transport packet cache */
     CHAR chan;                    /*   channel transport packet is for    */
     CHAR priority;                /*   priority of transport packet       */
     CHAR sndrcv;                  /*   send/receive buffer indicator      */
     CHAR seqnum;                  /*   sequential number for sequence     */
     CHAR partial;                 /*   is this packet partially sent?     */
     CHAR data[MAXTPSZ];           /*   transport packet data              */
};

struct trbuf {                     /* struct for transport in-memory buffer*/
     UINT reclen;                  /*   length of current in-memory record */
     UINT nqdinm;                  /*   number of records queued in memory */
     UINT bytsqd;                  /*   total number of bytes queued in mem*/
     struct trbrec *rec;           /*   cur packet rec, or NULL if on disk */
     INT memidx;                   /*   idx of rec's mem record, if != NULL*/
};

struct trdata {                    /* per-channel transport layer structure*/
     struct trbuf in;              /*   input transport packet memory      */
     struct trbuf out;             /*   output transport packet memory     */
     CHAR tpkinq[NPRIOS];          /*   per-prio: input packet in queue?   */
     CHAR trbptr[NPRIOS];          /*   per-prio: output packet ahead ptr  */
     CHAR traptr[NPRIOS];          /*   per-prio: output packet behind ptr */
     INT lockseq;                  /*   sequence number to begin locking at*/
     INT trerr;                    /*   transport error code               */
};

WGSEXP VOID trsini(INT maxtask,INT nchans,INT ncperb,CHAR *msfile);
WGSEXP VOID trinit(INT chan);
WGSEXP VOID trinap(INT opnmode,CHAR *path);
WGSEXP VOID trrcvp(INT chan,UINT paklen,CHAR *pakbuf);
WGSEXP VOID trlknx(INT chan);
WGSEXP GBOOL trlokd(INT chan);
WGSEXP VOID trunlk(INT chan);
WGSEXP UINT travai(INT chan,INT priority);
WGSEXP GBOOL troclr(INT chan);
WGSEXP VOID troutp(INT chan,UINT paklen,CHAR *pakbuf,INT priority);
WGSEXP INT trpump(INT chan);
WGSEXP VOID trclap(VOID);
WGSEXP VOID trclos(INT chan);
WGSEXP VOID trfin(VOID);

                                   /* API Layer                            */

struct saunam {                    /* name of dynapak in "structure form"  */
     CHAR sysid[SIDSIZ];           /*   system ID                          */
     CHAR appid[AIDSIZ];           /*   application ID                     */
     CHAR usrid[UIDSIZ];           /*   user ID                            */
     CHAR flags;                   /*   flags (local, file, etc.)          */
     CHAR suffix[SFXSIZ];          /*   suffix                             */
};

WGSEXPV(struct flddef) saunamFDA[];

struct vbsaunam {                  /* VB form of saunam structure          */
     CHAR sysid[SIDSIZ-1];         /*   system ID                          */
     CHAR appid[AIDSIZ-1];         /*   application ID                     */
     CHAR usrid[UIDSIZ-1];         /*   user ID                            */
     CHAR flags;                   /*   flags (local, file, etc.)          */
     CHAR suffix[SFXSIZ-1];        /*   suffix                             */
};
                                   /* side-independent flag bits for saunam*/
#define FLGFIL    1                /*   dynapak is a file                  */
                                   /* additional client-side flag bits     */
#define FLGLCL    2                /*   dynapak is local to client         */

#define MAXREQS  30                /* max number of outstanding requests   */
#define MINFRQS   5                /* min free requests for qroom()        */

#define DLMCHR      ';'            /* delimiter for prefix overrides       */

#define GLCSIZ   16                /* greater-than/less-than chunk size    */

struct filinf {                    /* info in first packet of file dynapak */
     CHAR name[GCMAXFNM];          /*   file name                          */
     USHORT time;                  /*   file time                          */
     USHORT date;                  /*   file date                          */
     LONG size;                    /*   file size in bytes                 */
};
WGSEXPV(struct flddef) filinfFDA[];

                                   /* flags for typwrf and typrdf records  */
#define FILDUN      1              /*   this is the last packet in the file*/
#define ATRESO      2              /*   resuming file from here (rdf only) */

                             /* APTYP record layouts from client to server */

struct typcsu {          /* APTYPCSU: change default 's' and 'u' values    */
     CHAR hdrtyp;
     CHAR sysid[SIDSIZ];
     CHAR usrid[1];
};

struct typreq {          /* APTYPREQ: read specific dynapak                */
     CHAR hdrtyp;             /* priority and crc MUST follow reqid        */
     CHAR reqid;
     CHAR priority;
     LONG crc;
     CHAR name[1];
};

struct typrgl {          /* APTYPRGL: read greater-than/less-than w/count  */
     CHAR hdrtyp;
     CHAR reqid;
     CHAR priority;
     SCHAR direction;
     USHORT askcnt;
     CHAR minmat;
     CHAR namncrcs[1];
};

struct typwrt {          /* APTYPWRT: write specific dynapak               */
     CHAR hdrtyp;
     CHAR reqid;
     CHAR priority;
     CHAR namnval[1];
};

struct typwrf {          /* APTYPWRF: write dynapak, file continuation     */
     CHAR hdrtyp;
     CHAR reqid;
     CHAR flags;
     CHAR data[1];
};

struct typsts {          /* APTYPSTS: status/length check                  */
     CHAR hdrtyp;             /* priority and crc MUST follow reqid        */
     CHAR reqid;
     CHAR priority;
     LONG crc;
     CHAR name[1];
};

struct typabo {          /* APTYPABO: abort request by reqid               */
     CHAR hdrtyp;
     CHAR reqid;
     CHAR priority;
};

struct typdnr {          /* APTYPDNR: download of file not required        */
     CHAR hdrtyp;
     CHAR reqid;
     CHAR priority;
     SHORT whodnr;
};

struct typres {          /* APTYPRES: download of file can be resumed      */
     CHAR hdrtyp;
     CHAR reqid;
     CHAR priority;
     SHORT whores;
     LONG resoff;
};

                             /* APTYP record layouts from server to client */

struct typrok {          /* APTYPROK: read data CRC is OK                  */
     CHAR hdrtyp;
     CHAR reqid;
};

struct typrdi {          /* APTYPRDI: read data download w/implied name    */
     CHAR hdrtyp;
     CHAR reqid;
     USHORT length;
     CHAR data[1];
};

struct typxok {          /* APTYPXOK: read data CRC is OK w/index          */
     CHAR hdrtyp;
     CHAR reqid;
     CHAR crcidx;
};

struct typrdx {          /* APTYPRDX: read data download w/explicit name   */
     CHAR hdrtyp;
     CHAR reqid;
     USHORT length;
     CHAR namnval[1];
};

struct typsln {          /* APTYPSLN: directional status/length check      */
     CHAR hdrtyp;
     CHAR reqid;
     LONG length;
     CHAR name[1];
};

struct typrdf {          /* APTYPRDF: read dynapak, file continuation      */
     CHAR hdrtyp;
     CHAR reqid;
     CHAR flags;
     CHAR data[1];
};

struct typrdn {          /* APTYPRDN/APTYPSDN: read denied                 */
     CHAR hdrtyp;
     CHAR reqid;
};

struct typwrr {          /* APTYPWRR: write response                       */
     CHAR hdrtyp;
     CHAR reqid;
     CHAR ok;
     CHAR data[1];
};
                                   /* typwrr.ok flag bits                  */
#define WRRWOK 1                   /*   write was OK by the agent          */
#define WRRABR 2                   /*   agent responded early (abort req'd)*/

struct typevt {          /* APTYPEVT: "event": unsolicited dpk received    */
     CHAR hdrtyp;
     CHAR anamval[1];
};

struct typlen {          /* APTYPLEN: dynapak length for stsdpk()          */
     CHAR hdrtyp;
     CHAR reqid;
     LONG length;
};

struct typdnc {          /* APTYPDNC: download-not-required confirmation   */
     CHAR hdrtyp;
     CHAR reqid;
};

struct typabc {          /* APTYPABC: abort confirmation                   */
     CHAR hdrtyp;
     CHAR reqid;
};

WGSEXP VOID apsini(VOID);
WGSEXP VOID apinit(INT chan,ULONG cpsrat);
WGSEXP VOID aprcvp(INT chan,UINT paklen,CHAR *pakbuf,GBOOL endofp);
WGSEXP INT appump(INT chan);
WGSEXP VOID apclos(INT chan);
WGSEXP VOID apfin(VOID);

WGSEXP UINT cnvs2c(struct saunam *saunam,CHAR *combuf,CHAR *dsysid,CHAR *dusrid);
WGSEXP UINT s2capp(CHAR *cbfptr,CHAR *appid);
WGSEXP UINT cnvc2s(CHAR *combuf,struct saunam *saunam,CHAR *dsysid,CHAR *dusrid);
WGSEXP UINT c2sapp(CHAR *dest,CHAR *cbfptr);
WGSEXP LONG namcrc(LONG crc,struct saunam *sautmp);
WGSEXP GBOOL samepatu(CHAR *sau1,CHAR *sau2,GBOOL exact);

WGSEXP INT lupapp(CHAR *appid);
WGSEXP CHAR *namapp(INT appno);

                       /* Management Layer -- side independent prototypes */

WGSEXP INT gmtidx(VOID);
WGSEXP struct dldata *dldptr(INT chan);
WGSEXP struct trdata *trdptr(INT chan);

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __GCSP_H
