#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <utility>
#include <iostream>

namespace stepik
{
  template <class Type>
  struct node
  {
    Type value;
    node* next;
    node* prev;

    node(const Type& value, node<Type>* next, node<Type>* prev) : value(value), next(next), prev(prev) {}
  };

   template <class Type>
    class list; //forward declaration

    template <class Type>
    class list_iterator
    {
    public:
        typedef Type value_type;
        typedef Type* pointer;
        typedef Type& reference;
        typedef size_t size_type;
        typedef std::forward_iterator_tag iterator_category;

      list_iterator() : m_node(NULL) {}   
      list_iterator(const list_iterator& other) : m_node(other.m_node) {}

      list_iterator& operator = (const list_iterator& other)
      {
          if (this != &other)
          {
              m_node = other.m_node;
          }
          return *this;
      }

      bool operator == (const list_iterator& other) const
      {
           return m_node == other.m_node;
      }

      bool operator != (const list_iterator& other) const
      {
          return (m_node != other.m_node);
      }

      reference operator * ()
      {
           return m_node -> value;
      }

      pointer operator -> ()
      {
          return &(m_node -> value);
      }

      list_iterator& operator ++ ()
      {
          m_node = m_node -> next;
          return *this;
      }

      list_iterator operator ++ (int)
      {
          list_iterator old = *this;
          ++( *this );
          return old;
      }

    private:
      friend class list<Type>;

      list_iterator(node<Type>* p) : m_node(p) {}

      node<Type>* m_node;
    };

  template <class Type>
  class list
  {
  public:
    typedef Type value_type;
    typedef value_type& reference;
    typedef const value_type&  const_reference;
    typedef list_iterator<Type> iterator;

    list() : m_head(nullptr), m_tail(nullptr) {}

    ~list()
    {
        clear();
    }

    list(const list& other)
    {
        m_head = nullptr;
        m_tail = nullptr;
        *this = other;
    }

    list(list&& other)
    {
        m_head = nullptr;
        m_tail = nullptr;
        *this = other;
        other.clear();
    }

    list& operator= (const list& other)
    {
        clear();
        node<Type>* ptr = other.m_head;
        while( ptr )
        {
            this->push_back( ptr->value );
            ptr = ptr -> next;
        }
        return *this;
    }

    void push_back(const value_type& value)
    {
        if(!this->empty() )
        {
            m_tail -> next = new node<Type>( value, nullptr, m_tail );
            m_tail = m_tail -> next;
        }
        else
        {
            m_tail = new node<Type>( value, nullptr, nullptr );
            m_head = m_tail;
        }
    }

    void push_front(const value_type& value)
    {
        if(!this->empty() )
        {
            m_head -> prev = new node<Type>( value, m_head, nullptr );
            m_head = m_head -> prev;
        }
        else
        {
            m_head = new node<Type>( value, nullptr, nullptr );
            m_tail = m_head;
        }
    }

    reference front()
    {
      return m_head->value;
    }

    const_reference front() const
    {
      return m_head->value;
    }

    reference back()
    {
      return m_tail -> value;
    }

    const_reference back() const
    {
      return m_tail -> value;
    }

    void pop_front()
    {
        if( m_head )
        {
            if( m_head -> next )
            {
                m_head = m_head -> next;
                delete m_head -> prev;
                m_head -> prev = nullptr;
            }
            else
            {
                m_tail = nullptr;
                delete m_head;
                m_head = nullptr;
            }
        }
    }

    void pop_back()
    {
        if( m_tail )
        {
            if( m_tail -> prev )
            {
                m_tail = m_tail -> prev;
                delete m_tail -> next;
                m_tail -> next = nullptr;
            }
            else
            {
                m_head = nullptr;
                delete m_tail;
                m_tail = nullptr;
            }
        }
    }

    iterator insert(iterator pos, const Type& value)
    {
        if( pos == end() )
        {
            push_back( value );
            return iterator( m_tail );
        }
        if( pos == begin() )
        {
            push_front( value );
            return begin();
        }
        node<Type> *p = new node<Type>( value, pos.m_node, pos.m_node->prev );
        p->prev->next = p;
        p->next->prev = p;
        return iterator( p );
    }

    iterator erase(iterator pos)
    {
        if( pos == begin() )
        {
            pop_front();
            return iterator(m_head);
        }
        if( pos.m_node == m_tail )
        {
            pop_back();
            return iterator();
        }
        node<Type> *ptr = pos.m_node;
        iterator retVal( ptr->next );
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        delete ptr;

        return retVal;
    }

    void clear()
    {
        node<Type>* curr = m_head;
        while( m_head )
        {
            curr = m_head;
            m_head = m_head->next;
            delete curr;
        }
        m_head = nullptr;
        m_tail = nullptr;
    }

    bool empty() const
    {
        return (!m_head && !m_tail) ? true : false;
    }

    size_t size() const
    {
        node<Type>* ptr = m_head;
        size_t size = 0;
        while( ptr )
        {
            ++size;
            ptr = ptr -> next;
        }
        return size;
    }

    list::iterator begin()
    {
        return iterator(m_head);
    }

    list::iterator end()
    {
        return iterator();
    }

  private:

    node<Type>* m_head;
    node<Type>* m_tail;
  };
}