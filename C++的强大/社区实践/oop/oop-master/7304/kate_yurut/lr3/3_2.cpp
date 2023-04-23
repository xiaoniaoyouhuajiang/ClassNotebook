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
      :  m_node(NULL)
    {}

    list_iterator(const list_iterator& other)
      :  m_node(other.m_node)
    {}

    list_iterator& operator = (const list_iterator& other)
    {
        // implement this
        m_node = other.m_node;
        return *this;
    }

    bool operator == (const list_iterator& other) const
    {
        // implement this
        return m_node == other.m_node;
    }

    bool operator != (const list_iterator& other) const
    {
        // implement this
        return m_node != other.m_node;
    }

    reference operator * ()
    {
        // implement this
        return m_node->value; 
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
        list_iterator buf(*this);
		++(*this);
        return buf;
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
        // implement this  
        clear();
    }

    list(const list& other)
        :  m_head(nullptr)
        ,  m_tail(nullptr)
    {
        // implement this
        try
		{
			copy(const_cast<node<Type>*>(other.m_head));
		}
		catch(...)
		{
			delete[] m_head;
			throw;
        }
    }

    list(list&& other)
        :  list()
    {
        // implement this
        if (this != &other)
            swap(other);
    }

    list& operator= (const list& other)
    {
        // implement this
        if(this != &other)
			list(other).swap(*this);
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
        // implement this
        if (empty())
		{
			node<Type> *buf = new node<Type>(value, nullptr, nullptr);
			m_head = buf;
			m_tail = buf;
		}
		else 
		{
			node<Type> *buf = new node<Type>(value, nullptr, m_tail);
			m_tail->next = buf;
			m_tail = buf;
        }
    }

    void push_front(const value_type& value)
    {
        // implement this
        if (empty())
	  	{
			node<Type> *buf = new node<Type>(value, nullptr, nullptr);
		  	m_head = buf;
		  	m_tail = buf;
	  	}
		else
		{
			node<Type> *buf = new node<Type>(value, m_head, nullptr);
			m_head->prev = buf;
			m_head = buf;
        }
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
        if (!empty())
		{
			if (size() == 1)
			{
				node<Type>* buf = m_head;
				m_head = NULL;
				m_tail = NULL;
			}
			else
			{
				node<Type>* buf = m_head->next;
				buf->prev = nullptr;
				delete m_head;
				m_head = buf;
			}
        }
    }

    void pop_back()
    {
        // implement this
        if (!empty())
		{
			if (size() == 1)
			{
				node<Type>* buf = m_head;
				m_head = NULL;
				m_tail = NULL;
			}
			else
			{
				node<Type>* buf = m_tail->prev;
				buf->next = nullptr;
				delete m_tail;
				m_tail = buf;
			}
        } 
    }

    iterator insert(iterator pos, const Type& value)
    {
        // implement this
        if (pos.m_node == NULL)
		{
				push_back(value);
				return iterator(m_tail);
		}
		else if (pos.m_node->prev == NULL)
		{
			push_front(value);
			return iterator(m_head);
		}
		else 
		{
			node<Type>* buf = new node<Type>(value, pos.m_node, pos.m_node->prev);
			pos.m_node->prev->next = buf;
            pos.m_node->prev = buf;
			return iterator(buf);
        }
    }

    iterator erase(iterator pos)
    {
        // implement this
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
			node<Type>* buf = pos.m_node;
			iterator new_pos(pos.m_node->next);
			delete buf;
			return new_pos;
        }
    }

    void clear()
    {
        // implement this    
        while (m_head)
		{
			m_tail = m_head->next;
			delete m_head;
			m_head = m_tail;
        }
    }

    bool empty() const
    {
        // implement this
        return m_head == NULL; 
    }

    size_t size() const
    {
        // implement this
        node<Type>* buf = m_head;
		size_t i = 0;
		do 
        {
			i++;
			buf = buf->next;
		} while(buf != NULL);
        return i;
    }

    void copy(node<Type> * other)
    {
	while(other)
	{
		push_back(other->value);
		other = other->next;
	}
    }
      
    void swap(list & lst)
	{
		std::swap(m_head, lst.m_head);
		std::swap(m_tail, lst.m_tail);
    }

  private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik
