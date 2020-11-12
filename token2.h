#ifndef TOKEN2_H
#define TOKEN2_H

#include "std_lib_facilities.h"

class Token
{
public:
  char kind;        /// what kind of token
  double value;     /// for numbers: a value
  string name;

  Token (char ch) : kind{ ch }  { }

  Token (char ch, double val) : kind{ ch }, value{ val }  { }

  Token (char ch, string n) : kind{ch}, name{n} {}
};


#endif // TOKEN2_H
