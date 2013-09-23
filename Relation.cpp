#include "Relation.h"

using namespace std;

//creates a relation of name "n"
Relation::Relation(string n){
		name = n;
}

Relation::Relation(string n, vector<Attribute> a){
		name = n;
    attributes = a;
}

Relation::Relation(string n, vector<Attribute> a, vector<Attribute*> k){
		name = n;
    attributes = a;
    keys = k;
}
Relation::Relation(string n, vector<Attribute> a, vector< vector<string> > t){
		name = n;
    attributes = a;
    tuples = t;
}
Relation::Relation(string n, vector<Attribute> a, vector<Attribute*> k, vector< vector<string> > t){
		name = n;
    attributes = a;
    keys = k;
    tuples = t;
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

Attribute* Relation::getAttribute(int x){
	return &attributes[x];
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

int Relation::size(){
  return attributes.size();
}

Attribute* Relation::getAttributeByName(string n){
  for(int i = 0; i < attributes.size(); i++){
    if(attributes[i].name == n){
      return &attributes[i];
    }
  }
  return NULL;
}

int Relation::getAttributeIndexByName(string n){
  for(int i = 0; i < attributes.size(); i++){
    if(attributes[i].name == n){
      return i;
    }
  }
  return -1;
}


bool Relation::operator==(const Relation &other){
  return (name == other.name) &&
    (attributes == other.attributes) &&
    (keys == other.keys) &&
    (tuples == other.tuples);
}
