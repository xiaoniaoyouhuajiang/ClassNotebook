#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template<typename T>
class Array{
public:
    // (default) constructor
    Array(const size_t size = 0): 
    m_size(size), m_array(m_size ? new T[m_size]() : nullptr)
    {}
    
    //деструктор
    ~Array(){
		delete[] m_array;
        m_size = 0;
	}
    
    // Конструктор копирования
    //используется для создания объекта через копирование существующего объекта
    Array(const Array &array) : //выполняется инициализация объекта через ссылку 
        m_size(array.m_size), m_array(m_size ? new T[m_size]() : nullptr)
        {
		    std::copy(array.m_array, array.m_array + array.m_size, m_array);//ф-ция библиотеки <algorithm>, копирует ряд элементов 
        }                                                                   //copy(first, last, d_first)
    
    // Конструктор перемещения
    //работа заключается в перемещении ресурсов из одного объекта в другой вместо их копирования.
    Array(Array && x){
            this->m_size = x.m_size;
            this->m_array = x.m_array;
            x.m_array = nullptr; // помечает другие объекты как пустые
            x.m_size = 0;
    }
    
    // Оператор присваивания
	Array& operator = (const Array & array){
        if (this != &array) {           // если объект не вызывается сам по себе
            T* temp= new T[array.m_size];
            std::unique_ptr<T[]> ptr(temp); //умный указатель(получает единоличное владение объектом через его указатель и разрушает объект через его указатель, когда unique_ptr выходит из области видимости
            //обеспечивает безопастность исключений
            std::copy(array.m_array,array.m_array+array.m_size,ptr.get());//get() возвращает указатель на управляемый объект
            delete[] m_array; 
            this->m_size = array.m_size;
            this->m_array = ptr.release(); // realise() возвращает указатель на управляемый объект и освобождает собственность
        }
        return *this;//возвращает ссылку на себя
    }
	
    const size_t size() const{
        return m_size;
    }
    
    T& operator [](const size_t index){// operator[] обеспечивает индексированный доступ к управляемому массиву
        assert(index < m_size); //если false, вызывает abort()
        return m_array[index];
    }

private:
    size_t m_size;
    T* m_array;
};
