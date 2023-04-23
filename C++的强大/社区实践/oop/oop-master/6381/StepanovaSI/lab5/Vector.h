#pragma once
namespace stepik
{
	template <typename Type>
	class vector
	{
	public:
		typedef Type* iterator;//итератор(указатель) произвольного доступа, который может читать или изменять любой элемент в векторе
		typedef const Type* const_iterator;//итератор(указатель) произвольного доступа, который может читать элемент const в векторе

		typedef Type value_type;//тип данных, хранящихся в векторе

		typedef value_type& reference;//ссылка на элемент, хранящийся в векторе
		typedef const value_type& const_reference;//итератор(указатель) произвольного доступа, который может читать любой элемент const в векторе

		typedef std::ptrdiff_t difference_type;//различие между адресами двух элементов в векторе

		explicit vector(size_t count = 0) { //constructor
			m_first = new value_type[count];//создаём массив
			m_last = m_first + count;
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last) { //constructor
			m_first = new value_type[last - first];//создаём массив
			for (size_t i = 0; i < (last - first); i++)//копируем значения
				m_first[i] = *(first + i);
			m_last = m_first + (last - first);
		}

		vector(std::initializer_list<Type> init) { //constructor
			m_first = new value_type[init.size()];//создаём массив
			for (size_t i = 0; i < init.size(); i++)//копируем значения
				m_first[i] = *(init.begin() + i);
			m_last = m_first + init.size();
		}

		vector(const vector& other) { //constructor
			m_first = new value_type[other.size()];//создаём массив
			for (size_t i = 0; i < other.size(); i++)//копируем значения
				m_first[i] = other[i];
			m_last = m_first + other.size();
		}

		vector(vector&& other) { //constructor
			m_first = other.begin();//переприсваиваем указатели
			m_last = other.end();
			other.m_first = nullptr;//затираем указатели в other
			other.m_last = nullptr;
		}

		~vector() { //destructor
			delete[] m_first;//удаляем массив
			m_first = nullptr;//затираем указатели
			m_last = nullptr;
		}

		vector& operator=(const vector& other) { //assignment operator
			if (this != &other) {
				delete[] m_first;//удаляем старый массив
				m_first = new value_type[other.size()];//создаём новый
				for (size_t i = 0; i < other.size(); i++)//копируем значения
					m_first[i] = other[i];
				m_last = m_first + other.size();
			}
			return *this;
		}

		vector& operator=(vector&& other) { //assignment operator
			delete[] m_first;//удаляем старый массив
			m_first = other.begin();//переприсваиваем указатели
			m_last = other.end();
			other.m_first = nullptr;//затираем указатели в other
			other.m_last = nullptr;
		}

		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last) { //assign method
			if (first == nullptr || last == nullptr) {
				throw "Error in assignment method: one of the input pointers is nullptr!";
			}
			else {
				delete[] m_first;//удаляем старый
				m_first = new value_type[last - first];//создаём новый
				for (size_t i = 0; i < (last - first); i++)//копируем значения
					m_first[i] = *(first + i);
				m_last = m_first + (last - first);
			}
		}

		void resize(size_t count) { //resize method
			if (count<size()) {//если количество элементов нужно уменьшить (удаляем)
				iterator m1_first = new value_type[count];//создаём новый
				for (size_t i = 0; i<count; i++)//копируем значения
					m1_first[i] = m_first[i];
				delete[] m_first;//удаляем старый
				m_first = m1_first;//перекидываем новый
				m_last = m_first + count;
			}
			if (count>size()) {//если количество элементов нужно увеличить добавляем
				iterator m1_first = new value_type[count];//создаём новый
				for (size_t i = 0; i<(this->size()); i++)//копируем значения
					m1_first[i] = m_first[i];
				delete[] m_first;//удаляем старый
				m_first = m1_first;//перекидываем новый
				m_last = m_first + count;
			}
		}

		iterator erase(const_iterator pos) { //erase method
			if (pos == nullptr) {//если указатель nullptr
				throw "Error in erase method: input pointer is nullptr!";
			}
			else {
				erase(pos, pos + 1);
			}
		}

		iterator erase(const_iterator first, const_iterator last) { //erase method
			if (first == nullptr || last == nullptr) {//если указатель nullptr
				throw "Error in erase method: one of the input pointers is nullptr!";
			}
			else {
				if (m_first == nullptr) {//если массив пуст
					throw "Error in erase method: vector is empty!";
				}
				iterator curr = m_first;//curr перемещается по старому массиву
				iterator ret;//для возврата
				size_t i = 0;//i перемещается по новому массиву
				iterator m1_first = new value_type[size() - (last - first)];//создаём новы массив
				while (curr != first) {//копируем, пока не дойдём до первого удаляемого
					m1_first[i] = m_first[curr - m_first];
					i++;
					curr++;
				}
				while (curr != last) {//пропускаем удаляемые элементы
					curr++;
				}
				ret = m1_first + i;//сохраняем для возврата
				while (curr != m_last) {//копируем элементы после удаляемого промежутка
					m1_first[i] = m_first[curr - m_first];
					i++;
					curr++;
				}
				delete[] m_first;//удаляем старый массив
				m_first = m1_first;//перекидываем новый
				m_last = m_first + i;
				return ret;
			}
		}

		iterator insert(const_iterator pos, const Type& value) { //insert methods
			if (pos == nullptr) {//если указатель nullptr
				throw "Error in insert method: input iterator is nullptr!";
			}
			else {
				size_t size_v = size();//запоминаем старый размер
				iterator curr = m_first;//curr перемещается по старому массиву
				iterator ret;//для возврата
				size_t i = 0;//i перемещается по новому массиву
				iterator m1_first = new value_type[size_v + 1];//создаём новый массив
				while (curr != pos) {//копируем элементы до вставляемого
					m1_first[i] = m_first[curr - m_first];
					i++;
					curr++;
				}
				m1_first[i] = value;//вставляем новый элемент
				ret = m1_first + i;//запоминаем указаель для возврата
				i++;//переходим к новому элементу
				while (curr != m_last) {//копируем элементы от вставляемого до конца
					m1_first[i] = m_first[curr - m_first];
					i++;
					curr++;
				}
				delete[] m_first;//удаляем старый массив
				m_first = m1_first;//перекидываем новый
				m_last = m_first + size_v + 1;
				return ret;
			}
		}

		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last) { //insert methods
			if (pos == nullptr || first == nullptr || last == nullptr) {//если указатель nullptr
				throw "Error in insert method: input iterator is nullptr!";
			}
			else {
				size_t size_v = size();//запоминаем старый размер
				iterator curr = m_first;//curr перемещается по старому массиву
				iterator ret;//для возврата
				size_t i = 0;//i перемещается по новому массиву
				iterator m1_first = new value_type[size_v + (last - first)];//создаём новый массив
				while (curr != pos) {//копируем элементы до вставляемой позиции
					m1_first[i] = m_first[curr - m_first];
					i++;
					curr++;
				}
				ret = m1_first + i;//сохраняем указатель для возврата
				for (int j = 0; j < (last - first); j++) {//вставляем элементы из диапазона
					m1_first[i] = *(first + j);
					i++;
				}
				while (curr != m_last) {//копируем элементы после вставляемого диапазона
					m1_first[i] = m_first[curr - m_first];
					i++;
					curr++;
				}
				delete[] m_first;//удаляем старый
				m_first = m1_first;//перекидываем указатель на новый
				m_last = m_first + size_v + (last - first);
				return ret;
			}
		}

		void push_back(const value_type& value) { //push_back methods
			size_t size_v = size();//запоминаем старый размер
			iterator m1_first = new value_type[size_v + 1];//создаём новый массив
			for (size_t i = 0; i<size_v; i++)//копируем все элементы
				m1_first[i] = m_first[i];
			m1_first[size_v] = value;//вставляем в конец новый элемент
			delete[] m_first;//удаляем старый массив
			m_first = m1_first;//перекидываем указатель на новый
			m_last = m_first + size_v + 1;
		}

		reference at(size_t pos) { //at method
			return checkIndexAndGet(pos);
		}

		const_reference at(size_t pos) const { //at method
			return checkIndexAndGet(pos);
		}

		reference operator[](size_t pos) { //[] operator
			return m_first[pos];
		}

		const_reference operator[](size_t pos) const { //[] operator
			return m_first[pos];
		}

		iterator begin() { //*begin method
			return m_first;
		}

		const_iterator begin() const { //*begin method
			return m_first;
		}

		iterator end() { //*end method
			return m_last;
		}

		const_iterator end() const { //*end method
			return m_last;
		}

		size_t size() const { //size method
			return m_last - m_first;
		}

		bool empty() const { //empty method
			return m_first == m_last;
		}

	private:
		reference checkIndexAndGet(size_t pos) const {
			if (pos >= size()) {
				throw std::out_of_range("out of range");
			}
			return m_first[pos];
		}

	private:
		iterator m_first;//указатель на первый элемент вектора
		iterator m_last;//указатель на последний элемент вектора
	};

	
}// namespace stepik