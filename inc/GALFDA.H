/***************************************************************************
 *                                                                         *
 *   GALFDA.H                                                              *
 *                                                                         *
 *   Copyright (c) 1995-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Architecture independent conversion library.                          *
 *                                                                         *
 *                                       - Mahesh Neelakanta 6/12/95       *
 *                                                                         *
 ***************************************************************************/

#ifndef __GALFDA_H
#define __GALFDA_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>

#ifdef GCV2
#define register_dpkfda(app,key,fda) ((VOID)0)
#define lookup_dpkfda(dpk) (NULL)
#else
WGSEXP VOID register_dpkfda(CHAR *appid,CHAR *key,struct flddef *fda);
WGSEXP struct flddef *lookup_dpkfda(struct saunam *saunam);
#endif // GCV2

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __GALFDA_H
