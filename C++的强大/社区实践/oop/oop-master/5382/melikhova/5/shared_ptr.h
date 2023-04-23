#pragma once
#include "stdafx.h"
#include <iostream>

template <typename T>
class shared_ptr
{
public:
	explicit shared_ptr(T *ptr = 0)
	{
		if (ptr) {
			this->count = new long;
			*(this->count) = 1;
			this->m_obj = ptr;
		}
		else {
			this->m_obj = nullptr;
			this->count = nullptr;
		}
	}

	~shared_ptr()
	{
		if (count) {
			(*count)--;
			if (*count == 0) {
				delete m_obj;
				m_obj = nullptr;
				delete count;
				count = nullptr;
			}
		}
	}

	shared_ptr(const shared_ptr & other)
	{
		if (other.get()) {
			this->count = other.get_count();
			++(*count);
			this->m_obj = other.get();
		}
		else
		{
			this->m_obj = nullptr;
			this->count = nullptr;
		}
	}

	shared_ptr& operator=(const shared_ptr & other)
	{
		if (this == &other)
			return *this;

		this->~shared_ptr();
		if (other.get()) {
			this->m_obj = other.get();
			this->count = other.get_count();
			(*this->count)++;
		}
		else {
			this->m_obj = nullptr;
			count = nullptr;
		}
		return *this;
	}

	explicit operator bool() const
	{
		if (this->get())
			return true;
		else return false;
	}

	T* get() const
	{
		if (m_obj)
			return m_obj;
		else return nullptr;
	}

	long use_count() const
	{
		if (m_obj)
			return *count;
		else return 0;
	}

	long* get_count() const
	{
		if (m_obj)
			return count;
		else return nullptr;
	}

	T& operator*() const
	{
		return *m_obj;
	}

	T* operator->() const
	{
		return m_obj;
	}

	void swap(shared_ptr& x) noexcept
	{
		shared_ptr<T> help = *this;
		*this = x;
		x = help;
	}

	void reset(T *ptr = 0)
	{
		this->~shared_ptr();
		if (ptr) {
			this->m_obj = ptr;
			this->count = new long;
			*(this->count) = 1;
		}
		else {
			this->m_obj = nullptr;
			this->count = nullptr;
		}
	}

	template <class Y>
	shared_ptr(const shared_ptr<Y> & other)
	{
		if (other.get()) {
			m_obj = other.get();
			count = other.get_count();
			++(*count);
		}
		else {
			m_obj = nullptr;
			count = nullptr;
		}
	}

	template <class Y>
	shared_ptr& operator=(const shared_ptr<Y>& other)
	{
		this->~shared_ptr();
		if (other.get()) {
			m_obj = other.get();
			count = other.get_count();
			++(*count);
		}
		else {
			m_obj = nullptr;
			count = nullptr;
		}
		return *this;
	}

	bool operator <(const shared_ptr& ptr) {
		return *m_obj < *ptr.get();
	}

	bool operator <=(const shared_ptr& ptr) {
		return *m_obj <= *ptr.get();
	}

private:
	T *m_obj;
	long *count;
};

template <class F, class S>
bool operator== (const shared_ptr<F>& left, const shared_ptr<S>& right) {
	return left.get() == right.get();
}