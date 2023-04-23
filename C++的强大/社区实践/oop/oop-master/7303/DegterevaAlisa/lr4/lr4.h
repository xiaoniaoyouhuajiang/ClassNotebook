
	template <typename T>
	class shared_ptr
	{
	public:

		explicit shared_ptr(T *ptr = 0) : obj(ptr), count(ptr ? new long(1) : nullptr) {

		}

		~shared_ptr() {

			make_empty();
		}

		shared_ptr(const shared_ptr & other) : obj(other.obj), count(other.count) {

			if (count) {

				++(*count);
			}
		}

		shared_ptr& operator=(const shared_ptr & other) {

			if (obj != other.obj) {

				make_empty();
				obj = other.obj;
				count = other.count;

				if (count) {

					++(*count);
				}
			}
			return *this;
		}

		explicit operator bool() const {

			return get();
		}

		T* get() const {

			return obj;
		}

		long use_count() const {

			if (count) {
				return *count;
			}
			return 0;
		}

		T& operator*() const {

			return *obj;
		}

		T* operator->() const {

			return obj;
		}

		void swap(shared_ptr& x) noexcept {

			std::swap(obj, x.obj);
			std::swap(count, x.count);
		}

		void reset(T *ptr = 0) {

			shared_ptr temp(ptr);
			swap(temp);
		}

		void make_empty() {

			if (count) {

				if (--(*count) <= 0) {

					delete obj;
					delete count;
				}
			}

			obj = nullptr;
			count = nullptr;
		}

		template <typename D>
		friend class shared_ptr;

		template <class D>

		shared_ptr(const shared_ptr<D> & other) : obj(other.obj), count(other.count) {

			if (count) {
				++ *count;
			}
		}

		template <typename D>
		shared_ptr& operator=(const shared_ptr<D> & other)
		{
			if (obj != other.obj) {

				make_empty();
				obj = other.obj;
				count = other.count;
				if (count) {

					++ *count;
				}
			}
			return *this;
		}

	private:
		long * count;
		T* obj;
	};

	template <typename T, typename  D>
	bool  operator==(const shared_ptr<T>& lhs, const shared_ptr<D>& rhs) {
		return  lhs.get() == rhs.get();
	}
