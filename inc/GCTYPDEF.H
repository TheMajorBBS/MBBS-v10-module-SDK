/***************************************************************************
 *                                                                         *
 *   GCTYPDEF.H                                                            *
 *                                                                         *
 *   Copyright (c) 1996-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Various type definitions.                                             *
 *                                                                         *
 *                                        - Craig Yap 01/10/96             *
 *                                                                         *
 ***************************************************************************/

#ifndef __GCTYPDEF_H
#define __GCTYPDEF_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#if defined( WIN32 ) && ! defined( GCWINNT )
#    define   GCWINNT
#endif

#if defined(UNIX)
#   undef _FARFUNC
#   undef _Cdecl
#   undef _FAR
#   undef far
#   undef huge
#   undef EXPORT
#   define _FARFUNC
#   define _Cdecl
#   define _FAR
#   define FAR
#   define huge
#   define EXPORT
#   undef INT
#   undef UINT

#elif defined(GCWINNT)
#   if ! defined( _FAR )
#       define _FAR
#   endif
#   if ! defined( far )
#       define far
#   endif
#   if ! defined( FAR )
#       define FAR far
#   endif
#   if ! defined(_MSC_VER)
#       if ! defined( EXPORT )
#           define EXPORT _export
#       endif
#   endif // ! defined(_MSC_VER)

#define DLLAPI  __stdcall
#define CPPAPI  __cdecl

#   if defined(_MSC_VER)
#       if defined (USE_DEF_FILE)
#           define EXPORT
#           define IMPORT
#           define EXPORTV
#           define IMPORTV  __declspec(dllimport)
#       else
#           define EXPORT   __declspec(dllexport)
#           define IMPORT   __declspec(dllimport)
#           define EXPORTV  __declspec(dllexport)
#           define IMPORTV  __declspec(dllimport)
#       endif // USE_DEF_FILE
#   endif

#   if defined(__BORLANDC__)
#       define EXPORT   __export
#       define IMPORT   __import
#       define EXPORTV  __export
#       define IMPORTV  __import
#   endif

#elif defined(GCDOSP)
#   define _FAR
#   undef FAR
#   define FAR
#   define EXPORT _export

#elif defined(GCWIN3X)
#   define EXPORT _export

#elif defined(GCDOSL)
#   define EXPORT
#   undef FAR
#   define FAR far
#endif // UNIX

#if !defined(CTREE)
#   if !defined(GCWIN3X)
        typedef unsigned int   UINT;
#   endif // GCWIN3X

#   ifdef GCOSF3X
        typedef int            LONG;
        typedef unsigned int   ULONG;
#   else
#       if defined(GCWIN3X) && MODEL == V
#           define LONG           long
#           define ULONG          unsigned long
#       else
            typedef long           LONG;
            typedef unsigned long  ULONG;
#       endif // GCWIN3X
#   endif // GCOSF3X
#endif // CTREE

typedef int            INT;

#if defined(GCWIN3X) && MODEL == V
#   define CHAR           char
#   define SHORT          short
#   define USHORT         unsigned short
#else
    typedef char           CHAR;
    typedef short          SHORT;
    typedef unsigned short USHORT;
#endif // GCWIN3X

typedef unsigned char  UCHAR;
typedef signed char    SCHAR;

#ifndef VOID
#   define VOID           void
#endif  // VOID

typedef double         DOUBLE;
typedef float          FLOAT;
typedef short          GBOOL;

#if !defined(TRUE)
#   define FALSE 0
#   define TRUE  (!FALSE)
#endif
                                   /* maximum values for types             */
#define GCMAXSHORT   (0x7FFF)
#define GCMAXLONG    (0x7FFFFFFFL)
#define GCMAXUSHORT  (0xFFFFU)
#define GCMAXULONG   (0xFFFFFFFFL)

#ifdef GCWINNT
#define GCMAXINT    GCMAXLONG
#define GCMAXUINT   GCMAXULONG
#else
#define GCMAXINT    GCMAXSHORT
#define GCMAXUINT   GCMAXUSHORT
#endif

#if !defined(GCWINNT) && !defined(GCWIN3X)
#define WINAPI
#endif // GCWINNT

#ifdef GCWINNT
#   ifdef __BORLANDC__
#       define EXPORT_VARIABLE(t)       extern t EXPORT
#       define EXPORT_FUNCTION(t, n)    extern t (* EXPORT n)
#       define IMPORT_VARIABLE(t)       extern t IMPORT
#       define IMPORT_FUNCTION(t, n)    extern t (* IMPORT n)
#   endif // __BORLANDC__
#   if defined(_MSC_VER) || defined(__GNUC__)
#       define EXPORT_VARIABLE(t)       EXPORTV t
#       define EXPORT_FUNCTION(t, n)    EXPORTV t (* n)
#       define IMPORT_VARIABLE(t)       IMPORTV t
#       define IMPORT_FUNCTION(t, n)    IMPORTV t (* n)
#   endif // defined (_MSC_VER) || defined(__GNUC__)
#else // GCWINNT
#   define IMPORT
#   define EXPORT
#   define IMPORTV
#   define EXPORTV
#   define CALLING_CONVENTION
#   define EXPORT_VARIABLE(t)           extern t
#   define EXPORT_FUNCTION(t, n)        extern t (* n)
#   define IMPORT_VARIABLE(t)           extern t
#   define IMPORT_FUNCTION(t, n)        extern t (* n)
#endif // GCWINNT

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __GCTYPDEF_H