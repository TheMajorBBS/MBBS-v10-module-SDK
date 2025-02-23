/////////////////////////////////////////////////////////////////////////////
//
//   TLCPAL.H
//
//   Copyright (c) 1997 Galacticomm, Inc.         All Rights Reserved
//
//   Teleconference Pals Header file
//
//                                              - Phil Henning 8/18/97
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __TLCPAL_H
#define __TLCPAL_H
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct pals {
     CHAR pszUserid[UIDSIZ];
     CHAR pszPal[TLCUIDSIZ];
     USHORT ltime;
     USHORT ldate;
     USHORT lelapsed;
     USHORT flags;
} PALDSK, *LPPALDSK;

// key 0 - multiseg
// store pals as userid/pal combo
// store logon info for everyone as PALTRAK/user combo

typedef struct palmem {
     CHAR pszPal[TLCUIDSIZ];
} PALMEM, *LPPALMEM;

#define PALFILE "GALTELP.DAT"
#define PALTRAK "!PAL"

const SHORT PAL_LOGON      =0;
const SHORT PAL_LOGOFF     =1;

const SHORT PAL_ALREADY    =1;
const SHORT PAL_ADDED      =2;
const SHORT PAL_TOOMANY    =3;

const USHORT PAL_FLAG_LON  =1;
const USHORT PAL_FLAG_LOF  =2;
const USHORT PAL_FLAG_LMSG =4;

#define GETPALPTR(x) ((LPPALMEM)(ptrblok(pmemreg,x)))

VOID palClear(INT unum);
VOID palSave(INT unum,GBOOL updateself=TRUE);
VOID palLoad(INT unum);
VOID palNotify(const CHAR* user, SHORT type);
VOID palWasUpdated(INT unum);
VOID palStatus(const CHAR* user=NULL);

extern GBOOL usepalt;
extern CHAR *pkey;
extern DFAFILE *dfaPal;
extern INT TLCEXP pmax;
extern USHORT *ppref;

extern GBOOL (*palvrfyhook)(const CHAR* user);
extern GBOOL (*palisonhook)(const CHAR* user);

VOID initpal();
#ifdef __cplusplus
};
#endif // __cplusplus
#endif // __TLCPAL_H


