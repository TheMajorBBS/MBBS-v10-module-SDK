/***************************************************************************
 *                                                                         *
 *   VDIRBBS.H                                                             *
 *                                                                         *
 *   Copyright (c) 1994-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Virtual Directory API Server for File Libraries, etc.                 *
 *                                                                         *
 *   Glue for getting:  FTP Server Daemon / Virtual Directory API          *
 *   to live with:  File Libraries / File Reservations Kernel.             *
 *   This is the only source file with references to both systems.         *
 *                                                                         *
 *                                        - RNStein  7/11/94               *
 *                                                                         *
 ***************************************************************************/

#include "vdir.h"

#ifndef __VDIRBBS_H
#define __VDIRBBS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

VDIREXPV(CHAR*) osvkey;			/* key required to view DOS sub-tree    */
VDIREXPV(CHAR*) osgkey;			/* key required to read fm DOS sub-tree */
VDIREXPV(CHAR*) ospkey;			/* key required to write to DOS sub-tree*/
VDIREXPV(CHAR*) libkey;			/* extra key req for Library sub-tree   */
VDIREXPV(struct vdirsvc) vdirlib;	/* VDIRserver for Library sub-tree  */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __VDIRBBS_H
