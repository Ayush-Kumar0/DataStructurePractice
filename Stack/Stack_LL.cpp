#include <iostream>
using namespace std;

// Stack without templates

// class Stack
// {
//     // Node class inside Stack
//     class Node
//     {
//     public:
//         int data;
//         Node *next;
//         Node(int x)
//         {
//             data = x;
//             next = nullptr;
//         }
//     };

//     Node *head;
//     int count;

// public:
//     Stack()
//     {
//         head = nullptr;
//         count = 0;
//     }
//     void push(int element)
//     {
//         Node *temp = new Node(element);
//         if (head == nullptr)
//             head = temp;
//         else
//         {
//             temp->next = head;
//             head = temp;
//         }
//         count++;
//     }
//     int pop()
//     {
//         if (head == nullptr)
//         {
//             cout << "Underflow\n";
//             return 0;
//         }
//         else
//         {
//             Node *temp = head;
//             int data = temp->data;
//             head = head->next;
//             count--;
//             delete temp;
//             return data;
//         }
//     }
//     int size()
//     {
//         return count;
//     }
//     int top()
//     {
//         return head->data;
//     }
//     bool isEmpty()
//     {
//         return head == nullptr;
//     }
// };

// Stack using Templates
template <typename T>
class Stack
{
    // Node class inside Stack
    template <typename V>
    class Node
    {
    public:
        V data;
        Node *next;
        Node(V x)
        {
            data = x;
            next = nullptr;
        }
    };

    Node<T> *head;
    int count;

public:
    Stack()
    {
        head = nullptr;
        count = 0;
    }
    void push(T element)
    {
        Node<T> *temp = new Node<T>(element);
        if (head == nullptr)
            head = temp;
        else
        {
            temp->next = head;
            head = temp;
        }
        count++;
    }
    T pop()
    {
        if (head == nullptr)
        {
            cout << "Underflow\n";
            T returnVal;
            return returnVal;
        }
        else
        {
            Node<T> *temp = head;
            T data = temp->data;
            head = head->next;
            count--;
            delete temp;
            return data;
        }
    }
    int size()
    {
        return count;
    }
    T top()
    {
        return head->data;
    }
    bool isEmpty()
    {
        return head == nullptr;
    }
};
int main(int argc, char *argv[])
{
    Stack<char> *s = new Stack<char>();
    s->push('b');
    s->push('a');
    cout << s->size() << "  ";
    cout << s->pop() << "  ";
    cout << s->pop() << "  ";
    cout << s->pop() << "  ";
    cout << s->size() << "  ";
    cout << s->isEmpty() << "  ";
    return 0;
}