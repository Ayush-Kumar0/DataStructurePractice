#include <iostream>
using namespace std;

class LList
{

public:
    int data;
    LList *next;
    LList()
    {
        data = 0;
        next = nullptr;
    }
    LList(LList const &L)
    {
    }
    void display() // Print L.L.
    {
        LList *temp = this;
        while (temp != nullptr)
        {
            cout << temp->data << "   ";
            temp = temp->next;
        }
        cout << "\n";
    }
    void takeInput() // Add Elements to L.L.
    {
        int d = 0;
        cin >> d;
        if (d == -1)
            return;
        this->data = d;
        LList *temp = this;
        cin >> d;
        while (d != -1)
        {
            LList *temp2 = new LList;
            temp2->data = d;
            temp->next = temp2;
            temp = temp2;
            cin >> d;
        }
    }
    // void takeInput() // Add Elements to L.L.
    // {
    //     cin >> data;
    //     LList *temp = new LList;
    //     temp = this;
    //     char ch = 0;
    //     while (true)
    //     {
    //         cout << "Y/N: ";
    //         cin >> ch;
    //         if (ch == 'N' || ch == 'n')
    //             break;
    //         LList *temp2 = new LList;
    //         cin >> temp2->data;
    //         temp2->next = nullptr;
    //         temp->next = temp2;
    //         temp = temp2;
    //     }
    // }

    int length() // Return total Length of L.L.
    {
        int c = 0;
        LList *temp = this;
        while (temp != nullptr)
        {
            temp = temp->next;
            c++;
        }
        return c;
    }
    void printNode(int i) // Print ith node
    {
        LList *temp = this;
        int j = 0;
        while (j < i)
        {
            temp = temp->next;
            j++;
        }
        cout << i << "th node's data is : " << temp->data;
    }
    LList *insertEnd(int data)
    {
        LList *temp = this;
        while (temp->next != nullptr)
            temp = temp->next;
        LList *node = new LList;
        node->data = data;
        temp->next = node;
        return this;
    }
    LList *insertStart(int data)
    {
        LList *node = new LList;
        node->data = data;
        node->next = this;
        return node;
    }
    LList *insertNode(int data, int position) // Insert data at any position
    {
        if (position < 0)
        {
            cout << "Inserted at start rather than at " << position << "\n";
            return insertStart(data);
        }
        else if (position == 0)
        {
            return insertStart(data);
        }
        else if (length() < position)
        {
            cout << "Inserted at end rather than at " << position << "\n";
            insertEnd(data);
        }
        else
        {
            LList *temp = this;
            LList *node = new LList;
            node->data = data;
            int i = 0;
            while (i < position - 1)
            {
                i++;
                temp = temp->next;
            }
            node->next = temp->next;
            temp->next = node;
        }
        return this;
    }
    LList *deleteNode(int position)
    {
        if (position == 0)
        {
            LList *temp = this->next;
            delete this;
            return temp;
        }
        else if (position >= 0 && position < length())
        {
            LList *temp = this;
            int i = 0;
            while (i < position - 1)
            {
                i++;
                temp = temp->next;
            }
            LList *temp2 = temp->next->next;
            delete temp->next;
            temp->next = temp2;
        }
        else
            cout << "No node at " << position << "\n";
        return this;
    }
};

int lengthRec(LList *head)
{
    if (head == nullptr)
    {
        return 0;
    }
    else
    {
        return (1 + lengthRec(head->next));
    }
}

LList *insertNodeR(LList *head, int data, int position)
{
    if (position == 0)
    {
        LList *node = new LList;
        node->data = data;
        node->next = head;
        head = node;
    }
    else if (head != nullptr)
    {
        LList *temp = insertNodeR(head->next, data, position - 1);
        head->next = temp;
    }
    return head;
}
LList *deleteNodeR(LList *head, int position)
{
    if (position == 0)
    {
        if (head != nullptr)
        {
            LList *temp = head->next;
            delete head;
            head = temp;
        }
    }
    else if (head != nullptr)
    {
        LList *temp = deleteNodeR(head->next, position - 1);
        head->next = temp;
    }
    return head;
}

int findNode(LList *head, int data)
{
    int i = 0;
    while (head->data != data)
    {
        if (head->next == nullptr)
            return -1;
        i++;
        head = head->next;
    }
    return i;
}

LList *appendLastNToFirst(LList *head, int n)
{
    int l = head->length();
    n %= l;
    if (n == 0 || head == nullptr)
        return head;
    LList *curr = head;
    int i = 0;
    while (i < l - n - 1)
    {
        curr = curr->next;
        i++;
    }
    LList *temp = curr->next;
    curr->next = nullptr;
    curr = temp;
    i++;
    while (i < l - 1)
    {
        curr = curr->next;
        i++;
    }
    curr->next = head;
    head = temp;
    return head;
}

LList *removeDuplicates(LList *head)
{
    if (head == nullptr)
        return head;
    LList *temp1 = head;
    LList *temp2 = head->next;
    while (temp2 != nullptr)
    {
        if (temp1->data == temp2->data)
        {
            temp1->next = temp2->next;
            delete temp2;
            temp2 = temp1->next;
        }
        else
        {
            temp1 = temp2;
            temp2 = temp2->next;
        }
    }
    return head;
}

void displayReverse(LList *head)
{
    if (head == nullptr)
        return;
    else if (head->next == nullptr)
        cout << head->data << "   ";
    else
    {
        displayReverse(head->next);
        cout << head->data << "   ";
    }
}

bool checkPalindrome(LList *head)
{
    LList *head2 = head;
    int i = 0;
    int l = head->length();
    if (l < 2)
        return true;
    while (i++ < (l + 1) / 2)
        head2 = head2->next;

    // Reversing second half
    LList *prev = nullptr;
    while (head2->next != nullptr)
    {
        LList *temp = head2;
        head2 = head2->next;
        temp->next = prev;
        prev = temp;
    }

    // Comparision
    bool c = true;
    while (head2 != nullptr)
    {
        if (head->data != head2->data)
        {
            c = false;
            break;
        }
        head = head->next;
        head2 = head2->next;
    }
    return c;
}

void midpoint(LList *head)
{
    if (head == nullptr)
        cout << "Empty Linked List\n";

    LList *slow = head;
    LList *fast = head->next;
    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    if (fast == nullptr)
        cout << "Midpoint's data is: " << slow->data << "\n";
    else if (fast->next == nullptr)
        cout << "Midpoints' data are: " << slow->data << "  and  " << slow->next->data << "\n";
}

LList *mergeLList(LList *h1, LList *h2)
{
    if (h1 == nullptr)
        return h2;
    else if (h2 == nullptr)
        return h1;
    else
    {
        LList *fH, *fT;
        if (h1->data > h2->data)
        {
            fH = h2;
            h2 = h2->next;
        }
        else
        {
            fH = h1;
            h1 = h1->next;
        }
        fT = fH;
        while (h1 != nullptr && h2 != nullptr)
        {
            if (h1->data < h2->data)
            {
                fT->next = h1;
                fT = h1;
                h1 = h1->next;
            }
            else
            {
                fT->next = h2;
                fT = h2;
                h2 = h2->next;
            }
        }
        fT->next = (h1 == nullptr) ? h2 : h1;
        return fH;
    }
}

LList *mergeSort(LList *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;
    else
    {
        LList *mid;
        LList *slow = head, *fast = head->next;
        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        mid = slow->next;
        slow->next = nullptr;

        head = mergeSort(head);
        mid = mergeSort(mid);

        head = mergeLList(head, mid);
        return head;
    }
}

// Reversing method 1
LList *reverseRec1(LList *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;
    else
    {
        LList *small = reverseRec1(head->next);
        LList *temp = small;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = head;
        head->next = nullptr;
        return small;
    }
}

// Reversing method 2
class Pair
{
public:
    LList *head;
    LList *tail;
    Pair reverse(LList *head)
    {
        if (head == nullptr || head->next == nullptr)
        {
            Pair p;
            p.head = head;
            p.tail = head;
            return p;
        }
        else
        {
            Pair p = reverse(head->next);
            head->next = nullptr;
            p.tail->next = head;
            p.tail = head;
            return p;
        }
    }
};
inline LList *reverseRec2(LList *head)
{
    Pair p;
    p = p.reverse(head);
    return p.head;
}
// Reversing method 3
LList *reverseRec3(LList *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;
    else
    {
        LList *small = reverseRec3(head->next);
        LList *temp = head->next;
        temp->next = head;
        head->next = nullptr;
        return small;
    }
}
// Reversing method 4
LList *reverseIter(LList *head)
{
    LList *prev = nullptr;
    while (head != nullptr)
    {
        LList *next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

int findNodeRec(LList *head, int data)
{
    if (head->data == data)
        return 0;
    else
        return (1 + findNodeRec(head->next, data));
}

LList *evenAfterOdd(LList *head)
{
    LList *oddH, *oddT, *evenH, *evenT;
    // oddH = oddT = evenH = evenT = nullptr;
    while (head != nullptr)
    {
        if (head->data % 2 == 0)
        {
            if (evenH == nullptr)
            {
                evenH = head;
                evenT = head;
            }
            else
            {
                evenT->next = head;
                evenT = head;
                // if (oddT != nullptr)
                //     oddT->next = nullptr;
            }
        }
        else
        {
            if (oddH == nullptr)
            {
                oddH = head;
                oddT = head;
            }
            else
            {
                oddT->next = head;
                oddT = head;
                // if (evenT != nullptr)
                //     evenT->next = nullptr;
            }
        }
        head = head->next;
    }
    if (oddT != nullptr && evenH == nullptr)
    {
        head = oddH;
        oddT->next = nullptr;
    }
    else if (evenT != nullptr && oddH == nullptr)
    {
        head = evenH;
        evenT->next = nullptr;
    }
    else
    {
        head = oddH;
        oddT->next = evenH;
        evenT->next = nullptr;
    }
    return head;
}

LList *deleteEveryNNode(LList *head, int n, int m) // delete 'n' nodes after each 'm' nodes
{
    if (head == nullptr)
        return head;
    LList *tail = new LList;
    LList *head2 = tail;
    LList *temp = head;
    while (temp != nullptr)
    {
        for (int i = 1; i <= m; i++)
        {
            if (temp != nullptr)
            {
                tail->next = temp;
                tail = temp;
                temp = temp->next;
            }
            else
                break;
        }
        for (int i = 1; i <= n; i++)
        {
            if (temp != nullptr)
            {
                LList *temp2 = temp;
                temp = temp->next;
                delete temp2;
            }
            else
                break;
        }
    }
    delete head2;
    if (m == 0)
        return nullptr;
    tail->next = nullptr;
    return head;
}

LList *swapNodes(LList *head, int a, int b)
{
    if (head == nullptr || a == b)
        return head;
    LList *temp = head;
    LList *c1, *c2, *p1, *p2;
    c1 = c2 = p1 = p2 = nullptr;
    int i;
    if (a == 0)
    {
        // When first node is swapped
        c1 = head;
    }
    else
    {
        for (i = 0; i < a; i++)
        {
            p1 = temp;
            temp = temp->next;
        }
        c1 = temp;
    }
    if (a - b == 1 || b - a == 1)
    {
        // Swapping consecutive nodes
        c2 = c1->next;
        if (a == 0)
        {
            // First Consecutive node
            c1->next = c2->next;
            c2->next = c1;
            head = c2;
        }
        else
        {
            // Non-first consecutive node
            c1->next = c2->next;
            c2->next = c1;
            p1->next = c2;
        }
    }
    else
    {
        // Swapping non-consecutive nodes
        temp = temp->next;
        i++;
        for (; i < b; i++)
        {
            p2 = temp;
            temp = temp->next;
        }
        c2 = temp;
        if (a == 0)
        {
            // First non-consecutive nodes
            p2->next = c1;
            LList *t = c1->next; // temporary
            c1->next = c2->next;
            c2->next = t;
            head = c2;
        }
        else
        {
            // Non-first non-consecutive nodes
            p1->next = c2;
            p2->next = c1;
            LList *t = c1->next; // temporary
            c1->next = c2->next;
            c2->next = t;
        }
    }
    return head;
}

LList *kReverse(LList *head, int k)
{
    if (head == nullptr)
        return head;
    else
    {
        int i = 0;
        LList *temp = head, *tail = head;
        temp = temp->next;
        while (++i < k)
        {
            if (temp == nullptr)
                break;
            tail->next = temp;
            tail = temp;
            temp = temp->next;
        }
        tail->next = nullptr;
        // Reversing 'k' nodes
        LList *prev = nullptr, *head2 = head;
        while (head != nullptr)
        {
            LList *t = head->next;
            head->next = prev;
            prev = head;
            head = t;
        }
        // Rejoining small part with large one
        temp = kReverse(temp, k);
        head2->next = temp;
        head = prev;
        return head;
    }
}

LList *bubbleSort(LList *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;
    int l = head->length();
    for (int i = 0; i < l - 1; i++)
    {
        LList *prev = nullptr, *curr = head, *next = head->next;
        while (curr->next != nullptr)
        {
            if (prev == nullptr)
            {
                if (curr->data > curr->next->data)
                {
                    prev = curr->next;
                    curr->next = prev->next;
                    prev->next = curr;
                    head = prev;
                }
                else
                {
                    prev = curr;
                    curr = curr->next;
                }
            }
            else
            {
                if (curr->data > curr->next->data)
                {
                    // Swap
                    prev->next = curr->next;
                    curr->next = curr->next->next;
                    prev->next->next = curr;
                    prev = prev->next;
                }
                else
                {
                    prev = curr;
                    curr = curr->next;
                }
            }
        }
    }
    return head;
}

// Next number
LList *nextNumber(LList *head)
{
    // Reversing
    LList *prev = nullptr;
    while (head != nullptr)
    {
        LList *temp = head->next;
        head->next = prev;
        prev = head;
        head = temp;
    }
    head = prev;

    // Increment and Reversing
    int carry = 0;
    if (head->data < 9)
        head->data++;
    else
    {
        head->data = 0;
        carry = 1;
    }
    prev = head;
    head = head->next;
    prev->next = nullptr;
    while (head != nullptr)
    {
        LList *temp = head->next;
        head->data += carry;
        carry = head->data / 10;
        head->data %= 10;
        head->next = prev;
        prev = head;
        head = temp;
    }
    head = prev;
    // head->display();
    if (carry != 0)
    {
        LList *temp = new LList;
        temp->data = carry;
        temp->next = head;
        head = temp;
    }

    // Returning
    return head;
}

int main(int argc, char *argv[])
{
    LList *L = new LList();
    L->takeInput();
    L->display();
    // L = deleteNodeR(L, 1);.
    // cout << findNode(L, 99) << "\n";
    // L = appendLastNToFirst(L, 41);
    // removeDuplicates(L);
    // L->display();
    // displayReverse(L);
    // cout << checkPalindrome(L);
    // midpoint(L);
    // LList *L2 = new LList;
    // L2->takeInput();
    // L2->display();
    // L = mergeLList(L, L2);
    // L = mergeSort(L);
    // L = reverseIter(L);
    // L = evenAfterOdd(L);
    // L = deleteEveryNNode(L, 1, 1);
    // int i, j;
    // cin >> i >> j;
    // L = swapNodes(L, i, j);
    // L = kReverse(L, 4);
    // L = bubbleSort(L);
    // L->display();
    L = nextNumber(L);
    L->display();
    return 0;
}