#include "Lexer.h"
#include "Token.h"


Lexer::Lexer(){
}

Token Lexer::getToken(){



  stringstream ret;


  while(buffer){

    string tmp;
    buffer >> tmp;
    ret << tmp;

  }


  cout << ret.str();

  
  return Token();
}
