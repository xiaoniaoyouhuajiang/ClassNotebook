#ifndef LAB_OOP_2_VECTOR_H
#define LAB_OOP_2_VECTOR_H

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace custom {
    template<typename Type>
    class vector {
    public:
        typedef Type* iterator;
        typedef const Type* const_iterator;

        typedef Type value_type;

        typedef value_type& reference;
        typedef const value_type& const_reference;

        typedef std::ptrdiff_t difference_type;


        explicit vector(size_t count = 0)
                : m_first(count ? new value_type[count]() : nullptr), m_last(count ? &m_first[count] : nullptr) {
//            for(size_t i = 0; i < count; i++) {
//                m_first[i] = 0;
//            }
        }

        template<typename InputIterator>
        vector(InputIterator first, InputIterator last) {
            difference_type arr_size = last - first;
            m_first = new value_type[arr_size];
            m_last = &m_first[arr_size];
            std::copy(first, last, m_first);
        }

        vector(std::initializer_list<Type> init)
                : m_first(init.size() ? new value_type[init.size()] : nullptr),
                  m_last(init.size() ? &m_first[init.size()] : m_first) {
            std::copy(init.begin(), init.end(), m_first);
        }

        vector(const vector& other)
                : m_first(other.size() ? new value_type[other.size()] : nullptr),
                  m_last(other.size() ? &m_first[other.size()] : nullptr) {
            std::copy(other.begin(), other.end(), m_first);
        }

        vector(vector&& other)
                : m_first(other.m_first), m_last(other.m_last) {
            other.m_first = nullptr;
            other.m_last = nullptr;
        }

        ~vector() {
            //delete[] m_first;
        }

        //insert methods
        iterator insert(const_iterator pos, const Type& value) {
            difference_type diff = pos - m_first;
            push_back(value);
            std::rotate(m_first + diff, m_last - 1, m_last);

            return &m_first[diff];
        }

        template<typename InputIterator>
        iterator insert(const_iterator pos, InputIterator first, InputIterator last) {
            difference_type keep_size = this->size();
            difference_type diff = pos - m_first;
            difference_type insert_size = last - first;
            this->resize(keep_size + insert_size);
            std::copy(first, last, m_first + keep_size);
            std::rotate(m_first + diff, m_last - (last - first), m_last);
            return &m_first[diff];
        }

        //push_back methods
        void push_back(const value_type& value) {
            this->resize(this->size() + 1);
            m_first[size() - 1] = value;
        }

        // resize methods
        void resize(size_t count) {
            iterator temp = new value_type[count];
            std::copy(m_first, (this->size() > count) ? &m_first[count] : m_last, temp);

            //delete[] m_first;

            m_first = temp;
            m_last = &m_first[count];
        }

        //erase methods
        iterator erase(const_iterator pos) {
            difference_type diff = pos - m_first;
            std::rotate(m_first + diff, m_first + diff + 1, m_last);
            this->resize(m_last - m_first - 1);
            return &m_first[diff];
        }

        iterator erase(const_iterator first, const_iterator last) {
            difference_type diff = first - m_first;
            difference_type length = last - first;
            std::rotate(m_first + diff, m_first + diff + length, m_last);
            this->resize(m_last - m_first - length);
            return &m_first[diff];
        }


        //assignment operators
        vector& operator=(const vector& other) {
            iterator keep_first = m_first;
            iterator keep_last = m_last;
            vector* new_vector = new vector(other);
            m_first = new_vector->m_first;
            m_last = new_vector->m_last;
            delete[] keep_first;

            return *this;
        }

        vector& operator=(vector&& other) {
            delete[] m_first;
            m_first = other.m_first;
            m_last = other.m_last;
            other.m_first = nullptr;
            other.m_last = nullptr;

            return *this;
        }

        // assign method
        template<typename InputIterator>
        void assign(InputIterator first, InputIterator last) {
            delete[] m_first;
            m_first = nullptr;
            m_last = nullptr;

            difference_type arr_size = last - first;

            m_first = new value_type[arr_size];
            m_last = &m_first[arr_size];
            std::copy(first, last, m_first);
        }

        //at methods
        reference at(size_t pos) {
            return checkIndexAndGet(pos);
        }

        const_reference at(size_t pos) const {
            return checkIndexAndGet(pos);
        }

        //[] operators
        reference operator[](size_t pos) {
            return m_first[pos];
        }

        const_reference operator[](size_t pos) const {
            return m_first[pos];
        }

        //*begin methods
        iterator begin() {
            return m_first;
        }

        const_iterator begin() const {
            return m_first;
        }

        //*end methods
        iterator end() {
            return m_last;
        }

        const_iterator end() const {
            return m_last;
        }

        //size method
        size_t size() const {
            return m_last - m_first;
        }

        //empty method
        bool empty() const {
            return m_first == m_last;
        }

    private:
        reference checkIndexAndGet(size_t pos) const {
            if(pos >= size()) {
                throw std::out_of_range("out of range");
            }

            return m_first[pos];
        }

        //your private functions

    private:
        iterator m_first;
        iterator m_last;
    };
}

#endif //LAB_OOP_2_VECTOR_H
