#pragma once
#include <iostream>

using namespace std;
template <class T>
class TStack
{
protected:
  T* arr;
  int length;
  int vs;

public:
  TStack(int size = 0);
  TStack(TStack<T>& s);
  ~TStack();

  TStack<T>& operator =(TStack<T>& _v);

  void Push(T Elem); 
  T Get(); 
  void SetData(T* _arr, int size, int _vs);

  bool IsEmpty();
  bool IsFull();

  int GetSize();
  int GetCount();

  template<class T1>
  friend ostream& operator<< (ostream& ostr, const TStack<T1>& A);
  template<class T1>
  friend istream& operator>> (istream& istr, TStack<T1>& A);
};

template<class T>
inline TStack<T>::TStack(int size)
{
  if (size >= 0)
  {
    this->length = size;
    arr = new T[length];
    this->vs = -1;
  }
  else
    throw logic_error("size of stack must be >= 0");
}

template<class T>
inline TStack<T>::TStack(TStack& s)
{
  length = s.length;
  vs = s.vs;
  arr = new T[length];
  for (int i = 0; i < vs; i = i + 1)
    arr[i] = s.arr[i];
}

template<class T>
inline TStack<T>::~TStack()
{
  length = 0;
  if (arr != 0)
    delete[] arr;
  arr = 0;
  vs = -1;
}

template<class T>
inline TStack<T>& TStack<T>::operator=(TStack<T>& _v)
{
  if (this == &_v)
    return *this;

  length = _v.length;
  delete[] arr;
  arr = new T[length];
  for (int i = 0; i < vs; i++)
    arr[i] = _v.arr[i];
  vs = _v.vs;
  return *this;
}

template<class T>
inline void TStack<T>::Push(T Elem)
{
  if (IsFull())
    throw "isfull";

  vs++;
  arr[vs] = Elem;

}

template<class T>
inline T TStack<T>::Get()
{
  if (this->empty())
    throw "Stack is empty";
  arr[vs] = 0;
  vs--;

  return arr[vs];
}

template<class T>
inline bool TStack<T>::IsEmpty()
{
  if (vs < 0)
    return true;
  else
    return false;
}

template<class T>
inline bool TStack<T>::IsFull()
{
  return (vs + 1) >= length;
}

template<class T>
inline int TStack<T>::GetSize()
{
  return length;
}

template<class T>
inline int TStack<T>::GetCount()
{
  return vs;
}

template<class T>
inline void TStack<T>::SetData(T* _arr, int size, int _vs)
{
  length = size;
  arr = _arr;
  vs = _vs;
}

template<class T1>
inline ostream& operator<<(ostream& ostr, const TStack<T1>& A)
{
  for (int i = 0; i < A.vs; i++)
    ostr << A.arr[i] << endl;
  return ostr;
}

template<class T1>
inline istream& operator>>(istream& istr, TStack<T1>& A)
{
  int Count = 0;
  istr >> Count;
  for (int i = 0; i < count; i++)
  {
    T1 d;
    istr >> d;
    A.Push(d);
  }
  return istr;
}