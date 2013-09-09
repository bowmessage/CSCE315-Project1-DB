#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <vector>
#include <string>

using namespace std;

class Attribute{
  public:


    int intValue;
    char* charValue;
    bool isInt;

    string name;

    bool operator==(const Attribute &other);
};

#endif
