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

    node(const Type& value, node<Type>* next, node<Type>* prev)
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
        return &(m_node->value);
    }

    list_iterator& operator ++ ()
    {
        m_node = m_node->next;
        return *this;
    }

    list_iterator operator ++ (int)
    {
        list_iterator tmp(*this);
        m_node = tmp.m_node->next;
        return *this;
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
        if(empty())
        {
            m_tail = new node<Type>(value, nullptr, nullptr);
            m_head = m_tail;
        }
        else
        {
            m_tail->next = new node<Type>(value, nullptr, m_tail);
            m_tail = m_tail->next;
        }
    }

    void push_front(const value_type& value)
    {
        if(empty())
        {
            m_tail = new node<Type>(value, nullptr, nullptr);
            m_head = m_tail;
        }
        else
        {
            m_head->prev = new node<Type>(value, m_head, nullptr);
            m_head = m_head->prev;
        }
    }

    reference front()
    {
        return m_head->value;
    }

    const_reference front() const
    {
        return m_tail->value;
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
        if(empty())
            return;
        if(m_head->next != nullptr)
        {
            m_head = m_head->next;
            delete m_head->prev;
            m_head->prev = nullptr;

        }
        else
        {
            delete m_head;
            m_head = nullptr;
            m_tail = nullptr;
        }
    }

    void pop_back()
    {
        if(empty())
            return;
        if(m_tail->prev != nullptr)
        {
            
            m_tail = m_tail->prev;
            delete m_tail->next;
            m_tail->next = nullptr;
            
        }
        else
        {
            delete m_tail;
            m_head = nullptr;
            m_tail = nullptr;
        }
    }

    void clear()
    {    
        while(!empty())
            pop_back();
    }

    bool empty() const
    {
        return m_head == nullptr;
    }

    size_t size() const
    {
        size_t count = 0;
        node<Type>* tmp = m_head;
        while(tmp)
        {
            tmp = tmp->next;
            count++;
        }
        return count;
    }
    ~list()
    {  
        clear();
    }

    list(const list& other):m_head(nullptr), m_tail(nullptr)
    {
        node<Type>* tmp = other.m_head;
        while(tmp)
        {
            push_back(tmp->value);
            tmp = tmp->next;
        }
    }

    list(list&& other):m_head(other.m_head), m_tail(other.m_tail)
    {
        other.m_head = nullptr;
        other.m_tail = nullptr;
    }

    list& operator= (const list& other)
    {
      if (m_head == other.m_head)
          return *this;
      clear();
      node<Type>* tmp = other.m_head;
      while (tmp){
          push_back(tmp->value);
          tmp = tmp->next;
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

    iterator insert(iterator pos, const Type& value)
    {
        if( empty() || pos.m_node == m_head)
        {
            push_front(value);
            return iterator(m_head);
        }
        else
        {
            node<Type>* tmp = new node<Type>(value, pos.m_node, pos.m_node->prev);
            pos.m_node -> prev -> next = tmp;
            pos.m_node -> prev = tmp;
            return iterator(tmp);
        }
        
    }

    iterator erase(iterator pos)
    {
        if(pos.m_node == m_head)
        {
            pop_back();
            return pos;
        }
        if(pos.m_node == m_tail)
        {
            pop_front();
            return iterator(m_tail);
        }
        pos.m_node -> next -> prev = pos.m_node -> prev;
        pos.m_node -> prev -> next = pos.m_node ->next;
        iterator tmp(pos.m_node ->next);
        delete pos.m_node;
        return tmp;
    }
private:
    node<Type>* m_head;
    node<Type>* m_tail;
};

