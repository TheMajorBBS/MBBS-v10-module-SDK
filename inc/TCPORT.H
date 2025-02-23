/***************************************************************************
 *                                                                         *
 *   TCPORT.H                                                              *
 *                                                                         *
 *   Copyright (c) 1996-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   TCP/IP Portability Issues - Only included for module with             *
 *   implementation-specific variants. (GALTCPIP.DLL)                      *
 *                                                                         *
 *                                           - R. Skurnick  7/9/96         *
 *                                                                         *
 ***************************************************************************/

#ifndef __TCPORT_H
#define __TCPORT_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef PACSOFT
#ifndef IPSWITCH
#error Must choose one:  -DPACSOFT  -DIPSWITCH
#endif // !IPSWITCH
#endif // !PACSOFT

/*--- Pacific Softworks' Fusion TCP/IP Kernel ---*/
#ifdef PACSOFT
INT socketclose(INT skt);
#define NUMSOCKETS (INT)(so_cnt)   /* maximum (configured) no. of sockets  */
extern ULONG so_cnt;
extern INT dbgtcp;                 /* debug reporting enabled              */
extern CHAR *dbgtcpfn;             /* debug reporting file name            */
extern INT do_check_heap;          /* debug kernel heap checking           */
extern INT timskep;                /* check PPP timers at phase transitions*/
#define TCPIP_CAN_SENDBA           /* can sendba() (pre-poll send capacity)*/
#endif                             /* PACSOFT                              */

/*--- Ipswitch's Piper/IP Kernel ---*/
#ifdef IPSWITCH
#if defined(UNIX)
#define socketclose      close
#elif defined(GCWINNT)
#define socketclose      closesocket
#else
#define socketclose(skt) soclose(_fdexternalize(skt))
#endif // UNIX
#define NUMSOCKETS FD_SETSIZE      /* maximum number of sockets available  */
#define tcpkinit()                 /* (no kernel initialization required)  */
                                   /*--- Global vars for fd_scanxxx()'s ---*/
#ifdef GCWINNT
TCPIPEXPV(fd_set *) fdscptr;
#else
extern UINT *fdscptr;              /* pointer to an fd_set from select()   */
#endif // GCWINNT
TCPIPEXPV(UINT) fdscbits;     /* 16 bits at a time  from fdscptr[i]   */
TCPIPEXPV(UINT) fdscmsk;      /* shifts through 16 mask values        */
TCPIPEXPV(CHAR) fdscj;        /* counts 0..15 and back again          */
TCPIPEXPV(INT) fdscskt;       /* counts sockets, 0..NUMSOCKETS-1      */
#define ll_config(d,i,n,m) ((VOID)0)
#define ll_route(d,g,h) ((VOID)0)
#endif // IPSWITCH

TCPIPEXPV(struct sktmap *) sktmap; /* maps socket numbers -> event handlers*/
                                   /* this is a virtual 2D array -- use the*/
                                   /* sktmapped() macro to index elements  */
#define sktmapped(idx,skt) sktmap[idx*NUMSOCKETS+skt]
TCPIPEXPV(INT*) sktarr;      /* array of sockets currently in use    */
TCPIPEXPV(INT*) sktunm;      /* maps socket number -> user number    */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif //__TCPORT_H
