#ifndef TOKEN_STREAM2_H
#define TOKEN_STREAM2_H

#include "token2.h"

class Token_stream
{
public:
  Token_stream ();    /// make a Token_stream that reads from cin
  Token get ();
  void putback(Token t);
  void ignore(char c);

private:
  bool full {false};  /// is there a Token in the buffer?
  Token buffer;        /// here we keep a Token put back using putback()
};

#endif // TOKEN_STREAM2_H
