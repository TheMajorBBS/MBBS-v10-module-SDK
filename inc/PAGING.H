/***************************************************************************
 *                                                                         *
 *    PAGING.H                                                             *
 *                                                                         *
 *    Copyright (c) 1997 Galacticomm, Inc.       All Rights Reserved.      *
 *                                                                         *
 *    This is the baseline paging header file.                             *
 *                                                                         *
 *                                          - P. Henning 11/14/97          *
 *                                                                         *
 ***************************************************************************/

#ifndef __PAGING_H
#define __PAGING_H

#if !defined GCDOS
#include "worcomn.h"
#endif /* GCDOS */

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define PAGMNM "Paging"            // module name for gen db page records

// page status codes
#define PAGE_OK  1                 // page set to OK
#define PAGE_OFF 2                 // page set to OFF
#define PAGE_ON  3                 // page set to ON

#define PAGETCKINT 15              // page rtkick interval

#define MIN2PINT(n) ((n)*(60/PAGETCKINT)) // convert minutes to page intervals
#define PINT2MIN(p) (((p)*PAGETCKINT)/60) // convert page intervals to minutes

#define NEEDCO  -1                 // target user-id count when colon is needed
#define MAXIGN  25                 // max # of pagers users can ignore
#if defined(GCDOS)
#define IGNLSIZ UIDSIZ             // max size of uid in page ignore list
#else
#define IGNLSIZ WUIDSIZ            // max size of uid in page ignore list
#endif /* GCDOS */

// return codes from page command parser
#define PRS_PAGE_USER    0         // paging a user
#define PRS_PAGE_FORMAT  1         // show the format of page command
#define PRS_PAGE_TOK     2         // set page setting to "OK"
#define PRS_PAGE_TOF     3         // set page setting to "OFF"
#define PRS_PAGE_TON     4         // set page setting to "ON"
#define PRS_PAGE_SHOW    5         // show current page settings
#define PRS_PAGE_SETINT  6         // set page interval
#define PRS_PAGE_IGNORE  7         // ignore pages from a user
#define PRS_PAGE_ALLOW   8         // allow pages from a user
#define PRS_PAGE_NOTFND  9         // user specified not found (on or offline)
#define PRS_PAGE_NOTON   10        // user specified not online
#define PRS_PAGE_NEEDCO  11        // ambig. command, need colon
#define PRS_PAGE_AMBIG   12        // ambig. command, must specify completely

struct WGSEXP pageInfo {                  // in-memory per-user page info
     INT pagedCtr;                 //   intervals-since-last-paged counter
     INT pagedConsCtr;             //   intervals-since-paged-sysop counter
     INT pageInt;                  //   user-set page interval
     INT pageSts;                  //   user-set page status
     INT nIgnore;                  //   number of users being ignored
     CHAR ignList[MAXIGN][IGNLSIZ];//   list of users being ignored
};

struct WGSEXP pageInfoDisk {              // on-disk page info (for gen db)
     CHAR userid[UIDSIZ];          //   userid in question
     CHAR modnam[MNMSIZ];          //   module name ("User Paging")
     INT pageInt;                  //   default page interval
     INT pageSts;                  //   default page status
     INT nIgnore;                  //   number of users being ignored
     CHAR ignList[MAXIGN][IGNLSIZ];//   list of users being ignored
};


// global paging-related routine pointers
WGSEXPF(INT,parsePageCmdRou)(CHAR *pageCmdBuf,VOID *pageCmdInfo);
WGSEXPF(INT,pagerouUid)(const CHAR *from,const CHAR *to,CHAR *msg);
WGSEXPF(INT,pagesetUid)(const CHAR *userid);
WGSEXPF(INT,cspagerou)(CHAR *to,CHAR *msg);
WGSEXPF(INT,gpirouUid)(const CHAR *userid);
WGSEXPF(INT,pageHowmnyHook)(CHAR *stg, GBOOL samas, CHAR *match);

WGSEXPF(VOID,spagesetUid)(const CHAR *userid,GBOOL on,GBOOL ok);
WGSEXPF(VOID,hdlPageCmdRou)(INT pageCode,VOID *pageCmdInfo);
WGSEXPF(VOID,setPageIntRou)(const CHAR *userid, INT pageIntMins);
WGSEXPF(VOID,pageShowRou)(const CHAR *userid);

WGSEXPF(GBOOL,pageIgnoredRou)(const CHAR *userid,const CHAR *uid);
WGSEXPF(GBOOL,ignorePageRou)(const CHAR *userid,const CHAR *uid);
WGSEXPF(GBOOL,allowPageRou)(const CHAR *userid,const CHAR *uid);
WGSEXPF(GBOOL,canPageHook)(const CHAR* userid);
WGSEXPF(GBOOL,pageOutputHook)(const CHAR* userid);

WGSEXPF(CHAR*,pagePrspowHook)(CHAR* start, INT mnum, INT* count, CHAR *match);

WGSEXPF(struct pageInfo*,pageGetInfoHook)(const CHAR* userid);

// Depreciated Vectors - for backward compatability only
WGSEXPF(INT,pagerou)(CHAR *to,CHAR *msg);
WGSEXPF(INT,pageset)(VOID);
WGSEXPF(INT,gpirou)(INT usn);

WGSEXPF(VOID,spageset)(GBOOL on,GBOOL ok);
// ***

INT pageUserMessage(CHAR *pageCmdBuf,VOID *pageCmdInfo);

WGSEXPV(INT) gpagint;              // global page interval,use if gpirou==NULL

WGSEXPV(CHAR*) pagekey;            // key required to use paging
WGSEXPV(CHAR*) noignkey;           // key required to not be ignored

WGSEXPV(INT) dftpop;               // default on/off/ok setting
WGSEXPV(INT) defpgint;             // default page interval

WGSEXPV(struct pageInfo*) pageptr; // pointer to user's page info

WGSEXPV(HMCVFILE) pagemb;          // paging configuration file

WGSEXPV(GBOOL) pageEnabled;        // is baseline paging enabled?

WGSEXP struct pageInfo*
pageGetInfoNum(                    /* get page info struct by channel      */
INT unum);                         /*   channel number to get              */

#ifdef __cplusplus
};
#endif // __cplusplus

#endif // __PAGING_H

