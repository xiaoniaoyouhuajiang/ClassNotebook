#include <iostream>

namespace stepik
{
template <typename T>
class shared_ptr
{
	  
	template <typename U>
	friend class shared_ptr;

public:
   
	shared_ptr():
	ptr(nullptr), counter(nullptr)
	{
	}
  
  
	explicit shared_ptr(T *p):
	ptr(p), counter(new int(1))
	{
		
	}

	~shared_ptr()
	{
		if (counter) 
		{
			if (*counter == 1) 
			{
				delete counter;
				delete ptr;
			}
			else (*counter)--;
		}
	}

	template <typename U>
	shared_ptr(const shared_ptr<U> & other):
		counter(other.counter), ptr(other.ptr)   
	{
		if (counter)
			(*counter)++;
	}

	shared_ptr(const shared_ptr<T> & other):
		counter(other.counter), ptr(other.ptr)   
	{	
		if (counter)
			(*counter)++;
	}


	template <typename U>
	shared_ptr& operator=(const shared_ptr<U> & other)
	{
		shared_ptr p(other);
		swap(p);
	}

	shared_ptr& operator=(const shared_ptr<T> & other)
	{
		shared_ptr p(other);
		swap(p);
	}


	explicit operator bool() const
	{
		return ptr != nullptr;
	}
	
	T* get() const
	{
		return ptr;
	}

	long use_count() const
	{
		return counter ? *counter : 0;
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
		std::swap(ptr, x.ptr);
		std::swap(counter, x.counter);
	}
   
	void reset()
	{
		this -> ~shared_ptr();
		ptr = nullptr;
		counter = nullptr;
	}

	void reset(T *p)
	{
		reset();
		counter = new int(1);
		ptr = p; 
	}
       
	
	void make_shared_ptr(T *p)
	{
		counter = new int(1);
		ptr = p;
	}


	template <typename U>
	bool operator==(const shared_ptr<U> &other) const
	{
		return (ptr == other.ptr);
	} 


	bool operator==(const shared_ptr<T> &other) const
	{
		return (ptr == other.ptr);
	} 

    
    private:
    	T* ptr;
		int *counter;

  };
}
