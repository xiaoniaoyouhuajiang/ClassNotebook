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
	class list
	{
	public:
		typedef Type value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;

		list()
			: m_head(nullptr), m_tail(nullptr)
		{
		}

		void push_back(const value_type& value)
		{
			node <value_type>* el = new node <value_type>(value, nullptr, m_tail);
			if (empty()) {

				m_head = el;
				m_tail = m_head;

			}
			else {
				m_tail->next = el;
				m_tail = el;
			}
		}

		void push_front(const value_type& value)
		{
			node <value_type>* el = new node <value_type>(value, m_head, nullptr);

			if (empty()) {

				m_head = el;
				m_tail = m_head;

			}
			else {
				m_head->prev = el;
				m_head = el;
			}
		}

		reference front()
		{
			if (!empty()) {
				return m_head->value;
			}
		}

		const_reference front() const
		{
			if (!empty()) {
				return m_head->value;
			}
		}

		reference back()
		{
			if (!empty()) {
				return m_tail->value;
			}
		}

		const_reference back() const
		{
			if (!empty()) {
				return m_tail->value;
			}
		}

		void pop_front()
		{
			node <value_type>* el = m_head;

			if (size() == 1) {

				m_head = nullptr;
				m_tail = nullptr;
			}
			else {
				m_head->next->prev = nullptr;
				m_head = m_head->next;
			}

			delete el;
		}

		void pop_back()
		{
			node <value_type>* el = m_tail;

			if (size() == 1) {

				m_head = nullptr;
				m_tail = nullptr;
			}
			else {
				m_tail->prev->next = nullptr;
				m_tail = m_tail->prev;
			}

			delete el;
		}

		size_t size() const
		{
			size_t i = 0;
			node <value_type> * el = m_head;

			while (el) {
				el = el->next;
				i++;
			}

			return i;
		}
		~list()
		{
			while (m_head) {
				delete m_head->prev;
				m_head = m_head->next;
			}

			delete m_tail;
		}


		list(const list& other)
		{
			m_head = new node <value_type>(other.m_head->value, nullptr, nullptr);
			node <value_type>* el = m_head;
			node <value_type>* cur = m_head->next;
			node <value_type>* other_el = other.m_head->next;
			while (other_el) {

				cur = new node <value_type>(other_el->value, nullptr, el);
				el->next = cur;
				other_el = other_el->next;
				el = cur;
			}
			m_tail = cur;
		}

		list(list&& other)
		{
			m_head = other.m_head;
			m_tail = other.m_tail;
			other.m_head = nullptr;
			other.m_tail = nullptr;
		}

		list& operator= (const list& other)
		{
			if (m_head == other.m_head) {
				return *this;
			}

			if (!other.size()) {
				m_head = nullptr;
				m_tail = nullptr;
				return *this;
			}
			else {
				this->clear();

				m_head = new node <value_type>(other.m_head->value, nullptr, nullptr);
				node <value_type>* el = m_head;
				node <value_type>* cur = m_head->next;
				node <value_type>* other_el = other.m_head;

				while (other_el) {
					cur = new node <value_type>(other_el->value, nullptr, el);
					el->next = cur;
					other_el = other_el->next;
					el = cur;
				}

				m_tail = cur;
				return *this;

			}
		}

		size_t size() const
		{
			size_t i = 0;
			node <value_type> * el = m_head;

			while (el) {
				el = el->next;
				i++;
			}

			return i;
		}
		
		void clear()
		{
			node <value_type>* tmp = m_head;
			node <value_type>* el;

			while (tmp) {
				el = tmp;
				tmp = tmp->next;
				delete el;
			}

			m_head = nullptr;
			m_tail = nullptr;
		}
		bool empty() const
		{
			return !m_head;
		}

		list::iterator begin()
		{
			return iterator(m_head);
		}

		list::iterator end()
		{
			return iterator();
		}
		iterator insert(iterator pos, const Type& value)
		{
			if (!pos.m_node) {
				push_back(value);
				return iterator(m_tail);
			}
			else if (!pos.m_node->prev) {
				push_front(value);
				return iterator(m_head);
			}
			else {
				node <value_type>* in = new node <value_type>(value, pos.m_node, pos.m_node->prev);
				pos.m_node->prev = pos.m_node->prev->next = in;
				return iterator(in);
			}
		}

		iterator erase(iterator pos)
		{
			if (!pos.m_node) {
				return nullptr;
			}
			else if (!pos.m_node->prev) {
				pop_front();
				return iterator(m_head);
			}
			else if (!pos.m_node->next) {
				pop_back();
				return iterator(m_tail);
			}


			node <value_type>* el = pos.m_node;
			pos.m_node->next->prev = pos.m_node->prev;
			pos.m_node->prev->next = pos.m_node->next;
			delete el;
			return iterator(pos.m_node->next);
		}

	private:
		//your private functions

		node<Type>* m_head;
		node<Type>* m_tail;
	};

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
			return  m_node->value;
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
			list_iterator tmp(*this);
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
}// namespace stepik