#ifndef LIST_HPP
#define LIST_HPP
#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <iostream>

#define DEBUG

namespace stepik
{

void Debug(const char* str){
#ifdef DEBUG
    std::cout << "#: " << str << std::endl;
#endif //DEBUG
}

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


//================|Stepik 2_2_3|================
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
        Debug("Empty list iterator constructor");
    }

    list_iterator(const list_iterator& other)
        : m_node(other.m_node)
    {
        Debug("List iterator copy constructor");
    }

    list_iterator& operator = (const list_iterator& other)
    {
        Debug("List iterator assignment operator");
        m_node = other.m_node;
        return *this;
    }

    bool operator == (const list_iterator& other) const
    {
        Debug("List iterator comparison");
        return m_node == other.m_node;
    }

    bool operator != (const list_iterator& other) const
    {
        Debug("List iterator anticomparison");
        return m_node != other.m_node;
    }

    reference operator * ()
    {
        Debug("Reference operator");
        return m_node->value;
    }

    pointer operator -> ()
    {
        Debug("Pointer operator");
        return &(m_node->value);
    }

    list_iterator& operator ++ ()
    {
        Debug("Prefix increment operator");
        if (m_node)
            m_node = m_node->next;
        return *this;
    }

    list_iterator operator ++ (int)
    {
        Debug("Postfix increment operator");
        list_iterator keep = *this;
        m_node = m_node->next;
        return keep;
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
        Debug("Initializing empty list");
    }
    //================|Stepik 2_2_4|================
    iterator insert(iterator pos, const Type& value)
    {
        Debug("Insert operator");
        if (pos == begin()){
            push_front(value);
            return begin();
        }
        if (pos == end()){
            push_back(value);
            return iterator(m_tail);
        }
        node<Type>* new_node = new node<Type>(value, pos.m_node, pos.m_node->prev);
        new_node->prev->next = new_node;
        new_node->next->prev = new_node;
        return iterator(new_node);
    }

    iterator erase(iterator pos)
    {
        Debug("Erase operator");
        if (!pos.m_node)
            return iterator();
        if (pos == begin()){
            pop_front();
            return begin();
        }
        if (pos == iterator(m_tail)){
            pop_back();
            return end();
        }
        pos.m_node->next->prev = pos.m_node->prev;
        pos.m_node->prev->next = pos.m_node->next;
        list_iterator<Type> for_return(pos.m_node->next);
        delete pos.m_node;
        return for_return;
    }

    //================|Stepik 2_2_3|================
    list::iterator begin()
    {
        return iterator(m_head);
    }

    list::iterator end()
    {
        return iterator();
    }
    //================|Stepik 2_2_2|================
    ~list()
    {
        Debug("Destructor");
        clear();
    }

    void swap(list& first, list& second)
    {
        Debug("Swap");
        using std::swap;
        swap(first.m_head, second.m_head);
        swap(first.m_tail, second.m_tail);
    }

    list(const list& other) : list()
    {
        Debug("Copy constructor");
        for (node<Type>* otherref = other.m_head; otherref; otherref = otherref->next){
            push_back(otherref->value);
        }
    }

    list(list&& other) : list()
    {
        Debug("Move constructor");
        swap(*this, other);
    }

    list& operator= (const list& other)
    {
        Debug("Assignment copy operator");
        if (!empty())
            clear();
        for (node<Type>* otherref = other.m_head; otherref; otherref = otherref->next){
            push_back(otherref->value);
        }
        return *this;
    }


    //================|Stepik 2_2_1|================


    void push_back(const value_type& value)
    {
        Debug("Push back");
        if (!empty()){
            m_tail->next = new node<Type>(value, nullptr, m_tail);
            m_tail = m_tail->next;
        }
        else{
            m_tail = new node<Type>(value, nullptr, nullptr);
            m_head = m_tail;
        }
    }

    void push_front(const value_type& value)
    {
        Debug("Push front");
        if (!empty()){
            m_head->prev = new node<Type> (value, m_head, nullptr);
            m_head = m_head->prev;
        }
        else{
            m_head = new node<Type>(value, nullptr, nullptr);
            m_tail = m_head;
        }
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
        Debug("Pop front");
        if (m_head){
            if (m_head->next){
                m_head = m_head->next;
                delete m_head->prev;
                m_head->prev = nullptr;
            }
            else{
                delete m_head;
                m_head = nullptr;
                m_tail = nullptr;
            }
        }
    }

    void pop_back()
    {
        Debug("Pop back");
        if (m_tail){
            if (m_tail->prev){
                m_tail = m_tail->prev;
                delete m_tail->next;
                m_tail->next = nullptr;
            }
            else{
                delete m_tail;
                m_tail = nullptr;
                m_head = nullptr;
            }
        }
    }

    void clear()
    {
        Debug("Clear");
        while (!empty())
            pop_back();
    }

    bool empty() const
    {
        return (!m_head && !m_tail);
    }

    size_t size() const
    {
        node<Type>* ref = m_head;
        size_t res;
        for (res = 0; ref; res
             ++, ref = ref->next);
        return res;
    }

    void out(){
        std::cout << "OUT: " << size() << ": ";
        for (node<Type>* ref = m_head; ref; ref = ref->next){
            std::cout << ref->value << " ";
        }
        std::cout << std::endl;
    }

    void out_it(){
        std::cout << "OUT_IT: " << size() << ": ";
        for(list_iterator<Type> it = begin(); it != end(); it++){
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
};

}// namespace stepik
#endif // LIST_HPP
