#pragma once
#include <iostream>
#include <vector>
#include "Queue.h"

using namespace std;

template <class T>
class MyVector
{
private:
    T* m_arr;
    int m_sizeVector;
    int m_sizeMemory;

    class Run
    {
    public:
        int indexStart;
        int length;
    };
    int GetMinrun(int n);
    void sortInsertionPart(int* arr, int indexFirst, int indexLast);
    void merge(int* arr, int firstIndexStart, int firstLenght, int secondIndexStart, int secondLenght);
public: 
    MyVector();
    ~MyVector();
    void Add(int Position, T Value);
    void AddFront(T Value);
    void AddBack(T Value);
    void Delete(int Position);
    void DeleteFront();
    void DeleteBack();
    void Print();
    int GetSizeVector();
    int GetSizeMemory();
    void SortTimsort();
    void BubbleSort();
    void RandomMix();
    void RandomFill(int NewSizeVector);
    bool IsSort();
    void ClearVector();
};

//-----------------------------------------------------------------------------------------------------

template <class T>
inline MyVector<T>::MyVector()
{
    m_arr = new T[1];
    m_sizeVector = 0;
    m_sizeMemory = 1;
}

template<class T>
inline MyVector<T>::~MyVector()
{
    delete[] m_arr;
}

template<class T>
inline void MyVector<T>::Add(int Position, T Value)
{
    if (Position < 0 || Position > m_sizeVector)
    {
        cout << "\nErorr in MyVector::Add()";
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
inline void MyVector<T>::Print()
{
    if (m_sizeVector == 0)
    {
        cout << "[ Empty vector ]";
        return;
    }
    cout << "[ ";
    for (int i = 0; i < m_sizeVector; i++)
        cout << m_arr[i] << " ";
    cout << " ]";

}

template<class T>
inline void MyVector<T>::AddFront(T Value)
{
    this->Add(0, Value);
}

template<class T>
inline void MyVector<T>::AddBack(T Value)
{
    this->Add(m_sizeVector, Value);
}

template<class T>
inline void MyVector<T>::Delete(int Position)
{
    if (Position < 0 || Position >= m_sizeVector)
    {
        cout << "\nErorr in MyVector::Delete()";
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
inline void MyVector<T>::DeleteFront()
{
    this->Delete(0);
}

template<class T>
inline void MyVector<T>::DeleteBack()
{
    this->Delete(m_sizeVector - 1);
}

template<class T>
inline int MyVector<T>::GetSizeVector()
{
    return m_sizeVector;
}

template<class T>
inline int MyVector<T>::GetSizeMemory()
{
    return m_sizeMemory;
}

template<class T>
inline int MyVector<T>::GetMinrun(int n)
{
    int r = 0;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

template<class T>
inline void MyVector<T>::sortInsertionPart(int* arr, int indexFirst, int indexLast)
{
    for (int i = indexFirst + 1; i < indexLast; ++i)
    {
        int current = arr[i];
        int j = i - 1;
        while ((j >= indexFirst) && (current < arr[j]))
        {
            int num = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = num;
            --j;
        }
    }
}

template<class T>
inline void MyVector<T>::merge(int* arr, int firstIndexStart, int firstLenght, int secondIndexStart, int secondLenght)
{
    int* temporary = new int[firstLenght];

    for (int i = 0; i < firstLenght; i++)
        temporary[i] = arr[firstIndexStart + i];

    int firstIndexMerge = 0;
    int secondIndexMerge = secondIndexStart;
    int arrIndex = firstIndexStart;

    while (arrIndex < secondIndexStart + secondLenght - 1)
    {
        if (arr[secondIndexMerge] > temporary[firstIndexMerge])
        {
            arr[arrIndex] = temporary[firstIndexMerge];
            firstIndexMerge++;
        }
        else if (arr[secondIndexMerge] <= temporary[firstIndexMerge])
        {
            arr[arrIndex] = arr[secondIndexMerge];
            secondIndexMerge++;

        }
        if (secondIndexMerge == secondIndexStart + secondLenght)
        {
            if (firstIndexMerge != firstLenght)
            {
                for (int i = firstIndexMerge; i < firstLenght; i++)
                    arr[i - firstIndexMerge + arrIndex + 1] = temporary[i];
                arrIndex = secondIndexStart + secondLenght;
            }
        }
        if (firstIndexMerge == firstLenght)
        {
            arrIndex = secondIndexStart + secondLenght;
        }
        arrIndex++;
    }
    delete[] temporary;
}

template<class T>
inline void MyVector<T>::SortTimsort()
{
    int minrun = GetMinrun(m_sizeVector);//
    Queue <Run> queueRun;
    //queueRun.reserve(m_sizeVector / minrun);//

    int indexStart = 0;

    while (indexStart < m_sizeVector - 1)//
    {
        int indexFirst = indexStart;
        int indexLast = indexFirst + 1;

        bool nextStep = true;
        while (nextStep)
        {
            if (m_arr[indexFirst] > m_arr[indexLast])
                nextStep = false;
            if (indexLast - indexStart < minrun)
                nextStep = true;
            if (indexLast == m_sizeVector - 1)//
                nextStep = false;

            if (nextStep)
            {
                indexFirst++;
                indexLast++;
            }
        }

        if (indexLast == m_sizeVector - 2)//
        {
            indexLast++;
        }

        sortInsertionPart(m_arr, indexStart, indexLast + 1);

        Run newRun;
        newRun.indexStart = indexStart;
        newRun.length = indexLast - indexStart;
        queueRun.AddBack(newRun);

        indexStart = indexLast;

        while (queueRun.GetSizeVector() >= 3)
        {
            Run x = queueRun.GetBack();
            queueRun.DeleteBack();
            Run y = queueRun.GetBack();
            queueRun.DeleteBack();
            Run z = queueRun.GetBack();
            queueRun.DeleteBack();

            if (z.length >= x.length + y.length && y.length >= x.length)
            {
                queueRun.AddBack(z);
                queueRun.AddBack(y);
                queueRun.AddBack(x);
                break;
            }
            else if (z.length >= x.length + y.length)
            {
                if (x.indexStart < y.indexStart)
                {
                    swap(x.indexStart, y.indexStart);
                    swap(x.length, y.length);
                }
                merge(m_arr, y.indexStart, y.length, x.indexStart, x.length);
                queueRun.AddBack(z);
                y.length = y.length + x.length;
                queueRun.AddBack(y);
            }
            else
            {
                if (y.indexStart < z.indexStart)
                {
                    swap(y.indexStart, z.indexStart);
                    swap(y.length, z.length);
                }
                merge(m_arr, z.indexStart, z.length, y.indexStart, y.length);
                z.length = z.length + y.length;
                queueRun.AddBack(z);
                queueRun.AddBack(x);
            }
        }

    }

    while (queueRun.GetSizeVector() > 1)
    {
        Run x = queueRun.GetFront();
        queueRun.DeleteFront();
        Run y = queueRun.GetFront();
        queueRun.DeleteFront();
        if (x.indexStart > y.indexStart)
        {
            swap(x.indexStart, y.indexStart);
            swap(x.length, y.length);
        }
        if (y.indexStart != x.indexStart + x.length)
        {
            queueRun.AddBack(y);
            queueRun.AddBack(x);
            continue;
        }
        merge(m_arr, x.indexStart, x.length, y.indexStart, y.length);
        x.length = x.length + y.length;
        queueRun.AddBack(x);
    }
}

template<class T>
inline void MyVector<T>::BubbleSort()
{
    for (int i = 0; i < m_sizeVector - 1; i++) {
        for (int j = 0; j < m_sizeVector - i - 1; j++) {
            if (m_arr[j] > m_arr[j + 1]) {
                T temp = m_arr[j];
                m_arr[j] = m_arr[j + 1];
                m_arr[j + 1] = temp;
            }
        }
    }
}

template<class T>
inline void MyVector<T>::RandomMix()
{
    for (int i = 0; i < (m_sizeVector + 1) / 2; i++)
        swap(m_arr[i], m_arr[(rand() % m_sizeVector)]);
}

template<class T>
inline void MyVector<T>::RandomFill(int NewSizeVector)
{
    ClearVector();
    m_sizeVector = NewSizeVector;
    while (m_sizeMemory < m_sizeVector)
        m_sizeMemory *= 2;
    m_arr = new T[m_sizeMemory];
    for (int i = 0; i < m_sizeVector; i++)
        m_arr[i] = rand() % 1000;


    //for (int)
}

template<class T>
inline void MyVector<T>::ClearVector()
{
    m_sizeMemory = 1;
    m_sizeVector = 0;
    delete[] m_arr;
    m_arr = new T[1];
}

template<class T>
inline bool MyVector<T>::IsSort()
{
    bool mistake = false;
    for (int i = 0; i < m_sizeVector - 1; i++)
        if (m_arr[i] > m_arr[i + 1])
            mistake = true;
    return !mistake;
}

//_________-__________________________________________________________________________________\\
