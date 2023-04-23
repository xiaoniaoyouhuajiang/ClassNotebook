#include <assert.h> 
#include <algorithm> // std::copy, std::rotate 
#include <cstddef> // size_t 
#include <initializer_list> 
#include <stdexcept> 

namespace stepik{
	template <typename Type>
	class vector{
	public:
		typedef Type* iterator;
		typedef const Type* const_iterator;

		typedef Type value_type;

		typedef value_type& reference; //ссылка
		typedef const value_type& const_reference;//константная ссылка

		typedef std::ptrdiff_t difference_type; //указатель на разные типы

		explicit vector(size_t count = 0){ //явный конструктор(неконвертирующийся конструктор)
			m_first = new Type[count];
			m_last = m_first + count;// use previous step implementation 
		}

		template <typename InputIterator> 
		vector(InputIterator first, InputIterator last){
			Type *first_t = (Type*)first;
			Type *last_t = (Type*)last;

			m_first = new Type[last_t - first_t];
			m_last = m_first + (last_t - first_t);
			std::copy(first_t, last_t, m_first);// use previous step implementation 
		}

		vector(std::initializer_list<Type> init) :
			vector(init.begin(), init.end())
		{}

		vector(const vector& other) :
			vector(other.m_first, other.m_last)
		{}

		vector(vector&& other){ 
			swap(*this, other);// use previous step implementation 
		}

		~vector(){ 
			delete[] m_first;
			m_first = nullptr;
			m_last = nullptr;// use previous step implementation 
		}

		vector& operator=(const vector& other){ 
			if (((void*)this) == ((void*)(&other)))return *this;
			vector v(other);
			swap(*this, v);
			//std::cout « "присваивание копированием\n"; 
			return *this;
		}

		vector& operator=(vector&& other){ 
			if (((void*)this) == ((void*)(&other)))return *this;
			swap(*this, other);
			//std::cout « "присваивание перемещением\n"; 
			return *this;
		}

		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last){ //написала
			vector v(first, last);
			swap(*this, v);
			//std::cout « "assign\n"; 
		}

		void resize(size_t count){ 
			size_t c = m_last - m_first;
			if (count == c)return;

			vector v(count);
			size_t ms = count < c ? count : c;
			std::copy(m_first, m_first + ms, v.m_first);
			swap(*this, v);
		}

		//insert methods 
		iterator insert(const_iterator pos, const Type& value){ 
			size_t f = (Type*)pos - m_first;
			vector v(size() + 1);
			std::copy(m_first, m_first + f, v.m_first);
			*(v.m_first + f) = value;
			std::copy(m_first + f, m_last, v.m_first + f + 1);
			*this = std::move(v);
			//std::cout « "вставка одного элемента\n"; 
			return m_first + f;// implement this 
		}

		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last){
			size_t f = (Type*)pos - m_first;
			size_t l = f + (last - first);
			vector v(size() + last - first);
			std::copy(m_first, m_first + f, v.m_first);
			std::copy(first, last, v.m_first + f);
			std::copy(m_first + f, m_last, v.m_first + l);
			*this = std::move(v);
			//std::cout « "вставка диапозона элементов\n"; 
			return m_first + f;// implement this 
		}

		//push_back methods 
		void push_back(const value_type& value){ 
			resize(size() + 1);
			*(m_last - 1) = value;// implement this 
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

		const_reference operator[](size_t pos) const { 
			return m_first[pos];
		}

		//*begin methods 
		iterator begin(){ 
			return m_first;
		}

		const_iterator begin() const { 
			return m_first;
		}

		//*end methods 
		iterator end(){
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

		static void swap(vector& a, vector& b) {
			std::swap(a.m_first, b.m_first);
			std::swap(a.m_last, b.m_last);
		}
		//your private functions 

	private: 
		iterator m_first = nullptr;
		iterator m_last = nullptr;
	};
}// namespace stepik
