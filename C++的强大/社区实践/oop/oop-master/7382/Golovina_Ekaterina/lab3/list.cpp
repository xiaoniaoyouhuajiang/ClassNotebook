#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>

template <class Type>
struct node{

    Type value;
    node* next;
    node* prev;

    node(const Type& value, node<Type>* next, node<Type>* prev)
      : value(value), next(next), prev(prev){}
};

template <class Type>
class list;

template <class Type>
class list_iterator{
  public:
    typedef ptrdiff_t difference_type;
    typedef Type value_type;
    typedef Type* pointer;
    typedef Type& reference;
    typedef size_t size_type;
    typedef std::forward_iterator_tag iterator_category;

    list_iterator()
      : m_node(nullptr)
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
	list_iterator<Type> tmp(m_node);
	m_node = m_node->next;
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
class list{

  public:
    typedef Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef list_iterator<Type> iterator;

    list(): m_head(nullptr), m_tail(nullptr){
    }
    ~list()
    {
	erase_nodes(m_head);
    }
    list::iterator begin(){
      return iterator(m_head);
    }
    list::iterator end(){
      return iterator();
    }
    list(const list& other): m_head(nullptr), m_tail(nullptr)
    {
	node <Type> * tmp = other.m_head;
	while (tmp != nullptr){
		push_back(tmp->value);
		tmp=tmp->next;
	}
    }

    list(list&& other): m_head(nullptr), m_tail(nullptr)
    {
	std::swap(m_head,other.m_head);
	std::swap(m_tail,other.m_tail);
    }

    list& operator= (const list& other)
    {
	if (m_head != other.m_head){
		node <Type> * saved_head = m_head;
		node <Type> * saved_tail = m_tail;
		node <Type> * tmp = other.m_head;
		try{
			m_head = m_tail = nullptr;
			while (tmp != nullptr){
				push_back(tmp->value);
				tmp=tmp->next;
			}
		}
		catch(std::exception &e){
			if (saved_head != m_head){
				erase_nodes(m_head);
				m_head = saved_head;
			}
			if (saved_tail != m_tail) m_tail = saved_tail;
			throw;
		}
		erase_nodes(saved_head);
	  }
	return *this;
    }
    void push_back(const value_type& value)
    {
	node<Type> * tmp = new node<Type>(value,nullptr,m_tail);
	if (m_tail != nullptr) m_tail->next = tmp;
	m_tail = tmp;
	if (m_head == nullptr) m_head = tmp;
    }
    iterator insert(iterator pos, const Type& value)
    {
	node<Type> * tmp = new node<Type>(value,pos.m_node,nullptr);
	if (begin() == pos){
		if (m_head != nullptr){
			m_head->prev = tmp;
		}
		else m_tail = tmp;
		m_head = tmp;
	}
	else if (end() == pos){
		m_tail->next = tmp;
		tmp->prev = m_tail;
		tmp = m_tail;
	}
	else{
		pos.m_node->prev->next = tmp;
		tmp -> prev = pos.m_node->prev;
		pos.m_node->prev = tmp;
	}
	return iterator(tmp);
    }

    iterator erase(iterator pos)
    {
	node<Type> * tmp = pos.m_node;
	node<Type> * next = nullptr;
	if (tmp != nullptr) next = tmp->next;
	if (m_head != nullptr){
		if (begin() == pos){
			m_head = m_head->next;
			if (m_head != nullptr){
				m_head->prev = nullptr;
			}
			else m_tail = m_head;
		}
		else{
			pos.m_node->prev->next=pos.m_node->next;
			if (pos.m_node->next != nullptr){
				pos.m_node->next->prev = pos.m_node->prev;
			}
			else m_tail = pos.m_node->prev;
		}
		delete tmp;
	}
	return iterator(next);

    }
    void push_front(const value_type& value)
    {
	node<Type> * tmp = new node<Type>(value,m_head,nullptr);
	if (m_head != nullptr) m_head->prev = tmp;
	m_head = tmp;
	if (m_tail == nullptr) m_tail = tmp;
    }

    reference front()
    {
	if (m_head != nullptr) return m_head->value;
    }

    const_reference front() const
    {
	if (m_head != nullptr) return m_head->value;
    }

    reference back()
    {
	if (m_tail != nullptr) return m_tail->value;
    }

    const_reference back() const
    {
	if (m_tail != nullptr) return m_tail->value;
    }

    void pop_front()
    {
	node<Type> * tmp = m_head;
	if (tmp != nullptr){
		m_head = m_head->next;
		delete tmp;
		if (m_head != nullptr) m_head->prev = nullptr;
		else m_tail = nullptr;
	}
    }

    void pop_back()
    {
	node<Type> * tmp = m_tail;
	if (tmp != nullptr){
		m_tail=m_tail->prev;
		delete tmp;
		if (m_tail != nullptr) m_tail->next = nullptr;
		else m_head = nullptr;
	}
    }

    void clear()
    {
	if (!empty()){
		node<Type> * tmp = m_head;
		while (tmp->next != nullptr){
			tmp = tmp->next;
			delete tmp->prev;
		}
		delete tmp;
	}
	m_head = nullptr;
	m_tail = m_head;
    }

    bool empty() const
    {
	if (m_head == nullptr) return true;
	else return false;
    }

    size_t size() const
    {
	if (!empty()){
		node<Type> * tmp = m_head;
		size_t counter=0;
		while (tmp != nullptr){
			counter++;
			tmp = tmp->next;
		}
		return counter;
	}
	else return 0;

    }

  private:
	void erase_nodes(node<Type> * start){
		if (start != nullptr){
			node<Type> * tmp = start;
			while (tmp->next != nullptr){
				tmp = tmp->next;
				delete tmp->prev;
			}
			delete tmp;
		}
	}
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
};
