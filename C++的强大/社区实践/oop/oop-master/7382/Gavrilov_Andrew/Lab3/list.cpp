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
      if(*this != other)
         m_node = other.m_node;
      return *this;
    }

    bool operator == (const list_iterator& other) const
    {
      return this->m_node==other.m_node;
    }

    bool operator != (const list_iterator& other) const
    {
      return this->m_node!=other.m_node;
    }

    reference operator * ()
    {
      return m_node->value;
    }

    pointer operator -> ()
    {
      return &m_node->value;
    }

    list_iterator& operator ++ ()
    {
      if(m_node!=nullptr)
          m_node=m_node->next;
      return *this;
    }

    list_iterator operator ++ (int)
    {
       if(m_node!=nullptr)
           return list_iterator(m_node->next);
        return *this;
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
      auto pos=m_head;
      while(pos!=nullptr){
          delete pos;
          pos=pos->next;
      }
    }

    list(const list& other): m_head(nullptr), m_tail(nullptr)
    {
      auto pos=other.m_head;
      while(pos!=nullptr){
          push_back(pos->value);
          pos=pos->next;
      }
    }

    list(list&& other)
    : m_head(nullptr), m_tail(nullptr)
    {
      std::swap(m_head, other.m_head);
      std::swap(m_tail, other.m_tail);
    }

    list& operator= (const list& other)
    {
      clear();
      auto pos=other.m_head;
      while(pos!=nullptr){
          push_back(pos->value);
          pos=pos->next;
      }
    }

    list::iterator begin()
    {
      return iterator(m_head);
    }

    list::iterator end()
    {
      return iterator();
    }

    void clear()
    {
      auto pos=m_head;
      while(pos!=nullptr){
          delete pos;
          pos=pos->next;
      }
      m_tail=nullptr;
      m_head=nullptr;
    }
    void push_back(const value_type& value)
    {
      auto el=new node<value_type>(value,nullptr,nullptr);
        if(empty()){
            m_head=el;
            m_tail=el;
        }
        else{
            m_tail->next=el;
            el->prev=m_tail;
            m_tail=el;
        }
    }
    void push_front(const value_type& value)
    {
        auto el=new node<value_type>(value,nullptr,nullptr);
        if(empty()){
            m_head=el;
            m_tail=el;
        }
        else{
            m_head->prev=el;
            el->next=m_head;
            m_head=el;
        }
    }
      
    bool empty() const
    {
      if(m_head==nullptr)
          return true;
      return false;
    }

    iterator insert(iterator pos, const Type& value)
    {
        if(size()<2 || pos.m_node==m_head){
            push_front(value);
            return iterator(m_head);
        }
      auto cur=m_head;
      while(cur->next!=pos.m_node){
          cur=cur->next;
      }
        auto el=new node<value_type>(value, pos.m_node,cur);
        cur->next=el;
        pos.m_node->prev=el;
        return iterator(el);
    }
    
    size_t size() const
    {
      auto pos=m_head;
      size_t count=0;
      while(pos!=nullptr){
          count++;
          pos=pos->next;
      }
      return count;
    }

    iterator erase(iterator pos)
        {
            auto& deleted = pos.m_node;

            if (deleted == nullptr)
                return pos;

            if (deleted->next == nullptr)
            {
                pop_back();
                return nullptr;
            }

            if (deleted->prev == nullptr)
            {
                pop_front();
                return iterator(m_head);
            }
            deleted->prev->next = deleted->next;
            deleted->next->prev = deleted->prev;
            auto next = deleted->next;
            delete deleted;
            return iterator(next);
    }
    void pop_front()
    {
      if(m_head==m_tail){
          delete m_head;
          m_head=nullptr;
          m_tail=nullptr;
      }
      else{
          auto el=m_head;
          m_head=m_head->next;
          m_head->prev=nullptr;
          delete el;
      }
    }
    void pop_back()
    {
      if(m_head==m_tail){
          delete m_head;
          m_head=nullptr;
          m_tail=nullptr;
      }
      else{
          auto el=m_tail;
          m_tail=m_tail->prev;
          m_tail->next=nullptr;
          delete el;
      }
    }
    reference front()
    {
      return m_head->value;
    }

    reference back()
    {
      return m_tail->value;
    }

    const_reference front() const
    {
      return m_head->value;
    }

    const_reference back() const
    {
      return m_tail->value;
    }

  private:

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}