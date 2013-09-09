#ifndef DATABASEMANAGER_H_
#define DATABASEMANAGER_H_

#include "Database.h"

using namespace std;

class DatabaseManager{

  public:

    DatabaseManager();
    ~DatabaseManager();

    Database database;




    //bool openRelation(string r);
    //bool closeRelation(string r);
    bool createTable(string name, vector<Attribute> attributes, vector<Attribute*> keys);
    bool insertInto(string name, vector<string> literals);
};



#endif
