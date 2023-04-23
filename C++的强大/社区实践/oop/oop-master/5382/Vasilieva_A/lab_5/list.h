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
		node *next;
		node *prev;

		node(const Type& value, node<Type>* next, node<Type>* prev) : value(value), next(next), prev(prev) {}
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

		list_iterator() : m_node(NULL) {}

		list_iterator(const list_iterator& other) : m_node(other.m_node) {}

		list_iterator& operator = (const list_iterator& other)
		{
			m_node = other.m_node;
			return *this;
		}

		bool operator == (const list_iterator& other) const
		{
			if (this == &other)
			{
				return true;
			}
			return m_node == other.m_node;;
		}

		bool operator != (const list_iterator& other) const
		{
			return !operator==(other);
		}

		reference operator * ()
		{
			return m_node->value;
		}

		pointer operator -> ()
		{
			return &m_node->value;
		}

		list_iterator& operator ++ ()
		{
			m_node = m_node->next;
			return *this;
		}

		list_iterator operator ++ (int)
		{
			list_iterator tmp(*this);
			m_node = m_node->next;
			return tmp;
		}

	private:
		friend class list<Type>;
		list_iterator(node<Type>* p) : m_node(p) {}
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

		list() : m_head(nullptr), m_tail(nullptr) {}

		~list()	//деструктор
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

		iterator insert(iterator pos, const Type& value)
		{
			node<Type>* add_elem = new node<Type>(value, nullptr, nullptr);
			if (pos.m_node == m_head)
			{
				add_elem->next = m_head;
				m_head->prev = add_elem;
				m_head = add_elem;
			}
			else
			{
				add_elem->next = pos.m_node;
				add_elem->prev = pos.m_node->prev;
				pos.m_node->prev->next = add_elem;
				pos.m_node->prev = add_elem;
			}
			return add_elem;
		}

		iterator erase(iterator pos)
		{
			node<Type>* ret_node = pos.m_node->next;
			if (pos.m_node == m_head)
			{
				pop_front();
			}
			else
			{
				if (pos.m_node->next == nullptr)
				{
					m_tail->prev->next = nullptr;
					m_tail = m_tail->prev;
					delete pos.m_node;
					pos.m_node = nullptr;
				}
				else
				{
					pos.m_node->prev->next = pos.m_node->next;
					pos.m_node->next->prev = pos.m_node->prev;
					delete pos.m_node;
					pos.m_node = nullptr;
				}
			}
			return ret_node;
		}

		list(const list& other) : m_head(), m_tail()  //конструктор копирования
		{
			node<Type> *tmp = other.m_head;
			for (size_t i = 0; i != other.size(); i++)
			{
				push_back(tmp->value);
				tmp = tmp->next;
			}
		}

		list(list&& other)	//конструктор перемещения
		{
			m_head = other.m_head;
			m_tail = other.m_tail;
			other.m_head = nullptr;
			other.m_tail = nullptr;
		}

		void my_swap(list& a)
		{
			node<Type>* tmp1 = m_head;
			m_head = a.m_head;
			a.m_head = tmp1;

			node<Type>* tmp2 = m_tail;
			m_tail = a.m_tail;
			a.m_tail = tmp2;
		}

		list& operator= (const list& other)
		{
			list<Type> tmp(other);
			tmp.my_swap(*this);
			return *this;
		}

		void push_back(const value_type& value)	//вставка в хвост
		{
			node<Type> *add_elem = new node<Type>(value, nullptr, nullptr);
			if (m_head == nullptr)
			{
				m_head = add_elem;
			}
			else
			{
				m_tail->next = add_elem;
				add_elem->prev = m_tail;
			}
			m_tail = add_elem;
		}

		void push_front(const value_type& value)	//вставка в голову
		{
			node<Type> *add_elem = new node<Type>(value, nullptr, nullptr);
			if (m_head == nullptr)
			{
				m_tail = add_elem;
			}
			else
			{
				m_head->prev = add_elem;
				add_elem->next = m_head;
			}
			m_head = add_elem;
		}

		reference front()	//возвращает ссылку на первый элемент
		{
			return m_head->value;
		}

		const_reference front() const
		{
			return m_head->value;
		}

		reference back()	//возвращает ссылку на последний элемент
		{
			return m_tail->value;
		}

		const_reference back() const
		{
			return m_tail->value;
		}

		void pop_front()	//удаляет первый элемент
		{
			if (m_head != nullptr)
			{
				if (m_tail == m_head)
				{
					delete m_head;
					m_head = nullptr;
					m_tail = nullptr;
				}
				else
				{
					node<Type> *del_elem = m_head;
					m_head = m_head->next;
					delete del_elem;
					m_head->prev = nullptr;
				}
			}
		}

		void pop_back()	//удаляет последний элемент
		{
			if (m_head != nullptr)
			{
				if (m_tail == m_head)
				{
					delete m_head;
					m_head = nullptr;
					m_tail = nullptr;
				}
				else
				{
					node<Type> *del_elem = m_tail;
					m_tail = m_tail->prev;
					delete del_elem;
					m_tail->next = nullptr;
				}
			}
		}

		void clear()	//удаляет все элементы
		{
			size_t size = this->size();
			while (size != 0)
			{
				pop_front();
				size--;
			}
		}

		bool empty() const	//проверяет на пустоту
		{
			if (m_head == nullptr)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		size_t size() const	//возвращает размер
		{
			size_t count = 0;
			node<Type> *tmp = m_head;
			if (this->empty() == false)
			{
				while (tmp != m_tail->next)
				{
					tmp = tmp->next;
					count++;
				}
			}
			return count;
		}

	private:
		//your private functions
		node<Type>* m_head;
		node<Type>* m_tail;
	};
}
