#include "Attribute.h"


Attribute::Attribute(){
}

Attribute::~Attribute(){
  delete[] charValue;
}

int Attribute::updateIntValue(int i){
  intValue = i;
  return intValue;
}

char* Attribute::updateCharValue(char* c){
  charValue = c;
  return charValue;
}



int Attribute::getIntValue(){
  return intValue;
}

char* Attribute::getCharValue(){
  return charValue;
}


bool Attribute::operator==(const Attribute &other){
  //TODO implement this
  return false;
}
