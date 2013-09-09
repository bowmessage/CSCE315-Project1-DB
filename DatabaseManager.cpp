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
  } else return false;
}

//bool DatabaseManager::update(string name, v
