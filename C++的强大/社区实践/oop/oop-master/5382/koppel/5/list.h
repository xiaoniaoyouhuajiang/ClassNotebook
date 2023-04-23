#pragma once
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

		node(const Type& value, node<Type>* next, node<Type>* prev)
			: value(value), next(next), prev(prev){}
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
		{}

		list_iterator(const list_iterator& other)
			: m_node(other.m_node)
		{}

		list_iterator& operator = (const list_iterator& other)
		{
			// use previous step implementation
			m_node = other.m_node;
		}

		bool operator == (const list_iterator& other) const
		{
			// use previous step implementation
			return m_node == other.m_node;
		}

		bool operator != (const list_iterator& other) const
		{
			// use previous step implementation
			return m_node != other.m_node;
		}

		reference operator * ()
		{
			// use previous step implementation
			return m_node->value;
		}

		pointer operator -> ()
		{
			// use previous step implementation
			return &(m_node->value);
		}

		list_iterator& operator ++ ()
		{
			// use previous step implementation
			m_node = m_node->next;
			return *this;
		}

		list_iterator operator ++ (int)
		{
			// use previous step implementation
			list_iterator temp(*this);
			++(*this);
			return temp;
		}

	private:
		friend class list<Type>;

		list_iterator(node<Type>* p)
			: m_node(p)
		{}

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
			// use previous step implementation
			while (m_head != nullptr) pop_front();
		}

		iterator begin()
		{
			return iterator(m_head);
		}

		iterator end()
		{
			return iterator();
		}

		void push_back(const value_type& value)
		{
			// use previous step implementation
			if (empty()) {
				add_first(value);
			}
			else {
				node<value_type> *tmp = new node<value_type>(value, nullptr, this->m_tail);
				m_tail->next = tmp;
				m_tail = tmp;
			}
		}

		iterator insert(iterator pos, const Type& value)
		{
			// implement this
			if (pos.m_node == NULL) {
				push_back(value);
				return iterator(m_tail);
			}
			else if (pos.m_node->prev == NULL) {
				push_front(value);
				return begin();
			}
			else {
				node<value_type> *tmp = new node<value_type>(value, pos.m_node, pos.m_node->prev);
				pos.m_node->prev->next = tmp;
				pos.m_node->prev = tmp;
				return iterator(tmp);
			}
		}

		iterator erase(iterator pos)
		{
			// implement this
			if (pos.m_node->prev == NULL) {
				pop_front();
				return begin();
			}
			else if (pos.m_node->next == NULL) {
				pop_back();
				return iterator(m_tail);
			}
			else {
				pos.m_node->next->prev = pos.m_node->prev;
				pos.m_node->prev->next = pos.m_node->next;
				node<value_type>* tmp = pos.m_node;
				iterator i(pos.m_node->next);
				delete tmp;
				return i;
			}
		}

		reference front()
		{
			// use previous step implementation
			return m_head->value;
		}

		reference back()
		{
			// use previous step implementation
			return m_tail->value;
		}

	private:
		//your private functions
		void push_front(const value_type& value)//âñòàâëÿåò ýëåìåíòû â íà÷àëî ñïèñêà
		{
			// implement this
			if (empty()) {
				add_first(value);
			}
			else {
				node<value_type> *tmp = new node<value_type>(value, this->m_head, nullptr);
				m_head->prev = tmp;
				m_head = tmp;
			}
		}

		void pop_front()//óäàëÿåò ïåðâûé ýëåìåíò 
		{
			// implement this
			if (size() == 1) {
				delete_last();
			}
			else if (!empty()) {
				node<value_type>* new_head = m_head->next;
				new_head->prev = nullptr;
				delete m_head;
				m_head = new_head;
			}
		}

		void pop_back()//Óäàëÿåò ïîñëåäíèé ýëåìåíò 
		{
			// implement this
			if (size() == 1) {
				delete_last();
			}
			else if (!empty()) {
				node<value_type>* new_tail = m_tail->prev;
				new_tail->next = nullptr;
				delete m_tail;
				m_tail = new_tail;
			}
		}
		size_t size() const//Âîçâðàùàåò êîëè÷åñòâî ýëåìåíòîâ â êîíòåéíåðå 
		{
			// implement this
			size_t quantity = 0;
			node<value_type>* tmp = m_head;
			while (tmp != NULL) {
				quantity++;
				tmp = tmp->next;
			}
			return quantity;
		}


		void add_first(const value_type &value) {
			node<value_type> *tmp = new node<value_type>(value, nullptr, nullptr);
			m_tail = tmp;
			m_head = tmp;
		}

		void delete_last() {
			node<value_type> *tmp = m_head;
			m_head = NULL;
			m_tail = NULL;
			delete tmp;
		}

		bool empty() const {
			return m_head == 0;
		}

		node<Type>* m_head;
		node<Type>* m_tail;
	};