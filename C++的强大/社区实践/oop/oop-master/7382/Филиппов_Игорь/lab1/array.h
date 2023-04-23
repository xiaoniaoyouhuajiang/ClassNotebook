#pragma once

#include <assert.h>
#include <algorithm> 
#include <cstddef> 
#include <iostream>

template<typename T>
class Array
{
public:
    explicit Array(const size_t size = 0)
            : m_array_(size ? new T[size]() : nullptr)
            , m_size_(size)
    {}

    Array(const Array& other)
            : m_array_(other.size() ? new T[other.size()]() : nullptr)
            , m_size_(other.size())
    {

        std::copy(other.m_array_, other.m_array_ + other.size(), m_array_);
    }

    Array(Array&& other) noexcept
        : m_array_(nullptr)
        , m_size_(0)
    {
        std::swap(m_array_, other.m_array_);
        std::swap(m_size_, other.m_size_);
    }

    Array& operator=(const Array& other)
    {
        if (this != &other)
        {
            auto m_array_saver = m_array_;

            try
            {
                m_array_ = other.size() ? new T[other.size()]() : nullptr;
                std::copy(other.m_array_, other.m_array_ + other.size(), m_array_);
            }
            catch (std::exception& e)
            {
                if (m_array_saver != m_array_)
                {
                    delete[] m_array_;
                    m_array_ = m_array_saver;
                }

                throw;
            }

            delete[] m_array_saver;
            m_size_ = other.size();
        }

        return *this;
    }

    Array& operator=(Array&& other) noexcept
    {
        if (this != &other)
        {
            delete[] m_array_;
            m_size_ = 0;

            std::swap(m_array_, other.m_array_);
            std::swap(m_size_, other.m_size_);
        }

        return *this;
    }

    ~Array()
    {
        delete[] m_array_;
    }

    size_t size() const
    {
        return m_size_;
    }

    T& operator [](const size_t index)
    {
        assert(index < m_size_);

        return m_array_[index];
    }

public:
    T* m_array_;
    size_t m_size_;
};