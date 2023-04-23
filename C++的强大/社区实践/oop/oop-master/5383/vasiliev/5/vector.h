#ifndef ETUOOP_VECTOR_H
#define ETUOOP_VECTOR_H

#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>

namespace etuoop
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
        m_first = (count ? new value_type[count] : nullptr);
        m_last = m_first + count;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last) : vector((size_t)(last-first))
    {
        try {
            std::copy(first, last, m_first);
        } catch (...) {
            delete[] m_first;
            throw;
        }
    }

    vector(std::initializer_list<Type> init) : vector((size_t)(init.end()-init.begin()))
    {
        std::move(init.begin(), init.end(), m_first);
    }

    vector(const vector& other) : vector(other.begin(),other.end())
    {
    }

    vector(vector&& other)
    {
        m_first = other.m_first;
        m_last = other.m_last;
        other.m_first = other.m_last = nullptr;
    }

    ~vector()
    {
        delete[] m_first;
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
        return *this = std::move(vector<Type>(other));
    }

    vector& operator=(vector&& other)
    {
        delete[] m_first;
        m_first = other.m_first;
        m_last = other.m_last;
        other.m_first = other.m_last = nullptr;
        return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        *this = std::move(vector<Type>(first, last));
    }

    // resize methods
    void resize(size_t count)
    {
        iterator end = (count > size() ? m_last : m_first+count);
        vector tmp(count);
        std::move(m_first, end, tmp.m_first);
        *this = std::move(tmp);
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
        return erase(pos, pos+1);
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        size_t part = first-m_first;
        std::move((iterator)last, m_last, (iterator)first);
        resize(size()-(last-first));
        return m_first + part;
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
        return insert(pos, &value, &value+1);
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        size_t part = pos-m_first;
        resize(size()+(last-first));
        std::move_backward(m_first+part, m_last-(last-first), m_last);
        std::copy(first, last, m_first+part);
        return m_first + part;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
        insert((const_iterator)m_last, value);
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
}// namespace etuoop

#endif
