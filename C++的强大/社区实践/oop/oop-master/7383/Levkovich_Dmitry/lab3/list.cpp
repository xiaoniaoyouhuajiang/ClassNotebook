#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <utility>
#include <iostream>
using namespace std;
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
        ++(*this);
        return old;
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

    list::iterator begin()
    {
      return iterator(m_head);
    }

    list::iterator end()
    {
      return iterator();
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
    void pop_front()
    {
        if(m_head){
          if(m_head->next){
              m_head = m_head->next;
              delete m_head->prev;
              m_head->prev = nullptr;
          }
          else{
              m_tail = nullptr;
              delete m_head;
              m_head = nullptr;
          }
        }
    }

    void pop_back()
    {
        if(m_tail){
          if(m_tail->prev){
              m_tail->prev = m_tail;
              delete m_tail->next;
              m_tail->next = nullptr;
          }
          else{
              m_head = nullptr;
                      delete m_tail;
              m_tail = nullptr;
          }
        }
    }

    iterator insert(iterator pos, const Type& value)
    {
      if (pos.m_node ==nullptr) {push_back(value); return iterator(m_tail);}
      if (pos.m_node->prev == nullptr) {push_front(value); return iterator(m_head);}
      auto newNode = new node<Type>(value,pos.m_node,pos.m_node->prev);
       pos.m_node->prev->next = newNode;
       pos.m_node->prev = newNode;
       return iterator(newNode);
    }

    iterator erase(iterator pos)
    {
        if(pos.m_node == nullptr){
            return end();
        }
        if(pos == begin()){
            pop_front();
            return iterator(m_head);
        }
        if(pos == iterator(m_tail)){
            pop_back();
            return end();
        }
        auto temp = pos.m_node->next;
        pos.m_node->prev->next = pos.m_node->next;
        pos.m_node->next->prev = pos.m_node->prev;
        delete pos.m_node;
        return temp;
    }
    void clear()
    {
        node <value_type>* cur = m_head;
        node <value_type>* del;

        while (cur) {

            del = cur;
            cur = cur->next;
            delete del;
        }

        m_head = nullptr;
        m_tail = nullptr;
    }

    bool empty() const
    {
        return m_head==nullptr;
    }

    size_t size() const
    {
        size_t count = 0;
        auto tmp = m_head;
        while(tmp){
            count++;
            tmp = tmp->next;
        }
        return count;
    }
reference front()
    {
      return m_head->value;
    }

    reference back()
    {
      return m_tail -> value;
    }

  private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik

int main()
{
    stepik::list<int> a;
    a.push_back(6);
    a.push_back(10);
    stepik::list<int>::iterator it = a.begin();
    a.erase(it);
    cout<<a.size()<<endl;
    a.push_front(5);
    it = a.erase(it);
    cout<<a.size();
    return 0;
}
