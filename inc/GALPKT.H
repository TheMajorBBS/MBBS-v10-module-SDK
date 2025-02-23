/* GALPKT.H */

/* Ref PC/TCP Packet Driver Specification revision 1.11 released 6/2/94    */
/* Available from FTP Software:  ftp://ftp.ftp.com/pub/packetd/pds111.doc  */

#ifndef __GALPKT_H
#define __GALPKT_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define PDVFIRST 0x20              /* First possible packet driver vector  */
#define PDVLAST  0xFF              /* Last possible packet driver vector   */
#define PDVAUTO  0                 /* Signify pkt_init() to find pkt drvr  */
#define PDVNONE  (-1)              /* Signify pkt_init() no pkt drvr       */

/* Basic Packet Driver functions */

#define PKT_DRIVER_INFO         1
#define PKT_DRIVER_INFO_AX      ((PKT_DRIVER_INFO<<8)+255)
#define PKT_ACCESS_TYPE         2
#define PKT_RELEASE_TYPE        3
#define PKT_SEND_PKT            4
#define PKT_TERMINATE           5
#define PKT_GET_ADDRESS         6
#define PKT_RESET_INTERFACE     7

/* Selected High-Performance Packet Driver functions */

#define PKT_GET_PARAMETERS     10
#define PKT_AS_SEND_PKT        12
#define PKT_DROP_PKT           13

/* Selected Extended Packet Driver functions */

#define PKT_GET_STATISTICS     24
#define PKT_SET_ADDRESS        25
#define PKT_GET_STRUCTURE      30

/* Classes */

#define CLASS_ETHERNET   1
#define CLASS_TOKENRING  3

struct pkt_sendiocb {              /* structure for PKT_AS_SEND_PKT call   */
     char *buffer;                 /* pointer to packet xmit buffer        */
     unsigned length;              /* number of bytes in packet            */
     unsigned char flagbits;       /* see PKT_IOCB_XXX masks below         */
     unsigned char code;           /* packet driver error code             */
     void (*transmitter)();        /* transmitter done upcall              */
     char reserved[4];             /* future use                           */
     char private[8];              /* packet drivers private use           */
};

#define PKT_IOCB_DONE   0x01       /* packet driver is done with this iocb */
#define PKT_IOCB_UPCALL 0x02       /* application req (*transmit)() call   */

struct pkt_parameters {            /* structure for PKT_GET_PARAMETERS call*/
     char major;
     char minor;
     char length;
     char addr_len;
     short mtu;
     short aval;
     short rcv_bufs;
     short xmt_bufs;
     short int_num;
};

/*--- Constants, Macros and Structures ---*/

#define PKTXBSIZ 2048              /* size of P.D. real-mode xmit buffer   */
#define PKTRBSIZ 2048              /* size of P.D. real-mode recv buffer   */

struct slotinfo {                  /* Preallocated m structure slot info   */
     int sizpkt;                   /* m_new size parm, mult of (m_extra+1) */
     void *mplist;                 /* linked list of preallocated m's      */
     unsigned int nwant;           /* how many we want preallocated        */
     unsigned int nactual;         /* how many actually available in list  */
     unsigned int namin;           /* minimum nactual                      */
     unsigned long nused;          /* counter of packets used from slot    */
     unsigned long nskip;          /* skips to bigger-packet slots         */
};                                 /* slots must be ordered small -> big   */
extern
struct slotinfo slotinfo[];

/*--- Variables in GALPKTP.C ---*/

extern
int pkt_int;
extern
char pkt_errmsg[];
extern
short pkt_hiperf;
extern
short pkt_extend;
extern
int pkt_v100;                      /* Packet Driver version x 100 (or 0)   */
extern
int pkt_inited;                    /* Packet Driver vars initialized       */
extern
int pkt_iphandle;                  /* Packet Driver handle for Ethernet IP */
extern
int pkt_arphandle;                 /* Packet Driver handle for Ethernet ARP*/
extern
unsigned long pkt_dropheap;        /* count of incoming packets dropped due*/
                                   /* to insufficient heap space           */
extern
int (*pktd_incoming)(              /* incoming packet handler vector       */
     char *buffer,
     unsigned int nbytes);
extern
int numslots;                      /* number of preallocated slots defined */
extern
unsigned long pkt_rcalls;          /* count of packet receiver calls       */
extern
unsigned long pkt_rque;            /* count of packet receiver pkts queued */
extern
unsigned long pkt_rdrop;           /* count of packet receiver pkts dropped*/

/*--- Functions in GALPKTP.C ---*/

int                                /*   ret 1=ok, 0=error (see pkt_errmsg) */
pkt_init(                          /* Packet Driver initialization         */
u32 numskt);                       /*   max number of sockets expected     */
                                   /*   initialize pkt_class before calling*/

int                                /*   ret 1=ok, 0=error (see pkt_errmsg) */
pkt_vector(                        /* Check a packet driver interrupt vec  */
int intno);                        /*   software interrupt number          */

void
prot_pkt_xmitdone(void);           /* prot-mode notify, as_send_pkt done   */

void
prot_pkt_receiver(                 /* packet driver packet receiver        */
int mode,                          /*   0=buffer query, 1=copy notify      */
int handle,                        /*   from access_type call              */
int nbytes);                       /*   mode 0: size of packet             */

void
pkt_cycle(void);                   /* Packet Driver system-cycle processing*/

void
pkt_fin(void);                     /* Packet Driver finalization           */

/*--- Variables in GALPKTR.C ---*/

extern
char pkt_iptype[2],                /* IP packet type                       */
     *realp_pkt_iptype;            /* real-mode pointer to pkt_iptype      */
extern
char pkt_arptype[2],               /* ARP packet type                      */
     *realp_pkt_arptype;           /* real-mode pointer to pkt_arptype     */
extern
char pkt_rarptype[2],              /* RARP packet type                     */
     *realp_pkt_rarptype;          /* real-mode pointer to pkt_rarptype    */
extern
a48 pkt_eaddr,                     /* Packet Driver ethernet address       */
     *realp_pkt_eaddr;             /* real-mode pointer to pkt_eaddr       */
extern
u16 rcvr_cx;                       /* used by pkt_receiver()               */
extern
u32 rcvr_esdi;
extern
char pkt_xbuff[PKTXBSIZ],          /* Pkt real-mode transmit data buffer   */
     *realp_pkt_xbuff;             /* real-mode pointer to pkt_xbuff       */
extern
char pkt_rbuff[PKTRBSIZ],          /* Pkt real-mode receive data buffer    */
     *realp_pkt_rbuff;             /* real-mode pointer to pkt_rbuff       */
extern
int pkt_rbinuse;                   /* 1=pkt_rbuff[] is in use, 0=free      */
extern
struct pkt_sendiocb pkt_sendiocb,  /* Pkt real-mode send IOCB              */
     *realp_pkt_sendiocb;          /* real-mode pointer to pkt_sendiocb    */
extern
void (*realp_pkt_receiver)(void);  /* real-mode pointer to pkt_receiver()  */
extern
int in_pkt_receiver;               /* probe to detect pkt_receiver time    */
extern
int in_pkt_xmitdone;               /* probe to detect pkt_xmitdone time    */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __GALPKT_H
