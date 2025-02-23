/***************************************************************************
 *                                                                         *
 *   TLC.H                                                                 *
 *                                                                         *
 *   Copyright (c) 1997 Galacticomm, Inc.         All Rights Reserved      *
 *                                                                         *
 *   Teleconference Mainline Declarations                                  *
 *                                                                         *
 *                                               - Phil Henning 5/14/97    *
 *                                                                         *
 ***************************************************************************/

#ifndef __TLC_H
#define __TLC_H

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#include "tlcchan.h"
#include "tlcuser.h"
#include "GCOMM.H"

#ifdef GCWINNT
#   ifdef __BUILDTELE
#       define TELEEXP           EXPORT
#       define TELEEXPV(x)       EXPORT_VARIABLE(x)
#       define TELEEXPF(x, y)    EXPORT_FUNCTION(x, y)
#    else
#       define TELEEXP           IMPORT
#       define TELEEXPV(x)       IMPORT_VARIABLE(x)
#       define TELEEXPF(x, y)    IMPORT_FUNCTION(x, y)
#    endif
#else
#       define TELEEXP
#       define TELEEXPV
#       define TELEEXPF
#endif // GCWINNT


#define USERFILE    "GALTELU3.DAT"
#define EEMNOT      "Entrance/Exit Messages"
#define UNREFERENCED(X) ((VOID)X)

typedef struct banrfil {
    CHAR* name;
    struct banrfil* next;
} BANRFIL, *LPBANRFIL;

#define XTOOTH 0x0001
#define RSTX2M 0x0002
#define TYPING 0x0004

typedef struct chatinfo {
    INT chatch;
    USHORT switchcount;
    CHAR lastchannel[CHAN_MAX_SIZE];
    INT retstt;
    INT retsub;
    INT retrat;
    SHORT flags;
    LONG chatflags;
} CHATINFO, *LPCHATINFO;

typedef struct tlcusredt : public tlcusrdsk {
    LONG m_iCredits;
    INT  m_usrnum;
} SYSUSREDT, *LPSYSUSREDT;


const SHORT WRKBUFSIZ           =10000;

/* substates */
const INT TLC_STT_INTLC         =-2;
const INT TLC_CHATTING          =-3;


#ifdef __BUILDTELE
extern DFAFILE* dfaChan;
extern DFAFILE* dfaTlcUser;
extern LPCHATINFO aachat;
extern SYSUSREDT tlcsysedt;
extern struct module tlcmod;
extern CHAR etlpmt;
extern CHAR intdirchr[];
extern SHORT* teltimes;
extern GBOOL* msgchanged;
extern CHAR dftchan[CHAN_MAX_SIZE];
extern CHAR * mainchan;
extern GBOOL tlcinp(VOID);
#endif // __BUILDTELE

/* EXPORTS */

TELEEXPV(HMCVFILE) msgTlc;
TELEEXPV(VOID*) tlcwrk;
TELEEXPV(CHAR) dirchr;
TELEEXPV(INT) tinpsz;
TELEEXPV(SHORT) n2fgt;
TELEEXPV(SHORT) n2inv;
TELEEXPV(SHORT) n2ign;
TELEEXPV(CHAR*) pszTicker;
TELEEXPV(CHAR*) pszTickerNoAnsi;
TELEEXPV(INT) iTickerTime;
TELEEXPV(LPBANRFIL) banrfiles;
TELEEXPV(LPCHATINFO) aachat;
TELEEXPV(INT) banrval;

extern INT GetTeleState(VOID);

VOID init__galtele();
TELEEXP VOID outtele(INT unum);

#ifdef SUPPORTREMOVED //AHTML  and C/S Support removed
/* TLCAH.CPP    */
#ifdef GCWINNT
extern INT TLCEXP iAHTrans;

VOID initactiveh(VOID);
VOID initActiveHLite(VOID);
VOID initahpag(VOID);
#endif // GCWINNT
#endif

/* TLCFCHN.CPP  */
VOID initForumChannels();
VOID dwnForumChannels();

#define ANSISIZ                              10
#define MAXANSI                              14

/* gender-based color stuff */
extern UINT iMale;
extern UINT iFemale;
extern CHAR colors[MAXANSI][ANSISIZ];
#define SEXIDX(s) ((s) == 'M' ? iMale : iFemale)

/*
NOT USED IN CODE.... FOR REFERENCE ONLY

enum {
        COLOR_RED=1,   COLOR_BLUE,    COLOR_GREEN,   COLOR_YELLOW,
        COLOR_MAGENTA, COLOR_CYAN,    COLOR_WHITE,   COLOR_BRED,
        COLOR_BBLUE,   COLOR_BGREEN,  COLOR_BYELLOW, COLOR_BMAGENTA,
        COLOR_BCYAN,   COLOR_BWHITE
};
*/

#ifdef __cplusplus
};
#endif //__cplusplus

#endif // __TLC_H
