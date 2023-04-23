
#include <memory>

namespace stepik
{
	template <typename T>
	class shared_ptr
	{
  	public:

	  	using value_type = T;
		using reference = T&;
		using pointer = T*;

		template <class U>
		friend class shared_ptr;

		explicit shared_ptr(T *ptr = 0)
		: m_ptr(ptr), m_refsCounter(ptr ? new long(1) : nullptr)
		{
		}

		~shared_ptr()
		{
			dec_refs();
		}

		shared_ptr(const shared_ptr & other)
		: m_ptr(other.m_ptr), m_refsCounter(other.m_refsCounter)
		{
			inc_refs();
		}
		
		template <class U>
		shared_ptr(const shared_ptr<U> & other)
		: m_ptr(other.m_ptr), m_refsCounter(other.m_refsCounter)
		{
			inc_refs();
		}

		shared_ptr& operator=(const shared_ptr& r)
		{
			shared_ptr(r).swap(*this);
			return (*this);
		}

		template <class U>
		shared_ptr& operator=(const shared_ptr<U>& r)
		{
			shared_ptr(r).swap(*this);
			return (*this);
		}

		explicit operator bool() const
		{
			return (m_ptr != nullptr);
		}

		pointer get() const
		{
			return m_ptr;
		}

		long use_count() const
		{
			return (m_refsCounter ? *m_refsCounter : 0);
		}

		reference operator*() const
		{
			return *m_ptr;
		}

		pointer operator->() const
		{
			return m_ptr;
		}

		void swap(shared_ptr& x) noexcept
		{
			std::swap(m_ptr, x.m_ptr);
			std::swap(m_refsCounter, x.m_refsCounter);
		}

		void reset(T *ptr = 0)
		{
			dec_refs();
			m_ptr = ptr;
			m_refsCounter = ptr ? new long(1) : nullptr;
		}

	private:

		void dec_refs()
		{
			if (m_refsCounter)
				--*m_refsCounter;
			if (use_count() == 0)
				destroy();
		}

		void inc_refs()
		{
			if (m_refsCounter)
				++*m_refsCounter;
		}

		void destroy()
		{
			if (m_ptr) {
				delete m_ptr;
				delete m_refsCounter;
			}
		}

		pointer m_ptr;
		long *m_refsCounter;
	};      
	
	template <class T, class U>
    bool operator==(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
	{
		return (lhs.get() == rhs.get());
	}

	template <class T, class... Args>
	shared_ptr<T> make_shared(Args... args)
	{
		return shared_ptr<T>(new T(args...));
	}

} // namespace stepik

#include <iostream>

class A {
public:
	A(int a) : m_a(a) { }
private:
	int m_a;
};

class B : public A {
public:
	B(int a, int b) : A(a), m_b(b) { }
private:
	int m_b;
};

int main()
{
	stepik::shared_ptr<B> bPtr(new B(7, 8));
	
	stepik::shared_ptr<A> aPtr = bPtr;
	
	return EXIT_SUCCESS;
}