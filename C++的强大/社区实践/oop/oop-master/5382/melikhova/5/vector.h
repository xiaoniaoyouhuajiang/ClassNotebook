#include "stdafx.h"
#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
#include <iostream>

using namespace std;

template <typename Type>
class my_vector
{
public:
	typedef Type* iterator;
	typedef const Type* const_iterator;

	typedef Type value_type;

	typedef value_type& reference;
	typedef const value_type& const_reference;

	typedef std::ptrdiff_t difference_type;

	explicit my_vector(size_t count = 0)
	{
		if (count == 0) m_first = m_last = nullptr;
		else {
			m_first = new Type[count];
			m_last = m_first + count;
		}
	}

	template <typename InputIterator>
	my_vector(InputIterator first, InputIterator last)
		:my_vector(last - first)
	{
		for (auto i = this->begin(); i != this->end(); ++i, ++first) {
			*i = *first;
		}
	}

	my_vector(std::initializer_list<Type> init)
		:my_vector(init.begin(), init.end())
	{}

	my_vector(const my_vector& other)
		:my_vector(other.begin(), other.end())
	{}

	my_vector(my_vector&& other)
		:my_vector(other.begin(), other.end())
	{
		other.m_first = other.m_last = nullptr;
	}

	~my_vector()
	{
		delete[] m_first;
		m_first = m_last = nullptr;
	}

	//assignment operators
	my_vector& operator=(const my_vector& other)
	{
		if (this != &other)
		{
			my_vector help(other);
			iterator help_ptr = m_first;
			m_first = help.m_first;
			help.m_first = help_ptr;

			help_ptr = m_last;
			m_last = help.m_last;
			help.m_last = help_ptr;
		}
		return *this;
	}

	my_vector& operator=(my_vector&& other)
	{
		m_first = other.m_first;
		m_last = m_first + other.size();
		other.m_first = other.m_last = nullptr;
		return *this;
	}

	// assign method
	template <typename InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
		delete[] m_first;
		m_first = m_last = nullptr;

		m_first = new Type[last - first];
		m_last = m_first + (last - first);
		for (auto i = this->begin(); i != this->end(); ++i, ++first) {
			*i = *first;
		}
	}

	// resize methods
	void resize(size_t count)
	{
		if (count == this->size()) return;
		else if (count == 0)
		{
			delete[] m_first;
			m_first = m_last = nullptr;
		}
		else if (count < this->size())
		{
			my_vector<Type> help(count);
			for (auto i = help.begin(), index = this->begin(); i != help.end(); ++i, ++index)
			{
				*i = *index;
			}
			*this = my_vector<Type>(count);
			for (auto index = m_first, i = help.begin(); index != m_last; ++index, ++i)
			{
				*index = *i;
			}
		}
		else if (count > this->size())
		{
			my_vector<Type> help(this->size());
			size_t reserv = this->size();
			for (auto index = this->begin(), i = help.begin(); index != this->end(); ++i, ++index)
			{
				*i = *index;
			}
			*this = my_vector<Type>(count);
			for (auto index = this->begin(), i = help.begin(); index != this->begin() + reserv; ++index, ++i)
			{
				*index = *i;
			}
			for (auto index = this->begin() + reserv; index != this->end(); ++index)
			{
				*index = 0;
			}
		}
	}

	//erase methods
	iterator erase(const_iterator pos)
	{
		return erase(pos, pos + 1);
	}

	iterator erase(const_iterator first, const_iterator last)
	{
		my_vector<Type> help(this->size() - (last - first));
		auto index = this->begin();
		auto i = help.begin();
		for (; index != this->end(); ++index)
		{
			if ((index >= first) && (index < last))
			{
				continue;
			}
			*i = *index;
			++i;
		}

		size_t num = first - this->begin();
		*this = help;
		return this->begin() + num;
	}

	//insert methods
	iterator insert(const_iterator pos, const Type& value)
	{
		my_vector<Type> help(this->size() + 1);
		auto i = help.begin();

		for (auto index = this->begin(); index != pos; ++index, ++i) {
			*i = *index;
		}
		*i = value;
		++i;
		size_t num = pos - this->begin();

		for (auto index = pos; index != this->end(); ++index, ++i) {
			*i = *index;
		}

		delete[] m_first;
		m_first = new Type[help.size()];
		m_last = m_first + help.size();

		for (auto index = this->begin(), i = help.begin(); index != this->end(); ++index, ++i) {
			*index = *i;
		}
		return this->begin() + num;
	}

	template <typename InputIterator>
	iterator insert(const_iterator pos, InputIterator first, InputIterator last)
	{
		my_vector<Type> help(this->size() + (last - first));
		auto i = help.begin();
		auto index = this->begin();
		for (; index != pos; ++index, ++i)
		{
			*i = *index;
		}
		size_t num = pos - this->begin();
		for (auto k = first; k != last; ++k, ++i)
		{
			*i = *k;
		}
		for (; index != this->end(); ++index, ++i)
		{
			*i = *index;
		}

		delete[] m_first;
		m_first = new Type[help.size()];
		m_last = m_first + help.size();

		for (auto index = this->begin(), i = help.begin(); index != this->end(); ++index, ++i)
		{
			*index = *i;
		}
		return this->begin() + num;
	}

	//push_back methods
	void push_back(const value_type& value)
	{
		insert(this->end(), value);
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

private:
	iterator m_first;
	iterator m_last;
};
