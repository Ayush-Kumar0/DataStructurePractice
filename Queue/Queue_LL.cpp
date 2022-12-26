#include <iostream>
using namespace std;

// Template Queue using Linked List
template <typename T>
class Queue
{
    // Class for linked list
    class Node
    {
    public:
        T data;
        Node *next;
        Node(T data)
        {
            this->data = data;
            next = nullptr;
        }
    };

    /*................*/

    Node *head, *tail;
    int s;

public:
    Queue()
    {
        s = 0;
        head = tail = nullptr;
    }

    // Functions
    void push(T data)
    {
        if (head == nullptr)
        {
            head = new Node(data);
            tail = head;
        }
        else
        {
            Node *temp = new Node(data);
            tail->next = temp;
            tail = temp;
        }
        s++;
    }
    T pop()
    {
        if (head == nullptr)
        {
            cout << "Underflow\n";
            return 0;
        }
        T a = head->data;
        Node *temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr)
            tail = head;
        s--;
        return a;
    }
    T front()
    {
        if (head == nullptr)
            return 0;
        else
            return head->data;
    }
    int size()
    {
        return s;
    }
    bool isEmpty()
    {
        return s == 0;
    }
};

int main(int argc, char *argv[])
{
    Queue<int> *q = new Queue<int>();

    q->push(1);
    q->push(2);
    q->push(3);
    q->push(4);
    cout << "Size=" << q->size() << "\n";
    cout << q->pop() << "  ";
    cout << q->pop() << "  ";
    cout << q->pop() << "  ";
    cout << q->pop() << "  ";
    cout << "\nSize=" << q->size() << "\n";
    return 0;
}