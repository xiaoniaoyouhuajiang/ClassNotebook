#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

namespace stepik
{
  template <typename Type>
  class vector{

  public:
    typedef Type* iterator;
    typedef const Type* const_iterator;

    typedef Type value_type;

    typedef value_type& reference;
    typedef const value_type& const_reference;

    typedef std::ptrdiff_t difference_type;

    explicit vector(size_t count = 0):
        m_first(count ? new value_type[count]:nullptr),
        m_last(m_first + count){

    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last):
        m_first(new value_type[last - first]),
        m_last(m_first + (last - first)){

      std::copy(first,last,m_first);
    }

    vector(std::initializer_list<Type> init):
        m_first(new value_type[init.size()]),
        m_last(m_first + init.size()){

      std::copy(init.begin(), init.end(),m_first);
    }

    vector(const vector& other):
        m_first(new value_type[other.size()]),
        m_last(m_first + other.size()){
      
      std::copy(other.begin(), other.end(),m_first);
    }

    vector(vector&& other){
        m_first = other.m_first;
        m_last = other.m_last;
        other.m_first = nullptr;
        other.m_last = nullptr;
    }

    ~vector(){
        delete[] m_first;
    }

    vector& operator= (const vector &other){
        if( this == &other) return *this;

        delete[] m_first;
        m_first = new value_type[other.size()];
        m_last = m_first + other.size();
        std::copy(other.m_first, other.m_last, m_first);
        return *this;
    }

    vector& operator= (vector&& other){
        if( this == &other) return *this;

        delete[] m_first;
        m_first = other.m_first;
        m_last = other.m_last;
        other.m_first = nullptr;
        other.m_last = nullptr;

        return *this;
    
    }
    //at methods

    template < typename InputIterator >void assign(InputIterator first, InputIterator last){
        delete[] m_first;
        m_first = new value_type[ last - first ];
        m_last = m_first + ( last - first );
        std::copy(first,last,m_first);

    }

    void resize(size_t count){
        if(count == size()) return;
        iterator temp = new value_type[count];

        if(count < size())
            std::copy(m_first,m_first+count,temp);
        else
            std::copy(m_first,m_last,temp);

        delete[] m_first;
        m_first = temp;
        m_last = m_first + count;
    }

    iterator erase(const_iterator pos){
  
        size_t len = size() -1;
        size_t elem = pos - m_first;
        iterator temp = new value_type[len];
        std::copy(m_first,(iterator)pos,temp);
        std::copy((iterator)pos + 1, m_last,temp + elem);
        delete[] m_first;
        m_first = temp;
        m_last = m_first + len;
        return m_first + elem;
    }

    iterator erase( const_iterator first, const_iterator last ){

        size_t len = size() -(last - first);
        size_t elem = first - m_first;
        iterator temp = new value_type[len];
        std::copy(m_first,(iterator)first,temp);
        std::copy((iterator)last, m_last,temp + elem);
        delete[] m_first;
        m_first = temp;
        m_last = m_first + len;
        return m_first + elem;
    }


iterator insert( const_iterator pos, const Type& value ){
    size_t len = size() +1;
    size_t elem = pos - m_first;
    iterator temp = new value_type[len];
    std::copy(m_first, m_first + elem, temp);
    *(temp + elem) = value;
    std::copy(m_first + elem, m_last, temp+elem);
    delete[] m_first;
    m_first = temp;
    m_last = temp + len;
    return m_first + elem;
}

template< class InputIt >
iterator insert( const_iterator pos, InputIt first, InputIt last ){
    size_t len = size() +(last - first);
    size_t elem = pos - m_first;
    iterator temp = new value_type[len];
    std::copy(m_first,(iterator) pos,temp);
    std::copy(first, last, temp + elem);
    std::copy(m_first + elem, m_last,temp + elem + (last - first));
    delete[] m_first;
    m_first = temp;
    m_last = m_first + len;

    return m_first + elem;
}

void push_back( const Type& value ){
    resize(size() + 1);
    *(m_last - 1) = value;
}
		





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