#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Custom Priority Queue
class PriorityQueue
{
    vector<int> pq;

public:
    PriorityQueue()
    {
    }
    ~PriorityQueue()
    {
    }

    bool isEmpty()
    {
        return pq.size() == 0;
    }
    int getSize()
    {
        return pq.size();
    }
    int getMin()
    {
        if (!this->isEmpty())
            return pq.at(0);
        else
            return -1;
    }
    void display()
    {
        for (auto x : pq)
            cout << x << "  ";
        cout << "\n";
    }

private:
    void swap(int x, int y)
    {
        pq.at(x) = pq.at(y) ^ pq.at(x) ^ (pq.at(y) = pq.at(x));
    }

public:
    void insert(int ele)
    {
        pq.push_back(ele);
        int childPos = pq.size() - 1;
        int parentPos = (childPos - 1) / 2;

        // Up-Heapify
        while (pq.at(childPos) < pq.at(parentPos))
        {
            swap(childPos, parentPos);
            childPos = parentPos;
            parentPos = (childPos - 1) / 2;
        }
    }

    void remove()
    {
        int lastPos = pq.size() - 1;
        if (lastPos < 0)
            return;

        swap(0, lastPos);
        pq.pop_back();

        int i = 0;
        int child1 = 2 * i + 1;
        int child2 = 2 * i + 2;

        // Down-Heapify
        while (child1 < pq.size() || child2 < pq.size())
        {
            if (child2 < pq.size())
            {
                if (pq.at(child1) <= pq.at(child2) && pq.at(i) > pq.at(child1))
                {
                    swap(i, child1);
                    i = child1;
                }
                else if (pq.at(i) > pq.at(child2))
                {
                    swap(i, child2);
                    i = child2;
                }
                else
                    break;
            }
            else if (pq.at(i) > pq.at(child1))
            {
                swap(i, child1);
                i = child1;
            }
            else
                break;
            child1 = 2 * i + 1;
            child2 = 2 * i + 2;
        }
    }
};

inline void swap(int *x, int *y)
{
    *x = *x ^ *y ^ (*y = *x);
}
// Heap Sort
void inplaceHeapSort(int *arr, int len)
{
    if (len <= 1)
        return;

    // Insert elements in heap
    for (int i = 1; i < len; i++)
    {
        int childPos = i;
        int parentPos = (i - 1) / 2;
        // Up-Heapify
        while (*(arr + childPos) < *(arr + parentPos))
        {
            swap(arr + childPos, arr + parentPos);
            childPos = parentPos;
            parentPos = (childPos - 1) / 2;
        }
    }

    // Remove elements from heap
    for (int i = 0; i < len; i++)
    {
        swap(arr, arr + len - i - 1);

        // Down-Heapify
        int parentPos = 0;
        int child1 = 2 * parentPos + 1;
        int child2 = 2 * parentPos + 2;
        while (child1 < len - i - 1)
        {
            if (child2 < len - i - 1)
            {
                if (*(arr + child1) <= *(arr + child2))
                {
                    if (*(arr + child1) < *(arr + parentPos))
                    {
                        swap(arr + child1, arr + parentPos);
                        parentPos = child1;
                    }
                    else
                        break;
                }
                else
                {
                    if (*(arr + child2) < *(arr + parentPos))
                    {
                        swap(arr + child2, arr + parentPos);
                        parentPos = child2;
                    }
                    else
                        break;
                }
            }
            else
            {
                if (*(arr + child1) < *(arr + parentPos))
                {
                    swap(arr + child1, arr + parentPos);
                    parentPos = child1;
                }
                else
                    break;
            }

            child1 = 2 * parentPos + 1;
            child2 = 2 * parentPos + 2;
        }
    }
}

void kSortedArray(int *arr, int len, int k)
{
    priority_queue<int> pq;
    if (k >= len)
        return;

    for (int i = 0; i < k; i++)
        pq.push(*(arr + i));

    for (int i = 0; i < len - k; i++)
    {
        *(arr + i) = pq.top();
        pq.pop();
        pq.push(*(arr + i + k));
    }
    for (int i = len - k; i < len; i++)
    {
        *(arr + i) = pq.top();
        pq.pop();
    }
}

void kSmallestElements(int *arr, int len, int k)
{
    if (k > len)
        k = len;
    priority_queue<int> pq;
    for (int i = 0; i < len; i++)
        pq.push(*(arr + i));

    for (int i = 0; i < len - k; i++)
        pq.pop();

    for (int i = 0; i < k; i++)
    {
        cout << pq.top() << " ";
        pq.pop();
    }
}

void kLargestElements(int *arr, int len, int k)
{
    if (k > len)
        k = len;
    priority_queue<int> pq;
    for (int i = 0; i < len; i++)
        pq.push(*(arr + i));

    for (int i = 0; i < k; i++)
    {
        cout << pq.top() << "  ";
        pq.pop();
    }
}

bool checkMaxHeap(int *arr, int len)
{
    bool flag = true;
    for (int i = 1; i < len; i++)
    {
        int parentPos = (i - 1) / 2;
        if (*(arr + i) > *(arr + parentPos))
        {
            flag = false;
            break;
        }
    }
    return flag;
}

int kthLargestElement(int *arr, int len, int k)
{
    if (k > len)
        return -9999;
    priority_queue<int> pq;
    for (int i = 0; i < len; i++)
        pq.push(*(arr + i));

    for (int i = 0; i < k - 1; i++)
    {
        pq.pop();
    }
    return pq.top();
}

vector<int> mergeKSortedArrays(vector<vector<int>> v)
{
    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> arr;
    for (int i = 0; i < v.size(); i++)
    {
        vector<int> ele = v.at(i);
        for (int j = 0; j < ele.size(); j++)
            pq.push(ele.at(j));
    }

    while (!pq.empty())
    {
        arr.push_back(pq.top());
        pq.pop();
    }
    return arr;
}

void runningMedian(int *arr, int len)
{
    if (len <= 0)
        return;

    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

    vector<int> medians;
    minHeap.push(*arr);
    medians.push_back(*arr);

    for (int i = 1; i < len; i++)
    {
        int ele = *(arr + i);
        if (maxHeap.size() < minHeap.size())
        {
            maxHeap.push(ele);
        }
        else
        {
            minHeap.push(ele);
        }
        while (maxHeap.size() > minHeap.size())
        {
            int y = maxHeap.top();
            maxHeap.pop();
            minHeap.push(y);
        }
        while (maxHeap.top() > minHeap.top())
        {
            int x = maxHeap.top();
            maxHeap.pop();
            int y = minHeap.top();
            minHeap.pop();

            maxHeap.push(y);
            minHeap.push(x);
        }

        if (minHeap.size() > maxHeap.size())
            medians.push_back(minHeap.top());
        else
            medians.push_back((maxHeap.top() + minHeap.top()) / 2);
    }

    for (auto it : medians)
        cout << it << " ";
    cout << "\n";
}

int buytheTicket(int *arr, int len, int k)
{
    if (k >= len)
        return -1;

    queue<int> q;
    priority_queue<int> pq;
    for (int i = 0; i < len; i++)
    {
        q.push(*(arr + i));
        pq.push(*(arr + i));
    }

    int min = 0;
    while (!(k == 0 && q.front() == pq.top()))
    {
        if (k == 0)
        {
            q.push(q.front());
            q.pop();
            k = q.size() - 1;
        }
        else if (q.front() != pq.top())
        {
            q.push(q.front());
            q.pop();
            k--;
        }
        else
        {
            q.pop();
            pq.pop();
            min++;
            k--;
        }
    }

    return min + 1;
}

int main(int argc, char *argv[])
{

    // PriorityQueue pq;
    // pq.insert(1);
    // pq.insert(4);
    // pq.insert(-5);
    // pq.insert(8);
    // pq.insert(-8);
    // pq.display();
    // pq.remove();
    // pq.remove();
    // pq.display();

    // int arr[] = {5, 2, 6, 8, 3, 8, 10, 1, -6, 90};
    // inplaceHeapSort(arr, sizeof(arr) / sizeof(int));
    // for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
    //     cout << *(arr + i) << "  ";

    // priority_queue<int> pq;
    // pq.push(2);
    // pq.push(5);
    // pq.push(7);
    // pq.push(2);
    // pq.push(-1);

    // while (!pq.empty())
    // {
    //     cout << pq.top() << "  ";
    //     pq.pop();
    // }

    // int arr[] = {10, 12, 6, 7, 9};
    // kSortedArray(arr, sizeof(arr) / sizeof(int), 3);
    // for (int x : arr)
    //     cout << x << "  ";

    // int arr[] = {10, 12, 6, 7, 9};
    // kLargestElements(arr, sizeof(arr) / sizeof(int), 4);

    // int arr[] = {10, 12, 6, 7, 9};
    // cout << kthLargestElement(arr, sizeof(arr) / sizeof(int), 2) << endl;

    // int arr[] = {6, 2, 1, 3, 7, 5};
    // runningMedian(arr, sizeof(arr) / sizeof(int));

    int arr[] = {2, 3, 2, 2, 4};
    // int arr[] = {3, 9, 4};
    cout << buytheTicket(arr, sizeof(arr) / sizeof(int), 0) << endl;

    return 0;
}