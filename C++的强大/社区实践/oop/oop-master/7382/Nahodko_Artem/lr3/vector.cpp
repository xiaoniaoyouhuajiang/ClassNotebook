#include <iostream>
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
	if(count != 0)
	{
		m_first = new Type[count];
		m_last = m_first + count;
	}
	else
	{
		m_first = nullptr;
		m_last = nullptr;
	}
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last) : vector(last - first)
    {
	std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init) : vector(init.begin(), init.end()) {}

    vector(const vector& other) : vector(other.m_first, other.m_last) {}

    vector(vector&& other)
    {
	swap(*this, other);
	other.m_first = nullptr;
	other.m_last = nullptr;
    }

    ~vector()
    {
	delete [] m_first;
	m_first = nullptr;
	m_last = nullptr;
    }

/*    void print()
    {
         for(auto elem = m_first; elem->next != nullptr; elem = elem->next)
             std::cout << elem->value << " ";
    }*/

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
	size_t offset = pos - m_first;
	resize(size() + 1);
	*(m_last - 1) = value;
	std::rotate(m_first + offset, m_last - 1, m_last);
	return m_first + offset;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
	size_t offset = pos - m_first;
	size_t insert_size = last - first;
	resize(size() + insert_size);
	std::copy(first, last, m_last - insert_size);
	std::rotate(m_first + offset, m_last - insert_size, m_last);
	return m_first + offset;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
	resize(size() + 1);
	(*(m_last - 1)) = value;
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
	if(this != &other)
	{
		vector v1(other);
		swap(*this, v1);
	}
	return *this;
    }

    vector& operator=(vector&& other)
    {
	if(this != &other)
	{
		swap(*this, other);
	}
	return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
	vector v1(first, last);
	swap(*this, v1);
    }

    // resize methods
    void resize(size_t count)
    {
	vector v1(count);
	if(count >= size())
	{
		std::copy(m_first, m_last, v1.m_first);
	}
	else
	{
		std::copy(m_first, m_first + count, v1.m_first);
	}
	swap(*this,v1);
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
	size_t elem = pos - m_first;
	std::rotate(m_first + elem, m_first + elem + 1, m_last);
	resize(size()-1);
	return (m_first + elem);
    }

    iterator erase(const_iterator first, const_iterator last)
    {
	size_t start = first - m_first;
	size_t erase_size = last - first;
	std::rotate(m_first + start, m_first + start + erase_size, m_last);
	resize(m_last - m_first - erase_size);
	return m_first + start;
    }

    void swap(vector& a, vector& b)
    {
    std::swap(a.m_first, b.m_first);
    std::swap(a.m_last, b.m_last);
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
}// namespace stepik


int main() {

	stepik::vector<int> Vec = {1, 2, 3, 4, 5};
	for(int i = 0; i<Vec.size(); i++) std::cout << Vec[i] << " " << std::endl;
        std::cout << std::endl;
	std::cout << "copy vector:" << std::endl;
	stepik::vector<int> newVec (Vec.begin(), Vec.end());
	for(int i = 0; i<newVec.size(); i++) std::cout << newVec[i] << " " << std::endl;
        std::cout << std::endl;
	std::cout << "resize vector:" << std::endl;
	newVec.resize(9);
	newVec[5] = 6;
	newVec[6] = 7;
	newVec[7] = 8;
	newVec[8] = 9;
	for(int i = 0; i<newVec.size(); i++) std::cout << newVec[i] << " ";
        std::cout << std::endl;
	std::cout << "erase vetor:" << std::endl;
	newVec.erase(newVec.begin()+2, newVec.begin()+4);
	for(int i = 0; i<newVec.size(); i++) std::cout << newVec[i] << " ";
        std::cout << std::endl;
	std::cout << "insert new element:" << std::endl;
	newVec.insert(newVec.begin()+2, 777);
	for(int i = 0; i<newVec.size(); i++) std::cout << newVec[i] << " ";
        std::cout << std::endl;
	std::cout << "push back element:" << std::endl;
	newVec.push_back(21);
	for(int i = 0; i<newVec.size(); i++) std::cout << newVec[i] << " ";
        std::cout << std::endl;
	return 0;
}

