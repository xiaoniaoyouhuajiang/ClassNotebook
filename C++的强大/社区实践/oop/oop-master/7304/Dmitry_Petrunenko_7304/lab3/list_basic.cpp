#include "list_basic.h"

  template <class Type>
    node<Type>::node(const Type& value, node<Type>* next, node<Type>* prev)
      : value(value), next(next), prev(prev)
    {
    }


    template <class Type>
      list_iterator<Type>::list_iterator()
        : m_node(NULL)
      {
      }

      template <class Type>
      list_iterator<Type>::list_iterator(const list_iterator& other)
        : m_node(other.m_node)
      {
      }

        template <class Type>
       list_iterator<Type>& list_iterator<Type>::operator=(const list_iterator<Type>& other)
      {
        m_node = other.m_node;
        return *this;
      }
     template <class Type>
      bool list_iterator<Type>::operator == (const list_iterator<Type>& other) const
      {
        return m_node == other.m_node;
      }
    template <class Type>
      bool list_iterator<Type>::operator != (const list_iterator<Type>& other) const
      {
        return m_node != other.m_node;
      }

      template <class Type>
      typename list_iterator<Type>::reference list_iterator<Type>::operator * ()
      {
        return m_node->value;
      }
        template <class Type>
      typename list_iterator<Type>::pointer list_iterator<Type>::operator -> ()
          {
            return &(m_node->value);
          }

        //prefix
      template <class Type>
      list_iterator<Type>& list_iterator<Type>::operator ++ ()
      {
          m_node=m_node->next;
          return *this;
      }

    //postfix
      template <class Type>
      list_iterator<Type> list_iterator<Type>::operator ++ (int)
      {
          list_iterator tmp(*this);
          ++(*this);
          return tmp;
      }


      template <class Type>
        list_iterator<Type>::list_iterator(node<Type>* p)
        : m_node(p)
      {
      }



  template <class Type>
     List<Type>::List()
      : m_head(nullptr), m_tail(nullptr)
    {
    }

     template <class Type>
        List<Type>::~List(){
            clear();
        }

        template <class Type>
           List<Type>::List(const List<Type>& other) : m_head(nullptr), m_tail(nullptr){
            copy(const_cast<List&>(other));
        }

           template <class Type>
              List<Type>::List(List&& other) : List(){
            if(this!= &other){
                swap(other);
            }
        }
        template <class Type>
        List<Type>& List<Type>::operator= (const List<Type>& other){
            if(this!= &other){
                List tmp(other);
                tmp.swap(*this);
            }
            return *this;
        }
        template <class Type>
       typename List<Type>::iterator List<Type>::begin()
            {
              return iterator(m_head);
            }

            template <class Type>
            typename List<Type>::iterator List<Type>::end()
            {
              return iterator();
            }


        template <class Type>
        void List<Type>::push_back(const value_type& value){
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
        template <class Type>
            void  List<Type>::push_front(const value_type& value){
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
            template <class Type>
            void List<Type>::pop_front(){
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
            template <class Type>
            void List<Type>::pop_back(){
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
            template <class Type>
            typename List<Type>::iterator List<Type>::insert(List<Type>::iterator pos, const Type& value)
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
                template <class Type>
                typename List<Type>::iterator List<Type>::erase(iterator pos)
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
        template <class Type>
        typename List<Type>::reference List<Type>::front(){
                return m_head->value;
            }
            template <class Type>
           typename List<Type>::const_reference List<Type>::front() const{
                return m_head->value;
            }
                template <class Type>
           typename List<Type>:: reference List<Type>::back(){
                return m_tail->value;
            }
                template <class Type>
           typename List<Type>:: const_reference List<Type>::back() const{
                return m_tail->value;
            }
                template <class Type>
            bool List<Type>::empty() const{
              return (m_head == nullptr);
            }
                template <class Type>
            size_t List<Type>::size() const{
              node<Type>* tmp = m_head;
              size_t i = 0;
              while(tmp){
                  i++;
                  tmp = tmp->next;
              }
              return i;
            }
            template <class Type>
        void List<Type>::copy(List & lst){
                node<Type>* tmp = lst.m_head;
                while(tmp){
                    push_back(tmp->value);
                    tmp=tmp->next;
                }
            }
            template <class Type>
        void List<Type>::swap(List & lst)
            {
                std::swap(m_head, lst.m_head);
                std::swap(m_tail, lst.m_tail);
            }
            template <class Type>
        void List<Type>::clear(){
               while(m_head){
                   m_tail = m_head->next;
                   delete m_head;
                   m_head = m_tail;
               }
            }
