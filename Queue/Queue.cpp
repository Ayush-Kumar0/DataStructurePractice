#include <iostream>
#include <queue>
using namespace std;

template <typename T>
void reverseQueue(queue<T> *q1)
{
    if (q1->empty())
    {
        return;
    }
    else
    {
        T t = q1->front();
        q1->pop();
        reverseQueue<T>(q1);
        q1->push(t);
    }
}

template <typename T>
class Dequeue
{
    T *arr;
    int front, back, capacity;

public:
    Dequeue()
    {
        capacity = 10;
        front = capacity - 1;
        back = 0;
        arr = new T[capacity];
    }
    void insertFront(T data)
    {
        if (front = back - 1)
        {
            cout << " -1 ";
            return;
        }
        else
        {
            arr[front] = data;
            front--;
            if (front = -1)
                front = capacity - 1;
        }
    }
    void insertRear(T data)
    {
        if (front == back - 1)
        {
            cout << " -1 ";
            return;
        }
        else
        {
            arr[back] = data;
            back++;
            if (back == capacity)
                back = 0;
        }
    }
    void deleteFront()
    {
        if (front == capacity - 1 && back == 0)
        {
            cout << " -1 ";
            return;
        }
        else
        {
            front++;
            if (front == capacity)
                front = 0;
        }
    }
    void deleteRear()
    {
        if (front == capacity - 1 && back == 0)
        {
            cout << " -1 ";
            return;
        }
        else
        {
            back--;
            if (back == -1)
                back = capacity - 1;
        }
    }
    T getFront()
    {
        if (front == capacity - 1 && back == 0)
        {
            cout << " -1 ";
            return 0;
        }
        else
        {
            if (front == capacity - 1)
                return arr[0];
            else
                return arr[front + 1];
        }
    }
    T getRear()
    {
        if (front == capacity - 1 && back == 0)
        {
            cout << " -1 ";
            return 0;
        }
        else
        {
            if (back == 0)
                return arr[capacity - 1];
            else
                return arr[back - 1];
        }
    }
};

int main(int argc, char *argv[])
{
    queue<char> q;
    q.push(65);
    q.push(66);
    q.push(67);
    q.push(68);
    reverseQueue<char>(&q);
    cout << q.front() << "  ";
    q.pop();
    cout << q.front() << "  ";
    q.pop();
    cout << q.front() << "  ";
    q.pop();
    cout << q.front() << "  ";
    q.pop();
    return 0;
}