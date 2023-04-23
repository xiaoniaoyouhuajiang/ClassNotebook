#include <cstddef>
#include <stdexcept>
#include <initializer_list>
#include <utility>
#include <algorithm>
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

	explicit vector(size_t count = 0){
		m_first= new value_type[count]();
		m_last=m_first+count;
	}
	template <typename InputIterator>
	vector(InputIterator first, InputIterator last){
		difference_type size=last-first;
		m_first = new value_type[size]();
		m_last = m_first+size;
		std::copy(first,last,m_first);
	}
	vector(std::initializer_list<Type> init){
		size_t size = init.size();
		m_first = new value_type[size]();
		m_last = m_first+size;
		std::copy(init.begin(),init.end(),m_first);
	}
	vector(const vector& other){
		size_t size = other.size();
		m_first= new value_type[size]();
		m_last = m_first+size;
		std::copy(other.begin(),other.end(),m_first);
	}
	vector( vector&& other){
		m_first=nullptr;
		m_last=nullptr;
		std::swap(m_first,other.m_first);
		std::swap(m_last,other.m_last);
	}
	~vector(){
		delete [] m_first;
	}
	iterator insert(const_iterator pos, const Type& value){
		difference_type offset = pos-m_first;
		size_t size = this->size()+1;
		if (0<= offset && offset <= this->size()){
			iterator tmp = m_first;
			m_first = new value_type[size]();
			std::copy(tmp,tmp+offset,m_first);
			*(m_first+offset)=value;
			std::copy(tmp+offset,m_last,m_first+offset+1);
			m_last=m_first+size;
			delete [] tmp;
		}
		return m_first+offset;
	}
	template <typename InputIterator>
	iterator insert(const_iterator pos, InputIterator first, InputIterator last){
		difference_type offset = pos-m_first;
		difference_type quantity = last-first;
		size_t size = this->size()+quantity;
		if (0 <= offset && offset <= this->size()){
			iterator tmp = m_first;
			m_first = new value_type[size]();
			std::copy(tmp,tmp+offset,m_first);
			std::copy(first,last,m_first+offset);
			std::copy(tmp+offset,m_last,m_first+offset+quantity);
			m_last=m_first+size;
			delete [] tmp;
		}
		return m_first+offset;
	}
	void push_back(const value_type& value){
		iterator tmp = m_first;
		size_t size = this->size()+1;
		m_first = new value_type[size]();
		std::copy(tmp,m_last,m_first);
		m_last=m_first+size;
		*(m_last-1)=value;
		delete [] tmp;
	}
	void resize(size_t count){
		if (count != size()){
			size_t copy_size= size() < count ? size(): count;
			iterator tmp_first=m_first;
			m_first = count ? new value_type[count](): nullptr;
			std::copy(tmp_first,tmp_first+copy_size,m_first);
			m_last = m_first+count;
			delete [] tmp_first;
		}
	}
	iterator erase(const_iterator pos){
		difference_type offset= pos - m_first;
		iterator tmp = m_first+offset;
		std::cout<<"offset = "<<offset<<'\n';
		if (0 <= offset &&  offset < size()){
			std::copy(tmp+1,m_last,m_first+offset);
			m_last-=1;
		}
		return m_first+offset;
	}
	iterator erase(const_iterator first, const_iterator last){
		difference_type offset = first-m_first, end = m_last-last;
		if (offset>=0 && end>=0){
			iterator tmp=m_last-end;
			std::copy(tmp,m_last,m_first+offset);
			m_last-=(last-first);
		}
		return m_first+offset;
	}
	vector& operator=(const vector& other){
		if (m_first != other.m_first){
			iterator tmp_first = m_first;
			try{
				m_first= other.size() ? new value_type[other.size()]() : nullptr;
				std::copy(other.begin(),other.end(),m_first);
			}
			catch(std::exception &e){
				if (m_first != tmp_first){
					delete [] m_first;
					m_first=tmp_first;
				}
				throw;
			}
			m_last=m_first+other.size();
			delete [] tmp_first;
		}
		return *this;
	}
	vector& operator=(vector&& other){
		iterator tmp_first = m_first;
		try{
			m_first=nullptr;
			std::swap(m_first,other.m_first);
		}
		catch(std::exception &e){
			if (m_first != tmp_first){
				m_first=tmp_first;
			}
			throw;
		}
		m_last=nullptr;
		std::swap(m_last,other.m_last);
		delete [] tmp_first;
		return *this;
	}
	template <typename InputIterator>
	void assign(InputIterator first, InputIterator last){
		difference_type size = last - first;
		delete [] m_first;
		m_first = new value_type[size]();
		m_last = m_first + size;
		std::copy(first,last,m_first);
	}

	reference at(size_t pos){
		return checkIndexAndGet(pos);
	}
	const_reference at(size_t pos) const {
		return checkIndexAndGet(pos);
	}
	reference operator[](size_t pos){
		return m_first[pos];
	}
	const_reference operator[](size_t pos) const{
		return m_first[pos];
	}
	iterator begin(){
		return m_first;
	}
	const_iterator begin() const {
		return m_first;
	}
	iterator end(){
		return m_last;
	}
	const_iterator end() const {
		return m_last;
	}
	size_t size() const {
		return m_last-m_first;
	}
	bool empty() const {
		return m_first == m_last;
	}

   private:
	reference checkIndexAndGet(size_t pos){
		if ( pos>= size() ){
			throw std::out_of_range("out of range");
		}
		return m_first[pos];
	}

	iterator m_first;
	iterator m_last;
 };
