#include "Parser.h"

#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <string>
#include <iostream>

#define DEBUG 1

Parser::Parser(){
}

Parser::Parser(DatabaseManager* m){
  man = m;
}


Parser::~Parser(){
}


void Parser::removeFirst(){
  curPos++;
}

bool Parser::parse(vector<Token>* t){
  curPos = 0;
  return ( query(t) || command(t) ) && literal(t, ";");
}

bool Parser::query(vector<Token>* t){
  string name;
  Relation* r = NULL;
  bool ret = ((name=relationName(t)) != "") && literal(t, "->") && ((r = expression(t)) != NULL);
  return ret;
}

Relation* Parser::expression(vector<Token>* t){
  Relation* ret = NULL;
  bool validExpression = (ret = atomicExpr(t)) != NULL ||
    (ret = selectionExpr(t)) != NULL ||
    (ret = projectionExpr(t)) != NULL ||
    (ret = renamingExpr(t)) != NULL ||
    (ret = unionExpr(t)) != NULL ||
    (ret = differenceExpr(t)) != NULL ||
    (ret = productExpr(t)) != NULL;
  return ret;
}

Relation* Parser::atomicExpr(vector<Token>* t){
  int curPosNow = curPos;
  string name;
  bool isARelationName = (name = relationName(t)) != "";
  if(isARelationName){
    return man->database.getRelationByName(name);
  }
  else{
    Relation* ret = NULL;
    bool isAnotherExpression = literal(t, "(") && 
      (ret = expression(t)) != NULL && 
      literal(t, ")");
    return ret;
  }
  curPos = curPosNow;
  return NULL;
}

Relation* Parser::selectionExpr(vector<Token>* t){
  int curPosNow = curPos;
  string cond;
  Relation* r = NULL;
  bool valid = literal(t, "select") &&
    literal(t, "(") &&
    (cond = condition(t)) != "" &&
    literal(t, ")") &&
    (r = atomicExpr(t)) != NULL;
  if(valid){
    //TODO: this cond cond cond is wrong.
    return man->select(r->name, cond, cond, cond);
  }
  else{
    curPos = curPosNow;
    return NULL;
  }
}


Relation* Parser::projectionExpr(vector<Token>* t){
  int curPosNow = curPos;
  vector<Attribute>* attrList = NULL;
  Relation* r = NULL;
  bool valid = literal(t, "project") &&
    literal(t, "(") &&
    (attrList = attributeList(t)) != NULL &&
    literal(t, ")") &&
    (r = atomicExpr(t)) != NULL;
  if(valid){
    vector<string> namesOfAttrs;
    for(int i = 0; i < attrList->size(); i++){
      namesOfAttrs.push_back(attrList->at(i).name);
    }
    return man->project(r->name, namesOfAttrs);
  }
  else{
    curPos = curPosNow;
    return NULL;
  }
}

Relation* Parser::renamingExpr(vector<Token>* t){
  int curPosNow = curPos;
  vector<Attribute>* attrList = NULL;
  Relation* r = NULL;
  bool valid = literal(t, "rename") &&
    literal(t, "(") &&
    (attrList = attributeList(t)) != NULL &&
    literal(t, ")") &&
    (r = atomicExpr(t)) != NULL;
  if(valid){
    vector<string> namesOfAttrs;
    for(int i = 0; i < attrList->size(); i++){
      namesOfAttrs.push_back(attrList->at(i).name);
    }
    bool success = man->rename(r->name, namesOfAttrs);
    if(success){
      return man->database.getRelationByName(r->name);
    }
    else{
      curPos = curPosNow;
      return NULL;
    }
  }
  else{
    curPos = curPosNow;
    return NULL;
  }
}

Relation* Parser::unionExpr(vector<Token>* t){
  Relation* r1 = NULL;
  Relation* r2 = NULL;
  bool isValid = (r1 = atomicExpr(t)) != NULL &&
    literal(t, "+") &&
    (r2 = atomicExpr(t)) != NULL;
  if(isValid){
    return &man->database.setUnion(*r1, *r2);
  } else return NULL;
}

Relation* Parser::differenceExpr(vector<Token>* t){
  Relation* r1 = NULL;
  Relation* r2 = NULL;
  bool isValid = (r1 = atomicExpr(t)) != NULL &&
    literal(t, "-") &&
    (r2 = atomicExpr(t)) != NULL;
  if(isValid){
    return &man->database.setDifference(*r1, *r2);
  } else return NULL;
}

Relation* Parser::productExpr(vector<Token>* t){
  Relation* r1 = NULL;
  Relation* r2 = NULL;
  bool isValid = (r1 = atomicExpr(t)) != NULL &&
    literal(t, "*") &&
    (r2 = atomicExpr(t)) != NULL;
  if(isValid){
    return &man->database.setProduct(*r1, *r2);
  } else return NULL;
}

string Parser::condition(vector<Token>* t){
  string comp1, comp2;
  if((comp1 = comparison(t)) != ""){
    int curPosNow = curPos;
    if(literal(t, "||") && (comp2 = comparison(t)) != ""){
      stringstream ss;
      ss << comp1 << " && " << comp2;
      return ss.str();
    }
    else{
      curPos = curPosNow;
      return comp1;
    }
  }
  else return "";
}

string Parser::conjunction(vector<Token>* t){
  string comp1, comp2;
  if((comp1 = comparison(t)) != ""){
    int curPosNow = curPos;
    if(literal(t, "&&") && (comp2 = comparison(t)) != ""){
      stringstream ss;
      ss << comp1 << " && " << comp2;
      return ss.str();
    }
    else{
      curPos = curPosNow;
      return comp1;
    }
  }
  else return "";
}

string Parser::comparison(vector<Token>* t){
  string op1, op2, oper;
  bool isValid = (op1 = operand(t)) != "" &&
    (oper = op(t)) != "" &&
    (op2 = operand(t)) != "";
  if(isValid){
    stringstream ss;
    ss << op1 << " " << oper << " " << op2;
    return ss.str();
  }
  else return "";
}

string Parser::op(vector<Token>* t){
  string val = tokenAtCurPos(t).value;
  if(val == "==" ||
      val == "!=" ||
      val == "<" ||
      val == ">" ||
      val == "<=" ||
      val == ">="){
    removeFirst();
    return val;
  }
  else return "";
}

string Parser::operand(vector<Token>* t){
  string name;
  bool isValid = (name = attributeName(t)) != "" ||
    (name = literal(t)) != "";
  if(isValid){
    return name;
  }
  else return "";
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

string Parser::literal(vector<Token>* t){
  string ret = tokenAtCurPos(t).value;
  removeFirst();
  return ret;
}

bool Parser::literal(vector<Token>* t, string s){
  if(tokenAtCurPos(t).value == s){
    removeFirst();
    return true;
  }
  else return false;
}

string Parser::relationName(vector<Token>* t){
  if(DEBUG){
    cout << "Relation Name Test... curPos: " << curPos << ".\n";
  }
  if(identifier(t)){
    string ret = tokenAtCurPos(t).value;
    removeFirst();
    return ret;
  }
  return "";
}

Token Parser::tokenAtCurPos(vector<Token>* t){
  int lim = t->size();
  if(curPos >= lim){
    return Token();
  }
  else return t->at(curPos);
}

bool Parser::identifier(vector<Token>* t){
  if(DEBUG){
    std::cout << "Identifier test... curPos: " << curPos << ".\n";
    std::cout << "Value is: " << tokenAtCurPos(t).value << ".\n";
  }
  string val = tokenAtCurPos(t).value;
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
  int curPosNow = curPos;
  string name;
  bool isValid =  literal(t, "OPEN") &&
    (name = relationName(t)) != "";
  if(isValid){
    return true;
  }
  else {
    curPos = curPosNow;
    return false;
  }
}
bool Parser::closeCmd(vector<Token>* t){
  int curPosNow = curPos;
  string name;
  bool isValid = literal(t, "CLOSE") &&
    (name = relationName(t)) != "";
  if(isValid){
    return true;
  }
  else{
    curPos = curPosNow;
    return false;
  }
}
bool Parser::writeCmd(vector<Token>* t){
  int curPosNow = curPos;
  string name;
  bool isValid = literal(t, "WRITE") &&
    (name = relationName(t)) != "";
  if(isValid){
    return true;
  }
  else{
    curPos = curPosNow;
  }
}
bool Parser::exitCmd(vector<Token>* t){
  int curPosNow = curPos;
  bool isValid = literal(t, "EXIT");
  if(isValid){
    return true;
  }
  else{
    curPos = curPosNow;
    return false;
  }
}
bool Parser::showCmd(vector<Token>* t){
  int curPosNow = curPos;
  bool isValid = literal(t, "SHOW") &&
    atomicExpr(t);
  if(isValid){
    return true;
  }
  else{
    curPos = curPosNow;
    return false;
  }
}
bool Parser::createCmd(vector<Token>* t){
  int curPosNow = curPos;
  string name;
  vector<Attribute>* typedAttrs;
  vector<Attribute>* keyAttrs;
  bool isValid = literal(t, "CREATE") &&
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
  if(isValid){
    man->createTable(name, *typedAttrs, *keyAttrs);
    return true;
  }
  else{
    curPos = curPosNow;
    return false;
  }
}
bool Parser::updateCmd(vector<Token>* t){
  int curPosNow = curPos;
  string name;
  bool isValid =  literal(t, "UPDATE") &&
    (name = relationName(t)) != "" &&
    literal(t, "SET") &&
    attributeName(t) &&
    literal(t, "=") &&
    (literal(t) != "") &&
    literal(t, "WHERE") &&
    (condition(t) != "");
  if(isValid){
    return true;
  }
  else{
    curPos = curPosNow;
    return false;
  }
}
bool Parser::insertCmd(vector<Token>* t){
  int curPosBeforeFirstHalf = curPos;
  string relation1, relation2;
  Relation* expr;
  vector<string>* literals;
  bool firstHalf = literal(t, "INSERT") &&
    literal(t, "INTO") &&
    (relation1 = relationName(t)) != "" &&
    literal(t, "VALUES") &&
    (literals = literalList(t)) != NULL;
  if(!firstHalf){
    curPos = curPosBeforeFirstHalf;
    bool secondHalf = literal(t, "INSERT") &&
    literal(t, "INTO") &&
    (relation2 = relationName(t)) != "" &&
    literal(t, "VALUES") &&
    literal(t, "FROM") &&
    literal(t, "RELATION") &&
    (expr = expression(t)) != NULL;
    if(secondHalf){
      vector< vector<string> > add = expr->tuples;
      Relation* addTo = man->database.getRelationByName(relation2);
      for(int i = 0; i < add.size(); i++){
        addTo->tuples.push_back(add[i]);
      }
    }
  }
  else{
    man->insertInto(relation1, *literals);
    return firstHalf;
  }
  //Getting to this line means not first half nor second.
  curPos = curPosBeforeFirstHalf;
  return false;
}


vector<string>* Parser::literalList(vector<Token>* t){
  //Returns NULL on invalid literal-list.
  vector<string>* ret = new vector<string>();
  bool startsRight = literal(t, "(");
  bool validList = false;
    while(literal(t) != ""){
      if(!literal(t, ",")) {
        validList = true;
        break;
      }
    }
  if(startsRight && validList && literal(t,")")){
    return ret;
  }
  else return NULL;
}

bool Parser::deleteCmd(vector<Token>* t){
  //TODO fix this
  string name;
  string cond;
  bool ret = literal(t, "DELETE") &&
    literal(t, "FROM") &&
    (name = relationName(t)) != "" &&
    literal(t, "WHERE") &&
    (cond = condition(t)) != "";
  return ret;
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

string Parser::type(vector<Token>* t){
  bool firstHalf = literal(t, "VARCHAR") &&
    literal(t, "(") &&
    integer(t) &&
    literal(t, ")");
  if(!firstHalf){
    if(literal(t, "INTEGER")){
      return string("INTEGER");
    }
  }
  else{
    return string("VARCHAR");
  }
  return string("");
}

int* Parser::integer(vector<Token>* t){
  //Returns null on invalid integer
  string intStr = tokenAtCurPos(t).value;
  for(int i = 0; i < intStr.size(); i++){
    if(!isdigit(intStr.at(i) || i == 0 && !isdigit(intStr.at(i)) && intStr.at(i) != '-')){
      return NULL;
    }
  }
  int* ret = new int(atoi(intStr.c_str()));
  return ret;
}
