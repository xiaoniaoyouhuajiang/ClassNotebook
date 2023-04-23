#ifndef LIST_H
#define LIST_H
#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>

using namespace std;
{
  template <class Type>
  struct node
  {
    Type value;
    node* next;
    node* prev;

    node(const Type& value, node<Type>* next, node<Type>* prev)
      : value(value), next(next), prev(prev)
    {
    }
  };

  template <class Type>
    class list; //forward declaration

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

      list_iterator()
        : m_node(NULL)
      {
      }

      list_iterator(const list_iterator& other)
        : m_node(other.m_node)
      {
      }

      list_iterator& operator = (const list_iterator& other)
      {
          m_node = other.m_node;
          return m_node;
        // implement this
      }

      bool operator == (const list_iterator& other) const
      {
          return (m_node == other.m_node);
        // implement this
      }

      bool operator != (const list_iterator& other) const
      {
          return !(m_node == other.m_node);
        // implement this
      }

      reference operator * ()
      {
          return (m_node->value);
        // implement this
      }

      pointer operator -> ()
      {
          return &(m_node->value);
        // implement this
      }

      list_iterator& operator ++ ()
      {
        m_node = m_node->next;
        return *this;
        // implement this
      }

      list_iterator operator ++ (int)
      {
        list_iterator* next_node = new list_iterator(*this);
        m_node = m_node->next;
        return *next_node;
        // implement this
      }

    private:
      friend class list<Type>;

      list_iterator(node<Type>* p)
        : m_node(p)
      {
      }

      node<Type>* m_node;
    };

  template <class Type>
  class list
  {
  public:
    typedef Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;

    list()
      : m_head(nullptr), m_tail(nullptr)
    {
    }

    void push_back(const value_type& value)
    {
        node<Type>* new_node = new node<Type>(value, nullptr, m_tail);
        if (m_head == NULL)
            m_head = new_node;
        else
            m_tail->next = new_node;
           m_tail = new_node;
      // implement this
    }

    void push_front(const value_type& value)
    {
         node<Type>* new_node = new node<Type>(value, m_head, nullptr);
        if (m_tail == NULL)
            m_tail = new_node;
        else
            m_head->prev = new_node;
           m_head = new_node;
      // implement this
    }

    reference front()
    {
        return m_head->value;
      // implement this
    }

    const_reference front() const
    {
      return m_head->value;
      // implement this
    }

    reference back()
    {
        return m_tail->value;
      // implement this
    }

    const_reference back() const
    {
        return m_tail->value;
      // implement this
    }

    void pop_front()
    {
         if (m_head == NULL)
             return;
          node<Type>* new_head = m_head->next;
          delete m_head;
          if (new_head != NULL)
              new_head->prev = nullptr;
          else
              m_tail = new_head;
            m_head = new_head;
      // implement this
    }

    void pop_back()
    {
        if (m_tail == NULL)
            return;
            node<Type>* new_tail = m_tail->prev;
            delete m_tail;
            if (new_tail != NULL)
                new_tail->next = nullptr;
            else
                m_head = new_tail;
               m_tail = new_tail;

      // implement this
    }

    void clear()
    {
        while(!empty())
            pop_front();
      // implement this
    }

    bool empty() const
    {
        return !m_head;
      // implement this
    }

    size_t size() const
    {
        int size = 0;
        node<Type>* tmp = m_head;
        while (tmp != NULL) {
            tmp = tmp->next;
            size++;
        }
        return size;
      // implement this
    }
    ~list()
       {
           clear();
         // implement this
       }

       list(const list& other): list()
       {
           node<Type>* new_node = other.m_head;
           while(new_node != NULL){
               push_back(new_node->value);
               new_node = new_node->next;
           }
         // implement this
       }

       list(list&& other) : list()
       {
           swap(m_head, other.m_head);
           swap(m_tail, other.m_tail);
         // implement this
       }

       list& operator= (const list& other)
       {
            if (this != &other) {
                clear();
               node<Type>* new_node = other.m_head;
               while(new_node != NULL){
               push_back(new_node->value);
               new_node = new_node->next;
               }
         }
           return *this;
         // implement this
       }

       iterator insert(iterator pos, const Type& value)
          {
              if (pos.m_node == NULL)
              {
                  push_back(value);
                  return iterator(m_tail);
              }
              else if (pos.m_node->prev == NULL) {
                  push_front(value);
                  return iterator(m_head);
              }
              else {
                  node<Type>* a = new node<Type>(value, pos.m_node, pos.m_node->prev);
                  pos.m_node->prev->next = a;
                  pos.m_node->prev = a;
                  return iterator(a);
              }
            // implement this
          }

          iterator erase(iterator pos)
          {
              if (pos.m_node == NULL)
              {
                  return NULL;
              }
              else if (pos.m_node->prev == NULL)
              {
                  pop_front();
                  return iterator(m_head);
              }
              else if (pos.m_node->next == NULL)
              {
                  pop_back();
                  return iterator(m_tail);
              }
              else
              {
                  pos.m_node->next->prev = pos.m_node->prev;
                  pos.m_node->prev->next = pos.m_node->next;
                  node<Type>* a = pos.m_node;
                  iterator pos_next(pos.m_node->next);
                  delete a;
                  return pos_next;
              }
            // implement this
          }


  private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}
#endif // LIST_H
