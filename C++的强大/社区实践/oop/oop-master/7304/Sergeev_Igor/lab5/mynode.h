#ifndef NODE
#define NODE

template <class Type>
class node
{
public:

  double firstInput;
  double secondInput;
  double firstResult;
  double secondResult;
  node<Type>* neg;
  node<Type>* abs;
  node<Type>* div;
  node<Type>* dechun;
  node<Type>* add;
  node<Type>* mul;
  node<Type>* divmod;
  node<Type>* muldiv;
  node<Type>* prev;

  node(node<Type>* prev)
    : neg(NULL), abs(NULL), div(NULL), dechun(NULL), add(NULL), mul(NULL), divmod(NULL),
      muldiv(NULL), prev(prev), firstInput(0), secondInput(0), firstResult(0), secondResult(0)
  {
  }
  ~node()
  {
      neg = NULL;
      abs = NULL;
      div = NULL;
      dechun = NULL;
      add = NULL;
      mul = NULL;
      divmod = NULL;
      muldiv = NULL;
      prev = NULL;
      firstInput = 0;
      secondInput = 0;
      firstResult = 0;
      secondResult = 0;
  }
};

#endif // NODE
