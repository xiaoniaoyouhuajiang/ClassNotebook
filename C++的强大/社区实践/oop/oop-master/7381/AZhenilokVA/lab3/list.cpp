#include <iostream>
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
    class list; 

    template <class Type>
    class list_iterator
    {
    public:
        friend class list<Type>;

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

        list_iterator(node<Type>* p) 
        : m_node(p)
        {
        }

        list_iterator(const list_iterator& other)
        : m_node(other.m_node)
        {
        }

        list_iterator& operator=(const list_iterator& other)
        {
            m_node = other.m_node;
            return (*this);
        }

        bool operator == (const list_iterator& other) const
        {
            return (m_node == other.m_node);
        }

        bool operator != (const list_iterator& other) const
        {
            return (m_node != other.m_node);
        }

        reference operator * ()
        {
            return (m_node->value);
        }

        pointer operator->()
        {
            return (m_node);
        }

        list_iterator& operator++()
        {
            m_node = m_node->next;
            return (*this);
        }

        list_iterator operator++(int)
        {
            list_iterator* old_iterator = new list_iterator(*this);
            m_node = m_node->next;
            return (*old_iterator);
        }

    private:
        node<Type>* m_node;
    };

    template <class Type>
    class list
    {
    public:
        typedef list_iterator<Type> iterator;
        typedef Type value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;

        list() : m_head(nullptr), m_tail(nullptr), m_size(0)
        {
        }

        ~list()
        {
            clear();
        }

        list(const list& other) : m_head(nullptr), m_tail(nullptr), m_size(0)
        {
            for (node<Type>* Pnode = other.m_head; Pnode; Pnode = Pnode->next)
                push_back(Pnode->value);
        }

        list(list&& other) : m_head(nullptr), m_tail(nullptr), m_size(0)
        {
            std::swap(m_head, other.m_head);
            std::swap(m_tail, other.m_tail);
            std::swap(m_size, other.m_size);
        }

        list& operator=(const list& other)
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

        iterator insert(iterator pos, const Type& value)
        {
            node<Type>* Pnode = pos.m_node;
            if (Pnode == nullptr)
            {
                push_back(value);
                return iterator(m_tail);
            }
            else if (Pnode->prev == nullptr)
            {
                push_front(value);
                return iterator(m_head);
            }
            node<Type>* new_node = new node<Type>(value, Pnode, Pnode->prev);
            Pnode->prev->next = new_node;
            Pnode->prev = new_node;
            ++m_size;
            return iterator(new_node);
        }

        iterator erase(iterator pos)
        {
            node<Type>* Pnode = pos.m_node;

            if (Pnode == nullptr)
                return pos;
                
            if (Pnode->prev == nullptr)
            {
                pop_front();
                return iterator(m_head);
            }

            if (Pnode->next == nullptr)
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

        void push_back(const value_type& value)
        {
            node<Type>* new_node = new node<Type>(value, nullptr, m_tail);
            if (m_size == 0)
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
            if (m_size == 0)
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

        void pop_front()
        {
            --m_size;
            node<Type>* new_head = m_head->next;
            delete m_head;
            m_head = new_head;
            if (m_size == 0)
            {
                m_tail = nullptr;
            }
            else 
            {
                m_head->prev = nullptr;
            }
        }

        void pop_back()
        {
            --m_size;
            node<Type>* new_tail = m_tail->prev;
            delete m_tail;
            m_tail = new_tail;
            if (m_size == 0)
            {
                m_head = nullptr;
            }
            else 
            {
                m_tail->next = nullptr;
            }
        }

        void clear()
        {
            node<Type>* Pnode = m_head;
            node<Type>* Pnext;
            while (Pnode)
            {
                Pnext = Pnode->next;
                delete Pnode;
                Pnode = Pnext;
            }
            m_head = m_tail = nullptr;
            m_size = 0;
        }

        reference front()
        {
            return (m_head->value);
        }

        const_reference front() const
        {
            return (m_head->value);
        }

        reference back()
        {
            return (m_tail->value);
        }

        const_reference back() const
        {
            return (m_tail->value);
        }

        bool empty() const
        {
            return (!m_size);
        }

        size_t size() const
        {
            return (m_size);
        }

        iterator begin() const
        {
            return iterator(m_head);
        }

        iterator end() const
        {
            return iterator();
        }

    private:
        node<Type>* m_head;
        node<Type>* m_tail;
        size_t m_size;
    };
}// namespace stepik