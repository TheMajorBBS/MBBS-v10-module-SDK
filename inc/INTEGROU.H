/***************************************************************************
 *                                                                         *
 *   INTEGROU.H                                                            *
 *                                                                         *
 *   Copyright (c) 1992-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   These routines perform the dynamic integration functions built into   *
 *   MenuTree.                                                             *
 *                                                                         *
 *     VOID iniint(VOID);          initialize module integrator biz        *
 *     CHAR **avlmods(GBOOL csedit);return an array of ptrs to module names*
 *     VOID clrefs(VOID);          clear all module reference counts       *
 *     VOID incref(CHAR *modnam);  increment count of references to modnam *
 *     VOID decref(CHAR *modnam);  decrement count of references to modnam *
 *     VOID finint(VOID);          write WGSERV.CFG, WGSMDF.REF,           *
 *                                      WGSINT.REF, and ACTMDFS.LST        *
 *     VOID reqchk(VOID);          just the "required" check from finint() *
 *                                 1=ok, 0=missing required modules        *
 *                                                                         *
 *   It is recommended to call iniint() prior to opening WGSMENU.DAT, and  *
 *   to call finint() after closing WGSMENU.DAT.  The rest of the time,    *
 *   avlmods() provides a list of the available module names.  incref()    *
 *   should be called each time an additional reference is made to one     *
 *   of these modules, and decref() should be called each time an existing *
 *   reference is deleted.  This way, when the number of references to a   *
 *   module drops to zero, it will be removed from WGSERV.CFG.  reqchk()   *
 *   need not be called unless not calling finint() and WGSREQ.FLG exists. *
 *   The reqchk() routine provides a quick check of the "required:"        *
 *   relations between MDF files and pops up a warning window if           *
 *   "required" mods are not present.                                      *
 *                                                                         *
 *   General plan of attack: if MDF files or WGSMENU.DAT have changed      *
 *   since the last time finint() was called, reconstruct WGSERV.CFG.      *
 *   Do this by reading in all MDF data, checking for duplicate module     *
 *   names (and resolving any conflicts on the spot through pop-up menus   *
 *   and such), then making sure that our module reference counts can      *
 *   be relied upon (which consists of making sure that MDF.REF matches    *
 *   the latest version of WGSMENU.DAT and using its reference counts if   *
 *   so; otherwise re-tallying them from scratch).  Upon exit, eliminate   *
 *   duplicate DLL's and write Btrieve data and DLL list to WGSERV.CFG.    *
 *   WGSINT.REF is a record of all the .MDF date/time/size info present    *
 *   when WGSERV.CFG was written, and ACTMDFS.LST is a list of the         *
 *   currently active .MDFs (those not "replaced"), for use by WGSFNDO     *
 *   and CNF.                                                              *
 *                                                                         *
 *   Note: clrefs() should only be called when the caller is about to      *
 *   make a complete pass through all menu pages, calling incref() as      *
 *   appropriate to reconstruct the complete reference count array.        *
 *                                                                         *
 *                                            - T. Stryker 2/12/92         *
 *                                                                         *
 ***************************************************************************/

#ifndef __INTEGROU_H
#define __INTEGROU_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define DNMSIZ  (24+1)        /* developer name size                       */
#define DELIMS ", \t;"        /* valid delimiters for DLL & EXE lists      */
#define MAXDLL 5              /* max # of DLL's per MDF                    */
#define MAXMDF 5              /* max # of MDF's in required/replaces/etc.  */
#define ALLMDF "Everyone"     /* keyword for "all MDF's"                   */
#define MMMODN "Menuing System" /* Main Menu's module name (no MDF for it) */
#define FUNCSZ  (64)          /* size of initialization function(init__...)*/
#define OBJSIZ  (256)         /* path+filename of object file list         */

WGSEXPV(INT) nmdfs;           /* number of modules found in .MDF files     */
WGSEXPV(INT) nmods;           /* number of modules referenced altogether   */
WGSEXPV(CHAR**) modnmv;       /* list of module names from .MDF files      */

#if ! defined(_MSC_VER)
extern
#endif
struct moddat {               /* module data                               */
     CHAR modnam[MNMSIZ];     /* module name in English                    */
     CHAR mdfnam[FNSIZE];     /* module definition (.MDF) file name/csappid*/
     CHAR devnam[DNMSIZ];     /* developer name                            */
     CHAR instal[FNSIZE];     /* install-utility name (if exists)          */
     CHAR usrtxt[FNEXSZ];     /* addition to online user manual (if exists)*/
     CHAR dllnam[MAXDLL][FNSIZE];  /* DLL's constituting this module       */
     CHAR mdfreq[MAXMDF][FNSIZE];  /* MDF's required to run this module    */
     CHAR mdfrep[MAXMDF][FNSIZE];  /* MDF's replaced by this module        */
     CHAR ineed[MAXMDF][FNSIZE];   /* mods that this one needs to be init'd*/
     CHAR needme[MAXMDF][FNSIZE];  /* mods that need this one to be init'd */
#ifdef UNIX
     CHAR ifnnam[MAXDLL][FUNCSZ];  /* Initialization functions             */
     CHAR objlst[MAXDLL][FUNCSZ];  /* Object File List                     */
#endif // UNIX
     CHAR defico[FNSIZE];     /* default icon name if any (.ICO assumed)   */
     INT flags;               /* fun facts to know and tell                */
     INT btrfls;              /* number of Btrieve files this module needs */
     INT nrefs;               /* no. of references in MenuTree to this guy */
     struct lingo *lp;        /* language information, if any              */
     CHAR *msgs;              /* dynamic list of .MSG file names           */
     char *stfunc;            /* startup app permission function name      */
};

WGSEXPV(struct moddat*) moddat;/* dynam alloc'd array of module data       */

                              /* moddat "flags" bits:                      */
#define UNCOND  0x01          /* unconditionally include DLL's at run time */
#define INTERN  0x02          /* "internal" module; don't show in MenuTree */
#define REQUIR  0x04          /* this MDF's DLL's are required by somebody */
#define HASCLX  0x08          /* this MDF has a client-side EXE            */
#define ISINRF  0x10          /* this MDF is already recorded in WGSINT.REF*/
#define CSONLY  0x20          /* this MDF is "internal" to ASCII/ANSI      */
#define CSTART  0x40          /* this MDF is a C/S "startup app"           */
#define HADIND  0x80          /* this MDF had an "I need" line in it       */

#if ! defined (_MSC_VER)
extern
#endif
struct refstf {               /* reference-count (WGSMDF.REF) file header  */
     INT nmods;               /* number of moddat structs after the ffblk  */
     struct ffblk fb;         /* time/date etc. of BBSMENU.DAT this tracks */
};

WGSEXPV(struct refstf) refstf;

VOID iniint(VOID);            /* initialize module integrator biz          */
CHAR **avlmods(GBOOL csedit); /* return an array of ptrs to module names   */
VOID clrefs(VOID);            /* clear all module reference counts         */
VOID incref(CHAR *modnam);    /* increment count of references to modnam   */
VOID decref(CHAR *modnam);    /* decrement count of references to modnam   */
VOID finint(VOID);            /* write WGSERV.CFG, WGSMDF.REF, WGSINT.REF, */
                              /*        and BBSMDFS.LST                    */
VOID wrtmjr(VOID);            /* writes WGSERV.CFG                         */
#ifdef UNIX
VOID wrtmod(VOID);            /* writes module.c                           */
#endif // UNIX
VOID reqchk(VOID);            /* just the "required" check from finint()   */
INT refsok(VOID);             /* module references ok? (1 or 0)            */
VOID ctrefs(VOID);            /* re-count module references                */
CHAR *gtmdfnam(CHAR *appname); /* given module name, return mdf name       */
VOID markfile(CHAR *filname,struct ffblk *fb,GBOOL fromend);
                              /* mark file with WGSMENU.DAT's ffblk       */

#define MISSREQ "wgsreq.flg"  /* file to signal missing required modules   */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                        /* __INTEGROU_H                              */
