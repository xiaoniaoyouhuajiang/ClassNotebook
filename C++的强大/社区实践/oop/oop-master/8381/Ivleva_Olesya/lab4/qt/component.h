#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <field.h>


class Component {
protected:
    Component *parent_;
public:
    virtual ~Component() {}
    void setParent(Component *parent) {
        this->parent_ = parent;
    }
    Component *getParent() const {
        return this->parent_;
    }
    virtual string getUnits_WhoAmI() = 0;
    virtual void Add(Component *component) = 0;
    virtual void Remove(Component *component) = 0;
    virtual Component *getChildren(unsigned index) = 0;
    virtual void addUnit(Item *unit) = 0;
    virtual void removeUnit(Item *unit) = 0;

};

class Composite : public Component
{
protected:
    vector<Component *> children;
public:
    string getUnits_WhoAmI() {
        string output = "";
        output += "{";
        for (auto i : children) {
            output += i->getUnits_WhoAmI();
        }
        output += "}\n";
        return output;
    }
    Component * getChildren(unsigned index) {
        if (index > children.size())
            return nullptr; //size error
        return children[index];
    }
    void Add(Component *component) {
        children.push_back(component);
        component->setParent(this);
    }
    void Remove(Component *component) {
        for (unsigned i=0; i<children.size(); i++) {
            if (children[i] == component)
                children.erase(children.begin() + i);
        }
        component->setParent(nullptr);
    }
    void addUnit(Item *unit) {}
    void removeUnit(Item *unit) {}
};

class Leaf : public Component
{
protected:
    list<Item *> units;
public:
    string getUnits_WhoAmI() {
        string output = "";
        output += " {";
        for (auto i : units) {
            output += i->print_who() + " ";
        }
        output += "} ";
        return output;
    }
    void Add(Component *component) {}
    void Remove(Component *component) {}
    void addUnit(Item *unit) {
        units.push_back(unit);
    }
    Component * getChildren(unsigned int index) {
        return this;
    }
    void removeUnit(Item *unit) {
        units.remove(unit);
    }
    list<Item *> getUnits() {
        return units;
    }
};
