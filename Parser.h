#ifndef PARSER_H_
#define PARSER_H_

#include "Token.h"

#include <vector>

using namespace std;

class Parser{
  public:

    Parser();
    ~Parser();

    void removeFirst(vector<Token>* t);

    bool parse(vector<Token>* t); 

    bool query(vector<Token>* t);
    bool command(vector<Token>* t);

    bool literal(vector<Token>* t);
    bool literal(vector<Token>* t, string s);
    bool relationName(vector<Token>* t);
    bool identifier(vector<Token>* t);
    bool expression(vector<Token>* t);


    bool atomicExpr(vector<Token>* t);
    bool selectionExpr(vector<Token>* t);
    bool projectionExpr(vector<Token>* t);
    bool renamingExpr(vector<Token>* t);
    bool unionExpr(vector<Token>* t);
    bool differenceExpr(vector<Token>* t);
    bool productExpr(vector<Token>* t);


    bool condition(vector<Token>* t);
    bool conjunction(vector<Token>* t);
    bool comparison(vector<Token>* t);
    bool op(vector<Token>* t);
    bool operand(vector<Token>* t);
    bool attributeName(vector<Token>* t);
    bool attributeList(vector<Token>* t);

    bool openCmd(vector<Token>* t);
    bool closeCmd(vector<Token>* t);
    bool writeCmd(vector<Token>* t);
    bool exitCmd(vector<Token>* t);
    bool showCmd(vector<Token>* t);
    bool createCmd(vector<Token>* t);
    bool updateCmd(vector<Token>* t);
    bool insertCmd(vector<Token>* t);
    bool deleteCmd(vector<Token>* t);
};

#endif
