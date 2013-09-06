#include "Relation.h"

using namespace std;

//creates a relation of name "n"
Relation::Relation(string n){
		Name = n;
}

//removes a relation of name "n"
Relation::~Relation(string n){
	Name = NULL;
	entity.erase();
	attribute.erase();
}

//adds entity "e" to the relation of name "n"
Entity Relation::addEntity(Entity e){
	entity.push_back(e);
	return e;
}

//removes entity "e" from relation "n"
Entity Relation::removeEntity(Entity e){
	for(int i = 0; i < entity.size(); i++){
		if(e == entity[i]){
			entity[i].erase();
			return e;
	}
}

//adds attribute "a" to the relation of name "n"
Attribute Relation::addAttribute(Attribute a){
	attribute.push_back(a);
	return a;
}

//adds entity "e" to the relation of name "n"
Attribute Relation::removeAttribute(Attribute a){
	for(int i = 0; i < r.attribute.size(); i++){
		if(a == r.attribute[i]){ 
			attribute[i].erase();
			return a;
	}
}
