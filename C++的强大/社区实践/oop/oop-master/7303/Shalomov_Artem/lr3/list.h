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

    node(const Type& value, node<Type>* prev = nullptr, node<Type>* next = nullptr)
      : value(value), next(next), prev(prev)
    {
    }
  };

  template <class Type>
  class list;

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
      : m_node(nullptr)
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
        return m_node==other.m_node;
    }

    bool operator != (const list_iterator& other) const
    {
        return m_node!=other.m_node;
    }

    reference operator * ()
    {
        return m_node->value;
    }

    pointer operator -> ()
    {
        return &(m_node->value);
    }

    list_iterator& operator ++ ()
    {
        m_node = m_node -> next;
        return *this;
    }

    list_iterator operator ++ (int)
    {
        auto tmp = m_node;
        ++(*this);
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
     list(const list& other)
    {
        if(other.empty()) return;
        auto src = other.m_head;
        while(src!=nullptr){
            push_back(src->value);
            src = src->next;
        }
    }

    list(list&& other)
    {
        m_head = other.m_head;
        m_tail = other.m_tail;
        other.m_head = other.m_tail = nullptr;
    }

    list& operator= (const list& other)
    {
        clear();
        auto src = other.m_head;
        while(src!=nullptr){
            push_back(src->value);
            src = src->next;
        }
    }

    void push_back(const value_type& value)
    {
        if(empty()){
            m_head = m_tail = new node<Type>(value);
        }
        else{
            m_tail->next = new node<Type>(value,m_tail, nullptr);
            m_tail = m_tail->next;
        }
    }

    void push_front(const value_type& value)
    {
        if(empty()){
            m_head = m_tail = new node<Type>(value);
        }
        else{
            m_head->prev = new node<Type>(value,nullptr, m_head);
            m_head = m_head->prev;
        }
    }

     iterator insert(iterator pos, const Type& value)
    {
            if(pos.m_node == nullptr){
                push_back(value);
                return {m_tail};
            }
            if(pos.m_node == m_head){
                push_front(value);
                return {m_head};
            }
            auto tmp = new node<Type>(value,m_node->prev,m_node);
            tmp->prev->next = tmp->next->prev = tmp;
            return {tmp};
    }

    iterator erase(iterator pos)
    {
        if(pos.m_node == m_head){
            pop_front();
            return {m_head};
        }
        if(pos.m_node == m_tail){
            pop_back();
            return {m_tail};
        }
        pos.m_node->prev->next = pos.m_node->next;
        pos.m_node->next->prev = pos.m_node->prev;
        iterator i(pos.m_node->next);
        delete m_node;
        return i;
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
            m_head = m_tail = nullptr;
        }
        else{
            m_head = m_head->next;
            delete m_head->prev;
            m_head->prev = nullptr;
        }
    }

    void pop_back()
    {
        if(m_head == m_tail){
            delete m_head;
            m_head = m_tail = nullptr;
        }
        else{
            m_tail = m_tail->prev;
            delete m_tail->next;
            m_tail->next = nullptr;
        }
    }

    void clear()
    {
        while(!empty())
            pop_back();
    }

    bool empty() const
    {
        return !m_head;
    }

    size_t size() const
    {
        auto s = 0;
        auto p = m_head;
        while(p){
            s++;
            p = p->next;
        }
        return s;
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

}// namespace stepik
