/***************************************************************************
 *                                                                         *
 *   CFGAPI.H                                                              *
 *                                                                         *
 *   Copyright (c) 1997 Galacticomm, Inc.         All Rights Reserved.     *
 *                                                                         *
 *   Configuration buffer management functions.                            *
 *                                                                         *
 *                                            - J. Alvrus   5/29/97        *
 *                                                                         *
 ***************************************************************************/

#ifndef __CFGAPI_H
#define __CFGAPI_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

CHAR *                             /*   returns ptr to destination         */
cfgGetStr(                         /* get string from configuration buffer */
const CHAR *sectName,              /*   section name                       */
const CHAR *itemName,              /*   item name                          */
const CHAR *dftVal,                /*   default value                      */
CHAR *dst,                         /*   destination buffer                 */
size_t dstSiz,                     /*   size of destination buffer         */
const CHAR *src);                  /*   configuration buffer               */

GBOOL                              /*   returns TRUE if able to set        */
cfgSetStr(                         /* set string in configuration buffer   */
const CHAR *sectName,              /*   section name                       */
const CHAR *itemName,              /*   item name                          */
const CHAR *value,                 /*   string to add                      */
CHAR *buf,                         /*   configuration buffer               */
size_t bufSiz);                    /*   size of configuration buffer       */

GBOOL                              /*   returns TRUE if able to set        */
cfgMerge(                          /* merge two configuration buffers      */
CHAR *dst,                         /*   destination config buf (added to)  */
const CHAR *src,                   /*   source config (to be added)        */
size_t dstSiz);                    /*   size of destination buffer         */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __CFGAPI_H
