#include "DatabaseManager.h"

using namespace std;


DatabaseManager::DatabaseManager(){

}

DatabaseManager::~DatabaseManager(){
  //Nothing to delete.. workingRelation taken care of by database.
}

//Returns with success value
bool DatabaseManager::openRelation(string r){
  if(currentRelation == NULL){
    try{
      currentRelation = &database.getRelationByName(r);
      return true;
    }
    catch(exception e){}
    return false;
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
}


