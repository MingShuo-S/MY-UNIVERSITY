#include<vector>
#include<stdexcept>
#include<iostream>

template<class T>
class CMinHeap
{
public:
    std::vector<T> minheap;
    int n;
public:
    CMinHeap() :n(0) {};
    CMinHeap(std::vector<T>& v, int m)
    {
    n = m;
    minheap = v;
    for (int i = n / 2; i >= 0; i--)
         AdjustDown(i);
    }
    
    void AdjustDown(int i)
    {
    int left = i * 2;
    int right = i * 2 + 1;
    int smallest = i;
    if (left < n && minheap[left] < minheap[smallest])
        smallest = left;
    if (right < n && minheap[right] < minheap[smallest])
    smallest = right;
    if (smallest != i)
    {
        T a = minheap[i];
        minheap[i] = minheap[smallest];
        minheap[smallest] = a;
        AdjustDown(smallest);
    }
    }

    T RemoveHead()
    {
    if(n<=0)
        throw std::runtime_error("Heap is empty");
    else{
    T p = minheap[0];
    minheap[0] = minheap[--n];
    AdjustDown(0);
    return p;
    }
    }

    void Putout()
    {
    for (int i = 0; i < n; i++)
        std::cout << minheap[i] << ' ';
    std::cout << std::endl;
    }

};

template <class T>
void heapsort(std::vector<T>& arr, int n)
{
    CMinHeap<T> heap(arr, n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = heap.RemoveHead();
    }
};
