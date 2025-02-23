/***************************************************************************
 *                                                                         *
 *   UPDUTL.H                                                              *
 *                                                                         *
 *   Copyright (c) 1989-1997 Galacticomm, Inc.  All Rights Reserved        *
 *                                                                         *
 *   This is the header file for the utility routines used by INSTALL.EXE  *
 *   and WGSMUP.EXE to update .MSG files by merging new messages into old  *
 *   message files.                                                        *
 *                                                                         *
 *   The merge1() routine will update the destination directory with any   *
 *   .MSG files now already present, also merging .MSG's present in both   *
 *   directories, so that the resulting destination directory files have   *
 *   the structure and message order of the original source directory      *
 *   files, but the message-contents of the original destination directory *
 *   files.  The original destination directory .MSG files are renamed to  *
 *   another filetype in the process (if files of this type are already    *
 *   present when merge1() is invoked, they are used in place of the       *
 *   .MSG's).                                                              *
 *                                                                         *
 *   The merge1() routine's "lang2ow" parameter tells UPDUTL to copy all   *
 *   text blocks for any one language from the new MSG file to the output  *
 *   one.  Passing "English/RIP" as the "lang2ow" parameter will cause all *
 *   English/RIP text blocks in the new MSG file to go into the output     *
 *   one, ignoring any changes the Sysop may have made to existing         *
 *   messages.  Pass "" or NULL as the "lang2ow" to treat all languages in *
 *   the default manner.                                                   *
 *                                                                         *
 *   If the keyword "END_UPD" is found immediately before a LEVEL## {}     *
 *   directive, merge1() will copy the remaining contents of the *old*     *
 *   message file into the output file.                                    *
 *                                                                         *
 *   Usage:                                                                *
 *                                                                         *
 *        merge1(oldnam,newnam,outnam);                                    *
 *                                                                         *
 *                                            - T. Stryker 2/7/89          *
 *                                              (walhf SJB)                *
 *                                            - C. Robert 1/31/93          *
 *                                                                         *
 ***************************************************************************/

#ifndef __UPDUTL_H
#define __UPDUTL_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define UPDSUCCESS 0
#define UPDFAILURE (-1)

extern
CHAR *upderr;

VOID merge1(CHAR *oldn,CHAR *newn,CHAR *outn,CHAR *lang2ow);
INT ll_merge1(GBOOL cataonerr,CHAR *oldn,CHAR *newn,CHAR *outn,CHAR *lang2ow);
INT updmdf (GBOOL cataonerr,CHAR *oldmdf, CHAR *newmdf, CHAR *finmdf);
VOID freeupdm(VOID);

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __UPDUTL_H                           */
