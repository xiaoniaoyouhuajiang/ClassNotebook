#ifndef LAB_OOP_2_SHARED_PTR_H
#define LAB_OOP_2_SHARED_PTR_H

#include <cstddef>
#include <typeinfo>
#include <functional>

namespace custom {
    template<typename T>
    class shared_ptr {
    public:
        explicit shared_ptr(T* ptr = 0) : m_elem(ptr), m_elem_count(ptr ? new long(1) : nullptr) {}

        ~shared_ptr() {
            free();
        }

        shared_ptr(const shared_ptr& other) {
            m_elem = other.m_elem;
            m_elem_count = other.m_elem_count;
            if(m_elem_count != nullptr) {
                ++(*m_elem_count);
            }
        }

        template<typename Y>
        shared_ptr(shared_ptr<Y>& other) {
            m_elem = dynamic_cast<T*>(other.get());
            m_elem_count = other.count_ptr();
            if(m_elem_count != nullptr) {
                (*m_elem_count)++;
            }
        }

        shared_ptr& operator=(const shared_ptr& other) {
            if(this != &other) {
                free();
                m_elem = other.m_elem;
                m_elem_count = other.m_elem_count;
                if(m_elem_count != nullptr) {
                    (*m_elem_count)++;
                }
            }
            return *this;
        }

        template<typename Y>
        shared_ptr& operator=(shared_ptr<Y>& other) {
            free();
            m_elem = dynamic_cast<T*>(other.get());
            m_elem_count = other.count_ptr();
            if(m_elem_count != nullptr) {
                (*m_elem_count)++;
            }
            return *this;
        }

        explicit operator bool() const {
            return m_elem != nullptr;
        }

        T* get() const {
            return m_elem;
        }

        long use_count() const {
            return m_elem_count != nullptr ? (*m_elem_count) : 0;
        }

        long* count_ptr() const {
            return m_elem_count;
        }

        T& operator*() const {
            return (*m_elem);
        }

        T* operator->() const {
            return m_elem;
        }

        void swap(shared_ptr& x) noexcept {
            T* temp = m_elem;
            long* temp_size = m_elem_count;
            m_elem = x.m_elem;
            m_elem_count = x.m_elem_count;
            x.m_elem = temp;
            x.m_elem_count = temp_size;
        }

        void reset(T* ptr = 0) {
            free();
            m_elem = ptr;
            m_elem_count = ptr ? new long(1) : nullptr;
        }

    private:
        void free() {
            if(m_elem_count != nullptr && --(*m_elem_count) == 0) {
                delete m_elem;
                delete m_elem_count;
            }
        }

        long* m_elem_count;
        T* m_elem;
    };

//from cppreference
//(1)
    template<class T, class U>
    bool operator==(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) {
        return lhs.get() == rhs.get();
    }

//(2)
    template<class T, class U>
    bool operator!=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) {
        return !(lhs == rhs);
    }

//(3)
    template<class T, class U>
    bool operator<(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) {
        return std::less<T*>()(lhs.get(), rhs.get());
    }

//(4)
    template<class T, class U>
    bool operator>(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) {
        return !(rhs < lhs);
    }

//(5)
    template<class T, class U>
    bool operator<=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) {
        return !(lhs < rhs);
    }

//(6)
    template<class T, class U>
    bool operator>=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) {
        return !lhs;
    }

//(7)
    template<class T>
    bool operator==(const shared_ptr<T>& lhs, std::nullptr_t rhs) {
        return !rhs;
    }

//(8)
    template<class T>
    bool operator==(std::nullptr_t lhs, const shared_ptr<T>& rhs) {
        return (bool) lhs;
    }

//(9)
    template<class T>
    bool operator!=(const shared_ptr<T>& lhs, std::nullptr_t rhs) {
        return lhs.get() != rhs;
    }

//(10)
    template<class T>
    bool operator!=(std::nullptr_t lhs, const shared_ptr<T>& rhs) {
        return (bool) rhs;
    }

//(11)
    template<class T>
    bool operator<(const shared_ptr<T>& lhs, std::nullptr_t rhs) {
        return std::less<T*>()(lhs.get(), nullptr);
    }

//(12)
    template<class T>
    bool operator<(std::nullptr_t lhs, const shared_ptr<T>& rhs) {
        return std::less<T*>()(nullptr, rhs.get());
    }

//(13)
    template<class T>
    bool operator<=(const shared_ptr<T>& lhs, std::nullptr_t rhs) {
        return nullptr < lhs;
    }

//(14)
    template<class T>
    bool operator<=(std::nullptr_t lhs, const shared_ptr<T>& rhs) {
        return rhs < nullptr;
    }

//(15)
    template<class T>
    bool operator>(const shared_ptr<T>& lhs, std::nullptr_t rhs) {
        return !(nullptr < lhs);
    }

//(16)
    template<class T>
    bool operator>(std::nullptr_t lhs, const shared_ptr<T>& rhs) {
        return !(rhs < nullptr);
    }

//(17)
    template<class T>
    bool operator>=(const shared_ptr<T>& lhs, std::nullptr_t rhs) {
        return !(lhs < nullptr);
    }

//(18)
    template<class T>
    bool operator>=(std::nullptr_t lhs, const shared_ptr<T>& rhs) {
        return !(nullptr < rhs);
    }

}

#endif //LAB_OOP_2_SHARED_PTR_H
