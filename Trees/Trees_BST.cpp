#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

// Binary Search Tree class
template <typename T>
class BTNode
{
public:
    T data;
    BTNode<T> *left, *right;
    BTNode(T data)
    {
        this->data = data;
        left = right = nullptr;
    }
};

// Take input level-wise
BTNode<int> *takeInput()
{
    cout << "Enter Binary Search Tree:  ";
    int d;
    cin >> d;
    if (d == -1)
        return nullptr;

    BTNode<int> *root = new BTNode<int>(d);
    queue<BTNode<int> *> q;

    q.push(root);
    while (!q.empty())
    {
        BTNode<int> *temp = q.front();
        q.pop();

        cin >> d;
        if (d != -1)
        {
            temp->left = new BTNode<int>(d);
            q.push(temp->left);
        }
        cin >> d;
        if (d != -1)
        {
            temp->right = new BTNode<int>(d);
            q.push(temp->right);
        }
    }
    return root;
}

// Display level-wise
void display(BTNode<int> *root)
{
    if (root == nullptr)
        return;

    queue<BTNode<int> *> q;
    q.push(root);

    while (!q.empty())
    {
        BTNode<int> *temp = q.front();
        q.pop();
        cout << temp->data << " :  ";

        if (temp->left != nullptr)
        {
            cout << "L" << temp->left->data << " ";
            q.push(temp->left);
        }
        if (temp->right != nullptr)
        {
            cout << "R" << temp->right->data << " ";
            q.push(temp->right);
        }
        cout << "\n";
    }
}

// Search in Binary Search Tree
BTNode<int> *search(BTNode<int> *root, int data)
{
    if (root == nullptr)
        return nullptr;

    if (root->data == data)
        return root;

    if (data > root->data)
    {
        return search(root->right, data);
    }
    else if (data < root->data)
    {
        return search(root->left, data);
    }
    else
        return nullptr;
}

void printInRange(BTNode<int> *root, int min, int max)
{
    if (root == nullptr)
        return;

    if (root->data > min)
        printInRange(root->left, min, max);

    if (root->data >= min && root->data <= max)
        cout << root->data << " ";

    if (root->data < max)
        printInRange(root->right, min, max);
}

// Check if BTree is BTNode
// Solution 1
int maximum(BTNode<int> *root)
{
    if (root == nullptr)
        return INT32_MIN;

    if (root->right != nullptr)
        return maximum(root->right);
    else
        return root->data;
}
int minimum(BTNode<int> *root)
{
    if (root == nullptr)
        return INT32_MAX;

    if (root->left != nullptr)
        return minimum(root->left);
    else
        return root->data;
}
bool isBTNode1(BTNode<int> *root)
{
    if (root == nullptr)
        return true;

    int max_left = maximum(root->left);
    int min_right = minimum(root->right);

    return (max_left < root->data && min_right >= root->data) && isBTNode1(root->left) && isBTNode1(root->right);
}
// Solution 2
class Triple
{
public:
    int minimum;
    int maximum;
    bool isBTNode;
};
Triple isBTNode2(BTNode<int> *root)
{
    Triple tri;
    if (root == nullptr)
    {
        tri.minimum = INT32_MAX;
        tri.maximum = INT32_MIN;
        tri.isBTNode = true;
        return tri;
    }

    Triple tri1 = isBTNode2(root->left);
    Triple tri2 = isBTNode2(root->right);
    tri.maximum = max(root->data, max(tri1.maximum, tri2.maximum));
    tri.minimum = min(root->data, min(tri1.minimum, tri2.minimum));

    tri.isBTNode = (root->data > tri1.maximum) && (root->data <= tri2.minimum) && tri1.isBTNode && tri2.isBTNode;

    return tri;
}
// Solution 3
bool isBTNode3(BTNode<int> *root, int min = INT32_MIN, int max = INT32_MAX)
{
    if (root == nullptr)
        return true;
    if (root->data < min || root->data > max)
        return false;

    return isBTNode3(root->left, min, root->data - 1) && isBTNode3(root->right, root->data, max);
}

// Construct a BTNode from sorted Array
BTNode<int> *constructBTNode(int *arr, int si = 0, int li = 0)
{
    if (li < si)
        return nullptr;

    const int mid = (li + si) / 2;
    int index = mid;
    while (index - 1 >= si && (*(arr + index - 1) == *(arr + mid)))
        index--;
    cout << endl
         << index << endl;

    BTNode<int> *root = new BTNode<int>(*(arr + index));
    root->left = constructBTNode(arr, si, index - 1);
    root->right = constructBTNode(arr, index + 1, li);
    return root;
}

// Construct a linked list from a BTNode
class List
{
public:
    int data;
    List *next;
    List()
    {
        data = 0;
        next = nullptr;
    }
    List(int data)
    {
        this->data = data;
        next = nullptr;
    }
    void display()
    {
        cout << "\nThe Linked list is: \n";
        List *temp = this;
        while (temp != nullptr)
        {
            cout << temp->data << "  ";
            temp = temp->next;
        }
        cout << "\n";
    }
};
pair<List *, List *> constructLL(BTNode<int> *root)
{
    if (root == nullptr)
        return pair<List *, List *>(nullptr, nullptr);

    pair<List *, List *> p1 = constructLL(root->left);
    pair<List *, List *> p2 = constructLL(root->right);
    List *temp = new List(root->data);

    if (p1.first == nullptr && p2.first == nullptr)
    {
        return pair<List *, List *>(temp, temp);
    }
    else
    {
        if (p1.first == nullptr)
        {
            temp->next = p2.first;
            return pair<List *, List *>(temp, p2.second);
        }
        else if (p2.first == nullptr)
        {
            p1.second->next = temp;
            return pair<List *, List *>(p1.first, temp);
        }
        else
        {
            p1.second->next = temp;
            temp->next = p2.first;
            return pair<List *, List *>(p1.first, p2.second);
        }
    }
}

// Root to node path in Binary Tree
vector<int> *rootToNode(BTNode<int> *root, int k)
{
    if (root == nullptr)
        return nullptr;

    if (root->data == k)
    {
        return new vector<int>(1, root->data);
    }
    else
    {
        vector<int> *left = rootToNode(root->left, k);
        vector<int> *right = rootToNode(root->right, k);
        if (left != nullptr)
        {
            left->push_back(root->data);
            return left;
        }
        if (right != nullptr)
        {
            right->push_back(root->data);
            return right;
        }
        else
            return nullptr;
    }
}

class BST
{
    BTNode<int> *root;

public:
    BST()
    {
        root = nullptr;
    }
    ~BST()
    {
        delete root;
    }

    // Member functions
private:
    BTNode<int> *insert(int data, BTNode<int> *root)
    {
        if (root == nullptr)
        {
            BTNode<int> *temp = new BTNode<int>(data);
            return temp;
        }
        else
        {
            if (data >= root->data)
                root->right = insert(data, root->right);
            else
                root->left = insert(data, root->left);
            return root;
        }
    }

public:
    void insert(int data)
    {
        root = insert(data, root);
    }

private:
    BTNode<int> *deleteData(int data, BTNode<int> *root)
    {
        if (root == nullptr)
            ;
        else if (data < root->data)
            root->left = deleteData(data, root->left);
        else if (data > root->data)
            root->right = deleteData(data, root->right);
        else
        {
            if (root->left == nullptr && root->right == nullptr)
            {
                delete root;
                return nullptr;
            }
            else if (root->right == nullptr)
            {
                BTNode<int> *temp = root->left;
                root->left = nullptr;
                delete root;
                return temp;
            }
            else if (root->left == nullptr)
            {
                BTNode<int> *temp = root->right;
                root->right = nullptr;
                delete root;
                return temp;
            }
            else
            {
                BTNode<int> *small = root->right;
                while (small->left != nullptr)
                    small = small->left;

                root->data = small->data;
                root->right = deleteData(small->data, root->right);

                // return root;
            }
        }
        return root;
    }

public:
    void deleteData(int data)
    {
        root = deleteData(data, this->root);
    }

private:
    bool hasData(int data, BTNode<int> *root)
    {
        if (root == nullptr)
            return false;

        if (root->data == data) // root
            return true;
        else if (root->data > data) // Left
        {
            return hasData(data, root->left);
        }
        else if (root->data < data) // Right
        {
            return hasData(data, root->right);
        }
    }

public:
    bool hasData(int data)
    {
        return hasData(data, root);
    }
    void print()
    {
        display(this->root);
    }
};

// Insert Duplicates to the left side of each node.
BTNode<int> *insertDuplicateNodes(BTNode<int> *root)
{
    if (root == nullptr)
        return root;

    root->left = insertDuplicateNodes(root->left);
    root->right = insertDuplicateNodes(root->right);

    if (root->left == nullptr)
    {
        BTNode<int> *temp = new BTNode<int>(root->data);
        root->left = temp;
    }
    else
    {
        BTNode<int> *left = root->left;
        BTNode<int> *temp = new BTNode<int>(root->data);
        temp->left = left;
        root->left = temp;
    }
    return root;
}

// Print pair sums in a binary tree
void makeArray(BTNode<int> *root, vector<int> *v)
{
    if (root == nullptr)
    {
        return;
    }
    else
    {
        v->push_back(root->data);
        makeArray(root->left, v);
        makeArray(root->right, v);
    }
}
void printPairs(BTNode<int> *root, int k)
{
    vector<int> *v = new vector<int>();
    makeArray(root, v);

    sort(v->begin(), v->end());

    vector<int>::iterator i = v->begin(), j = v->end() - 1;
    while (i < j)
    {
        if (*i + *j == k)
        {
            cout << *i << " " << *j << "\n";
            i++;
            j--;
        }
        else if (*i + *j > k)
            j--;
        else
            i++;
    }
}

// Find lowest common ancestor in a tree
int lca(BTNode<int> *root, int a, int b)
{
    if (root == nullptr)
        return -1;

    if (root->data == a || root->data == b)
        return root->data;
    else
    {
        int left = lca(root->left, a, b);
        int right = lca(root->right, a, b);

        if (left == -1 && right == -1)
            return -1;
        else if (left == -1)
            return right;
        else if (right == -1)
            return left;
        else
            return root->data;
    }
}

// Largest BST in a Binary Tree
class quad
{
public:
    int min;
    int max;
    bool isBST;
    int height; // height of largest BST
};
quad largestBST(BTNode<int> *root)
{
    quad q;
    q.min = q.max = 0;
    q.isBST = true;
    q.height = 0;
    if (root == nullptr)
        return q;

    quad left = largestBST(root->left);
    quad right = largestBST(root->right);

    if (root->left == nullptr && root->right == nullptr) // No subtree
    {
        q.min = q.max = root->data;
        q.height++;
        return q;
    }
    else if (root->right == nullptr) // Left subtree
    {
        q.max = max(root->data, left.max);
        q.min = min(root->data, left.min);
        q.height = left.height;
        if (left.isBST)
        {
            if (left.max < root->data)
            {
                q.height = 1 + left.height;
                q.isBST = true;
            }
            else
            {
                q.isBST = false;
            }
        }
        else
            q.isBST = false;
        return q;
    }
    else if (root->left == nullptr) // Right subtree
    {
        q.max = max(root->data, right.max);
        q.min = min(root->data, right.min);
        q.height = right.height;
        if (right.isBST)
        {
            if (root->data <= right.min)
            {
                q.height = 1 + right.height;
                q.isBST = true;
            }
            else
            {
                q.isBST = false;
            }
        }
        else
            q.isBST = false;
        return q;
    }
    else // Both subtree
    {
        q.max = max(root->data, max(left.max, right.max));
        q.min = min(root->data, min(left.min, right.min));
        q.height = max(left.height, right.height);
        if (left.isBST == false || right.isBST == false) // At least one is not BST
        {
            q.isBST = false;
        }
        else // Both are BST
        {
            if (left.max < root->data && root->data <= right.min)
            {
                q.height = 1 + max(left.height, right.height);
                q.isBST = true;
            }
            else
            {
                q.isBST = false;
            }
        }
        return q;
    }
}

// Replace data node with the sum  of nodes in tree containing data greater than or equal to the node
int replaceWithSumGreater(BTNode<int> *root, int aboveSum = 0)
{
    if (root == nullptr)
        return 0;

    int rightSum = root->data + replaceWithSumGreater(root->right, aboveSum);

    // Replace with right side's sum
    root->data = rightSum + aboveSum;

    int totalSum = rightSum + replaceWithSumGreater(root->left, root->data);

    // Return sum of full tree
    return totalSum;
}

// Print path from Root to leaf such that its sum is equal to 'K'
void rootToLeaf(BTNode<int> *root, int K, string path = "")
{
    stringstream str;
    if (root == nullptr || K < root->data)
        return;
    else if (K == root->data)
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            str << root->data;
            string st;
            str >> st;
            path += " " + st;
            cout << path << "\n";
        }
        else
            return;
    }
    else
    {
        str << root->data;
        string st;
        str >> st;
        rootToLeaf(root->left, K - root->data, path + " " + st);
        rootToLeaf(root->right, K - root->data, path + " " + st);
    }
}

// Print at depth K
void printAtDepthK(BTNode<int> *root, int K)
{
    if (K < 0 || root == nullptr)
        return;
    else if (K == 0)
        cout << root->data << "  ";
    else
    {
        printAtDepthK(root->left, K - 1);
        printAtDepthK(root->right, K - 1);
    }
}
// Print all nodes at distance K from a given node
int printNodeAtK(BTNode<int> *root, int K, int data)
{
    if (K < 0 || root == nullptr)
        return -1;
    else if (root->data == data)
    {
        printAtDepthK(root, K);
        return 0;
    }
    else
    {
        // lD+rD+2=K
        // data is either on left or on right

        int lD, rD;
        lD = printNodeAtK(root->left, K, data);

        if (lD + 1 == K)
        {
            cout << root->data << "  ";
            return lD + 1;
        }
        else if (lD != -1)
        {
            printAtDepthK(root->right, K - lD - 2);
            return lD + 1;
        }

        rD = printNodeAtK(root->right, K, data);
        if (rD == -1)
            return -1;
        else if (rD + 1 == K)
        {
            cout << root->data << "  ";
            return rD + 1;
        }
        else
        {
            printAtDepthK(root->left, K - rD - 2);
            return rD + 1;
        }
    }
}

// Pair sum in BST
void pairSum(BTNode<int> *root, int K)
{
    stack<BTNode<int> *> s1, s2;
    BTNode<int> *temp = root;
    while (temp != nullptr)
    {
        s1.push(temp);
        temp = temp->left;
    }
    temp = root;
    while (temp != nullptr)
    {
        s2.push(temp);
        temp = temp->right;
    }

    while (!s1.empty() && !s2.empty())
    {
        BTNode<int> *x, *y;
        x = s1.top();
        y = s2.top();
        if (x == y)
            break;

        bool l = false, r = false;
        if (x->data + y->data == K)
        {
            l = r = true;
            cout << "(" << x->data << ", " << y->data << ")  ";
        }
        else if (x->data + y->data < K)
        {
            l = true;
        }
        else if (x->data + y->data > K)
        {
            r = true;
        }

        if (l)
        {
            s1.pop();
            x = x->right;
            while (x != nullptr)
            {
                s1.push(x);
                x = x->left;
            }
        }
        if (r)
        {
            s2.pop();
            y = y->left;
            while (y != nullptr)
            {
                s2.push(y);
                y = y->right;
            }
        }
    }
}

int main(int argc, char *argv[])
{

    BTNode<int> *root = takeInput();
    display(root);
    string s('.', 30);
    cout << s << endl;

    // BTNode<int> *srch = search(t, 5);
    // if (srch != nullptr)
    //     cout << "Found\n";
    // else
    //     cout << "Not Found\n";

    // printInRange(t, 6, 10);

    // cout << isBTNode3(t);

    // int arr[] = {1, 2, 3, 4, 5, 6, 7};
    // display(constructBTNode(arr, 0, 6));

    // constructLL(t).first->display();

    // int d = 0;
    // cin >> d;
    // vector<int> *vec = rootToNode(t, d);
    // for (int x : *vec)
    // {
    //     cout << x << "  ";
    // }

    // BST t;
    // t.insert(5);
    // t.insert(6);
    // t.insert(3);
    // t.insert(1);
    // t.insert(4);
    // t.insert(0);
    // t.insert(2);
    // t.print();

    // cout << endl
    //      << "..........."
    //      << endl;
    // t.deleteData(1);
    // t.print();

    // root = insertDuplicateNodes(root);
    // display(root);

    // int k;
    // cin >> k;
    // printPairs(root, k);

    // int a, b;
    // cin >> a >> b;
    // cout << "\n"
    //      << lca(root, a, b) << "\n";

    // cout << "Height of largest bst is : " << largestBST(root).height << endl;

    // replaceWithSumGreater(root);
    // cout << "Changed tree: \n";
    // display(root);

    // int K;
    // cout << "Enter the value of K : ";
    // cin >> K;
    // rootToLeaf(root, K);

    // int node;
    // int K;
    // cin >> node >> K;
    // cout << "The nodes at distance K are: \n";
    // printNodeAtK(root, K, node);

    int k;
    cin >> k;
    pairSum(root, k);

    delete root;
    return 0;
}