#pragma once

namespace stepik
{
	template <typename Type>
	class shared_ptr
	{

		template<class V> friend class shared_ptr;
		typedef long* l_ptrl;

	private:
		Type * m_ptr;
		l_ptrl m_count;

	public:
		explicit shared_ptr(Type *ptr = 0)
			: m_ptr(ptr), m_count((ptr != nullptr) ? new long(1) : nullptr) {}

		~shared_ptr()
		{
			if (use_count() > 1)
				(*m_count) -= 1;
			else
			{
				delete m_ptr;
				delete m_count;
				m_ptr = nullptr;
				m_count = nullptr;
			}
		}


		template <typename V>
		shared_ptr(const shared_ptr<V> & other) :
			m_ptr(other.m_ptr), m_count(other.m_count)
		{
			if (use_count())
				(*m_count)++;

		}

		shared_ptr(const shared_ptr & other) :
			m_ptr(other.m_ptr), m_count(other.m_count)
		{
			if (use_count())
				(*m_count)++;
		}

		template <typename V>
		shared_ptr& operator=(const shared_ptr<V> & other)
		{
			if (m_ptr != other.get()) {
				this->~shared_ptr();
				m_ptr = other.m_ptr;
				m_count = other.m_count;
				if (use_count())
					(*m_count)++;
			}
			return *this;
		}

		shared_ptr& operator=(const shared_ptr & other)
		{
			if (this != &other) {
				this->~shared_ptr();
				m_ptr = other.m_ptr;
				m_count = other.m_count;
				if (use_count())
					(*m_count)++;
			}
			return *this;
		}

		explicit operator bool() const
		{
			return m_ptr != nullptr;
		}

		Type* get() const
		{
			return m_ptr;
		}

		long use_count() const
		{
			return (m_ptr != nullptr) ? *m_count : 0;
		}

		Type& operator*() const
		{
			return *m_ptr;
		}

		Type* operator->() const
		{
			return m_ptr;
		}

		void swap(shared_ptr& x) noexcept
		{
			std::swap(m_ptr, x.m_ptr);
			std::swap(m_count, x.m_count);
		}

		void reset(Type *m_ptr = 0)
		{
			shared_ptr<Type>(m_ptr).swap(*this);
		}

		template <typename TN>
		bool operator ==(const shared_ptr<TN> &other) const {
			return (void*)m_ptr == (void*)other.m_ptr;
		}

		bool operator ==(const shared_ptr &other)const {
			return (void*)m_ptr == (void*)other.m_ptr;
		}

	};
}
