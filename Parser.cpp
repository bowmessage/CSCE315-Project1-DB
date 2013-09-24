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
  Relation* r = NULL;
  bool ret = (name=relationName(t) != "") && literal(t, "->") && (r = expression(t)) != NULL;
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
  string relationName;
  bool isARelationName = (relationName = relationName(t)) != "";
  if(isARelationName){
    return man->getRelationByName(relationName);
  }
  else{
    Relation* ret = NULL;
    bool isAnotherExpression = literal(t, "(") && 
      (ret = expression(t)) != NULL && 
      literal(t, ")");
    return ret;
  }
  return NULL;
}

Relation* Parser::selectionExpr(vector<Token>* t){
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
  else return NULL;
}


Relation* Parser::projectionExpr(vector<Token>* t){
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
    return man->select(r->name, namesOfAttrs);
  }
  else return NULL;
}

Relation* Parser::renamingExpr(vector<Token>* t){
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
    return man->rename(r->name, namesOfAttrs);
  }
  else return NULL;
}

Relation* Parser::unionExpr(vector<Token>* t){
  Relation* r1 = NULL;
  Relation* r2 = NULL;
  bool isValid = (r1 = atomicExpr(t)) != NULL &&
    literal(t, "+") &&
    (r2 = atomicExpr(t)) != NULL;
  if(valid){
    return * man->database.setUnion(&r1, &r2);
  } else return NULL;
}

Relation* Parser::differenceExpr(vector<Token>* t){
  Relation* r1 = NULL;
  Relation* r2 = NULL;
  bool isValid = (r1 = atomicExpr(t)) != NULL &&
    literal(t, "-") &&
    (r2 = atomicExpr(t)) != NULL;
  if(valid){
    return * man->database.setDifference(&r1, &r2);
  } else return NULL;
}

Relation* Parser::productExpr(vector<Token>* t){
  Relation* r1 = NULL;
  Relation* r2 = NULL;
  bool isValid = (r1 = atomicExpr(t)) != NULL &&
    literal(t, "*") &&
    (r2 = atomicExpr(t)) != NULL;
  if(valid){
    return * man->database.setProduct(&r1, &r2);
  } else return NULL;
}

string Parser::condition(vector<Token>* t){
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

string Parser::literal(vector<Token>* t){
  return t->at(curPos).value;
}

bool Parser::literal(vector<Token>* t, string s){
  if(t->at(curPos).value == s){
    removeFirst(t);
    return true;
  }
}

string Parser::relationName(vector<Token>* t){
  if(identifier(t)){
    string ret = t->at(curPos).value;
    removeFirst(t);
    return ret;
  }
  return "";
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
  string name;
  return literal(t, "OPEN") &&
    (name = relationName(t)) != "";
}
bool Parser::closeCmd(vector<Token>* t){
  string name;
  return literal(t, "CLOSE") &&
    (name = relationName(t)) != "";
}
bool Parser::writeCmd(vector<Token>* t){
  string name;
  return literal(t, "WRITE") &&
    (name = relationName(t)) != "";
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
  vector<Attribute>* typedAttrs;
  vector<Attribute>* keyAttrs;
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
    man->createTable(name, &typedAttrs, &keyAttrs);
  }
  return ret;
}
bool Parser::updateCmd(vector<Token>* t){
  string relationName;
  return literal(t, "UPDATE") &&
    (relationName = relationName(t)) != "" &&
    literal(t, "SET") &&
    attributeName(t) &&
    literal(t, "=") &&
    literal(t) &&
    literal(t, "WHERE") &&
    condition(t);
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
      man->database.getRelationByName(relation2)->tuples.pushback(expr -> tuples);
    }
    return secondHalf;
  }
  else{
    man->insertInto(relation1, literals);
    return firstHalf;
  }
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
  string relationName;
  string condition;
  bool ret = literal(t, "DELETE") &&
    literal(t, "FROM") &&
    (relationName = relationName(t)) != "" &&
    literal(t, "WHERE") &&
    (condition = condition(t)) != "";
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
  string intStr = t->at(curPos).value;
  for(int i = 0; i < intStr.size(); i++){
    if(!isdigit(intStr.at(i) || i == 0 && !isdigit(intStr.at(i)) && intStr.at(i) != '-')){
      return NULL;
    }
  }
  int* ret = new int;
  ret = &atoi(intStr.c_str());
  return ret;
}
