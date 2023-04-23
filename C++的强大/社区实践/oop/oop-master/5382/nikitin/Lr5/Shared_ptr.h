#pragma once
template <typename T>
class shared_ptr
{

private:
	T* pointer;
	long *counter;

public:
	explicit shared_ptr(T *ptr = 0) :pointer(ptr)
	{
		if (pointer == 0) counter = nullptr;
		else counter = new long(1);
	}

	~shared_ptr()
	{
		if (pointer != nullptr){
			(*counter)--;
			if ((*counter) == 0){
				delete pointer;
				delete counter;
				pointer = nullptr;
				counter = nullptr;
			}
		}
	}

	shared_ptr(const shared_ptr & other)
	{
		if (other.get() != nullptr){
			pointer = other.get();
			counter = other.c_get();
			(*counter)++;
		}
		else{
			pointer = nullptr;
			counter = nullptr;
		}
	}

	shared_ptr& operator=(const shared_ptr & other)
	{
		shared_ptr temp(other);
		this->swap(temp);
		return *this;
	}

	template<class Y>
	shared_ptr(const shared_ptr<Y> & other)
	{
		if (other.get() != nullptr){
			pointer = other.get();
			counter = other.c_get();
			(*counter)++;
		}
		else{
			pointer = nullptr;
			counter = nullptr;
		}
	}

	explicit operator bool() const
	{
		if (pointer == nullptr)return false;
		else return true;
	}

	T* get() const
	{
		return pointer;
	}

	long use_count() const
	{
		if (pointer == nullptr)return 0;
		else return *counter;
	}

	T& operator*() const
	{
		return *pointer;
	}

	T* operator->() const
	{
		return pointer;
	}

	void swap(shared_ptr& x)
	{
		std::swap(pointer, x.pointer);
		std::swap(counter, x.counter);
	}

		void reset(T *ptr = 0)
	{
		shared_ptr<T>(ptr).swap(*this);
	}
	long* c_get() const
	{
		return counter;
	}
};
template <class F, class S>
bool operator == (const shared_ptr<F>& first, const shared_ptr<S>& second){
	return first.get() == second.get();
}