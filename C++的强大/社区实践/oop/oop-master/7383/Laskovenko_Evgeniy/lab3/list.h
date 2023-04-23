#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>

#ifndef LIST_H
#define LIST_H

template <class Type>
struct node
{
    Type value;
    node* next;
    node* prev;

    node(const Type& value, node<Type>* next, node<Type>* prev)
        : value(value), next(next), prev(prev) {}
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
        : m_node(NULL) {}

    list_iterator(const list_iterator& other)
        : m_node(other.m_node) {}

    list_iterator& operator = (const list_iterator& other)
    {
        m_node = other.m_node;

        return *this;
    }

    bool operator == (const list_iterator& other) const
    { return m_node == other.m_node; }

    bool operator != (const list_iterator& other) const
    { return m_node != other.m_node; }

    reference operator * ()
    { return m_node->value; }

    pointer operator -> ()
    { return &(m_node->value); }

    list_iterator& operator ++ ()
    {
        m_node = m_node ? m_node->next : nullptr;

        return *this;
    }

    list_iterator operator ++ (int)
    {
        list_iterator tmp = *this;
        ++(*this);

        return tmp;
    }

private:
    friend class list<Type>;

    list_iterator(node<Type>* p)
        : m_node(p) {}

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
        : m_head(nullptr), m_tail(nullptr) {}

    ~list()
    {
        while(m_head)
        {
            delete m_head->prev;
            m_head = m_head->next;
        }
        delete m_tail;
    }

    list(const list& other) : list()
    {
        if(!(other.empty()))
        {
            node<value_type>* it = other.m_head;
            node<value_type>* tmp = new node<value_type>(it->value, nullptr, nullptr);
            node<value_type>* n_head = tmp;
            for(size_t i=1; i<other.size(); ++i)
            {
                it = it->next;
                tmp = new node<value_type>(it->value, nullptr, tmp);
                tmp->prev->next = tmp;
            }

            m_head = n_head;
            m_tail = tmp;
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
        if(this->m_head != other.m_head)
        {
            this->clear();
            if(!(other.empty()))
            {
                node<value_type>* it = other.m_head;
                node<value_type>* tmp = new node<value_type>(it->value, nullptr, nullptr);
                node<value_type>* n_head = tmp;
                for(size_t i=1; i<other.size(); ++i)
                {
                    it = it->next;
                    tmp = new node<value_type>(it->value, nullptr, tmp);
                    tmp->prev->next = tmp;
                }

                m_head = n_head;
                m_tail = tmp;
            }
            else
                m_head = m_tail = nullptr;
        }

        return *this;
    }

    void push_back(const value_type& value)
    {
        node<value_type>* new_el = new node<value_type>(value, nullptr, m_tail);
        if(empty())
        {
            m_head = m_tail = new_el;
            return;
        }

        m_tail->next = new_el;
        m_tail = new_el;
    }

    void push_front(const value_type& value)
    {
        node<value_type>* new_el = new node<value_type>(value, m_head, nullptr);
        if(empty())
        {
            m_head = m_tail = new_el;
            return;
        }

        m_head->prev = new_el;
        m_head = new_el;
    }

    reference front()
    {
        if(!empty())
            return m_head->value;
    }

    const_reference front() const
    {
        if(!empty())
            return m_head->value;
    }

    reference back()
    {
        if(!empty())
            return m_tail->value;
    }

    const_reference back() const
    {
        if(!empty())
            return m_tail->value;
    }

    void pop_front()
    {
        if(empty())
            return;

        if(m_head->next)
        {
            m_head = m_head->next;
            delete m_head->prev;
            m_head->prev = nullptr;
        }
        else
        {
            delete m_head;
            m_head = m_tail = nullptr;
        }
    }

    void pop_back()
    {
        if(empty())
            return;

        if(m_tail->prev)
        {
            m_tail = m_tail->prev;
            delete m_tail->next;
            m_tail->next = nullptr;
        }
        else
        {
            delete m_tail;
            m_head = m_tail = nullptr;
        }
    }

    iterator insert(iterator pos, const Type& value)
    {
        if(pos.m_node == nullptr)
        {
            push_back(value);
            return iterator(m_tail);
        }
        if(pos.m_node == m_head)
        {
            push_front(value);
            return iterator(m_head);
        }

        node<Type>* nw = new node<Type>(value, pos.m_node, pos.m_node->prev);
        pos.m_node->prev->next = nw;
        pos.m_node->prev = nw;

        return iterator(nw);
    }

    iterator erase(iterator pos)
    {
        if(pos.m_node == m_head)
        {
            pop_front();
            return iterator(m_head);
        }
        if(pos.m_node == m_tail)
        {
            pop_back();
            return iterator(m_tail);
        }

        pos.m_node->prev->next = pos.m_node->next;
        pos.m_node->next->prev = pos.m_node->prev;
        iterator res(pos.m_node->next);
        delete pos.m_node;

        return res;
    }

    void clear()
    {
        node<value_type>* tmp = m_head;
        for(size_t i=0; i<size(); ++i)
        {
            m_head = tmp->next;
            delete tmp;
            tmp = m_head;
        }
    }

    bool empty() const
    { return m_head == nullptr; }

    size_t size() const
    {
        size_t sz = 0;
        node<value_type>* tmp = m_head;
        while(tmp)
        {
            tmp = tmp->next;
            sz++;
        }

        return sz;
    }

private:
  //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
};

#endif // LIST_H
