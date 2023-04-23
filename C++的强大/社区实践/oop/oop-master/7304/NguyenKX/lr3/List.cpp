#include "stdafx.h"
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
			this->m_node = other.m_node;
			return *this;
		}

		bool operator == (const list_iterator& other) const
		{
			return this->m_node == other.m_node;
		}

		bool operator != (const list_iterator& other) const
		{
			return this->m_node != other.m_node;
		}

		reference operator * ()
		{
			return this->m_node->value;
		}

		pointer operator -> ()
		{
			return &(this->m_node->value);
		}

		list_iterator& operator ++ ()
		{
			//++x;
			this->m_node = this->m_node->next;
			return *this;
		}

		list_iterator operator ++ (int)
		{
			// x++;
			list_iterator<Type> ret(*this);
			this->m_node = this->m_node->next;
			return ret;
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
			this->clear();
		}

		list(const list& other) : m_head(nullptr), m_tail(nullptr)
		{
			node<Type> *cur = other.m_head;
			while (cur != nullptr) {
				push_back(cur->value);
				cur = cur->next;
			}
		}

		list(list&& other) : m_head(other.m_head), m_tail(other.m_tail)
		{
			other.m_head = nullptr;
			other.m_tail = nullptr;
		}

		list& operator= (const list& other)
		{
			this->clear();
			node<Type> *cur = other.m_head;
			while (cur != nullptr) {
				this->push_back(cur->value);
				cur = cur->next;
			}
			return *this;
		}
		void push_back(const value_type& value)
		{
			if (m_tail == nullptr) {
				m_head = new node<value_type>(value, nullptr, nullptr);
				m_tail = m_head;
			}
			else {
				node<Type> *cur = new node<Type>(value, nullptr, m_tail);
				m_tail->next = cur;
				m_tail = cur;
			}
		}

		iterator insert(iterator pos, const Type& value)
		{
			if (pos == begin()) {
				this->push_front(value);
				return this->begin();
			}
			node<Type> *next = pos.m_node;
			node<Type> *prev = pos.m_node->prev;
			node<Type> *ins = new node<Type>(value, next, prev);
			if (prev != nullptr) prev->next = ins;
			if (next != nullptr) next->prev = ins;
			return iterator(ins);
		}

		iterator erase(iterator pos)
		{
			if (pos == begin()) {
				this->pop_front();
				return this->begin();
			}
			if (pos.m_node == m_tail) {
				this->pop_back();
				return iterator();
			}

			node<Type> *next = pos.m_node->next;
			node<Type> *prev = pos.m_node->prev;
			node<Type> *del = pos.m_node;
			if (next != nullptr) next->prev = prev;
			if (prev != nullptr) prev->next = next;
			delete del;
			return iterator(next);
		}

		void push_front(const value_type& value)
		{
			if (m_head == nullptr) {
				m_head = new node<value_type>(value, nullptr, nullptr);
				m_tail = m_head;
			}
			else {
				node<Type> *cur = new node<Type>(value, m_head, nullptr);
				m_head->prev = cur;
				m_head = cur;
			}
		}

		reference front()
		{
			return m_head->value;
		}

		const_reference front() const
		{
			return  m_head->value;
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
			node<Type> *h = m_head;
			m_head = m_head->next;
			if (m_head == nullptr) m_tail = nullptr;
			else m_head->prev = nullptr;
			delete h;
		}

		void pop_back()
		{
			node<Type> *t = m_tail;
			m_tail = m_tail->prev;
			if (m_tail == nullptr) m_head = nullptr;
			else m_tail->next = nullptr;
			delete t;
		}

		void clear()
		{
			while (m_head != nullptr) {
				pop_front();
			}
		}

		bool empty() const
		{
			return m_head == nullptr;
		}

		size_t size() const
		{
			node<Type> *cur = m_head;
			int count = m_head ? 1 : 0;
			while (cur != m_tail) {
				count++;
				cur = cur->next;
			}
			return count;
		}

		list::iterator begin()
		{
			return iterator(m_head);
		}

		list::iterator end()
		{
			return iterator();
		}

	private:
		//your private functions

		node<Type>* m_head;
		node<Type>* m_tail;
	};

}// namespace stepik


#include <iostream>
int main() {
	stepik::list<int> a;
	a.push_back(5);
	a.push_front(2);
	a.insert(a.begin(), 3);
	stepik::list_iterator<int> iter = a.begin();
	iter++;
	iter++;
	iter=a.erase(iter);
	
	std::cout << a.size()<<(iter== stepik::list_iterator<int>());
	getchar();
}