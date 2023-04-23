#ifndef LAB3_H
#define LAB3_H

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
    node<Type>* next;
    node<Type>* prev;

    node<Type>(const Type& value, node<Type>* next, node<Type>* prev)
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
        list_iterator tmp(other);
        swap(tmp);

        return *this;
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
        m_node = m_node->next;

        return *this;
    }

  private:
    friend class list<Type>;

    list_iterator(node<Type>* p)
      : m_node(p)
    {
    }

    void swap(list_iterator& other) noexcept
    {
        std::swap(m_node, other.m_node);
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

    list() //constructor
      : m_head(nullptr), m_tail(nullptr)
    {
    }

    ~list() //destructor
    {
        clear();
    }
    //Copy and move constructors
    list(const list& other) :
        m_head(nullptr), m_tail(nullptr)
    {
        for (node<Type>* ptr = other.m_head; ptr; ptr = ptr->next)
        {
            push_back(ptr->value);
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
        list tmp(other);
        swap(tmp);
    }
    //insert elements into the head and tail
    void push_back(const value_type& value)
    {
        if (m_head && m_tail)
        {
            m_tail->next = new node<Type>(value, nullptr, m_tail);
            m_tail = m_tail->next;
        }
        else
        {
            // empty list
            m_head = m_tail = new node<Type>(value, nullptr, nullptr);
        }
    }

    void push_front(const value_type& value)
    {
        if (m_head && m_tail)
        {
            node<Type>* new_node = new node<Type>(value, m_head, nullptr);
            m_head->prev = new_node;

            m_head = new_node;
        }
        else
        {
            // empty list
            m_head = m_tail = new node<Type>(value, nullptr, nullptr);
        }
    }

    iterator insert(iterator pos, const Type& value)
    {
        node<Type>* ptr = pos.m_node;
        node<Type>* new_node = nullptr;


        if (ptr)
        {
            bool prev_empty = (ptr->prev == nullptr);
            bool next_empty = (ptr->next == nullptr);

            if (prev_empty)
            {
                push_front(value);
                return begin();
            }
            else
            {
                new_node = new node<Type>(value, ptr, ptr->prev);

                ptr->prev->next = new_node;
                ptr->prev = new_node;

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
        node<Type>* ptr = pos.m_node;

        if (ptr)
        {
            bool prev_empty = (ptr->prev == nullptr);
            bool next_empty = (ptr->next == nullptr);

            if (prev_empty)
            {
                if (next_empty)
                {
                    pop_back();
                    return nullptr;
                }
                else
                {
                    pop_front();
                    return m_head;
                }
            }
            else
            {
                if (next_empty)
                {
                    pop_back();
                    return nullptr;
                }
                else
                {
                    node<Type>* ret = ptr->next;

                    ptr->prev->next = ptr->next;
                    ptr->next->prev = ptr->prev;

                    delete ptr;

                    return ret;
                }
            }

        }
    }
    //get an element from the head and from the tail
    reference front()
    {
        if (m_head) return m_head->value;
    }

    const_reference front() const
    {
        if (m_head) return m_head->value;
    }

    reference back()
    {
        if (m_tail) return m_tail->value;
    }

    const_reference back() const
    {
        if (m_tail) return m_tail->value;
    }
    //delete from head, tail and cleaning
    void pop_front()
    {
        if (m_head)
        {
            node<Type>* next_node = m_head->next;
            delete m_head;

            if (next_node)
                next_node->prev = nullptr;
            else
                m_tail = nullptr;

            m_head = next_node;
        }
    }

    void pop_back()
    {
        if (m_tail)
        {
            node<Type>* prev_node = m_tail->prev;
            delete m_tail;

            if (prev_node)
                prev_node->next = nullptr;
            else
                m_head = nullptr;

            m_tail = prev_node;
        }
    }

    void clear()
    {
        node<Type>* ptr_curr = m_head;
        node<Type>* ptr_next = nullptr;

        while (ptr_curr)
        {
            ptr_next = ptr_curr->next;
            delete ptr_curr;
            ptr_curr = ptr_next;
        }

        m_head = m_tail = nullptr;
    }

    bool empty() const
    {
        return (m_head == nullptr);
    }
    //check the size
    size_t size() const
    {
        size_t count = 0;

        for (node<Type>* ptr = m_head; ptr; ptr = ptr->next)
            count++;

        return count;
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

    void swap(list& other) noexcept
    {
        std::swap(m_head, other.m_head);
        std::swap(m_tail, other.m_tail);
    }
  };

}// namespace stepik

#endif // LAB3_H
