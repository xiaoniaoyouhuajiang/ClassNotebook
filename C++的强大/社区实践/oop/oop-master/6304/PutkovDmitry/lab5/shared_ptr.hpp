//
// Created by Dmitry Putkov on 21.05.2018.
//

#ifndef OOPTOTALLAB_SHARED_PTR_H
#define OOPTOTALLAB_SHARED_PTR_H

#endif //OOPTOTALLAB_SHARED_PTR_H

#include <iostream>

using namespace std;

namespace custom {

    template<typename T>
    class shared_ptr {
        T *ptr_;
        size_t *count;

    public:

        explicit shared_ptr(T *ptr = 0)
                : ptr_(ptr), count(ptr ? new size_t(1) : nullptr) {}

        ~shared_ptr() {
            if (count) {
                if (!(*count)) {
                    delete ptr_;
                    delete count;
                    ptr_ = nullptr;
                    count = nullptr;
                } else
                    --(*count);
            }
        }

        shared_ptr(const shared_ptr &other) {
            ptr_ = other.get();
            count = other.get_count();
            ++(*count);
        }

        shared_ptr &operator=(const shared_ptr &other) {
            if (this != &other) {
                this->~shared_ptr();
                if (other.get()) {
                    ptr_ = other.get();
                    count = other.get_count();
                    ++(*count);
                } else {
                    ptr_ = nullptr;
                    count = nullptr;
                }
            }
            return *this;
        }

        template<class Y>
        shared_ptr(const shared_ptr<Y> &other) {
            if (other.get()) {
                ptr_ = other.get();
                count = other.get_count();
                ++(*count);
            } else {
                ptr_ = nullptr;
                count = nullptr;
            }
        }

        template<class Y>
        shared_ptr &operator=(const shared_ptr<Y> &other) {
            this->~shared_ptr();
            if (other.get()) {
                ptr_ = other.get();
                count = other.get_count();
                ++(*count);
            } else {
                ptr_ = nullptr;
                count = nullptr;
            }
            return *this;
        }

        explicit operator bool() const {
            return ptr_ != nullptr;
        }

        T *get() const {
            return ptr_;
        }

        size_t *get_count() const {
            return count;
        }

        size_t use_count() const {
            return ptr_ ? *count : 0;
        }

        T &operator*() const {
            return *ptr_;
        }

        T *operator->() const {
            return ptr_;
        }

        void swap(shared_ptr &x) noexcept {
            std::swap(*this, x);
        }

        void reset(T *ptr = 0) {
            shared_ptr<T>(ptr).swap(*this);
        }

    };

    template<class F, class S>
    bool operator==(const shared_ptr<F> &left, const shared_ptr<S> &right) {
        return left.get() == right.get();
    }
}