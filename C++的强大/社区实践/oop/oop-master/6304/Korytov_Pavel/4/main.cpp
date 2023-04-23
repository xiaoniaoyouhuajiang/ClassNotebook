#include <iostream>
#include "shared_ptr.hpp"

using namespace std;
using stepik::shared_ptr;

class MyClass{
public:
    explicit MyClass(int b = 0): a(b)
    { }
    int get() {return a;}
    void set(int b = 0) {a = b;}
    void print(){
        cout << a << endl;
    }
private:
    int a;
};

class MyClassDer : public MyClass{
public:
    void do_nothing() {cout << "Jag är björk. Aldrig Återvända" << endl; }
};

int main()
{
    Debug("|============|Constructor test|============|");
    MyClass* obj = new MyClass(15);
    shared_ptr<MyClass> ap(obj);
    Debug("|============|Get test|============|");
    ap.get()->print();
    Debug("|============|Operator * test|============|");
    (*ap).print();
    Debug("|============|Operator -> test|============|");
    ap->print();
    Debug("|============|Copy constructor test|============|");
    shared_ptr<MyClass> bp(ap);
    shared_ptr<MyClass> cp(bp);
    cout << ap.use_count() << " " << bp.use_count() << " " << cp.use_count() << endl;
    Debug("|============|Assignment test|============|");
    MyClass* obj2 = new MyClass(20);
    shared_ptr<MyClass> dp(obj2);
    cp = dp;
    cout << cp.use_count() << " " << dp.use_count() << endl;
    cout << cp->get() << " " << dp->get() << endl;
    Debug("|============|Reset test|============|");
    MyClass* obj3 = new MyClass(25);
    cp.reset(obj3);
    cout << ap.use_count() << " " << bp.use_count() << " " << cp.use_count() << endl;
    bp.reset();
    cout << ap.use_count() << " " << bp.use_count() << " " << cp.use_count() << endl;
    Debug("|============|Polymorph test|============|");
    MyClassDer* Derived = new MyClassDer;
    Derived->set(30);
    shared_ptr<MyClassDer> derivedPtr(Derived);
    derivedPtr->do_nothing();
    derivedPtr->print();
    shared_ptr<MyClass> basePtr = derivedPtr;
    basePtr->print();
    cout << derivedPtr.use_count() << " " << basePtr.use_count() << endl;
    Debug("|============|End of program|============|");
    return 0;
}
