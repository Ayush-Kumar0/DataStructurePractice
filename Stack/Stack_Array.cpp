#include <iostream>
using namespace std;

// Non-generic classes

// // Stack using static array
// class SStack
// {
// private:
//     int arr[];
//     int capacity;
//     int nextIndex;

// public:
//     // Constructors
//     SStack()
//     {
//         arr[100];
//         capacity = 100;
//         nextIndex = 0;
//     }
//     SStack(int capacity)
//     {
//         arr[capacity];
//         this->capacity = capacity;
//         nextIndex = 0;
//     }

//     // Functions
//     void push(const int element)
//     {
//         if (nextIndex >= capacity)
//         {
//             cout << "Overflow\n";
//             return;
//         }
//         else
//         {
//             arr[nextIndex++] = element;
//         }
//     }
//     int pop()
//     {
//         if (nextIndex <= 0)
//         {
//             cout << "Underflow\n";
//             return INT8_MIN;
//         }
//         else
//         {
//             return arr[--nextIndex];
//         }
//     }
//     int top()
//     {
//         if (nextIndex <= 0)
//         {
//             return INT8_MIN;
//         }
//         else
//             return arr[nextIndex - 1];
//     }
//     int size()
//     {
//         return nextIndex;
//     }
//     bool isEmpty()
//     {
//         return nextIndex == 0;
//     }
// };

// // Stack using dynamic array
// class DStack
// {
// private:
//     int *arr;
//     int capacity;
//     int nextIndex;

// public:
//     // Constructors
//     DStack()
//     {
//         arr = new int[10];
//         capacity = 10;
//         nextIndex = 0;
//     }
//     // Functions
//     void push(const int element)
//     {
//         if (nextIndex >= capacity)
//         {
//             // Extend array size
//             int *temp = new int[capacity * 2];
//             for (int i = 0; i < capacity; i++)
//                 *(temp + i) = *(arr + i);
//             capacity = 2 * capacity;
//             delete[] arr;
//             arr = temp;
//             arr[nextIndex++] = element;
//         }
//         else
//         {
//             arr[nextIndex++] = element;
//         }
//     }
//     int pop()
//     {
//         if (nextIndex <= 0)
//         {
//             cout << "Underflow\n";
//             return INT8_MIN;
//         }
//         else
//         {
//             return arr[--nextIndex];
//         }
//     }
//     int top()
//     {
//         if (nextIndex <= 0)
//         {
//             return INT8_MIN;
//         }
//         else
//             return arr[nextIndex - 1];
//     }
//     int size()
//     {
//         return nextIndex;
//     }
//     bool isEmpty()
//     {
//         return nextIndex == 0;
//     }
// };

// Generic Classes

// Stack using static array
template <typename T>
class SStack
{
private:
    T arr[];
    int capacity;
    int nextIndex;

public:
    // Constructors
    SStack()
    {
        arr[100];
        capacity = 100;
        nextIndex = 0;
    }
    SStack(T capacity)
    {
        arr[capacity];
        this->capacity = capacity;
        nextIndex = 0;
    }

    // Functions
    void push(const T element)
    {
        if (nextIndex >= capacity)
        {
            cout << "Overflow\n";
            return;
        }
        else
        {
            arr[nextIndex++] = element;
        }
    }
    T pop()
    {
        if (nextIndex <= 0)
        {
            cout << "Underflow\n";
            return 0;
        }
        else
        {
            return arr[--nextIndex];
        }
    }
    T top()
    {
        if (nextIndex <= 0)
        {
            cout << "Underflow\n";
            return 0;
        }
        else
            return arr[nextIndex - 1];
    }
    int size()
    {
        return nextIndex;
    }
    bool isEmpty()
    {
        return nextIndex == 0;
    }
};

// Stack using dynamic array
template <typename T>
class DStack
{
private:
    T *arr;
    int capacity;
    int nextIndex;

public:
    // Constructors
    DStack()
    {
        arr = new T[10];
        capacity = 10;
        nextIndex = 0;
    }
    // Functions
    void push(const T element)
    {
        if (nextIndex >= capacity)
        {
            // Extend array size
            T *temp = new T[capacity * 2];
            for (int i = 0; i < capacity; i++)
                *(temp + i) = *(arr + i);
            capacity = 2 * capacity;
            delete[] arr;
            arr = temp;
            arr[nextIndex++] = element;
        }
        else
        {
            arr[nextIndex++] = element;
        }
    }
    T pop()
    {
        if (nextIndex <= 0)
        {
            cout << "Underflow\n";
            return 0;
        }
        else
        {
            return arr[--nextIndex];
        }
    }
    T top()
    {
        if (nextIndex <= 0)
        {
            cout << "Underflow\n";
            return 0;
        }
        else
            return arr[nextIndex - 1];
    }
    int size()
    {
        return nextIndex;
    }
    bool isEmpty()
    {
        return nextIndex == 0;
    }
};

int main(int argc, char *argv[])
{
    DStack<char> *S = new DStack<char>();
    S->push(65);
    S->push(66);
    S->push(67);
    cout << S->pop() << "  ";
    cout << S->pop() << "  ";
    cout << S->pop() << "  ";
    cout << S->isEmpty() << "  ";
    return 0;
}