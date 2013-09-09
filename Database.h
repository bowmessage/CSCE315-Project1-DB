#ifndef DATABASE_H 
#define DATABASE_H 

#include <string>
#include <vector>

#include "Relation.h"
#include "Attribute.h"


using namespace std;

class Database{
  public:
    vector<Relation> relations;

    Database();
    ~Database();

    Relation addRelation(Relation r);
    Relation removeRelation(Relation r);
    Relation* getRelationByName(string n);
};

#endif
