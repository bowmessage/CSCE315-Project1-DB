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

//adds entity "e" to the relation of name "n"
Entity Relation::addEntity(Entity e){
	entities.push_back(e);
	return e;
}

//removes entity "e" from relation "n"
Entity Relation::removeEntity(Entity e){
	for(int i = 0; i < entities.size(); i++){
		if(e == entities[i]){
      entities.erase(entities.begin()+i);
			return e;
    }
	}
}

//adds attribute "a" to the relation of name "n"
Attribute Relation::addAttribute(Attribute a){
	attributes.push_back(a);
	return a;
}

//adds entity "e" to the relation of name "n"
Attribute Relation::removeAttribute(Attribute a){
	for(int i = 0; i < attributes.size(); i++){
		if(a == attributes[i]){ 
      attributes.erase(attributes.begin()+i);
			return a;
    }
	}
}

bool Relation::operator==(const Relation &other){
  //TODO implement this
  return false;
}
