#include "func.h"

const char number = '8';
const char quit = 'q';
const char print = ';';
const string prompt = "> ";
const string result = "= ";

Token_stream ts;

double primary ()
{
  Token t = ts.get();
  switch (t.kind)
  {
  case '(':          // handle '(' expression ')'
  {
    double d = expression();
    t = ts.get();
    if (t.kind != ')')
      error("')' expected");
    return d;
  }

  case number:          // we use '8' to represent a number
    return t.value;

  case '-':
      return - primary();

  case '+':
      return primary();

  default:
    error("primary expected");
  }
}


/// deal with *, /, and %
double term ()
{
  double left = primary();
  Token t = ts.get();    // get the next token from token stream

  while (true)
  {
    switch (t.kind)
    {
    case '*':
      left *= primary();
      t = ts.get();
      break;

    case '%':
    {
      double d = primary();
      if (d == 0) error("divide by zero");
      left = fmod(left,d);
      t = ts.get();
      break;
    }

    case '/':
    {
      double d = primary();
      if (d == 0) error("divide by zero");
      left /= d;
      t = ts.get();
      break;
    }

    default:
      ts.putback(t);     // put t back into the token stream
      return left;
    }
  }
}


/// deal with + and -
double expression ()
{
  double left = term();  // read and evaluate a Term
  Token t = ts.get();    // get the next token from token stream

  while (true)
  {
    switch (t.kind)
    {
    case '+':
      left += term();    // evaluate Term and add
      t = ts.get();
      break;

    case '-':
      left -= term();    // evaluate Term and subtract
      t = ts.get();
      break;

    default:
      ts.putback(t);     // put t back into the token stream
      return left;       // finally: no more + or -: return the answer
    }
  }
}

void clean_up_mess()
{
    ts.ignore(print);
}

void calculate()
{
    while (cin)
    try {
      cout << prompt;
      Token t = ts.get();
      while (t.kind == print) t = ts.get();  // 'q' for quit
      if (t.kind == quit) return;       // ';' for "print now"
      ts.putback(t);
      cout << result << expression() << '\n';
     }
    catch (exception& e){
        cerr << e.what() << '\n';
        clean_up_mess();
    }
}
