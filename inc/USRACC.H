/***************************************************************************
 *                                                                         *
 *   USRACC.H                                                              *
 *                                                                         *
 *   Copyright (c) 1987-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   This is the user account/billing header file.                         *
 *                                                                         *
 *                                            - T. Stryker 6/24/86         *
 *                                                                         *
 ***************************************************************************/

#ifndef __USRACC_H
#define __USRACC_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "ustructs.h"

WGSEXPV(struct usracc*) usaptr;/* user accting block pointer for usrnum    */
WGSEXPV(struct usracc*) othuap;/* gen purp other-user accting data ptr     */
WGSEXPV(struct usracc)  acctmp; /* temporary user account storage area      */

struct keyrec {               /* key (or keyring) structure                */
     CHAR userid[UIDSIZ];     /*   User-ID (or keyring name)               */
     CHAR keys[1];            /*   variable length list of key names       */
};

struct uidxrf {                    /* user-id cross reference structure    */
     CHAR xrfstg[XRFSIZ+1];        /*   cross reference string             */
     CHAR userid[UIDSIZ];          /*   user-id for this cross reference   */
#ifdef GCV2
     CHAR spare[6];                /*   former spare space                 */
#endif // GCV2
};

WGSEXPV(struct uidxrf) uidxrf;

WGSEXPV(INT) numcls;          /* total number of classes in system         */
WGSEXPV(USHORT) dtrack;       /* days tracked so far (for statistic avgs)  */

//struct WGSEXP clstab* clshead;/* head record for class table             */
//struct WGSEXP clstab* clsptr; /* general ptr to class table entry        */
WGSEXPV (struct clstab*) clshead;/* head record for class table             */
WGSEXPV (struct clstab*) clsptr; /* general ptr to class table entry        */

                              /* csbump() return values for immediate bump */
#define BMPDEL -1             /*   user account deleted due to bad class   */
#define BMPAOK  0             /*   user account OK: no immediate bump      */
#define BMPTIM  1             /*   out of time for today                   */
#define BMPLNV  2             /*   user not validated to logon yet         */
#define BMPSNV  3             /*   user not validated to logon after signup*/
#define BMPOTH  4             /*   app-defined error, message in prfbuf    */

WGSEXPV(DFAFILE*) accbb;      /* user account database file ptr             */
WGSEXPV(DFAFILE*) clsbb;      /* class database file ptr                    */

                              /*-- options for decevy() and (*decusr)() ---*/
WGSEXPV(INT) decusn;          /* user number                               */
WGSEXPV(struct user*) decusp; /* user online information (MAJORBBS.H)      */
WGSEXPV(struct usracc*) decuap;    /* user account information (USRACC.H)      */
WGSEXPV(LONG) deccst;         /* cost of online time since last (*decusr)()*/
WGSEXPF(VOID,decusr)(VOID);   /* decevy() service vector                   */

/* ACCOUNT.C 03/04/92 11.19.18 */
WGSEXP VOID iniacc(VOID);
WGSEXP struct usracc* uacoff(INT unum);
WGSEXP INT crtclass(struct acclass *cptr);
WGSEXP struct clstab *fndcls(const CHAR *clsname);
WGSEXP VOID swtcls(struct usracc* uacc,GBOOL makprm,const CHAR *clsnam,INT dest,INT days);
WGSEXP INT namacls(CHAR *clsname);
WGSEXP LONG tfcchg(LONG nbytes,LONG credpk);
WGSEXP INT dedcrd(LONG amt,GBOOL asmuch);
WGSEXP INT rdedcrd(LONG amt,GBOOL asmuch);
WGSEXP INT odedcrd(INT unum,LONG amt,GBOOL real,GBOOL asmuch);
WGSEXP INT ndedcrd(const CHAR *uid,LONG amt,GBOOL real,GBOOL asmuch);
WGSEXP INT gdedcrd(const CHAR *uid,LONG amt,GBOOL real,GBOOL asmuch);
WGSEXP INT ldedcrd(struct usracc* uptr,LONG amt,GBOOL real,GBOOL asmuch);
WGSEXP LONG hdedcrd(struct usracc* uptr,LONG amt,GBOOL real,GBOOL asmuch);
WGSEXP INT tstcrd(LONG amt);
WGSEXP INT rtstcrd(LONG amt);
WGSEXP INT otstcrd(INT unum,LONG amt,GBOOL real);
WGSEXP INT ntstcrd(const CHAR *uid,LONG amt,GBOOL real);
WGSEXP INT gtstcrd(const CHAR *uid,LONG amt,GBOOL real);
WGSEXP INT ltstcrd(const struct usracc* uptr,LONG amt,GBOOL real);
WGSEXP VOID dltcls(struct clstab *tabptr);
WGSEXP INT addcrd(CHAR *keyuid,const CHAR *tckstg,GBOOL real);
WGSEXP INT crdusr(CHAR *keyuid,const CHAR *tckstg,GBOOL real,GBOOL affall);
WGSEXP INT saycrd(const CHAR *tckstg,GBOOL real);
WGSEXP VOID cpykey(CHAR *dest,const CHAR *src,INT len);
WGSEXP VOID decevy(VOID);
WGSEXP INT declog(VOID);
WGSEXP INT decsup(VOID);
WGSEXP INT dectdy(VOID);
WGSEXP INT deccal(VOID);
WGSEXP VOID dec15s(VOID);
WGSEXP VOID deccrd(LONG surdsc);
WGSEXP VOID chkliu(VOID);
WGSEXP VOID savvbl(VOID);
WGSEXP INT imbump(GBOOL logon);
WGSEXP INT csbump(GBOOL logon);
WGSEXP INT wtwait(INT lomin,INT himin);
WGSEXP INT nliniu(VOID);
WGSEXP VOID updacc(VOID);
WGSEXP VOID updaccu(struct usracc* puac);
WGSEXP INT accmcu(VOID);
WGSEXP VOID accacct(const struct usracc* accptr,INT plusor);
WGSEXP INT delacct(const CHAR *userid);
WGSEXP INT kiluid(const CHAR *userid);
WGSEXP VOID howbuy(VOID);
WGSEXP VOID clsacc(VOID);

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __USRACC_H                           */
