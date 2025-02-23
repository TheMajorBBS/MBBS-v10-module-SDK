/***************************************************************************
 *                                                                         *
 *   DNFMGR.H                                                              *
 *                                                                         *
 *   Copyright (c) 1998 Galacticomm, Inc.         All Rights Reserved.     *
 *                                                                         *
 *   Custom DynaFile templates management declarations.                    *
 *                                                                         *
 *                                           - J. Alvrus    06/25/1998     *
 *                                                                         *
 ***************************************************************************/

#ifndef __DNFMGR_H
#define __DNFMGR_H

#include <iostream.h>
#include "gcomm.h"
#include "galacth.h"
#include "dnf.h"

dnfHandler * EXPORT                //   returns allocated handler
dnfCreateHandlerURL(               // create a new DNF handler from URL
acthSession * pSes,                //   for this session
dnfMap * pMapBase,                 //   map on which to base handler
CHAR const * BaseDir);             //   base template directory

dnfHandler * EXPORT                //   returns allocated handler
dnfCreateHandler(                  // create a new DNF handler for a file
ostream * pbout,                   //   stream to the browser
dnfMap * pMapBase,                 //   map on which to base handler
CHAR const * tempFile);            //   DynaFile template to handle

dnfMap * EXPORT                    //   returns map for template
dnfGetMap(                         // get a DNF map for a template
dnfMap * pMapBase,                 //   base map used for template
CHAR const * tempFile);            //   DynaFile template to handle

CHAR * EXPORT                      //   returns destination buffer
dnfTemplateFromURL(                // create template path from URL
CHAR const * BaseDir,              //   base template directory
CHAR const * url,                  //   URL w/relative path & file name
CHAR * buf,                        //   buffer to receive complete path
size_t bufSiz);                    //   size of buffer

VOID EXPORT
dnfSetTemplateTvb(                 // set DNF_TEMPLATE text variable
dnfHandler const * dnf);           //   based on this dnfHandler

VOID EXPORT
dnfClearTemplateTvb();             // clear DNF_TEMPLATE text variable

#endif // __DNFMGR_H
