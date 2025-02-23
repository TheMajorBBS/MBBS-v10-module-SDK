/***************************************************************************
 *                                                                         *
 *   TLCTRANS.H                                                            *
 *                                                                         *
 *   Copyright (c) 1998  Galacticomm, Inc.        All Rights Reserved      *
 *                                                                         *
 *   Baseline Teleconference Transport Classes                             *
 *   Declarations                                                          *
 *                                               - Phil Henning 5/14/97    *
 *                                                                         *
 ***************************************************************************/

#ifndef __TLCTRANS_H
#define __TLCTRANS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

const SHORT TRANSNAMSIZ             =31;

const SHORT RECV_TYPE_PUBLIC        =0;
const SHORT RECV_TYPE_WHISPER       =1;
const SHORT RECV_TYPE_DIRECTED      =2;
const SHORT RECV_TYPE_INTRO         =3;
const SHORT RECV_TYPE_ENTRANCE      =4;
const SHORT RECV_TYPE_EXIT          =5;
const SHORT RECV_TYPE_USERLIST      =6;
const SHORT RECV_TYPE_WELCOME       =7;
const SHORT RECV_TYPE_NEWTOPIC      =8;
const SHORT RECV_TYPE_ENTEREDEDIT   =9;
const SHORT RECV_TYPE_SWITCHCHAN    =10;
const SHORT RECV_TYPE_ACTION        =11;
const SHORT RECV_TYPE_DBTOGGLE      =12;
const SHORT RECV_TYPE_DBOARDDATA    =13;
const SHORT RECV_TYPE_USERENTER     =14;
const SHORT RECV_TYPE_USEREXIT      =15;
const SHORT RECV_TYPE_WHISPERFR     =16;
const SHORT RECV_TYPE_CHATMSG       =17;
const SHORT RECV_TYPE_PAGE          =18;
const SHORT RECV_TYPE_RETEDIT       =19;
const SHORT RECV_TYPE_PRFBUF        =20;
const SHORT RECV_TYPE_ENTCHAT       =21;
const SHORT RECV_TYPE_RETCHATUSER   =22;
const SHORT RECV_TYPE_RETCHAT       =23;
const SHORT RECV_TYPE_LISTCHG       =24;

const SHORT TRANS_NOBROADCAST       =0x0001;
const SHORT TRANS_IMPLDB            =0x0002;
const SHORT TRANS_IMPLCHAT          =0x0004;
const SHORT TRANS_IMPLPRIV          =0x0008;
const SHORT TRANS_NOECHO            =0x0010;

#ifdef __cplusplus
};
#endif // __cplusplus

#endif // __TLCTRAN_H
