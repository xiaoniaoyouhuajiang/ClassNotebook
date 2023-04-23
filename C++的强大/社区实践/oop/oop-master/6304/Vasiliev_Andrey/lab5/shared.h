#ifndef SHARED_H
#define SHARED_H

#include <algorithm>
#include <iostream>

namespace stepik
{
template <typename T>
class shared_ptr
{
		template<class U> friend class shared_ptr;
public:
		explicit shared_ptr(T *ptr = 0)
				  :m_ptr(ptr),m_ref_count(m_ptr ? new long(1) : nullptr)
		{}

		shared_ptr(const shared_ptr & other)
			:m_ptr(other.m_ptr), m_ref_count(other.m_ref_count)
	{
			if(use_count()>0)
				++(*m_ref_count);
	}

	template <class U>
	shared_ptr(const shared_ptr<U> & other)
			:m_ptr(other.m_ptr), m_ref_count(other.m_ref_count)
	{
			if(use_count()>0)
				++(*m_ref_count);
	}

	~shared_ptr()
	{
	  if(use_count()>1){
			  --(*m_ref_count);
		  //std::cout << "not last copy deleted\n";
	  }
	  else if(use_count() == 1)
	  {
			  delete m_ptr;
			  delete m_ref_count;
			  m_ptr = nullptr;
		  m_ref_count = nullptr;
		//  std::cout << "last copy deleted\n";
	  }
	 }

	shared_ptr& operator=(const shared_ptr & other)
	{
			if(get() != other.get())
		{

				this->~shared_ptr();
				m_ptr = other.m_ptr;
			m_ref_count = other.m_ref_count;
			if(use_count()>0)
					++(*m_ref_count);
		}

		return *this;
	}

	template <class U>
	shared_ptr& operator=(const shared_ptr<U>& other)
	{
			if(get() != other.get())
		{
				this->~shared_ptr();
				m_ptr = other.m_ptr;
			m_ref_count = other.m_ref_count;
			if(use_count()>0)
					++(*m_ref_count);
		}
		return *this;
	}

	explicit operator bool() const
	{
			return m_ptr != nullptr;
	}

	T* get() const
	{
			return m_ptr;
	}

	bool unique() const
	{
			return use_count() == 1;
	}

	long use_count() const
	{
	  return m_ptr ? *m_ref_count : 0;
	}

	T& operator*() const
	{
	  return *m_ptr;
	}

	T* operator->() const
	{
	  return m_ptr;
	}

	void swap(shared_ptr& x) noexcept
	{
	  std::swap(m_ptr,x.m_ptr);
	  std::swap(m_ref_count,x.m_ref_count);
	}

	void reset(T *ptr = 0)
	{

			shared_ptr<T>(ptr).swap(*this);
	}
private:

	T * m_ptr;
	long * m_ref_count;
};


template<class T, class U>
inline bool operator==(shared_ptr<T> const & a, shared_ptr<U> const & b)
{
		return a.get() == b.get();
}

template<class T, class U>
inline bool operator!=(shared_ptr<T> const & a, shared_ptr<U> const & b)
{
		return !(a.get() == b.get());
}
} // namespace stepik

#endif
