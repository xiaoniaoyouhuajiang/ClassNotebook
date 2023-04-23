#ifndef COMPOSITE_H
#define COMPOSITE_H
#include "component.h"
#include <list>

class Composite: public Component {
   protected:
    std::list<Object*> objects;
    //Object** children_;


   public:
    void attachObserver() override {

    }
    void detachObserver() override {

    }
    void notifyObservers() override {

    }
    /*
    void Add(Component *component) override {
      this->objects.push_back(component);
      //component->SetParent(this);
    }

    void Remove(Component *component) override {
      //children_.remove(component);
      component->SetParent(nullptr);
    }
    bool IsComposite() const override {
      return true;
    }

    Object* getInnerObject() const override{
      std::string result;
      for (const Component *c : children_) {
        if (c == children_.back()) {
          result += c->Operation();
        } else {
          result += c->Operation() + "+";
        }
      }
      return "Branch(" + result + ")";
    }*/
};

#endif // COMPOSITE_H
