
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
        if(this != &other) {
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
        return (m_node = m_node->next, *this);
    }

    list_iterator operator ++ (int)
    {
        auto tmp = *this;
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
        if(empty()) {
            m_tail = new node<Type>(value, nullptr, nullptr);
            m_head = m_tail;
        } else {
            m_head->prev = new node<Type>(value, m_head, nullptr);
            m_head = m_head->prev;
        }
    }

    void push_back(const value_type& value)
    {
        if(empty()) {
            m_tail = new node<Type>(value, nullptr, nullptr);
            m_head = m_tail;
        } else {
            m_tail->next = new node<Type>(value, nullptr, m_tail);
            m_tail = m_tail->next;
        }
    }

    iterator insert(iterator pos, const Type& value)
    {
        if(!pos.m_node) {
            push_back(value);
            return iterator(m_tail);
        }
        if(pos == begin()) {
            push_front(value);
            return begin();
        }

        node<Type>* new_node = new node<Type>(value, pos.m_node, pos.m_node->prev);
        pos.m_node->prev->next = new_node;
        pos.m_node->prev = new_node;

        return new_node;
    }

    iterator erase(iterator pos)
    {
        if(!pos.m_node) {
            return end();
        }
        if(pos == begin()) {
            pop_front();
            return iterator(m_head);
        }
        if(pos == iterator(m_tail)) {
            pop_back();
            return end();
        }

        node<Type>* to_return = pos.m_node->next;

        pos.m_node->next->prev = pos.m_node->prev;
        pos.m_node->prev->next = pos.m_node->next;

        delete pos.m_node;
        return to_return;
    }

    reference front()
    {
        return m_head->value;
    }

    reference back()
    {
        return m_tail->value;
    }

    void pop_back()
    {
        if (!empty()) {
            node<Type>* removable = m_tail;

            if (size() == 1) {
                m_tail = m_head = nullptr;
            } else {
                m_tail = m_tail->prev;
                m_tail->next = nullptr;
            }

            delete removable;
        }
    }

    void clear()
    {
        while(!empty())
            pop_back();
    }

    bool empty() const
    {
        return (m_head == nullptr);
    }

    size_t size() const
    {
        size_t size = 0;
        for(node<Type>* slider = m_head; slider != nullptr; slider = slider->next)
            size++;
        return size;
    }

    void pop_front()
    {
        if (!empty()) {
            node<Type>* removable = m_head;

            if (size() == 1) {
                m_tail = m_head = nullptr;
            } else {
                m_head = m_head->next;
                m_head->prev = nullptr;
            }

            delete removable;
        }
    }
private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
};

}// namespace stepik