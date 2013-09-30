#include <stdexcept>
#include "Database.h"
#include <iostream>

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
    std::cout << "Checking that " << relations[i].name << " == " << n << "? \n";
    if(relations[i].name == n){
      return &relations[i];
    }
  }
  return NULL;
}

Relation* Database::setUnion(Relation r1, Relation r2){
	Relation* final = new Relation(r1.name+" and "+r2.name);
	for(int i = 0; i < r1.size(); i++){
		final->addAttribute(*r1.getAttribute(i));
	}
	final->tuples = r1.tuples;
	bool contains;
	for(int j = 0; j < r2.size(); j++){
		contains = false;
		Attribute a = *r2.getAttribute(j);
		for(int k = 0; k < final->size(); k++){
			if(a == *final->getAttribute(k))
				contains = true;
		}
		if(contains == false){
			final->addAttribute(a);
			for(int x = 0; x < r2.tuples.size(); x++){
				for(int y = 0; y < final->tuples.size(); y++){
					final->tuples[y][final->size()-1] = r2.tuples[x][j];
				}
			}
		}
	}
	return final;
}

Relation* Database::setDifference(Relation r1, Relation r2){
	Relation* final = new Relation(r1.name+" XOR "+r2.name);
	for(int i = 0; i < r1.size(); i++){
		final->addAttribute(*r1.getAttribute(i));
	}
		bool contains;
	for(int j = 0; j < r2.size(); j++){
		contains = false;
		Attribute a = *r2.getAttribute(j);
		for(int k = 0; k < final->size(); k++){
			if(a == *final->getAttribute(k))
				contains = true;
		}
		if(contains){
			final->removeAttribute(a);
		}
		else{
			final->addAttribute(a);
			for(int x = 0; x < r2.tuples.size(); x++){
				for(int y = 0; y < final->tuples.size(); y++){
					final->tuples[y][final->size()-1] = r2.tuples[x][j];
				}
			}
		}
	}
	return final;
}

Relation* Database::setProduct(Relation r1, Relation r2){
	Relation* final = new Relation(r1.name+" x "+r2.name);
	int sum = r1.size()+r2.size();
	vector<Attribute> v = r1.attributes;
	v.insert( v.end(), r2.attributes.begin(), r2.attributes.end() );  //concatenates v and r2.attributes
	
	for(int i = 0; i < r1.tuples.size(); i++){
		for(int j = 0; j < r2.tuples.size(); j++){
			vector<string> newtuple = r1.tuples[i];
			newtuple.insert( newtuple.end(), r2.tuples[j].begin(), r2.tuples[j].end() );  //concatenates
			final->tuples.push_back( newtuple );
		}
	}

	final->attributes = v;

	return final;
}
