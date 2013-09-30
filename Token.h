#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>

using namespace std;

class Token{
  public:

    enum Type{
      INSERT,
      DELETE,
      CREATE,
      INTO,
      FROM,
      TABLE,
      UPDATE, 
      SHOW,
      OPEN,
      CLOSE,
      WRITE,
      EXIT,
      SELECT,
      PROJECT,
      RENAME,
      SET,
      CROSS,
      UNION,
      DIFFERENCE,
      PRODUCT,
      LEFTPAREN,
      RIGHTPAREN,
      QUOTE,
      LITERAL
    };


    Token();
    Token(string v);
    Token(Type t, string v);
    
    string value;
    Type type;
};


#endif
