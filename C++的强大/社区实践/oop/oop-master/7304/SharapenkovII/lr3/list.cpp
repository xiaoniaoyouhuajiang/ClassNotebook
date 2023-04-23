#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <iostream>
#include <list>

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
                : m_head(nullptr), m_tail(nullptr), m_size(0)
        {
        }

        ~list()
        {
            clear();
        }

        list(const list& other)
                : m_head(nullptr), m_tail(nullptr), m_size(0)
        {
            auto current = other.m_head;

            while(current) {
                push_back(current->value);
                current = current->next;
            }
        }

        list(list&& other) noexcept
                : m_head(nullptr), m_tail(nullptr), m_size(0)
        {
            m_size = other.m_size;
            m_head = other.m_head;
            m_tail = other.m_tail;

            other.m_head = nullptr;
            other.m_tail = nullptr;
        }

        list& operator= (const list& other)
        {
            clear();

            auto current = other.m_head;

            while(current) {
                push_back(current->value);
                current = current->next;
            }

            return *this;
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
            auto new_node = new node<Type>(value, nullptr, nullptr);

            if(m_head == nullptr) {
                m_head = new_node;
                m_tail = new_node;
            } else {
                m_tail->next = new_node;
                new_node->prev = m_tail;
                m_tail = new_node;
            }

            m_size++;
        }

        void push_front(const value_type& value)
        {
            auto new_node = new node<Type>(value, nullptr, nullptr);

            if(m_head == nullptr) {
                m_head = new_node;
                m_tail = new_node;
            } else {
                m_head->prev = new_node;
                new_node->next = m_head;
                m_head = new_node;
            }

            m_size++;
        }

        iterator insert(iterator pos, const Type& value)
        {
            auto new_node = new node<Type>(value, nullptr, nullptr);
            auto node = pos.m_node;

            if(node) {
                if(node->prev) {
                    node->prev->next = new_node;
                    new_node->prev = node->prev;
                    new_node->next = node;
                    node->prev = new_node;
                } else {
                    new_node->prev = node->prev;
                    new_node->next = node;
                    node->prev = new_node;
                    m_head = new_node;
                }
            } else {
                if(empty()) {
                    m_head = new_node;
                    m_tail = new_node;
                } else {
                    new_node->prev = m_tail;
                    m_tail->next = new_node;
                    m_tail = new_node;
                }
            }

            m_size++;
            return iterator(new_node);
        }

        iterator erase(iterator pos)
        {
            auto node = pos.m_node;

            if (node->prev) {
                node->prev->next = node->next;
                if (node->next) node->next->prev = node->prev;
                else m_tail = node->prev;
            } else {
                m_head = node->next;
                if (m_head) node->next->prev = nullptr;
                else m_head = nullptr;
            }

            m_size--;
            auto next = node->next;
            return iterator(next);
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
            node<Type> *tmp = m_head;

            if(m_head != nullptr) {
                if(m_head->next) m_head->next->prev = nullptr;
                else m_tail = nullptr;
                m_head = m_head->next;
                m_size--;
                delete tmp;
            }
        }

        void pop_back()
        {
            node<Type> *tmp = m_tail;

            if(m_head != nullptr) {
                if(m_tail->prev) m_tail->prev->next = nullptr;
                else m_head = nullptr;
                m_tail = m_tail->prev;
                m_size--;
                delete tmp;
            }
        }

        void clear()
        {
            while(!empty())
                pop_front();
        }

        bool empty() const
        {
            return !m_head;
        }

        size_t size() const
        {
            return m_size;
        }

    private:
        node<Type>* m_head;
        node<Type>* m_tail;
        size_t m_size;
    };

}// namespace stepik


int main() {

    stepik::list<int> a;

    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_front(4);



    std::cout << *a.insert(a.begin(), 10) << std::endl;
    std::cout << a.front() << std::endl;
    return 0;
}