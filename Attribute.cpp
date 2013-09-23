#include "Attribute.h"


Attribute::Attribute(){
}

Attribute::Attribute(string n){
  name = n;
}

Attribute::~Attribute(){
}



bool Attribute::operator==(const Attribute &other){
  return name == other.name;
}
