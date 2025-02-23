/***************************************************************************
 *                                                                         *
 *   TVB.H                                                                 *
 *                                                                         *
 *   Copyright (c) 1996-1997 Galacticomm, Inc.    All rights reserved.     *
 *                                                                         *
 *   Text variables for C++.                                               *
 *                                                                         *
 *                                                - RNStein  8/16/96       *
 *                                                                         *
 ***************************************************************************/

#ifndef __TVB_H
#define __TVB_H

#include <iostream.h>

class tvbTranslation;              // Text Variable translation (stream-stream)
class tvbDefinition;               // Text Variable definition (one or more)
class tvbReference;                // Text Variable reference

const CHAR *                       //   it gives you a value (""=no such name)
textVar(                           // Text Variable conversion
const CHAR *name);                 //   give it a name

#define TVBNAMSIZ 256              // max size of name tvbTranslate() can xlat
#define TVBPREFIX '['              // default text variable name prefix
#define TVBSUFFIX ']'              // default text variable name suffix

class EXPORT tvbTranslation {      // translate Text Variables in char stream

public:
     tvbTranslation(               // construct in-stream text var translation
     istream& _tvin,               //   input stream (with text variable names)
     ostream& _tvout);             //   output stream (with text var values)

     ~tvbTranslation();            // destructor

     VOID
     setFixes(                     // set prefix and suffix for text var names
     CHAR _prefix,                 // prefix (e.g. '[')
     CHAR _suffix);                // suffix (e.g. ']')

     VOID
     setLimit(                     // limit number of bytes to read from tvin
     LONG _limit);                 //   max number to read from input stream

     VOID
     proceed();                    // proceed with translation

private:
     istream& tvin;                // input stream
     ostream& tvout;               // output stream
     CHAR prefix;                  // prefix (e.g. '[')
     CHAR suffix;                  // suffix (e.g. ']')
     GBOOL islimit;                // TRUE=use limit, FALSE=read to EOF
     LONG limit;                   // limit on bytes to read from tvin
     LONG ngot;                    // bytes gotten from tvin

     GBOOL                         //   TRUE=was more, FALSE=EOF or limit
     nextChar(                     // get next charcter from stream
     CHAR& ch);                    //   character got if TRUE
};

class EXPORT tvbDefinition {       // Text Variable definition (one or more)

public:
     tvbDefinition(                // constructor
     const CHAR *_name=NULL);      //   text var name, NULL=many,indeterminate

     virtual
     ~tvbDefinition();             // destructor

     VOID
     registerDef();                // register the text variable definition
                                   //   (often called by derived constructor)

     virtual
     GBOOL                         //   TRUE=this definition can resolve
     claim(                        // does this definition claim this name?
     const CHAR *nam);             //   name of text variable

     virtual
     const CHAR *                  //   it gives you a value ("" if !claim())
     resolve(                      // resolve a text var name into its value
     const CHAR *nam)=0;           //   give it the name of the text variable
                                   //   Returned string lives at least until
                                   //   same def instance is resolve()'d again.

     inline
     CHAR const *
     getName() const               // get name of this variable
     {
          return(name);
     }

protected:
     CHAR *name;                   // internal copy of constructed name
                                   //   (NULL=many,indeterminate)
};

class EXPORT tvbReference {        // Text Variable reference
public:
     tvbReference(                 // construct a reference to a text variable
     const CHAR *_name);           //   name of alleged text variable

     ~tvbReference();              // destructor

     GBOOL
     defined();                    // is this the name of a defined text var?

     const CHAR *
     getName();                    // get name reference was contructed with

     const CHAR *                  //   if !defined(), returns "", never NULL
     getValue();                   // get value of text variable

private:
     CHAR *name;                   // internal copy of name being referenced
     tvbDefinition *tvd;           // corresponding definition (NULL=undefined)

     VOID
     findDef();                    // associate with a registered tvbDefinition
};

#endif // __TVB_H
