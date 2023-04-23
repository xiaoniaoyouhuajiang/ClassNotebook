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
        if (*this != other)
            m_node = other.m_node;
            return *this;
    }

    bool operator == (const list_iterator& other) const
    {
        return m_node == other.m_node;
    }

    bool operator != (const list_iterator& other) const
    {
        return !(*this==other);
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
        auto tmp = m_node;
            m_node = m_node->next;

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

    list(const list& other):m_head(nullptr),m_tail(nullptr)
    {
        node<Type>* tmp = other.m_head;
        while (tmp) {
            push_back(tmp->value);
            tmp = tmp->next;
        }
    }

    list(list&& other):m_head(nullptr),m_tail(nullptr)
    {
        std::swap(m_head, other.m_head);
        std::swap(m_tail, other.m_tail);
    }

    list& operator= (const list& other)
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

    void push_back(const value_type& value)
    {
        if (!empty())
        {
            auto tmp = m_tail;
            m_tail = new node<value_type>(value,nullptr,tmp);

            tmp->next = m_tail;
        }
        else
        {
            init(value);
        }
      // use previous step implementation
    }

    void push_front(const value_type& value)
    {
        if (!empty())
        {
            m_head->prev = new node<value_type>(value, m_head, nullptr);
            m_head = m_head->prev;
        }
        else
        {
            init(value);
        }
    }
    iterator insert(interator pos,const Type& value)
    {
        auto& inserted = pos.m_node;

            if (inserted == nullptr) 
            {
                push_back(value); 

                return iterator(m_tail);
            }

            if (inserted->prev == nullptr) 
            {
                push_front(value); 
                return iterator(m_head);
            }

            auto new_node = new node<Type>(value, inserted, inserted->prev);
            
            inserted->prev->next = new_node;
            inserted->prev = new_node;
            
            return iterator(new_node);
    }
    iterator erase(iterator pos)
    {
        auto& inserted = pos.m_node;

            if (inserted == nullptr) 
                return pos;

            if (inserted->next == nullptr) 
            {
                pop_back(); 
                
                return nullptr;
            }

            if (inserted->prev == nullptr) 
            {
                pop_front(); 

                return iterator(m_head);
            }

            auto returned = inserted->next;
            inserted->prev->next = inserted->next;
            inserted->next->prev = inserted->prev;

            delete inserted;

            return returned; 
    }

    reference front()
    {
        return m_head->value;
    }

    const_reference front() const
    {
        return front();
    }

    reference back()
    {
         return m_tail->value;
        
    }

    const_reference back() const
    {
        return back();
    }

    void pop_front()
    {
        if (!empty())
        {
            if (single())
            {
                destroy();
            }
            else {
            auto del = m_head;
            m_head = m_head->next;
            m_head->prev = nullptr;
            delete del;
            }
        }
    }

    void pop_back()
    {
        if (!empty())
        {
            if (single())
            {
                destroy();
            }
            else 
            {
            auto del = m_tail;
            m_tail = m_tail->prev;
            m_tail->next = nullptr;
            delete del;
            }
        }
    }

    void clear()
    {
        while (!empty()) pop_back();
      // implement this     
    }

    bool empty() const
    {
        return m_head==nullptr;
    }

    size_t size() const
    {
        if (empty()) return 0;
        size_t size = 0;
        for (auto it = m_head; it != m_tail; it = it->next)
        {
            size++;
        }
        size++; //tail
        return size;

    }
    
  private:
    //your private functions
    void init(const value_type& value)
    {
        m_head = new node<value_type>(value, nullptr, nullptr);
        m_tail = m_head;
    }

    void destroy()
    {
        delete m_head;
        m_head = m_tail = nullptr;
    }

    bool single()
    {
        return m_tail==m_head;
    }
    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik