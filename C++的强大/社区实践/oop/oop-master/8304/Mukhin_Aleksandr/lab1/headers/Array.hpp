#pragma once
#include <cstdint>
#include <bits/exception.h>
#include <stdexcept>
#include <iostream>
#include <memory>
#include "Unit.h"
#include "Iterator.hpp"

/*!
 * @brief Собственный класс-контейнер
 * @var Array::max_size количество элементов, которое вмещает в себя этот контейнер
 * @vat Array::object указатель на первый элемент контейнера
 * @tparam T элементы этого типа будет проинициализирован контейнер
 */
template<class T>
class Array{
public:
    Array() = default;

    /*!
     * @brief Конструктор
     * @param size размер контейнера
     */
    explicit Array(size_t size) : max_size(size) {
        object = new T[size]();
    }

    /*!
     * @brief Конструктор копирования
     * @param old_obj образец, по которому надо создать копию
     */
    Array(const Array& old_obj) {
        delete[] object;
        max_size = old_obj.max_size;
        object = new T[max_size];
        for (int i = 0; i < max_size; i++) {
            object[i] = old_obj.object[i];
        }
    }

    /*!
     * @brief Конструктор переноса
     * @param old_obj образец, данные из которого надо перенести
     */
    Array(Array&& old_obj) {
        max_size = old_obj.max_size;
        object = old_obj.object;
        for (int i = 0; i < max_size; i++) {
            object[i] = old_obj.object[i];
        }
    }

    /*!
     * @brief Оператор присваивания копированием
     * @param old_obj образец, откуда надо скопировать данные
     * @return экземпляр класса Array с новым сожержимым
     */
    Array& operator= (const Array& old_obj) {
        if (this != &old_obj) {
            delete[] object;
            max_size = old_obj.max_size;
            object = new T[max_size];
            for (int i = 0; i < max_size; i++) {
                object[i] = old_obj.object[i];
            }
        }
        return *this;
    }

    T& operator[] (size_t index) const{
        if (index < max_size) {
            return object[index];
        } else {
            throw std::out_of_range("Array index out of range!");
        }
    }

    bool operator== (Array const& second_object) {
        bool len = size() == second_object.size();
        if (len) {
            for (int i = 0; i < len; i++) {
                if (this[i] != second_object[i]) {
                    return false;
                }
            }
        }

        return len;
    }

    /*!
     * @brief Возвращает максимально возможный индекс в контейнеры
     * @return максимально возможный индекс в контейнеры
     */
    size_t size() {
        return max_size - 1;
    }

    ~Array() {
        delete[] object;
        max_size = 0;
        object = nullptr;
    }

    /*!
     * @brief Возвращает итератор на первый элемент массива
     * @return итератор на первый элемент массива
     */
    Iterator<T> begin() const {
        return Iterator(object);
    }

    /*!
     * @brief Возвращает итератор на последний элемент массива
     * @return итератор на последний элемент массива
     */
    Iterator<T> end() const {
        return Iterator(object + max_size);
    }


private:
    size_t max_size = 0;
    T* object = nullptr;
};
