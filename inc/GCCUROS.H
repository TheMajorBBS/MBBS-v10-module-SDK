/***************************************************************************
 *                                                                         *
 *   GCCUROS.H                                                             *
 *                                                                         *
 *   Copyright (c) 1996-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Header for current OS type.                                           *
 *                                                                         *
 *                                            - Craig Yap 1/09/96          *
 *                                                                         *
 ***************************************************************************/

#ifndef __GCCUROS_H
#define __GCCUROS_H

/***************************************************************************
 * When compiling you should define one of the following                   *
 *  GCDOSL               DOS Large Model                                   *
 *  GCDOSP               DOS Protected Model (Phar-Lap)                    *
 *  GCWIN3X              Windows 3.X                                       *
 *  GCTNT86              TNT (x86)                                         *
 *  GCWINNT              Windows NT (x86)                                  *
 *  GCBSD2X              BSD/OS 2.X                                        *
 *  GCSCO30              SCO 3.0                                           *
 *  GCLNX1X              Linux 1.1+                                        *
 *  GCUWR2X              UnixWare 2.X                                      *
 *  GCOSF30              OSF/1 3.0 (alpha)                                 *
 *  GCSOL2X              Solaris 2.X (sparc)                               *
 *  GCHPU10              HP-UX 10.0  (pa-risc)                             *
 ***************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#if defined(GCDOSL) || defined(GCDOSP)
#define GCDOS
#endif // GCDOSL || GCDOSP

                                   /* return values for curos()            */
#define   OSDOSL     0x100         /*   DOS Large Model                    */
#define   OSDOSP     0x101         /*   DOS Protected Model (Phar-Lap)     */
#define   OSWIN3X    0x102         /*   16-bit Windows client              */
#define   OSTNT86    0x200         /*   TNT                                */
#define   OSNTX86    0x300         /*   NT for Intel                       */
#define   OSBSD2X    0x400         /*   BSD/OS 2.X                         */
#define   OSSCO30    0x401         /*   SCO 3.0                            */
#define   OSLNX1X    0x402         /*   Linux 1.X                          */
#define   OSUWR2X    0x403         /*   UnixWare 2.X                       */
#define   OSOSF30    0x404         /*   OSF/1 3.0 Alpha                    */
#define   OSSOL2X    0x500         /*   Sun Solaris 2.X                    */
#define   OSHPU10    0x501         /*   HP-UX 10.0                         */

SHORT                              /*   return current OS                  */
curos(VOID);

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif //  __GCCUROS_H
