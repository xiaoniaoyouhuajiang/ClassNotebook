#pragma once
//#include "stdafx.h"
//#include <iostream>
//#include <memory>

template <typename T>
class shared_ptr
{
	T* ptr_;
	long* count;

public:

	explicit shared_ptr(T *ptr = 0)
		:ptr_(ptr)
	{
		// implement this
		if (ptr_) count = new long(1);
		else count = nullptr;
	}

	~shared_ptr()
	{
		// implement this
		if (ptr_) {
			--(*count);
			if (!(*count)) {
				delete ptr_;
				delete count;
				ptr_ = nullptr;
				count = nullptr;
			}
		}
	}

	shared_ptr(const shared_ptr & other)
		:ptr_(other.get()), count(other.get_count())
	{
		// implement this
		if (ptr_) ++(*count);
	}

	shared_ptr& operator=(const shared_ptr & other)
	{
		// implement this
		if (this != &other) {
			this->~shared_ptr();
			ptr_ = other.get();
			count = other.get_count();
			if (ptr_) ++(*count);
		}
		return *this;
	}

	template <class Y>
	shared_ptr(const shared_ptr<Y> & other)
		:ptr_(other.get()), count(other.get_count())
	{
		// implement this
		if (ptr_) ++(*count);
	}

	template <class Y>
	shared_ptr& operator=(const shared_ptr<Y>& other)
	{
		// implement this
		this->~shared_ptr();
		ptr_ = other.get();
		count = other.get_count();
		if (ptr_) ++(*count);
		return *this;
	}

	explicit operator bool() const
	{
		// implement this
		return ptr_ != nullptr;
	}

	T* get() const
	{
		// implement this
		return ptr_;
	}

	long* get_count() const
	{
		return count;
	}

	long use_count() const
	{
		// implement this
		if (ptr_) return *count;
		else return 0;
	}

	T& operator*() const
	{
		// implement this
		return *ptr_;
	}

	T* operator->() const
	{
		// implement this
		return ptr_;
	}

	void swap(shared_ptr& x) noexcept
	{
		// implement this

		if (this != &x)
		{
			shared_ptr<T> tmp(*this);
			*this = x;
			x = tmp;
		}
	}

	void reset(T *ptr = 0)
	{
		shared_ptr<T>(ptr).swap(*this);
	}

};

template <class F, class S>
bool operator== (const shared_ptr<F>& left, const shared_ptr<S>& right) {
	return left.get() == right.get();
}