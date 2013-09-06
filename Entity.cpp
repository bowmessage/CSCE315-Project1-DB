#include "Entity.h"

Entity::Entity(string name){
  this->name = name;
}

Entity::~Entity(){
}

Attribute Entity::addAttribute(Attribute a){
  attributes.push_back(a);
}

Attribute Entity::removeAttribute(Attribute a){
  for(int i = 0; i < attributes.size(); i++){
    if(attributes[i] == a){
      attributes.erase(attributes.begin()+i);
      break;
    }
  }
}
