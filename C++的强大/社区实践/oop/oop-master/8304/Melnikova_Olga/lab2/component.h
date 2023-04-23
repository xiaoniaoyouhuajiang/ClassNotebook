#include "objects/object.h"


class Component
{
    //Component *parent_;
public:
    virtual ~Component() {}
    virtual void attachObserver(Observer* obj);
    virtual void detachObserver();
    virtual void notifyObservers();


/*

    Object* innerObject_;
public:
    virtual ~Component() {}
    void SetParent(Component *parent);
    Component *GetParent() const ;
    virtual void Add(Component *component) {}
    virtual void Remove(Component *component) {}
    virtual bool IsComposite() const {
        return false;
    }
    virtual void setInnerObject(Object* object);
    virtual Object* getInnerObject();
    virtual Object* ();
*/
};

