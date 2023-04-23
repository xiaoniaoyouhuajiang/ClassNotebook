#include <iostream>

#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <memory>

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

    list_iterator& operator ++ ()
    {
      m_node = m_node->next;
      return *this;
    }

    list_iterator operator ++ (int)
    {
      list_iterator temp(*this);
      ++(*this);
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

    list()
      : m_head(nullptr), m_tail(nullptr)
    {
    }

    ~list()
    {
        clear();
    }

    list(const list& other)
    {
        for (node<Type>* ptr = other.m_head; ptr; ptr = ptr->next) {
            push_back(ptr->value);
        }
    }

    list(list&& other): m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size) {
      other.m_head = nullptr;
      other.m_tail = nullptr;
    }

    list& operator=(list&& other)
    {
        m_head = other.m_head;
        m_tail = other.m_tail;
        m_size = other.m_size;

        other.m_head = other.m_tail = nullptr;
        return *this;
    }

    list& operator=(const list& other)
    {
        if (this != &other) {
            clear();

            for (node<Type>* ptr = other.m_head; ptr; ptr = ptr->next) {
                push_back(ptr->value);
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
        if (empty()) {
            m_tail = m_head = new node<Type>(value, nullptr, nullptr);
            m_head->next = m_tail;
            m_tail->prev = m_head;
        }
        else {
            m_tail->next = new node<Type>(value, nullptr, m_tail);
            m_tail = m_tail->next;
        }

        m_size += 1;
    }

    void push_front(const value_type& value)
    {
        if (empty()) {
            m_tail = m_head = new node<Type>(value, nullptr, nullptr);
            m_head->next = m_tail;
            m_tail->prev = m_head;
        }
        else {
            m_head = new node<Type>(value, m_head, nullptr);
            m_head->next->prev = m_head;
        }

        m_size += 1;
    }

    iterator insert(iterator pos, const Type& value)
    {
        node<Type>* pos_node = pos.m_node;

        if (pos_node) {
            if (pos_node == m_head) {
                push_front(value);
                return iterator(m_head);
            }
            else {
                node<Type>* new_node = new node<Type>(value, pos_node, pos_node->prev);
                pos_node->prev->next = new_node;
                pos_node->prev = new_node;

                m_size += 1;
                return iterator(new_node);
            }
        }
        else {
            push_back(value);
            return iterator(m_tail);
        }
    }

    iterator erase(iterator pos)
    {
        node<Type>* pos_node = pos.m_node;

        if (pos_node == m_head) {
            pop_front();
            return iterator(m_head);
        }
        else if (pos_node == m_tail) {
            pop_back();
            return iterator(m_tail);
        } else {
            node<Type>* ret_node = pos_node->next;
            pos_node->prev->next = pos_node->next;
            pos_node->next->prev = pos_node->prev;

            delete pos_node;
            m_size -= 1;
            return iterator(ret_node);
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
        node<Type>* delete_node = m_head;
        m_head = m_head->next;

        delete delete_node;
        m_size -= 1;

        if (m_size == 0) {
            m_head = m_tail = nullptr;
        }
    }

    void pop_back()
    {
        node<Type>* delete_node = m_tail;
        m_tail = m_tail->prev;
        m_tail->next = nullptr;

        delete delete_node;
        m_size -= 1;

        if (m_size == 0) {
            m_head = m_tail = nullptr;
        }
    }

    void clear()
    {
        node<Type>* cur_node = m_head;
        node<Type>* next_node = nullptr;

        if (m_size != 1) {
            while (cur_node) {
                next_node = cur_node->next;
                delete cur_node;
                cur_node = next_node;
            }
        }
        else {
            delete m_head;
        }

        m_head = m_tail = nullptr;
        m_size = 0;
    }

    bool empty() const
    {
      return m_size == 0;
    }

    size_t size() const
    {
      return m_size;
    }

  private:
    //your private functions

    node<Type>* m_head = nullptr;
    node<Type>* m_tail = nullptr;
    size_t m_size = 0;
  };

}// namespace stepik

int main() {
  stepik::list<int> list;
  list.push_front(5);
  list.push_front(2);
  list.push_back(17);
  list.push_back(2342);

  // std::cout << *list.begin() << std::endl;

  auto it = list.begin();
  list.insert(it, 323);
  list.erase(++++++it);
  for (auto el : list) {
    std::cout << el << ' ';
  } std::cout << std::endl;

  // stepik::list<int> list_assign(list_copy);
  // list_assign = list;
  //
  // list_assign.pop_back();
  // list_assign.pop_back();
  // list_assign.pop_back();
  // list_assign.pop_back();
  //
  // list_assign.clear();
  // list_assign.push_back(23);
  // std::cout << list_assign.back() << std::endl;

  return 0;
}
