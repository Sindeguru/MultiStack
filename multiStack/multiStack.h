#include <iostream>
#include "stack.h"
#include "math.h"

using namespace std;
template <class T>
class MultiStack
{
protected:
  T* data;
  int length; //of full date 
  int stackCount;

  TStack<T>* stacks;

  T** oldData;

  void StackRelocation(int i);
   
public:
  MultiStack(int size = 1, int _stackCount = 1);
  MultiStack(MultiStack<T>& _v);
  ~MultiStack();

  MultiStack<T>& operator =(MultiStack<T>& _v);

  void Push(T Elem, int i); // 
  T Get(int i); // or T pop() in stack
  bool IsEmpty(int i) const;
  bool IsFull(int i) const;

  template<class T1>
  friend ostream& operator<< (ostream& ostr, const MultiStack<T1>& A);
  template<class T1>
  friend istream& operator>> (istream& istr, MultiStack<T1>& A);

  int GetSize();

};

template<class T>
inline void MultiStack<T>::StackRelocation(int index)
{
  int freeSize = 0;
  for (int i = 0; i < stackCount; i++)
    freeSize += stacks[i].GetSize() - stacks[i].GetCount();

  if (freeSize == 0)
    throw - 2;
  
  int count = int(floor(double(freeSize) / stackCount));
  int* sizes = new int[this->stackCount];

  for (int i = 0; i < (stackCount - 1); i++)
    sizes[i] = stacks[i].GetCount() + count;

  int c = stacks[stackCount - 1].GetCount();
  sizes[this->stackCount - 1] = c+ (freeSize - (count * (this->stackCount)));

  T** newData = new T * [stackCount];
 
  int k = 0;
  for (int i = 0; i < stackCount; i++)
  {
    newData[i] = &(data[k]);
    k = k + sizes[i];
  }

  for (int i = 0; i < stackCount; i++)
  {
    if (newData[i] == oldData[i])
    {
      stacks[i].SetData(newData[i], sizes[i], stacks[i].GetCount());
    }
    else if (newData[i] < oldData[i])
    {
      for (int j = 0; j < stacks[i].GetCount(); j++)
      {
        newData[i][j] = oldData[i][j];
      }
      stacks[i].SetData(newData[i], sizes[i], stacks[i].GetCount());
    }
    else if (newData[i] > oldData[i])
    {
      int k = i;
      for (; k < stackCount; k++)
        if (newData[k] > oldData[k])
          continue;
        else
          break;
      k--;

      for (int s = k; s <= i; s--)
      {
        for (int j = stacks[i].GetCount() - 1; j >= 0; j--)
        {
          newData[s][j] = oldData[s][j];
        }
        stacks[s].SetData(newData[s], sizes[s], stacks[s].GetCount());
      }
    }
  }
  T** buf = oldData;
  oldData = newData;
  delete[] newData;
  delete[] sizes;
}


template<class T>
inline MultiStack<T>::MultiStack(int size, int _stackCount)
{
  if ((size > 0)&&(_stackCount>0))
  {
    this->length = size;
    this->stackCount = _stackCount;

    data = new T[length];
    for (int i = 0; i < length; i++)
      data[i] = 0;
    
    int count = int(floor(double(size) / stackCount));
    int* sizes = new int[this->stackCount];

    for (int i = 0; i < (stackCount - 1); i++)
    {
      sizes[i] = count;
    }
     
    oldData = new T * [stackCount];
    sizes[stackCount - 1] = size - (count * (stackCount - 1));
    this->stacks = new TStack<T>[stackCount];
    int k = 0;
    for (int i = 0; i < stackCount; i++)
    {
      this->stacks[i].SetData(&(data[k]), sizes[i], 0);
      this->oldData[i] = &(data[k]);
      k = k + sizes[i];
    }
  }
  else
    throw - 1;
}

template<class T>
inline MultiStack<T>::MultiStack(MultiStack& _v)
{
  length = _v.length;
  stackCount = _v.stackCount;

  data = new T[length];
  for (int i = 0; i < length; i++)
    data[i] = _v.data[i];

  stacks = new TStack<T>[stackCount];
  for (int i = 0; i < stackCount; i++)
    stacks[i] = _v.stacks[i]; 
}

template<class T>
inline MultiStack<T>::~MultiStack()
{
  length = 0;
  stackCount = 0;

  if (data != 0)
  {
    delete[] data;
    delete[] stacks;
    data = 0;
  }
}

template<class T>
inline MultiStack<T>& MultiStack<T>::operator=(MultiStack<T>& _v)
{
  if (this == &_v)
    return *this;

  length = _v.length;
  
  delete[] data;
  delete[] stacks;
  data = new T[length];
  for (int i = 0; i < length; i++)
    data[i] = _v.data[i];

  stacks = new TStack<T>[stackCount];
  for (int i = 0; i < stackCount; i++)
    stacks[i] = _v.stacks[i];

  return *this;
}

template<class T>
inline void MultiStack<T>::Push(T d, int i)
{
  if (i<0 || i >=stackCount)
    throw - 1;

  if (stacks[i].IsFull())
    StackRelocation(i);

  stacks[i].Push(d);

}

template<class T>
inline T MultiStack<T>::Get(int i)
{
  if ((i >= 0) && (i <= stackCount))
    throw - 1;
  if (stacks[i]->IsEmpty())
    throw - 2;

  T d = stacks[i].Get();
  return d;
}

template<class T>
inline bool MultiStack<T>::IsEmpty(int i) const
{
  if ((i >= 0) && (i <= stackCount))
    throw - 1;
  return stacks[i]->IsEmpty();
}

template<class T>
inline bool MultiStack<T>::IsFull(int i) const
{
  if ((i >= 0) && (i <= stackCount))
    throw - 1;
  return stacks[i]->IsFull();
}

template<class T>
inline int MultiStack<T>::GetSize()
{
  return length;
}

template<class T1>
inline ostream& operator<<(ostream& ostr, const MultiStack<T1>& A)
{
  for (int i = 0; i < A.stackCount; i++)
    ostr << (A.stacks[i]) << endl;
return ostr; 
}

template<class T1>
inline istream& operator>>(istream& istr, MultiStack<T1>& A)
{
  int stCount = 0;
  istr >> stCount;
  int size = 0;
  istr >> size;
  A.Resize(size, stCount);
  for (int i = 0; i < stCount; i++)
    istr >> A.stacks[i];
  return istr;
}
