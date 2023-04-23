#ifndef INC_5_LIST_H
#define INC_5_LIST_H


#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <utility>


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

    list_iterator& operator--() {
        m_node = m_node->prev;
        return *this;
    }

    list_iterator(const list_iterator& other)
      : m_node(other.m_node)
    {
    }

    list_iterator& operator = (const list_iterator& other)
    {
        if (this != &other)
        {
            m_node=other.m_node;
        }
        return *this;
    }

      list_iterator& operator + (int t) {
          for (int i=0; i<t; i++) {
              (*this)++;
          }
      }





    bool operator == (const list_iterator& other) const
    {
        return (m_node == other.m_node);
    }

    bool operator != (const list_iterator& other) const
    {
        return (m_node != other.m_node);
    }

    reference operator * ()
    {
          return (m_node->value);
    }

    pointer operator -> ()
    {
          return &(m_node->value);
    }

    list_iterator& operator ++ ()
    {
        m_node=m_node->next;
        return *this;
    }

    list_iterator operator ++ (int)
    {
      list_iterator tmp(*this);
      (*this)++;
      return tmp;
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
    typedef list_iterator<Type> iterator;

    list()
      : m_head(nullptr), m_tail(nullptr)
    {
    }

    ~list()
    {
      clear();
    }

        reference front()
    {
        return m_head->value;
    }

    reference back()
    {
        return m_tail->value;
    }
      void clear() {
        while (m_head!=nullptr) {
            m_tail = m_head->next;
            delete m_head;
            m_head = m_tail;
        }
    }

      void pop_front() {
        if (m_head == m_tail) {
            m_head = m_tail = nullptr;
        } else {
            m_head = m_head->next;
            m_head->prev = nullptr;
        }
    }

    void pop_back() {
        if (m_head == m_tail) {
            m_head = m_tail = nullptr;
        } else {
            m_tail = m_tail->prev;
            m_tail->next = nullptr;
        }
    }

      void push_front(const value_type& value)
    {
        {
            node<Type> *tmp = new node<Type>(value, nullptr, nullptr);
            if (m_head == nullptr) {
                m_head = m_tail = tmp;
            } else {
                tmp->next = m_head;
                m_head->prev = tmp;
                m_head = tmp;
            }
        }
    }

    list::iterator begin()
    {
      return iterator(m_head);
    }

    list::iterator end()
    {
      return iterator();
    }

    void push_back(const value_type& value)
    {
        {
            node<Type> *tmp = new node<Type>(value, nullptr, nullptr);
            if (m_head == nullptr) {
                m_head = tmp;
                m_tail = tmp;
            } else {
                tmp->prev = m_tail;
                m_tail->next = tmp;
                m_tail = tmp;
            }
        }
    }

    iterator insert(iterator pos, const Type& value)
    {
        if (pos.m_node == m_head)
        {
            push_front(value);
            return iterator(m_head);
        }
        if (pos.m_node == nullptr)
        {
            push_back(value);
            return iterator(m_tail);
        }
        node<Type> *tmp = new node<Type>(value, nullptr, nullptr);
        tmp->next = pos.m_node;
        tmp->prev = pos.m_node->prev;
        pos.m_node->prev->next = tmp;
        pos.m_node->prev = tmp;
        pos.m_node = tmp;
        return iterator(tmp);
    }

    iterator erase(iterator pos)
    {
        if (pos.m_node == m_head)
        {
            pop_front();
            return iterator(m_head);
        }
        if (pos.m_node == m_tail)
        {
            pop_back();
            return iterator(m_tail);
        }
        pos.m_node->next->prev = pos.m_node->prev;
        pos.m_node->prev->next = pos.m_node->next;
        iterator tmp(pos.m_node->next);
        delete pos.m_node;
        return tmp;
    }


      size_t size() {
          size_t size=0;
          for (auto it = this->begin(); it != this->end(); it++) {
              size++;
          }
          return size;
      }



  private:
    node<Type>* m_head;
    node<Type>* m_tail;
  };



#endif //INC_5_LIST_H
