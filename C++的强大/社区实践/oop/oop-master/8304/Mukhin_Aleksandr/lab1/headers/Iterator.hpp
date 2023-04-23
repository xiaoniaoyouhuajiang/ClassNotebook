#ifndef LAB1_ITERATOR_HPP
#define LAB1_ITERATOR_HPP

template<class T>
class Iterator {
    T* current = nullptr;
public:
    explicit Iterator(T* object) : current(object) {}

    T& operator++() {
        if (current + 1 != nullptr) {
            return *++current;
        }
    }

    bool operator!=(const Iterator& second_object) {
        return current != second_object.current;
    }

    T& operator*() {
        if (current != nullptr) {
            return *current;
        }
    }
};


#endif
