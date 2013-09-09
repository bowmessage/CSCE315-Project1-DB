#include "Relation.h"

using namespace std;

//creates a relation of name "n"
Relation::Relation(string n){
		name = n;
}

//removes a relation of name "n"
Relation::~Relation(){
  //Don't need to do these things as they're implicitly destructed (not pointer refrenced)
	//Name = NULL;
	//entity.erase();
	//attribute.erase();
}

//adds attribute "a" to the relation of name "n"
Attribute Relation::addAttribute(Attribute a){
	attributes.push_back(a);
  for(int i = 0; i < tuples.size(); i++){
    tuples[i].push_back("");
  }
	return a;
}

//adds entity "e" to the relation of name "n"
Attribute Relation::removeAttribute(Attribute a){
  int colNumRemoved = 0;
	for(int i = 0; i < attributes.size(); i++){
		if(a == attributes[i]){ 
      attributes.erase(attributes.begin()+i);
      colNumRemoved = i;
    }
	}
  for(int i = 0; i < tuples.size(); i++){
    for(int j = 0; j < tuples[i].size(); j++){
      if(j == colNumRemoved){
        tuples[i].erase(tuples[i].begin()+j);
        j--;
      }
    }
  }
  return a;
}

bool Relation::operator==(const Relation &other){
  //TODO implement this
  return false;
}
