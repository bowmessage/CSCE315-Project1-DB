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
    Attribute* getAttribute(int x);
    int size();


    vector<Attribute*> keys;
    vector< vector<string> > tuples;
    //All values are strings.
    //If it is a blank string, NULL equivalent.
    //If it sarts with !..., parse as int.
    //If it starts with !!..., parse with string that starts "!.."

    Relation(string n);
    Relation(string n, vector<Attribute> a);
    Relation(string n, vector<Attribute> a, vector<Attribute*> k);
    Relation(string n, vector<Attribute> a, vector< vector<string> > t);
    Relation(string n, vector<Attribute> a, vector<Attribute*> k, vector< vector<string> > t);
    ~Relation();

    Attribute addAttribute(Attribute a);
    Attribute removeAttribute(Attribute a);
    Attribute* getAttributeByName(string n);
    int getAttributeIndexByName(string n);

    bool operator==(const Relation &other);
};

#endif
