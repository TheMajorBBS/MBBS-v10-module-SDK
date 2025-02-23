/***************************************************************************
 *                                                                         *
 *   BRKTHU.H                                                              *
 *                                                                         *
 *   Copyright (c) 1986-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   This is the header file prototyping all of the GSBL routines.         *
 *                                                                         *
 *                                            - T. Stryker 2/12/92         *
 *                                                                         *
 ***************************************************************************/

#ifndef __BRKTHU_H
#define __BRKTHU_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT
#   ifdef __BUILDGSBL
#       define EXPGSBL          EXPORT           
#       define EXPGSBLV(x)      EXPORT_VARIABLE(x)
#       define EXPGSBLF(x,y)    EXPORT_FUNCTION(x, y)
#   else
#       define EXPGSBL          IMPORT
#       define EXPGSBLV(x)      IMPORT_VARIABLE(x)
#       define EXPGSBLF(x,y)    IMPORT_FUNCTION(x, y)
#   endif // __BUILDGSBL
#else
#   define EXPGSBL
#	define EXPGSBLV
#	define EXPGSBLF
#endif // GCWINNT

#include "datstm.h"

#define RING   1              /* btusts() return for ringing/lost carrier  */
#define CMDOK  2              /* btusts() return for command completed ok  */
#define CRSTG  3              /* btusts() return for CR-term'd string avail*/
#define INBLK  4              /* btusts() return for count-trg input avail */
#define OUTMT  5              /* btusts() return for output buffer empty   */
#define OBFCLR 6              /* btusts() return for output buffer cleared */
#define ABOREQ 7              /* btusts() return for abort output requested*/
#define LOST2C 11             /* btusts() return for 2400 baud lost-carrier*/
#define CMN2OK 12             /* btusts() return for 2400 baud cmd complete*/
#define CMN2NG 13             /* uart/hayes cmd byte not executable        */
#define LOST25 21             /* btusts() return for X.25 lost-carrier     */
#define CM25OK 22             /* btusts() return for X.25 cmd complete     */
#define RCVX29 24             /* btusts() return for X.29 string received  */
#define SPXTRM 31             /* btusts() for SPX terminate by other side  */
#define IPXPSE 32             /* btusts() for IPX/SPX pause complete       */
#define SPXINC 34             /* btusts() for SPX incoming call complete   */
#define SPXOUT 35             /* btusts() for SPX outgoing call complete   */
#define SPXTDN 36             /* btusts() for SPX termination complete     */
#define IPXRER 37             /* btusts() for IPX recv error (chan group)  */
#define IPXUNK 38             /* btusts() for IPX unknown packet (chan grp)*/
#define SPXWDG 39             /* btusts() for SPX watchdog error, etc      */
#define INAPP 'I'             /* Inappropriate status (fm ^H cmd if 300bd) */
                              /* status codes 200-249 are app-specific     */
                              /* status codes 250-255 are buffer overflow  */

#define X25CLO     0x500      /* btux29() return code for window-full error*/

#define SDFANY  0             /* GSBL btusdf() argument for XECOM/UART hdw */
#define SDFX25  4             /* GSBL btusdf() argument for X.25 hardware  */
#define SDFIPXD 5             /* GSBL btusdf() argument for IPX Direct hdw */
#define SDFIPXV 6             /* GSBL btusdf() argument for IPX Virtual hdw*/
#define SDFSPX  7             /* GSBL btusdf() argument for SPX hardware   */
#define SDFGCDI 8             /* GSBL btusdf() argument for GCDI channels  */

                         /* bturep()/btuset() "stid" parameter values      */
#define PARITY -9        /* parity                                         */
#define DATABT -8        /* data bits                                      */
#define STOPBT -7        /* stop bits                                      */
#define RSVD01 -6        /* reserved                                       */
#define CHARIN -5        /* character interrupt routine (from btuchi())    */
#define PAGDIV -4        /* page divider string pointer (from btuxnf())    */
#define PAUSCH -3        /* handle pause character routine (from btuhpk()) */
#define BAUDRT -2        /* baud rate (from btubbr())                      */
#define RECNFG -1        /* reconfiguration notify routine                 */
#define CNTCHR 0         /* character count                                */
#define CNTPAK 1         /* packet count                                   */
#define CNTOVR 2         /* input overrun count                            */
#define CNTPTY 3         /* input parity errors                            */
#define CNTFMG 4         /* input framing errors                           */

#define X25ERR -13       /* btusdf() return code -- no GSBL/X25 linked     */
#define LANERR -14       /* btusdf() return code -- LAN access not avail   */
#define MEMERR -15       /* btuitz()/btusdf() return code -- out of memory */

                         /* parity, data bits and stop bits settings       */
#define PARNON 0         /* no parity                                      */
#define PARODD 1         /* odd parity                                     */
#define PAREVN 2         /* even parity                                    */
#define DABSVN 2         /* 7 data bits                                    */
#define DABEGT 3         /* 8 data bits                                    */
#define STBONE 0         /* 1 stop bit                                     */
#define STBTWO 2         /* 2 stop bits                                    */

                              /* cdi command modes used by btupcc()        */
#define CDIQUE 1              /* cdi que, but don't process, commands      */
#define CDIQAP 2              /* cdi que and process commands              */

#ifdef GCWINNT
#define ECHBSZ 512                 /* size of echo buffer                  */
#else
#define ECHBSZ 256                 /* size of echo buffer                  */
#endif // GCWINNT

EXPGSBLV(CHAR) btuver[];           /* GSBL version code                    */

EXPGSBLV(SHORT) ictact;            /* after btuict() or btuica():# byte avl*/

EXPGSBLV(INT) btusrs;              /* # users supported under this license */
EXPGSBLV(INT) btudtr;              /* 1=disable DTR-dropping during reset  */
EXPGSBLV(INT) btux25;              /* flag indicating X.25 support in GSBL */
EXPGSBLV(INT) x25ign;              /* # of received packets ignored by GSBL*/
EXPGSBLV(INT) x25udt;              /* set to 1 to capture User Data Field  */
EXPGSBLV(INT) lanecb;              /* # of listen-ECBs per LAN channel     */
EXPGSBLV(INT) lansop;              /* socket actually opened by btusdf()   */
EXPGSBLV(INT) lansca;              /* SPX connections available            */
EXPGSBLV(INT) btuicx;              /* 'in cdi transmit' flag               */

static CHAR cdixfn;                /* flag to save "sti" in GCDI output sink*/
                                   /* (in CS -- must create DS alias to write)*/

EXPGSBLV(INT) btulan;              /* Flags from the GSBL/LAN:             */
#define BTLIPXD  0x0001            /*    bit 0: IPX Direct supported       */
#define BTLIPXV  0x0002            /*    bit 1: IPX Virtual supported      */
#define BTLSPX   0x0004            /*    bit 2: SPX circuits supported     */
#define BTLI7A   0x0100            /*    bit 8: IPX driver is loaded       */
#define BTLSPXL  0x0200            /*    bit 9: SPX is loaded              */

EXPGSBLV(CHAR) bturno[];           /* registration # of this copy of GSBL  */
EXPGSBLV(CHAR) lanrev[2];          /* SPX revision number                  */

EXPGSBL INT btusiz(INT nchan,INT isiz,INT osiz);
EXPGSBL LONG btulsz(INT nchan,INT isiz,INT osiz);
EXPGSBL INT btuitz(VOID *region);
EXPGSBL INT btuitm(VOID *region);
EXPGSBL INT btudef(INT schan,INT sport,INT n);
EXPGSBL INT btusdf(INT schan,INT nchan,INT chtype,...);
EXPGSBL INT btux29(INT chan,INT nbyt,const CHAR *data);
EXPGSBL LONG btuset(INT chan,INT stid,LONG newval);
EXPGSBL LONG bturep(INT chan,INT stid);
EXPGSBL INT btuudf(INT schan,INT n);
EXPGSBL INT btumxs(UINT bdrate);
EXPGSBL INT bturti(INT n,INT (*rtirou)(VOID));
EXPGSBL INT btupfl(VOID (*pflrou)(INT type,UINT off,UINT sel));
EXPGSBLV(LONG FAR *) ppflreal;
EXPGSBLV(LONG) pflplap;
EXPGSBLV(LONG) pflmys3;
EXPGSBLV(LONG) pflgsbl;
EXPGSBLV(LONG) pflrng3;
EXPGSBLV(CHAR) pfn;
EXPGSBL INT btubsz(INT chan,INT isiz,INT osiz);
EXPGSBL INT btusts(INT chan);
EXPGSBL INT btucmd(INT chan,const CHAR *cmdstg);
EXPGSBL INT btubrt(INT chan,UINT bdrate);
EXPGSBL INT btubbr(INT chan,LONG bdrate);
EXPGSBL INT btuxmt(INT chan,CHAR *datstg);
EXPGSBL INT btuscn(VOID);
EXPGSBL INT btuinp(INT chan,CHAR *rdbptr);
EXPGSBL VOID btuxlt(CHAR oldchr,CHAR newchr);
EXPGSBL INT btupmt(INT chan,CHAR pmchar);
EXPGSBL INT btubse(INT chan,CHAR bschar);
EXPGSBL INT btutrm(INT chan,CHAR crchar);
EXPGSBL INT btuchi(INT chan,CHAR FAR (*rouadr)(INT chan,INT c));
EXPGSBL INT btuche(INT chan,INT onoff);
EXPGSBL INT btulfd(INT chan,CHAR lfchar);
EXPGSBL INT btutsw(INT chan,INT width);
EXPGSBL INT btumil(INT chan,INT maxinl);
EXPGSBL INT btuscr(INT chan,CHAR softcr);
EXPGSBL INT btuhcr(INT chan,CHAR hardcr);
EXPGSBL INT btuech(INT chan,INT onoff);
EXPGSBL INT btuxnf(INT chan,INT xon,INT xoff,...);
EXPGSBL INT btuhwh(INT chan,INT inpcut);
EXPGSBL INT btutru(INT chan,CHAR trunch);
EXPGSBL INT btuerp(INT chan,INT onoff);
EXPGSBL INT btumon(INT chan);
EXPGSBL INT btumds(VOID);
EXPGSBL VOID btumks(CHAR kyschr);
EXPGSBL INT btumon2(INT chan);
EXPGSBL INT btumds2(VOID);
EXPGSBL VOID btumks2(CHAR kyschr);
EXPGSBL INT btuinj(INT chan,INT status);
EXPGSBL INT btuoes(INT chan,INT onoff);
EXPGSBL INT btuoba(INT chan);
EXPGSBL INT btueba(INT chan);
EXPGSBL INT btuibw(INT chan);
EXPGSBL INT btuxct(INT chan,INT nbyt,const CHAR *datstg);
EXPGSBL INT btutrg(INT chan,INT nbyt);
EXPGSBL INT btuict(INT chan,CHAR *rdbptr);
EXPGSBL INT btuica(INT chan,CHAR *rdbptr,INT max);
EXPGSBL INT btuffo(INT chan,INT onoff);
EXPGSBL INT btulok(INT chan,INT onoff);
EXPGSBL INT btuclo(INT chan);
EXPGSBL INT btucli(INT chan);
EXPGSBL INT btuclc(INT chan);
EXPGSBL INT btucls(INT chan);
EXPGSBL INT bturst(INT chan);
EXPGSBL INT btutrs(INT chan,INT onoff);
EXPGSBL INT btupbc(INT chan,CHAR pausch);
EXPGSBL INT btucpc(INT chan,CHAR clrpch);
EXPGSBL INT btuhpk(INT chan,INT FAR (*hpkrou)(INT chan,CHAR c));
EXPGSBL INT btuolk(INT chan,INT onoff);
EXPGSBL INT btuirp(INT comno);
EXPGSBL INT btuhit(INT comint);
EXPGSBL INT btuxmn(INT chan,CHAR *datstg);
EXPGSBL INT btuhdr(INT sapchn,INT bufsiz,VOID *buffer);
EXPGSBL struct datstm FAR *btucdi(INT chan,struct datstm FAR *outsnk);
EXPGSBL INT btupcc(INT chan,INT mode);
EXPGSBL INT btuopl(INT chan);
EXPGSBL VOID btuend(VOID);
EXPGSBL VOID chiinp(INT chan,CHAR c);
EXPGSBL VOID chiout(INT chan,CHAR c);
EXPGSBL VOID chious(INT chan,const CHAR *stg);
EXPGSBL VOID chiinj(INT chan,INT s);
EXPGSBL INT btuusp(INT chan,INT onoff);
EXPGSBL ULONG hrtval(VOID);

EXPGSBLV(INT) _DebuggerHookData;

#ifdef GCV2
EXPGSBLV(volatile USHORT) ticker;
#define btuTicker() (ticker)
#else
EXPGSBL USHORT btuTicker(VOID);
#endif // GCV2

#if defined(GCWINNT)
EXPGSBL VOID locchn(INT chno);
#endif                             /* GCWINNT                              */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __BRKTHU_H                           */
