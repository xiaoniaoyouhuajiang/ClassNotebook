#include <iostream>
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
	if(m_node != nullptr)
      	m_node = m_node->next;
      	return *this;
    }

    list_iterator operator ++ (int)
    {
       	list_iterator tmp(*this);
       	++(*this);
       	return tmp;
    }

    list_iterator& operator -- ()
    {
	if(m_node != nullptr)
        m_node = m_node->prev;
        return *this;
    }

    list_iterator operator -- (int)
    {
        list_iterator tmp(*this);
        --(*this);
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

    ~list()
    {
    	clear();
    }

    list(const list& other) :  m_head(nullptr), m_tail(nullptr)
    {
    	node<Type>* el = other.m_head;
        while (el)
        {
        	push_back(el->value);
                el = el->next;
        }
    }

    list(list&& other) : list()
    {
        if(this != &other)
          swap(other);
    }

    list& operator= (const list& other)
    {
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

/*    void print()
    {
         for(auto elem = m_head; elem->next != nullptr; elem = elem->next)
             std::cout << elem->value << " ";
	 std::cout << m_tail->value;
         std::cout << std::endl;
    }*/

    void push_back(const value_type& value)
    {
        node<Type>* tmp = new node<Type>(value, nullptr, nullptr);
        if(empty())
        {
            m_head = tmp;
            m_tail = tmp;
        }
        else
        {
            m_tail->next = tmp;
            tmp->prev = m_tail;
            m_tail = tmp;
        }
    }

    void push_front(const value_type& value)
    {
        node<Type>* tmp = new node<Type>(value, nullptr, nullptr);
        if(empty())
        {
            m_head = tmp;
            m_tail = tmp;
        }
        else
        {
            m_head->prev = tmp;
            tmp->next = m_head;
            m_head = tmp;
        }
    }

    iterator insert(iterator pos, const Type& value)
    {
      if(pos.m_node == nullptr)
      {
          push_back(value);
          return iterator(m_tail);
      }
      else
      {
            if(pos.m_node->prev == nullptr)
            {
                push_front(value);
                return iterator(m_head);
            }
            else
            {
                    node<Type>* tmp = new node<Type>(value, pos.m_node, pos.m_node->prev);
                    pos.m_node->prev->next = tmp;
                    pos.m_node->prev = tmp;
                    return iterator(tmp);
            }
      }
    }

    iterator erase(iterator pos)
    {
            if(!pos.m_node)
            {
                      return nullptr;
            }
            else if(!pos.m_node->prev)
            {
                      pop_front();
                      return iterator(m_head);
            }
            else if(!pos.m_node->next)
            {
                      pop_back();
                      return iterator(m_tail);
            }
            else
            {
                node<Type>* tmp = pos.m_node;
                pos.m_node->next->prev = pos.m_node->prev;
                pos.m_node->prev->next = pos.m_node->next;
                iterator new_l(pos.m_node->next);
                delete tmp;
                return new_l;
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
	if(m_head == m_tail)
	{
		delete m_head;
		m_head = nullptr;
		m_tail = nullptr;
	}
	else
	{
		m_head = m_head->next;
		delete m_head->prev;
		m_head->prev = nullptr;
	}
    }

    void pop_back()
    {
	if(m_head == m_tail)
        {
                delete m_head;
                m_head = nullptr;
                m_tail = nullptr;
        }
	else
	{
        	m_tail = m_tail->prev;
        	delete m_tail->next;
        	m_tail->next = nullptr;
	}
    }

    void clear()
    {
	while(m_head)
	{
		pop_back();
	}
	m_head = nullptr;
	m_tail = nullptr;
    }

    bool empty() const
    {
        return m_head == nullptr;
    }

    size_t size() const
    {
	node<Type> *list_el = m_head;
	size_t i = 0;
	while(list_el)
	{
		i++;
		list_el = list_el->next;
	}
	return i;
    }

  private:
    //your private functions
    void swap(list& other)
    {
    	std::swap(m_head, other.m_head);
        std::swap(m_tail, other.m_tail);
    }

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik

int main(){
	stepik::list<int> my_list;
	my_list.push_back(100);
	my_list.push_back(110);
	my_list.push_front(90);
	my_list.push_front(80);
	std::cout << "list Size: " << std::endl;
	std::cout << my_list.size() << std::endl;
        my_list.print();
	std::cout << "Pop front element: " << std::endl;
	my_list.pop_front();
	my_list.print();
	std::cout << "Pop back element: " << std::endl;
	my_list.pop_back();
	my_list.print();
	std::cout << "Insert element:" << std::endl;
	stepik::list_iterator<int> pos = my_list.begin();
 	pos++;
	my_list.insert(pos, 57);
	my_list.print();
	std::cout << "Erase:" << std::endl;
	stepik::list_iterator<int> pos1 = my_list.begin();
	pos1++;
	my_list.erase(pos1);
	my_list.print();

	return 0;
}
