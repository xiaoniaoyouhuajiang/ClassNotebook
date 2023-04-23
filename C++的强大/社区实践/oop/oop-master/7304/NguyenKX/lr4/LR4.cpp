// LR4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
namespace stepik
{
	template <typename T>
	class shared_ptr
	{
	public:
		explicit shared_ptr(T *ptr = 0) : ptr(ptr), counter(ptr?new long(1):nullptr)
		{
		}

		~shared_ptr()
		{
			if (ptr != nullptr) {
				if (*counter == 1) {
					delete counter;
					delete ptr;
				}
				else {
					(*counter)--;
				}
			}
		}
		template<class U>
		friend class shared_ptr;

		template<class U>
		shared_ptr(const shared_ptr<U> & other) : ptr(other.get() ? other.get() : nullptr), counter(other.get() ? &(++(*other.counter)) : nullptr){}

		template< class U >
		shared_ptr<T>& operator=(const shared_ptr<U>& other) noexcept {
			shared_ptr<T>(other).swap(*this);
		}

		template <class U>
		bool operator==(const shared_ptr<U>& rhs) const {
			return this->get() == rhs.get();
		}

		explicit operator bool() const
		{
			return get() != nullptr;
		}

		T* get() const
		{
			return ptr;
		}

		long use_count() const
		{
			return counter==nullptr?0:(*counter);
		}

		T& operator*() const
		{
			return *ptr;
		}

		T* operator->() const
		{
			return ptr;
		}

		void swap(shared_ptr& x) noexcept
		{
			long * t_count = this->counter;
			this->counter = x.counter;
			x.counter = t_count;

			T* t_ptr = this->ptr;
			this->ptr = x.ptr;
			x.ptr = t_ptr;
		}

		void reset(T *ptr = 0)
		{
			shared_ptr<T>(ptr).swap(*this);
		}

	private:
		// data members
		long * counter;
		T *ptr;
	};
} // namespace stepik
#include <iostream>

int main()
{
	int *a = new int(1);

    std::cout << a<<'\n'<<&(++(*a));
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
