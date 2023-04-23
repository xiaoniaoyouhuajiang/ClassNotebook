
#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <utility>

template <class Type>
struct node
{
	Type value;
	node* next;
	node* prev;

	node():value(nullptr),next(nullptr),prev(nullptr){

	}
	node(const Type& value, node<Type>* next, node<Type>* prev)
		: value(value), next(next), prev(prev)
	{
	}
};

template <class Type>
class list; 

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

	list_iterator(node<Type>* p)
		: m_node(p)
	{
	}
private:
	friend class list<Type>;
	
	node<Type>* m_node;
};

template <class Type>
class my_list
{
public:
	typedef Type value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef list_iterator<Type> iterator;

	my_list()
		: m_head(nullptr), m_tail(nullptr)
	{
	}

	my_list(const my_list& other)
	{
		m_head = m_tail = nullptr;
		node<Type>* temp = other.m_head;
		while (temp != nullptr)
		{
			push_back(temp->value);
			temp = temp->next;
		}
	}
	
	my_list(my_list&& other) 
		:m_head(other.m_head), m_tail(other.m_tail){
		other.m_head = other.m_tail = nullptr;
	}

	my_list& operator= (const my_list& other)
	{
		if (this != &other)
		{
			while (m_head){
				m_tail = m_head->next;
				delete m_head;
				m_head = m_tail;
			}
			node<Type>* temp = other.m_head;
			while (temp != nullptr)
			{
				push_back(temp->value);
				temp = temp->next;
			}
		}
		return *this;
	}

	~my_list()
	{
		while (m_head){
			m_tail = m_head->next;
			delete m_head;
			m_head = m_tail;
		}
	}

	iterator begin()
	{
		return iterator(m_head);
	}

	iterator end()
	{
		return iterator(m_tail);
	}

	void push_back(const value_type& value)
	{
		node<Type> *temp = new node<Type>(value, nullptr, nullptr);
		if (m_head != nullptr){
			temp->prev = m_tail;
			m_tail->next = temp;
			m_tail = temp;
		}
		else m_head = m_tail = temp;
	}

	void push_front(const value_type& value)
	{
		node<Type> *temp = new node<Type>(value, nullptr, nullptr);
		if (m_head != nullptr){
			temp->next = m_head;
			m_head->prev = temp;
			m_head = temp;
		}
		else m_head = m_tail = temp;
	}
	void pop_front()
	{
		if (m_head == m_tail){
			node<Type>*temp = m_head;
			m_head = m_tail = nullptr;
			delete temp;
		}
		else{
			node<Type>*temp = m_head;
			m_head = m_head->next;
			m_head->prev = nullptr;
			delete temp;
		}
	}

	void pop_back()
	{
		if (m_head == m_tail){
			node<Type>*temp = m_tail;
			m_head = m_tail = nullptr;
			delete temp;
		}
		else{
			node<Type>*temp = m_tail;
			m_tail = m_tail->prev;
			m_tail->next = nullptr;
			delete temp;
		}
	}
	iterator insert(iterator pos, const Type& value)
	{
		if (pos.m_node == m_head){
			push_front(value);
			return iterator(m_head);
		}
		if (pos.m_node == nullptr){
			push_back(value);
			return iterator(m_tail);
		}
		else{
			node<Type> *temp = new node<Type>(value, nullptr, nullptr);
			temp->next = pos.m_node;
			temp->prev = pos.m_node->prev;
			pos.m_node->prev->next = temp;
			pos.m_node->prev = temp;
			pos.m_node = temp;
			return iterator(temp);
		}
	}

	iterator erase(iterator pos)
	{
		if (pos.m_node == m_head){
			pop_front();
			return iterator(m_head);
		}
		if (pos.m_node == m_tail){
			pop_back();
			return iterator(m_tail);
		}
		else{
			pos.m_node->next->prev = pos.m_node->prev;
			pos.m_node->prev->next = pos.m_node->next;
			iterator temp(pos.m_node->next);
			delete pos.m_node;
			return temp;
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

	void clear()
	{
		while (m_head){
			m_tail = m_head->next;
			delete m_head;
			m_head = m_tail;
		}   
	}

	bool empty() const
	{
		if (m_head == nullptr) return true;
		else return false;
	}

	size_t size() const
	{
		node<Type>* temp = m_head;
		size_t count = 0;
		while (temp){
			count++;
			temp = temp->next;
		}
		return count;
	}

private:
	node<Type>* m_head;
	node<Type>* m_tail;
};
