#ifndef DATABASEMANAGER_H_
#define DATABASEMANAGER_H_

#include "Database.h"

using namespace std;

class DatabaseManager{

  public:

    DatabaseManager();
    ~DatabaseManager();

    Database database;



    bool createTable(string name, vector<Attribute> attributes, vector<Attribute> keys);
    bool insertInto(string name, vector<string> literals);
    bool deleteTable(string name);
    void show(string name);
    void show(Relation* r);
	  bool rename(string name, vector<string> newNames);

    Relation* select(string relationName, string op1, string comparison, string op2);
    Relation* project(string relationName, vector<string> attributeNames);
};



#endif
