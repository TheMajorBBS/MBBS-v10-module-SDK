/***************************************************************************
 *                                                                         *
 *   WGSUEXT.H                                                             *
 *                                                                         *
 *   Copyright (c) 2002 HSI Software, Inc.  All Rights Reserved            *
 *                                                                         *
 *   Declarations for the user account extension table WGSUEXT.DAT         *
 *                                                                         *
 *                                                - J. Alvrus  7/23/2002   *
 *                                                                         *
 ***************************************************************************/

#ifndef __WGSUEXT_H
#define __WGSUEXT_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef GCWINNT
#   ifdef __BUILDWGSUEXT
#       define WGSUEXTEXP         EXPORT
#       define WGSUEXTEXPV(x)     EXPORT_VARIABLE(x)
#       define WGSUEXTEXPF(x, y)  EXPORT_FUNCTION(x, y)
#    else
#       define WGSUEXTEXP         IMPORT
#       define WGSUEXTEXPV(x)     IMPORT_VARIABLE(x)
#       define WGSUEXTEXPF(x, y)  IMPORT_FUNCTION(x, y)
#    endif
#else
#       define WGSUEXTEXP
#       define WGSUEXTEXPV
#       define WGSUEXTEXPF
#endif // GCWINNT

//#if defined(GCWINNT)
//#ifdef __BUILDWGSUEXT
//#define WGSUEXTEXP __export
//#else
//#define WGSUEXTEXP __import
//#endif                             /* __BUILDWGSUEXT                      */
//#else
//#define WGSUEXTEXP
//#endif                             /* GCWINNT                              */

#define UACCEXTDAT "WGSUEXT.DAT"   /* user account extension data file name*/

//extern DFAFILE * dfaUserExt; /* user account extension data file*/  // Duckula - Removed MAY23

VOID
init__wgsuext(VOID);               /* initialize DLL                       */

#ifdef __cplusplus
}; // extern "C"
#endif /* __cplusplus */

#endif                             /* __WGSUEXT_H                          */
