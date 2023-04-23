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
     return  m_node->value;
    }

    pointer operator -> ()
    {
     return &(m_node->value);
    }

    list_iterator& operator ++ ()
    {
      m_node=m_node->next;
      return *this;
    }

    list_iterator operator ++ (int)
    {
      list_iterator tmp(*this);
      ++(*this);
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

    list(const list& other):m_head(nullptr), m_tail(nullptr)
    {
      copy(const_cast<list&>(other));
    }

    list(list&& other):list()
    {
     if(this!=&other){
         swap(other);
     }
    }

    list& operator= (const list& other)
    {
        if(this!=&other){
            list tmp(other);
            tmp.swap(*this);
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
      if(m_tail){
          node<value_type> *tmp =new node<value_type>(value, nullptr, m_tail);
          m_tail->next=tmp;
          m_tail=tmp;
      }
      else{
          m_head=new node <value_type>(value, nullptr, nullptr);
          m_tail=m_head;
      }      
    }

    void push_front(const value_type& value)
    {
        if(m_head){
          node<value_type> *tmp=new node<value_type>(value, m_head, nullptr);
          m_head->prev=tmp;
          m_head=tmp;
        }
        else{
          m_head=new node <value_type>(value, nullptr, nullptr);
          m_tail=m_head;
        }
            
    }

     void pop_front()
    {
      node<value_type> *tmp=m_head;
      m_head=m_head->next;
      if(m_head){
          m_head->prev=nullptr;
      }
      else{
          m_head=nullptr;
          m_tail=nullptr;
      }
      delete tmp;
    }

    void pop_back()
    {   
        node<value_type> *tmp=m_tail;
        m_tail=m_tail->prev;
        if(m_tail){ 
            m_tail->next=nullptr;
        }
        else{
            m_head=nullptr;
            m_tail=nullptr;
        }
        delete tmp;            
    }
    iterator insert(iterator pos, const Type& value)
    {
       if(!pos.m_node){
            push_back(value);
            return iterator(m_tail);
        }
        else if(!pos.m_node->prev){
            push_front(value);
            return iterator(m_head);
        }
        else{
            node<Type>* tmp = new node<Type>(value, pos.m_node, pos.m_node->prev);
            pos.m_node->prev =pos.m_node->prev->next= tmp;
            return iterator(tmp);
        }
    }

    iterator erase(iterator pos)
    {
      if (!pos.m_node){
      return nullptr;
    }
    else if (!pos.m_node->prev){
      pop_front();
      return iterator(m_head);
    }
    else if (!pos.m_node->next){
      pop_back();
      return iterator(m_tail);
    }
    else{
            node<Type>* tmp = pos.m_node;
      pos.m_node->next->prev = pos.m_node->prev;
      pos.m_node->prev->next = pos.m_node->next;
      iterator n(pos.m_node->next);
      delete tmp;
      return n;
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
    void clear()
    {
      while(m_head){
          pop_back();
      }
      m_head=nullptr;
      m_tail=nullptr;
    }

    bool empty() const
    {
        if(m_head){
           return false;
        }
        else{
            return true;
        }
    }

    size_t size() const
    {
      size_t count=0;
      node<value_type> *tmp=m_head;
       while(tmp!=nullptr){
           count++;
           tmp=tmp->next;
       }
       return count;
    }
private:
    void swap(list &other){
        std::swap(m_head, other.m_head);
        std::swap(m_tail, other.m_tail);
    }
    void copy(list &other){
        node<value_type> *tmp=other.m_head;
        while(tmp){
            push_back(tmp->value);
            tmp=tmp->next;
        }
    }
    
    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik

