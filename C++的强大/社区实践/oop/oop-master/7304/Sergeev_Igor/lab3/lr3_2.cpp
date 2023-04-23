#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <utility>
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
        if (this != &other){
            m_node = other.m_node;
        }
        return *this;
    }

    bool operator == (const list_iterator& other) const
    {
       if (m_node == other.m_node)
           return true;
       else return false;
    }

    bool operator != (const list_iterator& other) const
    {
      if (!(*this == other))
          return true;
      else return false;
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
      : m_head(nullptr), m_tail(nullptr), m_size(0)
    {
    }

    ~list()
    {
      clear();
    }

    list(const list& other)
    {
      if (other.m_head == nullptr){
          m_head = nullptr;
          m_tail = nullptr;
          m_size = 0;
      }
      else{
          m_size++;
          m_head = new node<Type>(other.m_head->value,nullptr,nullptr);
          m_tail = m_head;
          if (other.m_head->next == nullptr){
              return;
          }
          else{
              node<Type>* tmp = other.m_head->next;
              while (tmp != nullptr){
                  m_size++;
                  m_tail->next = new node<Type>(tmp->value,nullptr,m_tail);
                  m_tail = m_tail->next;
                  tmp = tmp->next;
              }
          }
      }
    }

    list(list&& other)
    {
      m_head = other.m_head;
      m_tail = other.m_tail;
      m_size = other.m_size;
      other.m_head = nullptr;
      other.m_tail = nullptr;
      other.m_size = 0;
    }

    list& operator= (const list& other)
    {
      clear();
      if (other.m_head == nullptr){
          m_head = nullptr;
          m_tail = nullptr;
          m_size = 0;
      }
      else{
          m_size++;
          m_head = new node<Type>(other.m_head->value,nullptr,nullptr);
          m_tail = m_head;
          node<Type>* tmp = other.m_head->next;
          if (other.m_head->next == nullptr){
              return *this;
          }
          else{
              node<Type>* tmp = other.m_head->next;
              while (tmp != nullptr){
                  m_size++;
                  m_tail->next = new node<Type>(tmp->value,nullptr,m_tail);
                  m_tail = m_tail->next;
                  tmp = tmp->next;
              }
          }
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
      m_size++;
      node<Type>* ptr = new node<Type>(value,nullptr,m_tail);
      if (m_head == nullptr){
          m_head = ptr;
      }
      m_tail = ptr;
      if (m_tail->prev != nullptr){
        m_tail->prev->next = ptr;
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

    void clear()
    {
      node<Type>* ptr;
      while (m_head != nullptr){
          ptr = m_head;
          m_head = m_head->next;
          if (m_head == nullptr){
              m_tail = nullptr;
          }
          else m_head->prev = nullptr;
          delete ptr;
      }
      m_size = 0;
    }

    bool empty() const
    {
      return m_head == nullptr;
    }

    size_t size() const
    {
      return m_size;
    }

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

    void pop_front()
    {
      if (m_size == 0)
          return;
      m_size--;
      node<Type>* ptr = m_head;
      m_head = m_head->next;
      if (m_head == nullptr)
          m_tail = nullptr;
      else m_head->prev = nullptr;
      delete ptr;
    }

    void pop_back()
    {
      if (m_size == 0)
          return;
      m_size--;
      node<Type>* ptr = m_tail;
      m_tail = m_tail->prev;
      if (m_tail == nullptr)
          m_head = nullptr;
      else m_tail->next = nullptr;
      delete ptr;
    }

    void push_front(const value_type& value)
    {
      m_size++;
      node<Type>* ptr = new node<Type>(value,m_head,nullptr);
      if (m_head == nullptr){
          m_tail = ptr;
      }
      m_head = ptr;
      if (m_head->next != nullptr){
          m_head->next->prev = ptr;
      }
    }

  private:
    //your private functions
    size_t m_size;
    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik

int main(){
    stepik::list<int> my = stepik::list<int>();
    my.push_back(2);
    my.push_back(4);
    cout << "PUSHING 2 AND 4\n";
    cout << "INSERTING 5 at pos 0\n";
    my.insert(my.begin(),5);
    cout << "FRONT AND BACK ELEMENTS " << my.front() <<  "   " << my.back() << endl;
    cout << "SIZE OF LIST " << my.size() << endl;
}
