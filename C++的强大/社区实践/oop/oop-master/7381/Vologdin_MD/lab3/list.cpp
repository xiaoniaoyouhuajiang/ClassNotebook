#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <iostream>
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
        return !(m_node == other.m_node);
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
        if (m_node != nullptr)
            m_node = m_node->next;
        return *this;
    }

    list_iterator operator ++ (int)
    {
        list_iterator* temp = new list_iterator(*this);
        ++(*this);
        return (*temp);
    }
    //////////////////////
    list_iterator& operator -- ()
    {
        if (m_node != nullptr)
            m_node = m_node->prev;
        return *this;
    }

    list_iterator operator -- (int)
    {
        
        list_iterator* temp = new list_iterator(*this);
        --(*this);
        return (*temp);
    }
    //////////////////////
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
      : m_head(nullptr), m_tail(nullptr), m_size(0)
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

    list(const list& other) : m_head(nullptr), m_tail(nullptr), m_size(0)
    {
        for (node<Type>* Pnode = other.m_head; Pnode; Pnode = Pnode->next)
            push_back(Pnode->value);
    }


    list(list&& other): m_head(nullptr), m_tail(nullptr), m_size(0)
    {
        std::swap(m_head, other.m_head);
        std::swap(m_tail, other.m_tail);
        std::swap(m_size, other.m_size);
    }

    list& operator= (const list& other)
    {
        clear();
        for (node<Type>* Pnode = other.m_head; Pnode; Pnode = Pnode->next)
            push_back(Pnode->value);
        return (*this);
    }
    
    list& operator=(list&& other)
    {
        std::swap(m_head, other.m_head);
        std::swap(m_tail, other.m_tail);
        std::swap(m_size, other.m_size);
        return (*this);
    }

    void push_back(const value_type& value)
    {
        node<Type>* new_node = new node<Type>(value, nullptr, m_tail);
        if (empty())
        {
            m_head = m_tail = new_node;
        }
        else 
        {
            m_tail->next = new_node;
            m_tail = new_node;
        }
        ++m_size;
    }

    void push_front(const value_type& value)
    {
        node<Type>* new_node = new node<Type>(value, m_head, nullptr);
        if (empty())
        {
            m_head = m_tail = new_node;
        }
        else
        {
            m_head->prev = new_node;
            m_head = new_node;
        }
        ++m_size;
    }

    iterator insert(iterator pos, const Type& value)
    {
        node<Type>* Pnode = pos.m_node;

        if (Pnode) 
        {
            if (Pnode == m_head) 
            {
                push_front(value);
                return iterator(m_head);
            }
            else 
            {
                node<Type>* new_node = new node<Type>(value, Pnode, Pnode->prev);
                Pnode->prev->next = new_node;
                Pnode->prev = new_node;
                ++m_size;
                return iterator(new_node);
            }
        }
        else
        {
            push_back(value);
            return iterator(m_tail);
        }
    }

    iterator erase(iterator pos)
    {
        node<Type>* Pnode = pos.m_node;

            if (Pnode == nullptr)
                return pos;
                
            if (Pnode == m_head)
            {
                pop_front();
                return iterator(m_head);
            }

            if (Pnode == m_tail)
            {
                pop_back();
                return iterator();
            }
            
            node<Type>* Pnext = Pnode->next;
            Pnode->next->prev = Pnode->prev;
            Pnode->prev->next = Pnode->next;
            delete Pnode;
            --m_size;
            return iterator(Pnext);
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
        if(!empty())
        {
            --m_size;
            if (m_head==m_tail)
            {
                    delete m_head;
                    m_head=m_tail=nullptr;
            }
            else 
            {
                node<Type>* temp=m_head->next;
                delete m_head;
                m_head=temp;
                m_head->prev = nullptr;
            }
        }
    }

    void pop_back()
    {
        if(!empty())
        {
            --m_size;
            if (m_head==m_tail)
            {
                delete m_head;
                m_head=m_tail=nullptr;
            }
            else
            {
                node<Type>* temp=m_tail->prev;
                delete m_tail;
                m_tail=temp;
                m_tail->next = nullptr;    
            }
    }
    }
    void clear()
    {
        while(!empty())
            pop_back();  
    }

    bool empty() const
    {
        return !m_size;
    }

    size_t size() const
    {
        return m_size;
    }

  private:
    //your private functions
    size_t m_size;
    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik