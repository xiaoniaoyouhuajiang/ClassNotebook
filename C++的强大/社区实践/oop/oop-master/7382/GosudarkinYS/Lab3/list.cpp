#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
#include <iostream>
#include <cstring>

#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>

namespace stepik
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
          return *this;
      }

      bool operator == (const list_iterator& other) const
      {
          return m_node == other.m_node;
      }

      bool operator != (const list_iterator& other) const
      {
          return m_node != other.m_node;
      }

      reference operator * ()
      {
          return m_node->value;
      }

      pointer operator -> ()
      {
          return &m_node->value;
      }

      list_iterator& operator ++ ()
      {
          m_node = m_node->next;
          return *this;
      }

      list_iterator operator ++ (int)
      {
          list_iterator base = *this;
          m_node = m_node->next;
          return base;
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

    list(const list& other) : list()
    {
        std::cout << "COPY CONSTRUCTOR\n";
        if(!other.empty())
            for(node<Type>* i = other.m_head; i != nullptr; i = i->next)
                push_back(i->value);
    }

    list(list&& other)
    {
        std::cout << "MOVE CONSTRUCTOR\n";
        m_head = other.m_head;
        m_tail = other.m_tail;
    }

    list& operator= (const list& other)
    {
        std::cout << "COPY ASSIGNMENT OPERATOR\n";
        if(&other != this)
        {
            clear();
            for(node<Type>* i = other.m_head; i != nullptr; i = i->next)
                push_back(i->value);
        }
        return *this;
    }

    void push_back(const value_type& value)
    {
        if(!m_tail || !m_head)
        {
            m_head = new node<value_type>(value, nullptr, nullptr);
            m_tail = m_head;
            return;
        }
        node<value_type>* curr = new node<value_type>(value, nullptr, m_tail);
        m_tail->next = curr;
        m_tail = curr;
    }

    void push_front(const value_type& value)
    {
        if(!m_tail || !m_head)
        {
            m_head = new node<value_type>(value, nullptr, nullptr);
            m_tail = m_head;
            return;
        }
        node<value_type>* curr = new node<value_type>(value, m_head, nullptr);
        m_head->prev = curr;
        m_head = curr;
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
        return m_tail->value;
    }

    const_reference back() const
    {
        return m_tail->value;
    }

    void pop_front()
    {
        if(!m_tail->prev) { delete_last_one(); return; }
        m_head = m_head->next;
        delete m_head->prev;
        m_head->prev = nullptr;
    }

    void pop_back()
    {
        if(!m_tail->prev) { delete_last_one(); return; }
        m_tail = m_tail->prev;
        delete m_tail->next;
        m_tail->next = nullptr;
    }

    iterator insert(iterator pos, const Type& value)
    {
        if(pos.m_node == m_head) { push_front(value); return begin(); }
        if(pos.m_node == m_tail->next) { push_back(value); return iterator(m_tail); }

        node<Type>* curr = new node<Type>(value, pos.m_node, pos.m_node->prev);
        curr->next = pos.m_node;
        curr->prev = pos.m_node->prev;
        return iterator(curr);
    }

    iterator erase(iterator pos)
    {
        if(!pos.m_node) return end();
        if(pos.m_node == m_head) { pop_front(); return begin(); }
        if(pos.m_node == m_tail) { pop_back(); return end(); }

        node<Type>* curr = pos.m_node;
        node<Type>* next = curr->next;
        next->prev = curr->prev;
        curr->prev->next = next;
        delete curr;
        return iterator(next);
    }

    iterator begin()
    {
        return iterator(m_head);
    }

    iterator end()
    {
        return iterator();
    }

    void clear()
    {
        while(m_tail && m_head)
            pop_back();
    }

    bool empty() const
    {
        return m_tail ? false : true;
    }

    size_t size() const
    {
        size_t count = 0;
        for(node<Type>* i = m_head; i != nullptr; i = i->next)
            count++;
        return count;
    }

    void print()
    {
        std::cout << "List: ";
        for(node<Type>* i = m_head; i != nullptr; i = i->next)
            std::cout << i->value << ", ";
        std::cout << "\n";
        std::cout << "empty: " << empty() << "\n";
        //std::cout << "back: " << back() << "\n";
        //std::cout << "front: " << front() << "\n";
        std::cout << "size: " << size() << "\n";
    }

  private:
    //your private functions
    void delete_last_one()
    {
        delete m_tail;
        m_tail = nullptr;
        m_head = nullptr;
    }

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik

int main()
{
    stepik::list<int> a;
    a.push_back(4);
    a.push_back(5);
    a.push_back(6);
    a.push_front(6);
    a.push_front(2);
    a.push_front(3);
    a.print();
    stepik::list_iterator<int> it = a.begin(); it++; it++;
    a.erase(it);
    a.print();
    a.insert(it, 9);
    a.print();
    return 0;
}
