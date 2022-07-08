#ifndef VECTOR_H
#define VECTOR_H

template <class T>
class Vector {
    T* m_array;
    int m_size;
    int m_length;
    int m_lastIndex;
public:
    Vector() {
        m_array = 0;
        m_size = 0;
        m_length = 0;
        m_lastIndex = -1;
    }
    ~Vector() { if (m_array) delete[] m_array; }

    T& operator[](int index)
    {
        if (index >= m_size)
        {
            Resize(index+1);
            m_length++;
        }
        if (m_lastIndex < index)
            m_lastIndex = index;
        return m_array[index];
    }
    int Size() { return m_length; }
    void PushBack(const T& item) {
        m_lastIndex++;
        if (m_lastIndex >= m_size)
            Resize(m_lastIndex + 1);
        m_array[m_lastIndex] = item;
        m_length++;
    }
    void Clear()
    {
        delete[] m_array;
        m_array = 0;
        m_size = 0;
        m_length = 0;
        m_lastIndex = -1;
    }
private:
    // This function will resize array to at least the minimal size
    void Resize(int minSize)
    {
        int newSize = m_size == 0 ? 8 : m_size;

        while (newSize < minSize)
            newSize *= 2;

        T* newArray = new T[newSize];
        for (int i = 0; i < m_size; i++)
            newArray[i] = m_array[i];

        if (m_array)
            delete[] m_array;

        m_array = newArray;
        m_size = newSize;
    }
};

#endif
