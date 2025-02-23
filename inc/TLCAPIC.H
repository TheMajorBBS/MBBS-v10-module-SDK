
#ifndef __TLCAPIC_H
#define __TLCAPIC_H

#include "tlcdyntr.h"
#include "tlcdyncm.h"
#include "tlcdynch.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

const SHORT JOINOK           = 0;
const SHORT NOSUCHUSER       =-1;
const SHORT NOSUCHCHAN       =-2;
const SHORT ALRDYINCHAN      =-3;

/***************************************************************************
 *   User related functions                                                *
 ***************************************************************************/

LPUSRSTRUCT tlcUserGetInfo(const CHAR* userid);
GBOOL       tlcUserSetInfo(LPUSRSTRUCT stUsr);
GBOOL       tlcUserCheckAccess(const CHAR* userid, const CHAR* key);
GBOOL       tlcUserCheckAccessM(const CHAR* userid, SHORT key);
GBOOL       tlcUserSendText(
                const CHAR* userid,
                const CHAR* from,
                const CHAR* to,
                const CHAR* pMsg,
                SHORT fType,
                SHORT iMsgNum,
                const CHAR* ptr1,
                const CHAR* ptr2,
                const CHAR* ptr3);
GBOOL       tlcUserInChannel(const CHAR* userid,const CHAR* channel);
SHORT       tlcUserSwitchChannel(const CHAR* userid, const CHAR* channel);
GBOOL       tlcUserInTlc(const CHAR* userid);
ULONG       tlcUserFindID(const CHAR* userid);
ULONG       tlcUserCreateUniqueID(const CHAR* userid);
LPUSRSTRUCT tlcUserGetFirst();
LPUSRSTRUCT tlcUserGetNext();
LPUSRSTRUCT tlcUserGetGT(const CHAR* userid);
GBOOL       tlcUserCreate(LPUSRSTRUCT stUsr, INT iTrans, const CHAR* channel);
GBOOL       tlcUserRemove(const CHAR* userid, const CHAR* channel);
VOID        tlcUserSetTransport(const CHAR* userid, INT idx);
INT         tlcUserGetTransport(const CHAR* userid);
GBOOL       tlcUserCheckIgnore(const CHAR* userid, const CHAR* chkuid);
GBOOL       tlcUserCheckForget(const CHAR* userid, const CHAR* chkuid);
const CHAR* tlcUserGetChatUser(const CHAR* userid);
GBOOL       tlcUserSetChatUser(const CHAR* userid, const CHAR* chatuser);
GBOOL       tlcUserChatBegin(const CHAR* userid, SHORT context);
LPUSRSTRUCT tlcUserSetContext(const CHAR* userid);
LPUSRSTRUCT tlcUserGetContext();


/***************************************************************************
 *   Channel related functions                                             *
 ***************************************************************************/

SHORT       tlcChannelCreateCustom(LPCHANINFO pChanInfo,LPCHFUNCPTRS pFuncs);
SHORT       tlcChannelCreateLocal(LPCHANDSK pChanDsk,GBOOL persist=FALSE);
SHORT       tlcChannelCreatePrivate(
                const CHAR* owner,
                LPCHANDSK pChanDsk=NULL);
VOID        tlcChannelDelete(LPCHANINFO pChanInfo);
CHAR*       tlcChannelFindUser(
                const CHAR* channel,
                const CHAR* pszSearch,
                INT* num,
                LPUSRSTRUCT* ppUser);
LPCHANINFO  tlcChannelGetFirst(VOID);
LPCHANINFO  tlcChannelGetNext(VOID);
LPCHANINFO  tlcChannelGetGT(const CHAR* channel);
INT         tlcChannelGetNumberUsers(const CHAR* channel);

LPUSRSTRUCT tlcChannelGetFirstUser(const CHAR* channel);
LPUSRSTRUCT tlcChannelGetNextUser(const CHAR* channel);
LPUSRSTRUCT tlcChannelGetUserGT(const CHAR* channel, const CHAR* userid);
LPUSRSTRUCT tlcChannelGetUser(const CHAR* channel, const CHAR* userid);
LPCHANINFO  tlcChannelGetInfo(const CHAR* channel);
GBOOL       tlcChannelSetInfo(LPCHANINFO pChanInfo);
VOID        tlcChannelMoveAllUsers(
                const CHAR* channel,
                const CHAR* to,
                SHORT reason,
                SHORT msg);
VOID        tlcChannelRemove(const CHAR* channel);
VOID        tlcChannelRemoveUser(
                const CHAR* channel,
                const CHAR* userid,
                SHORT reason);

GBOOL       tlcChannelPublicSend(
                const CHAR* channel,
                const CHAR* pszUseridFrom,
                const CHAR* pszUseridTo,
                const CHAR* pMsg,
                SHORT fType,
                SHORT iMsgNum,
                const CHAR* ptr1=NULL,
                const CHAR* ptr2=NULL,
                const CHAR* ptr3=NULL);
GBOOL        tlcChannelPublicSendBut(
                const CHAR* channel,
                const CHAR* pszUseridFrom,
                const CHAR* pszUseridTo,
                const CHAR* pMsg,
                SHORT fType,
                SHORT iMsgNum,
                const CHAR* ptr1=NULL,
                const CHAR* ptr2=NULL,
                const CHAR* ptr3=NULL,
                const CHAR* pszUseridNot1=NULL,
                const CHAR* pszUseridNot2=NULL);
GBOOL       tlcChannelPrivateSend(
                const CHAR* channel,
                const CHAR* pszUseridFrom,
                const CHAR* pszUseridTo,
                const CHAR* pMsg,
                SHORT fType,
                SHORT iMsgNum,
                const CHAR* ptr1=NULL,
                const CHAR* ptr2=NULL,
                const CHAR* ptr3=NULL);
GBOOL       tlcChannelRegisterCmd(
                const CHAR* channel,
                LPCMDSTRUCT pCmdSt);
GBOOL       tlcPrivateChannelIsInvited(
                const CHAR* channel,
                const CHAR* userid);
GBOOL       tlcPrivateChannelInvite(
                const CHAR* channel,
                const CHAR* userid);
VOID        tlcPublicSendAllChannels(
                const CHAR* pszUseridFrom,
                const CHAR* pszUseridTo,
                const CHAR* pMsg,
                SHORT fType,
                SHORT iMsgNum,
                const CHAR* ptr1=NULL,
                const CHAR* ptr2=NULL,
                const CHAR* ptr3=NULL);
LPCHANINFO  tlcChannelSetContext(
                const CHAR* channel);
LPCHANINFO  tlcChannelGetContext();

/***************************************************************************
 *   Action API functions                                                  *
 ***************************************************************************/

VOID        actListCreate(LPACTLST liststr);
VOID        actListDelete(const CHAR* listname);
CHAR*       actListGetFirst(VOID);
CHAR*       actListGetNext(VOID);
CHAR*       actListGetCurrent(VOID);
VOID        actListResetCurrent(VOID);
LPACTLST    actListGetConfig(const CHAR* list);
GBOOL       actListSetConfig(const CHAR* list, LPACTLST config);
GBOOL       actListIsDeleted(const CHAR* list);
const CHAR* actWordGetFirst(const CHAR* list);
const CHAR* actWordGetNext(const CHAR* list);
GBOOL       actWordExists(const CHAR* list, const CHAR* word);
LPACTION    actWordGetGT(const CHAR* list, const CHAR* word);
LPACTION    actWordInfoGetCurrent(const CHAR* list);
const CHAR* actGetLastDirected(VOID);
GBOOL       actIsSecret(VOID);
GBOOL       actIsFile(VOID);

/***************************************************************************
 *   Transport functions                                                   *
 ***************************************************************************/

INT         tlcTransRegister(const CHAR* name,LPTFUNCPTRS funcptr);
INT         tlcTransGetNumber(VOID);
INT         tlcTransUserIs(const CHAR* userid);
LPUSRSTRUCT tlcTransGetFirstUser(INT idx,const CHAR* channel=NULL);
LPUSRSTRUCT tlcTransGetNextUser(INT idx,const CHAR* channel=NULL);
GBOOL       tlcTransAddUser(INT idx,LPUSRSTRUCT stUsr);
GBOOL       tlcTransRemoveUser(INT idx,LPUSRSTRUCT stUsr);
GBOOL       tlcTransOutput(INT idx,LPUSRSTRUCT stUsr);
GBOOL       tlcTransSendAll(
                INT idx,
                const CHAR* pszUseridFrom,
                const CHAR* pszUseridTo,
                const CHAR* pMsg,
                SHORT fType,
                const CHAR* channel,
                SHORT iMsgNum=0,
                const CHAR* ptr1=NULL,
                const CHAR* ptr2=NULL,
                const CHAR* ptr3=NULL);
GBOOL       tlcTransSendAllKey(
                INT idx,
                const CHAR* pszUseridFrom,
                const CHAR* pszUseridTo,
                const CHAR* pMsg,
                SHORT fType,
                const CHAR* channel,
                SHORT iMsgNum=0,
                const CHAR* ptr1=NULL,
                const CHAR* ptr2=NULL,
                const CHAR* ptr3=NULL,
                const CHAR* key=NULL);
GBOOL       tlcTransSendAllBut(
                INT idx,
                const CHAR* pszUseridFrom,
                const CHAR* pszUseridTo,
                const CHAR* pMsg,
                SHORT fType,
                const CHAR* channel,
                SHORT iMsgNum=0,
                const CHAR* ptr1=NULL,
                const CHAR* ptr2=NULL,
                const CHAR* ptr3=NULL,
                const CHAR* pszUseridNot1=NULL,
                const CHAR* pszUseridNot2=NULL);
GBOOL       tlcTransCmdResult(
                INT idx,
                LPUSRSTRUCT stUsr,
                SHORT iOperation,
                GBOOL bSuccess,
                SHORT iReason);

/***************************************************************************
 *   Command functions                                                     *
 ***************************************************************************/

GBOOL
tlcCommandRegister(                // register a new command
LPCMDSTRUCT st);                   //  command to register

SHORT
tlcCommandIssue(                   // issue a command based on text
const CHAR* cmdName,               //  cmd to issue
VOID* pParam);                     //  params to pass

/***************************************************************************
 *   Misc utility functions                                                *
 ***************************************************************************/

CHAR* tlcPrivateFromUser(const CHAR* userid);
VOID  tlcSetDefaultChannel(const CHAR* channel);
CHAR* tlcGetDefaultChannel(VOID);
VOID  tlcOutputFinished(VOID);

#ifdef __cplusplus
};
#endif // _cplusplus
#endif // __TLCAPIC_H

