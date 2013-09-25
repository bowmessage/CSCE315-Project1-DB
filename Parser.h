#ifndef PARSER_H_
#define PARSER_H_

#include "Token.h"
#include "DatabaseManager.h"

#include <vector>

using namespace std;

class Parser{
  public:

    Parser();
    Parser(DatabaseManager* m);
    ~Parser();

    DatabaseManager* man;
    int curPos;





    void toUpper(string& in);
    Token tokenAtCurPos(vector<Token>* t);

    void removeFirst();

    bool parse(vector<Token>* t); 

    bool query(vector<Token>* t);
    bool command(vector<Token>* t);

    string literal(vector<Token>* t);
    bool literal(vector<Token>* t, string s);
    string relationName(vector<Token>* t);
    bool identifier(vector<Token>* t);
    Relation* expression(vector<Token>* t);


    Relation* atomicExpr(vector<Token>* t);
    Relation* selectionExpr(vector<Token>* t);
    Relation* projectionExpr(vector<Token>* t);
    Relation* renamingExpr(vector<Token>* t);
    Relation* unionExpr(vector<Token>* t);
    Relation* differenceExpr(vector<Token>* t);
    Relation* productExpr(vector<Token>* t);


    string condition(vector<Token>* t);
    string conjunction(vector<Token>* t);
    string comparison(vector<Token>* t);
    string op(vector<Token>* t);
    string operand(vector<Token>* t);
    bool attributeName(vector<Token>* t);
    vector<Attribute>* attributeList(vector<Token>* t);

    bool openCmd(vector<Token>* t);
    bool closeCmd(vector<Token>* t);
    bool writeCmd(vector<Token>* t);
    bool exitCmd(vector<Token>* t);
    bool showCmd(vector<Token>* t);
    bool createCmd(vector<Token>* t);
    bool updateCmd(vector<Token>* t);
    bool insertCmd(vector<Token>* t);
    bool deleteCmd(vector<Token>* t);

    vector<Attribute>* typedAttributeList(vector<Token>* t);
    string type(vector<Token>* t);
    int* integer(vector<Token>* t);
    vector<string>* literalList(vector<Token>* t);

};

#endif
