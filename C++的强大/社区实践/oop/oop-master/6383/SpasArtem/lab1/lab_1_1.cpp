class A
{
public:
  A() {};

private:
    // some resources 
    A(const A& a);
    A const operator=(const A& a);
};