#pragma once

namespace gindemit
{
    template<typename T>
    class vector
    {
    public:
        vector() :
            vector(4)
        {
        }
        vector(int capacity) :
            m_size(0),
            m_capacity(capacity)
        {
            m_values = new T[m_capacity];
        }
        vector(int count, T fillValue) :
            vector(count * 2)
        {
            for (int i = 0; i < count; ++i)
            {
                m_values[i] = fillValue;
            }
            m_size = count;
        }

        int size()
        {
            return m_size;
        }
        T& operator[](int index)
        {
            return m_values[index];
        }
        void push_back(T value)
        {
            if (m_size == m_capacity)
            {
                T* new_values = new T[m_capacity * 2];
                m_capacity *= 2;
                for (int i = 0; i < m_size; ++i)
                {
                    new_values[i] = m_values[i];
                }
                delete m_values;
                m_values = new_values;
            }
            m_values[m_size++] = value;
        }
        T pop_back()
        {
            return m_values[m_size--];
        }
        void insert(int index, T value)
        {
            m_values[index] = value;
        }
        void erase(int index)
        {
            while (index < m_size)
            {
                m_values[index] = m_values[index + 1];
                index++;
            }
        }

    private:
        int m_size;
        int m_capacity;
        T *m_values;
    };

}