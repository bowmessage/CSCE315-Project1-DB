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

bool DatabaseManager::createTable(string name, vector<Attribute> attributes, vector<Attribute> keys){
  if(database.getRelationByName(name) == NULL){
    vector<Attribute*> keyPointers;
    for(int i = 0; i < keys.size(); i++){
      keyPointers.push_back(&keys[i]);
    }
    database.addRelation(Relation(name, attributes, keyPointers));
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

bool DatabaseManager::deleteTable(string name){
  Relation* curRelation = database.getRelationByName(name);
  if(curRelation != NULL){
    database.removeRelation(name);
  }
  else return false;
}

void outputSpaces(int i){
	for(int j = i; j >= 0; j--){
		cout << " ";
	}
}

void DatabaseManager::show(string name){
   Relation* curRelation = database.getRelationByName(name);
   if(curRelation == NULL){
	  cout <<"Relation does not exist" << endl;
	  return;
   }
   cout << "***********" << name << "***********" << endl;
   for(int i = 0; i < curRelation->attributes.size(); i++){
     cout << "|" << curRelation->attributes[i].name;
	 int x = curRelation->attributes[i].name.size();
	 outputSpaces(20-x);
   }
   cout << "\n======================================\n";
   for(int i = 0; i < curRelation->tuples.size(); i++){
      for(int j = 0; j < curRelation->tuples[i].size(); j++){
	     cout << "|" << curRelation->tuples[i][j];
		 int x = curRelation->tuples[i][j].size();
		 
		 outputSpaces(20-x);
	  }cout << "\n";
   }
   return;
}

void DatabaseManager::show(Relation* r){
   if(r == NULL){
	  cout <<"Relation does not exist" << endl;
	  return;
   }
   cout << "***********" << r->name << "***********" << endl;
   for(int i = 0; i < r->attributes.size(); i++){
     cout << "|" << r->attributes[i].name;
	 int x = r->attributes[i].name.size();
	 outputSpaces(20-x);
   }
   cout << "\n======================================\n";
   for(int i = 0; i < r->tuples.size(); i++){
      for(int j = 0; j < r->tuples[i].size(); j++){
	     cout << "|" << r->tuples[i][j];
		 int x = r->tuples[i][j].size();
		 outputSpaces(20-x);
	  }cout << "\n";
   }
   return;
}

bool DatabaseManager::rename(string name, vector<string> newNames){
  Relation* curRelation = database.getRelationByName(name);
  if(curRelation != NULL){
    for(int i = 0; i < curRelation->attributes.size(); i++){
      curRelation->attributes[i].name = newNames[i];
    }
    return true;
  } else return false;
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
    else if(comparison == ">"){
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
    for(int i = 0; i < curRelation->attributes.size(); i++){
        if(find(attributeNames.begin(), attributeNames.end(), curRelation->attributes[i].name) != attributeNames.end()){
          retAttributes.push_back(curRelation->attributes[i]);
        }
    }
    for(int i = 0; i < curRelation->tuples.size(); i++){
      vector<string> rowToAdd;
      for(int j = 0; j < curRelation->attributes.size(); j++){
        if(find(attributeNames.begin(), attributeNames.end(), curRelation->attributes[j].name) != attributeNames.end()){
          rowToAdd.push_back(curRelation->tuples[i][j]);
        }
      }
      retTuples.push_back(rowToAdd);
    }
    return new Relation(relationName, retAttributes, retTuples);

    //Relation with given name not found
  } else return NULL;
}
