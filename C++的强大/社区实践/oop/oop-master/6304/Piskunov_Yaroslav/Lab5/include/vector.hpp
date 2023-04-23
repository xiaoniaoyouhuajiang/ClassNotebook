#ifndef VECTOR_H
#define VECTOR_H

#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
#include <cstring>

#endif // VECTOR_H

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

    void out(){
        if (empty())
        {
            return;
        }
        for (size_t i = 0; i < size(); i++){
            std::cout << this->operator [](i) << " ";
        }
        std::cout << std::endl;
    }

    explicit vector(size_t count = 0)
    {
        if (count)
        {
            m_first = new Type[count];
            m_last = m_first + count;
        }
        else
        {
            m_first = NULL;
            m_last = NULL;
        }
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
        int length = last - first;
        m_first = new Type[length];
        m_last = m_first + length;
        for (int i=0; i<length; first++)
            m_first[i++] = *first;
    }

    vector(std::initializer_list<Type> init)
    {
        m_first = new Type[init.size()];
        m_last = m_first + init.size();
        int i = 0;
        for (auto current: init)
            m_first[i++] = current;
    }

    vector(const vector& other)
    {
        m_first = new Type[other.size()];
        m_last = m_first + other.size();
        for (size_t i=0; i<other.size(); i++)
            m_first[i] = other[i];
    }

    void swap(vector& first, vector& second)
    {
        std::swap(first.m_first, second.m_first);
        std::swap(first.m_last, second.m_last);
    }

    vector(vector&& other): vector()
    {
        swap(*this, other);
    }

    ~vector()
    {
        delete[] m_first;
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
        int newSize = size() + 1;
        iterator temp = new Type[newSize];
        int newNumber = pos - m_first;
        iterator newPos = &m_first[newNumber];
        iterator element = std::copy(m_first, newPos, temp);
        std::copy(newPos, m_last, element+1);
        *(element) = value;
        delete[] m_first;
        m_first = new Type[newSize];
        m_last = m_first + newSize;
        std::copy(temp, temp+newSize, m_first);
        delete[] temp;

        return &m_first[newNumber];

    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        vector temp(size()+(last-first));
        size_t newElSize = pos - begin();

        std::copy(const_iterator(begin()), pos, temp.begin());
        std::copy(first, last, temp.begin()+newElSize);

        if (pos+1 < end())
            std::copy(pos, const_iterator(end()), temp.begin()+newElSize+(last-first));
        temp.swap(temp, *this);
        return begin()+newElSize;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
        vector<Type> temp = *this;
        delete[] m_first;
        m_first = new Type[temp.size()+1];
        m_last = m_first + temp.size() + 1;
        std::copy(temp.begin(), temp.end(), m_first);
        m_first[temp.size()] = value;
    }

    // resize methods
    void resize(size_t count)
    {
        vector temp (*this);
        delete[] m_first;
        m_first = new Type[count];
        m_last = m_first + count;

        if (count > temp.size())
            count = temp.size();

        for (size_t i=0; i<count; i++)
            m_first[i] = temp.m_first[i];
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
        int number = pos - m_first;
        iterator removePos = &m_first[number];
        int ammount = m_last - removePos - 1;
        std::memmove (removePos, removePos+1, (ammount*sizeof(Type)));
        m_last--;
        return removePos;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        int firstNumber = first - m_first;
        iterator firstPos = &m_first[firstNumber];
        int lastNumber = last - m_first;
        iterator lastPos = &m_first[lastNumber];
        std::memmove (firstPos, last, ((m_last - lastPos)*sizeof(Type)));
        m_last = m_last - (last - first);
        return firstPos;
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
        delete[] m_first;
        int length = other.m_last - other.m_first;
        m_first = new Type[length];
        m_last = m_first + length;
        for (int i=0; i<length; i++)
            m_first[i] = other.m_first[i];
    }

    vector& operator=(vector&& other)
    {
        swap (*this, other);
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        delete[] m_first;
        int length = last - first;
        m_first = new Type[length];
        m_last = m_first + length;
        for (int i=0; i<length; first++)
            m_first[i++] = *first;
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

private:
    iterator m_first;
    iterator m_last;
};

}// namespace stepik
