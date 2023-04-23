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
        {}
    };

    template <class Type>
    class list; 

    template <class Value>
    class list_iterator
    {
    public:
        friend class list<Value>;

        typedef ptrdiff_t difference_type;
        typedef Value value_type;
        typedef Value* pointer;
        typedef Value& reference;
        typedef size_t size_type;
        typedef std::forward_iterator_tag iterator_category;

        list_iterator()
            : m_node(NULL)
        {}

        list_iterator(const list_iterator& other)
            : m_node(other.m_node)
        {}

        list_iterator(node<Value>* p) : m_node(p)
        {}

        list_iterator& operator = (const list_iterator& other)
        {
            if (*this != other)
                m_node = other.m_node;

            return *this;
        }

        bool operator ==(const list_iterator& other) const
        {
            return m_node == other.m_node;
        }

        bool operator != (const list_iterator& other) const
        {
            return !(*this == other);
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
        node<Value>* m_node;
    };

    template <class Type>
    class list
    {
    public:
        typedef list_iterator<Type> iterator;
        typedef Type value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;

        list() : m_head(nullptr), m_tail(nullptr)
        {}

        ~list()
        {
            clear();
        }

        list(const list& other) : m_head(nullptr), m_tail(nullptr)
        {
            if (!other.empty())
            {
                for (auto it = other.m_head; it != other.m_tail; it = it->next)
                {
                    push_back(it->value);
                }
                push_back(other.m_tail->value); // For tail
            }
        }

        list(list&& other) noexcept : m_head(nullptr), m_tail(nullptr)
        {
            std::swap(m_head, other.m_head);
            std::swap(m_tail, other.m_tail);
        }

        iterator insert(iterator pos, const Type& value)
        {
            auto& pos_node = pos.m_node;

            if (pos_node == nullptr) 
            {
                push_back(value); 

                return iterator(m_tail);
            }

            if (pos_node->prev == nullptr) 
            {
                push_front(value); 
                return iterator(m_head);
            }

            auto new_node = new node<Type>(value, pos_node, pos_node->prev);
            
            pos_node->prev->next = new_node;
            pos_node->prev = new_node;
            
            return iterator(new_node);
        }

        iterator erase(iterator pos)
        {
            auto& pos_node = pos.m_node;

            if (pos_node == nullptr) 
                return pos;

            if (pos_node->next == nullptr) 
            {
                pop_back(); 
                
                return nullptr;
            }

            if (pos_node->prev == nullptr) 
            {
                pop_front(); 

                return iterator(m_head);
            }

            auto ret = pos_node->next;
            pos_node->prev->next = pos_node->next;
            pos_node->next->prev = pos_node->prev;

            delete pos_node;

            return ret;
        }

        void push_back(const value_type& value)
        {
            if (!empty())
            {
                auto old_tail = m_tail;
                m_tail = new node<value_type>(value, nullptr, nullptr);

                m_tail->prev = old_tail;
                old_tail->next = m_tail;
            }
            else
            {
                create_first_node(value);
            }
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
                create_first_node(value);
            }
        }

        void pop_front()
        {
            if (only_one_node())
            {
                delete_last_node();
            }
            else
            {
                auto head_to_del = m_head;
                m_head = m_head->next;
                m_head->prev = nullptr;

                delete head_to_del;
            }
        }

        void pop_back()
        {
            if (only_one_node())
            {
                delete_last_node();
            }
            else
            {
                auto tail_to_del = m_tail;
                m_tail = m_tail->prev;
                m_tail->next = nullptr;

                delete tail_to_del;
            }
        }

        void clear()
        {
            while (!empty())
            {
                pop_back();
            }

            m_head = m_tail = nullptr;
        }

        bool empty() const
        {
            return (m_head == nullptr || m_tail == nullptr);
        }

        size_t size() const
        {
            if (empty())
                return 0;

            size_t size = 0;
            for (auto it = m_head; it != m_tail; it = it->next)
            {
                size++;
            }
            size++; // For tail

            return size;
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
    private:
        void create_first_node(const value_type& value)
        {
            m_head = new node<value_type>(value, nullptr, nullptr);
            m_tail = m_head;
        }

        void delete_last_node()
        {
            delete m_head;
            m_head = m_tail = nullptr;
        }

        bool only_one_node()
        {
            return m_head == m_tail && m_head != nullptr;
        }
    };

}// namespace stepik