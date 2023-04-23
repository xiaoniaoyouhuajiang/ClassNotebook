#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <iostream>
using namespace std;
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
        //prefix
      list_iterator& operator ++ ()
      {
          m_node=m_node->next;
          return *this;
      }
    //postfix
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

    ~list(){
            clear();
        }

        list(const list& other) : m_head(nullptr), m_tail(nullptr){
            copy(const_cast<list&>(other));
        }

        list(list&& other) : list(){
            if(this!= &other){
                swap(other);
            }
        }

        list& operator= (const list& other){
            if(this!= &other){
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

        void push_back(const value_type& value){
                node<Type>* tmp = new node<Type>(value, nullptr, nullptr);
                if(empty()){
                    m_head=m_tail=tmp;
                }
                else{
                    m_tail->next=tmp;
                    tmp->prev = m_tail;
                    m_tail = tmp;
                }
            }

            void push_front(const value_type& value){
                 node<Type>* tmp =new node<Type>(value, nullptr, nullptr);
                 if(empty()){
                     m_head=m_tail=tmp;
                 }
                 else{
                     m_head->prev=tmp;
                     tmp->next = m_head;
                     m_head = tmp;
                 }
            }

            void pop_front(){
                if(!empty()){
                    if(size()!=1){
                        node<Type>* tmp = m_head->next;
                        tmp->prev = nullptr;
                        delete m_head;
                        m_head = tmp;
                    }
                    else{
                        delete m_head;
                        m_head = m_tail = nullptr;
                    }
                }
            }

            void pop_back(){
                if(!empty()){
                    if(size()!=1){
                        node<Type>* tmp = m_tail->prev;
                        tmp->next = nullptr;
                        delete m_tail;
                        m_tail = tmp;
                    }
                    else{
                        delete m_head;
                        m_head = m_tail = nullptr;
                    }
                }
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
                        pos.m_node->prev = pos.m_node->prev->next = tmp;
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
                        iterator newest(pos.m_node->next);
                        delete tmp;
                        return newest;
                    }
                }

        reference front(){
                return m_head->value;
            }

            const_reference front() const{
                return m_head->value;
            }

            reference back(){
                return m_tail->value;
            }

            const_reference back() const{
                return m_tail->value;
            }

            bool empty() const{
              return (m_head == nullptr);
            }

            size_t size() const{
              node<Type>* tmp = m_head;
              size_t i = 0;
              while(tmp){
                  i++;
                  tmp = tmp->next;
              }
              return i;
            }

  private:
        void copy(list & lst){
                node<Type>* tmp = lst.m_head;
                while(tmp){
                    push_back(tmp->value);
                    tmp=tmp->next;
                }
            }

        void swap(list & lst)
            {
                std::swap(m_head, lst.m_head);
                std::swap(m_tail, lst.m_tail);
            }

        void clear(){
               while(m_head){
                   m_tail = m_head->next;
                   delete m_head;
                   m_head = m_tail;
               }
            }
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };
}
