/***************************************************************************
 *                                                                         *
 *   IPX.H                                                                 *
 *                                                                         *
 *   Copyright (c) 1991-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Novell Netware IPX/SPX general purpose header file                    *
 *                                                                         *
 *                                             - R. Stein 12/08/90         *
 *                                                                         *
 ***************************************************************************/

#ifndef __IPX_H
#define __IPX_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define hilo(i) (((UINT)(i)>>8)|((CHAR)(i)<<8))
                /* swap hi and lo bytes (between Motorola and Intel order) */
               /* Note:  "lo-hi" = Intel format, "hi-lo" = Motorola format */

/*--- IPX and SPX Command Codes (for BX register) ---*/

#define IPXOPEN   0x00             /* IPX Open socket                      */
#define IPXCLOSE  0x01             /* IPX Close Socket                     */
#define IPXGETTRG 0x02             /* IPX Get Local Target                 */
#define IPXSEND   0x03             /* IPX Send Packet                      */
#define IPXLISTEN 0x04             /* IPX Listen For Packet                */
#define IPXSCHED  0x05             /* IPX Schedule IPX Event               */
#define IPXCANCEL 0x06             /* IPX Cancel Event                     */
#define IPXGETMRK 0x08             /* IPX Get Interval Marker              */
#define IPXGETADR 0x09             /* IPX Get Internetwork Address         */
#define IPXRELINQ 0x0A             /* IPX Relinquish Control               */
#define IPXDISCON 0x0B             /* IPX Disconnect From Target           */

#define SPXINIT   0x10             /* SPX Initialize                       */
#define SPXESTCON 0x11             /* SPX Establish Connection             */
#define SPXLISCON 0x12             /* SPX Listen for Connection            */
#define SPXTRMCON 0x13             /* SPX Terminate Connection             */
#define SPXABORT  0x14             /* SPX Abort Connection                 */
#define SPXSTATUS 0x15             /* SPX Get Connection Status            */
#define SPXSEND   0x16             /* SPX Send Sequenced Packet            */
#define SPXLISTEN 0x17             /* SPX Listen For Sequenced Packet      */

struct ipxhdr {                    /* IPX packet header contains...        */
     SHORT chksum;
     SHORT length; /* 30-576:  includes header PLUS rest of packet (hi-lo) */
     CHAR trnspt;                  /* IPX sets to 0                        */
     CHAR paktyp;                  /* 0=unknown 4=IPX 5=SPX                */
     CHAR dstnet[4];               /* destination network                  */
     CHAR dstnod[6];               /* destination node                     */
     SHORT dstsoc;                 /* destination socket (hi-lo)           */
     CHAR srcnet[4];               /* source network                       */
     CHAR srcnod[6];               /* source node                          */
     SHORT srcsoc;                 /* source socket (hi-lo)                */
};

#define IPXSIZ 546     /* max bytes of data field of IPX packet (after hdr) */

struct spxhdr {                    /* SPX packet header contains...        */
     struct ipxhdr ipx;            /* IPX header                           */
     CHAR connect;                 /* bits: 7=system 6=ackreq 4=eomessage  */
     CHAR datstm;    /* datastream type 00-FD=user defined FE=eoconnection */
     SHORT srccid;                 /* source connection ID                 */
     SHORT dstcid;                 /* destination connection ID            */
     SHORT seq;                    /* sequence number                      */
     SHORT ack;                    /* acknowledge number                   */
     SHORT allocn;            /* allocation number (acceptable incoming seq) */
};

#define SPXSIZ 534    /* max bytes of data field of SPX packet (after hdr) */

struct ecbgsbl {       /* Event Control Block (for use with GSBL btuhdr()) */
     VOID *link;
     VOID (*esr)();                /* event service routine                */
     CHAR inuse;                   /* 0=not in use FE=listening FF=sending */
     CHAR complt;          /* 0=good, non-zero=command-specific error code */
     SHORT socket;                 /* sending socket (hi-lo)               */
     CHAR ipxwsp[4];               /* IPX workspace                        */
     CHAR drvwsp[12];              /* driver workspace                     */
     CHAR immnod[6];               /* immediate node address               */
     SHORT frgcnt;                 /* fragment count (lo-hi)               */
     VOID *frgadr;                 /* address of first fragment            */
     SHORT frgsiz;                 /* size of first fragment (lo-hi)       */
     SHORT prtseg;         /* protected mode segment (GSBL-specific usage) */
     SHORT chanx2;             /* channel number * 2 (GSBL-specific usage) */
};

struct ecb2 {         /* Event Control Block (with 2 fragment descriptors) */
     VOID *link;
     VOID (*esr)();                /* event service routine                */
     CHAR inuse;                   /* 0=not in use FE=listening FF=sending */
     CHAR complt;          /* 0=good, non-zero=command-specific error code */
     SHORT socket;                 /* sending socket (hi-lo)               */
     CHAR ipxwsp[4];               /* IPX workspace                        */
     CHAR drvwsp[12];              /* driver workspace                     */
     CHAR immnod[6];               /* immediate node address               */
     SHORT frgcnt;                 /* fragment count (lo-hi)               */
     VOID *frgadr;                 /* address of first fragment            */
     SHORT frgsiz;                 /* size of first fragment (lo-hi)       */
     VOID *fr2adr;                 /* address of (optional) second fragment*/
     SHORT fr2siz;           /* size of (optional) second fragment (lo-hi) */
};

struct netnodsoc {                 /* Network, Node, and Socket            */
     CHAR net[4];
     CHAR nod[6];
     SHORT soc;
};

struct netnod {                    /* Network and Node                     */
     CHAR net[4];
     CHAR nod[6];
};

/*--- GSBL/LAN finite state machine ---*/
#define LSNONE  0           /*   For Non-LAN channels                       */
                            /*   For IPX Direct Circuit channels:           */
#define LSDCOMM 1           /*       Communicating                          */
                            /*   For IPX Virtual Circuit channels:          */
#define LSVRAWP 2           /*       Raw packet I/O mode                    */
#define LSVCOMM 3           /*       Communicating                          */
                            /*   For SPX channels:                          */
#define LSSIDLE 4           /*       Idle                                   */
#define LSSINWT 5           /*       Waiting for incoming call              */
#define LSSOUTW 6           /*       Waiting for outgoing call              */
#define LSSESTB 7           /*       Session Established                    */
#define LSSTERM 8           /*       Session Terminating (fm this side)     */

                            /* Flags from the GSBL/LAN:                     */
#define BTLIPXD  0x0001     /*    bit 0:  IPX Direct circuits supported     */
#define BTLIPXV  0x0002     /*    bit 1:  IPX Virtual circuits supported    */
#define BTLSPX   0x0004     /*    bit 2:  SPX circuits supported            */
#define BTLI7A   0x0100     /*    bit 8:  IPX driver is loaded              */
#define BTLSPXL  0x0200     /*    bit 9:  SPX is loaded                     */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __IPX_H                              */
