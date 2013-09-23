#include "Parser.h"

#include <stdexcept>
#include <algorithm>
#include <string>

Parser::Parser(){
}

Parser::Parser(DatabaseManager* m){
  man = m;
}


Parser::~Parser(){
}


void Parser::removeFirst(vector<Token>* t){
  curPos++;
}

bool Parser::parse(vector<Token>* t){
  curPos = 0;
  return ( query(t) || command(t) ) && literal(t, ";");
  /*if(query(t)){
  }
  else if (command(t)){
  }
  else{
  }*/
}

bool Parser::query(vector<Token>* t){
  string name;
  bool ret = (name=relationName(t) != "") && literal(t, "->") && expression(t);
  //Don't know what to do with atomic expressions.
  
  return ret
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
  string val = t->at(curPos).value;
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

vector<Attribute>* Parser::attributeList(vector<Token>* t){
  //Returns NULL on invalid attribute-list.
  vector<Attribute>* ret = new vector<Attribute>();
  string curName;
  bool validList = false;
  while((curName = attributeName(t)) != ""){
    ret->push_back(Attribute(curName));
    if(!literal(t, ",")){
      validList = true;
      break;
    }
  }
  if(validList){
    return ret;
  }
  else return NULL;
}

bool Parser::literal(vector<Token>* t){
  return true;
}

bool Parser::literal(vector<Token>* t, string s){
  if(t->at(curPos).value == s){
    removeFirst(t);
    return true;
  }
}

string Parser::relationName(vector<Token>* t){
  if(identifier(t)){
    removeFirst(t);
    return true;
  }
}

bool Parser::identifier(vector<Token>* t){
  string val = t->at(curPos).value;
  string upperVal = val;
  toUpper(upperVal);
  if(
    upperVal == "WRITE"
    || upperVal == "DELETE"
    || upperVal == "CREATE"
    || upperVal == "INTO"
    || upperVal == "FROM"
    || upperVal == "TABLE"
    || upperVal == "UPDATE"
    || upperVal == "SHOW"
    || upperVal == "OPEN"
    || upperVal == "CLOSE"
    || upperVal == "EXIT"
    || upperVal == "SELECT"
    || upperVal == "PROJECT"
    || upperVal == "RENAME"
    || upperVal == "SET"
    || upperVal == "CROSS"
    || upperVal == "UNION"
    || upperVal == "DIFFERENCE"
    || upperVal == "PRODUCT"
    || upperVal == "("
    || upperVal == ")"
    || upperVal == "\""
    ) return false;

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

void Parser::toUpper(string& in){
  for(int i = 0; i < in.length(); i++){
    in[i] = toupper(in[i]);
  }
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
  string name;
  vector<Attribute>* typedAttrs, keyAttrs;
  bool ret = literal(t, "CREATE") &&
    literal(t, "TABLE") &&
    (name = relationName(t)) != "" &&
    literal(t, "(") &&
    (typedAttrs = typedAttributeList(t)) != NULL &&
    literal(t, ")") &&
    literal(t, "PRIMARY") &&
    literal(t, "KEY") &&
    literal(t, "(") &&
    (keyAttrs = attributeList(t)) != NULL &&
    literal(t, ")");
  if(ret){
    man.createTable(name, &typedAttrs, &keyAttrs);
  }
  return ret;
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
  int curPosBeforeFirstHalf = curPos;
  bool firstHalf = literal(t, "INSERT") &&
    literal(t, "INTO") &&
    relationName(t) &&
    literal(t, "VALUES") &&
    literalList(t);
  if(!firstHalf){
    curPos = curPosBeforeFirstHalf;
    bool secondHalf = literal(t, "INSERT") &&
    literal(t, "INTO") &&
    relationName(t) &&
    literal(t, "VALUES") &&
    literal(t, "FROM") &&
    literal(t, "RELATION") &&
    expression(t);
    return secondHalf;
  }
  else{
    return true;
  }
}


bool Parser::literalList(vector<Token>* t){
  bool startsRight = literal(t, "(");
    while(literal(t) && literal(t, ",")){}
  return startsRight && literal(t) && literal(t,")");
}

bool Parser::deleteCmd(vector<Token>* t){
  string relationName, condition;
  bool ret = literal(t, "DELETE") &&
    literal(t, "FROM") &&
    relationName(t) &&
    literal(t, "WHERE") &&
    condition(t);
}

vector<Attribute>* Parser::typedAttributeList(vector<Token>* t){
  //Returns NULL on invalid typed-attribute-list.
  vector<Attribute>* ret = new vector<Attribute>();
  string curName, curType;
  bool validList = false;
  while((curName = attributeName(t)) != "" &&
      (curType = type(t)) != ""){
    ret->push_back(Attribute(curName));
    if(!literal(t, ",")){
      validList = true;
      break;
    }
  }
  if(validList){
    return ret;
  }
  else return NULL;
}

bool Parser::type(vector<Token>* t){
  return (literal(t, "VARCHAR") &&
    literal(t, "(") &&
    integer(t) &&
    literal(t, ")")) ||
    (literal(t, "INTEGER"));
}

bool Parser::integer(vector<Token>* t){
  string intVal = t->at(curPos).value;
  for(int i = 0; i < intVal.size(); i++){
    if(!isdigit(intVal.at(i))){
      return false;
    }
  }
}
