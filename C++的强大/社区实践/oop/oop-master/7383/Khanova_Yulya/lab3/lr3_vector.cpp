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

    explicit vector(size_t count = 0): m_first(count ? new value_type[count] : nullptr) ,m_last(m_first + count)
    {

    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
        difference_type size = last - first;
        if(size<=0) {
            m_last = nullptr;
            m_first = nullptr;
            return;
        }
        m_first = new value_type[size];
        for (size_t i = 0; i < size; i++)
            m_first[i] = *first++;
        m_last = m_first + size;

    }

    vector(std::initializer_list<Type> init)    {

        if(!init.size()) {
            m_last = nullptr;
            m_first = nullptr;
            return;
        }
        m_first = new value_type[init.size()];

        std::copy(init.begin(), init.end(), m_first);
        m_last = m_first + init.size();

    }


    vector(const vector& other)
    {
        if(other.size()==0) {
            m_last = nullptr;
            m_first = nullptr;
            return;
        }

        m_first = new value_type[other.size()];
        for (size_t i = 0; i < other.size(); i++)
            m_first[i] = other.m_first[i];
        m_last = m_first + other.size();

    }

    vector(vector&& other)
    {
        m_first = other.begin();
        m_last = other.end();

        other.m_first = nullptr;
        other.m_last = nullptr;

    }

    ~vector()
    {
        if(!empty())
            delete[] m_first;

    }

    void resize(size_t count)              //изменение размера вектора
    {
        if(count == m_last - m_first)
            return;
        size_t size = m_last - m_first;
        value_type new_first[size];
        std::copy(m_first, m_last, new_first);
        delete [] m_first;
        m_first = new value_type[count];
        m_last = m_first + count;
        if(count > size) {
            std::copy(new_first, new_first + size, m_first);
        } else {
            std::copy(new_first, new_first + count, m_first);
        }
    }

    iterator erase(const_iterator pos)                        //удаление элемента
    {
        size_t size = m_last - m_first;
        size_t index = pos - m_first;
        for(size_t i = index; i < size - 1; i++) {
            m_first[i] = m_first[i + 1];
        }
        m_last = m_first + size - 1;
        resize(size - 1);
        return m_first + index;
    }

    iterator erase(const_iterator first, const_iterator last)        //удаление элементов в интрвале
    {
        size_t size = m_last - m_first;
        size_t size_ = last - first;
        size_t index = first - m_first;

        for(size_t i = index; i < size - size_; i++) {
            m_first[i] = m_first[i + size_];
        }
        resize(size - size_);
        return m_first + index;
    }


    iterator insert(const_iterator pos, const Type& value)              //вставка элемента
    {
        size_t size = m_last - m_first;
        size_t index = pos - m_first;
        resize(size+1);
        *(m_last-1)=value;
        std::rotate(m_first+index, m_last-1, m_last);
        return m_first+index;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)    //вставка ряда элементов
    {
        size_t size = m_last - m_first;
        size_t size_ = last - first;
        size_t index = pos - m_first;

        iterator new_first=const_cast<iterator>(pos);
        while(size_) {
            size_--;
            new_first=insert(new_first, *(first+size_));
        }
        return new_first;

    }


    void push_back(const value_type& value)                          //добавление в конец вектора
    {
        insert(m_last, value);

    }

    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)              //замена элементов вектора
    {
        difference_type size = last - first;
        delete [] m_first;
        m_first = new value_type[size];
        std::copy(first, last, m_first);
        m_last = m_first+size;

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
