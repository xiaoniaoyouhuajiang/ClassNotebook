# Coded by @kovinevmv
# Last Update 30.04.2018

#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <iostream>
#include <memory>
using namespace std;


template<typename T>

class Array
{
private:
	size_t m_size;
	std::unique_ptr <T[]> m_array;
	void print(const char* message)
	{
		cout << "[" << this << "] " << message << "\n";
	}
	
public:
	// Стандартный конструтктор
	Array(const size_t size = 0)
		: m_size(size)
		, m_array(m_size ? new T[m_size]() : nullptr)
	{
		print("default constr");
	}

	// Конструктор копирования
	Array(const Array& obj)
		: m_size(obj.m_size)
		, m_array(m_size ? new T[m_size]() : nullptr)
	{
		for (size_t i = 0; i < m_size; ++i) 
			m_array[i] = obj.m_array[i];
		print("copy constr");
	}

	// Оператор присваивания
	Array& operator=(Array obj)
	{
		std::swap(m_size, obj.m_size);
		std::swap(m_array, obj.m_array);
		print("operator=");
		return*this;
	}

	// Конструктор перемещения
	Array(Array&& obj)
	{
		m_array = move(obj.m_array);
		swap(m_size, obj.m_size);
		obj.m_size = 0;

		print("move constr");
	}

	// Размер массива
	const size_t size() const
	{
		return m_size;
	}

	// Оператор индексирования
	T& operator [](const size_t index)
	{
		assert(index < m_size);
		return m_array[index];
	}

	// Вывод элементов массива
	void print()
	{
		cout << "\nArray\n";
		for (int i=0;  i< m_size; i++)
			cout << m_array[i] << " ";
		cout << endl;
	}
	


};

// Привести элемент к типу rvalue
Array<int> GetRValue(Array<int> A) 
{
	return A;
}

int main()
{

	// ================ Test ================ // 
	cout << "v1 initial: ";
	Array <int> v1(10);

	cout << "v2 initial: ";
	Array <int> v2;

	cout << "############################\n";
	cout << "Assigment\n\n";
	cout << "v1 before copy:";
	v1.print();
	cout << "v2 before copy:";
	v2.print();

	cout << "Start Copy\n";
	v2 = v1;
	cout << "End copy\n" << endl;

	cout << "v1 after copy:";
	v1.print();
	cout << "v2 after copy:";
	v2.print();

	
	cout << "############################\n";
	cout << "Copy\n\n";

	cout << "v3 initial: ";
	Array <int> v3(20);
	cout << "Start Copy\n";
	cout << "v4 initial: ";
	Array <int> v4(v3);
	cout << "End copy\n" << endl;

	cout << "v3 after copy:";
	v3.print();
	cout << "v4 after copy:";
	v4.print();



	cout << "############################\n";
	cout << "Move\n\n";
	cout << "Start Move\n";
	cout << "v5 initial: ";
	Array <int> v5 = GetRValue(v4);
	cout << "End Move\n" << endl;

	cout << "v5 after move:";
	v5.print();
	cout << "v4 after move:";
	v4.print();

	cout << "############################\n";
	cout << "Empty copy\n\n";

	cout << "v6 initial: ";
	Array <int> v6;
	cout << "Start Copy\n";
	cout << "v7 initial: ";
	Array <int> v7 = v6;
	cout << "End Copy\n" << endl;
	
	// ================ END Test ================ // 

	system("pause");
    return 0;
}
