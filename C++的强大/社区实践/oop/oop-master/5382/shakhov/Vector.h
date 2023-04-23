#pragma once
#include "stdafx.h"
#include "iostream"
#include <assert.h>
#include <initializer_list>
#include <stdexcept>
#include <vector>

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
		// implement this
		if (count == 0)	m_first = m_last = nullptr;
		else
		{
			m_first = new Type[count];
			m_last = m_first + count;
		}
	}

	template <typename InputIterator>
	my_vector(InputIterator first, InputIterator last)
		:my_vector(last - first)
	{
		// implement this
		for (size_t i = 0; i<last - first; ++i)
		{
			m_first[i] = first[i];
		}
	}

	my_vector(std::initializer_list<Type> init)
		:my_vector(init.begin(), init.end())
	{
		// implement this
	}

	my_vector(const my_vector& other)
		:my_vector(other.begin(), other.end())
	{
		// implement this
	}

	my_vector(my_vector&& other)
		:m_first(other.m_first), m_last(other.m_last)
	{
		// implement this
		other.m_first = other.m_last = nullptr;
	}

	~my_vector()
	{
		// implement this
		delete[] m_first;
		m_first = m_last = nullptr;
	}

	my_vector& operator=(const my_vector& other)
	{
		// implement this
		if (this != &other)
		{
			if (other.empty()) this->~my_vector();
			else
			{
				this->~my_vector();
				this->m_first = new Type[other.size()];
				this->m_last = m_first + other.size();
				auto i = other.begin();
				for (auto index = this->begin(); index != this->end(); ++index, ++i)
				{
					*index = *i;
				}
			}
		}
		return *this;
	}

	my_vector& operator=(my_vector&& other)
	{
		// implement this
		if (this != &other)
			if (other.empty()) this->~my_vector();
			else
			{
				this->~my_vector();
				this->m_first = other.m_first;
				this->m_last = other.m_last;
				other.m_first = other.m_last = nullptr;
			}
		return *this;
	}

	// assign method
	template <typename InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
		// implement this
		resize(last - first);
		for (size_t i = 0; i< size; ++i)
		{
			m_first[i] = first[i];
		}
	}

	// resize methods
	void resize(size_t count)
	{
		// implement this
		if (count == this->size()) return;
		else if (count == 0) this->~my_vector();
		else if (count < this->size())
		{
			my_vector<Type> help(count);
			for (auto i = help.begin(), index = this->begin(); i != help.end(); ++i, ++index)
			{
				*i = *index;
			}
			delete[] m_first;
			m_first = new Type[count];
			m_last = m_first + count;
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
			if (m_first) delete[] m_first;
			m_first = new Type[count];
			m_last = m_first + count;
			for (auto index = this->begin(), i = help.begin(); index != this->begin() + reserv; ++index, ++i)
			{
				*index = *i;
			}
		}
	}

	iterator erase(const_iterator pos)
	{
		my_vector<Type> help(this->size() - 1);
		auto index = this->begin();
		auto i = help.begin();
		for (; index != this->end(); ++index)
		{
			if (index == pos)
			{
				continue;
			}
			*i = *index;
			++i;
		}
		size_t num = pos - this->begin();

		if (m_first) delete[] m_first;
		m_first = new Type[help.size()];
		m_last = m_first + help.size();
		for (index = this->begin(), i = help.begin(); index != this->end(); ++index, ++i)
		{
			*index = *i;
		}
		return this->begin() + num;
	}

	iterator erase(const_iterator first, const_iterator last)
	{
		// implement this
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

		if (m_first) delete[] m_first;
		m_first = new Type[help.size()];
		m_last = m_first + help.size();
		for (index = this->begin(), i = help.begin(); i != help.end(); ++index, ++i)
		{
			*index = *i;
		}
		return this->begin() + num;
	}

	//insert methods
	iterator insert(const_iterator pos, const Type& value)
	{
		my_vector<Type> help(this->size() + 1);
		auto i = help.begin();
		for (auto index = this->begin(); index != pos; ++index, ++i)
		{
			*i = *index;
		}
		*i = value;
		++i;
		size_t num = pos - this->begin();
		for (auto index = pos; index != this->end(); ++index, ++i)
		{
			*i = *index;
		}

		resize(help.size());

		for (auto index = this->begin(), i = help.begin(); index != this->end(); ++index, ++i)
		{
			*index = *i;
		}
		//copy(*this, help);

		return this->begin() + num;

	}

	template <typename InputIterator>
	iterator insert(const_iterator pos, InputIterator first, InputIterator last)
	{
		// implement this
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

		//copy(*this, help);

		return this->begin() + num;
	}

	//push_back methods
	void push_back(const value_type& value)
	{
		// implement this
		insert(end(), value);
	}

	void copy(my_vector &first, const my_vector& second)
	{
		auto i = second.begin();
		for (auto index = first.begin(); index != first.end(); ++index, ++i)
		{
			*index = *i;
		}
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

	//your private functions

private:
	iterator m_first;
	iterator m_last;
};