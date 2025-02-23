
#ifndef __TLCDYNTR_H
#define __TLCDYNTR_H
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct transfuncptrs {
     size_t size;
     VOID  (*construct)(VOID);
     VOID  (*destruct)(VOID);
     VOID  (*adduserfunc)(LPUSRSTRUCT);
     VOID  (*removeuserfunc)(LPUSRSTRUCT);
     VOID  (*sendallfunc)(const CHAR* from,const CHAR* to,
               const CHAR* msg,SHORT type, const CHAR* chan,
               SHORT msgnum, const CHAR* p1, const CHAR* p2,
               const CHAR* p3);
     VOID  (*sendallbutfunc)(const CHAR* from,const CHAR* to,
               const CHAR* msg,SHORT type,const CHAR* chan,
               SHORT msgnum, const CHAR* p1, const CHAR* p2,
               const CHAR* p3,const CHAR* not1, const CHAR* not2);
     VOID  (*recvtextfunc)(const CHAR* from,const CHAR* to,
               const CHAR* msg,SHORT type, SHORT msgnum,
               const CHAR* p1, const CHAR* p2, const CHAR* p3);

     GBOOL (*cmdresultfunc)(LPUSRSTRUCT,SHORT operation, GBOOL success,
               SHORT reason);
     VOID  (*outputfunc)(LPUSRSTRUCT);
     VOID  (*sendtabbeddb)(const CHAR* pszUserid, const CHAR* pszChannel);
     SHORT flags;
} TFUNCPTRS, *LPTFUNCPTRS;

#ifdef __cplusplus
};
#endif // __cplusplus
#endif // __TLCDYNTR_H

