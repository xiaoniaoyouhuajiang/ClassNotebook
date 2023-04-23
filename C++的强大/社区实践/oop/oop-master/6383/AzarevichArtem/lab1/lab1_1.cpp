class A
{
public:
  A() {};

private:
  // some resources
    A( const A&){}
    A& operator = (const A&){}
};