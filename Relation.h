#ifndef RELATION_H
#define RELATION_H

#include <string>
#include <vector>

#include "Attribute.h"

using namespace std;

class Relation{
  public:
    string name;					//name of relation
    vector<Attribute> attributes; //vector of attributes of this relation
    vector< vector<string> > tuples;

    Relation(string n);
    ~Relation();

    Attribute addAttribute(Attribute a);
    Attribute removeAttribute(Attribute a);

    bool operator==(const Relation &other);
};

#endif
