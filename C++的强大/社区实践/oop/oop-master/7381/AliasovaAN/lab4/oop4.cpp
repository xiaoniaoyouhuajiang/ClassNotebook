#include "pch.h"
#include <iostream>

namespace stepik {
	template <typename T>
	class shared_ptr { 
	public:
		explicit shared_ptr(T *ptr = 0) {//конструктор
			pointer = ptr;
			if (pointer != nullptr)
				count = new long(1);
			else
				count = nullptr;
		}
		
		~shared_ptr() {
			if (pointer != nullptr) {
				if ((*count) == 1) {
					delete pointer;
					delete count;
				}
				else
					(*count)--;
			}
		}

		template <class Y>
		friend class shared_ptr;

		template <class Y>
		shared_ptr(const shared_ptr<Y> & other) : pointer(other.pointer), count(other.count) {
			if (pointer)
				(*count)++;
		}
	
		template <class Y>
		shared_ptr& operator=(const shared_ptr<Y> & other) {
			shared_ptr<T>(other).swap(*this);
			return *this;
		}

		template <class Y>
		bool operator==(const shared_ptr<Y> & other) const {
			return pointer == other.pointer;
		}

		explicit operator bool() const { //Проверяет *this управляет объектом, то есть ли get() != 0.
			if (pointer != nullptr)
				return true;
			else
				return false;
		}

		T* get() const { //Возвращает указатель на управляемый объект.
			return pointer;
		}

		long use_count() const {//Возвращает количество различных shared_ptr экземпляров
			if (count)
				return (*count);
			else
				return 0;
		}
/*Возвращает количество различных shared_ptrэкземпляров ( это включено) управляющий текущий объект. Если нет управляемого объекта, 0 возвращаются. */

		T& operator*() const { //оператор разыменововыния
			return *pointer;
		}//возвр ссылку

		T* operator->() const { // оператор, чтобы исп
			return pointer;
		}//возвр указатель на управляемый объект.
	

		void swap(shared_ptr& x) noexcept { //обмен содержимым, ф-ция не генерирует исключения
			std::swap(pointer, x.pointer);
			std::swap(count, x.count);
		}
	.
		void reset(T *ptr = 0) { //заменяет объект, которым владеет
			shared_ptr<T>(ptr).swap(*this);
		}


	private:
		T    * pointer;
		long * count;
	};
}