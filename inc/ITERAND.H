/***************************************************************************
 *                                                                         *
 *   ITERAND.H                                                             *
 *                                                                         *
 *   Copyright (c) 1996-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Random access version of STL's istream_iterator<>.                    *
 *                                                                         *
 *   Currently, istream_iterand adds bidirectional capabilities as well    *
 *   as + and - operators to istream_iterator.  Full random access is      *
 *   not yet supported.                                                    *
 *                                                                         *
 *                                              - R. Stein  8/7/96         *
 *                                                                         *
 ***************************************************************************/

#ifndef __STD_ITERAND__
#define __STD_ITERAND__


// istream_iterand == (perhaps one day to be a) random access istream_iterator
//                    (now just bidirectional with + and - operators)
//                    (left out:  <  +=  -=  []  )

#include <iterator>

#define FILREV "$Revision: 1.3 $"

#ifndef RWSTD_NO_NAMESPACE
namespace std {
#endif

#ifdef RWSTD_NO_UNDECLARED_FRIEND
template <class T, class Distance>
class istream_iterand;
template <class T, class Distance>
bool operator== (const istream_iterand<T, Distance>& x,
                 const istream_iterand<T, Distance>& y);
#endif

#ifndef RWSTD_NO_DEFAULT_TEMPLATES
template <class T, class Distance = ptrdiff_t> // Distance == ptrdiff_t
#else
template <class T, class Distance>             // Distance == ptrdiff_t
#endif
class istream_iterand : public random_access_iterator<T, Distance>
{
  friend bool operator== (const istream_iterand<T, Distance>& x,
                          const istream_iterand<T, Distance>& y);
protected:

    Distance pos;                  // absolute position in stream
    istream* stream;
    T        value;
    bool     end_marker;

    void seekrel (Distance so)
    {
        seekabs(pos+so);
    }
    void seekabs (Distance sp)
    {
        pos=max(static_cast<Distance>(0),sp);
        read();
    }
    void read ();                  // impose "pos" on stream and value members
    void seekeof ();               // set pos just past the last byte
public:
    istream_iterand (istream& s, Distance p=0) : stream(&s)
    {
        stream->unsetf(ios::skipws);
        seek(p);
    }
    istream_iterand (const istream_iterand<T, Distance>& ir, Distance p)
    {
        stream=ir.stream;
        value=ir.value;
        end_marker=ir.end_marker;
        seek(p);
    }
    istream_iterand (const istream_iterand<T, Distance>& ir)
    {
        stream=ir.stream;
        value=ir.value;
        end_marker=ir.end_marker;
        seek(ir.pos);
    }
public:                            // no default constructor, instead use
    istream_iterand ()             // istream_iterand<X>(x,EOF) for end-of-stream
    {
        ASSERTM(0,"istream_iterand default constructor called!");
    }
public:
    void seek(Distance p)
    {
        if (p == EOF) {
            seekeof();
        }
        else {
            seekabs(p);
        }
    }
    const T& operator* () const { return value; }
    const istream_iterand<T, Distance>& operator++ ()
    {
        seekrel(sizeof(T));
        return *this;
    }
    const istream_iterand<T, Distance> operator++ (int)
    {
        istream_iterand<T, Distance> tmp = *this;
        seekrel(sizeof(T));
        return tmp;
    }
    const istream_iterand<T, Distance>& operator-- ()
    {
        seekrel(-sizeof(T));
        return *this;
    }
    const istream_iterand<T, Distance> operator-- (int)
    {
        istream_iterand<T, Distance> tmp = *this;
        seekrel(-sizeof(T));
        return tmp;
    }
    Distance operator- (
    const istream_iterand<T, Distance>& rgt) const
    {
        return pos-rgt.pos;
    }
    istream_iterand<T, Distance> operator- (
    Distance so) const
    {
        istream_iterand<T, Distance> tmp(*this,pos-so);
        return tmp;
    }
    istream_iterand<T, Distance> operator+ (
    Distance so) const
    {
        istream_iterand<T, Distance> tmp(*this,pos+so);
        return tmp;
    }
};

template <class T, class Distance>
void istream_iterand<T,Distance>::read () // impose "pos" on stream and value members
{
    stream->clear();
    if (stream->seekg(pos).fail()) {
        seekeof();
    }
    else {
        *stream >> value;
        if (stream->fail()) {
            seekeof();
        }
    }
}

template <class T, class Distance>
void istream_iterand<T,Distance>::seekeof () // set pos just past the last byte
{
    stream->clear();
    stream->seekg(0,ios::end);
    if (stream->fail()) {
        stream->clear();
        stream->seekg(pos=0);
    }
    else {
        pos=stream->tellg();
    }                              // value member undefined at EOF
}

template <class T, class Distance>
inline istream_iterand<T, Distance>
operator+ (
Distance so,
const istream_iterand<T, Distance>& rgt)
{
    return istream_iterand<T,Distance>(rgt.pos+so);
}

template <class T, class Distance>
inline bool operator== (const istream_iterand<T, Distance>& x,
                        const istream_iterand<T, Distance>& y)
{
    return(x.stream == y.stream && x.pos == y.pos);
}

typedef istream_iterand<char,streamoff> racsit;
                                   // Random Access Character Stream ITerator

class racsRange {                  // range within a character stream
public:
     racsit begin;
     racsit end;
     racsRange(racsit& _begin,racsit& _end) : begin(_begin), end(_end) {}
     racsRange() : begin(), end() {}         // should never be called

     inline streamoff length()
     {
          return(end-begin);
     }

     friend inline ostream& operator<< (ostream& out,const racsRange& rr)
     {                             // output range of characters
          copy(racsit(rr.begin),racsit(rr.end),ostream_iterator<char>(out));
          return(out);
     }
};

#ifndef RWSTD_NO_NAMESPACE
}
#endif

#undef FILREV

#endif // __STD_ITERAND__
