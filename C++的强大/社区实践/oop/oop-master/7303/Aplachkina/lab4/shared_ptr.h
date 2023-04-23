#pragma once
template <typename T>
class shared_ptr
{
public:
	template <typename Sad> friend class shared_ptr;
	explicit shared_ptr(T *ptr = 0)
	{
		pObj = ptr;
		count = new long(1);
	}

	~shared_ptr()
	{
		if ((*count)>0) {
			(*count)--;
		}
		if ((*count) == 0) {
			delete pObj;
			delete count;
		}
	}

	shared_ptr(const shared_ptr & other)
	{
		pObj = other.pObj;
		count = other.count;
		if (count)
			++(*count);
	}

	shared_ptr& operator=(const shared_ptr & other)
	{
		if (this != &other) {
			if ((*count)>0) {
				(*count)--;
			}
			if ((*count) == 0) {
				delete pObj;
				delete count;
			}
			pObj = other.pObj;
			count = other.count;
			if (count)
				++(*count);
		}
		return *this;
	}

	explicit operator bool() const
	{
		return !(pObj == nullptr);
	}

	T* get() const
	{
		return pObj;
	}

	long use_count() const
	{
		if (pObj)
			return *count;
		return 0;
	}

	T& operator*() const
	{
		return *pObj;
	}

	T* operator->() const
	{
		return pObj;
	}

	void swap(shared_ptr& x) noexcept
	{
		shared_ptr p(x);
		x = *this;
		*this = p;
	}

	void reset(T *ptr = 0)
	{
		shared_ptr p(ptr);
		swap(p);
	}

	template <typename Sad>
	shared_ptr(const shared_ptr<Sad> & other) :pObj(other.pObj), count(other.count)
	{
		if (count) {

			(*count)++;

		}
	}

	template <typename Sad>
	shared_ptr& operator=(const shared_ptr<Sad> & other)
	{
		if (pObj != other.pObj) {

			if ((*count)>0) {
				(*count)--;
			}
			if ((*count) == 0) {
				delete pObj;
				delete count;
			}

			pObj = other.pObj;
			count = other.count;
			(*count)++;
		}
		return *this;
	}

	template <typename Sad>
	bool operator == (const shared_ptr<Sad>& other) const {
		return pObj == other.pObj;
	}

private:
	// data members
	T * pObj;
	long*  count;
};