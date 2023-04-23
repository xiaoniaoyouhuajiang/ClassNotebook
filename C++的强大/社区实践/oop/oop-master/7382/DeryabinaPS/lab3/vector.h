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

    explicit vector(size_t count = 0)
        : m_first(new Type[count])
        , m_last(m_first + count)
    {
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
        : vector(last - first)
    {
        std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init)
        : vector(init.size())
    {
        int count = 0;
        for (auto& element : init) {
            m_first[count] = element;
            ++count;
        }
    }

    vector(const vector& other)
        : vector(other.size())
    {
        std::copy(other.begin(), other.end(), m_first);
    }

    vector(vector&& other)
    {
        std::swap(m_first, other.m_first);
        std::swap(m_last, other.m_last);
    }
    ~vector()
    {
        delete[] m_first;
        m_first = m_last = nullptr;
    }

    vector& operator=(const vector& other)
    {
        delete[] m_first;
        m_first = new Type[other.size()];
        m_last = m_first + other.size();
        std::copy(other.begin(), other.end(), m_first);
        return *this;
    }

    vector& operator=(vector&& other)
    {
        std::swap(m_first, other.m_first);
        std::swap(m_last, other.m_last);
        return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        delete[] m_first;
        int size = last - first;
        m_first = new Type[size];
        m_last = m_first + size;
        std::copy(first, last, m_first);
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
        size_t ind = pos - m_first;
        size_t old_size = m_last - m_first;
        size_t new_size = old_size + 1;

        resize(new_size);
        std::copy(m_first + ind, m_last, m_first + ind + 1);
        m_first[ind] = value;

        return m_first + ind;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        size_t ind = pos - m_first;
        size_t add = last - first;
        size_t old_size = m_last - m_first;

        resize(old_size + add);

        for (int i = old_size + add - 1; i != ind; i--) {
            m_first[i] = m_first[i - add];
        }
        std::copy(first, last, m_first + ind);

        return m_first + ind;
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
        if (pos >= size()) {
            throw std::out_of_range("out of range");
        }

        return m_first[pos];
    }

    //your private functions

private:
    iterator m_first;
    iterator m_last;
};

} // namespace stepik
