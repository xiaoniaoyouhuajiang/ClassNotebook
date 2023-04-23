#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <utility>

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
      list_iterator retval(m_node);
      m_node = m_node->next;
      return retval;
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

    list(const list& other)
    {
      if(other.m_head == nullptr){
        m_head = nullptr;
        m_tail = nullptr;
        return;
      }
      auto cur = other.m_head;
      m_head = new node<Type>(cur->value, nullptr, nullptr);
      cur = cur->next;
      m_tail = m_head;
      while(cur != nullptr){
        m_tail->next = new node<Type>(cur->value, nullptr, m_tail);
        m_tail = m_tail->next;
        cur = cur->next;
      }
    }

    list(list&& other)
    {
      m_head = other.m_head;
      m_tail = other.m_tail;
      other.m_head = nullptr;
      other.m_tail = nullptr;
    }

    list& operator= (const list& other)
    {
      if(m_head == other.m_head)
        return *this;
      clear();
      if(other.m_head == nullptr){
        m_head = nullptr;
        m_tail = nullptr;
        return * this;
      }
      auto cur = other.m_head;
      m_head = new node<Type>(cur->value, nullptr, nullptr);
      cur = cur->next;
      m_tail = m_head;
      while(cur != nullptr){
        m_tail->next = new node<Type>(cur->value, nullptr, m_tail);
        m_tail = m_tail->next;
        cur = cur->next;
      }
      return *this;
    }
    void push_back(const value_type& value)
    {
      if(m_tail != nullptr){
        m_tail->next = new node<Type>(value, nullptr, m_tail);
        m_tail = m_tail->next;
      }
      else{
        m_head = new node<Type>(value, nullptr, nullptr);
        m_tail = m_head;
      }
    }

    void push_front(const value_type& value)
    {
      if(m_head != nullptr){
        m_head->prev = new node<Type>(value, m_head, nullptr);
        m_head = m_head->prev;
      }
      else{
        m_head = new node<Type>(value, nullptr, nullptr);
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
      return m_tail->value;
    }

    const_reference back() const
    {
      return m_tail->value;
    }

    void pop_front()
    {
      if(m_head == m_tail){
        delete m_head;
        m_head = nullptr;
        m_tail = nullptr;
        return;
      }
      if(m_head != nullptr){
        m_head = m_head->next;
        delete m_head->prev;
        m_head->prev = nullptr;
      }
    }

    void pop_back()
    {
      if(m_head == m_tail){
        delete m_head;
        m_head = nullptr;
        m_tail = nullptr;
        return;
      }
      if(m_tail != nullptr){
        m_tail = m_tail->prev;
        delete m_tail->next;
        m_tail->next = nullptr;
      }
    }

    void clear()
    {
      auto cur = m_head;
      while(cur != m_tail){
        cur = cur->next;
        delete cur->prev;
      }
      delete m_tail;
      m_head = nullptr;
      m_tail = nullptr;     
    }

    bool empty() const
    {
      return m_head == nullptr;
    }

    size_t size() const
    {
      if(m_head == nullptr)
        return 0;
      size_t count = 1;
      auto cur = m_head;
      while(cur != m_tail){
        ++count;
        cur = cur->next;
      }
      return count;
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

    iterator insert(iterator pos, const Type& value)
    {
      if(pos.m_node == nullptr){
        if(m_tail != nullptr){
          m_tail->next = new node<Type>(value, nullptr, m_tail);
          m_tail = m_tail->next;
        }
        else{
          m_head = new node<Type>(value, nullptr, nullptr);
          m_tail = m_head;
        }
        return iterator(m_tail);
      }
      else{
        auto next = pos.m_node->next;
        pos.m_node->next = new node<Type>(*pos, next, pos.m_node);
        *pos = value;
	if(next != nullptr)
	  next->prev = pos.m_node->next;
        return pos;
      }
    }

    iterator erase(iterator pos)
    {
      if(pos.m_node == nullptr)
        return pos;
      iterator retval(pos.m_node->next);
      if(pos.m_node->next != nullptr)
        pos.m_node->next->prev = pos.m_node->prev;
      else m_tail = pos.m_node->prev;
      if(pos.m_node->prev != nullptr)
        pos.m_node->prev->next = pos.m_node->next;
      else m_head = pos.m_node->next;
      delete pos.m_node;
      pos.m_node = nullptr;
      return retval;
    }

  private:
    node<Type>* m_head;
    node<Type>* m_tail;
  };

}
