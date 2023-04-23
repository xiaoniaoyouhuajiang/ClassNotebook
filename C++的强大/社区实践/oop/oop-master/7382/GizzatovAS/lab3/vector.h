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
        if(count) {
            m_first = new value_type[count];
        }
        else {
            m_first = nullptr;
        }
        if(m_first) {
            m_last=m_first+count;
        }
        else {
            m_last = nullptr;
        }
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last):vector(last - first)
    {
        if(last - first) {
            std::copy(first,last,m_first);
        }
    }

    vector(std::initializer_list<Type> init):vector(init.begin(),init.end())
    {
        // implement this
    }

    vector(const vector& other):vector(other.begin(),other.end())
    {
        // implement this
    }

    vector(vector&& other)
    {
        m_first = other.begin();
        m_last = other.end();
        other.m_first = other.m_last = nullptr;
    }

    ~vector()
    {
        delete[] m_first;
        m_last = m_first = nullptr;
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
        assign(other.m_first,other.m_last);
    }

    vector& operator=(vector&& other)
    {
        if(m_first) {
            delete[] m_first;
        }
        m_first = other.m_first;
        m_last = other.m_last;
        other.m_first = nullptr;
        other.m_last = nullptr;
        return (*this);
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        vector a(first,last);
        (*this) = std::move(a);
    }

    void resize(size_t count)
    {
        int new_size = size();
        if(count != new_size) {
            if(count < new_size) {
                m_last = m_first+count;
            }
            else {
                vector a(count);
                std::copy(m_first,m_last,a.m_first);
                (*this) = std::move(a);
            }
        }
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
        iterator el = m_first + (pos - m_first);
        std::rotate(el,el+1,m_last);
        m_last--;
        return el;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        iterator start =  m_first + (first - m_first);
        iterator end =  m_first + (last - m_first);
        std::rotate(start,end,m_last);
        m_last -= (end - start);
        return start;
    }
    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
        size_t insert_index = pos - m_first;
        resize(size()+1);
        m_first[size()-1] = value;
        std::rotate((iterator)(m_first + insert_index),m_last,m_last);
        return (iterator)(m_first + insert_index);
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        size_t insert_index = pos - m_first;
        size_t old_size = size();
        resize(old_size + last - first);
        std::copy(first, last, m_first+ old_size);
        std::rotate((iterator)(insert_index+m_first),(iterator)(m_first + old_size),m_last);
        return insert_index+m_first;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
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

