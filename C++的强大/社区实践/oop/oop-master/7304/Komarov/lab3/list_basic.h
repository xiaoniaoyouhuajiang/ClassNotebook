#ifndef LIST_BASIC_H
#define LIST_BASIC_H
#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
  template <class Type>
  struct node
  {
    Type value;
    node* next;
    node* prev;

    node(const Type& value, node<Type>* next, node<Type>* prev);
  };

  template <class Type>
    class List;
    template <class Type>
    class list_iterator
    {
    public:
      typedef ptrdiff_t difference_type;
      typedef Type value_type;
      typedef Type* pointer;
      typedef Type& reference;
      typedef size_t size_type;
      typedef std::forward_iterator_tag iterator_category;

      list_iterator();

      list_iterator(const list_iterator& other);

      list_iterator& operator = (const list_iterator& other);

      bool operator == (const list_iterator<Type> &other) const;

      bool operator != (const list_iterator& other) const;

      reference operator * ();

      pointer operator -> ();
        //prefix
      list_iterator& operator ++ ();
    //postfix
      list_iterator operator ++ (int);

    private:
      friend class List<Type>;

      list_iterator(node<Type>* p);

      node<Type>* m_node;
    };

  template <class Type>
  class List
  {
  public:
    typedef Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef list_iterator<Type> iterator;

    List();

    ~List();

        List(const List& other);

        List(List&& other);

        List& operator= (const List& other);
        List::iterator begin();
        List::iterator end();

        void push_back(const value_type& value);

            void push_front(const value_type& value);

            void pop_front();

            void pop_back();

            iterator insert(iterator pos, const Type& value);

                iterator erase(iterator pos);

        reference front();

            const_reference front() const;

            reference back();
            const_reference back() const;
            bool empty() const;

            size_t size() const;

  private:
        void copy(List & lst);

        void swap(List & lst);

        void clear();
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };
#endif // VECTOR_H
