#ifndef RELATION_H
#define RELATION_H

#include <string>
#include <vector>

#include "Attribute.h"
#include "Entity.h"


using namespace std;

class Relation{
  public:
    string name;
    vector<Entity> entities;
    vector<Attribute> attributes;

    Attribute addAttribute(Attribute a);
    Attribute removeAttribute(Attribute a);

    bool operator==(const Relation &other);
};

#endif
