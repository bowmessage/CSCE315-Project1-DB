#include "Parser.h"

#include <stdexcept>
#include <string>

Parser::Parser(){
  extractTokens = new vector<Token>();
}


Parser::~Parser(){
  delete extractTokens;
}


void Parser::removeFirst(vector<Token>* t){
  extractTokens->push_back(t->at(0));
  t->erase(t->begin());
}

bool Parser::parse(vector<Token>* t){
  extractTokens->clear();
  return ( query(t) || command(t) ) && literal(t, ";");
  /*if(query(t)){
  }
  else if (command(t)){
  }
  else{
  }*/
}

bool Parser::query(vector<Token>* t){
  return relationName(t) && literal(t, "->") && expression(t);
}

bool Parser::expression(vector<Token>* t){
  return atomicExpr(t) ||
    selectionExpr(t) ||
    projectionExpr(t) ||
    renamingExpr(t) ||
    unionExpr(t) ||
    differenceExpr(t) ||
    productExpr(t);
}

bool Parser::atomicExpr(vector<Token>* t){
  return relationName(t) || ( literal(t, "(") && expression(t) && literal(t, ")"));
}

bool Parser::selectionExpr(vector<Token>* t){
  return literal(t, "select") &&
    literal(t, "(") &&
    condition(t) &&
    literal(t, ")") &&
    atomicExpr(t);
}


bool Parser::projectionExpr(vector<Token>* t){
  return literal(t, "project") &&
    literal(t, "(") &&
    attributeList(t) &&
    literal(t, ")") &&
    atomicExpr(t);
}

bool Parser::renamingExpr(vector<Token>* t){
  return literal(t, "rename") &&
    literal(t, "(") &&
    attributeList(t) &&
    literal(t, ")") &&
    atomicExpr(t);
}

bool Parser::unionExpr(vector<Token>* t){
  return atomicExpr(t) &&
    literal(t, "+") &&
    atomicExpr(t);
}

bool Parser::differenceExpr(vector<Token>* t){
  return atomicExpr(t) &&
    literal(t, "-") &&
    atomicExpr(t);
}

bool Parser::productExpr(vector<Token>* t){
  return atomicExpr(t) &&
    literal(t, "*") &&
    atomicExpr(t);
}

bool Parser::condition(vector<Token>* t){
  if(conjunction(t)){
    if(literal(t, "||")){
      return conjunction(t);
    }
    return true;
  }
  else{
    return false;
  }
}

bool Parser::conjunction(vector<Token>* t){
  if(comparison(t)){
    if(literal(t, "&&")){
      return comparison(t);
    }
    return true;
  }
  else{
    return false;
  }
}

bool Parser::comparison(vector<Token>* t){
  return operand(t) &&
    op(t) &&
    operand(t);
}

bool Parser::op(vector<Token>* t){
  string val = t->at(0).value;
  if(val == "==" ||
      val == "!=" ||
      val == "<" ||
      val == ">" ||
      val == "<=" ||
      val == ">="){
    removeFirst(t);
    return true;
  }
  else return false;
}

bool Parser::operand(vector<Token>* t){
  return attributeName(t) || literal(t);
}

bool Parser::attributeName(vector<Token>* t){
  return identifier(t);
}

bool Parser::attributeList(vector<Token>* t){
  bool startsWithAttr = attributeName(t);
  bool keepChecking = true;
  bool nextIsComma = false;
  bool nextIsAttrName = false;
  while(keepChecking){
    nextIsComma = literal(t, ",");
    nextIsAttrName = attributeName(t);
    keepChecking = nextIsComma && nextIsAttrName;
  }
  return startsWithAttr && nextIsComma == false && nextIsAttrName == false;
}

bool Parser::literal(vector<Token>* t){
  return true;
}

bool Parser::literal(vector<Token>* t, string s){
  if(t->at(0).value == s){
    removeFirst(t);
    return true;
  }
}

bool Parser::relationName(vector<Token>* t){
  if(identifier(t)){
    removeFirst(t);
    return true;
  }
}

bool Parser::identifier(vector<Token>* t){
  string val = t->at(0).value;
  for(int i = 0; i < val.size(); i++){
    if(i == 0){
      if(!isalpha(val[i])){
        throw runtime_error("Identifier must start with alpha.");
      }
    }
    else{
      if(!isalnum(val[i])){
        throw runtime_error("Identifier must be alphanumeric.");
      }
    }
  }
  return true;
}


bool Parser::command(vector<Token>* t){
  return openCmd(t) ||
    closeCmd(t) ||
    writeCmd(t) ||
    exitCmd(t) ||
    showCmd(t) ||
    createCmd(t) ||
    updateCmd(t) ||
    insertCmd(t) ||
    deleteCmd(t);
}

bool Parser::openCmd(vector<Token>* t){
  return literal(t, "OPEN") &&
    relationName(t);
}
bool Parser::closeCmd(vector<Token>* t){
  return literal(t, "CLOSE") &&
    relationName(t);
}
bool Parser::writeCmd(vector<Token>* t){
  return literal(t, "WRITE") &&
    relationName(t);
}
bool Parser::exitCmd(vector<Token>* t){
  return literal(t, "EXIT");
}
bool Parser::showCmd(vector<Token>* t){
  return literal(t, "SHOW") &&
    atomicExpr(t);
}
bool Parser::createCmd(vector<Token>* t){
  return literal(t, "CREATE") &&
    literal(t, "TABLE") &&
    relationName(t) &&
    literal(t, "(") &&
    typedAttributeList(t) &&
    literal(t, ")") &&
    literal(t, "PRIMARY") &&
    literal(t, "KEY") &&
    literal(t, "(") &&
    attributeList(t) &&
    literal(t, ")");
}
bool Parser::updateCmd(vector<Token>* t){
  return literal(t, "UPDATE") &&
    relationName(t) &&
    literal(t, "SET") &&
    attributeName(t) &&
    literal(t, "=") &&
    literal(t) &&
    literal(t, "WHERE") &&
    condition(t);
}
bool Parser::insertCmd(vector<Token>* t){
  return (literal(t, "INSERT") &&
    literal(t, "INTO") &&
    relationName(t) &&
    literal(t, "VALUES") &&
    literalList(t)) ||

    (literal(t, "INSERT") &&
    literal(t, "INTO") &&
    relationName(t) &&
    literal(t, "VALUES") &&
    literal(t, "FROM") &&
    literal(t, "RELATION") &&
    expression(t));
}


bool Parser::literalList(vector<Token>* t){
  bool startsRight = literal(t, "(");
    while(literal(t) && literal(t, ",")){}
  return startsRight && literal(t) && literal(t,")");
}

bool Parser::deleteCmd(vector<Token>* t){
  return literal(t, "DELETE") &&
    literal(t, "FROM") &&
    relationName(t) &&
    literal(t, "WHERE") &&
    condition(t);
}

bool Parser::typedAttributeList(vector<Token>* t){
  bool firstPair = attributeName(t) && type(t);
  while(literal(t,",") && attributeName(t) && type(t)){}
  return firstPair;
}

bool Parser::type(vector<Token>* t){
  return (literal(t, "VARCHAR") &&
    literal(t, "(") &&
    integer(t) &&
    literal(t, ")")) ||
    (literal(t, "INTEGER"));
}

bool Parser::integer(vector<Token>* t){
  string intVal = t->at(0).value;
  for(int i = 0; i < intVal.size(); i++){
    if(!isdigit(intVal.at(i))){
      return false;
    }
  }
}

string* Parser::extract(){
  return extractTokens->front().value;
}
