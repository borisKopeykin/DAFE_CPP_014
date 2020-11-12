#include "token_stream2.h"

const char number = '8';
const char quit = 'q';
const char print = ';';
const string prompt = "> ";
const string result = "= ";


Token_stream::Token_stream ()
  : buffer{ 0 }        /// no Token in buffer
{
}

void Token_stream::ignore(char c)
{
    if (full && c==buffer.kind){
        full = false;
        return;
    }
    full = false;
    char ch = 0;
    while (cin>>ch)
        if (ch==c) return;
}

void Token_stream::putback (Token t)
{
  if (full)
    error("putback() into a full buffer");

  buffer = t;
  full = true;
}


Token Token_stream::get ()
{
  if (full)         // do we already have a Token ready?
  {
    full = false;   // remove Token from buffer
    return buffer;
  }

  char ch;
  cin >> ch;  // note that >> skips whitespace (space, newline, tab, ...)

  switch (ch)
  {
  case print:    // for "print"
  case quit:    // for "quit"
  case '(':
  case ')':
  case '+':
  case '-':
  case '*':
  case '/':
  case '%':
    return Token{ ch };      // let each character represent itself
  case '.':

  case '0': case '1': case '2': case '3': case '4':
  case '5': case '6': case '7': case '8': case '9':
  {
    cin.putback(ch);         // put digit back into the input stream
    double val;
    cin >> val;              // read a floating-point number
    return Token{number, val};  // let '8' represent "a number"
  }

  default:
    error("Bad token");
  }
}
