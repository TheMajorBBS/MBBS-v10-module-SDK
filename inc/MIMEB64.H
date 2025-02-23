/***************************************************************************
 *                                                                         *
 *   MIMEB64.H                                                             *
 *                                                                         *
 *   Copyright (c) 1995-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   MIME Content-Type field for different file types                      *
 *                                                                         *
 *                               6/1/95 - Bert Love,                       *
 *                                        Scott Brinker,                   *
 *                                        Charles Dunn &                   *
 *                                        Mahesh Neelakanta                *
 *   Moved from SMTPRECV.C      7/16/96 - Bob Stein                        *
 *                                                                         *
 ***************************************************************************/

#ifndef __MIMEB64_H
#define __MIMEB64_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT
#ifdef __BUILDMIMEU
#define MIMEEXP __export
#else
#define MIMEEXP __import
#endif
#else
#define MIMEEXP
#endif // GCWINNT

INT                                /*   returns number of output bytes     */
base64dc(                          /* decode base64 string                 */
CHAR *inp,
CHAR *outp);

VOID
base64nc(
const CHAR* inBuffer,
CHAR* outBuffer,
INT outBufferSize);

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __MIMEB64_H
