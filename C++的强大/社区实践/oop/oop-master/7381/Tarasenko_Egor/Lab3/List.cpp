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
        m_node = other.m_node;
        return *this;
      // implement this
    }

    bool operator == (const list_iterator& other) const
    {
      // implement this
        if(m_node == other.m_node) return true;
        else return false;
    }

    bool operator != (const list_iterator& other) const
    {
      // implement this
        if(m_node != other.m_node) return true;
        else return false;
    }

    reference operator * ()
    {
      // implement this
        return (m_node->value);
    }

    pointer operator -> ()
    {
      // implement this
        return &(m_node->value);
    }

    list_iterator& operator ++ ()
    {
      // implement this
        m_node = m_node->next;
        return *this;
    }

    list_iterator operator ++ (int)
    {
      // implement this
        list_iterator* next = new list_iterator(*this);
        m_node = m_node->next;
        return *next;
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

    list()
      : m_head(nullptr), m_tail(nullptr)
    {
    }

	~list()
    {
      // implement this
        clear();
    }

    list(const list& other) : m_head(nullptr), m_tail(nullptr)
    {
      // implement this
        node<Type>* tmp = other.m_head;
        while(tmp){
            push_back(tmp->value);
            tmp = tmp->next;
        }
    }

    list(list&& other) : m_head(nullptr), m_tail(nullptr)
    {
      // implement this
        std::swap(m_head, other.m_head);
        std::swap(m_tail, other.m_tail);
    }

    list& operator= (const list& other)
    {
      // implement this
        if (this != &other){
            clear();
            node<Type>* tmp = other.m_head;
            while(tmp){
                push_back(tmp->value);
                tmp = tmp->next;
            }
        }
        return *this;
    }
	
    void push_back(const value_type& value)
    {
      // implement this
        node<Type>* new_element = new node<Type>(value, nullptr, m_tail);
        if (!m_head) m_head = new_element;
        else m_tail->next = new_element;
        m_tail = new_element;
    }

    void push_front(const value_type& value)
    {
      // implement this
        node<Type>* new_element = new node<Type>(value, m_head, nullptr);
        if (!m_tail) m_tail = new_element;
        else m_head->prev = new_element;
        m_head = new_element;
    }

	iterator insert(iterator pos, const Type& value)
    {
      // implement this
        node<Type>* pos_node = pos.m_node;
        if (!pos_node) {
            push_back(value);
            return iterator(m_tail);
        }
        if (pos_node == m_head) {
            push_front(value);
            return begin();
        }
        node<Type>* new_node = new node<Type>(value, pos_node, pos_node->prev);
        pos_node->prev->next = new_node;
        pos_node->prev = new_node;
        return iterator(new_node);
    }

    iterator erase(iterator pos)
    {
      // implement this
        node<Type>* pos_node = pos.m_node;
        if (!pos_node)
            return pos;
        if (!(pos_node->prev)) {
            pop_front();
            return begin();
        }
        if (!(pos_node->next)) {
            pop_back();
            return end();
        }
        pos_node->prev->next = pos_node->next;
        pos_node->next->prev = pos_node->prev;
        iterator next_pos = iterator(pos_node->next);
        delete pos_node;
        return next_pos;
    }

	
    reference front()
    {
      // implement this
        return m_head->value;
    }

    const_reference front() const
    {
      // implement this
        return m_head->value;
    }

    reference back()
    {
      // implement this
        return m_tail->value;
    }

    const_reference back() const
    {
      // implement this
        return m_tail->value;
    }

    void pop_front()
    {
      // implement this
        if (m_head){
            node<Type>* new_head = m_head->next;
            if (m_head->next) new_head->prev = nullptr;
            else m_tail = new_head;
            delete m_head;
            m_head = new_head;
        }
        else return;
    }

    void pop_back()
    {
      // implement this
        if(m_tail){
            node<Type>* new_tail = m_tail->prev;
            if(m_tail->prev) m_tail->prev->next = nullptr;
            else m_head = new_tail;
            delete m_tail;
            m_tail = new_tail;
        }
        else return;
    }

    void clear()
    {
      // implement this
        m_tail = nullptr;
        delete[] m_head;
    }

    bool empty() const
    {
      // implement this
        if(m_head) return false;
        else return true;
    }

    size_t size() const
    {
      // implement this
        int s = 0;
        node<Type>* tmp = m_head;
        while(tmp){
            s++;
            tmp = tmp->next;
        }
        return s;
    }

  private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik