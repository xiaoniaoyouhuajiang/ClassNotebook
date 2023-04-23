#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <utility>
#include <iostream>

using namespace std;

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
			list_iterator temp(*this);
			m_node = m_node->next;
			return temp;
		}

	private:
		friend class list<Type>;

		list_iterator(node<Type>* p): m_node(p)
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

		list(const list& other) : m_head(nullptr), m_tail(nullptr)
		{
			// implement this
			node<Type> *p = other.m_head;
			while (p != nullptr) {
				push_back(p->value);
				p = p->next;
			}
			delete p;
		}

		list(list&& other) : m_head(other.m_head), m_tail(other.m_tail)
		{
			// implement this
			other.m_head = nullptr;
			other.m_tail = nullptr;
		}

		list& operator= (const list& other)
		{
			// implement this
			clear();
			node<Type> *p = other.m_head;
			while (p != nullptr) {
				push_back(p->value);
				p = p->next;
			}
			delete p;
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
			node<Type> *p = new node<Type>(value, nullptr, nullptr);
			if (m_tail == nullptr) {
				m_head = p;
				m_tail = m_head;
			}
			else {
				p->prev = m_tail;
				m_tail->next = p;
				m_tail = p;
			}
		}

		iterator insert(iterator pos, const Type& value)
		{
			// implement this
			if (pos.m_node == nullptr) {
				push_back(value);
				return iterator(m_tail);
			}
			else if (pos.m_node->prev == nullptr) {
				push_front(value);
				return iterator(m_head);
			}
			else {
				node<Type> *p = new node<Type>(value, pos.m_node, pos.m_node->prev);
				pos.m_node->prev->next = p;
				pos.m_node->prev = p;
				return iterator(p);
			}
		}

		iterator erase(iterator pos)
		{
			// implement this
			if (pos.m_node == nullptr)
				return nullptr;

			else if (pos.m_node->prev == nullptr) {
				pop_front();
				return iterator(m_head);
			}
			else if (pos.m_node->next == nullptr) {
				pop_back();
				return iterator(m_tail);
			}
			else {
				node<Type>* del = pos.m_node;
				pos.m_node->next->prev = pos.m_node->prev;
				pos.m_node->prev->next = pos.m_node->next;
				delete del;
				return iterator(pos.m_node->next);
			}
		}

		void push_front(const value_type& value)
		{
			// implement this
			node<Type> *p = new node<Type>(value, nullptr, nullptr);
			if (m_head == nullptr) {
				m_tail= p;
				m_head = m_tail;
			}
			else {
				p->next = m_head;
				m_head->prev = p;
				m_head = p;
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
			if (!empty()) {
				node<Type> *p = m_head;
				m_head = m_head->next;
				if (m_head == nullptr)
					m_tail=nullptr;
				else {
					m_head->prev = nullptr;
				}
				delete p;
			}
		}

		void pop_back()
		{
			// implement this
			if (!empty()) {
				node<Type> *p = m_tail;
				m_tail = m_tail->prev;
				if (m_tail == nullptr)
					m_head = nullptr;
				else {
					m_tail->next = nullptr;
				}
				delete p;
			}
		}

		void clear()
		{
			// implement this
			while (m_head != nullptr)
				pop_front();
		}

		bool empty() const
		{
			// implement this
			return m_head == nullptr;
		}

		size_t size() const
		{
			// implement this
			size_t count = 0;
			node<Type> *p = m_head;
			while (p != nullptr) {
				count++;
				p = p->next;
			}
			return count;
		}

		void print() {
			node<int> *p = m_head;
			while (p != nullptr) {
				cout << p->value << " ";
				p = p->next;
			}cout << endl;
		}

	private:
		//your private functions

		node<Type>* m_head;
		node<Type>* m_tail;
	};

}// namespace stepik

int main()
{
	stepik::list<int> a;
	for (int i = 0; i < 10; i++) {
		a.push_back(i + 1);
	}
	cout << "List: ";
	a.print();

	a.pop_back();
	cout << "Pop back: ";
	a.print();

	a.insert(a.end(), 3);
	cout << "Insert: ";
	a.print();

	stepik::list_iterator<int> iter = a.begin();
	iter++;
	iter = a.erase(iter);
	cout << "Erase: ";
	a.print();

	system("pause");
	return 0;
}
