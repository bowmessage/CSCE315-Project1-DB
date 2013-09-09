#include <stdexcept>
#include "Database.h"

Database::Database(){
}

Database::~Database(){
}

Relation Database::addRelation(Relation r){
  relations.push_back(r);
  return r;
}

Relation Database::removeRelation(Relation r){
  for(int i = 0; i < relations.size(); i++){
    if(relations[i] == r){
      relations.erase(relations.begin()+i);
      break;
    }
  }
  return r;
}

Relation* Database::getRelationByName(string n){
  for(int i = 0; i < relations.size(); i++){
    if(relations[i].name == n){
      return &relations[i];
    }
  }
  return NULL;
}
