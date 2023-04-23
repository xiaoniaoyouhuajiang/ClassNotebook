class Base
{
protected:
    Base() {};
    ~Base() {};
private:
    Base(Base const &);
    Base& operator = (Base const &);
};

class A : Base
{
public:
  A() {};

private:
  // some resources
};

