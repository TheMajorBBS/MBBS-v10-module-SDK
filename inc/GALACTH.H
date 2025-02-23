/***************************************************************************
 *                                                                         *
 *   GALACTH.H                                                             *
 *                                                                         *
 *   Copyright (c) 1996-1997 Galacticomm, Inc.    All rights reserved.     *
 *                                                                         *
 *   Web server interface for Active HTML kernel (GALACTH).                *
 *                                                                         *
 *                                                - RNStein  8/6/96        *
 *                                                                         *
 ***************************************************************************/

#ifndef __GALACTH_H
#define __GALACTH_H

#include <strstrea.h>
#if !defined(GCV30)
#include <iomanip.h>
#endif

#if defined(GCV30)
#define acthVersion "ActiveHTML/1.0" // Active HTML kernel version
#elif defined(AH11)
#define acthVersion "ActiveHTML/1.1" // Active HTML kernel version
#else
#define acthVersion "ActiveHTML/1.2" // Active HTML kernel version
#endif // GCV30

#define httpVersion "HTTP/1.0"     // server's HTTP version

#define PNAMESIZ 80                // max room for parameter name (decoded)

// Classes defined here //
class acthSession;                 // Kernel's HTTP session, request - response
class acthOstreambuf;              // output stream to client
class acthUserID;                  // Kernel's User-ID
class acthRequest;                 // Web server's HTTP request (abstract)
class acthResponse;                // Web server's HTTP response (abstract)
class acthAgent;                   // Agent-specific stuff (abstract)
class acthSynthesis;               // Agent-spec sess-specific stuff (abstract)

#if !defined(GCV30)

#if !defined(AH11)
// return values from acthUserID::pswAuthentic & acthSession::getUserAuthFailure()
enum AUTHSTAT {
    USERBADPASSWORD =-4,
    USERDELETED     =-3,
    USERSUSPENDED   =-2,
    USERNOTONFILE   =-1,
    USERUNKNOWN     =0,
    USERAUTHENTIC   =1
};

enum AUTHTYPE {                    // authentication types
     AT_UNKNOWN,                   //   type not initialized
     AT_BROWSER,                   //   browser authentication (header)
     AT_COOKIE                     //   cookie authentication
};

enum AUTHMETH {                    // authentication sub-type/method
     AM_UNKNOWN,                   //   sub-type not initialized
     AM_BASIC,                     //   basic authentication (B64 Uid:Pwd)
     AM_DIGEST                     //   digest authentication (not impl.)
};

enum PARAMENC {                    // parameter encoding identifiers
     PENC_UNKNOWN,                 //   unknown encoding type
     PENC_URL,                     //   "application/x-www-form-urlencoded"
     PENC_MULTIPART                //   "multipart/form-data"
};

#endif // !AH11

typedef VOID* AGTPOSITION;

#endif // !GCV30

// Objects used internally (only in galacth.cpp) //
#ifndef ACTHUVECTOR
#define ACTHUVECTOR VOID
#endif
#ifndef ACTHPVECTOR
#define ACTHPVECTOR VOID
#endif

extern
const INT EXPORT pnamesiz;         // max room for parameter name (decoded)

///////////////////////////////////////////////////////////////
// KERNEL'S CLASSES (acthSession, acthOstreambuf acthUserID) //
///////////////////////////////////////////////////////////////

class EXPORT acthSession {         // Kernel's HTTP session

public:                            // Web Server's functions:
     acthSession(                  // constructor, begin a new session
     acthRequest *_req,            //   already-instantiated sssRequest
     acthResponse *_rsp);          //   already-instantiated sssResponse

     ~acthSession();               // destructor, session over

private:
     acthSession();                // no default constructor

     acthSession(                  // no copy constructor
     acthSession& hs);

     VOID
     operator=(                    // no assignment operator
     acthSession& hs);

public:
     GBOOL                         //   returns TRUE=someone, FALSE=no one
     claim();                      // check if an agent will handle resource

     GBOOL
     proceed();                    // handle ses, TRUE=call again, FALSE=done

     VOID
     abort();                      // abort session, no more proceed() calls

public:                            // Callable until freereq() is called:
                                   // (return values of these functions also
                                   // expected to remain valid until freereq())
     VOID
     freereq();                    // done with request-specific information

     const CHAR *
     host();                       // request host, eg "www.company.com"

     const CHAR *
     urlsfx();                     // request path, eg "sub/index.htm" (suffix)

     INT
     urlargc();                    // parse suffix, return no. path elements

     CHAR *                        //   returns copy of namval
     urlargv(                      // return path element 0 to urlargc()-1
     INT index,                    //   index 0 to urlargc()-1
     CHAR *namval,                 //   where to store name=value pair
     INT size);                    //   room for pair (incl '\0')

     const CHAR *
     urlargv(                      // return path element 0 to urlargc()-1
     INT index);                   //   index 0 to urlargc()-1

#if !defined(GCV30) && !defined(AH11)

     PARAMENC                      //   returns encoding type code
     paramEncoding();              // get type of encoding used for parameters

#endif // !GCV30 && !AH11

     INT
     nparam();                     // number of parameters

     GBOOL                         //   TRUE=parameter specified, FALSE=missing
     param(                        // get parameter by name (FALSE=no such)
     const CHAR *name,             //   name of parameter (case ignored)
     CHAR *value=NULL,             //   where to store value (eg "2")
     INT size=0);                  //   room for value (incl '\0')

     INT                           //   returns length (not incl term)
     param(                        // get parameter by index
     INT index,                    //   0 to nparam()-1
     CHAR *name,                   //   where to put name (eg "parm")
     INT namsiz,                   //   room for name (incl '\0')
     CHAR *value=NULL,             //   where to put value (eg "2")
     INT valsiz=0);                //   room for value (incl '\0')

#if !defined(GCV30) && !defined(AH11)

     bool                          //   true=parameter specified, false=missing
     paramStreamOpen(              // get parameter input stream by name
     CHAR const * name,            //   name of parameter (case ignored)
     istream ** ppstParam);        //   buffer to receive stream pointer

     VOID
     paramStreamOpen(              // get parameter input stream by index
     INT index,                    //   0 to nparam()-1
     istream ** ppstParam);        //   buffer to receive stream pointer

     VOID
     paramStreamClose(             // finish up use of parameter stream
     istream * pstParam);          //   stream pointer from paramStreamOpen

#endif // !GCV30 && !AH11

     GBOOL                         //   TRUE=found, FALSE=none
     paramIndex(                   // get index of parameter name
     const CHAR *name,             //   name of parameter (case ignored)
     INT& idx);                    //   answer, 0 to nparam()-1

     INT                           //   room needed to store param (incl term)
     paramRoom(                    // room needed to decode entire param
     const CHAR *name);            //   name of parameter (eg "parm")

     INT                           //   room needed to store param (incl term)
     paramRoom(                    // room needed to decode entire param
     INT index);                   //   0 to nparam()-1

#if !defined(GCV30) && !defined(AH11)

     INT
     paramNumHeaders(              // get number of parameter headers
     INT index) const;             //   0 to nparam()-1

     size_t                        //   returns length of value (less term.)
     paramHeader(                  // get a parameter header
     INT index,                    //   index of parameter (0 to nparam()-1)
     INT hdrIndex,                 //   index of header
     CHAR * namBuf,                //   buffer to receive name
     size_t namSiz,                //   size of name buffer
     CHAR * valBuf=NULL,           //   buffer to receive result
     size_t valSiz=0) const;       //   size of buffer

     bool                          //   returns true if header exists
     paramHeader(                  // get a parameter header
     INT index,                    //   index of parameter (0 to nparam()-1)
     CHAR const * hdrName,         //   name of header
     CHAR * valBuf=NULL,           //   buffer to receive result
     size_t valSiz=0) const;       //   size of buffer

     INT
     paramNumHeaders(              // get number of parameter headers
     CHAR const * name) const;     //   name of parameter (eg "parm")

     bool                          //   returns true if parameter exists
     paramHeader(                  // get a parameter header
     CHAR const * name,            //   name of parameter (case ignored)
     INT hdrIndex,                 //   index of header
     CHAR * namBuf,                //   buffer to receive name
     size_t namSiz,                //   size of name buffer
     CHAR * valBuf=NULL,           //   buffer to receive result
     size_t valSiz=0) const;       //   size of buffer

     bool                          //   returns true if parameter/header exist
     paramHeader(                  // get a parameter header
     CHAR const * name,            //   name of parameter (case ignored)
     CHAR const * hdrName,         //   name of header
     CHAR * valBuf=NULL,           //   buffer to receive result
     size_t valSiz=0) const;       //   size of buffer

#endif // !GCV30 && !AH11

     INT
     vernum();                     // 0=HTTP/0.9, 100=HTTP/1.0, 101=HTTP/1.1

     ULONG                         //   network order: 0x01020304 => 1.2.3.4
     clientIP();                   // IP address of remote client

     USHORT                        //   usually 1024 to 65535
     clientPort();                 // TCP port number of remote client

     INT
     age();                        // age of connection in seconds

     GBOOL
     header(                       // get hdr field by name (FALSE=no such)
     const CHAR *name,             //   name of field (eg "accept")
     CHAR *value,                  //   where to put value (eg "*/*")
     INT valsiz);                  //   room for value (incl '\0')

     const CHAR *
     method();                     // e.g. "GET"

     const CHAR *
     url();                        // e.g. "/dynamic/app/index.htm?parm=2"

     const CHAR *
     version();                    // e.g. "HTTP/1.0"

     const CHAR *
     hdr1st();                     // e.g. "Host: www.abc.com" (NULL=none)

     const CHAR *
     hdrnxt();                     // e.g. "Accept: */*" ... (NULL=no more)

     LONG
     lenBody();                    // length of request's entity-body

     istream&
     bodyin();                     // request entity body input stream

public:                            // call these only in the ACTHPREHDR stage:
     VOID
     headerFollows();              // agent makes header ("nph" in CGI lingo)

     VOID
     setStatus(                    // specify status (ala CGI "Status:" hdr)
     const CHAR *sts);             //   e.g. "200 OK"

     VOID
     redirect(                     // redirect request to another URL (sts 302)
     const CHAR *url);             //   full URL of alternate resource

     GBOOL                         //   TRUE=redir to new URL, FALSE=ok as is
     forceDir();                   // force URL to be a directory (end in "/")

public:                            // call these in ACTHPREHDR or ACTHHEADER stg:
     VOID
     contypeFext(                  // specify content type by file extension
     const CHAR *fext);            //   e.g. "htm"

     VOID
     contypeMIME(                  // specify Content-type header field value
     const CHAR *mimetype);        //   e.g. "text/html" (default: text/html)

     VOID
     addlVersion(                  // append product version to Server header
     const CHAR *prodver);         //   product and version, e.g. "Zhoots/6.0"

     VOID
     headerField(                  // inject custom header field into response
     const CHAR *field);           //   e.g. "Who-knows: what"

     VOID
     headerField(                  // inject custom header field into response
     const CHAR *fieldname,        //   e.g. "Who-knows"
     const CHAR *fieldvalue);      //   e.g. "what"

public:                            // Agent's functions, entire session:
     INT                           //   number of bytes actually sent
     sndrsp(                       // send response (portion) to browser (BIN)
     const CHAR *data,             //   data to send
     INT nbytes);                  //   number of bytes

     INT                           //   number of bytes actually sent
     sndrsp(                       // send response (portion) to browser (BIN)
     const CHAR *data);            //   string to send ('\0' terminated)

     GBOOL                         //   TRUE=begun FALSE="not found" reported
     sndfile(                      // send file as entity body
     const CHAR *fpath);           //   path of file (type inferred from ext)

     GBOOL                         //   TRUE=begun FALSE="not found" reported
     sndfile(                      // send file as entity body
     const CHAR *fpath,            //   path of file
     const CHAR *mimetype);        //   MIME type of file (e.g. "text/html")

     LONG
     sndfileCount();               // bytes sent by most recent sndfile()

     const CHAR *
     mainHost();                   // server main domain (eg "www.gcomm.com")

     const CHAR *
     serverVer();                  // server's version (eg "Worldgroup/2.1")

     ostream *boutp;               // stream to the browser

     acthUserID *
     getUser();                    // get user information, or NULL=anonymous

#if !defined(GCV30)
#if !defined(AH11)

     AUTHSTAT
     getUserAuthFailure();         // get reason for getUser returning NULL

     AUTHTYPE
     getUserAuthType() const;      // get authentication type (browser/cookie)

     AUTHMETH
     getUserAuthMeth() const;      // get authentication method (basic)

#endif // AH11

     VOID
     setUser(                      // set authentication cookie
     const CHAR *uid,              //   User-ID
     const CHAR *psw);             //   password

     VOID
     clrUser();                    // clear authentication cookie

     VOID
     authProcess(
     CHAR *buffer);
#endif // !GCV30

private:
     acthRequest *req;             // request from browser, NULL=done with it
     acthResponse *rsp;            // response to browser
     acthAgent *agt;               // agent-specific stuff
     acthSynthesis *syn;           // agent-specific session-specific stuff
     acthUserID *usr;              // user specific stuff (NULL=anonymous)
     acthOstreambuf *osb;          // output stream to client
     GBOOL authChecked;            // authentication checked
     CHAR *_host;                  // host name of request
     CHAR *_urlsfx;                // URL suffix
     CHAR *ualc;                   // parsed URL suffix
     ACTHUVECTOR *urlv;            // URL argument vector
     ACTHPVECTOR *parmv;           // parameter map
     GBOOL moretogo;               // done proceeding
     istrstream *urlparst;         // parameters appended to URL (obsolete)
#if !defined(GCV30) && !defined(AH11)
     AUTHSTAT usrfail;             // reason for getUser returning NULL
#endif // !GCV30 && !AH11

     GBOOL                         //   TRUE=found, FALSE=not found
     findAgent();                  // find an agent who will claim to handle

     VOID
     authCheck();                  // check authentication

     VOID
     paramInit();                  // parameter map (obsolete)

     VOID
     freereqStuff();               // preparations for req->freereq()
};

class acthOstreambuf : public streambuf {

public:
     acthOstreambuf(
     acthSession *_ses);           // construct a stream to the browser

     ~acthOstreambuf();            // destructor

     virtual
     INT                           //   return 0=OK, EOF=fail
     sync();                       // empty buffer contents

     virtual
     INT                           //   return 0=OK, EOF=fail
     overflow(                     // handle overflow of buffer
     INT ch);                      //   extra character after full buffer

private:
     INT sizbuf;                   // size of buffer
     CHAR *buffer;                 // allocated buffer
     acthSession *ses;             // corresponding Active HTML session
};

ostream& EXPORT
crlf(                              // manipulator, like endl but <CR><LF>
ostream& os);                      //   (and without a flush())

#if !defined(GCV30)
omanip<CHAR *> EXPORT
htmlBreaks(                        // manipulator, transl CR's to HTML <BR>'s
CHAR *crlines);                    //   CR-terminated lines (temp modified)
                                   //   (lines may also be CRLF-terminated)
#endif // !GCV30

typedef
acthUserID *                       //   base ptr to implemented derived class
UIDFACTORY(                        // User-ID factory, security system specific
const CHAR *userid);               //   User-ID, as user-typed, case ignored

class EXPORT acthUserID {          // Prime window unto all things user

public:
     static
     VOID
     setUIDfactory(                // User-ID implementation declares factory
     UIDFACTORY *uidf);            //   function to call to make acthUserID's

     acthUserID(                   // constructor
     const CHAR *userid);          //   User-ID, as user-typed, case ignored

     acthUserID();                 // contstructor
     virtual
     ~acthUserID();                // destructor

private:
     acthUserID(                   // no copy constructor
     acthUserID&);

     VOID
     operator=(                    // no assignment operator
     acthUserID&);

public:
     virtual
     const CHAR *
     userid() const =0;            // database-formatted User-ID

#if defined(GCV30) || defined(AH11)
     virtual
     GBOOL                         //   ret
     pswAuthentic(                 // authenticate user based on his password
     const CHAR *password)=0;      //   user-typed password (case matters)
#else
     virtual
     AUTHSTAT                      //   ret
     pswAuthentic(                 // authenticate user based on his password
     const CHAR *password)=0;      //   user-typed password (case matters)
#endif // GCV30 || AH11

     virtual
     GBOOL                         //   ret TRUE=pass, FALSE=fail
     digAuthentic(                 // authenticate user via digest of uid:psw
     const CHAR *digest,           //   32-digit digest, Digest Access Auth.
     const CHAR *typedUID=NULL)=0; //   User-ID as typed (if differs from ctor)
                                   //   (note:  case of password must matter)

     virtual
     VOID
     unAuthentic()=0;              // remove authenticated status

     virtual
     GBOOL                         //   TRUE=acceptable
     okSyntax() const =0;          // is syntax of typed User-ID acceptable?

     virtual
     GBOOL                         //   TRUE=in database FALSE=not
     isOnFile()=0;                 // is User-ID on file?

#if defined(GCV30) || defined(AH11)
     virtual
     GBOOL                         //   TRUE=xxxAuthentic() passed
     authentic()=0;                // has user been authenticated?
#else
     virtual
     AUTHSTAT                      //   TRUE=xxxAuthentic() passed
     authentic()=0;                // has user been authenticated?
#endif // GCV30 || AH11

public:                            // must be authenticated to use these:
     virtual
     GBOOL                         //   TRUE=granted, FALSE=denied
     hasKey(                       // access check, ala haskey("NORMAL")
     const CHAR *key)=0;           //   name of key

public:                            // can use these if user simply on file:
     virtual
     GBOOL                         //   TRUE=has enough, FALSE=doesn't
     afford(                       // can user afford this charge?
     LONG credits)=0;              //   so many credits

     virtual
     GBOOL                         //   TRUE=had enough, FALSE=didn't
     charge(                       // deduct credits from user's account
     LONG credits,                 //   so many credits
     GBOOL asmuch=TRUE)=0;         //   if short, take as much as possible?
};



//////////////////////////////////////////////////////
// WEB SERVER'S CLASSES (acthRequest, acthResponse) //
//////////////////////////////////////////////////////

class EXPORT acthRequest {         // Web server's HTTP request (abstract)

public:
     acthRequest();                // constructor (request fully received)

     virtual
     ~acthRequest();               // destructor (no longer need req info)

private:
     acthRequest(                  // no copy constructor
     acthRequest& hr);

     VOID
     operator=(                    // no assignment operator
     acthRequest& hr);

public:                            // Callable until freereq() is called:
                                   // (return values of these functions also
                                   // expected to remain valid until freereq())
     virtual
     const CHAR *
     method()=0;                   // e.g. "GET"

     virtual
     const CHAR *
     url()=0;                      // e.g. "/dynamic/app/index.htm?parm=2"
     virtual

     const CHAR *
     version()=0;                  // e.g. "HTTP/1.0"

     virtual
     const CHAR *
     hdr1st()=0;                   // e.g. "Host: www.abc.com" (NULL=none)

     virtual
     const CHAR *
     hdrnxt()=0;                   // e.g. "Accept: */*" ... (NULL=no more)

     virtual
     LONG
     lenBody()=0;                  // length of request's entity-body

     virtual
     istream&
     bodyin()=0;                   // request entity body input stream

     virtual
     INT
     vernum();                     // 0=HTTP/0.9, 100=HTTP/1.0, 101=HTTP/1.1

     virtual
     ULONG                         //   network order: 0x01020304 => 1.2.3.4
     clientIP()=0;                 // IP address of remote client

     virtual
     USHORT                        //   usually 1024 to 65535
     clientPort()=0;               // TCP port number of remote client

     virtual
     INT
     age()=0;                      // age of connection in seconds

     virtual
     VOID
     freereq();                    // free up request resources
};

enum ACTHSTAGE {
     ACTHPREHDR=0,                 // before sending header
     ACTHHEADER=1,                 // sending header fields
     ACTHBODY=2                    // sending entity body
};

class EXPORT acthResponse {        // Web server's HTTP response (abstract)

public:
     acthResponse();               // constructor (ready to respond)

     virtual
     ~acthResponse();              // destructor (end of response sent)

private:
     acthResponse(                 // no copy constructor
     acthResponse& hr);

     VOID
     operator=(                    // no assignment operator
     acthResponse& hr);

public:                            // call these only in the ACTHPREHDR stage:
     virtual
     VOID
     headerFollows()=0;            // agent makes header ("nph" in CGI lingo)

     virtual
     VOID
     setStatus(                    // specify status (ala CGI "Status:" hdr)
     const CHAR *sts)=0;           //   e.g. "200 OK"

     virtual
     VOID
     redirect(                     // redirect request to another URL (sts 302)
     const CHAR *url)=0;           //   full URL of alternate resource

     virtual
     VOID
     notFound()=0;                 // 404 not found error

public:                            // call these in ACTHPREHDR or ACTHHEADER stg:
     virtual
     VOID
     contypeFext(                  // specify content type by file extension
     const CHAR *fext)=0;          //   e.g. "htm"

     virtual
     VOID
     contypeMIME(                  // specify Content-type header field value
     const CHAR *mimetype)=0;      //   e.g. "text/html" (default: text/html)

     virtual
     VOID
     addlVersion(                  // append product version to Server header
     const CHAR *prodver);         //   product and version, e.g. "Zhoots/6.0"

     virtual
     VOID
     headerField(                  // inject custom header field into response
     const CHAR *field)=0;         //   e.g. "Who-knows: what"

     virtual
     VOID
     headerField(                  // inject custom header field into response
     const CHAR *fieldname,        //   e.g. "Who-knows"
     const CHAR *fieldvalue)=0;    //   e.g. "what"

public:                            // call these at any stage:
     virtual
     INT                           //   number of bytes actually sent
     sndrsp(                       // send response (portion) to Web browser
     const CHAR *data,             //   data to send
     INT nbytes)=0;                //   number of bytes

     virtual
     INT                           //   number of bytes actually sent
     sndrsp(                       // send response (portion) to Web browser
     const CHAR *data)=0;          //   string to send ('\0' terminated)

     virtual
     GBOOL                         //   TRUE=begun FALSE="not found" reported
     sndfile(                      // send file as entity body
     const CHAR *fpath)=0;         //   path of file (type inferred from ext)

     virtual
     GBOOL                         //   TRUE=begun FALSE="not found" reported
     sndfile(                      // send file as entity body
     const CHAR *fpath,            //   path of file
     const CHAR *mimetype)=0;      //   MIME type of file (e.g. "text/html")

     virtual
     LONG
     sndfileCount()=0;             // bytes sent by most recent sndfile()

     virtual
     const CHAR *
     mainHost()=0;                 // server main domain (eg "www.gcomm.com")

     virtual
     const CHAR *
     serverVer();                  // server's version (eg "Worldgroup/2.1")

protected:
     ACTHSTAGE stage;
};



////////////////////////////////////////////////
// AGENT'S CLASSES (acthAgent, acthSynthesis) //
////////////////////////////////////////////////

class EXPORT acthAgent {           // Agent-specific stuff (abstract)

public:
     acthAgent(                    // prefix agent construction
     const CHAR *apnam,            //   application (eg "File Libraries")
     const CHAR *upfx=NULL);       //   URL prefix (eg "library")

     virtual
     ~acthAgent();                 // agent "destructor" (shutdown)

private:
     acthAgent();                  // no default constructor

     acthAgent(                    // no copy constructor
     acthAgent& ha);

     VOID
     operator=(                    // no assignment operator
     acthAgent& ha);

#if !defined(GCV30)
     VOID
     versionError(                 // report agent/kernel version conflict
     const CHAR *moduleVersion);   //   kernel version expected by module
#endif // GCV30

public:

     virtual
     VOID
     registerAgent();              // 1.0 register agent function

#if defined(GCV30)
#define registerAgent(v) registerAgent() // (for source-code compatibility)
#else
     virtual
     VOID
     registerAgent(                // register agent with ACTH kernel
     const CHAR *versionString);   //   kernel version expected by agent
                                   // (usually called by constructor)
     virtual
     AGTPOSITION                   //   position in the agent array
     getFirstAgent();              // get the position of the first agent

     virtual
     acthAgent*                    //   pointer to the next agent in the list
     getNextAgent(                 // get the next agent
     AGTPOSITION& pos);            //   position structure
#endif // GCV30

                                   // Each request session is "offered" to
                                   // every agent via their claim() member.
                                   // The first to claim it, handles it, except
                                   // that Universal agent claims override
                                   // prefix agent claims.

     virtual
     GBOOL                         //   TRUE=all requests passed to claim()
     isUniversal();                // is agent Universal?

     virtual
     GBOOL                         //   returns TRUE=will handle, FALSE=won't
     claim(                        // check if agent will handle req session
     acthSession *ses);            //   for inquiring about request

     virtual
     acthSynthesis *               //   agent's session info (NULL=can't)
     newSynthesis(                 // instantiate agent's derived zzzSynthesis
     acthSession *ses)=0;          //   only for passing to acthSynthesis's ctor

     const CHAR *
     urlpfx(VOID);                 // get URL prefix for agent

     const CHAR *
     appname(VOID);                // get application name for agent

protected:
     CHAR *_appname;               // application (eg "File Libraries")
     CHAR *_urlpfx;                // URL prefix (eg "library") (NULL=univ)
     int pfxlen;                   // strlen(_urlpfx), if any
};

enum ACTHCODE {                    // return code for hdtSynthesis::proceed()
     ACTHNOTFND=-4,                //   resource not found (404)
     ACTHFORBID=-3,                //   deny request, not allowed (403)
     ACTHNOANON=-1,                //   log user on, then retry request (401)
     ACTHDONE=0,                   //   request handled, reply sent
     ACTHMORE=1,                   //   more work, keep calling proceed()
};
#define ACTHMORETOGO(ac) (ac > ACTHDONE)     // code(s) for more proceed()ing

class EXPORT acthSynthesis {       // Agent-spec sess-specific stuff (abstract)

public:
     acthSynthesis(                // constructor, agent-spec, sess-spec stuff
     acthSession *_ses);           //   kernel's session info

     virtual
     ~acthSynthesis();             // destructor

private:
     acthSynthesis();              // no default constructor

     acthSynthesis(                // no copy constructor
     acthSynthesis& hs);

     VOID
     operator=(                    // no assignment operator
     acthSynthesis& hs);

public:
     virtual ACTHCODE              //   see enumerated values above
     proceed()=0;                  // agent's request handler

     GBOOL
     firsttime();                  // TRUE=proceed()'s first call, FALSE=after

     VOID
     postproceed();                // Called by kernel after first proceed()

     virtual VOID
     abort();                      // kernel -> agent, request died
                                   //   (expect no more proceed() calls)
protected:
     acthSession *ses;             // kernel's session info
     ostream& bout;                // output stream to browser

private:
     GBOOL _firsttime;             // returned by firsttime()
};

//////////////////////////////
// HEADER PARSING UTILITIES //
//////////////////////////////

CHAR * EXPORT                      //   returns pointer to destination buffer
acthGetHeaderValue(                // extract a header's value (incl. quoted)
CHAR const * hdr,                  //   entire header contents
size_t * pvalsiz,                  //   pointer to size of buffer (updated)
CHAR * valbuf=NULL);               //   buffer to receive value

bool EXPORT                        //   returns true if found
acthGetHeaderParam(                // extract a parameter of header field
CHAR const * hdr,                  //   entire header contents
CHAR const * paramName,            //   name of parameter (e.g. "boundary")
size_t * pvalsiz=NULL,             //   pointer to size of buffer (updated)
CHAR * valbuf=NULL);               //   where to put value (e.g. "*/*")

/////////////////////////
// MEDIA TYPE HANDLING //
/////////////////////////

extern
const CHAR * const EXPORT noMediaType;  // "application/octet-stream"
extern
const CHAR * const EXPORT noMediaExt;   // ""

const CHAR * EXPORT                //   media type (eg "text/html")
acthMediaType(                     // get media type from a file extension
const CHAR *filext);               //   file extension (eg "htm")
                                   //   returns noMediaType if filext unknown
                                   //   never returns NULL

const CHAR * EXPORT                //   file extension (eg "htm")
acthMediaFext(                     // get file extension from media type
const CHAR *type);                 //   media type (eg "text/html")
                                   //   returns "" if type unknown
                                   //   never returns NULL

////////////////////////////
// CONFIGURATION HANDLING //
////////////////////////////

enum ACTHOPTCODE {                 // Active HTML Kernel option result codes
     AHOPT_SUCCESS,                //   operation successful
     AHOPT_NOTFOUND,               //   the requested resource was not found
     AHOPT_BUFFERSIZE,             //   the supplied buffer was too small
     AHOPT_OUTOFRANGE,             //   the supplied index was out of range
     AHOPT_READONLY,               //   the value may not be written
     AHOPT_WRITEONLY,              //   the value may not be read
     AHOPT_EMPTY,                  //   the value may not be empty
     AHOPT_TOOLARGE,               //   the supplied value is too large
     AHOPT_INVALID,                //   generic invalid value response
     AHOPT_INVSYNTAX,              //   invalid value: bad syntax
     AHOPT_INVRESERVED,            //   invalid value: reserved value used
     AHOPT_INVFORBID               //   invalid: value forbidden by other opts
};

ACTHOPTCODE EXPORT                 //   result code
acthGetOption(                     // get an Active HTML Kernel option
CHAR const * Name,                 //   name of option to retrieve
size_t * pBufSize,                 //   size of buffer (updated)
CHAR * pBuffer);                   //   buffer to receive option value

ACTHOPTCODE EXPORT                 //   result code
acthSetOption(                     // set an Active HTML Kernel option
CHAR const * Name,                 //   name of option to set
CHAR const * Value);               //   new value for option

INT EXPORT
acthNumOptions();                  // number of Active HTML Kernel options

ACTHOPTCODE EXPORT                 //   result code
acthGetOptionName(                 // get an an Active HTML Kernel option name
INT Index,                         //   index of option to get name of
size_t * pBufSize,                 //   size of buffer (updated)
CHAR * pBuffer);                   //   buffer to receive option name

#endif // __GALACTH_H
