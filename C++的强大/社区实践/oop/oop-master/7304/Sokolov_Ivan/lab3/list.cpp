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
			m_node = m_node->next;
			return *this;
		}

		list_iterator operator ++ (int)
		{
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

		friend list& operator + (list& l1, list& l2);
		friend list& operator = (list& l1, list& l2);

		list()
			: m_head(nullptr), m_tail(nullptr)
		{
		}

		void push_back(const value_type& value)
		{
			if (!empty())
			{
				node<Type>* newl = new node<Type>(value, nullptr, m_tail);
				m_tail->next = newl;
				m_tail = newl;
			}
			else
			{
				node<Type>* newl = new node<Type>(value, nullptr, nullptr);
				m_head = newl;
				m_tail = newl;
			}
		}

		void push_front(const value_type& value)
		{
			if (!empty())
			{
				node<Type>* buf = new node<Type>(value, m_head, nullptr);
				m_head->prev = buf;
				m_head = buf;
			}
			else
			{
				node<Type>* buf = new node<Type>(value, nullptr, nullptr);
				m_head = buf;
				m_tail = buf;
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
			if (!empty())
			{
				if (size() == 1)
				{
					m_head = NULL;
					m_tail = NULL;
				}
				else
				{
					node<Type>* newl = m_head->next;
					newl->prev = nullptr;
					delete m_head;
					m_head = newl;
				}
			}
		}

		void pop_back()
		{
			if (!empty())
			{
				if (size() == 1)
				{
					m_head = NULL;
					m_tail = NULL;
				}
				else
				{
					node<Type>* newl = m_tail->prev;
					newl->next = nullptr;
					delete m_tail;
					m_tail = newl;
				}
			}
		}

		void clear()
		{
			while (m_head != NULL)
			{
				m_tail = m_head->next;
				delete m_head;
				m_head = m_tail;
			}
		}

		bool empty() const
		{
			return m_head == NULL;
		}

		size_t size() const
		{
			node<Type>* newl = m_head;
			size_t countSize = 0;
			do
			{
				countSize++;
				newl = newl->next;
			} while (newl != NULL);
			return countSize;
		}

		list::iterator begin()
		{
			return iterator(m_head);
		}

		list::iterator end()
		{
			return iterator();
		}

		iterator insert(iterator pos, const Type & value)
		{
			if (pos.m_node == NULL)
			{
				push_back(value);
				return iterator(m_tail);
			}
			else
				if (pos.m_node->prev == NULL)
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
			if (pos.m_node == NULL)
			{
				return NULL;
			}
			else
				if (pos.m_node->prev == NULL)
				{
					pop_front();
					return iterator(m_head);
				}
				else
					if (pos.m_node->next == NULL)
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

		void print()
		{
			for (auto elem = m_head; elem->next != nullptr; elem = elem->next)
				std::cout << elem->value << " ";
			std::cout << m_tail->value;
			std::cout << std::endl;
		}

	private:


		void swap(list & lst)
		{
			std::swap(m_head, lst.m_head);
			std::swap(m_tail, lst.m_tail);
		}

		node<Type>* m_head;
		node<Type>* m_tail;
	};

}

list& operator + (list& l1, list& l2);
{

}

list& operator = (list& l1, list& l2);
{

}

int main() {
	std::cout << "List:" << std::endl;
	stepik::list<int> my_list;
	stepik::list<int> l2;
	stepik::list<int> l3;
	my_list.push_back(32);
	my_list.push_back(45);
	my_list.push_front(62);
	my_list.push_front(13);
	my_list.print();
	l2.push_back(1);
	l2.push_back(2);
	l2.push_back(3);
	l2.push_back(4);
	l2.push_back(5);
	l2.push_back(6);
	l2.print();
	l3 = my_list + l2;
	std::cout << "Print my_list: " << std::endl;
	my_list.print();
	std::cout << "Print l3: " << std::endl;
	l3.print();
/*	std::cout << "Size:" << std::endl;
	std::cout << my_list.size() << std::endl;

	std::cout << "Pop front:" << std::endl;
	my_list.pop_front();
	my_list.print();

	std::cout << "Pop back:" << std::endl;
	my_list.pop_back();
	my_list.print();

	std::cout << "Insert:" << std::endl;
	stepik::list_iterator<int> pos = my_list.begin(); pos++;
	my_list.insert(pos, 57);
	my_list.print();

	std::cout << "Erase:" << std::endl;
	stepik::list_iterator<int> pos1 = my_list.begin(); pos1++;
	my_list.erase(pos1);
	my_list.print();
	*/
	return 0;
}
