#include <algorithm>
#include <iostream>
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

void DatabaseManager::show(string name){
   Relation* curRelation = database.getRelationByName(name);
   if(curRelation == NULL){
	  cout <<"Relation does not exist" << endl;
	  return;
   }
   cout << "|			" << name << "			|" << endl;
   for(int i = 0; i < curRelation->tuples.size(); j++){
      for(int j = 0; j < curRelation->tuples[i].size(); i++){
	     cout << "|" << curRelation->tuples[i][j] << " ";
	  }
   }
   return;
}

void DatabaseManager::rename(vector<string> newNames, Relation r){
	for(int i = 0; i < r.attributes.size(); i++){
		r.attributes[i].name = newNames[i];
	}
	return;
}

vector< vector<string> >* DatabaseManager::select(string relationName, string op1, string comparison, string op2){
  Relation* curRelation = database.getRelationByName(relationName);
  vector< vector<string> >* ret = new vector< vector<string> >();
  if(curRelation != NULL){
    if(comparison == "=="){
      //op1 will be an attribute name..
      int attrIndex = curRelation->getAttributeIndexByName(op1);
      for(int i = 0; i < curRelation->tuples.size(); i++){
        if(curRelation->tuples[i][attrIndex] == op2){
          ret->push_back(curRelation->tuples[i]);
        }
      }
      return ret;
    }
    else{
      //Comparison string not found
      return NULL;
    }
    //Relation with given name not found
  } else return NULL;
}

vector< vector<string> >* DatabaseManager::project(string relationName, vector<string> attributeNames){
  Relation* curRelation = database.getRelationByName(relationName);
  vector< vector<string> >* ret = new vector< vector<string> >();
  if(curRelation != NULL){
    for(int i = 0; i < curRelation->tuples.size(); i++){
      vector<string> rowToAdd;
      for(int j = 0; j < curRelation->attributes.size(); j++){
        if(find(attributeNames.begin(), attributeNames.end(), curRelation->attributes[j].name) != attributeNames.end()){
          rowToAdd.push_back(curRelation->tuples[i][j]);
        }
      }
      ret->push_back(rowToAdd);
    }
    return ret;

    //Relation with given name not found
  } else return NULL;
}
