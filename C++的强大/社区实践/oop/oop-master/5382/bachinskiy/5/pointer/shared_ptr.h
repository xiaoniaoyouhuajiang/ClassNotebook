
#ifndef SHARED_PTR
#define SHARED_PTR

#include <iostream>

namespace stepik {
    template<typename T>
    class shared_ptr {
    public:

        explicit shared_ptr(T *ptr = 0) : thing(ptr) {
            if (ptr != 0) {
                counter = new counter_type(1);
            }
        }

        virtual ~shared_ptr() {
            dec();
        }

        shared_ptr(const shared_ptr &other) {
            copy(other);
        }
        template<typename B>
        shared_ptr(const shared_ptr<B> &other) {
            copy(other);
        }

        template<typename B>
        shared_ptr &operator=(const shared_ptr<B> &other) {
            if (other.thing != thing) {
                dec();
                copy(other);
            }

        }

        explicit operator bool() const {
            return thing != nullptr && *counter > 0;
        }

        T *get() const {
            return thing;
        }

        long use_count() const {
            if (thing == nullptr) {
                return 0;
            } else {
                return *counter;
            }

        }

        T &operator*() const {
            return *thing;
        }

        T *operator->() const {
            return thing;
        }

        void swap(shared_ptr &x) noexcept {
            T *temp = thing;
            this->thing = x.thing;
            x.thing = temp;

            counter_type *tempLong = counter;
            counter = x.counter;
            x.counter = tempLong;
        }

        void reset(T *ptr = 0) {
            dec();
            thing = ptr;
            if (ptr == nullptr) {
                counter = nullptr;
            } else {
                counter = new counter_type(1);
            }
        }

        bool operator==(const shared_ptr &rhs) const {

            return thing == rhs.thing;

        }


    protected:
        typedef long counter_type;

        template <typename B>
        friend class shared_ptr;

    private:

        T *thing;
        counter_type *counter;

        void dec() {
            if (thing != nullptr || counter != nullptr) {
                (*counter)--;
                if (*counter == 0) {
                    delete thing;
                    delete counter;
                }
            }
        }

        template<typename B>
        void copy(const shared_ptr<B> &other) {
            thing = other.thing;
            if (other.get() == nullptr) {
                counter = nullptr;
            } else {
                counter = other.counter;
                (*counter)++;
            }
        }

    };
}
// namespace stepik

#endif