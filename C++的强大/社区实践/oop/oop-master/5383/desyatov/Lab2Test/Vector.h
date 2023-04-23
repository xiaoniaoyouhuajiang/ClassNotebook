#pragma once
#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

namespace stepik
{
	template <typename Type>
	class vector
	{
	public:
		typedef Type* iterator;
		typedef const Type* const_iterator;

		typedef Type value_type;

		typedef value_type& reference;
		typedef const value_type& const_reference;

		typedef std::ptrdiff_t difference_type;

		explicit vector(size_t count = 0)
		{
			// use previous step implementation
			m_first = new Type[count];
			m_last = m_first + count;
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			// use previous step implementation
			m_first = new Type[last - first];
			m_last = m_first + (last - first);
			try
			{
				std::copy(first, last, m_first);
			}
			catch (...)
			{
				delete[] m_first;
				throw;
			}
		}

		vector(std::initializer_list<Type> init) : vector(init.begin(), init.end())
		{
			// use previous step implementation
		}

		vector(const vector& other) : vector(other.begin(), other.end())
		{
			// use previous step implementation
		}

		vector(vector&& other)
		{
			// use previous step implementation
			m_last = other.m_last;
			m_first = other.m_first;
			other.m_first = nullptr;
			other.m_last = nullptr;
		}

		~vector()
		{
			// use previous step implementation
			delete[] m_first;
		}

		//insert methods
		//Вставляет элемент value перед элементом pos
		//Возвращает указатель на вставленный элемент
		iterator insert(const_iterator pos, const Type& value)
		{
			// implement this
			size_t quanity = pos - m_first;
			push_back(value);
			std::rotate(m_first + quanity, m_last - 1, m_last);
			return m_first + quanity;
		}
		//Вставляет элементы диапозона от first до last за элементом pos.
		//Возвращает указатель на первый вставленный элемент
		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			// implement this
			size_t size = last - first;
			iterator temporary = const_cast<iterator>(pos);
			while (size)
			{
				temporary = insert(temporary, first[size - 1]);
				size--;
			}
			return temporary;
		}

		//push_back methods
		//Добавляет элемент value в конец контейнера. Новый элемент является копией value
		void push_back(const value_type& value)
		{
			// implement this
			resize(size() + 1);
			m_first[size() - 1] = value;
		}

		//at methods
		reference at(size_t pos)
		{
			return checkIndexAndGet(pos);
		}

		const_reference at(size_t pos) const
		{
			return checkIndexAndGet(pos);
		}

		void resize(size_t count)
		{
			size_t size = m_last - m_first;
			iterator last = (count >= size) ? m_last : m_first + count;
			vector tmp(count);
			std::move(m_first, last, tmp.m_first);
			std::swap(tmp.m_first, m_first);
			std::swap(tmp.m_last, m_last);
		}

		//[] operators
		reference operator[](size_t pos)
		{
			return m_first[pos];
		}

		const_reference operator[](size_t pos) const
		{
			return m_first[pos];
		}

		//*begin methods
		iterator begin()
		{
			return m_first;
		}

		const_iterator begin() const
		{
			return m_first;
		}

		//*end methods
		iterator end()
		{
			return m_last;
		}

		const_iterator end() const
		{
			return m_last;
		}

		//size method
		size_t size() const
		{
			return m_last - m_first;
		}

		//empty method
		bool empty() const
		{
			return m_first == m_last;
		}

	private:
		reference checkIndexAndGet(size_t pos) const
		{
			if (pos >= size())
			{
				throw std::out_of_range("out of range");
			}

			return m_first[pos];
		}

		//your private functions

	private:
		iterator m_first;
		iterator m_last;
	};
}// namespace stepik