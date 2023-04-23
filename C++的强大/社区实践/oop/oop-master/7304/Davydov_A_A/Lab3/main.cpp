#include <iostream>

using namespace std;

#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
#include <vector>
#include <list>


namespace stepik
{
  //first part of lab 3
  template <typename Type>
  class vector
  {
  public:
    typedef Type* iterator;
    typedef const Type* const_iterator;

    typedef Type value_type;

    typedef value_type& reference;
    typedef const value_type& const_reference;

    typedef std::ptrdiff_t difference_type;

    //implementation of step 1
    explicit vector(size_t count = 0) : size_(count)
    {
        if(size_ == 0)
            pointer = nullptr;
        else
            pointer = new Type[count];
        m_first = pointer;
        m_last = pointer + count;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last) : size_(last - first)
    {
        if(size_ == 0)
            pointer = nullptr;
        else
            pointer = new Type[size_];
        for(InputIterator it = first ; it!= last; ++it)
        {
            pointer[it - first] = *it;
        }
        m_first = pointer;
        m_last = pointer + size_;
    }

    vector(std::initializer_list<Type> init) : size_(init.size())
    {
        if(size_ == 0)
            pointer = nullptr;
        else
        {
            pointer = new Type[size_];
            int i = 0;
            for(auto &el : init)
            {
                pointer[i] = el;
                ++i;
            }
        }
        m_first = pointer;
        m_last = pointer + size_;
    }

    //copy constructor
    vector(const vector& other) : size_(other.size_)
    {
        if(size_ == 0)
            pointer = nullptr;
        else
        {
            pointer = new Type[size_];
            for(int i = 0; i < size_; ++i)
                pointer[i] = other.pointer[i];
        }
        m_first = pointer;
        m_last = pointer + size_;
    }

    vector(vector&& other) : size_(other.size_), m_first(other.m_first), m_last(other.m_last), pointer(other.pointer)
    {
        other.pointer = nullptr;
        other.m_last = nullptr;
        other.m_first = nullptr;
    }

    ~vector()
    {
        delete[] pointer;
    }

    //implementaion of step 2
    //assignment operators
    vector& operator=(const vector& other)
    {
        if(this!= &other)
        {
            size_ = other.size_;
            delete[] pointer;
            if(size_ == 0)
                pointer = nullptr;
            else
            {
                pointer = new Type[size_];
                for(int i = 0; i < size_; ++i)
                    pointer[i] = other.pointer[i];
            }
        }
        m_first = pointer;
        m_last = pointer + size_;

        return *this;
    }

    vector& operator=(vector&& other)
    {
        if(this!= &other)
        {
            size_ = other.size_;
            delete[] pointer;
            pointer = other.pointer;
            m_first = other.m_first;
            m_last = other.m_last;
            other.m_last = nullptr;
            other.m_first = nullptr;
            other.pointer = nullptr;
        }

        return *this;
    }

        // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        delete[] pointer;
        size_ = last - first;
        pointer = new Type[size_];
        for(InputIterator it = first; it!= last; ++it)
            pointer[it - first] = *it;
        m_first = pointer;
        m_last = pointer + size_;
    }

    //implementation of 3 step
    // resize methods
    void resize(size_t count)
    {
         if(size_ == count)
             return;
         else if(size_ > count)
         {
             Type *buff = new Type[count];

             for(int i = 0; i < count; ++i)
                 buff[i] = pointer[i];

             size_ = count;
             delete[] pointer;
             pointer = buff;
         }
         else if(size_ < count)
         {
             Type *buff = new Type[count];

             for(int i = 0; i < size_; ++i)
                 buff[i] = pointer[i];
             size_ = count;
             delete[] pointer;
             pointer = buff;
         }
         m_first = pointer;
         m_last = pointer + size_;
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
         int dif = pos - m_first;
         if(pos == m_last)
             return m_last;
         Type * buff = new Type[size_ - 1];
         int i = 0;
         for(const_iterator it = m_first; it!= m_last; ++it)
             if(it == pos)
                 ;//pass
             else
             {
                buff[i] = *it;
                ++i;
             }

         delete[] pointer;
         --size_;
         pointer = buff;
         m_first = pointer;
         m_last = pointer + size_;
         return pointer + dif;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        int dif = first - m_first;
        Type * buff = new Type[size_ - (last - first)];
        int i = 0;
        for(const_iterator it = m_first; it!= m_last; ++it)
            if(it >= first && it < last)
                ;//pass
            else
            {
               buff[i] = *it;
               ++i;
            }

        delete[] pointer;
        size_ -= (last - first);
        pointer = buff;
        m_first = pointer;
        m_last = pointer + size_;
        return pointer + dif;
    }

    //implementation of step 4
    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
        int dif = pos - m_first;
        Type *buff = new Type[size_ + 1];

        for(iterator it = m_first; it!= pos; ++it)
            buff[it - m_first] = pointer[it - m_first];
        buff[pos - m_first] = value;

        for(const_iterator it = pos; it!= m_last; ++it)
            buff[it - m_first + 1] = pointer[it - m_first];

        size_ += 1;
        delete[] pointer;
        pointer = buff;
        m_first = pointer;
        m_last = pointer + size_;
        return pointer + dif;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        int dif = pos - m_first;
        Type *buff = new Type[size_ + (last - first)];

        for(iterator it = m_first; it!= pos; ++it)
            buff[it - m_first] = pointer[it - m_first];

        const_iterator it = pos;
        for(InputIterator it1 = first; it1!= last; ++it, ++it1)
            buff[it - m_first] = *it1;

        //use it after work of cycle above
        for(const_iterator it1 = pos; it1!= m_last; ++it, ++it1)
            buff[it - m_first] = pointer[it1 - m_first];

        size_ += (last - first);
        delete[] pointer;
        pointer = buff;
        m_first = pointer;
        m_last = pointer + size_;
        return pointer + dif;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
          resize(size_ + 1);
          pointer[size_ - 1] = value;
    }



    //at methods
    reference at(size_t pos)
    {
      return checkIndexAndGet(pos);
    }

    const_reference at(size_t pos) const
    {
      return checkIndexAndGet(pos);
    }

    //[] operators
    reference operator[](size_t pos)
    {
      return m_first[pos];
    }

    const_reference operator[](size_t pos) const
    {
      return m_first[pos];
    }

    //*begin methods
    iterator begin()
    {
      return m_first;
    }

    const_iterator begin() const
    {
      return m_first;
    }

    //*end methods
    iterator end()
    {
      return m_last;
    }

    const_iterator end() const
    {
      return m_last;
    }

    //size method
    size_t size() const
    {
      return m_last - m_first;
    }

    //empty method
    bool empty() const
    {
      return m_first == m_last;
    }

  private:
    reference checkIndexAndGet(size_t pos) const
    {
      if (pos >= size())
      {
        throw std::out_of_range("out of range");
      }

      return m_first[pos];
    }

    //your private functions

  private:
    iterator m_first;
    iterator m_last;
    size_t size_;
    Type *pointer;
  };

  //second part of lab 3
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

     //implemenation of step 3
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
       {}

       list_iterator(const list_iterator& other)
         : m_node(other.m_node)
       {}

       list_iterator& operator = (const list_iterator& other)
       {
           if(this!= &other)
               m_node = other.m_node;

           return *this;
       }

       bool operator == (const list_iterator& other) const
       {
            if(m_node == other.m_node)
                return true;
            else
                return false;
       }

       bool operator != (const list_iterator& other) const
       {
            if(!(*this == other))
                return true;
            else
                return false;
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
     {}

     //implementation of step 2
     ~list()
     {
        node<Type> *cur = m_tail;
        while(m_tail!= nullptr)
        {
            m_tail = m_tail->prev;
            delete cur;
            cur = m_tail;
        }
        m_head = nullptr;
     }

     //copy constructor
     list(const list& other)
     {
          if(other.m_head == nullptr)
              m_head = m_tail = nullptr;
          else
          {
              m_head = new node<Type>(other.m_head->value, nullptr, nullptr);
              m_tail = m_head;
              if(other.m_head->next == nullptr)
                  return;
              else
              {
                  node<Type> *cur = other.m_head->next;
                  while(cur!= nullptr)
                  {
                      m_tail->next = new node<Type>(cur->value, nullptr, m_tail);
                      m_tail = m_tail->next;
                      cur = cur->next;
                  }
              }
          }
     }

     list(list&& other) : m_head(other.m_head), m_tail(other.m_tail)
     {
          other.m_head = nullptr;
          other.m_tail = nullptr;
     }

     list& operator= (const list& other)
     {
        if(this!= &other)
        {
            clear();
            if(other.m_head == nullptr)
                m_head = m_tail = nullptr;
            else
            {
                m_head = new node<Type>(other.m_head->value, nullptr, nullptr);
                m_tail = m_head;
                if(other.m_head->next == nullptr)
                    ; //pass
                else
                {
                    node<Type> *cur = other.m_head->next;
                    while(cur!= nullptr)
                    {
                        m_tail->next = new node<Type>(cur->value, nullptr, m_tail);
                        m_tail = m_tail->next;
                        cur = cur->next;
                    }
                }
            }
        }

        return *this;
     }


     //implementation of step 1
     void push_back(const value_type& value)
     {
        if(m_head == nullptr)
        {
            m_head = new node<Type>(value, nullptr, nullptr);
            m_head->prev = nullptr;
            m_head->next = nullptr;
            m_tail = m_head;
        }
        else if(m_tail == m_head)
        {
            m_tail = new node<Type>(value, nullptr, m_head);
            m_head->next = m_tail;
            m_tail->prev = m_head;
        }
        else
        {
            m_tail->next = new node<Type>(value, nullptr, m_tail);
            m_tail->next->prev = m_tail;
            m_tail = m_tail->next;
        }
     }

     void push_front(const value_type& value)
     {
        if(m_head == nullptr)
        {
            m_head = new node<Type>(value, nullptr, nullptr);
            m_head->prev = nullptr;
            m_head->next = nullptr;
            m_tail = m_head;
        }
        else
        {
            node<Type> *old_head = m_head;
            m_head = new node<Type>(value, old_head, nullptr);
            m_head->next = old_head;
            old_head->prev = m_head;
            m_head->prev = nullptr;
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
         m_tail->value;
     }

     void pop_front()
     {
        if(m_head == nullptr)
            return;
        else if(m_tail == m_head)
        {
            delete m_head;
            m_head = nullptr;
            m_tail = nullptr;
        }
        else
        {
            node<Type> *next_head = m_head->next;
            delete m_head;
            m_head = next_head;
            m_head->prev = nullptr;
        }
     }

     void pop_back()
     {
         if(m_head == nullptr)
             return;
         else if(m_tail == m_head)
         {
             delete m_head;
             m_head = nullptr;
             m_tail = nullptr;
         }
         else
         {
            node<Type> *last = m_tail;
            m_tail = m_tail->prev;
            delete last;
            m_tail->next = nullptr;
         }
     }

     void clear()
     {
         if(m_head == nullptr)
             return;
         else
         {
             node<Type> *old_tail = m_tail;

             while(m_tail!= nullptr)
             {
                m_tail = m_tail->prev;
                delete old_tail;
                old_tail = m_tail;
             }
             m_head = nullptr;
         }
     }

     bool empty() const
     {
        if(m_head == nullptr && m_tail == nullptr)
            return true;
        else
            return false;
     }

     size_t size() const
     {
         int size_ = 0;
         node<Type> *cur = m_tail;

         while(cur!= nullptr)
         {
             cur = cur->prev;
             ++size_;
         }
         return size_;
     }

     list::iterator begin()
     {
        return iterator(m_head);
     }

     list::iterator end()
     {
        return iterator();
     }

     //implementation of step 4
     iterator insert(iterator pos, const Type& value)
     {
        if(pos.m_node == m_head)
        {
            push_front(value);
            pos.m_node = pos.m_node->prev;
            return pos;
        }
        else if(pos.m_node == nullptr)
        {
            push_back(value);
            pos.m_node = m_tail;
            return pos;
        }
        else
        {
            node<Type> *new_node = new node<Type>(value, pos.m_node, pos.m_node->prev);
            pos.m_node->prev->next = new_node;
            pos.m_node->prev = new_node;
            pos.m_node = pos.m_node->prev;
            return pos;
        }
     }

     iterator erase(iterator pos)
     {
        if(pos.m_node == m_head)
        {
            pop_front();
            pos.m_node = m_head;
            return pos;
        }
        else if(pos.m_node == nullptr)
        {
            return pos;
        }
        else if(pos.m_node->next == nullptr)
        {
            pop_back();
            pos.m_node = m_tail;
            return pos;
        }
        else
        {
            pos.m_node->prev->next = pos.m_node->next;
            pos.m_node->next->prev = pos.m_node->prev;
            delete pos.m_node;
            pos.m_node = pos.m_node->next;
            return pos;
        }
     }

   private:
     //your private functions
     node<Type>* m_head;
     node<Type>* m_tail;

   };


}// namespace stepik






int main()
{
    stepik::list<int> list;

    for(int i = 0; i < 10; ++i)
        list.push_back(i);
    list.erase(list.end());

    for(int i = 0; i < 9; ++i)
    {
        cout << list.front() << " ";
        list.pop_front();
    }

    return 0;
}
