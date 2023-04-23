#include <iostream>
#include <memory>
namespace stepik
{   
    template <typename T>
    class shared_ptr
    {
    public:
        explicit shared_ptr(T *ptr = nullptr)
        : ptr(ptr), count( new int(1))
        {        
        }

        ~shared_ptr()
        {
            clear();
        }

        shared_ptr(const shared_ptr & other)
        : ptr(other.ptr), count(other.count) 
        {
			++(*count);
        }

        shared_ptr& operator=(const shared_ptr & other)
        {
            if (ptr != other.ptr) 
            {
				clear();
				ptr = other.ptr;
				count = other.count;
				++(*count);
			}
			return *this;
        }

        explicit operator bool() const
        {
            return ptr != nullptr;  
        }

        T* get() const
        {
            return ptr;
        }

        int use_count() const
        {
            return ptr == nullptr ? 0 : *count;        
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
            std::swap(count, x.count);
        }

        void reset(T *ptr = 0)
        {
            shared_ptr temp(ptr);
            swap(temp);    
        }

        void clear() 
        {

            if (--(*count) <= 0) 
            {
                delete ptr;
                delete count;
            }
			ptr = nullptr;
			count = nullptr;
		}
        template <typename D>
		friend class shared_ptr;

		template <class D>

		shared_ptr(const shared_ptr<D> & other) : ptr(other.ptr), count(other.count) 
        {
			++ (*count);
		}

		template <typename D>
		shared_ptr& operator=(const shared_ptr<D> & other)
		{
			if (ptr != other.ptr) 
            {

				clear();
				ptr = other.ptr;
				count = other.count;
				++ (*count);

			}
			return *this;
		}
    private:
        T* ptr;
        int * count;
    };      
 // namespace stepik

template <typename T, typename  D>
	bool  operator==(const shared_ptr<T>& lhs, const shared_ptr<D>& rhs) {
		return  lhs.get() == rhs.get();
	}



template<typename T, typename... _Args>
stepik::shared_ptr<T>
my_make_shared(_Args&&... __args)
{
    return stepik::shared_ptr<T>(new T(__args...));
}

}

