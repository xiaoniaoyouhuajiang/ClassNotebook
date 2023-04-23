//
// Created by 1 on 10.03.2019.
//

#ifndef VECTOR_LIST_H
#define VECTOR_LIST_H
#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <iostream>

using  namespace std;
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
        if(this!=&other)
            m_node=other.m_node;
        return *this;
    }

    bool operator == (const list_iterator& other) const
    {
        return m_node==other.m_node;
    }

    bool operator != (const list_iterator& other) const
    {
        return m_node!=other.m_node;
    }

    reference operator * ()
    {
        return m_node->value;
    }

    pointer operator -> ()
    {
        return &(m_node->value);
    }

    list_iterator& operator -- ()
    {
        m_node=m_node->prev;
        return *this;
    }

    list_iterator operator -- (int)
    {
        m_node=m_node->prev;
        return m_node->next;
    }

    list_iterator& operator ++ ()
    {
        m_node=m_node->next;
        return *this;
    }

    list_iterator operator ++ (int)
    {
        m_node=m_node->next;
        return m_node->prev;
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
        for(node<Type>* element=other.m_head;element!=NULL;push_back(element->value),element=element->next);
    }

    list(list&& other):m_head(other.m_head),m_tail(other.m_tail)
    {
       other.m_head=other.m_tail=NULL;
    }

    list& operator= (const list& other)
    {
        if(this!=&other){
            clear();
            for(node<Type>* element=other.m_head;element!=NULL;push_back(element->value),element=element->next);
        }
        return *this;
    }

    void push_back(const value_type& value)
    {
        if(empty())
            m_head=m_tail=new node<Type>(value,NULL,NULL);
        else{
            m_tail->next=new node<Type>(value,NULL,m_tail);
            m_tail=m_tail->next;
        }
    }

    void push_front(const value_type& value)
    {
        if(empty())
            m_head=m_tail=new node<Type>(value,NULL,NULL);
        else{
            m_head->prev=new node<Type>(value,m_head,NULL);
            m_head=m_head->prev;
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
        if(!empty()){
            if(m_head==m_tail){
                delete(m_head);
                m_head=m_tail=NULL;
            }
            else{
                m_head=m_head->next;
                delete(m_head->prev);
                m_head->prev=NULL;
            }
        }
    }

    void pop_back()
    {
        if(!empty()){
            if(m_head==m_tail){
                delete(m_head);
                m_head=m_tail=NULL;
            }
            else{
                m_tail=m_tail->prev;
                delete(m_tail->next);
                m_tail->next=NULL;
            }
        }
    }

    iterator insert(iterator pos, const Type& value)
    {
        if(pos.m_node==NULL||pos.m_node==m_head)
            push_front(value);
        else {
            node<Type> *insertElem = new node<Type>(value, pos.m_node, pos.m_node->prev);
            pos.m_node->prev->next = insertElem;
            pos.m_node->prev = insertElem;
        }
        return iterator(pos.m_node->prev);

    }

    iterator erase(iterator pos)
    {
        iterator ret=pos.m_node->next;
        if(pos.m_node==m_head)
            pop_front();
        else if(pos.m_node==m_tail) {
            pop_back();
            ret=m_tail;
        }
        else {
            pos.m_node->prev->next = pos.m_node->next;
            pos.m_node->next->prev = pos.m_node->prev;
        }
        return ret;
    }

    void clear()
    {
        node<Type>* past;
        for(node<Type>* element=m_head;element!=NULL;past=element,element=element->next,delete past);
        m_head=m_tail=NULL;
    }

    bool empty() const
    {
        return m_head==NULL;
    }

    size_t size() const
    {
        size_t size=0;
        for(node<Type>* element=m_head;element!=NULL;element=element->next,size++);
        return size;
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
    //your private functions
    node<Type>* m_head;
    node<Type>* m_tail;
};
#endif //VECTOR_LIST_H
