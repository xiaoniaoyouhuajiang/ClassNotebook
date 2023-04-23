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
    typedef Type *iterator;
    typedef const Type *const_iterator;

    typedef Type value_type;

    typedef value_type &reference;
    typedef const value_type &const_reference;

    typedef std::ptrdiff_t difference_type;

    explicit vector(size_t count = 0): m_first(count ? new value_type[count] : nullptr), m_last(m_first + count){}

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last){
        if((last - first) <= 0){
            m_last = nullptr;
            m_first = nullptr;
            return;
        }
        m_first = new value_type[last - first];
        std::copy(first, last, m_first);
        m_last = m_first + (last - first);
    }
    vector(std::initializer_list<Type> init){
        if(!init.size()){
            m_last = nullptr;
            m_first = nullptr;
            return;
        }
        m_first = new value_type[init.size()];
        std::copy(init.begin(), init.end(), m_first);
        m_last = m_first + init.size();
    }

    vector(const vector &other){
        if(other.empty()){
            m_last = nullptr;
            m_first = nullptr;
            return;
        }
        m_first = new value_type[other.size()];
        std::copy(other.begin(), other.end(), m_first);
        m_last = m_first + other.size();
    }

    vector(vector &&other): m_first(other.m_first), m_last(other.m_last){
        other.m_first = nullptr;
        other.m_last = nullptr;
    }

    iterator insert(const_iterator pos, const Type &value){            //вставка элемента
        size_t size = m_last - m_first;
        size_t index = pos - m_first;
        resize(size + 1);
        *(m_last - 1) = value;
        std::rotate(m_first + index, m_last - 1, m_last);
        return m_first + index;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last){   //вставка ряда элементов
        size_t size = m_last - m_first;
        size_t size_ = last - first;
        size_t index = pos - m_first;
        iterator new_first = const_cast<iterator>(pos);
        while(size_){
            size_--;
            new_first = insert(new_first, *(first + size_));
        }
        return new_first;

    }
    void push_back(const value_type &value){                          //добавление в конец вектора
        insert(m_last, value);

    }
    // resize methods
    void resize(size_t count){              //изменение размера вектора
        if(count == (m_last - m_first))
            return;
        value_type new_first[m_last - m_first];
        size_t size = m_last - m_first;
        std::copy(m_first, m_last, new_first);
        delete [] m_first;
        m_first = new value_type[count];
        m_last = m_first + count;
        if(count > size)
            std::copy(new_first, new_first + size, m_first);
        else
            std::copy(new_first, new_first + count, m_first);
    }
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last){
        vector tmp(first, last);
        tmp.swap(*this);
    }
    ~vector(){
        if(!empty()){
            delete[] m_first;
            m_first = nullptr;
            m_last = nullptr;
        }
    }
    //at methods
    reference at(size_t pos){
        return checkIndexAndGet(pos);
    }

    const_reference at(size_t pos) const{
        return checkIndexAndGet(pos);
    }

    //[] operators
    reference operator[](size_t pos){
        return m_first[pos];
    }

    const_reference operator[](size_t pos) const{
        return m_first[pos];
    }

    //*begin methods
    iterator begin(){
        return m_first;
    }

    const_iterator begin() const{
        return m_first;
    }

    //*end methods
    iterator end(){
        return m_last;
    }

    const_iterator end() const{
        return m_last;
    }

    //size method
    size_t size() const{
        return m_last - m_first;
    }

    //empty method
    bool empty() const{
        return m_first == m_last;
    }

private:
    reference checkIndexAndGet(size_t pos) const{
        if(pos >= size())
            throw std::out_of_range("out of range");
        return m_first[pos];
    }

    void swap(vector &other){
        std::swap(this->m_first, other.m_first);
        std::swap(this->m_last, other.m_last);
    }

private:
    iterator m_first;
    iterator m_last;
};
}// namespace stepik
