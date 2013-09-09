#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>

#include "Attribute.h"

using namespace std;

class Entity{
  public:
    string name;
    vector<Attribute> attributes;
    Attribute* key;


    Entity(string s);
    ~Entity();


    Attribute addAttribute(Attribute a);
    Attribute removeAttribute(Attribute a);

    bool operator==(const Entity &other);


};

#endif
