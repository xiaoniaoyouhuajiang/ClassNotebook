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
        m_node = other.m_node;
        return *this;
      // implement this
    }

    bool operator == (const list_iterator& other) const
    {
        return m_node == other.m_node;
      // implement this
    }

    bool operator != (const list_iterator& other) const
    {
        return m_node != other.m_node;
      // implement this
    }

    reference operator * ()
    {
        return m_node->value;
      // implement this
    }

    pointer operator -> ()
    {
        return &(m_node->value);
      // implement this
    }

    list_iterator& operator ++ ()
    {
        m_node = m_node->next;
        return *this;
      // implement this
    }

    list_iterator operator ++ (int)
    {
        list_iterator temp(*this);
        ++(*this);
        return *this;
      // implement this
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
      // use previous step implementation
    }

	list(const list& other) : m_head(nullptr), m_tail(nullptr)
    {
        auto elem = other.m_head;
			while (elem) {
				push_back(elem->value);
				elem = elem->next;
			}
      // implement this
    }

    list(list&& other) : m_head(nullptr), m_tail(nullptr)
    {
        swap(other);
      // implement this
    }
     
    void swap(list& other) {
        std::swap(m_head, other.m_head);
        std::swap(m_tail, other.m_tail);
    }
    
    list& operator= (const list& other)
    {
        if(this != &other){
            clear();
            auto cur = other.m_head;
            while(cur){
                push_back(cur->value);
                cur = cur->next;
            }
        }
        return *this;
      // implement this
    }
	
    list::iterator begin()
    {
      return iterator(m_head);
    }

    list::iterator end()
    {
      return iterator();
    }

    void pop_front()
    {
        if (!empty()) {
            if (size() == 1) {
                node<Type >* elem = m_head;
                m_head = NULL;
                m_tail = NULL;
            }
            else {
                node<Type >* elem = m_head;
                elem = m_head->next;
                elem->prev = nullptr;
                delete m_head;
                m_head = elem;
            }
        }
        // implement this
    }

    void pop_back()
    {
        if (!empty()) {
            if (size() == 1) {
                node<Type >* elem = m_head;
                m_head = NULL;
                m_tail = NULL;
            }
            else {
                node<Type >* elem = m_tail;
                elem = m_tail->prev;
                elem->next = nullptr;
                delete m_tail;
                m_tail = elem;
            }
        } 
      // implement this
    }
      
    void push_back(const value_type& value)
    {
        if (empty()) {
            node<Type>* elem = new node<Type>(value, nullptr, nullptr);
            m_head = elem;
            m_tail = elem;
        }
        else {
            node<Type>* elem = new node<Type>(value, nullptr, m_tail);
            m_tail->next = elem;
            m_tail = elem;
        }
      // use previous step implementation
    }
      
    void push_front(const value_type& value)
    {
        if (empty()) {
            node<Type>* elem = new node<Type>(value, nullptr, nullptr);
            m_head = elem;
            m_tail = elem;
        }
        else {
            node<Type>* elem = new node<Type>(value, m_head, nullptr);
            m_head->prev = elem;
            m_head = elem;
        }
      // implement this
    }

    iterator insert(iterator pos, const Type& value)
    {
        if (pos.m_node == NULL)
        {
            push_back(value);
            return iterator(m_tail);
        }// implement this
        else if (pos.m_node->prev == NULL) {
            push_front(value);
            return iterator(m_head);
        }
        else {
            node<Type>* temp = new node<Type>(value, pos.m_node, pos.m_node->prev);
			pos.m_node->prev->next = temp;
            pos.m_node->prev = temp;
			return iterator(temp);
        }
      // implement this
    }

    iterator erase(iterator pos)
    {
        if (pos.m_node == NULL)
		{
			return NULL;
		}
		else if (pos.m_node->prev == NULL)
		{
			pop_front();
			return iterator(m_head);
		}
		else if (pos.m_node->next == NULL)
		{
			pop_back();
			return iterator(m_tail);
		}
		else
		{
			pos.m_node->next->prev = pos.m_node->prev;
			pos.m_node->prev->next = pos.m_node->next;
			node<Type>* temp = pos.m_node;
			iterator new_pos(pos.m_node->next);
			delete temp;
			return new_pos;
		}
    }

    reference front()
    {
        return m_head->value;
      // use previous step implementation
    }

    reference back()
    {
        return m_tail->value;
      // use previous step implementation
    }
      
      void clear()
    {
        while(m_head) {
            m_tail = m_head->next;
            delete m_head;
            m_head = m_tail;
        }
      // implement this     
    }

    bool empty() const
    {
        return m_head == NULL;
      // implement this
    }
      
      size_t size() const
    {
        node<Type>* elem = m_head;
        size_t i = 0;
        while (elem != NULL) {
            i++;
            elem = elem->next;
        }
        return i;
      // implement this
    }

  private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik