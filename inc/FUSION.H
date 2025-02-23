/*
        FUSION.H

        Network Research Corporation
        FUSION Developer's Kit (FDK) for MS-DOS

        Application Program Interface Common Header File.



          DATE    REVISION  ENGINEER    DESCRIPTION

        07/08/92   3.4/00   D. Dalton   Ported to MS-DOS Build Environment.

        06/04/93   3.5/01   W. Hu       Removed AF_1 Definition.
                                        Changed AF_2 from 11 to 10.
                                        Changed AF_KDB from 9 to 8.
                                        Changed AF_RARP from 8 to 9.

        Copyright (C)  Network Research Corporation  1983-1992.
        ALL RIGHTS RESERVED WORLDWIDE.

        NO PART OF THIS SOFTWARE MAY BE DISCLOSED OR DISTRIBUTED
        IN ANY FORM OR BY ANY MEANS WITHOUT THE PRIOR WRITTEN CONSENT
        OF NETWORK RESEARCH CORPORATION.
*/

#if             defined( FUSION_H )

        #pragma         message( "> > >  FUSION.H Included Multiple Times!  < < <" )

#else   /* FUSION_H */

        #define         FUSION_H




/* Byte ordering w/i 16 and 32 values; L2R means left-to-right
 * is the order of increasing byte value (e.g. VAX, 808x, PDP-11);
 * comment out if your machine is right-to-left increasing (e.g. MC68000).
 */
        #define         L2R_16
        #define         L2R_32


/* MANIFEST CONSTANT DEFINITIONS */

        #define         DST_NONE                        0
        #define         DST_USA                         1


/* internal err/status values */
        extern  int  res_errno;

        #define         ERR                     (-1)
        #define         NET_ERR                 55

        #define         EWOULDBLOCK             (NET_ERR +   0)  /* 35 */
        #define         EINPROGRESS             (NET_ERR +   1)  /* 36 */
        #define         EALREADY                (NET_ERR +   2)  /* 37 */
        #define         ENOTSOCK                (NET_ERR +   3)  /* 38 */
        #define         EDESTADDRREQ            (NET_ERR +   4)  /* 39 */
        #define         EMSGSIZE                (NET_ERR +   5)  /* 40 */
        #define         EPROTOTYPE              (NET_ERR +   6)  /* 41 */
        #define         ENOPROTOOPT             (NET_ERR +   7)  /* 42 */
        #define         EPROTONOSUPPORT         (NET_ERR +   8)  /* 43 */
        #define         ESOCKTNOSUPPORT         (NET_ERR +   9)  /* 44 */
        #define         EOPNOTSUPP              (NET_ERR +  10)  /* 45 */
        #define         EAFNOSUPPORT            (NET_ERR +  11)  /* 46 */
        #define         EADDRINUSE              (NET_ERR +  12)  /* 47 */
        #define         EADDRNOTAVAIL           (NET_ERR +  13)  /* 48 */
        #define         ENETDOWN                (NET_ERR +  14)  /* 49 */
        #define         ENETUNREACH             (NET_ERR +  15)  /* 50 */
        #define         ENETRESET               (NET_ERR +  16)  /* 51 */
        #define         ECONNABORTED            (NET_ERR +  17)  /* 52 */
        #define         ECONNRESET              (NET_ERR +  18)  /* 53 */
        #define         ENOBUFS                 (NET_ERR +  19)  /* 54 */
        #define         EISCONN                 (NET_ERR +  20)  /* 55 */
        #define         ENOTCONN                (NET_ERR +  21)  /* 56 */
        #define         ESHUTDOWN               (NET_ERR +  22)  /* 57 */
        #define         ETIMEDOUT               (NET_ERR +  23)  /* 58 */
        #define         ECONNREFUSED            (NET_ERR +  24)  /* 59 */
        #define         EPFNOSUPPORT            (NET_ERR +  25)  /* 60 */
        #define         EHOSTDOWN               (NET_ERR +  26)  /* 61 */
        #define         EHOSTUNREACH            (NET_ERR +  27)  /* 62 */

        #define         ENOURGENTDATA           (NET_ERR + 100)
        #define         ENOOOBDATA              (NET_ERR + 101)


/* pseudo keywords */
        #define         boolean                 int
        #define         import                  extern
        #define         export
        #define         OK                              0
        #define         true                    1
        #define         false                   0
        #define         forever                 for(;;)
        #define         until(cond)             while(!(cond))
        #define         unless(cond)            if(!(cond))
        #define         ifnot(cond)             if(!(cond))

        #ifndef nil
                #define         nil                             (void *)0
        #endif


/* Synonyms */
#if     ( _MSC_VER >= 700 )
                #define         strasn                  _strdup
#else
                #define         strasn                  strdup
#endif


/*
 * Network function equivalents
 */
        #define         gethostbyaddr                   ghbyaddr
        #define         gethostbyname                   ghbyname
        #define         gethostent                      ghent
        #define         gethostname                     ghname
        #define         getservbyname                   gsbyname
        #define         getservbyport                   gsbyport
        #define         getservent                      gsent


        #define         BSD                             42
        #define         sockaddr_in                     in_sockaddr
        #define         index                           strchr
        #define         rindex                          strrchr


/* Diddle variable flags */

/* access information */
        #define         F_D_WRITE                       0x0001  /* allows write access */
        #define         F_D_RPRIVILEGED                 0x0002  /* privileged user read access only */
        #define         F_D_WPRIVILEGED                 0x0004  /* privileged user write access only */
        #define         F_D_SHARED                      0x0008  /* shared with intelligent nodes */
        #define         F_D_PREINIT                     0x0010  /* can only be written before init */

/* type information */
        #define         F_D_BOOLEAN                     0x0100
        #define         F_D_I16                         0x0200
        #define         F_D_I32                         0x0400
        #define         F_D_U16                         0x0800
        #define         F_D_U32                         0x1000
        #define         F_D_STRING                      0x2000
        #define         F_D_OTHER                       0x4000

/* diddle function return values */
        #define         DID_DO_DEFAULT                  -1              /* positive values are reserved to */
        #define         DID_DONE                        0               /* err values */

/* protocol identifiers */
        #define         INTRA_DGRAM                     0               /* intramachine datagram */
        #define         INTRA_STREAM                    1               /* intramachine byte stream */

/* special IP addresses */
        #define         INADDR_ANY              ((u32)0)

/*
 * nselect() definitions
 * synchronous (via nselect) or asynchronous (via nselect or notify)
 * notification values.
 */
        #define         READ_NOTIFY             ((u16)0x0001)   /* read data available */
        #define         WRITE_NOTIFY            ((u16)0x0002)   /* write data space available */
        #define         ACCEPT_NOTIFY           ((u16)0x0004)   /* connection request awaits */
        #define         CLOSE_NOTIFY            ((u16)0x0008)   /* close down completed */
        #define         CONNECT_NOTIFY          ((u16)0x0010)   /* connection completed */
        #define         EXCEPT_NOTIFY           ((u16)0x0020)   /* exception has occurred */
        #define         RSHUTDOWN_NOTIFY        ((u16)0x0040)   /* read direction shutdown by peer */
        #define         TIMEOUT_NOTIFY          ((u16)0x0080)   /* request has timed out */
        #define         WSHUTDOWN_NOTIFY        ((u16)0x0100)   /* write direction shutdown by peer */
        #define         URGENT_NOTIFY           ((u16)0x0200)   /* urgent data available */
        #define         OOB_NOTIFY              ((u16)0x0400)   /* out of bounds data */

        #define         ALL_NOTIFY              ((u16)0x07FF)   /* all of the above */

/* everything except read and write -- mainly for other mask in select() */
        #define         OTHER_NOTIFY            ~(READ_NOTIFY | WRITE_NOTIFY)


/* address families */
        #define         AF_UNSPEC                       0                       /* unspecified */
        #define         AF_INTRA                        1                       /* O/S-dependent path names */
        #define         AF_INET                         2                       /* ARPA Internet address */
        #define         AF_NS                           3                       /* Xerox Network Systems protocols */
        #define         AF_NBS                          4                       /* NBS protocols */
        #define         AF_CCITT                        5                       /* CCITT protocols, X.25 etc */
        #define         AF_SNA                          6                       /* IBM SNA */
        #define         AF_ARP                          7                       /* Address Resolution Protocol */
        #define         AF_KDB                          8                       /* Kernel DeBug Protocol */
        #define         AF_RARP                         9                       /* Reverse Address Resolution Protocol */
        #define         AF_2                            10                      /* customer expansion */


/* link layer address families */
        #define         AF_LL                           AF_2            /* last address family */
        #define         AF_PPP                          (AF_LL+1)       /* PPP */
        #define         AF_ETHER                        (AF_LL+2)       /* Raw Ethernet */
        #define         AF_CMAN                         (AF_LL+3)       /* Channel Manager */
        #define         AF_IMPLINK                      (AF_LL+4)       /* IMP "host at IMP" addresses */
        #define         AF_SLIP                         (AF_LL+5)       /* SLIP */
        #define         AF_DDN                          (AF_LL+6)       /* DDN X.25 */
        #define         AF_TRN                          (AF_LL+7)       /* IBM Token Ring               */
        #define         AF_L1                           (AF_LL+7)       /* if no Token Ring, cust expand */
        #define         AF_L2                           (AF_LL+8)       /* customer expansion           */
        #define         AF_L3                           (AF_LL+9)       /* customer expansion           */
        #define         AF_L4                           (AF_LL+10)      /* customer expansion           */


/* address family and link layer address family counts / macros */
        #define         MAX_AF                          AF_L4           /* last link layer address family */
        #define         MIN_LLAF                        AF_PPP          /* first link layer address family */
        #define         MAX_LLAF                        MAX_AF          /* last link layer address family */
        #define         AF_UNIX                         AF_INTRA        /* UNIX path names */


        #define         NAF                             (MAX_AF+1)                                                              /* number of AF's */
        #define         NLLAF                           (MAX_LLAF-MIN_LLAF+1)                                   /* number of link layer AF's */
        #define         af_ix(a)                        (a)     /* AF to index */
        #define         aflim(a)                        bound((a),(u16)0,(u16)MAX_AF)                   /* bound AF */
        #define         afok(a)                         ((u16)(a)<=(u16)MAX_AF)
        #define         llaf_ix(a)                      ((a)-(u16)MIN_LLAF)                                             /* link layer AF to index */
        #define         llaflim(a)                      bound((a),(u16)MIN_LLAF,(u16)MAX_LLAF)  /* bound link layer AF */
        #define         llafok(a)                       inbound((a),(u16)MIN_LLAF,(u16)MAX_LLAF)


/* socket types */
        #define         SOCK_STREAM                     1                       /* virtual circuit */
        #define         SOCK_DGRAM                      2                       /* datagram */
        #define         SOCK_RAW                        3                       /* raw socket */
        #define         SOCK_RDM                        4                       /* reliable-delivered message */
        #define         SOCK_SEQPACKET                  5                       /* sequenced packet */
        #define         SOCK_PACK_EX                    6                       /* packet exchange non Berkeley */


/* level number for get/setsopt to apply to socket itself */

/* IP protocol codes */
        #define         IP_IP                           0                       /* Internet Protocol (for get/setsopt only) */
        #define         IP_ICMP                         1                       /* Internet Control Message Protocol */
        #define         IP_GGP                          3                       /* Gateway-to-Gateway Protocol */
        #define         IP_TCP                          6                       /* Transmission Control Protocol */
        #define         IP_UDP                          17                      /* User Datagram Protocol */

        #define         SOL_SOCKET                      0xFFFF          /* for socket interface level options */

        #define         IPPROTO_ICMP                    IP_ICMP
        #define         IPPROTO_TCP                     IP_TCP
        #define         IPPROTO_UDP                     IP_UDP


/* socket options used with get/setsopt calls */
        #define         SO_DEBUG                        0x1                     /* turn on debugging */
        #define         SO_ACCEPTCONN                   0x2                     /* socket has had listen() */
        #define         SO_REUSEADDR                    0x4                     /* allow local address reuse */
        #define         SO_KEEPALIVE                    0x8                     /* keep connections alive */
        #define         SO_DONTROUTE                    0x10                    /* just use interface addresses */
        #define         SO_LINGER                       0x80                    /* linger on close if data is present */
        #define         SO_DONTLINGER                   (~SO_LINGER)

        #define         MAXOPTVALEN                     32                      /* max. size of socket option value */


/* values for IP level socket options */
        #define         IP_O_TOS                        1                       /* Type of service */
        #define         IP_O_FRAG                       2                       /* Fragmentation Control */
        #define         IP_O_MAXTTL                     3                       /* Maximum TTL value */
        #define         IP_O_MINTTL                     4                       /* Minimum TTL value */
        #define         IP_O_SECURE                     5                       /* security:compartment:handling:tcc */
        #define         IP_O_LSRR                       6                       /* loose source and record route */
        #define         IP_O_SSRR                       7                       /* strict source and record route */
        #define         IP_O_RR                         8                       /* record route */
        #define         IP_O_STREAM                     9                       /* stream identifier */
        #define         IP_O_TIME                       10                      /* Internet timestamp */

/* bit fields in iph_tos */
        #define         IP_PRECEDENCE                   0xE0            /* top 3 bits of 'iph_tos' */
        #define         IP_DELAY                        0x10            /* delay */
        #define         IP_THROUGHPUT                   0x08            /* throughput */
        #define         IP_RELIABLE                     0x04            /* reliability */


/* Precedence values (masked by IP_PRECEDENCE) */
        #define         IP_NC                           0xE0            /* Network Control */
        #define         IP_IC                           0xC0            /* Internetwork Control */
        #define         IP_CRITIC                       0xA0            /* CRITIC/ECP */
        #define         IP_FLSHO                        0x80            /* Flash Override */
        #define         IP_FLASH                        0x60            /* Flash */
        #define         IP_IMMED                        0x40            /* Immediate */
        #define         IP_PRIORITY                     0x20            /* Priority */
        #define         IP_ROUTINE                      0x00            /* Routine */


/* Values for ipos_security field of security option */
        #define         IPOS_UNCLASSIFIED               0x0000          /* Unclassified */
        #define         IPOS_CONFIDENTIAL               0xF135          /* Confidential */
        #define         IPOS_EFTO                       0x789A          /* EFTO */
        #define         IPOS_MMMM                       0xBC4D          /* MMMM */
        #define         IPOS_PROG                       0x5E26          /* PROG */
        #define         IPOS_RESTRICTED                 0xAF13          /* Restricted */
        #define         IPOS_SECRET                     0xD788          /* Secret */
        #define         IPOS_TOP_SECRET                 0x6BC5          /* Top Secret */
        #define         IPOS_R0                         0x35E2          /* Reserved for future use */
        #define         IPOS_R1                         0x9AF1          /* Reserved for future use */
        #define         IPOS_R2                         0x4D78          /* Reserved for future use */
        #define         IPOS_R3                         0x24BD          /* Reserved for future use */
        #define         IPOS_R4                         0x135E          /* Reserved for future use */
        #define         IPOS_R5                         0x89AF          /* Reserved for future use */
        #define         IPOS_R6                         0xC4D6          /* Reserved for future use */
        #define         IPOS_R7                         0xE26B          /* Reserved for future use */


/*
 * IP Socket Timestamp Option
 * Bits Defined in Internet Timestamp Option
 */
        #define         IPO_T_OVER                      0xF0            /* Overflow mask */
        #define         IPO_T_TYPE                      0x0F            /* Timestamp type mask */
        #define         IPO_T_TO                        0x00            /* Timestamps only */
        #define         IPO_T_IT                        0x01            /* Internet address/timestamp pairs */
        #define         IPO_T_PIT                       0x03            /* Prespecified internet addr/stamp pairs */


/* 4.2bsd send/recv standard flags */
        #define         MSG_OOB                         0x1                     /* process out of band information */
        #define         MSG_PEEK                        0x2                     /* peek at incoming message */
        #define         MSG_DONTROUTE                   0x4                     /* send without using routing tables */


/* 4.2bsd standard flag mask */
        #define         MSG_FLAGS                       (MSG_OOB|MSG_PEEK|MSG_DONTROUTE)


/* NRC value added */
        #define         MSG_BLOCKING                    0x8000          /* override any nonblocking state */
        #define         MSG_NONBLOCKING                 0x4000          /* override any blocking state */
        #define         MSG_FDBROADCAST                 0x2000          /* want full duplex broadcasts */
        #define         MSG_TRUNCATE                    0x1000          /* truncate received packet */
        #define         MSG_URGENT                      0x0800          /* urgent data */
        #define         MSG_MASK                        (MSG_FLAGS|MSG_BLOCKING|MSG_NONBLOCKING|MSG_FDBROADCAST|MSG_TRUNCATE|MSG_URGENT)


/* Definitions for socket I/O Control operations */
        #ifndef ENIOCBASE
                #define         ENIOCBASE               ((u16)('e' << 8))
        #endif

        #ifndef INPIOCBASE
                #define         INPIOCBASE              ((u16)('i' << 8))
        #endif

        #ifndef SDIOCBASE
                #define         SDIOCBASE               ((u16)('o' << 8))
        #endif

        #ifndef SDIOCSTK
                #define         SDIOCSTK                SDIOCBASE                       /* give pre-sockdrv stack */
        #endif

        #ifndef SOIOCBASE
                #define         SOIOCBASE               ((u16)('s' << 8))
        #endif

        #ifndef SOIOCATMARK
                #define         SOIOCATMARK             (SOIOCBASE-3)           /* for MSG_OOB */
        #endif

        #ifndef SOIOCGNTTY
                #define         SOIOCGNTTY              (SOIOCBASE-20)          /* for get ntty */
                #define         SOIOCSNTTY              (SOIOCBASE-10)          /* for set ntty rlog/xns */
                #define         SOIOCSTEL               (SOIOCBASE-11)          /* for set ntty telnet/tcp */
                #define         SOIOCDTEL               (SOIOCBASE-12)          /* for daemon telnet/tcp */
                #define         SOIOCSRLOG              (SOIOCBASE-13)          /* for set ntty rlogin/tcp */
                #define         SOIOCDRLOG              (SOIOCBASE-14)          /* for daemon rlogin/tcp */
                #define         SOIOCRNTTY              (SOIOCBASE-15)          /* to reset attached tty */
        #endif

        #define         SOIOCNTATTACH                   (SOIOCBASE-4)   /* for net tty hookup */
        #define         SOIOCNTSETOUT                   (SOIOCBASE-5)   /* screen output redirect */
        #define         SOIOCURG                        (SOIOCBASE-6)   /* for MSG_OOB too */


        #define         INPIOCDOWNLOAD                  (INPIOCBASE + 0)
        #define         INPIOCEXECUTE                   (INPIOCBASE + 1)
        #define         INPIOCINITIALIZE                (INPIOCBASE + 2)
        #define         INPIOCPROBE                     (INPIOCBASE + 3)
        #define         INPIOCDIDDLE                    (INPIOCBASE + 4)


/* Values for raw ethernet ioctls.  These select the action inside
 * the link layer ioctl routine.
 */
        #define         ENIOCEND                        (ENIOCBASE+10)
        #define         ENIOCNORMAL                     ENIOCBASE       /* accept broadcast and specific */
        #define         ENIOCPROMISC                    (ENIOCBASE+1)   /* accept all undamaged packets */
        #define         ENIOCALL                        (ENIOCBASE+2)   /* accept ALL packets */
        #define         ENIOCRESET                      (ENIOCBASE+3)
        #define         ENIOCWHATRU                     (ENIOCBASE+4)   /* return device name from ndevsw */




/* FUNCTION MACRO DEFINITIONS */

/* structure assignment macro */
        #define         stass(d,s)              memcpy(&(d), &(s), sizeof(s))

/* Macros to do various flips */
        #define         _FLIP16(C)              (u16)((((C)>>8)&0xFF)|(((C)<<8)&0xFF00))

        #define         _FLIP32(C)              ((u32)(((((u32)C)>>24)&0x000000FF) | \
                                                                       ((((u32)C)>> 8)&0x0000FF00) | \
                                                                           ((((u32)C)<< 8)&0x00FF0000) | \
                                                                           ((((u32)C)<<24)&0xFF000000L)))


/* define the host/net order transformations specified in byteorder(3N)
 * as macros of the standard FUSION flip'ers
 */
        #define         htonl                   _flip32
        #define         htons                   _flip16
        #define         ntohl                   _flip32
        #define         ntohs                   _flip16


/* Conversions between axx, ixx and uxx types. */
        #define         U16(a)                  _flip16( *(u16 *)((a).a2))      /* a16 to u16 */
        #define         I16(a)                  (i16)(U16(a))                           /* a16 to i16 */

        #define         U32(a)                  _flip32( *(u32 *)((a).a4))      /* a32 to u32 */
        #define         I32(a)                  (i32)(U32(a))                           /* a32 to i32 */


/* axx Comparisons */
        #define         A16A(a,op,b)    (U16(a) op U16(b))
        #define         A32A(a,op,b)    (U32(a) op U32(b))


/* axx Operations
 * Note: Assignments are valid for the A16U, A16C, A32U and A32C macros,
 * Note: operators sensitive to bit position are not valid (such as +=).
 * Note: operators insensitive to bit position are valid (such as |=).
 */
        #define         A16U(a,op,u)    ( *(u16 *)(a).a2 op _flip16((u16)(u)))  /* a16 op u16 */
        #define         A16C(a,op,C)    ( *(u16 *)(a).a2 op _FLIP16(C))                 /* a16 op u16 */

        #define         A32U(a,op,u)    ( *(u32 *)(a).a4 op _flip32((u32)(u)))  /* a32 op u32 */
        #define         A32C(a,op,C)    ( *(u32 *)(a).a4 op _FLIP32(C))                 /* a32 op u32 */


/* bit field macros, bit clear, set, true, false */
        #define         bC1(v,f)                ((v) &= ~(f))
        #define         bS1(v,f)                ((v) |= (f))
        #define         bT1(v,f)                ((v) & (f))
        #define         bF1(v,f)                (((v) & (f)) == 0)
        #define         bC2(v,f1,f2)            bC1(v, ((f1)|(f2)))
        #define         bC3(v,f1,f2,f3)         bC1(v, ((f1)|(f2)|(f3)))
        #define         bS2(v,f1,f2)            bS1(v, ((f1)|(f2)))
        #define         bS3(v,f1,f2,f3)         bS1(v, ((f1)|(f2)|(f3)))
        #define         bT2(v,f1,f2)            (((v) & ((f1)|(f2))) == ((f1)|(f2)))
        #define         bT3(v,f1,f2,f3)         (((v) & ((f1)|(f2)|(f3))) == ((f1)|(f2)|(f3)))
        #define         bF2(v,f1,f2)            bF1(v, ((f1)|(f2)))
        #define         bF3(v,f1,f2,f3)         bF1(v, ((f1)|(f2)|(f3)))


/* Some handy macros */
        #ifndef abs
                #define         abs(i)                   ((i < 0) ? -i : i)
        #endif

        #ifndef max
                #define         max(x,y)                ((x) > (y) ? (x) : (y))
        #endif

        #ifndef min
                #define         min(x,y)                ((x) < (y) ? (x) : (y))
        #endif

        #ifndef bound
                #define         bound(v,min,max)        ((v)<(min) ? (min) : (v)<(max) ? (v) : (max))
        #endif

        #ifndef inbound
                #define         inbound(v,min,max)      ((min)<=(v) && (v)<=(max))
        #endif


/* Macros for dealing with Class A/B/C network numbers.
 * High 3 bits of uppermost byte indicates how to interpret
 * the remainder of the 32-bit Internet address.  The macros
 * may be used in time critical sections of code, while
 * subroutine versions also exist for use in other places.
 */
        #define         INCLSA       0X80000000
        #define         INCLSA_NET   0XFF000000     /* 8 bits of net # */
        #define         INCLSA_LNA   0X00FFFFFF
        #define         INCLSB       0X40000000
        #define         INCLSB_NET   0XFFFF0000     /* 16 bits of net # */
        #define         INCLSB_LNA   0X0000FFFF
        #define         INCLSC_NET   0XFFFFFF00     /* 24 bits of net # */
        #define         INCLSC_LNA   0X000000FF

        #define         IN_NETOF(in)      (((in).s_addr & INCLSA) == 0  \
                                                                ?   (in).s_addr & INCLSA_NET    \
                                                                :  ((in).s_addr & INCLSB) == 0  \
                                                                  ? (in).s_addr & INCLSB_NET    \
                                                                  : (in).s_addr & INCLSC_NET)

        #define         IN_LNAOF(in)      (((in).s_addr & INCLSA) == 0  \
                                                                ?   (in).s_addr & INCLSA_LNA    \
                                                                :  ((in).s_addr & INCLSB) == 0  \
                                                                  ? (in).s_addr & INCLSB_LNA    \
                                                                  : (in).s_addr & INCLSC_LNA)




/* DATA STRUCTURE/TYPE DEFINITIONS */

/* standard FUSION types */
        typedef boolean ( *pfb_t)();
        typedef int             ( *pfi_t)();
        typedef long    ( *pfl_t)();
        typedef pfi_t   ( *pfpfi_t)();
        typedef pfpfi_t ( *st)();                       /* ptr. to a state function */

/* Berkeley Types */
        #define         u_short                 u16
        #define         u_long                  u32
        #define         u_char                  u8
        #define         u_int                   u32
        typedef struct  fd_set { int fds_bits[1]; } fd_set;


        #define         local                   static  /* global 'static' storage class macro */

/* for compiler's that can't deal with intra segment pointers */
        #define         pflocal                 local


/* unsigned char's */
        #define         u8                      unsigned char

        #define         noshint                 extern int
        #define         noshchr                 extern char


/* nonambiguous primitive types */
        #define         i16                     short
        #define         u16                     unsigned short
        #define         i32                     long
        #define         u32                     unsigned long
        #define         INT_SHIFT               1


        typedef struct  a16
                        {       /* a 16-bit byte-ordered structure */
                                char    a2[2];
                        }       a16;

        typedef struct  a32
                        {       /* a 32-bit byte-ordered structure */
                                char    a4[4];
                        }       a32;

        typedef struct  a48
                        {       /* a 48-bit byte-ordered structure */
                                char    a6[6];
                        }       a48;


/* types used in Fusion code for non-4.2bsd systems */
                        struct  timeval
                        {
                                long    tv_sec;         /* seconds */
                                long    tv_usec;        /* and microseconds */
                        };

                        struct  timezone
                        {
                                int             tz_minuteswest;         /* minutes west of Greenwich */
                                int             tz_dsttime;                     /* type of dst correction */
                        };


/* Address structures for all supported families */
        typedef struct  ipa
                        {       /* DARPA Internet Protocol Address */
                                a16     ip_port;                /* protocol port number */
                                a32     ip_nethost;             /* network/host address */
                        }       ipa;


/* Typed socket addresses for all supported address families */
        typedef struct  sockaddr
                        {       /* Generic socket address */
                                short   sa_type;
                                char    sa_data[22];
                        }       saddr;

        typedef struct  lsockaddr
                        {       /* Intramachine (local) socket address */
                                short   sa_type;        /* AF_INTRA */
                                char    sa_name[2];     /* null-terminated string (can be longer) */
                        }       lsaddr;

/* Congruent to the nasty stuff in "in.h" */
        typedef struct  isockaddr
                        {       /* DARPA Internet socket address */
                                short   sa_type;        /* AF_INET */
                                ipa             sa_ipa;
                        }       isaddr;

        #define         isa_port                        sa_ipa.ip_port
        #define         isa_nethost                     sa_ipa.ip_nethost

        typedef struct  eaddr
                        {       /* Raw Ethernet socket address */
                                short   sa_type;        /* AF_ETHER */
                                a48             sa_ena;
                        }       esaddr;

        typedef struct  tsaddr
                        {       /* Raw Token Ring socket address */
                                short   sa_type;        /* AF_TRN */
                                a48             sa_tra;
                        }       tsaddr;

        typedef union   sa_u
                        {       /* union of all types of socket addresses */
                                saddr   au_saddr;       /* generic */
                                lsaddr  au_lsaddr;      /* AF_INTRA: local to this machine */
                                isaddr  au_isaddr;      /* AF_INET: DARPA Internet */
                                esaddr  au_esaddr;      /* AF_ETHER: Ethernet address */
                                tsaddr  au_tsaddr;      /* AF_TRN: Token Ring address */
                        }       sa_u;


/* The following converts a (saddr) to an (isaddr *) */
        #define         isaddrp(saddr)          ((isaddr *)&(saddr))


/* Socket option value structure */
        typedef struct  socketopt
                        {
                                int              so_optlen;             /* length of optdata area */
                                char    *so_optdata;    /* pointer to data */
                        }       socketopt;


/* Host database entry retrieval structure */
        typedef struct  hostent
                        {
                                char     *h_name;               /* official name of host */
                                char    **h_aliases;            /* alias list */
                                u16       h_addrtype;           /* host address type */
                                u16       h_length;             /* length of address */
                                char     *h_addr;               /* address */
                        }       hostent_t;


/* Service database entry retrieval structure */
        typedef struct  servent
                        {
                                char     *s_name;               /* official service name */
                                char    **s_aliases;            /* alias list */
                                u16       s_port;               /* port # */
                                char     *s_proto;              /* protocol to use */
                        }       servent_t;


/* Internet address
 *      This definition contains obsolete fields for backward
 *      compatibility with older code.  Subnetting renders the
 *      arbitrary division into fields somewhat confusing.  New
 *      code should restrict itself to the s_addr field.
 */
                        struct  in_addr
                        {
                                union
                                {
                                        struct { u8 s_b1,s_b2,s_b3,s_b4; }      S_un_b;
                                        struct { u16 s_w1,s_w2; }                       S_un_w;
                                        u32                                                                     S_addr;
                                }       S_un;
                        };

        #define         s_addr                  S_un.S_addr             /* Should be used for all code */
        #define         s_host                  S_un.S_un_b.s_b2        /* Obsolete: host on imp */
        #define         s_net                   S_un.S_un_b.s_b1        /* Obsolete: network */
        #define         s_imp                   S_un.S_un_w.s_w2        /* Obsolete: imp */
        #define         s_impno                 S_un.S_un_b.s_b4        /* Obsolete: imp # */
        #define         s_lh                    S_un.S_un_b.s_b3        /* Obsolete: logical host */


/* Socket address, internet style. */

                        struct  in_sockaddr
                        {
                                i16                             sin_family;
                                u16                             sin_port;
                                struct in_addr  sin_addr;
                                char                    sin_zero[8];
                        };


/* nselect() definitions */
        #define         se_dev                  se_2reserved

        typedef struct  sel
                        {
                                u16     se_inflags;             /* input/request flags */
                                u16     se_outflags;            /* output/reply flags */
                                i16     se_fd;                  /* holds process local file id */
                                i16     se_1reserved;           /* reserved for internal use */
                                u32     se_user;                /* user-definable value */
                                u32     se_2reserved;           /* reserved for internal use */
                        }       sel;


/* IP socket security option */
        typedef struct
                        {
                                a16     ipos_security;      /* security */
                                a16     ipos_compartments;  /* compartments */
                                a16     ipos_handling;      /* handling restrictions */
                                a32     ipos_tcc;           /* transmission control code */
                        }       ipos_t;


/* IP socket timestamp option */
        typedef struct  ipot_t
                        {
                                a16     ipot_overflow_type;     /* overflow/flag */
                                a32     ipot_timestamps[9];     /* timestamp/address slots (max 9) */
                        }       ipot_t;





/* FUNCTION PROTOTYPES */
        #ifndef NO_FUSION_PROTOTYPES

                #if             defined( __cplusplus )
                        extern  "C"
                        {
                #endif  /* __cplusplus */


        int                      accept( int fd, saddr *addrp, int *addrlen );
        char                    *advance( void );
        char                    *adr2str( saddr *addrp, char *buf );
        char                    *adr2name( saddr *addrp, char *buf );
        char                    *af2str( int af, char *buf );
        u16                      af_code( char *name );
        void                     af_db_load( void );
        void                     af_db_unload( void );
        char                    *af_name( u16 af );
        int                      all_tcp_closed( void );
        char                    *arg_peek( void );

        char                    *basename( char *path );
        int                      bind( int fd, saddr *name, int name_len );
        int                      blocking( int fd );

        int                      cabort( int sd );
        int                      caccept( int fd, saddr *addrp, int *addrlen);
        int                      connect( int fd, saddr *addrp, int addrlen );
        int                      con_read( char *cp );

        int                      doze( int cnt );

        void                     esent( void );

        void                     fatal( char *fmt, ... );
        void                     fatal_err( char *msg );

        u16                      _flip16( u16 u );
        u32                      _flip32( u32 u );

        int                      fdiddle( char *name );
        int                      ldiddle( char *name );
        int                      rdiddle( char *name, char *dest, int len );
        int                      wdiddle( char *name, char *data, int len );
        int                      fldiddle( char *name );
        void                     frdiddle( char *name, char *buf, int size );
        void                     fwdiddle( char *name, char *buf, int size );

        int                      fns_initialize( void );
        char                    *fullpath( void );

        char                    *get_opt( void );
        int                      getpeername( int s, saddr *name, int *namelen );
        int                      getsockname( int s, saddr *name, int *namelen );
        int                      getsockopt( int sd, int level, int optname, char *optval, int *optlen );
        char                    *get_time( void );

        int                      ghname( char *name, int namelen );
        int                      shname( char *name, int namelen );

        struct hostent          *ghbyaddr( char *adddr, int len, int type );
        struct hostent          *ghbyname( char *name, int address_family );

        struct servent          *gsbyname( char *name, char *proto );
        struct servent          *gsbyport( int port, char *proto );
        struct servent          *gsent( void );

        u32                      inet_addr( const char * );
        char *                   inet_ntoa( struct in_addr in );
        char                    *ipa2str( ipa *ipap, char *dst );
        int                      ip_bind( int s, int pref_sock );

        int                      listen( int fd, int backlog );

        int                      nget_int( char *name );
        char                    *nget_str( char *name );
        saddr                   *name2adr( char *mach_name, saddr *addrp, u16 address_family );
        int                      nonblocking( int fd );
        void                     nperror( char *msg );
        char                    *nserror( void );

        char                   **nrc_init( int *argcp, char **argv, char **envp );
        char                   **nrc_nginit( int *argcp, char **argv, char **envp );

        int                      nselect( sel *selp, int cnt, u32 *waitp, pfi_t pfi, u32 arg, int *errp );

        int                      pioctl( int fd, int cmnd, char *addr, int len, u16 flags );

        int                      recv( int fd, char *buf, int len, int flags );
        int                      recvfrom( int fd, char *buf, int buf_len, int flags, saddr *from, int *fromlen );
        int                      recvh( int fd, char *buf, int buf_len, int flags, char *hdr, int *hdrlen );
        int                      recvht( int fd, char *buf, int buf_len, int flags, char *hdr, int *hdrlen, u32 *timep );
        int                      reject( int fd );

        char                    *s2str( int s, char *buf );
        int                      select( int nfd, int *rfp, int *wfp, int *ofp, struct timeval *wait );
        int                      send( int fd, char *buf, int len, int flags );
        int                      sendh( int fd, char *buf, int buf_len, int flags, char *hdr, int hdrlen );
        int                      sendto( int fd, char *buf, int buf_len, int flags, saddr *to, int tolen );
        int                      set_time( u8 *time_str );
        int                      setsockopt( int sd, int level, int optname, char *optval, int optlen );
        void                     show_time( void );
        int                      shutdown( int fd, int direction );
        int                      socket( int af, int type, int protocol );
        int                      socket_index( int fd );
        int                      socketpair( int af, int type, int protocol, int *sv );
        int                      so_nread( int fd, u32 *bytep );
        int                      so_nwrite( int fd, u32 *bytep );
        int                      so_nrqmax( int fd, int newmax );
        boolean                  ssent( boolean stayopen );
        sa_u                    *str2adr( char *str, sa_u *itssap, u16 af );
        u16                      str2af( unsigned char **strp );
        ipa                     *str2ipa( char *str, ipa *ipap );

        int                      tcp_open( int pref_sock, ipa *_address );
        char                    *tokenize( char *line, char *delim );

        void                     u8_dump( u8 *u8p, int bcnt );
        void                     u16_dump( u16 *u16p, int bcnt );

        int                      udp_open( int pref_sock );
        int                      urename( char *old_name, char *new_name );
        void                     usage( char *fmt, ... );

        void                     warn( char *fmt, ... );


                #if             defined(  __cplusplus  )
                        }
                #endif  /* __cplusplus */

        #endif  /* NO_FUSION_PROTOTYPES */

#endif  /* FUSION_H */

