#ifndef LEXER_H_
#define LEXER_H_


#include <vector>
#include <string>
#include <iostream>
#include "Token.h"
#include "Parser.h"
#include <fstream>

using namespace std;

class Lexer{
  public:
    
    string current; 

    vector<Token> todo;

    Lexer();
    ~Lexer();

    Parser p;

    void readFile(string filename);

    void getString();

    void tokenize(string line);

    void addToken();

};

#endif
