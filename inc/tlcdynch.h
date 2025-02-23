
#ifndef __TLCDYNCH_H
#define __TLCDYNCH_H
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct chanfuncptrs {
     VOID   (*construct)(VOID);
     VOID   (*destruct)(VOID);
     SHORT  (*getnumvisfunc)(VOID);
     SHORT (*adduserfunc)(const CHAR* channel,LPUSRSTRUCT pUser,GBOOL bIsFirstEnter);
     SHORT (*removeuserfunc)(const CHAR* channel,LPUSRSTRUCT pUser, SHORT fExitType);
     VOID   (*presendwelcome)(LPUSRSTRUCT pUser);
     VOID   (*postsendwelcome)(LPUSRSTRUCT pUser);
     GBOOL  (*canaccess)(const CHAR* channel, LPUSRSTRUCT pUser, INT access);
} CHFUNCPTRS, *LPCHFUNCPTRS;

#ifdef __cplusplus
};
#endif // __cplusplus
#endif // __TLCDYNCH_H

