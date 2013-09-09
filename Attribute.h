#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <vector>
#include <string>

using namespace std;

class Attribute{
  public:

    Attribute();
    ~Attribute();


    int intValue;
    char* charValue;
    bool isInt;

    string name;

    int updateIntValue(int i);
    char* updateCharValue(char* c);

    int getIntValue();
    char* getCharValue();
    
    bool operator==(const Attribute &other);
};

#endif
