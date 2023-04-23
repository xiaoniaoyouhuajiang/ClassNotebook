#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <utility>
#include <memory>
#include <iostream>
#include <iterator>
#include <vector>
template<typename T>
class Array
{
public:
	// (default) constructor
	Array(const size_t size = 0)
		: m_size(size)
		, m_array(m_size ? new T[m_size]() : nullptr)
	{
	}
	// copy constructor
	Array(const Array& source) {
		std::cout << "Copy constructor called" << std::endl;
		this->m_size = source.m_size;
		std::unique_ptr<T[]> clone(m_size ? new T[m_size]() : nullptr);
		if (m_size) {
			std::copy(source.m_array.get(), source.m_array.get() + source.m_size, clone.get());
		}
		this->m_array.reset(clone.release());
	}
	// move constructor
	Array(Array&& source) {
		std::cout << "Move constructor called" << std::endl;
		this->m_size = source.m_size;
		this->m_array.reset(source.m_array.release());
		source.m_size = 0;
		source.m_array = nullptr;
	}
	Array<T>& operator =(const Array<T>& b) {
		std::cout << "Assignment operator called" << std::endl;
		if (&b == this) return *this;
		if (m_size != b.m_size) {
			std::unique_ptr<T[]> clone(b.m_size ? new T[b.m_size]() : nullptr);
			std::copy(b.m_array.get(), b.m_array.get() + b.m_size, clone.get());
			m_array.reset(clone.release());
			m_size = b.m_size;
			return *this;
		}
		std::copy(b.m_array.get(), b.m_array.get() + b.m_size, m_array.get());
		return *this;
	}
	const size_t size() const
	{
		return m_size;
	}

	T& operator [](const size_t index)
	{
		assert(index < m_size);

		return m_array[index];
	}

private:
	size_t m_size;
	std::unique_ptr<T[]> m_array;
};
int main() {
	Array<int> arr(5);
	std::cout << "Copy attemp: " << std::endl;
	Array<int> arr_cpy(arr);
	std::cout << "Length old: " << arr.size() << std::endl;
	std::cout << "Length cpy: " << arr_cpy.size() << std::endl;

	//std::vector<Array<int>> v;
	//v.push_back(Array<int>(25));
	std::cout << "Move attemp: " << std::endl;
	Array<int> arr_move(Array<int>(Array<int>(5)));

	std::cout << "Using assignment attemp: " << std::endl;
	Array<int> oper(5);
	oper = arr;
	std::cout << "Length arr: " << arr.size() << std::endl;
	std::cout << "Length oper: " << oper.size() << std::endl;
	getchar();
	return 0;
}