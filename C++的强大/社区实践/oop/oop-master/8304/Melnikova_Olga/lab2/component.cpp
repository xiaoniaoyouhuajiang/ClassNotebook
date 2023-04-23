#include "component.h"


void Component::SetParent(Component *parent) {
  this->parent_ = parent;
}
Component* Component::GetParent() const {
  return this->parent_;
}
