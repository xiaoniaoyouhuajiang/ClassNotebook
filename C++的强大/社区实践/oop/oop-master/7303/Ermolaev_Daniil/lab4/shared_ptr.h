#ifndef SMARTPTR_H
#define SMARTPTR_H

namespace stepik {
    template <typename T>
    class shared_ptr {
            template <typename V>
            friend class shared_ptr;
        public:
            explicit shared_ptr(T *ptr = 0)
                :ptr(ptr), count(new long(1))
            {}

            ~shared_ptr() {
                count_dec();
            }

            template<typename V>
            shared_ptr(const shared_ptr<V>& other)
                :ptr(other.ptr), count(other.count) {
                (*count)++;
            }

            template<typename V>
            shared_ptr& operator=(const shared_ptr<V>& other) {
                if (*this != other) {
                    count_dec();
                    ptr = other.ptr;
                    count = other.count;
                    (*count)++;
                }

                return *this;
            }

            explicit operator bool() const {
                return ptr != nullptr;
            }

            T* get() const {
                return ptr;
            }

            long use_count() const {
                return ptr ? *count : 0;
            }

            T& operator*() const {
                return *ptr;
            }

            T* operator->() const {
                return ptr;
            }

            void swap(shared_ptr& x) noexcept {
                std::swap(ptr, x.ptr);
                std::swap(count, x.count);
            }

            void reset(T *ptr = 0) {
                count_dec();
                this->ptr = ptr;
                count = new long(1);
            }

            template<typename V>
            bool operator==(const shared_ptr<V>& other) const {
                return ptr == other.ptr;
            }

            template<typename V>
            bool operator!=(const shared_ptr<V>& other) const {
                return ptr != other.ptr;
            }

        private:
            void count_dec() {
                if (--(*count) == 0) {
                    delete ptr;
                    delete count;
                }
            }

            T* ptr;
            long* count;
    };
}

#endif // SMARTPTR_H
