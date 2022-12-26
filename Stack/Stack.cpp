#include <iostream>
#include <string>
using namespace std;

// Inbuilt stack
#include <stack>

// Balanced Paranthesis problem
void balancedParanthesis(string s)
{
    stack<char> bracks;
    bool flag = true;
    for (int i = 0; i < s.length(); i++)
    {
        char ch = s.at(i);
        // Opening brackets
        if (ch == '(')
        {
            bracks.push(ch);
        }
        // Closing brackets
        else if (ch == ')')
        {
            if (!bracks.empty() && bracks.top() == '(')
            {
                bracks.pop();
            }
            else
            {
                flag = false;
                break;
            }
        }
    }
    if (!bracks.empty())
        flag = false;
    if (flag)
        cout << "Balanced\n";
    else
        cout << "Unbalanced\n";
}

// Reverse stack problem
template <typename T>
void reverseStack0(stack<T> *s1, stack<T> *s2)
{
    if (s1->empty())
    {
        return;
    }
    else
    {
        T temp = s1->top();
        s1->pop();
        reverseStack0<T>(s1, s2);
        s2->push(temp);
    }
}
template <typename T>
void reverseStack(stack<T> *s1, stack<T> *s2)
{
    reverseStack0<T>(s1, s2);
    while (!s2->empty())
    {
        s1->push(s2->top());
        s2->pop();
    }
}

// Check if there are redundant brackets in an expression
bool redundantParenthesis(string s)
{
    if (s[0] != '(' || s[s.size() - 1] != ')')
        s = "(" + s + ")";
    int l = s.length();
    stack<char> pare;
    int count = 0;
    for (int i = 0; i < l; i++)
    {
        char ch = s.at(i);
        if (ch != ')')
        {
            pare.push(ch);
        }
        else
        {
            count = 0;
            while (pare.top() != '(')
            {
                pare.pop();
                count++;
            }
            pare.pop();
            if (count < 1)
                break;
        }
    }
    if (count < 1)
        cout << "Redundant parenthesis\n";
    else
        cout << "Non-Redundant parenthesis\n";
}

// Stock span
void stockSpan(int *arr, int l, int *out)
{
    stack<int> s;
    for (int i = 0; i < l; i++)
    {
        if (s.empty() || *(arr + i) > s.top())
        {
            *(out + i) = s.size() + 1;
        }
        else
        {
            *(out + i) = 1;
            while (!s.empty())
                s.pop();
        }
        s.push(*(arr + i));
    }
}

// Find minimum number of brackets need to be reversed to make expression balanced
int bracketReversal(const string s)
{
    int l = s.length();
    if (l & 1 == 1)
        return -1;
    else
    {
        stack<char> st;
        // Remove balanced parts
        for (auto x : s)
        {
            if (x == '{')
                st.push(x);
            else if (x == '}')
            {
                if (st.empty() || st.top() == '}')
                    st.push(x);
                else if (st.top() == '{')
                {
                    st.pop();
                }
            }
        }
        // Operation on stack (unbalanced part)
        char c1, c2;
        int count = 0;
        while (!st.empty())
        {
            c1 = st.top();
            st.pop();
            c2 = st.top();
            st.pop();
            if (c1 == c2)
                count += 1;
            else
                count += 2;
        }
        return count;
    }
}

int main(int argc, char *argv[])
{
    // stack<char> s, t;
    // s.push(65);
    // s.push(66);
    // s.push(67);
    // reverseStack<char>(&s, &t);
    // cout << s.top() << "  ";
    // s.pop();
    // cout << s.top() << "  ";
    // s.pop();
    // cout << s.top() << "  ";
    // t.pop();
    // cout << t.top() << "  ";
    // redundantParenthesis("(5+8)");
    // int arr[] = {60, 86, 60, 75, 85};
    // int out[5];
    // stockSpan(arr, 5, out);
    // for (int x : out)
    // {
    //     cout << x << "  ";
    // }

    string s;
    cin >> s;
    cout << bracketReversal(s) << "\n";
    return 0;
}