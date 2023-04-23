template <typename T>
class shared_ptr
{
	template <typename Derived>
	friend class shared_ptr;
public:
	explicit shared_ptr(T *ptr = 0) : index(ptr), count(new size_t(1))
	{}

	~shared_ptr(){
		destroy();
	}

	shared_ptr(const shared_ptr & other) : index(other.index), count(other.count){
		(*count)++;
	}

	template <typename Derived>
	shared_ptr(const shared_ptr<Derived> & other) : index((T*)other.index), count(other.count) {
		(*count)++;
	}

	shared_ptr& operator=(const shared_ptr & other){
		if ((void*)this == (void*)&other) return *this;
		destroy();
		index = (T*)other.index;
		count = other.count;
		(*count)++;
		return *this;
	}

	template <typename Derived>
	shared_ptr& operator=(const shared_ptr<Derived> & other) {
		if ((void*)this == (void*)&other) return *this;
		destroy();
		index = (T*)other.index;
		count = other.count;
		(*count)++;
		return *this;
	}

	explicit operator bool() const{
		return index != NULL;
	}

	template <typename Derived>
	bool operator==(const shared_ptr<Derived> & other) const{
		return (index == other.index);
	}

	T* get() const{
		return index;
	}

	long use_count() const{
		return (index == NULL) ? 0 : *count;
	}

	T& operator*() const{
		return *index;
	}

	T* operator->() const{
		return index;
	}

	void swap(shared_ptr& x) noexcept{
		std::swap(this->index, x.index);
		std::swap(this->count, x.count);
	}

	void reset(T *ptr = 0){
		shared_ptr x(ptr);
		swap(x);
	}

private:
	void destroy() {
		if ((*count) > 1) {
			(*count)--;
			return;
		}
		delete index;
		delete count;
	}
	T *index = NULL;
	size_t *count;
};