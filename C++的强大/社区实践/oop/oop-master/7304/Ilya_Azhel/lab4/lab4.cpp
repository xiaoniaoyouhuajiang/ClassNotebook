#include <iostream>

using namespace std;

namespace stepik
{
    template <typename Type>
    class shared_ptr
    {
        
        template<class V> friend class shared_ptr;
        typedef long* l_ptrl;
        
    private:
        Type* m_ptr;    // Указатель на управляемый объект
        l_ptrl m_count; // Счетчик ссылок
        
    public:
        /* установка значение Type *ptr и счетчика ссылок = 1. */
        explicit shared_ptr(Type *ptr = 0)
        : m_ptr(ptr), m_count((ptr != nullptr) ? new long(1) : nullptr) {}
        
        // ---------------------------------------
        
        /* Создает новый shared_ptr на существующий объект.
         * Установка m_ptr и m_count такими же, как в other.
         * Увеличение счетчика на 1, т.к. новая ссылка на other*/
        shared_ptr(const shared_ptr & other) :
        m_ptr(other.m_ptr), m_count(other.m_count)
        {
            if (use_count())
                (*m_count)++;
        }
        
        template <typename V>
        shared_ptr(const shared_ptr<V> & other) :
        m_ptr(other.m_ptr), m_count(other.m_count)
        {
            if (use_count())
                (*m_count)++;
            
        }
        // ---------------------------------------
        
        
        /* Уничтожаем ссылку на объект. Уменьшаем
         * m_count. Если m_count = 0, освобождаем память и
         * уничтожаем объект. */
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
        // ---------------------------------------
        
        /* Если уже имеет существующее значение, нужно уменьшить его количество ссылок.
         * Затем копируем указатели other.m_ptr и other.m_ptr.
         * Так как мы создали новую ссылку, нам нужно увеличить m_count */
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
        // ---------------------------------------
        
        
        // Проверка хранения элементов
        explicit operator bool() const
        {
            return m_ptr != nullptr;
        }
        
        // доступ к хранимым элемента
        Type* get() const
        {
            return m_ptr;
        }
        
        // Количество объектов shared_ptr, ссылающиеся на тот же объект
        long use_count() const
        {
            return (m_ptr != nullptr) ? *m_count : 0;
        }
        
        // Возвращает ссылку на управляемый объект
        Type& operator*() const
        {
            return *m_ptr;
        }
        
        // Возвращает указатель на управляемый объект
        Type* operator->() const
        {
            return m_ptr;
        }
        
        // обмен указателей
        void swap(shared_ptr& x) noexcept
        {
            std::swap(m_ptr, x.m_ptr);
            std::swap(m_count, x.m_count);
        }
        
        // Функция, которая замещает указатель на другой
        void reset(Type *m_ptr = 0)
        {
            shared_ptr<Type>(m_ptr).swap(*this);
        }
        
        // Оператор равенства
        template <typename TN>
        bool operator ==(const shared_ptr<TN> &other) const {
            return (void*)m_ptr == (void*)other.m_ptr;
        }
        
        bool operator ==(const shared_ptr &other)const {
            return (void*)m_ptr == (void*)other.m_ptr;
        }
        // ---------------------------------------
        
    };
}


int main(){
    shared_ptr<int> ptr(new int(5));
    
    shared_ptr<int> newPtr(ptr);
    
    //ptr.reset();
    
    cout << *newPtr << endl;
    
    if(ptr == newPtr){
        cout << "equal" << endl;
    }
    
    
    
}
