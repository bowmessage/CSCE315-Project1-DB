#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <vector>
#include <string>

using namespace std;

template <class T>
class Attribute{
  public:


    T value;
    string name;

    bool operator==(const Attribute &other);
};

#endif
