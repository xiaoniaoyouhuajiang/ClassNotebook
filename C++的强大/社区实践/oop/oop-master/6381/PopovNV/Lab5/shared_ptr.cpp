#include <iostream>

using namespace std;

namespace stepik{
	template <typename T>
	class shared_ptr  {
public:
	explicit shared_ptr(T *ptr = 0){
		object = ptr;
		count = object ? new size_t(1) : nullptr;
	}

	~shared_ptr(){
		if (use_count() > 1)
			--(*count);
		else {
			delete object;
			delete count;
			object = nullptr;
			count = nullptr;
		}
	}

	shared_ptr(const shared_ptr & other){
		object = other.get();
		count = other.get_count();
		if(use_count())
			++(*count);
	}

	template <typename X>
	shared_ptr(const shared_ptr<X> & other){
		object = other.get();
		count = other.get_count();
		if(use_count())
			++(*count);
	}

	shared_ptr& operator=(const shared_ptr &other){
		if (!(get() == other.get())){
			if (use_count() > 1)
				--(*count);
			else {
				delete object;
				delete count;
				object = nullptr;
				count = nullptr;
			}
			object = other.get();
			count = other.get_count();
			if(use_count())
				++(*count);
		}
		return *this;
	}
	
	template <typename X>
	shared_ptr& operator=(const shared_ptr<X> & other){
		if (!(get() == other.get())){
			if (use_count() > 1)
				--(*count);
			else {
				delete object;
				delete count;
				object = nullptr;
				count = nullptr;
			}
			object = other.get();
			count = other.get_count();
			if(use_count())
				++(*count);
		}
		return *this;
	}

	explicit operator bool() const{
		return object != nullptr;
	}

	T* get() const{
		return object;
	}

	size_t* get_count() const{
		return count;
	}

	size_t use_count() const{
		return object ? *count : 0;
	}

	T& operator*() const{
		return *object;
	}

	T* operator->() const{
		return object;
	}

	void swap(shared_ptr& x){
		std::swap(*this, x);
	}

	void reset(T *ptr = 0){
		shared_ptr<T>(ptr).swap(*this);
	}

	friend ostream& operator<<(ostream& out, shared_ptr& sh){
		out << "ref [" << sh.object <<"] count [" << sh.count <<"]" << endl;
		return out;
	}

	private:
		T *object;
		size_t *count;
	};

	template <class X, class Y>
	bool operator ==(const shared_ptr<X> & a, const shared_ptr<Y> & b){
		return a.get() == b.get();
	}

	template <class X, class Y>
	bool operator !=(const shared_ptr<X> & a, const shared_ptr<Y> & b){
		return a.get() != b.get();
	}
}