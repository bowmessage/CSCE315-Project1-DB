#include "Parser.h"

#include <stdexcept>
#include <string>

Parser::Parser(){
}

Parser::~Parser(){}


void Parser::removeFirst(vector<Token>* t){
  t->erase(t->begin());
}

bool Parser::parse(vector<Token>* t){
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
}
