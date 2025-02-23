/***************************************************************************
 *                                                                         *
 *   VDIROS.H                                                              *
 *                                                                         *
 *   Copyright (c) 1994-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Virtual Directory API Server for selected OS drives                   *
 *                                                                         *
 *                                        - RNStein  7/11/94               *
 *                                                                         *
 ***************************************************************************/

#include "vdir.h"

#ifndef __VDIROS_H
#define __VDIROS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

VDIREXPV(CHAR*) ospath;			/* Allowed drives (must be upper case)  */
VDIREXPV(GBOOL) osdots;			/* show "." and ".." in file listing    */
VDIREXPV(struct vdirsvc) vdiros;	/* VDIRserver for OS subtree        */

VDIREXP GBOOL
canosvis(VOID);                    /* Exit point: can user view file names?*/

VDIREXP GBOOL
canosget(VOID);                    /* Exit point: can user read files      */

VDIREXP GBOOL
canosput(VOID);                    /* Exit point: can user write files     */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __VDIROS_H
