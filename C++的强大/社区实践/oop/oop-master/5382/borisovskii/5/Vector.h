#pragma once
#include <assert.h>
#include <initializer_list>
#include <stdexcept>

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
		: m_first (count ? new Type[count] : nullptr), m_last (count ? m_first + count : nullptr)
	{}

	template <typename InputIterator>
	my_vector(InputIterator first, InputIterator last)
		:my_vector(last - first)
	{
		my_copy(first, last, m_first);
	}

	my_vector(std::initializer_list<Type> init)
		:my_vector(init.begin(), init.end())
	{}

	my_vector(const my_vector& other)
		:my_vector(other.begin(), other.end())
	{}

	my_vector(my_vector&& other)
		:m_first(other.m_first), m_last(other.m_last)
	{
		other.m_first = other.m_last = nullptr;
	}

	~my_vector()
	{
		destroy();
	}

	void destroy() {
		delete[] m_first;
		m_first = m_last = nullptr;
	}

	my_vector& operator=(const my_vector& other)
	{
		if (this != &other)
		{
			if (other.empty()) destroy();
			else
			{
				destroy();
				this->m_first = new Type[other.size()];
				this->m_last = m_first + other.size();
				my_copy(other.begin(), other.end(), m_first);
			}
		}
		return *this;
	}

	my_vector& operator=(my_vector&& other)
	{
		if (this != &other)
			if (other.empty()) destroy();
			else
			{
				destroy();
				this->m_first = other.m_first;
				this->m_last = other.m_last;
				other.m_first = other.m_last = nullptr;
			}
		return *this;
	}

	template <typename InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
		resize(last - first);
		my_copy(first, last, m_first);
	}

	void resize(size_t count)
	{
		if (count == this->size()) return;
		else if (count == 0) destroy();
		else if (count < this->size())
		{
			my_vector<Type> help(m_first, m_first + count);
			*this = help;
		}
		else if (count > this->size())
		{
			my_vector<Type> help = *this;
			*this = my_vector<Type>(count);
			my_copy(help.begin(), help.end(), m_first);
		}
	}

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

	iterator insert(const_iterator pos, const Type& value)
	{
		my_vector<Type> help { value };
		return insert(pos, help.begin(), help.end());
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

		*this = help;
		return this->begin() + num;
	}

	void push_back(const value_type& value)
	{
		insert(end(), value);
	}

	reference at(size_t pos)
	{
		return checkIndexAndGet(pos);
	}

	const_reference at(size_t pos) const
	{
		return checkIndexAndGet(pos);
	}

	reference operator[](size_t pos)
	{
		return m_first[pos];
	}

	const_reference operator[](size_t pos) const
	{
		return m_first[pos];
	}

	iterator begin()
	{
		return m_first;
	}

	const_iterator begin() const
	{
		return m_first;
	}

	iterator end()
	{
		return m_last;
	}

	const_iterator end() const
	{
		return m_last;
	}

	size_t size() const
	{
		return m_last - m_first;
	}

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

template< class InputIt, class OutputIt >
OutputIt my_copy(InputIt first, InputIt last, OutputIt d_first) {
	for (; first != last; ++first, ++d_first) {
		*d_first = *first;
	}
	return d_first;
}