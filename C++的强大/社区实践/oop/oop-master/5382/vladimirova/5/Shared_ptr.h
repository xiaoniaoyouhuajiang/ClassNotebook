#pragma once

template <typename T>
class shared_ptr
{
public:

	explicit shared_ptr(T *ptr = 0)
		:smart(ptr)
	{
		if (smart == 0) count = nullptr;
		else count = new long(1);
	}

	~shared_ptr()
	{
		if (smart != nullptr)
		{
			(*count)--;
			if ((*count) == 0)
			{
				delete smart;
				delete count;
				smart = nullptr;
				count = nullptr;
			}
		}
	}

	shared_ptr(const shared_ptr & other)
	{
		if (other.get() != nullptr)
		{
			smart = other.get();
			count = other.c_get();
			(*count)++;
		}
		else
		{
			smart = nullptr;
			count = nullptr;
		}
	}

	shared_ptr& operator=(const shared_ptr & other)
	{
		shared_ptr tmp(other);
		this->swap(tmp);
		return *this;
	}

	template <typename H>
	shared_ptr(const shared_ptr<H> & other)
	{
		if (other.get() != nullptr)
		{
			smart = other.get();
			count = other.c_get();
			(*count)++;
		}
		else
		{
			smart = nullptr;
			count = nullptr;
		}
	}


	explicit operator bool() const
	{
		return smart == nullptr;
	}

	T* get() const
	{
		return smart;
	}

	long* c_get() const
	{
		return count;
	}

	long use_count() const
	{
		if (smart == nullptr) return 0;
		else return *count;
	}

	T& operator*() const
	{
		return *smart;
	}

	T* operator->() const
	{
		return smart;
	}

	void swap(shared_ptr& x) noexcept
	{
		std::swap(smart, x.smart);
		std::swap(count, x.count);
	}

	void reset(T *ptr = 0)
	{
		shared_ptr<T>(ptr).swap(*this);
	}

private:
	T *smart;
	long *count;
};

template <typename H, typename  U>
bool  operator==(const shared_ptr<H>& lhs, const shared_ptr<U>& rhs)
{
	return  lhs.get() == rhs.get();
}

template <class H, class U>
bool   operator!=(const shared_ptr<H>& lhs, const shared_ptr<U>& rhs)
{
	return lhs.get() != rhs.get();
}

template <class H, class U>
bool operator<(const shared_ptr<H>& lhs, const shared_ptr<U>& rhs)
{
	return lhs.get()<rhs.get();
}

template <class H, class U>
bool  operator>(const shared_ptr<H>& lhs, const shared_ptr<U>& rhs)
{
	return rhs < lhs;
}

template <class H, class U>
bool  operator<=(const shared_ptr<H>& lhs, const shared_ptr<U>& rhs)
{
	return !(rhs < lhs);
}

template <class H, class U>
bool  operator>=(const shared_ptr<H>& lhs, const shared_ptr<U>& rhs)
{
	return !(lhs < rhs);
}

template <class H>
bool  operator==(const shared_ptr<H>& lhs, std::nullptr_t rhs)
{
	return !lhs;
}

template <class H>
bool  operator==(std::nullptr_t lhs, const shared_ptr<H>& rhs)
{
	return !rhs;
}

template <class H>
bool operator!=(const shared_ptr<H>& lhs, std::nullptr_t rhs)
{
	return (bool)lhs;
}

template <class H>
bool operator!=(std::nullptr_t lhs, const shared_ptr<H>& rhs)
{
	return (bool)rhs;
}

template <class H>
bool operator<(const shared_ptr<H>& lhs, std::nullptr_t rhs)
{
	return lhs.get() < nullptr;
}

template <class H>
bool operator<(std::nullptr_t lhs, const shared_ptr<H>& rhs)
{
	return nullptr < rhs;
}

template <class H>
bool operator>(const shared_ptr<H>& lhs, std::nullptr_t rhs)
{
	return nullptr < lhs;
}

template <class H>
bool operator>(std::nullptr_t lhs, const shared_ptr<H>& rhs)
{
	return rhs < nullptr;
}

template <class H>
bool operator<=(const shared_ptr<H>& lhs, std::nullptr_t rhs)
{
	return !(nullptr < lhs);
}

template <class H>
bool operator<=(std::nullptr_t lhs, const shared_ptr<H>& rhs)
{
	return !(rhs < nullptr);
}

template <class H>
bool operator>=(const shared_ptr<H>& lhs, std::nullptr_t rhs)
{
	return !(lhs < nullptr);
}

template <class H>
bool operator>=(std::nullptr_t lhs, const shared_ptr<H>& rhs)
{
	return !(nullptr < rhs);
}
