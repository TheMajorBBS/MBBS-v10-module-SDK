/////////////////////////////////////////////////////////////////////////////
//
//   OBJMAP.H
//
//   Copyright (c) 1997  Galacticomm, Inc.        All Rights Reserved
//
//   Double Linked List Managemnt Class
//   Declarations
//                                               - Phil Henning 5/14/97
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __OBJMAP_H
#define __OBJMAP_H

#define   MAP_KEY_INUSE     -1
#define   MAP_OK             0

struct CObj {
    CHAR* pName;
    VOID* pObject;
    struct CObj* pPrev;
    struct CObj* pNext;
};

class CObjMap {
public:
    CObjMap();
    virtual ~CObjMap();

protected:
    INT m_count;
    CObj* m_first;
    CObj* m_last;
    CObj* m_current;
    CObj* m_next;
    CObj* m_prev;

public:
    virtual INT AddHead(const CHAR* pName, VOID* pObject);
    virtual INT AddTail(const CHAR* pName, VOID* pObject);
    virtual VOID* Find(const CHAR* pName);
    virtual VOID* Find(const INT iIdx);
    virtual VOID* GetHead();
    virtual VOID* GetTail();
    virtual VOID* GetNext();
    virtual VOID* GetPrev();
    INT GetCount();
    VOID RemoveAll();
    VOID RemoveHead();
    VOID RemoveTail();
    GBOOL Remove(const CHAR* pName);
    GBOOL RemoveIdx(const INT iIdx);

private:
    VOID SetCurrent(CObj* pObj);
    CObj* FindInternalRef(const CHAR* pName);
    CObj* FindInternalRef(const INT iIdx);
};

#endif // __OBJMAP_H

