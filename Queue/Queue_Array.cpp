#include <iostream>
using namespace std;

// Static Queue
class SQueue
{
    int arr[];
    int capacity;
    int left, next;

public:
    SQueue()
    {
        capacity = 20;
        arr[capacity];
        left = -1;
        next = 0;
    }
    SQueue(int capacity)
    {
        this->capacity = capacity;
        arr[capacity];
        left = -1;
        next = 0;
    }

    // Functions
    void push(int data)
    {
        if (next == left)
        {
            cout << "Overflow\n";
        }
        else
        {
            if (left == -1)
                left = 0;
            arr[next++] = data;
            if (next == capacity)
                next = 0;
        }
    }
    int pop()
    {
        if (left == -1)
        {
            cout << "Underflow\n";
            return INT8_MIN;
        }
        else
        {
            int a = arr[left++];
            if (left == capacity)
                left = 0;
            if (left == next)
                left = (next = 0) - 1;
            return a;
        }
    }
    int front()
    {
        return arr[left];
    }
    int size()
    {
        if (left == -1)
            return 0;
        if (left < next)
        {
            return next - left;
        }
        else
        {
            return (next + capacity - left);
        }
    }
    bool isEmpty()
    {
        return left == -1;
    }
};

// Dynamic Queue
class DQueue
{
    int *arr;
    int capacity;
    int left, next;

public:
    DQueue()
    {
        capacity = 20;
        arr = new int[capacity];
        left = -1;
        next = 0;
    }

    // Functions
    void push(int data)
    {
        if (next == capacity)
        {
            int *temp = new int[2 * capacity];
            for (int i = 0; i < capacity; i++)
                temp[i] = arr[i];
            delete[] arr;
            arr = temp;
            arr[next++] = data;
        }
        else
        {
            if (left == -1)
                left = 0;
            arr[next++] = data;
        }
    }
    int pop()
    {
        if (left == -1)
        {
            cout << "Underflow\n";
            return INT8_MIN;
        }
        else
        {
            int a = arr[left++];
            if (left == next)
                left = (next = 0) - 1;
            return a;
        }
    }
    int front()
    {
        if (left <= -1)
            return INT8_MIN;
        else
            return arr[left];
    }
    int size()
    {
        if (left == -1)
            return 0;
        else
            return next - left;
    }
    bool isEmpty()
    {
        return left == -1;
    }
};

// Template Queue
template <typename T>
class TQueue
{
    T *arr;
    int capacity;
    const int init_s = 5;
    int left, next;

public:
    TQueue()
    {
        capacity = init_s;
        arr = new T[capacity];
        left = -1;
        next = 0;
    }

    // Functions
    void push(T data)
    {
        if (next == capacity)
        {
            T *temp = new T[capacity + init_s];
            for (int i = 0; i < capacity; i++)
                temp[i] = arr[i];
            capacity += init_s;
            delete[] arr;
            arr = temp;
            arr[next++] = data;
        }
        else
        {
            if (left == -1)
                left = 0;
            arr[next++] = data;
        }
    }
    T pop()
    {
        if (left == -1)
        {
            cout << "Underflow\n";
            return 0;
        }
        else
        {
            T a = arr[left++];
            if (left == next)
            {
                left = (next = 0) - 1;
                delete[] arr;
                capacity = init_s;
                arr = new T[capacity];
            }
            return a;
        }
    }
    T front()
    {
        if (left <= -1)
            return 0;
        else
            return arr[left];
    }
    int size()
    {
        if (left == -1)
            return 0;
        else
            return next - left;
    }
    bool isEmpty()
    {
        return left == -1;
    }
};

int main(int argc, char *argv[])
{
    TQueue<char> *q = new TQueue<char>();
    return 0;
}