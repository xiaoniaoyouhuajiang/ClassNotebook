
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
        if (_Buy(count))
        {
            m_last += count;
        }
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
        size_t _Newsize = std::distance(first, last);
        if (_Buy(_Newsize))
        {
            m_last += _Newsize;
            std::copy(first, last, m_first);
        }
    }

    vector(std::initializer_list<Type> init)
    {
        if (_Buy(init.size()))
        {
            m_last += init.size();
            std::copy(init.begin(), init.end(), m_first);
        }
    }

    vector(const vector& other)
    {
        if (_Buy(other.capacity())) 
        {
            m_last += other.size();
            std::copy(other.begin(), other.end(), m_first);
        }
    }

    vector(vector&& other) : m_first(), m_last(), m_end()
    { 
        std::swap(m_first, other.m_first);
        std::swap(m_last, other.m_last);
        std::swap(m_end, other.m_end);
    }

    ~vector()
    {
        _Tidy();
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
        _Tidy();
        if (_Buy(other.capacity()))
        {
            m_last += other.size();
            std::copy(other.begin(), other.end(), m_first);
        }
        return *this;
    }

    vector& operator=(vector&& other)
    {
        _Tidy();
        std::swap(m_first, other.m_first);
        std::swap(m_last, other.m_last);
        std::swap(m_end, other.m_end);
        return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        _Tidy();
        size_t _Newsize = std::distance(first, last);
        size_t _Newcapacity = _Calculate_growth(_Newsize);
        if (_Buy(_Newcapacity))
        {
            m_last += _Newsize;
            std::copy(first, last, m_first);
        }
    }
    
    // resize methods
    void resize(size_t count)
    {
        _Resize(count);
    }

    //erase methods
    iterator erase(const_iterator pos)
    {   
        iterator _Pos = iterator(pos);
        std::rotate(_Pos, _Pos + 1, m_last);
        --m_last;
        return (_Pos);
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        size_t _Offset = std::distance(first, last);
        iterator _First = iterator(first);
        iterator _Last = iterator(last);
        std::rotate(_First, _Last, m_last);
        m_last -= _Offset;
        return (_First);
    }
    
    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {   
        iterator _Pos = iterator(pos);
        size_t _Offset = std::distance(m_first, _Pos);
        if (!_Has_unused_capacity())
        {
            _Resize(size() + 1);
            _Pos = m_first + _Offset;
        }
        std::rotate(_Pos + 1, _Pos + size() - 1, m_last);
        *_Pos = value;
        return (_Pos);
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        iterator _Pos = iterator(pos);
        iterator _First = iterator(first);
        iterator _Last = iterator(last);
        
        size_t _Offset = std::distance(_First, _Last);
        size_t _Tillpos = std::distance(m_first, _Pos);
        if (_Unused_capacity() < _Offset)
        {
            _Resize(size() + _Offset);
            _Pos = m_first + _Tillpos;
        }

        std::rotate(_Pos, _Pos + size() - _Offset - _Tillpos, m_last);
        std::copy(first, last, _Pos);
        return (_Pos);
    }

    //push_back methods
    void push_back(const value_type& value)
    {
        if (!_Has_unused_capacity())
        {
            _Resize(size() + 1);
            --m_last;
        }
        ++m_last;
        *(m_last - 1)= value;
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

    // capacity method
    size_t capacity() const
    {
        return m_end - m_first;
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

    bool _Buy(size_t _Newcapacity) 
    {	// allocate array with _Newcapacity elements
        m_first = m_last = m_end = iterator();
        if (!_Newcapacity)
            return (false);
        m_first = new value_type[_Newcapacity];
        m_last = m_first;
        m_end = m_first + _Newcapacity;
        return (true);
    }

    void _Tidy()
    {	// free all storage
        if (m_first != iterator())
        {	// deallocate old array
            delete[] m_first;
            m_first = m_last = m_end = iterator();
        }
    }

    void _Change_array(const iterator _Newvec, const size_t _Newsize, const size_t _Newcapacity)
    {	// discard old array, acquire new array
        _Tidy();
        m_first = _Newvec;
        m_last = _Newvec + _Newsize;
        m_end = _Newvec + _Newcapacity;
    }

    size_t _Calculate_growth(const size_t _Newsize) const
	{	// given _Oldcapacity and _Newsize, calculate geometric growth
		const size_t _Oldcapacity = capacity();

		const size_t _Geometric = _Oldcapacity + _Oldcapacity / 2;

		if (_Geometric < _Newsize)
		{
			return (_Newsize);	// geometric growth would be insufficient
		}

		return (_Geometric);	// geometric growth is sufficient
	}

    size_t _Unused_capacity() const noexcept
	{	// micro-optimization for capacity() - size()
		return m_end - m_last;
	}

	bool _Has_unused_capacity() const noexcept
	{	// micro-optimization for capacity() != size()
		return m_end != m_last;
	}

    void _Resize(const size_t _Newsize)
	{	// trim or append elements, provide strong guarantee
		const size_t _Oldsize = size();
		const size_t _Oldcapacity = capacity();

		if (_Newsize > _Oldcapacity)
		{	// reallocate
			const size_t _Newcapacity = _Calculate_growth(_Newsize);
            iterator _Newvec = new value_type[_Newcapacity];
            std::copy(m_first, m_last, _Newvec);
			_Change_array(_Newvec, _Newsize, _Newcapacity);
		}
		else if (_Newsize > _Oldsize)
		{	// append
            m_last += (_Newsize - _Oldsize);
		}
		else if (_Newsize == _Oldsize)
		{	// nothing to do, avoid invalidating iterators
		}
		else
		{	// trim
			m_last -= (_Oldsize - _Newsize);
		}
	}
private:
    iterator m_first;
    iterator m_last;
    iterator m_end;
};
}// namespace stepik