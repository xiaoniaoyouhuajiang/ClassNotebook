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

    list_iterator& operator = (const list_iterator& other) {
        m_node = other.m_node;
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
        return &m_node->value;
    }

    list_iterator& operator ++ () {
        m_node = m_node->next;
        return *this;
    }

    list_iterator operator ++ (int) {
        auto temp = m_node;
        m_node = m_node->next;
        return temp;
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

    list() : m_head(nullptr), m_tail(nullptr) {}
      
    ~list() {
        this->clear();    
    }

    list(const list& other) : m_head(nullptr), m_tail(nullptr) { 
        for (auto iter = other.m_head; iter != nullptr; iter = iter->next) {
            this->push_back(iter->value);    
        }
    }

    list(list&& other) {
        m_head = other.m_head;
        m_tail = other.m_tail;
        
        other.m_head = other.m_tail = nullptr;
    }

    list& operator= (const list& other) {
        this->clear();
        
        for (auto iter = other.m_head; iter != nullptr; iter = iter->next) {
            this->push_back(iter->value);    
        }
    }
      
    iterator insert(iterator pos, const Type &value) {
        if (!pos.m_node) {
            this->push_back(value);
            return iterator(m_tail);
        }
        
        if (pos == this->begin()) {
            push_front(value);
            return this->begin();
        }
        
        auto temp = new node<Type>(value, pos.m_node, pos.m_node->prev);
        pos.m_node->prev->next = temp;
        pos.m_node->prev = temp;
        
        return temp;
    }
      
    iterator erase(iterator pos) {
        if(!pos.m_node) {
            return end();
        }
        if(pos == begin()) {
            pop_front();
            return iterator(m_head);
        }
        if(pos == iterator(m_tail)) {
            pop_back();
            return end();
        }

        node<Type>* to_return = pos.m_node->next;

        pos.m_node->next->prev = pos.m_node->prev;
        pos.m_node->prev->next = pos.m_node->next;

        delete pos.m_node;
        return to_return;
    }

    void push_back(const value_type& value) {
        if (this->empty()) {
            m_head = m_tail = new node<Type>(value, nullptr, nullptr);
        }
        else {
            m_tail->next = new node<Type>(value, nullptr, m_tail);
            m_tail = m_tail->next;
        }
    }

    void push_front(const value_type& value) {
      if (this->empty()) {
            m_head = m_tail = new node<Type>(value, nullptr, nullptr);
        }
        else {
            m_head->prev = new node<Type>(value, m_head, nullptr);
            m_head = m_head->prev;
        }
    }

    reference front() {
      return m_head->value;
    }

    const_reference front() const {
      return m_head->value;
    }

    reference back() {
      return m_tail->value;
    }

    const_reference back() const {
      return m_tail->value;
    }

    void pop_front() {
        if (m_head == nullptr)
            return;
        
        auto to_remove = m_head;
        
        if (this->size() == 1) {
            m_head = m_tail = nullptr;    
        }
        else {
            m_head = m_head->next;;
            m_head->prev = nullptr;
        }
        
        delete to_remove;
    }

    void pop_back() {
        if (m_head == nullptr)
            return;
        
        auto to_remove = m_tail;
        
        if (this->size() == 1) {
            m_head = m_tail = nullptr;    
        }
        else {
            m_tail = m_tail->prev;
            m_tail->next = nullptr;
        }
        
        delete to_remove;
    }

    void clear() {
        while (!this->empty())
            this->pop_back();
    }

    bool empty() const {
        return m_head == nullptr;
    }

    size_t size() const {
        size_t size = 0;
        
        for (auto iter = m_head; iter != nullptr; iter = iter->next) {
            size++;    
        }
        
        return size;
    }
      
    iterator begin() {
        return iterator(m_head);    
    }
      
    iterator end() {
        return iterator(nullptr);    
    }

  private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik
