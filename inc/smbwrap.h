/***************************************************************************
 *                                                                         *
 *  SMBWRAP.H                                                              *
 *                                                                         *
 *  Copyright (c) 1997-1998 Galacticomm, Inc.     All Rights Reserved.     *
 *                                                                         *
 *  This is the header file for the wrapper class for the                  *
 *  library of routines for accessing memory data files with fixed         *
 *  length records. (SMBAPI)                                               *
 *                                                                         *
 *                                              - Phil Henning   6/21/97   *
 *                                                                         *
 ***************************************************************************/

#ifndef __SMBWRAP_H
#define __SMBWRAP_H

#include "smbapi.h"

class CSmb {
public:
    CSmb(
    size_t DataLength,             //  Maximium length of data
    pSMBKEYTABLE keyptr,           //  Pointer to key array
    UINT CachedRecords);           //  Number of records to cache

    CSmb();                        //  Default constructor
    ~CSmb();                       //  Destructor

    static const SHORT smbInUse;
    static const SHORT smbCreateError;

    GBOOL                          //  Call CSmb::GetLastError on failure
    Create(                        // Create an SMB object
    size_t DataLength,             //  Maximium length of data
    pSMBKEYTABLE keyptr,           //  Pointer to key array
    UINT CachedRecords);           //  Number of records to cache

    GBOOL                          //  Call CSmb::GetLastError on failure
    CreateFrom(                    // Create a wrapper around existing SMB
    SMBHANDLE smb);                //  SMBHANDLE to wrap

    VOID
    Close();                       // Close the smb

    static
    SHORT
    GetLastError();                // Returns last error

    inline
    SMBHANDLE                      //  Internal SMB handle
    GetHandle();                   // Get the handle.

    inline
    INT                            //  Number of recs
    GetCount();                    // Get count of items in smb

                                   //  Note: the count may get out of sync
                                   //  if the SMBHANDLE is used directly
                                   //  to insert and delete records


    VOID *                         //  Pointer to the data in the SMB
    Insert(                        // Insert a record into datafile
    const VOID *pData);            //  Data to insert

    VOID
    Delete();                      // Deletes the current record pointer

    VOID *                         //  Pointer to data or NULL
    GetEqual(                      // Get a record from a database
    const VOID *pKeyInfo,          //  Key we are searching for
    UINT uiKey);                   //  Key number to look up by

    VOID *                         //  Pointer to data or NULL
    GetPrevious();                 // Get previous from current record

    VOID *                         //  Pointer to data or NULL
    GetHigh(                       // Get highest record in the tree
    UINT uiKey);                   //  Key to get highest on

    VOID *                         //  Pointer to data or NULL
    GetLow(                        // Get the lowest record in the tree
    UINT Key);                     //  Key to get lowest on

    VOID *                         //  Pointer to data or NULL
    GetNext();                     // Get next from current record

    VOID *                         //  Pointer to data or NULL
    CurrentData();                 // Gets data of current record

    SMBPTR                         //  Absolute number of current record
    CurrentNumber();               // Gets current position of record

    VOID *                         //  Pointer to data or NULL
    GetBynum(                      // Get record by absolute number
    SMBPTR Number,                 //  Record number to get
    UINT uiKey);                   //  Key number to load as current

    VOID *
    GetGreater(                    //  Get greater than a key
    const VOID *pKeyInfo,          // Key we are searching for
    UINT uiKey);                   //  Key number to look up by

    VOID *
    GetLess(                       //  Get less than a key
    const VOID *pKeyInfo,          // Key we are searching for
    UINT uiKey);                   //  Key number to look up by

    SMBPTR                         //  Current Record Number
    Bookmark();                    // Bookmark the current record

    VOID*                          //  Data at bookmark
    RestoreBookMark();             // Restore the bookmark

private:
    SMBHANDLE m_handle;
    static SHORT m_err;
    INT m_count;
    UINT m_lastkey;
    UINT m_bookkey;
    SMBPTR m_bookmark;

    // copy and assignment operators are not implemented due
    // to possible dangers of deletion of the SMBHANDLE if one
    // is deleted or goes out of scope;

    CSmb(const CSmb& rhs);
    CSmb& operator=(const CSmb* rhs);
};
#endif // __SMBWRAP_H


