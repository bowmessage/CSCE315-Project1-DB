#ifndef RELATION_H
#define RELATION_H

#include <string>
#include <vector>

#include "Attribute.h"
#include "Entity.h"

using namespace std;

class Relation{
	vector<Entity> entity;			//vector of entities using this relation
	vector<Attribute> attribute;	//vector of attribues of this relation
	string Name;					//name of relation

	Relation(string n);
	~Relation(string n);

	Entity addEntity(Entity e);
	Entity removeEntity(Entity e);
	Attribute addAttribute(Attribute a);
	Attribute removeAttribute(Attribute a);
};

#endif
