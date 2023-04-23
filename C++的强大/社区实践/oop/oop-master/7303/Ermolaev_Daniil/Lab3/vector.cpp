#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

namespace stepik {
    template <typename Type>
    class vector {
        public:
            typedef Type* iterator;
            typedef const Type* const_iterator;

            typedef Type value_type;

            typedef value_type& reference;
            typedef const value_type& const_reference;

            typedef std::ptrdiff_t difference_type;

            explicit vector(size_t count = 0) {
                m_first = new Type[count];
                m_last = m_first + count;
            }

            template <typename InputIterator>
            vector(InputIterator first, InputIterator last) {
                size_t vectorSize;
                vectorSize = last - first;
                m_first = new Type[vectorSize];
                m_last = m_first + vectorSize;
                std::copy(first, last, m_first);
            }

            vector(std::initializer_list <Type> init) : vector(init.begin(), init.end()) {}

            vector(const vector& other) : vector(other.begin(), other.end()) {}

            vector(vector&& other) noexcept {
                m_first = other.m_first;
                m_last = other.m_last;
                other.m_first = nullptr;
                other.m_last = nullptr;
            }

            ~vector() {
                delete[] m_first;
            }

            //assignment operators
            vector& operator=(const vector& other) {
                if(this != &other) {
                    delete[] m_first;
                    size_t vectorSize = other.m_last - other.m_first;
                    m_first = new Type[vectorSize];
                    m_last = m_first + vectorSize;
                    std::copy(other.m_first, other.m_last, m_first);
                    return *this;
                }
            }

            vector& operator=(vector&& other) noexcept {
                if (this != &other) {
                    delete[] m_first;
                    m_first = other.m_first;
                    m_last = other.m_last;
                    other.m_first = nullptr;
                    other.m_last = nullptr;
                    return *this;
                }
            }

            // assign method
            template <typename InputIterator>
            void assign(InputIterator first, InputIterator last) {
                *this = std::move(vector(first, last));
            }

            void resize(size_t count) {
                iterator end = (count > size()) ? m_last : m_first + count;
                vector tempVector(count);
                std::move(m_first, end, tempVector.m_first);
                std::swap(m_first, tempVector.m_first);
                std::swap(m_last, tempVector.m_last);
            }

            //erase methods
            iterator erase(const_iterator pos) {
                size_t posNum = pos - m_first;
                std::rotate(const_cast<iterator>(pos), const_cast<iterator>(pos) + 1, m_last);
                resize(size() - 1);
                return m_first + posNum;
            }

            iterator erase(const_iterator first, const_iterator last) {
                iterator it = const_cast<iterator>(first);

                for(size_t i = 0, count = last - first; i < count; ++i) {
                    it = erase(it);
                }

                return it;
            }

            iterator insert(const_iterator pos, const Type& value) {
                vector tempVector(size() + 1);
                size_t diff = pos - m_first;
                std::copy(m_first, m_first + diff, tempVector.m_first);
                *(tempVector.begin() + diff) = value;
                std::copy(m_first + diff, m_last, tempVector.begin() + diff + 1);
                *this = std::move(tempVector);
                return m_first + diff;
            }

            template <typename InputIterator>
            iterator insert(const_iterator pos, InputIterator first, InputIterator last) {
                vector tempVector(size() + (last - first));
                size_t diff = pos - m_first;
                std::copy(m_first, m_first + diff, tempVector.m_first);
                std::copy(first, last, tempVector.begin() + diff);
                std::copy(m_first + diff, m_last, tempVector.begin() + diff + (last - first));
                *this = std::move(tempVector);
                return m_first + diff;
            }

            void push_back(const value_type& value) {
                insert(this->end(), value);
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
                if (pos >= size()) {
                    throw std::out_of_range("Index out of range");
                }

                return m_first[pos];
            }

        private:
            iterator m_first;
            iterator m_last;
    };
}// namespace stepik
