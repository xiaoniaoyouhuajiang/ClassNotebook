#include <iostream>
#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

namespace stepik
{
    template <typename Type>
    class vector
    {
    public:
        typedef Type* iterator;
        typedef const Type* const_iterator;

        typedef Type value_type;

        typedef value_type& reference;
        typedef const value_type& const_reference;

        typedef std::ptrdiff_t difference_type;

        explicit vector(size_t count = 0)
        {
            m_first = new Type[count];
            m_last = &(m_first[count]);
            for (int i = 0; i < count; i++)
            {
                m_first[i] = 0;
            }

        }

        template <typename InputIterator>
        vector(InputIterator first, InputIterator last) :
        vector(last - first)
        {

            std::copy(first, last, m_first);
        }

        vector(std::initializer_list<Type> init) :
        vector(init.begin(), init.end()) {}

        vector(const vector& other)
        {
            m_first = new Type[other.size()];
            m_last = &(m_first[other.size()]);
            std::copy(other.m_first, other.m_last, m_first);
        }

        vector(vector&& other)
        {
            m_first = other.m_first;
            m_last = other.m_last;
            other.m_first = nullptr;
            other.m_last = nullptr;
        }

        ~vector()
        {
            delete[] m_first;
        }
        vector& operator=(const vector& other)
        {
            if (this != &other)
                vector(other).swap(*this);
            return *this;
        }
        vector& operator=(vector&& other)
        {
            if (this != &other)
                swap(other);
            return *this;
        }

        template <typename InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            vector<Type>(first, last).swap(*this);
        }


        void resize(size_t count)
        {
            vector bufferVector(count);
            if (count > size())
            {
                std::move(m_first, m_last, bufferVector.m_first);
            }
            else
            {
                std::move(m_first,  m_first + count, bufferVector.m_first);
            }
            swap(bufferVector);
        }


        iterator erase(const_iterator pos)
        {
            size_t newPos = pos - m_first;
            std::rotate(const_cast<iterator>(pos), const_cast<iterator>(pos) + 1, m_last);
            resize(size() - 1);
            return m_first + newPos;
        }
        iterator erase(const_iterator first, const_iterator last)
        {
            size_t newPos = last - first;
            iterator newFirst = const_cast<iterator>(first);
            while (newPos != 0)
            {
                newFirst = erase(newFirst);
                newPos--;
            }
            return newFirst;
        }

        iterator insert(const_iterator pos, const Type& value)
        {
            size_t insertSize = pos - m_first;
            resize(size() + 1);
            iterator newPos = m_first + insertSize;
            std::rotate(newPos, m_last - 1, m_last);
            m_first[newPos - m_first] = value;
            return newPos;
        }

        template <typename InputIterator>
        iterator insert(const_iterator pos, InputIterator first, InputIterator last)
        {
            int insertSize = last - first;
            iterator newPos = const_cast<iterator>(pos);
            while (insertSize != 0)
            {
                insertSize--;
                newPos = insert(newPos, *(first + insertSize));
            }
            return newPos;
        }

        void push_back(const value_type& value)
        {
            insert(m_last, value);
        }

        reference at(size_t pos)
        {
            return checkIndexAndGet(pos);
        }

        const_reference at(size_t pos) const
        {
            return checkIndexAndGet(pos);
        }

        reference operator[](size_t pos)
        {
            return m_first[pos];
        }

        const_reference operator[](size_t pos) const
        {
            return m_first[pos];
        }

        iterator begin()
        {
            return m_first;
        }

        const_iterator begin() const
        {
            return m_first;
        }

        iterator end()
        {
            return m_last;
        }

        const_iterator end() const
        {
            return m_last;
        }

        size_t size() const
        {
            return m_last - m_first;
        }

        bool empty() const
        {
            return m_first == m_last;
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

        void swap(vector & other)
        {
            std::swap(this->m_first, other.m_first);
            std::swap(this->m_last, other.m_last);
        }
    private:
        iterator m_first;
        iterator m_last;
    };
}

int main() {

	stepik::vector<int> Vec = {11,23,44,12,1};
	std::cout << "Vector:" << std::endl;
	for(int i = 0; i<Vec.size(); i++) std::cout << Vec[i] << " ";
	std::cout << std::endl;

	std::cout << "Copy:" << std::endl;
	stepik::vector<int> newVec (Vec.begin(), Vec.end());
	for(int i = 0; i<newVec.size(); i++) std::cout << newVec[i] << " ";
	std::cout << std::endl;

	std::cout << "Resize:" << std::endl;
	newVec.resize(7);
	newVec[5]=23; newVec[6]=213;
	for(int i = 0; i<newVec.size(); i++) std::cout << newVec[i] << " ";
	std::cout << std::endl;

	std::cout << "Erase:" << std::endl;
	newVec.erase(newVec.begin()+2, newVec.begin()+4);
	for(int i = 0; i<newVec.size(); i++) std::cout << newVec[i] << " ";
	std::cout << std::endl;

	std::cout << "Insert:" << std::endl;
	newVec.insert(newVec.begin()+4, 1234);
	for(int i = 0; i<newVec.size(); i++) std::cout << newVec[i] << " ";
	std::cout << std::endl;

	std::cout << "Push back:" << std::endl;
	newVec.push_back(67);
	for(int i = 0; i<newVec.size(); i++) std::cout << newVec[i] << " ";
	std::cout << std::endl;

	return 0;
}
