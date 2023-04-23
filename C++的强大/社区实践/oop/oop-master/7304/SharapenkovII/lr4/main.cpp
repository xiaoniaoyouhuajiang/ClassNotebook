#include <iostream>

namespace stepik
{
    template <typename T>
    class shared_ptr
    {
    public:

        explicit shared_ptr(T *ptr = 0) : item(ptr), count(ptr ? new long(1) : nullptr)
        {
        }

        ~shared_ptr()
        {
            if(item) {
                if (*count == 1) {
                    delete item;
                    delete count;
                } else {
                    (*count)--;
                }
            }
        }

        shared_ptr(const shared_ptr & other)
        {
            item = other.item;
            count = other.count;
            if(item) (*count)++;
        }

        template< class Y >
        friend class shared_ptr;

        template< class Y >
        shared_ptr( const shared_ptr<Y>& other ) : item(other.get()), count(other.count)
        {
            if(count) (*count)++;
        }

        template<class Y>
        shared_ptr& operator=( const shared_ptr<Y> & other )
        {
            shared_ptr<T>(other).swap(*this);
        }

        template < class Y >
        friend bool operator==( const shared_ptr<T>& lhs, const shared_ptr<Y>& rhs )
        {
            return lhs.get() == rhs.get();
        }

        shared_ptr& operator=(const shared_ptr & other)
        {
            shared_ptr<T>(other).swap(*this);

            return *this;
        }

        explicit operator bool() const
        {
            return get() != nullptr;
        }

        T* get() const
        {
            return item;
        }

        long use_count() const
        {
            return count ? *count : 0;
        }

        T& operator*() const
        {
            return *item;
        }

        T* operator->() const
        {
            return item;
        }

        void swap(shared_ptr& x) noexcept
        {
            T *item_tmp = item;
            item = x.item;
            x.item = item_tmp;

            long *count_tmp = count;
            count = x.count;
            x.count = count_tmp;
        }

        void reset(T *ptr = 0)
        {
            shared_ptr<T>(ptr).swap(*this);
        }

    private:
        T *item;
        long *count;
    };
} // namespace stepik

int main() {
    long *num = new long;
    *num = 4;
    long *num1 = new long;
    *num1 = 5;

    stepik::shared_ptr<long> ptr1(nullptr);
    std::shared_ptr<long> sptr1(nullptr);

    {
        stepik::shared_ptr<long> ptr3(ptr1);
        std::shared_ptr<long> sptr3(sptr1);

        std::cout << ptr3.use_count() << std::endl;
        std::cout << sptr3.use_count() << std::endl;

    }
    std::cout << ptr1.use_count() << std::endl;
    std::cout << sptr1.use_count() << std::endl;
    return 0;
}