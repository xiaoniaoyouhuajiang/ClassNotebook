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

    /* list_iterator& operator = (const list_iterator& other)
     {
     for (node<Type> *element = other.m_head; element != NULL;element = element->next){
         push_back(element->value);
     }
     }*/

    bool operator == (const list_iterator& other) const
    {
        // implement this
        return m_node == other.m_node;
    }

    bool operator != (const list_iterator& other) const
    {
        // implement this
        return m_node != other.m_node;
    }

    reference operator * ()
    {
        // implement this
        return m_node->value;
    }

    pointer operator -> ()
    {
        // implement this
        return &m_node->value;
    }

    list_iterator& operator ++ ()
    {
        // implement this
        m_node = m_node->next;
        return *this;
    }

    list_iterator operator ++ (int)
    {
        // implement this
        list_iterator a(m_node);
        m_node = m_node->next;
        return a;
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
        // implement this
        clear();
    }

    list(const list& other): m_head(nullptr), m_tail(nullptr)
    {
        for(node<Type> *el = other.m_head; el!=nullptr; el=el->next) {
            push_back(el->value);
        }


    }

    list(list&& other): m_head(other.m_head), m_tail(other.m_tail)
    {
        other.m_tail = other.m_head = nullptr;

    }

    list& operator= (const list& other)
    {
        if (this != &other)
        {
            clear();
            for (node<Type> *el = other.m_head; el != nullptr; el=el->next) {
                push_back(el->value);
            }
        }
        return *this;
    }

    void push_back(const value_type& value)
    {
        // implement this
        if (empty())
            m_head = m_tail = new node<Type>(value, nullptr, nullptr);
        else
        {
            m_tail->next = new node<Type>(value, nullptr, m_tail);
            m_tail = m_tail->next;
        }
    }

    void push_front(const value_type& value)
    {
        // implement this
        if (empty())
            m_head = m_tail = new node<Type>(value, nullptr, nullptr);
        else
        {
            m_head->prev = new node<Type>(value, m_head, nullptr);
            m_head = m_head->prev;
        }
    }

    reference front()
    {
        // implement this
        return m_head->value;
    }

    const_reference front() const
    {
        // implement this
        return m_head->value;
    }

    reference back()
    {
        // implement this
        return m_tail->value;
    }

    const_reference back() const
    {
        // implement this
        return m_tail->value;
    }

    void pop_front()
    {
        // implement this
        if (!empty())
        {
            if (m_head == m_tail)
            {
                delete (m_head);
                m_head = m_tail = nullptr;
            }
            else
            {
                m_head = m_head->next;
                delete (m_head->prev);
                m_head->prev = nullptr;
            }
        }
    }

    void pop_back()
    {
        // implement this

        if (!empty())
        {
            if (m_head == m_tail)
            {
                delete (m_head);
                m_head = m_tail = nullptr;
            }
            else
            {
                m_tail = m_tail->prev;
                delete (m_tail->next);
                m_tail->next = nullptr;
            }
        }
    }

    void clear()
    {
        // implement this
        node<Type> *old;
        for(node<Type> *el = m_head; el!=nullptr; el=el->next) {
            old = el;
            delete old;
        }
        m_head = m_tail = nullptr;
    }

    bool empty() const
    {
        // implement this
        return m_head == nullptr;
    }

    size_t size() const
    {
        size_t length = 0;
        for(node<Type>*el = m_head; el!= nullptr; el=el->next) {
            length++;
        }
        return length;
        // implement this
    }

    list::iterator begin()
    {
        return iterator(m_head);
    }

    list::iterator end()
    {
        return iterator();
    }

    iterator insert(iterator pos, const Type &value)
    {
        if (pos.m_node == NULL || pos.m_node == m_head)
            push_front(value);
        else
        {
            node<Type> *insert_el = new node<Type>(value, pos.m_node, pos.m_node->prev);
            pos.m_node->prev->next = insert_el;
            pos.m_node->prev = insert_el;
        }
        return iterator(pos.m_node->prev);
    }

    iterator erase(iterator pos)
    {
        iterator new_iter = pos.m_node->next;
        if (pos.m_node == m_head)
            pop_front();
        else if (pos.m_node == m_tail)
        {
            pop_back();
            new_iter = m_tail;
        }
        else
        {
            pos.m_node->prev->next = pos.m_node->next;
            pos.m_node->next->prev = pos.m_node->prev;
        }
        return new_iter;
    }

private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
};

}// namespace stepik
