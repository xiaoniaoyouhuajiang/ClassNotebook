#pragma once

#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <iostream>

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

		list_iterator& operator= (const list_iterator& other)
		{
			if (this != &other) {
				m_node = other.m_node;
			}
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
			list_iterator tmp = *this;
			++(*this);
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
			: m_head(nullptr), m_tail(nullptr), m_size(0)
		{
		}

		~list()
		{
			clear();
		}

		list::iterator begin()
		{
			return iterator(m_head);
		}

		list::iterator end()
		{
			return iterator();
		}

		list(const list& other)
			: list()
		{
			*this = other;
		}

		list(list&& other)
			: list()
		{
			*this = other;
		}

		list& operator= (const list& other)
		{
			if (this != &other) {
				clear();

				if (other.size()) {
					node <Type> * tmp = other.m_head;

					while (tmp) {
						push_back(tmp->value);
						tmp = tmp->next;
					}
				}
			}

			return *this;
		}

		void push_back(const value_type& value)
		{
			if (!empty()) {
				m_tail->next = new node<Type>(value, nullptr, m_tail);
				m_tail = m_tail->next;
			}
			else {
				m_tail = new node<Type>(value, nullptr, nullptr);
				m_head = m_tail;
			}

			m_size++;
		}

		void push_front(const value_type& value)
		{
			if (!empty()) {
				m_head->prev = new node<Type>(value, m_head, nullptr);
				m_head = m_head->prev;
			}
			else {
				m_head = new node <Type>(value, nullptr, nullptr);
				m_tail = m_head;
			}

			m_size++;
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
			if (!empty()) {
				if (m_head == m_tail) {
					clear();
				}
				else {
					m_head = m_head->next;
					delete m_head->prev;
					m_head->prev = nullptr;

					m_size--;
				}
			}
		}

		void pop_back()
		{
			if (!empty()) {
				if (m_head == m_tail) {
					clear();
				}
				else {
					m_tail = m_tail->prev;
					delete m_tail->next;
					m_tail->next = nullptr;

					m_size--;
				}
			}
		}

		iterator insert(iterator pos, const Type& value)
		{
			if (pos == begin()) {
				push_front(value);
				return begin();
			}
			if (pos == end()) {
				push_back(value);
				return end();
			}
			node <Type> * tmp = new node<Type>(value, pos.m_node, pos.m_node->prev);
			tmp->next->prev = tmp;
			tmp->prev->next = tmp;

			m_size++;

			return iterator(tmp);
		}

		iterator erase(iterator pos)
		{
			if (pos == begin()) {
				pop_front();
				return begin();
			}
			if (pos.m_node == m_tail
				|| pos == end()) {
				pop_back();
				return end();
			}
			node<Type> *tmp = pos.m_node;
			iterator result(tmp->next);

			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;

			delete tmp;
			m_size--;

			return result;
		}

		void clear()
		{
			while (m_head) {
				if (m_head->next) {
					m_head = m_head->next;
					delete m_head->prev;
				}
				else {
					delete m_head;
					m_head = m_tail = nullptr;
				}
			}

			m_size = 0;
		}

		bool empty() const
		{
			return (m_size == 0);
		}

		size_t size() const
		{
			return m_size;
		}

		void print()
		{
			std::cout << "list is: ";
			if (!empty()) {
				for (iterator it = begin(); it != end(); it++) {
					std::cout << *it << " ";
				}

				std::cout << "size is: " << size();
			}
			else {
				std::cout << "list is empty";
			}

			std::cout << std::endl;
		}

	private:
		//your private functions

		size_t m_size;

		node<Type>* m_head;
		node<Type>* m_tail;
	};

}// namespace stepik

