#pragma once
namespace stepik {
	template <typename Base>
	class shared_ptr
	{
	public:
		template<typename Derived>
		friend class shared_ptr;

		explicit shared_ptr(Base *ptr = 0) {//конструктор
			number = new int(1);//количество указателей, указывающих на объект равно 1
			curr = ptr;//присваиваем указатель
		}

		~shared_ptr() {//деструктор
			reduction();
		}

		shared_ptr(const shared_ptr & other) {//конструктор копирования
			curr = other.curr;//присваиваем указатель
			number = other.number;//присваиваем счётчик
			(*number)++;//увеличиваем количество указателей на объект
		}

		template<typename Derived>
		shared_ptr(const shared_ptr<Derived> & other) {//конструктор копирования
			curr = other.curr;//присваиваем указатель
			number = other.number;//присваиваем счётчик
			(*number)++;//увеличиваем количество указателей на объект
		}

		shared_ptr& operator=(const shared_ptr & other) {//оператор присваивания
			if (this != &other) {//если мы не присваиваем сами себе
				if (other.curr == nullptr) {
					throw "Error in operator = : new pointer is nullptr!";
				}
				reduction();//уменьшаем старый указатель
				curr = other.curr;//присваиваем указатель
				number = other.number;//присваиваем счётчик
				(*number)++;//увеличиваем новый указатель
			}
			return *this;
		}

		template <typename Derived>
		shared_ptr& operator=(const shared_ptr<Derived> & other) {//оператор присваивания
			if ((void*)this != (void*)&other) {//если мы не присваиваем сами себе
				if (other.curr == nullptr) {
					throw "Error in operator = : new pointer is nullptr!";
				}
				reduction();//уменьшаем старый указатель
				curr = (Base*)other.curr;//присваиваем указатель
				number = other.number;//присваиваем счётчик
				(*number)++;//увеличиваем новый указатель
			}
			return *this;
		}

		bool operator ==(const shared_ptr &other) const {//оператор сравнения
			return (curr == other.curr);//сравнение указателей
		}

		template <typename Derived>
		bool operator ==(const shared_ptr<Derived> &other) const {//оператор сравнения
			return (curr == other.curr);//сравнение указателей
		}

		explicit operator bool() const {//проверяет, управляет ли указатель объектом
			return (curr != nullptr);
		}

		Base* get() const {//возвращает указатель на управляемый объект
			return curr;
		}

		long use_count() const {//возвращает количество различных экземпляров shared_ptr (в том числе), управляющих текущим объектом. Если управляемый объект отсутствует, возвращается 0
			if (curr == nullptr)//если указатель ни на что не указывает
				return 0;
			else
				return *number;
		}

		Base& operator*() const {//разыменовывает указатель на управляемый объект; возвращает ссылку на управляемый объект
			return *curr;
		}

		Base* operator->() const {//разыменовывает указатель на управляемый объект; возвращает указатель на управляемый объект
			return curr;
		}

		void swap(shared_ptr& x) noexcept {//обмен содержимым
			Base* curr_copy = x.curr;//перекидываем содиржимое по методу трёх стаканов
			x.curr = curr;
			curr = curr_copy;
			int* number_copy = x.number;
			x.number = number;
			number = number_copy;
		}

		void reset(Base *ptr = 0) {//заменяет объект которым владеет
			reduction();//уменьшаем количество указателей
			number = new int(1);//на новый объект указывает один указатель
			curr = ptr;//присваиваем указатель
		}

	private:
		Base* curr;//указатель на объект
		int* number;//количество указателей на этот объект

		void reduction() {//уменьшение количества указателей
			if (*number>1)//если больше 1
				(*number)--;//то просто вычитаем
			else {//если 1
				delete curr;//удаляем всё
				delete number;
				curr = nullptr;
				number = nullptr;
			}
		}
	};
}// namespace stepik