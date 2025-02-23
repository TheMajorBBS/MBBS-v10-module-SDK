/***************************************************************************
 *                                                                         *
 *   PHASEDBG.H                                                            *
 *                                                                         *
 *   Copyright (c) 1994-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Track the phases of the server, for better debugging, tracking, etc.  *
 *   Do this by bracketing important phases or application-specific        *
 *   processing with BEG_PHASE() and END_PHASE() macros.  These            *
 *   macros generate no code if DEBUG is not #-defined.  They generate     *
 *   interceptable vector calls if DEBUG is turned on.                     *
 *                                                                         *
 *                                            - R. Stein 10/14/94          *
 *                                                                         *
 ***************************************************************************/

#ifndef __PHASEDBG_H
#define __PHASEDBG_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define NUMPHS 16                  /* phase beginnings & endings tracked   */

struct phasedbg {                  /* phase tracking information           */
     CHAR *name;                   /* name of phase                        */
     LONG num;                     /* phase-specific number or pointer     */
     INT usrnum;                   /* user number (usrnum)                 */
     INT usrcls;                   /* user meta-state (usrptr->class)      */
     INT usrsta;                   /* user state (usrptr->state)           */
     INT usrsbs;                   /* user substate (usrptr->substt)       */
     INT flags;                    /* see below                            */
};

#define PDBBEG 0x0001              /* on=begin, off=end                    */

#ifdef DEBUG
#define BEG_PHASE(name,num) (*beg_phase)(name,(LONG)num)
#define END_PHASE(name,num) (*end_phase)(name,(LONG)num)
#else
#define BEG_PHASE(name,num) ((VOID)0)
#define END_PHASE(name,num) ((VOID)0)
#endif

WGSEXPF(VOID,beg_phase)(CHAR *name,LONG num);/*BEG_PHASE() vector*/
WGSEXPF(VOID,end_phase)(CHAR *name,LONG num);/*END_PHASE() vector*/
#ifdef GCWINNT
WGSEXPF(VOID,prtPhase)(INT x, INT y);         /* Print phase vector*/
#endif // GCWINNT

VOID
rptphs(                            /* report on the past NUMPHS phases     */
FILE *fp);                         /* file to send report to (FOPWA-opened)*/

struct phasedbg *
pstphs(                            /* get information on a past phase      */
INT index);                        /* 0=most recent, NUMPHS-1=earliest     */
                                   /* returns pointer to phasedbg struct   */
                                   /* or NULL=phase debugging not enabled  */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __PHASEDBG_H
