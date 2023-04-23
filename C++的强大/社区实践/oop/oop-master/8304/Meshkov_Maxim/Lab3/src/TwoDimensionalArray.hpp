#pragma once

#include <memory>

template <typename T>
class TwoDimensionalArray {
public:
    TwoDimensionalArray(int width, int height)
        : m_width(width), m_height(height), m_array(new T[width * height]) // TODO check sizes
    {}
    TwoDimensionalArray(const TwoDimensionalArray &other) {
        *this = other;
    }
    TwoDimensionalArray(TwoDimensionalArray &&other) noexcept {
        *this = other;
    }
    TwoDimensionalArray &operator=(const TwoDimensionalArray &other) {
        if (this != &other) {
            m_width = other.m_width;
            m_height = other.m_height;
            m_array.reset(new T[m_width * m_height]);
            for (size_t i = 0; i < m_width * m_height; i++) {
                m_array[i] = other.m_array[i];
            }
        }
        return *this;
    }
    TwoDimensionalArray &operator=(TwoDimensionalArray &&other) noexcept {
        if (this != &other) {
            m_width = other.m_width;
            m_height = other.m_height;
            m_array = std::move(other.m_array);
        }
        return *this;
    }

    int getWidth() const {
        return m_width;
    }
    int getHeight() const {
        return m_height;
    }

    T &at(int row, int col) {
        // TODO checks?
        return m_array[row * m_width + col];
    }
    const T &at(int row, int col) const {
        // TODO checks?
        return m_array[row * m_width + col];
    }

private:
    int m_width;
    int m_height;
    std::unique_ptr<T[]> m_array;
};
