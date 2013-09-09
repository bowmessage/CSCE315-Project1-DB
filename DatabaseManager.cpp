#include <algorithm>
#include "DatabaseManager.h"

using namespace std;


DatabaseManager::DatabaseManager(){

}

DatabaseManager::~DatabaseManager(){
}


//For the file management part of things.. not yet.
//Returns with success value
/*bool DatabaseManager::openRelation(string r){
  if(currentRelation == NULL){
    currentRelation = database.getRelationByName(r);
    return currentRelation != NULL;
  }
  else{
    return false;
  }
}

bool DatabaseManager::closeRelation(string r){
  if(currentRelation != NULL){
    currentRelation = NULL;
    return true;
  }
  else{
    return false;
  }
}*/

bool DatabaseManager::createTable(string name, vector<Attribute> attributes, vector<Attribute*> keys){
  if(database.getRelationByName(name) == NULL){
    database.addRelation(Relation(name, attributes, keys));
    return true;
  } else return false;
}

bool DatabaseManager::insertInto(string name, vector<string> literals){
  Relation* curRelation = database.getRelationByName(name);
  if(curRelation != NULL){
    curRelation->tuples.push_back(literals);
    return true;
  } else return false;
}

bool DatabaseManager::deleteRelation(string name){
  Relation* curRelation = database.getRelationByName(name);
  if(curRelation != NULL){
    database.removeRelation(name);
  }
  else return false;
}

Relation* DatabaseManager::select(string relationName, string op1, string comparison, string op2){
  Relation* curRelation = database.getRelationByName(relationName);
  vector< vector<string> > retTuples;
  if(curRelation != NULL){
    if(comparison == "=="){
      //op1 will be an attribute name..
      int attrIndex = curRelation->getAttributeIndexByName(op1);
      for(int i = 0; i < curRelation->tuples.size(); i++){
        if(curRelation->tuples[i][attrIndex] == op2){
          retTuples.push_back(curRelation->tuples[i]);
        }
      }
      return new Relation(relationName, curRelation->attributes, retTuples);
    }
    else{
      //Comparison string not found
      return NULL;
    }
    //Relation with given name not found
  } else return NULL;
}

Relation* DatabaseManager::project(string relationName, vector<string> attributeNames){
  Relation* curRelation = database.getRelationByName(relationName);
  vector<Attribute> retAttributes;
  vector< vector<string> > retTuples;
  if(curRelation != NULL){
    for(int i = 0; i < curRelation->tuples.size(); i++){
      vector<string> rowToAdd;
      for(int j = 0; j < curRelation->attributes.size(); j++){
        if(find(attributeNames.begin(), attributeNames.end(), curRelation->attributes[j].name) != attributeNames.end()){
          retAttributes.push_back(curRelation->attributes[j]);
          rowToAdd.push_back(curRelation->tuples[i][j]);
        }
      }
      retTuples.push_back(rowToAdd);
    }
    return new Relation(relationName, retAttributes, retTuples);

    //Relation with given name not found
  } else return NULL;
}
