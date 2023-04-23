#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
#include <iterator>
#include <iostream>

template< class Iterator >
std::reverse_iterator<Iterator> make_reverse_iterator(Iterator i)
{
    return std::reverse_iterator<Iterator>(i);
}

namespace stepik {
  template <typename Type>
  class vector {
  public:
    typedef Type* iterator;
    typedef const Type* const_iterator;

    typedef Type value_type;

    typedef Type& reference;
    typedef const Type& const_reference;

    typedef std::ptrdiff_t difference_type;

    explicit vector(size_t count = 0) {
      // std::cout << "---const---" << std::endl;
      m_first = new Type[count];
      m_last = m_first + count;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last) {
      // std::cout << "---iterator const---" << std::endl;
      size_t size = std::distance(first, last);
      m_first = new Type[size];
      std::copy(first, last, m_first);
      m_last = m_first + size;
    }

    vector(std::initializer_list<Type> init): vector(init.begin(), init.end()) {
      // std::cout << "---initlist const---" << std::endl;
    }

    vector(const vector& other): vector(other.begin(), other.end()) {
      // std::cout << "---copy const---" << std::endl;
    }

    vector(vector&& other): m_first(other.m_first), m_last(other.m_last) {
      // std::cout << "---move const---" << std::endl;
      other.m_first = other.m_last = nullptr;
    }

    //assignment operators
    vector& operator=(const vector& other) {
      // std::cout << "---copy---" << std::endl;
      if (this != &other) {
        delete[] m_first;
        m_first = new Type[other.size()];
        std::copy(other.m_first, other.m_last, m_first);
        m_last = m_first + other.size();
      }
    }

    vector& operator=(vector&& other) {
      if (this != &other) {
        delete[] m_first;
        m_first = other.m_first;
        m_last = other.m_last;
        other.m_first = other.m_last = nullptr;
      }
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last) {
      *this = vector(first, last);
    }

    ~vector() {
      delete[] m_first;
    }

    // resize methods
    void resize(size_t count) {
			vector new_vector(count);
			if (count > size()) {
				std::move(m_first, m_last, new_vector.m_first);
			}
			else {
				std::move(m_first, m_first + count, new_vector.m_first);
			}

			swap(new_vector);
		}

    //erase methods
    iterator erase(const_iterator pos) {
			size_t new_pos = pos - m_first;
			std::rotate(const_cast<iterator>(pos), const_cast<iterator>(pos)+1, m_last);
			resize(size() - 1);
			return m_first + new_pos;
		}

		iterator erase(const_iterator first, const_iterator last) {
      size_t new_pos = last - first;
			iterator new_first = const_cast<iterator>(first);
			while (new_pos != 0) {
				new_first = erase(new_first);
				new_pos--;
			}

			return new_first;
    }

    iterator insert(const_iterator pos, const Type& value) {
			size_t insertSize = std::distance(m_first, pos);
			resize(size() + 1);

			iterator new_pos = std::advance(m_first, insertSize);
			std::rotate(new_pos, m_last - 1, m_last);
			m_first[new_pos - m_first] = value;

      return new_pos;
		}


    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last) {
			int insert_size = std::distace(first, last);
			iterator new_pos = const_cast<iterator>(pos);
			while (insert_size != 0) {
				new_pos = insert(newPos, *(std::advance(first, insertSize--)));
			}
			return new_pos;
    }

    //push_back methods
    void push_back(const value_type& value) {
      insert(m_last, value);
    }

    //at methods
    reference at(size_t pos) {
      return checkIndexAndGet(pos);
    }

    const_reference at(size_t pos) const {
      return checkIndexAndGet(pos);
    }

    //[] operators
    reference operator[](size_t pos) {
      return m_first[pos];
    }

    const_reference operator[](size_t pos) const {
      return m_first[pos];
    }

    //*begin methods
    iterator begin() {
      return m_first;
    }

    const_iterator begin() const {
      return m_first;
    }

    //*end methods
    iterator end() {
      return m_last;
    }

    const_iterator end() const {
      return m_last;
    }

    //size method
    size_t size() const {
      return m_last - m_first;
    }

    //empty method
    bool empty() const {
      return m_first == m_last;
    }

  private:
    reference checkIndexAndGet(size_t pos) const {
      if (pos >= size()) {
        throw std::out_of_range("out of range");
      }

      return m_first[pos];
    }

    void swap(vector & other) {
			std::swap(this->m_first, other.m_first);
			std::swap(this->m_last, other.m_last);
		}

  private:
    iterator m_first;
    iterator m_last;
  };
} // namespace stepik

stepik::vector<char> make_vector() {
  return std::move(stepik::vector<char>{'m', 'o', 'v', 'e'});
}

int main() {
  stepik::vector<int> v_size_cons(4);
  stepik::vector<int> v_it_cons(v_size_cons.begin(), v_size_cons.end());
  stepik::vector<int> v_list_cons{1, 4, 2, 3, 10, 23, 6, 5};
  stepik::vector<int> v_copy_cons(v_list_cons);
  stepik::vector<char> v_move_cons(make_vector());

  stepik::vector<int> v_copy_assign = v_list_cons;
  stepik::vector<char> v_move_assign = make_vector();
  stepik::vector<int> v_assign{0, 0, 0};
  v_assign.assign(v_list_cons.begin(), v_list_cons.end());
  int* begin = v_assign.begin();
  v_assign.resize(10000);
  for (auto el : v_assign) {
    std::cout << el << ' ';
  } std::cout << std::endl;

  std::cout << *v_assign.begin() << std::endl;
  return 0;
}
