#include "Token.h"


Token::Token(){}

Token::Token(string v){
  value = v;
}

Token::Token(Type t, string v){
  type = t; value = v;
}
