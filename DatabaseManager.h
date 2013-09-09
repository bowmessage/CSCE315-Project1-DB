#ifndef DATABASEMANAGER_H_
#define DATABASEMANAGER_H_

#include "Database.h"

using namespace std;

class DatabaseManager{

  public:

    DatabaseManager();
    ~DatabaseManager();

    Database database;

    Relation* currentRelation;



    bool DatabaseManager::openRelation(string r);
    bool DatabaseManager::closeRelation(string r);

    vector<vector<Attribute>>



};



#endif
