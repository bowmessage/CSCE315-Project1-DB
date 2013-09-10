#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <vector>
#include <string>

using namespace std;

class Attribute{

  public:

    Attribute();
    ~Attribute();

    Attribute(string n);


    bool isKey;
    string name;

    bool operator==(const Attribute &other);
};

#endif
