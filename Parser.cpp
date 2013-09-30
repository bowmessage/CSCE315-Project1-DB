#include "Parser.h"

#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <string>
#include <iostream>

#define DEBUG 1

Parser::Parser(){
  man = new DatabaseManager();
}

Parser::Parser(DatabaseManager* m){
  man = m;
}


Parser::~Parser(){
  delete man;
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
  bool ret = ((name=relationName(t)) != "") && literal(t, "<-") && ((r = expression(t)) != NULL);
  if(ret){
    cout << "asdf adding relation r..." << (void*) r << "\n";
    r->name = name;
    man->database.addRelation(*r);
    return true;
  }
  else return false;
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
  if(DEBUG){
    cout << "atomic expr check: is relation name: " << isARelationName << "\n";
  }
  if(isARelationName){
    if(DEBUG){
      cout << "PTR RET: " << (void*) man->database.getRelationByName(name) << "\n";
    }
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
  vector<Token>* cond;
  Relation* r = NULL;
  bool valid = literal(t, "select") &&
    literal(t, "(") &&
    (cond = condition(t)) != NULL &&
    literal(t, ")") &&
    (r = atomicExpr(t)) != NULL;
  if(valid){
    Relation* ret = NULL;
    Relation* tmp = NULL;
    string curOp1, curOperator, curOp2;
    for(int i = 0; i < cond->size(); i++){
      cout << "ret: " << (void*) ret << "\n";
      cout << "tmp: " << (void*) tmp << "\n";
      cout << "i: " << i << "\n";
      if((i+1) % 4 == 0){
        tmp = man->select(r->name, curOp1, curOperator, curOp2);
        //This is a && or ||... decide
        if(cond->at(i).value == "||"){
          if(ret == NULL){
            ret = tmp;
          }
          else{
            ret = man->database.setUnion(*ret, *tmp);
          }
        }
        else if(cond->at(i).value == "&&"){
          if(ret == NULL){
            ret = tmp;
          }
          else{
            ret = man->database.setDifference(*ret, *tmp);
          }
        }
      }
      else{
        curOp1 = cond->at(i).value; i++;
        curOperator = cond->at(i).value; i++;
        curOp2 = cond->at(i).value;
      }
    }
    if(ret == NULL){
      ret = man->select(r->name, curOp1, curOperator, curOp2);
    }
    cout << "Return ret... " << (void*) ret << "\n";
    return ret;
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
    return man->database.setUnion(*r1, *r2);
  } else return NULL;
}

Relation* Parser::differenceExpr(vector<Token>* t){
  Relation* r1 = NULL;
  Relation* r2 = NULL;
  bool isValid = (r1 = atomicExpr(t)) != NULL &&
    literal(t, "-") &&
    (r2 = atomicExpr(t)) != NULL;
  if(isValid){
    return man->database.setDifference(*r1, *r2);
  } else return NULL;
}

Relation* Parser::productExpr(vector<Token>* t){
  Relation* r1 = NULL;
  Relation* r2 = NULL;
  bool isValid = (r1 = atomicExpr(t)) != NULL &&
    literal(t, "*") &&
    (r2 = atomicExpr(t)) != NULL;
  if(isValid){
    return man->database.setProduct(*r1, *r2);
  } else return NULL;
}

vector<Token>* Parser::condition(vector<Token>* t){
  vector<Token>* comp1;
  vector<Token>* comp2;
  vector<Token>* ret = new vector<Token>();
  if((comp1 = comparison(t)) != NULL){
    int curPosNow = curPos;
    ret->insert(ret->end(), comp1->begin(), comp1->end());
    if(literal(t, "||") && (comp2 = comparison(t)) != NULL){
      ret->push_back(Token("||"));
      ret->insert(ret->end(), comp2->begin(), comp2->end());
      return ret;
    }
    else{
      curPos = curPosNow;
      return comp1;
    }
  }
  else return NULL;
}

vector<Token>* Parser::conjunction(vector<Token>* t){
  vector<Token>* comp1;
  vector<Token>* comp2;
  vector<Token>* ret = new vector<Token>();
  if((comp1 = comparison(t)) != NULL){
    int curPosNow = curPos;
    ret->insert(ret->end(), comp1->begin(), comp1->end());
    if(literal(t, "&&") && (comp2 = comparison(t)) != NULL){
      ret->push_back(Token("&&"));
      ret->insert(ret->end(), comp2->begin(), comp2->end());
      return ret;
    }
    else{
      curPos = curPosNow;
      return ret;
    }
  }
  else return NULL;
}

vector<Token>* Parser::comparison(vector<Token>* t){
  int curPosNow = curPos;
  string op1, op2, oper;
  bool isValid = (op1 = operand(t)) != "" &&
    (oper = op(t)) != "" &&
    (op2 = operand(t)) != "";
  if(isValid){
    vector<Token>* ret = new vector<Token>();
    ret->push_back(Token(op1));
    ret->push_back(Token(oper));
    ret->push_back(Token(op2));
    return ret;
  }
  else{
    curPos = curPosNow;
    return NULL;
  }
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

string Parser::attributeName(vector<Token>* t){
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
  if(DEBUG){
    cout << "Seeing if pos " << curPos << " == literal value of any kind.\n";
  }
  string ret = tokenAtCurPos(t).value;
  removeFirst();
  return ret;
}

bool Parser::literal(vector<Token>* t, string s){
  if(DEBUG){
    cout << "Seeing if pos " << curPos << " == " << s << "\n";
  }
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
  return identifier(t);
}

Token Parser::tokenAtCurPos(vector<Token>* t){
  int lim = t->size();
  if(curPos >= lim){
    return Token();
  }
  else return t->at(curPos);
}

string Parser::identifier(vector<Token>* t){
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
    || upperVal == "INSERT"
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
    ) return "";

  for(int i = 0; i < val.size(); i++){
    if(i == 0){
      if(!isalpha(val[i])){
        return "";
        //throw runtime_error("Identifier must start with alpha.");
      }
    }
    else{
      if(!isalnum(val[i]) && val[i] != '_'){
        return "";
        //throw runtime_error("Identifier must be alphanumeric.");
      }
    }
  }
  removeFirst();
  return val;
}

void Parser::toUpper(string& in){
  for(int i = 0; i < in.length(); i++){
    in[i] = toupper(in[i]);
  }
}


bool Parser::command(vector<Token>* t){
  if(DEBUG){
    cout << "Testing if command...\n";
  }
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
    return false;
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
  Relation* toShow;
  bool isValid = literal(t, "SHOW") &&
    (toShow = atomicExpr(t)) != NULL;
  if(isValid){
    man->show(toShow->name);
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
    if(DEBUG){
      cout << "typed Attrs size: " << typedAttrs->size() << "\n";
      cout << "key Attrs size: " << keyAttrs->size() << "\n";
      cout << "Table Name: " << name << "\n";
    }
    man->createTable(name, *typedAttrs, *keyAttrs);
    //delete typedAttrs;
    //TODO: decide if we need these deletes here and elsewhere
    //delete keyAttrs;
    return true;
  }
  else{
    curPos = curPosNow;
    return false;
  }
}
bool Parser::updateCmd(vector<Token>* t){
  int curPosNow = curPos;
  string rName, aName;
  string lit;
  vector<Token>* cond;
  bool isValid =  literal(t, "UPDATE") &&
    (rName = relationName(t)) != "" &&
    literal(t, "SET") &&
    (aName = attributeName(t)) != "" &&
    literal(t, "=") &&
    (lit = literal(t)) != "" &&
    literal(t, "WHERE") &&
    ((cond = condition(t)) != NULL);
  if(isValid){
    Relation* toUpdate = man->database.getRelationByName(rName);
    if(toUpdate == NULL){
      return NULL;
    }

    Relation* ret = NULL;
    Relation* tmp = NULL;
    string curOp1, curOperator, curOp2;
    for(int i = 0; i < cond->size(); i++){
      if((i+1) % 4 == 0){
        tmp = man->select(rName, curOp1, curOperator, curOp2);
        //This is a && or ||... decide
        if(cond->at(i).value == "||"){
          if(ret == NULL){
            ret = tmp;
          }
          else{
            ret = man->database.setUnion(*ret, *tmp);
          }
        }
        else if(cond->at(i).value == "&&"){
          if(ret == NULL){
            ret = tmp;
          }
          else{
            ret = man->database.setDifference(*ret, *tmp);
          }
        }
      }
      else{
        curOp1 = cond->at(i).value; i++;
        curOperator = cond->at(i).value; i++;
        curOp2 = cond->at(i).value;
      }
    }
    if(ret == NULL){
      ret = man->select(rName, curOp1, curOperator, curOp2);
    }

    for(int i = 0; i < ret->tuples.size(); i++){
      for(int j = 0; j < toUpdate->tuples.size(); j++){
        if(ret->tuples.at(i) == toUpdate->tuples.at(j)){
          int index = toUpdate->getAttributeIndexByName(aName);
          toUpdate->tuples.at(j).at(index) = lit;
        }
      }
    }

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
    literal(t, "FROM") &&
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
  string nextLiteral;
    while((nextLiteral = literal(t)) != ""){
      ret->push_back(nextLiteral);
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
  vector<Token>* cond;
  bool ret = literal(t, "DELETE") &&
    literal(t, "FROM") &&
    (name = relationName(t)) != "" &&
    literal(t, "WHERE") &&
    (cond = condition(t)) != NULL;
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
  int varcharLen = -1;
  bool firstHalf = literal(t, "VARCHAR") &&
    literal(t, "(") &&
    (varcharLen = *integer(t)) != NULL &&
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
    if(!isdigit(intStr.at(i))){
      return NULL;
    }
  }
  int* ret = new int(atoi(intStr.c_str()));
  removeFirst();
  return ret;
}
