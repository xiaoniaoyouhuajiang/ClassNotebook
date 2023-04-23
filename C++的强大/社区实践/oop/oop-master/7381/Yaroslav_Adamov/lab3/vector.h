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
        
    
        // Constructors and destructor
        
        explicit vector(size_t count = 0)
        : m_first(count ? new value_type[count] : nullptr), m_last(count ? m_first + count : nullptr) {
        }

        template <typename InputIterator>
        vector(InputIterator first, InputIterator last) : vector(last - first) {
            for(int i = 0; i < last - first; i++)
                m_first[i] = (value_type)first[i];
        }

        vector(std::initializer_list<Type> init) : vector(init.begin(), init.end()) {
        }

        vector(const vector& other) : vector(other.m_first, other.m_last) {
        }

        vector(vector&& other) : vector() {
            swap(*this, other);
        }

        ~vector() {
            delete[] m_first;
        }



        // Methods and operators
        
        vector& operator=(const vector& other) {
            if (this != &other) {
                vector temp(other);
                swap(*this, temp);
            }
            return *this;
        }

        vector& operator=(vector&& other) {
            if (this != &other)
                swap(*this, other);
            return *this;
        }

        template <typename InputIterator>
        void assign(InputIterator first, InputIterator last) {
            delete[] m_first;
            m_first = last - first ? new value_type[last - first] : nullptr;
            m_last = last - first ? m_first + (last - first) : nullptr;
            for (int i = 0; i < last - first; i++)
                m_first[i] = (value_type)first[i];
        }

        void resize(size_t count) {
            if (m_last - m_first != count) {
                vector temp(count);
                std::copy(m_first, m_last - m_first > count ? m_first + count : m_last, temp.m_first);
                swap(*this, temp);
            }
        }
      
        iterator erase(const_iterator pos) {
            size_t offset = pos - m_first;
            std::rotate( m_first+offset, m_first+offset+1, m_last);
            resize(size()-1);
            return m_first + offset;
        }

        iterator erase(const_iterator first, const_iterator last) {
	    if (first < m_first || last > m_last)
                throw std::out_of_range("out of range");
            size_t f = first - m_first;
	    size_t l = last - m_first;
	    std::rotate(m_first + f, m_first + l, m_last);
	    resize(size() - l + f);
	    return m_first + f;
        }

        iterator insert(const_iterator pos, const Type& value) {
            size_t offset = pos - m_first;
            resize(size()+1);
            *(m_last-1) = value;
            std::rotate(m_first+offset, m_last-1, m_last);
            return m_first + offset;
        }

        template <typename InputIterator>
        iterator insert(const_iterator pos, InputIterator first, InputIterator last) {
            size_t offset = pos - m_first;
            resize( size() + (last-first));
            std::copy(first, last, m_last - (last-first));
            std::rotate(m_first+offset, m_last - (last-first) , m_last);
            return m_first + offset;
        }

        void push_back(const value_type& value) {
            resize(size()+1);
            *(m_last-1) = value;
        }

        reference at(size_t pos) {
            return checkIndexAndGet(pos);
        }

        const_reference at(size_t pos) const {
            return checkIndexAndGet(pos);
        }

        reference operator[](size_t pos) {
            return m_first[pos];
        }

        const_reference operator[](size_t pos) const {
            return m_first[pos];
        }

        iterator begin() {
            return m_first;
        }

        const_iterator begin() const {
            return m_first;
        }

        iterator end() {
            return m_last;
        }

        const_iterator end() const {
            return m_last;
        }

        size_t size() const {
            return m_last - m_first;
        }

        bool empty() const {
            return m_first == m_last;
        }



    private:   
        reference checkIndexAndGet(size_t pos) const {
            if (pos >= size())
                throw std::out_of_range("out of range");
            return m_first[pos];
        }

        void swap(vector& v1, vector& v2) {
			std::swap(v1.m_first, v2.m_first);
			std::swap(v1.m_last, v2.m_last);
		}


    private:
        iterator m_first;
        iterator m_last;
    };
}
