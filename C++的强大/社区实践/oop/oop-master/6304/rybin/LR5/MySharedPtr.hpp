//#pragma once
#include <algorithm>

namespace stepik
{
	template <typename T>
	class shared_ptr
	{
		template <typename Derived>
		friend class shared_ptr;

	public:
		explicit shared_ptr(T *ptr = 0)
		{
			m_ptr = ptr;
			m_count = m_ptr ? new size_t(1) : nullptr;
		}

		~shared_ptr()
		{
			if (use_count() > 1) {
				--(*m_count);
			}
			else if (use_count() == 1) {
				delete m_ptr;
				delete m_count;
			}
		}

		shared_ptr(const shared_ptr & other)
		{
			m_ptr = other.m_ptr;
			m_count = other.m_count;
			if (use_count()) {
				++(*m_count);
			}
		}

		template <typename Derived>
		shared_ptr(const shared_ptr<Derived> & other)
		{
			m_ptr = dynamic_cast<T*>(other.m_ptr);
			m_count = other.m_count;
			if (use_count()) {
				++(*m_count);
			}
		}

		shared_ptr& operator=(const shared_ptr & other)
		{
			if (this != &other) {
				if (use_count() > 1) {
					--(*m_count);
				}
				else if (use_count() == 1) {
					delete m_ptr;
					delete m_count;
				}

				m_ptr = other.m_ptr;
				m_count = other.m_count;
				if (use_count()) {
					++(*m_count);
				}
			}

			return *this;
		}

		template <typename Derived>
		shared_ptr& operator=(const shared_ptr<Derived> & other)
		{
			if (use_count() > 1) {
				--(*m_count);
			}
			else if (use_count() == 1) {
				delete m_ptr;
				delete m_count;
			}

			m_ptr = dynamic_cast<T*>(other.m_ptr);
			m_count = other.m_count;
			if (use_count()) {
				++(*m_count);
			}

			return *this;
		}

		explicit operator bool() const
		{
			return get() != nullptr;
		}

		T* get() const
		{
			return m_ptr;
		}

		long use_count() const
		{
			return m_ptr ? *m_count : 0;
		}

		T& operator*() const
		{
			return *m_ptr;
		}

		T* operator->() const
		{
			return m_ptr;
		}

		void swap(shared_ptr& x) noexcept
		{
			std::swap(m_ptr, x.m_ptr);
			std::swap(m_count, x.m_count);
		}

		void reset(T *ptr = 0)
		{
			shared_ptr<T>(ptr).swap(*this);
		}

		template<typename U>
		bool operator==(const shared_ptr<U>& rhs) const
		{
			return get() == rhs.get();
		}

		template<typename U>
		bool operator!=(const shared_ptr<U>& rhs) const
		{
			return get() != rhs.get();
		}

	private:
		// data members
		T * m_ptr;
		size_t* m_count;
	};
} // namespace stepik