/***************************************************************************
 *                                                                         *
 *   STATSCNS.H                                                            *
 *                                                                         *
 *   Copyright (c) 1992-1997 Galacticomm, Inc.        All Rights Reserved. *
 *                                                                         *
 *   This is the header to be included in any statistic screen handlers.   *
 *                                                                         *
 *                                               - Chris Robert 02/28/92   *
 *                                                                         *
 ***************************************************************************/

#ifndef __STATSCNS_H
#define __STATSCNS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct statsc {                    /* statistic screen interface structure */
     CHAR *name;                   /*   name of statistic screen           */
     CHAR *filnam;                 /*   file name to get screen from       */
     VOID (*inirou)(VOID);         /*   initialize (fill-in) routine       */
     UINT (*keyhit)(
          UINT scncod);            /*   key hit handler routine            */
     VOID (*occrou)(VOID);         /*   occasional update (every 60 secs)  */
     VOID (*cycrou)(VOID);         /*   once-per-cycle routine             */
     VOID (*finrou)(VOID);         /*   take down screen routine           */
};

extern INT stahdl;                 /* screen handle to pass to actvscn()   */

VOID inidst(VOID);
VOID register_stascn(struct statsc *stascn);

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __STATSCNS_H                         */
