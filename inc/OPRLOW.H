/***************************************************************************
 *                                                                         *
 *   OPRLOW.H                                                              *
 *                                                                         *
 *   Copyright (c) 1992-1997 Galacticomm, Inc.      All Rights Reserved.   *
 *                                                                         *
 *   Low level operator console for dealing with virtual screens,          *
 *   screen saving, dynamic registration, etc.                             *
 *                                                                         *
 *                                            - Robert A. Rose 02/05/92    *
 *                                                                         *
 ***************************************************************************/

#ifndef __OPRLOW_H
#define __OPRLOW_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct scrnid {
     CHAR *scnnam;            /* screen filename                           */
     INT scnlen;              /* length of screen (4000 for full screen)   */
     INT selssc;              /* select scan code (from main screen)       */
                              /* ala 'Keyboard Accelerator'                */
     VOID (*byerou)(VOID);    /* screen going away routine                 */
     VOID (*updrou)(VOID);    /* screen repaint routine                    */
     UINT (*keyrou)(UINT scan);/* key handler routine                      */
     VOID (*occrou)(VOID);    /* occasional update routine                 */
     INT secs;                /* seconds between occasional updates        */
     INT secs2go;             /* seconds to go before next update          */
     VOID (*disrou)(VOID);    /* called every cycle when displayed         */
     INT cx,cy;               /* current cursor position on screen         */
     INT curmove;             /* does cursor move?                         */
     INT scroll;              /* should screen scroll?                     */
     INT x1,y1,x2,y2;         /* scrolling for window (default)            */
     CHAR *buffer;            /* perm. save buffer                         */
     CHAR *location;          /* current location of screen                */
};

WGSEXPV(INT) mainhdl;         /* handle of screen on main (0=none)         */
WGSEXPV(INT) auxhdl;          /* handle of screen on aux (0=none)          */
WGSEXPV(INT) actvhdl;         /* what handle is active currently?          */
WGSEXPV(INT) backhdl;         /* handle for background (on actvscns < 4000)*/
WGSEXPV(INT) sec2mov;         /* seconds left before moving saver display  */
WGSEXPV(INT) sec2sav;         /* configured seconds to save screens 0=never*/
WGSEXPV(INT) cur2sav;         /* how much longer before we save screens    */
                              /* cur2sav=0 means screens are saved         */
WGSEXPV(INT) occgran;         /* granularity of occrou cycling             */
WGSEXPV(INT) maxscns;         /* maximum number of screens to allow        */
WGSEXPV(INT) regscns;         /* number of registered screens              */
WGSEXPV(INT) dfltmscn;        /* default main screen to show               */
WGSEXPV(INT) dfltascn;        /* default aux screen to show                */
WGSEXPV(INT) skcipg;          /* force all keys to background handler      */

WGSEXPV(struct scrnid*) scnids;
WGSEXPV(struct scrnid*) scncur;

#define LGNSIZ      47        /* maximum size of channel legends           */

struct uidisp {               /* users screen display data                 */
     CHAR sing;               /*    single character legend                */
     CHAR attrib;             /*    attribute for legend/labels            */
     CHAR labl[LGNSIZ];       /*    full legend for channel                */
};

WGSEXPV(struct uidisp*) uidarr;

#define saveworld(x) movmem(&curatr,x,sizeof(struct curatr))
#define restworld(x) movmem(x,&curatr,sizeof(struct curatr))

/* OPRLOW API calls:                                                       */

WGSEXP CHAR *                             /* rtns pointer to screen buffer        */
actvscn(                      /* make scnhdl the active screen for printfs */
INT scnhdl);                       /* screen handle (returned by regscn)   */

WGSEXP CHAR *                             /* rtns pointer to screen buffer        */
actvscnsp(                    /* make scnhdl the active screen for printfs */
INT scnhdl,                        /* screen handle (returned by regscn)   */
INT x1, INT y1,                    /* bounds and scroll (ovrids scnid sets)*/
INT x2, INT y2,
INT scn);

WGSEXP VOID
updbckgnd(VOID);              /* update visible piece of the background    */

WGSEXP VOID
scngoaway(                    /* screen wants to hide itself               */
INT scnhdl);                       /* screen handle                        */

WGSEXP INT                                /* returns handle number                */
regscn(                       /* register a screen for display             */
struct scrnid *newscn);            /* screen id block                      */

WGSEXP VOID
memswap(                      /* swap two memory regions (without buffer)  */
CHAR *source,                      /* source buffer                        */
CHAR *dest,                        /* destination buffer                   */
INT length);                       /* length in bytes to move              */

WGSEXP VOID
hidecurs(                     /* hide cursor on a screen                   */
INT scnhdl);

WGSEXP VOID
cls(                          /* Clear a screen to blanks                  */
CHAR *buf,                         /* screen buffer to clear               */
INT atr);                          /* attribute to clear to                */

/* OPRLOW System calls:                                                    */
WGSEXP VOID
inilopr(                      /* initialize OPRLOW code                    */
INT mxscn,                         /* maximum number of screens to allow   */
INT auxena);                       /* aux crt support enabled              */

WGSEXP VOID
endlopr(VOID);                     /* shutdown OPRLOW code                 */

WGSEXP UINT
keyhit(                       /* Process a key from the console            */
UINT scan);                        /* scan code of key hit                 */

WGSEXP VOID
conupd(VOID);                      /* Constant update (for displayed screens)*/

/* OPRLOW Internal calls:                                                  */

WGSEXP VOID
occhdl(VOID);                      /* Occasional update routine            */

WGSEXP VOID
shobox(                       /* Message that walks during screen saving   */
INT w,                             /* Which screen coords to use (main,aux)*/
INT sho);                          /* 1=show boxe, 0=remove box            */

WGSEXP VOID
unsavscns(VOID);                   /* unsave screens that have been saved  */

WGSEXP VOID
savscns(VOID);                     /* save screens to prevent burn-in      */

WGSEXP CHAR *
dbytes(                       /* convert # into xxx, xxxKb, xxxMb          */
ULONG bytes);

WGSEXP BOOL IsWow64();
WGSEXP unsigned __int64 getTotalDiskSpace(void);
WGSEXP unsigned __int64 getFreeDiskSpace(void);
WGSEXP unsigned __int64 getTotalMemory(void);
WGSEXP unsigned __int64 getFreeMemory(void);
WGSEXP char* formatBytes(unsigned __int64 bytes);
WGSEXP char* getCPUInfo(void);
WGSEXP BOOL Is64BitWindows();
WGSEXP char* getOSVersion(VOID);


#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __OPRLOW_H                           */
