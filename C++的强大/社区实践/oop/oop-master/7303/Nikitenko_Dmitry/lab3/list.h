#ifndef LIST_H
#define LIST_H
#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <utility>
#include "sector.h"
#include "parall.h"
#include "ellipse.h"
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

    list_iterator& operator = (const list_iterator& other) {

        if (m_node != other.m_node) {
            m_node = other.m_node;
        }
        return *this;
    }

    bool operator == (const list_iterator& other) const {

        return m_node == other.m_node;
    }

    bool operator != (const list_iterator& other) const {

        return m_node != other.m_node;
    }

    reference operator * () {

        return m_node->value;
    }

    pointer operator -> () {

        return &(m_node->value);
    }

    list_iterator& operator ++ () {

        if (m_node)
            m_node = m_node->next;
        return *this;
    }

    list_iterator operator ++ (int) {

        list_iterator iterator = *this;
        ++(*this);
        return iterator;
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

    list::iterator begin() const
    {
      return iterator(m_head);
    }

    list::iterator end() const
    {
      return iterator();
    }

    list(const list& other)
    {
        m_head = new node <value_type>(other.m_head->value, nullptr, nullptr);
        node <value_type>* cur_prev = m_head;
        node <value_type>* cur = m_head->next;
        node <value_type>* other_cur = other.m_head->next;

        while (other_cur)
        {
            cur = new node <value_type>(other_cur->value, nullptr, cur_prev);
            cur_prev->next = cur;
            other_cur = other_cur->next;
            cur_prev = cur;
        }

        m_tail = cur;
    }

    list(list&& other)
    {
        m_head = other.m_head;
        m_tail = other.m_tail;
        other.m_head = other.m_tail = nullptr;
    }

    list& operator= (const list& other)
    {
        if (m_head == other.m_head)
        {

            return *this;
        }

        if (!other.m_head) {

            m_head = nullptr;
            m_tail = nullptr;

            return *this;
        }

        this->clear();

        m_head = new node <value_type>(other.m_head->value, nullptr, nullptr);
        node <value_type>* cur_prev = m_head;
        node <value_type>* cur = m_head->next;
        node <value_type>* other_cur = other.m_head;

        while (other_cur) {

            cur = new node <value_type>(other_cur->value, nullptr, cur_prev);
            cur_prev->next = cur;
            other_cur = other_cur->next;
            cur_prev = cur;
        }

        m_tail = cur;
        return *this;
    }

    void push_back(const value_type& value)
    {
        node <value_type>* elem = new node <value_type>(value, nullptr, m_tail);
        if (empty())
        {
            m_head = m_tail = elem;
            return;
        }
        m_tail->next = elem;
        m_tail = elem;
    }

    void push_front(const value_type& value)
    {
         node <value_type>* elem = new node <value_type>(value, m_head, nullptr);
         if (empty())
         {
            m_head = m_tail = elem;
            return;
        }
        m_head->prev = elem;
        m_head = elem;
    }


    iterator insert(iterator pos, const Type& value)
    {
        if (pos.m_node == m_head)
        {
            push_front(value);
            return iterator(m_head);
        }
        else if (!pos.m_node)
        {
            push_back(value);
            return iterator(m_tail);
        }
        node <value_type>* elem = new node <value_type>(value, pos.m_node, pos.m_node->prev);
        pos.m_node->prev->next = elem;
        pos.m_node->prev = elem;
        return iterator(elem);
    }

    iterator erase(iterator pos)
    {
        if (pos.m_node == m_head) {

            pop_front();
            return iterator(m_head);
        }
        else if (pos.m_node == m_tail) {

            pop_back();
            return iterator(m_tail);
        }

        pos.m_node->prev->next = pos.m_node->next;
        pos.m_node->next->prev = pos.m_node->prev;

        iterator next = pos.m_node->next;
        delete pos.m_node;
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
      if(m_head == m_tail){
            delete m_head;
            m_head = m_tail = nullptr;
        }
        else{
            m_head = m_head->next;
            delete m_head->prev;
            m_head->prev = nullptr;
        }
    }

    void pop_back()
    {
      if(m_head == m_tail){
            delete m_head;
            m_head = m_tail = nullptr;
        }
        else{
            m_tail = m_tail->prev;
            delete m_tail->next;
            m_tail->next = nullptr;
        }
    }

    void clear()
    {
      while(!empty())
            pop_back();
    }

    bool empty() const
    {
      return !m_head;
    }

     friend const list<Type> operator+(const list<Type>& left, const list<Type>& right)
     {
         list<Type> res;
         Sector* sector = new Sector();
         Parall* parall = new Parall();
         Ellipse* ellipse = new Ellipse();
         list<Shape*>::iterator cur = left.begin();
         for (size_t i = 0; i < left.size();++i)
         {
             if ((*cur)->shape() == "Sector")
             {
                 for (size_t j = 0;j < (*cur)->getCoords().size();++j)
                 {
                    sector->setCoord(j,sector->getCoords()[j] + (*cur)->getCoords()[j]);

                 }
             }
             if ((*cur)->shape() == "Parall")
             {
                 for (size_t j = 0;j < (*cur)->getCoords().size();++j)
                 {
                     parall->setCoord(j,parall->getCoords()[j]+(*cur)->getCoords()[j]);
                 }
             }
             if ((*cur)->shape() == "Ellipse")
             {
                 for (size_t j = 0;j < (*cur)->getCoords().size();++j)
                 {
                     ellipse->setCoord(j,ellipse->getCoords()[j]+(*cur)->getCoords()[j]);
                 }
             }
             cur++;
         }
         cur = right.begin();
         for (size_t i = 0; i < right.size();++i)
         {
             if ((*cur)->shape() == "Sector")
             {
                 for (size_t j = 0;j < (*cur)->getCoords().size();++j)
                 {
                    sector->setCoord(j,sector->getCoords()[j] + (*cur)->getCoords()[j]);
                 }
             }
             if ((*cur)->shape() == "Parall")
             {
                 for (size_t j = 0;j < (*cur)->getCoords().size();++j)
                 {
                     parall->setCoord(j,parall->getCoords()[j]+(*cur)->getCoords()[j]);
                 }
             }
             if ((*cur)->shape() == "Ellipse")
             {
                 for (size_t j = 0;j < (*cur)->getCoords().size();++j)
                 {
                     ellipse->setCoord(j,ellipse->getCoords()[j]+(*cur)->getCoords()[j]);
                 }
             }
             cur++;
         }
         res.push_back(sector);
         res.push_back(parall);
         res.push_back(ellipse);
         return res;

     }


    size_t size() const
    {
        size_t i = 0;
        node <value_type> * el = m_head;
            while (el)
            {
                el = el->next;
                i++;
            }
        return i;
    }

  private:
    //your private functions
    node<Type>* m_head;
    node<Type>* m_tail;
  };


}// namespace stepik
#endif // LIST_H
