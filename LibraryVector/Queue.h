#pragma once
#include <iostream>

using namespace std;

template <class T>
class Queue
{
private:
    T* m_arr;
    int m_sizeVector;
    int m_sizeMemory;

public:
    Queue();
    ~Queue();
    void Add(int Position, T Value);
    void AddFront(T Value);
    void AddBack(T Value);
    void Delete(int Position);
    void DeleteFront();
    void DeleteBack();
    int GetSizeVector();
    T GetBack();
    T GetFront();
};

//-----------------------------------------------------------------------------------------------------

template<class T>
inline T Queue<T>::GetBack()
{
    return m_arr[m_sizeVector - 1];
}

template<class T>
inline T Queue<T>::GetFront()
{
    return m_arr[0];
}

template <class T>
inline Queue<T>::Queue()
{
    m_arr = new T[1];
    m_sizeVector = 0;
    m_sizeMemory = 1;
}

template<class T>
inline Queue<T>::~Queue()
{
    delete[] m_arr;
}

template<class T>
inline void Queue<T>::Add(int Position, T Value)
{
    if (Position < 0 || Position > m_sizeVector)
    {
        cout << "\nAAA";
        exit(666);
    }

    if (m_sizeMemory == m_sizeVector)
    {
        m_sizeMemory *= 2;
        T* newArr = new T[m_sizeMemory];

        for (int i = 0; i < m_sizeVector; i++)
            newArr[i] = m_arr[i];
        delete[] m_arr;
        m_arr = newArr;
    }

    m_sizeVector++;
    for (int i = m_sizeVector - 1; i > Position; i--)
        m_arr[i] = m_arr[i - 1];
    m_arr[Position] = Value;
}

template<class T>
inline void Queue<T>::AddFront(T Value)
{
    this->Add(0, Value);
}

template<class T>
inline void Queue<T>::AddBack(T Value)
{
    this->Add(m_sizeVector, Value);
}

template<class T>
inline void Queue<T>::Delete(int Position)
{
    if (Position < 0 || Position >= m_sizeVector)
    {
        cout << "\nAAA";
        exit(666);
    }

    if (m_sizeMemory == m_sizeVector * 4)
    {
        m_sizeMemory /= 2;
        T* newArr = new T[m_sizeMemory];

        for (int i = 0; i < m_sizeVector; i++)
            newArr[i] = m_arr[i];
        delete[] m_arr;
        m_arr = newArr;
    }

    m_sizeVector--;
    for (int i = Position; i < m_sizeVector; i++)
        m_arr[i] = m_arr[i + 1];
}

template<class T>
inline void Queue<T>::DeleteFront()
{
    this->Delete(0);
}

template<class T>
inline void Queue<T>::DeleteBack()
{
    this->Delete(m_sizeVector - 1);
}

template<class T>
inline int Queue<T>::GetSizeVector()
{
    return m_sizeVector;
}
