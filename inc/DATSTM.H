/***************************************************************************
 *                                                                         *
 *   DATSTM.H                                                              *
 *                                                                         *
 *   Copyright (c) 1994-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   DataStream API - Interface between byte sources (clients) and         *
 *                    byte sinks (servers)                                 *
 *                                                                         *
 *                                             - R. Stein  5/9/94          *
 *                                                                         *
 ***************************************************************************/

#ifndef __DATSTM_H
#define __DATSTM_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

               /* Note that far pointers are used in all DOS memory models */

struct datstm {                    /* DataStream structure for a data sink */
     USHORT FAR (*snkwin)(         /* return how much room sink has now    */
          struct datstm FAR *dsp); /* (pointer to sink's datstm structure) */
     VOID FAR (*hrsone)(           /* pass one byte to the sink            */
          struct datstm FAR *dsp,  /* (pointer to sink's datstm structure) */
          CHAR byte);              /* here's the one byte                  */
     USHORT FAR (*moveit)(         /* sink moves bytes (nactual is fedback)*/
          struct datstm FAR *dsp,  /* (pointer to sink's datstm structure) */
          CHAR FAR *srcloc,        /* source specifies the location        */
          USHORT nwant);           /* source wants sink to move this many  */
     VOID FAR (*didmov)(           /* source reports bytes moved to snkloc */
          struct datstm FAR *dsp,  /* (pointer to sink's datstm structure) */
          USHORT nactual);         /* this many were moved by the source   */
     CHAR FAR *snkloc;             /* snkwin output: where source can store*/
     USHORT snkmax;                /* snkwin output: maximum eventual room */
     USHORT flags;                 /* DSTOVF=sink reports overflow         */
};

#define DSTOVF 0x0001              /* flags: sink may record overflow      */

struct bufstm {                    /* Buffered DataStream sink-server      */
     struct datstm datstm;         /* DataStream session (MUST BE 1ST FLD) */
     CHAR *buffer;                 /* accumulation buffer                  */
     UINT bufsiz;                  /* permanently BUFSIZ (at least 1)      */
     UINT bufcnt;                  /* buffer count, 0..BUFSIZ-1            */
};

/*--- Stub routines for sinks implemented via moveit()  ---*/
/*---------------------------------------------------------*/
/*--- (Both parties may want to move the bytes, so the  ---*/
/*--- sink surrounds its datstm structure with a bufstm ---*/
/*--- structure, which specifies a buffer to interpose  ---*/
/*--- between the two non-lazy parties.)                ---*/

WGSEXP USHORT                      /*   returns room in buffer             */
swbufs(                            /* snkwin() stub for buffered DataStream*/
struct datstm FAR *dsp);           /*   dataStream structure inside bufstm */

WGSEXP VOID
hobufs(                            /* hrsone() stub for buffered DataStream*/
struct datstm FAR *dsp,            /*   dataStream structure inside bufstm */
CHAR byte);                        /*   here's the one byte                */

WGSEXP VOID
dmbufs(                            /* didmov() stub for buffered DataStream*/
struct datstm FAR *dsp,            /*   dataStream structure inside bufstm */
USHORT nactual);                   /*   this many were moved by the source */

/*--- Stub routines for sinks implemented via snkwin() & didmov() ---*/
/*-------------------------------------------------------------------*/
/*--- (Neither party may want to move the bytes, so a movmem()    ---*/
/*--- may need to intervene between the two lazy parties.)        ---*/

WGSEXP USHORT                      /*   rets actual number of bytes moved  */
mviad(                             /* moveit() stub via didmov() & snkwin()*/
struct datstm FAR *dsp,            /*   dataStream structure               */
CHAR FAR *srcloc,                  /*   source location                    */
USHORT nwant);                     /*   number of bytes desired to move    */

WGSEXP VOID
hviad(                             /* hrsone() stub via didmov() & snkwin()*/
struct datstm FAR *dsp,            /*   dataStream structure               */
CHAR byte);                        /*   data byte                          */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __DATSTM_H                           */
