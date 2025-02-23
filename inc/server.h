/***************************************************************************
 *                                                                         *
 *   SERVER.H                                                              *
 *                                                                         *
 *   Copyright (c) 1987-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   This file defines all of the different types of compiles that the     *
 *   Worldgroup server can be defined as.                                  *
 *                                                                         *
 *                                            - W. Muharsky 09/15/97       *
 *                                                                         *
 ***************************************************************************/
#ifndef __SERVER_H
#define __SERVER_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


/***************************************************************************
 *  Webcast Proserver #defines                                             *
 ***************************************************************************/
#ifdef WEBCAST

#define SVR_NAME         "WebCast"
#define SVR_NAMER        "   WebCast"
#define SVR_NAMEL        "WebCast   "
#define SVR_NAMEC        "WEBCAST"
#define SVR_FULL         "WebCast ProServer"
#define BBSVER           200          /* Server underlying version code           */
#define BBSVERSTG        "2.00"
#define REG_KEY_BASE     "SOFTWARE\\Galacticomm\\Webcast ProServer\\CurrentVersion"
#define BBSIRV           ""

/***************************************************************************
 *  ActiBase server #defines                                               *
 ***************************************************************************/
#elif defined (ACTIBASE)

#define SVR_NAME         "ActiBase"
#define SVR_NAMER        "  ActiBase"
#define SVR_NAMEL        "ActiBase  "
#define SVR_NAMEC        "ACTIBASE"
#define SVR_FULL         "ActiBase Server"
#define BBSVER           100
#define BBSVERSTG        "1.00"
#define REG_KEY_BASE     "SOFTWARE\\Galacticomm\\ActiBase Server\\CurrentVersion"
#define BBSIRV           ""

/***************************************************************************
 *  Worldgroup server #defines                                             *
 ***************************************************************************/
#else

#define SVR_NAME         "The Major BBS"
#define SVR_NAMER        "The Major BBS"
#define SVR_NAMEL        "The Major BBS"
#define SVR_NAMEC        "THE MAJOR BBS"
#define SVR_FULL         "The Major BBS" //TODO - Need to replace 
#define BBSVER           1000          /* Server underlying version code           */
#define BBSVERSTG        "10.00"
#define REG_KEY_BASE     "SOFTWARE\\Galacticomm\\The Major BBS\\CurrentVersion" //TODO - Need to replace and update existing Registry keys
#define BBSIRV           ""
#endif

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus
#endif

