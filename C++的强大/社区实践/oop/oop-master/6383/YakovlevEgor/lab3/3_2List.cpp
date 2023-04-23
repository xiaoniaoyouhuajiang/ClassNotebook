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

		iterator begin()
		{
			return iterator(m_head);
		}

		iterator end()
		{
			return iterator();
		}

		list(const list& other)
		{
			auto c = other.m_head;
			while (c != nullptr) {
				push_back(c->value);
				c = c->next;
			}
		}

		list(list&& other)
		{
			m_head = other.m_head;
			m_tail = other.m_tail;
			other.m_tail = nullptr;
			other.m_head = nullptr;
		}

		list& operator= (const list& other)
		{
			if (this == &other)return *this;
			clear();
			for (auto r = other.m_head; r != nullptr; r = r->next)push_back(r->value);
			return *this;
		}

		void push_back(const value_type& value)
		{
			if (empty()) {
				m_tail = m_head = new node<Type>(value, nullptr, nullptr);
				return;
			}
			m_tail->next = new node<Type>(value, nullptr, m_tail);
			m_tail = m_tail->next;
		}

		iterator insert(iterator pos, const Type& value)
		{
			auto ref = pos.m_node;
			if (ref == nullptr) {
				push_back(value);
				return iterator(m_tail);
			}
			if (ref == m_head) {
				push_front(value);
				return iterator(m_head);
			}
			auto n = new node<Type>(value, ref, ref->prev);
			n->next->prev = n;
			n->prev->next = n;
			return iterator(n);
		}

		iterator erase(iterator pos)
		{
			auto ref = pos.m_node;
			if (ref == m_head) {
				pop_front();
				return iterator(m_head);
			}
			if (ref == m_tail) {
				pop_back();
				return iterator(m_tail);
			}
			ref->prev->next = ref->next;
			ref->next->prev = ref->prev;
			iterator i(ref->next);
			delete ref;
			return i;
		}


		void push_front(const value_type& value)
		{
			if (empty()) {
				m_tail = m_head = new node<Type>(value, nullptr, nullptr);
				return;
			}
			m_head = new node<Type>(value, m_head, nullptr);
			m_head->next->prev = m_head;
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
			if (m_head == m_tail) {
				delete m_head;
				m_head = m_tail = nullptr;
				return;
			}
			m_head = m_head->next;
			delete m_head->prev;
			m_head->prev = nullptr;
		}

		void pop_back()
		{
			if (m_head == m_tail) {
				delete m_head;
				m_head = m_tail = nullptr;
				return;
			}
			m_tail = m_tail->prev;
			delete m_tail->next;
			m_tail->next = nullptr;
		}

		void clear()
		{
			while (!empty())pop_back();
		}

		bool empty() const
		{
			return m_head == nullptr;
		}

		size_t size() const
		{
			auto c = m_head;
			size_t s = 0;
			while (c != nullptr) {
				s++;
				c = c->next;
			}
			return s;
		}

	private:
		//your private functions

		node<Type>* m_head = nullptr;
		node<Type>* m_tail = nullptr;
	};

}// namespace stepik