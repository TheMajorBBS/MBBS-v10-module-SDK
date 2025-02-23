/* CMAN.h -- Channel Manager API */
#ifndef _CMAN_H_
#define _CMAN_H_

#ifdef KERNEL
#include <slip.h>
#include <vjcomp.h>
#include <ppp.h>
#endif /* KERNEL */

#define MAX_CHANNELS            254 /* we will allow 0 (this network)!!! */
#define MAX_SLIP_OUTBUF         (SL_MAX_DATA*2+2) /*MTU*2(for escapes)+ 2 for BEGIN and END*/
#define CMAN_ADDRLEN            max(SL_ADDRLEN, PPP_ADDRLEN)
#define CMAN_MAX_DATA           max(SL_MAX_DATA,LCP_DEF_MTU)
#define CMAN_HDR_SIZE           PPP_HDR_SIZE
#define INVALID_CHANNEL         0x7F00
#define ISVALID_CHANNEL(chn)    (0 <= (chn) && (chn) < cman_numchn)
#define MPORTFACTOR             2  /* factor, surplus magic ports          */
#define MOPENWAIT               60 /* secs til open entry becomes stale    */
#define MCLOSEWAIT              1  /* secs til closed entry assumed closed */
#define MUDPWAIT                0  /* secs til UDP entry used, last resort */
#define STANDINIP "1.1.1.1"        /* for when userips is FALSE            */

typedef struct cman_tbs {
        int     cman_flags;        /* see CMO_XXX masks below              */
        int     errplst;           /* protocol last counted towards errprot*/
        void    * cman_slppp_ptr;  /* slip/ppp specific structure          */
        u32     proxip;            /* fake IP user thinks he's using       */
        u32     errspur;           /* spurious TCP packet (not SYN)        */
        u32     errtoom;           /* too many TCP sessions                */
        u32     errprot;           /* non TCP/UDP packets thrown out       */
        u32     errfrag;           /* packets rejected due to framentation */
        u32     lclbytes;          /* bytes exchanged with local server    */
        u32     rembytes;          /* bytes exchanged with remote hosts    */
        u32     lclpakts;          /* packets exchanged with local server  */
        u32     rempakts;          /* packets exchanged with remote hosts  */
        char    spare[32];         /* spare space for exapansion           */
} cman_tbs;

import  cman_tbs * cman_tbp;       /* channel manager table of chan info   */

#ifdef KERNEL
typedef struct cm_sl_s {
        slip_s          cmsl_slip;
        slcompress      cmsl_comp;
        char            cmsl_outbuf[MAX_SLIP_OUTBUF];
} cm_sl_s;

typedef struct cm_ppp_s {
        pppsession      cmppp_session;
        char            cmppp_outbuf[LCP_MAX_SIZE];
} cm_ppp_s;
#endif /* KERNEL */

typedef struct cman_proxport {     /* proxy port information               */
        u16     fakeport;          /* TCP/UDP port user thinks he's using  */
        u16     realport;          /* TCP/UDP port on inet (aka magic port)*/
        u32     lasttime;          /* "time" sample of past packet passed  */
        u8      flags;             /* see PXPXXX flag masks below          */
} cman_proxport;
                                   /* fakeport and realport above are in   */
                                   /* HOST byte order, 0=entry not used yet*/

#define PXPUOPN 0x01               /* connection open, user's perspective  */
#define PXPROPN 0x02               /* connection open, remote perspective  */
#define PXPUDP  0x04               /* port used only for UDP (datagram)    */

extern
u32 *ip_of_chan;         /* table of IP addresses indexed 0 to numchn-1  */
                         /* (network byte order)                         */
#define CHNOIP  0UL      /* channel not using an IP address (quiescent)  */

extern
int *chan_of_ip;         /* table of channels indexed 0 to num_ip-1      */
#define IPNOCH (-1)      /* IP address not in use by any channel         */

extern
int cman_numchn;
extern
int maxpxp;                        /* max number of proxy ports/chan       */
extern
unsigned int num_ip;     /* number of IP addresses used by CMAN channels */
extern
u32 base_ip;             /* IP address of first CMAN channel (host order)*/

extern
int *idxofmport;                   /* array mapping magic real port number */
                                   /* to channel and index within channel  */
                                   /* (index is magic real port - minmport;*/
                                   /* value is chan*maxpxp+index)          */
                                   /* (unused entries are MPAVAIL)         */
#define MPAVAIL (-1)               /* means magic port number is available */

extern
cman_proxport *proxport;           /* array of magic port information      */
                                   /* per channel, per port within chan    */
                                   /* (array index is chn*maxpxp+idx where */
                                   /* chn is 0..cman_numchn-1 and idx is   */
                                   /* 0..maxpxp-1)                         */

extern
u16 nummport;                      /* number of magic port values          */
extern
u16 minmport;                      /* minimum magic port value (host ord)  */
extern
u16 maxmport;                      /* maximum magic port value (host ord)  */
extern
u32 main_ip;                       /* main IP address of host (eg ethernet)*/

int                                /* returns 0=ok, else=error number      */
init_cman(                         /* Init Channel Manager                 */
int numchn,                        /*   total number of channels           */
unsigned int *cbsize,              /*   channel-specific buffer size (max) */
u32 ipaddr,                        /*   1st IP addr used (network order)   */
unsigned int numip);               /*   number of possible addresses used  */
                                   /*   (call after all ll_config()'s)     */

int                                /*   returns 0=ok, else=error number    */
open_cman(                         /* Open a Channel Manager session       */
int chn,                           /*   channel index (0 to numchn-1)      */
int ll_af,                         /*   AF_SLIP or AF_PPP                  */
int flags,                         /*   CMO_CSLIP, CMO_PROXY               */
char *cbuff,                       /*   channel-specific buffer for session*/
                                   /*   (app frees after close_cman() call)*/
u32 ipaddr);                       /*   IP address to be used by this chan */
                                   /*   (network byte order)               */

/* mask stored in CMAN channel table (and/or passed in cman_open()) */
                                   /*--- masks for open_cman()'s flags ----*/
#define CMO_CSLIP       0x0001     /* CSLIP (when ll_af == AF_SLIP only)   */

#define CMO_SLIP        0x0002     /* SLIP uncompressed */

#define CMO_ANY_SLIP    (CMO_CSLIP | CMO_SLIP)

#define CMO_PPP         0x0004     /* PPP */

                                   /* mask internal to CMAN */
#define CMO_OPEN        0x0010     /* Set after successfull open_cman */
                                   /* Reset after close_cman() */

#define CMO_PROXY       0x0020     /* request Proxy SLIP/CSLIP */


void
cycle_cman(void);                  /* Channel Manager Cycle                */
                                   /*   (Application calls repeatedly.)    */

int                                /*   returns actual bytes processed     */
input_cman(                        /* Channel Manager input received       */
int chn,                           /*   channel index (0 to numchn-1)      */
char *bytes,                       /*   bytes (packet boundary not guar.)  */
int nbytes);                       /*   number of bytes                    */
                                   /*   (Called by application as incoming */
                                   /*   bytes are available.  Application  */
                                   /*   may discard if short count.)       */

extern int                         /*   returns actual sent (0 or nbytes)  */
(*output_cman)(                    /* Channel Manager output vector        */
int chn,                           /*   channel index (0 to numchn-1)      */
char *packet,                      /*   whole packet(s) only               */
unsigned int nbytes);              /*   number of bytes in packet(s)       */
                                   /*   (This vector points to a stub in   */
                                   /*   Channel Manager.  Application must */
                                   /*   intercept.  Channel Manager will   */
                                   /*   call when there are packet(s) to be*/
                                   /*   sent.  Application would ideally   */
                                   /*   send all or nothing.  Channel      */
                                   /*   Manager may have no choice but to  */
                                   /*   discard packet(s) on short count.) */

extern void
(*event_cman)(                     /* Channel Manager event reporting      */
int chn,                           /*   channel index (0 to numchn-1)      */
int evcode,                        /*   event code, see CME_XXXX below     */
int parm);                         /*   event-specific info, if any        */
                                   /*   (Points to dummy routine in Channel*/
                                   /*   Manager.  Called by Channel Manager*/
                                   /*   to indicate asynchrounous event.   */
                                   /*   Intercepted by application as req.)*/

                                   /*--- (*event_cman)() event codes ------*/
#define CME_TERM  0                /* Terminate connection (e.g. PPP)      */
#define CME_ABORT 1                /* Abort connection prematurely (eg PPP)*/


void
close_cman(                        /* Close a Channel Manager session      */
int chn);                          /*   channel index (0 to numchn-1)      */

int                                /*   ret channel&index, or -1=not found */
pxpfnd(                            /* find an entry for a fake port number */
int chn,                           /*   channel, 0 to cman_numchn-1        */
u16 fport);                        /*   fake port from user (host byte ord)*/
                                   /*   automatically updates entry's time */

int                                /*   ret channel&index, or -1=none avail*/
pxpnew(                            /* enlist a closed or stale open entry  */
int chn);                          /*   channel, 0 to cman_numchn-1        */
                                   /*   (if returns not -1, sets realport &*/
                                   /*   lasttime fields and PXP*OPN flags, */
                                   /*   caller should set fakeport field   */
                                   /*   and optionally PXPUDP flag)        */

u16                                /*   inclusive range minmport-maxmport  */
newmport(void);                    /* get a new magic port (host byte ord) */

void
pxpclose(                          /* close all proxy ports for a channel  */
int chn);

u16                                /*   returns 1's complement sum         */
sum1c(                             /* one's complement addition            */
u16 a,                             /*   of one 16-bit quantity             */
u16 b);                            /*   to another                         */

u16                                /*   returns normalized value (never -0)*/
normal1c(                          /* one's complement normalization       */
u16 a);                            /*   of a 16-bit quantity               */
                                   /*   (changes -0 to +0)                 */

#ifdef KERNEL
int
cman_init(                        /* cman init from Fusion so_initialize */
netdev  * ndp);                   /* cman ndevsw entry point */

int
cman_updown(                    /* cman updown called from Fusion ll_config */
netdev  * ndp,
u16     flags);             /* updown flags: F_N_ONLINE => UP, else => Down */

int
cman_ioctl(
netdev  * ndp,                  /* ndp device pointer */
int     cmnd,
char    FHP * addr,
int     len);

int
cman_start(
m       FHP * mp,               /* message pointer */
void    * unsused);             /* for PPP/CMAN compatibility */

st
cman_scomm(
m       FHP * mp);              /* message pointer */

#endif /* KERNEL */
#endif /*_CMAN_H_ */
