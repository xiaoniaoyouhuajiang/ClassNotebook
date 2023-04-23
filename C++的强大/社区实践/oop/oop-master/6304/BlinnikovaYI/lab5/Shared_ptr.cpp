
template <typename T>
class shared_ptr
{
public:
	explicit shared_ptr(T *ptr = 0)
		:cur_ptr(ptr), count(ptr ? new long(1) : nullptr)
	{}

	~shared_ptr()
	{
		if (use_count() > 1) {
			--(*count);
		}
		else {
			delete cur_ptr;
			delete count;
			cur_ptr = nullptr;
			count = nullptr;
		}
	}

	//copy
	shared_ptr(const shared_ptr & other) :
		cur_ptr(other.cur_ptr), count(other.count)
	{
		if (use_count())
			(*count)++;
	}

	//задает значение shared_ptr 
	shared_ptr& operator=(const shared_ptr & other)
	{
		if (this != &other) {
			this->~shared_ptr();
			cur_ptr = other.cur_ptr;
			count = other.count;
			if (use_count())
				(*count)++;
		}
		return *this;
	}

	//проверяет, указывает ли указатель на объект
	explicit operator bool() const
	{
		return cur_ptr != nullptr;
	}

	//возвращает указатель на управляемый объект 
	T* get() const
	{
		return cur_ptr;
	}

	//возвращает количество объектов shared_ptr, которые ссылаются на тот же управляемый объект 
	long use_count() const
	{
		return cur_ptr ? *count : 0;
	}

	//разыменовывает указатель на управляемый объект
	T& operator*() const
	{
		return *cur_ptr;
	}

	//разыменовывает указатель на управляемый объект 
	T* operator->() const
	{
		return cur_ptr;
	}

	void swap(shared_ptr& x) noexcept
	{
		std::swap(cur_ptr, x.cur_ptr);
		std::swap(count, x.count);
	}
	//заменяет объект, которым владеет 
	void reset(T *ptr = 0)
	{
		shared_ptr<T>(ptr).swap(*this);
	}

	long* get_count() const
	{
		return count;
	}

	//копирование указателей на полиморфные объекты
	template <class X>
	shared_ptr(const shared_ptr<X> & other)
	{
		if (other.get()) {
			cur_ptr = other.get();
			count = other.get_count();
			++(*count);
		}
		else {
			cur_ptr = nullptr;
			count = nullptr;
		}
	}

	template <class X>
	shared_ptr& operator=(const shared_ptr<X>& other)
	{
		this->~shared_ptr();
		if (other.get()) {
			cur_ptr = other.get();
			count = other.get_count();
			++(*count);
		}
		else {
			cur_ptr = nullptr;
			count = nullptr;
		}
		return *this;
	}

private:
	T* cur_ptr;
	long* count;
};

template <class A, class B>
bool operator== (const shared_ptr<A>& left, const shared_ptr<B>& right) {
	return left.get() == right.get();
}
