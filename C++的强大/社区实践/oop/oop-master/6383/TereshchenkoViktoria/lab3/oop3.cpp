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
			m_first = new Type[count];
			m_last = m_first + count;
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			unsigned int range = last - first;
			m_first = new Type[range];
			for (unsigned int i = 0; i < range; first++, i++)
			{
				m_first[i] = *first;
			}
			m_last = m_first + range;

		}

		vector(std::initializer_list<Type> init)
		{
			m_first = new Type[init.size()];
			int i = 0;
			for (auto init_list : init) 
            {
				m_first[i] = init_list;
				i++;
			}
			m_last = m_first + init.size();
		}

		vector(const vector& other)
		{
			m_first = new Type[other.size()];
			for (int i = 0; i < other.size(); i++) 
            {
				m_first[i] = other[i];
			}
			m_last = m_first + other.size();
		}

	
		void swap(vector& first, vector& second)
		{
			using std::swap;
			swap(first.m_first, second.m_first);
			swap(first.m_last, second.m_last);
		}

		vector(vector&& other) : vector()
		{
			swap(*this, other);
		}

		~vector()
		{
			delete[] m_first;
		}

		vector& operator=(const vector& other)
		{
			unsigned int count = other.m_last - other.m_first;
			delete[] m_first;
			m_first = new Type[count];
			for (int i = 0; i < other.size(); i++) 
            {
				m_first[i] = other[i];
			}
			m_last = m_first + count;
			return *this;
		}

		vector& operator=(vector&& other)
		{
			swap(*this, other);
		}

		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			unsigned int range = last - first;
			delete[] m_first;
			m_first = new Type[range];
			for (unsigned int i = 0; i < range; i++)
			{
				m_first[i] = *first;
				first++;
			}
			m_last = m_first + range;
		}

		void resize(size_t count)
		{
			vector dop(*this);
			delete[] m_first;
			m_first = new Type[count];
			if (dop.size() < count) {
				for (int i = 0; i < dop.size(); i++) 
                {
					m_first[i] = dop[i];
				}
				for (int i = dop.size(); i < count; i++) 
                {
					m_first[i] = 0;
				}
			}
			else {
				for (int i = 0; i < count; i++) 
                {
					m_first[i] = dop[i];
				}
			}
            m_last = m_first + count;
		}

		iterator erase(const_iterator pos)
		{
			difference_type elem = pos - m_first;
			std::rotate(m_first + elem, m_first + elem + 1, m_last);
			resize(size() - 1);
			return m_first + elem;

		}

		iterator erase(const_iterator first, const_iterator last)
		{
			difference_type elem = first - m_first;
			difference_type range = last - first;
			std::rotate(m_first + elem, m_first + elem + range, m_last);
			resize(size() - range);
			return m_first + elem;
		}
        
	   iterator insert(const_iterator pos, const Type& value)
	   {
		   
		 iterator item = new Type[size()+1];
		 difference_type range1 = pos-m_first;
		 std::copy(m_first, m_first+range1, item);
		 item[range1] = value;
		 std::copy(m_first+range1, m_last, item+range1+1);
		   
		 m_last = item+size()+1;  
		 if(m_first)
		   delete[] m_first;
		 m_first = item;		 
		 return m_first+range1;
	   }
   
	   template <typename InputIterator>
	   iterator insert(const_iterator pos, InputIterator first, InputIterator last)
	   {		
		 difference_type range1 = pos - m_first;
		 difference_type range2 = last - first;
		 iterator item = new Type[size() + range2];
		 std::copy(m_first, m_first+range1, item);
		 std::copy(first, last, item + range1);
		 std::copy(m_first+range1, m_last, item + range1 + range2);		   
		 m_last = item + size() + range2;
		 if(m_first)
		   delete[] m_first;
		 m_first = item;
		 return m_first + range1;
	   }
   
	   //push_back methods
	   void push_back(const value_type& value)
	   {		 
		 iterator item = new Type[size()+1];
		 std::copy(m_first, m_last, item);
		 item[size()] = value;		   
		 m_last = item + size() + 1;
		 if(m_first)
		   delete[] m_first;
		 m_first = item;		 
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
