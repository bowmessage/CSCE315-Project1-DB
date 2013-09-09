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
    //All values are strings.
    //If it is a blank string, NULL equivalent.
    //If it sarts with !..., parse as int.
    //If it starts with !!..., parse with string that starts "!.."

    Relation(string n);
    ~Relation();

    Attribute addAttribute(Attribute a);
    Attribute removeAttribute(Attribute a);

    bool operator==(const Relation &other);
};

#endif
