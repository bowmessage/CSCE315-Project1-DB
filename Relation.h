#ifndef RELATION_H
#define RELATION_H

#include <string>
#include <vector>

#include "Attribute.h"
#include "Entity.h"

using namespace std;

class Relation{
  public:
    vector<Entity> entities;			//vector of entities using this relation vector<Attribute> attributes;	//vector of attribues of this relation
    vector<Attribute> attributes; //vector of attributes of this relation
    string name;					//name of relation

    Relation(string n);
    ~Relation();

    Entity addEntity(Entity e);
    Entity removeEntity(Entity e);
    Attribute addAttribute(Attribute a);
    Attribute removeAttribute(Attribute a);

    bool operator==(const Relation &other);
};

#endif
