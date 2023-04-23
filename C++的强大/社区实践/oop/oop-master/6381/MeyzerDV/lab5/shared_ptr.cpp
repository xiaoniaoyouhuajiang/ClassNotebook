#include <iostream>
// #define DEBUG
// #define DEBUG2
#include <memory>
#include <stdexcept>

namespace stepik
{
template <typename T>
class shared_ptr
{
public:
	template<class Y>
	friend class shared_ptr;

	explicit shared_ptr(T *ptr = nullptr)
	{
		#ifdef DEBUG
			std::cout << "Constructing shared " << this << " from ptr "
					<< ptr << std::endl;
		#endif
		m_ptr = ptr;
		m_count = nullptr;
		if (m_ptr)
		{
			m_count = new long(1);
			if (!m_count) throw std::bad_alloc{};
		}
	}

	~shared_ptr() noexcept
	{
		#ifdef DEBUG
			std::cout << "Destroying shared_ptr " << this << std::endl;
		#endif
		if (m_ptr)
		{
			--(*m_count);
			if ((*m_count) == 0)
			{
				#ifdef DEBUG
					std::cout << "Counter is zero, deleting owned object "
							<< m_ptr << std::endl;
				#endif
				delete m_ptr;
				delete m_count;
			}
		}
	}

	shared_ptr(const shared_ptr & other) noexcept
	{
		#ifdef DEBUG
			std::cout << "Constructing shared_ptr " << this << " from shared_ptr "
					<< &other << std::endl;
		#endif
		m_ptr = other.m_ptr;
		m_count = other.m_count;
		if (m_ptr)
		++(*m_count);
	}

	template<class Y>
	shared_ptr(const shared_ptr<Y> & other) noexcept
	{
		#ifdef DEBUG
			std::cout << "Constructing shared_ptr " << this << " from shared_ptr "
					<< &other << std::endl;
		#endif
		m_ptr = dynamic_cast<T*>(other.m_ptr);
		m_count = other.m_count;
		if (m_ptr)
		++(*m_count);
	}

	shared_ptr& operator=(const shared_ptr &other) noexcept
	{
		#ifdef DEBUG
		std::cout << "Assigning shared ptrs: " << this << " = "
		<< &other << std::endl;
		#endif
		if ((void*)this == (void*)&other) return *this;
		if (m_ptr)
		{
			--(*m_count);
			if((*m_count)==0)
			{
				#ifdef DEBUG
					std::cout << "Counter is zero, deleting owned object "
							<< m_ptr << std::endl;
				#endif
				delete m_ptr;
				delete m_count;
				m_ptr = nullptr;
				m_count = nullptr;
			}
		}
		m_ptr = other.m_ptr;
		m_count = other.m_count;
		if (m_ptr)
		++(*m_count);
		return *this;
	}

	template<class Y>
	shared_ptr& operator=(const shared_ptr<Y> &other) noexcept
	{
		#ifdef DEBUG
			std::cout << "Assigning shared ptrs: " << this << " = "
					<< &other << std::endl;
		#endif
		if ((void*)this == (void*)&other) return *this;
		if (m_ptr)
		{
			--(*m_count);
			if((*m_count)==0)
			{
				#ifdef DEBUG
					std::cout << "Counter is zero, deleting owned object "
							<< m_ptr << std::endl;
				#endif
				delete m_ptr;
				delete m_count;
				m_ptr = nullptr;
				m_count = nullptr;
			}
		}
		m_ptr = dynamic_cast<T*>(other.m_ptr);
		m_count = other.m_count;
		if (m_ptr)
		++(*m_count);
		return *this;
	}

	explicit operator bool() const noexcept
	{
		#ifdef DEBUG2
			std::cout << "Bool called " << this << std::endl;
		#endif
		if (m_ptr) return true;
		return false;
	}

	T* get() const noexcept
	{
		#ifdef DEBUG2
			std::cout << "Get called " << this << std::endl;
		#endif
		return m_ptr;
	}

	long use_count() const noexcept
	{
		#ifdef DEBUG2
			std::cout << "Count called " << this << std::endl;
		#endif
		if (!m_count) return 0;
		return *m_count;
	}

	T& operator*() const noexcept
	{
		#ifdef DEBUG2
			std::cout << "* called " << this << std::endl;
		#endif
		return *m_ptr;
	}

	T* operator->() const noexcept
	{
		#ifdef DEBUG2
		std::cout << "-> called " << this << std::endl;
		#endif
		return m_ptr;
	}

	void swap(shared_ptr& x) noexcept
	{
		#ifdef DEBUG2
			std::cout << "Swapping shared ptrs " << this << " and "
			<< &x << std::endl;
		#endif
		T *tmp_ptr = m_ptr;
		long *tmp_count = m_count;
		m_ptr = x.m_ptr;
		m_count = x.m_count;
		x.m_ptr = tmp_ptr;
		x.m_count = tmp_count;
	}

	void reset(T *ptr = nullptr)
	{
		#ifdef DEBUG
			std::cout << "Resetting shared_ptr " << this << " from " << m_ptr
				<< " to " << ptr << std::endl;
		#endif
		if (m_ptr)
		{
		 --(*m_count);
		 if ((*m_count)==0)
		 {
			#ifdef DEBUG
				std::cout << "Counter is zero, deleting owned object "
						<< m_ptr << std::endl;
			#endif
			delete m_ptr;
			delete m_count;
			m_ptr = nullptr;
			m_count = nullptr;
		}
		}
		m_ptr = ptr;
		m_count = nullptr;
		if (m_ptr)
		{
			m_count = new long(1);
			if (!m_count) throw std::bad_alloc{};
		}
	}

private:
	// data members
	T *m_ptr;
	long *m_count;
};

	// Comparison operators
		template <class T, class U>
		bool operator==(const shared_ptr<T> &lhs,
							 const shared_ptr<U> &rhs) noexcept
		{
			return (lhs.get() == rhs.get());
		}

		template <class T, class U>
		bool operator!=(const shared_ptr<T> &lhs,
							 const shared_ptr<U> &rhs) noexcept
		{
			return !(lhs == rhs);
		}

		template <class T, class U>
		bool operator<(const shared_ptr<T> &lhs,
							 const shared_ptr<U> &rhs) noexcept
		{
			return (lhs.get() < rhs.get());
		}

		template <class T, class U>
		bool operator>(const shared_ptr<T> &lhs,
							 const shared_ptr<U> &rhs) noexcept
		{
			return (rhs < lhs);
		}

		template <class T, class U>
		bool operator<=(const shared_ptr<T> &lhs,
							 const shared_ptr<U> &rhs) noexcept
		{
			return !(rhs < lhs);
		}

		template <class T, class U>
		bool operator>=(const shared_ptr<T> &lhs,
							 const shared_ptr<U> &rhs) noexcept
		{
			return !(lhs < rhs);
		}

		// Class and nullptr
		template <class T>
		bool operator==(const shared_ptr<T> &lhs, std::nullptr_t rhs) noexcept
		{
			return !lhs;
		}
		template <class T>
		bool operator==(std::nullptr_t lhs, const shared_ptr<T> &rhs) noexcept
		{
			return !rhs;
		}
		template <class T>
		bool operator!=(const shared_ptr<T> &lhs, std::nullptr_t rhs) noexcept
		{
			return (bool)lhs;
		}
		template <class T>
		bool operator!=(std::nullptr_t lhs, const shared_ptr<T> &rhs) noexcept
		{
			return (bool)rhs;
		}
		template <class T>
		bool operator<(const shared_ptr<T> &lhs, std::nullptr_t rhs) noexcept
		{
			return lhs.get() < nullptr;
		}
		template <class T>
		bool operator<(std::nullptr_t lhs, const shared_ptr<T> &rhs) noexcept
		{
			return nullptr < rhs.get();
		}
		template <class T>
		bool operator>(const shared_ptr<T> &lhs, std::nullptr_t rhs) noexcept
		{
			return nullptr < lhs;
		}
		template <class T>
		bool operator>(std::nullptr_t lhs, const shared_ptr<T> &rhs) noexcept
		{
			return rhs < nullptr;
		}
		template <class T>
		bool operator<=(const shared_ptr<T> &lhs, std::nullptr_t rhs) noexcept
		{
			return !(nullptr < lhs);
		}
		template <class T>
		bool operator<=(std::nullptr_t lhs, const shared_ptr<T> &rhs) noexcept
		{
			return !(rhs < nullptr);
		}
		template <class T>
		bool operator>=(const shared_ptr<T> &lhs, std::nullptr_t rhs) noexcept
		{
			return !(lhs < nullptr);
		}
		template <class T>
		bool operator>=(std::nullptr_t lhs, const shared_ptr<T> &rhs) noexcept
		{
			return !(nullptr < rhs);
		}
	// End of comparison operators

} // namespace stepik
