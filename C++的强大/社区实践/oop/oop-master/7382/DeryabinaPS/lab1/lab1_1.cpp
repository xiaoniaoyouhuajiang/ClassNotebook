class A
{
public:
  A() {};

private:
  // some resources
   A( const A& );
   void operator=( const A& );
};
