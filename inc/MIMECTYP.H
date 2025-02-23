/***************************************************************************
 *                                                                         *
 *   MIMECTYP.H                                                            *
 *                                                                         *
 *   Copyright (c) 1994-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   MIME Content-Type field for different file types                      *
 *                                                                         *
 *                                        - Ilya Minkin 11/14/95           *
 *                                                                         *
 ***************************************************************************/

#ifndef __MIMECTYP_H
#define __MIMECTYP_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT
#   ifdef __BUILDMIMEU
#       define MIMEEXP          EXPORT
#       define MIMEEXPV(x)      EXPORT_VARIABLE(x)
#       define MIMEEXPF(x, y)   EXPORT_FUNCTION(x, y)
#    else
#       define MIMEEXP          IMPORT
#       define MIMEEXPV(x)      IMPORT_VARIABLE(x)
#       define MIMEEXPF(x, y)   IMPORT_FUNCTION(x, y)
#    endif
#else
#       define MIMEEXP
#       define MIMEEXPV
#       define MIMEEXPF
#endif // GCWINNT

MIMEEXP VOID
lmimctyp(                          /* Reads in the type and extentions     */
                                   /*   for the Content-Type field         */
const CHAR *filnam);               /*   name of file to read from          */

MIMEEXP const CHAR *               /*   returns Content-Type               */
gmimctyp(                          /* get Content-Type from global list    */
const CHAR *ext);                  /*   extension to search for in list    */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif //__MIMECTYP_H
