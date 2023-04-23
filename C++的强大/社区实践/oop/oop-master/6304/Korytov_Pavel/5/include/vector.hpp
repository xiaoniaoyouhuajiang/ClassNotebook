#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <iterator>


#ifdef TEST
using std::cout;
using std::endl;
#endif //TEST

using namespace std;
namespace stepik
{
#include <stdexcept>
    template <typename Type>
    class vector
    {
    public:
        typedef Type* iterator;
        typedef const Type* const_iterator;

        typedef Type value_type;

        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef ptrdiff_t difference_type;

        void Debug (const char* str){
#ifdef TEST
            cout << str << endl;
#endif

        }

        explicit vector(size_t count = 0) //Инициализация с числом
        {
        Debug("Initializing with number");
            if (count) {
                m_first = new Type[count];
                m_last = m_first + count;
            }
            else {
                m_first = nullptr;
                m_last = nullptr;
            }
        }

        template <typename InputIterator>
        vector(InputIterator first, InputIterator last) //Инициализация с содержимым диапазона [first, last)
        {
        Debug("Initializing with iterator");
            size_t count = last - first;
            if (count) {
                m_first = new Type[count];
				m_last = m_first + count;
                std::copy(first, last, m_first);
            }
            else {
                m_first = nullptr;
                m_last = nullptr;
            }
        }

        vector(std::initializer_list<Type> init) : vector (init.begin(), init.end()) //Инициализация с помощью списка инициализации
        {
            Debug("Initializing with initializer list");
        }

        vector(const vector& other) : vector (other.begin(), other.end())//Копирование
        {
            Debug("Copy constructor");
        }

        void swap(vector& first, vector& second)
        {
            Debug("Swapping");
            using std::swap;
            swap(first.m_first, second.m_first);
            swap(first.m_last, second.m_last);
        }

        vector(vector&& other) : vector()
        {
            Debug("Moving constructor");
            swap(*this, other);
        }
        ~vector()
        {
            Debug("Destroying");
            if (!empty()) {
                delete[] m_first;
                m_first = nullptr;
                m_last = nullptr;
            }
        }
        //assignment operators
        vector& operator=(const vector& other)
        {
            Debug("Assignment copy operator");
            size_t new_size = other.size();
            if (!empty()){
                delete[] m_first;
            }
            m_first = new Type[new_size];
            m_last = m_first + new_size;
            std::copy(other.begin(), other.end(), m_first);
            return *this;
        }

        vector& operator=(vector&& other)
        {
            Debug("Assignment moving operator");
            swap(*this, other);
        }

        // assign method
        template <typename InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            Debug ("Assing method");
            vector temp(first, last);
            swap(*this, temp);
        }

        // resize methods
        void resize(size_t count)
        {
            Debug("Resize");
            vector temp(*this);
            if (!empty())
                delete[] m_first;
            m_first = new Type[count];
            m_last = m_first + count;
            count = temp.size() < count ? temp.size() : count;
            for (size_t i = 0; i < count; i++){
                m_first[i] = temp.m_first[i];
            }
        }

        //erase methods
        iterator erase(const_iterator pos)
        {
            Debug("Erase one");
            checkIterator(pos);
            size_t keep = pos - m_first;
            std::rotate(m_first + keep, m_first+keep + 1, m_last);
            resize(size() - 1);
            return m_first + keep;
        }

        iterator erase(const_iterator first, const_iterator last)
        {
            Debug("Erase [first, last)");
            checkIterator(first); checkIterator(last);
            size_t keep = first - m_first;
            size_t lenght = last - first;
            std::rotate(m_first + keep, m_first + keep + lenght, m_last);
            resize(size() - lenght);
            return m_first + keep;
        }


        void out(){
            if (empty()){
                Debug("Container has been deleted");
                return;
            }
            for (size_t i = 0; i < size(); i++){
                std::cout << this->operator [](i) << " ";
            }
            std::cout << std::endl;
        }

		//insert methods
		iterator insert(const_iterator pos, const Type& value)
		{
			Debug("Inserting one element");
			checkIterator(pos);
            size_t keep = (size() == 0) ? 0 : pos - m_first;
			resize(size() + 1);
			m_first[size() - 1] = value;
            std::rotate(m_first + keep, m_first + size() - 1, m_last);
			return m_first + keep;
		}

        template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{
            Debug("Inserting many elements");
            checkIterator(pos);
            size_t insize = last - first;
            size_t keep = pos - m_first;
			size_t oldsize = size();
			resize(size() + insize);
            std::copy(first, last, m_first + oldsize);
            std::rotate(m_first + keep, m_first + oldsize, m_last);
            return m_first + keep;
		}

		//push_back methods
		void push_back(const value_type& value)
		{
            Debug("Inserting element back");
            insert(m_last, value);
		}

        //at methods
        reference at(size_t pos)
        {
            return checkIndexAndGet(pos);
        }

        const_reference at(size_t pos) const
        {
            return checkIndexAndGet(pos);
        }

        //[] operators
        reference operator[](size_t pos)
        {
            return m_first[pos];
        }

        const_reference operator[](size_t pos) const
        {
            return m_first[pos];
        }

        //*begin methods
        iterator begin()
        {
            return m_first;
        }

        const_iterator begin() const
        {
            return m_first;
        }

        //*end methods
        iterator end()
        {
            return m_last;
        }

        const_iterator end() const
        {
            return m_last;
        }

        //size method
        size_t size() const
        {
            return m_last - m_first;
        }

        //empty method
        bool empty() const
        {
            return m_first == m_last;
        }

        void fill(Type T) {
            for (size_t i = 0; i < size(); i++) {
                this->operator[](i) = T;
            }
        }

    private:
        reference checkIndexAndGet(size_t pos) const
        {
            if (pos >= size())
            {
                throw std::out_of_range("out of range");
            }

            return m_first[pos];
        }

        //your private functions
        void checkIterator(const_iterator pos){
            if ((pos < m_first) || (pos > m_last)){
                throw std::out_of_range("out of range");
            }
        }
    private:
        iterator m_first;
        iterator m_last;
    };
}// namespace stepik
#endif
