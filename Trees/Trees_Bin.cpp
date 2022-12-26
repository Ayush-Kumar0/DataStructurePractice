#include <iostream>
#include <queue>
#include <stack>
using namespace std;

template <typename T>
class BTree
{
public:
    // Data Members
    T data;
    BTree<T> *left, *right;

    // Constructors
    BTree()
    {
        data = -1;
        left = right = nullptr;
    }
    BTree(T data)
    {
        this->data = data;
        left = right = nullptr;
    }
    ~BTree()
    {
        delete left;
        delete right;
    }
};

// Take Input Recursively
BTree<int> *takeInputR()
{
    cout << "Enter data: ";
    int d;
    cin >> d;
    if (d == -1)
        return nullptr;
    BTree<int> *root = new BTree<int>(d);
    cout << "Left- ";
    root->left = takeInputR();
    cout << "Right- ";
    root->right = takeInputR();
    return root;
}

// Display tree Recursively
void displayPreR(BTree<int> *root) // Preorder traversal print
{
    if (root == nullptr)
        return;
    cout << root->data << " :  ";
    if (root->left != nullptr)
        cout << "L" << root->left->data << " ";
    if (root->right != nullptr)
        cout << "R" << root->right->data;
    cout << "\n";
    displayPreR(root->left);
    displayPreR(root->right);
}
void displayPostR(BTree<int> *root) // Postorder traversal print
{
    if (root == nullptr)
        return;
    if (root->left != nullptr)
        displayPostR(root->left);
    if (root->right != nullptr)
        displayPostR(root->right);
    cout << root->data << "  ";
}
void displayInR(BTree<int> *root) // Inorder traversal print
{
    if (root == nullptr)
        return;
    if (root->left != nullptr)
        displayInR(root->left);
    cout << root->data << "  ";
    if (root->right != nullptr)
        displayInR(root->right);
}

// Better I/O functions
BTree<int> *takeInput()
{
    cout << "Enter data: ";
    int d;
    cin >> d;
    if (d == -1)
        return nullptr;

    BTree<int> *root = new BTree<int>(d);
    queue<BTree<int> *> q;
    q.push(root);
    while (!q.empty())
    {
        BTree<int> *temp = q.front();
        q.pop();

        cout << "Enter left of " << temp->data << " : ";
        cin >> d;
        if (d != -1)
        {
            temp->left = new BTree<int>(d);
            q.push(temp->left);
        }
        cout << "Enter right of " << temp->data << " : ";
        cin >> d;
        if (d != -1)
        {
            temp->right = new BTree<int>(d);
            q.push(temp->right);
        }
    }
    return root;
}

// Better Display function
void display(BTree<int> *root)
{
    if (root == nullptr)
        return;

    queue<BTree<int> *> q;
    q.push(root);
    while (!q.empty())
    {
        BTree<int> *temp = q.front();
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

// Count number of nodes in binary tree
int countNodes(const BTree<int> *root)
{
    int c = 0;
    if (root == nullptr)
        return 0;
    else
    {
        c++;
        if (root->left != nullptr)
            c += countNodes(root->left);
        if (root->right != nullptr)
            c += countNodes(root->right);
        return c;
    }
}

// Return node if data matches
BTree<int> *isPresent(BTree<int> *root, int x)
{
    if (root == nullptr || root->data == x)
        return root;
    else
    {
        BTree<int> *temp1, *temp2;
        temp1 = isPresent(root->left, x);
        temp2 = isPresent(root->right, x);
        if (temp1 != nullptr)
            return temp1;
        else if (temp2 != nullptr)
            return temp2;
        else
            return nullptr;
    }
}

// Calculate height of tree
int height(BTree<int> *root)
{
    if (root == nullptr)
        return 0;
    else
    {
        return 1 + max(height(root->left), height(root->right));
    }
}

// Mirror the given tree
void mirrorTree(BTree<int> *root)
{
    if (root == nullptr)
        return;
    else
    {
        mirrorTree(root->left);
        mirrorTree(root->right);
        BTree<int> *swap = root->left;
        root->left = root->right;
        root->right = swap;
    }
}

// Make tree using Preorder and Inorder traversal
BTree<int> *makeTree1(int pre[], int in[], int l)
{
    if (l == 0)
        return nullptr;

    int rootIndex = 0;
    while (in[rootIndex++] != pre[0])
        ;
    rootIndex--;

    BTree<int> *root = new BTree<int>(pre[0]);
    BTree<int> *left = makeTree1(pre + 1, in, rootIndex);
    BTree<int> *right = makeTree1(pre + 1 + rootIndex, in + rootIndex + 1, l - 1 - rootIndex);
    root->left = left;
    root->right = right;

    return root;
}

// Make tree using Postorder and Inorder traversal
BTree<int> *makeTree2(int post[], int in[], int l)
{
    if (l == 0)
        return nullptr;

    int rootIndex = 0;
    while (in[rootIndex++] != post[l - 1])
        ;
    rootIndex--;

    BTree<int> *root = new BTree<int>(post[l - 1]);
    BTree<int> *left = makeTree2(post, in, rootIndex);
    BTree<int> *right = makeTree2(post + rootIndex, in + rootIndex + 1, l - 1 - rootIndex);
    root->left = left;
    root->right = right;

    return root;
}

// Find diameter of a tree
int diameter1(BTree<int> *root)
{
    if (root == nullptr)
        return 0;

    return max(height(root->left) + height(root->right), max(diameter1(root->left), diameter1(root->right)));
}

// Find Diameter of tree using pair class
pair<int, int> *diameter2(BTree<int> *root)
{
    pair<int, int> *p = new pair<int, int>(0, 0);
    if (root == nullptr)
        return p;

    pair<int, int> *p1 = diameter2(root->left);
    pair<int, int> *p2 = diameter2(root->right);

    /*
        first : height
        second : diameter
    */

    p->first = 1 + max(p1->first, p2->first);
    p->second = max(p->first, max(p1->second, p2->second));
    delete p1, p2;

    return p;
}

// Find max and min in a tree
pair<int, int> *min_max(BTree<int> *root)
{
    if (root == nullptr)
    {
        pair<int, int> *p = new pair<int, int>(-1, -1);
        return p;
    }
    pair<int, int> *p = new pair<int, int>(root->data, root->data);

    pair<int, int> *p1 = min_max(root->left);
    pair<int, int> *p2 = min_max(root->right);

    // Maximum
    if (p1->first != -1 && p2->first != -1)
        p->first = max(root->data, max(p1->first, p2->first));
    else if (p1->first != -1)
        p->first = max(root->data, p1->first);
    else if (p2->first != -1)
        p->first = max(root->data, p2->first);
    else
        p->first = p->first;

    // Minimum
    if (p1->second != -1 && p2->second != -1)
        p->second = min(p->second, min(p1->second, p2->second));
    else if (p1->second != -1)
        p->second = min(p->second, p1->second);
    else if (p2->second != -1)
        p->second = min(p->second, p2->second);
    else
        p->second = p->second;

    return p;
}

// Sum of nodes
int sumOfNode(BTree<int> *root)
{
    if (root == nullptr)
        return 0;
    return root->data + sumOfNode(root->left) + sumOfNode(root->right);
}

// Check if tree is balanced
int balanced(BTree<int> *root)
{
    /*
        We will return height of the tree if it is balanced, and
        if it is not balanced then we return -1 .
    */
    if (root == nullptr)
        return 0;
    int lH = balanced(root->left);
    int rH = balanced(root->right);

    int lJoints = lH;
    if (root->left != nullptr)
        lJoints++;
    int rJoints = rH;
    if (root->right != nullptr)
        rJoints++;

    if (lH != -1 && rH != -1)
    {
        int diff = lJoints - rJoints;
        diff = (diff > 0) ? diff : -diff;
        if (diff <= 1)
            return 1 + max(lH, rH);
        else
            return -1;
    }
    else
        return -1;
}

// Print level-order traversal each level in next line
void displayNextLine(BTree<int> *root)
{
    if (root == nullptr)
        return;

    queue<BTree<int> *> q;
    q.push(root);
    q.push(nullptr);

    cout << root->data << "\n";
    while (!q.empty())
    {
        BTree<int> *temp = q.front();
        q.pop();

        if (temp == nullptr)
        {
            if (q.empty())
                break;
            cout << "\n";
            q.push(nullptr);
        }
        else
        {
            if (temp->left != nullptr)
            {
                cout << temp->left->data << " ";
                q.push(temp->left);
            }
            if (temp->right != nullptr)
            {
                cout << temp->right->data << " ";
                q.push(temp->right);
            }
        }
    }
}

// Remove leaf nodes in binary tree
BTree<int> *removeLeaves(BTree<int> *root)
{
    if (root->left == nullptr && root->right == nullptr)
    {
        delete root;
        return nullptr;
    }
    else
    {
        if (root->left != nullptr)
            root->left = removeLeaves(root->left);
        if (root->right != nullptr)
            root->right = removeLeaves(root->right);
        return root;
    }
}

// Create array of head of linked lists of each level and return it.
class List
{
public:
    int data;
    List *next;
    List(int data)
    {
        this->data = data;
        next = nullptr;
    }
};
vector<List *> *treeLinkedList(BTree<int> *root)
{
    queue<BTree<int> *> q;
    vector<List *> *v = new vector<List *>();

    q.push(root);
    q.push(nullptr);

    while (!q.empty())
    {
        BTree<int> *temp = q.front();

        List *head = new List(temp->data);
        List *tail = head;

        if (temp->left != nullptr)
            q.push(temp->left);
        if (temp->right != nullptr)
            q.push(temp->right);
        q.pop();

        while (tail != nullptr)
        {
            if (q.front() == nullptr)
            {
                v->push_back(head);
                tail = nullptr;
            }
            else
            {
                List *t = new List(q.front()->data);
                tail->next = t;
                tail = tail->next;

                if (q.front()->left != nullptr)
                    q.push(q.front()->left);
                if (q.front()->right != nullptr)
                    q.push(q.front()->right);
            }
            q.pop();
        }

        if (q.empty())
            break;
        else
            q.push(nullptr);
    }

    return v;
}
void printLLVector(vector<List *> *list)
{
    cout << "\nThe Lists in vector are: \n";
    for (int i = 0; i < list->size(); i++)
    {
        List *head = list->at(i);
        while (head != nullptr)
        {
            cout << head->data << "  ";
            head = head->next;
        }
        cout << "\n";
    }
}

// Print tree in zig-zag manner
// Using 2 stacks
void zigZagDisplay(BTree<int> *root)
{
    stack<BTree<int> *> s1; // L->R
    stack<BTree<int> *> s2; // R->L

    s2.push(root);

    while (!(s1.empty() && s2.empty()))
    {
        while (!s1.empty())
        {
            BTree<int> *temp = s1.top();
            cout << temp->data << "  ";
            s1.pop();

            if (temp->right != nullptr)
                s2.push(temp->right);
            if (temp->left != nullptr)
                s2.push(temp->left);
        }
        cout << endl;
        while (!s2.empty())
        {
            BTree<int> *temp = s2.top();
            cout << temp->data << "  ";
            s2.pop();

            if (temp->left != nullptr)
                s1.push(temp->left);
            if (temp->right != nullptr)
                s1.push(temp->right);
        }
        cout << endl;
    }
}

// Print nodes with no siblings
void printNoSibling(BTree<int> *root)
{
    if (root == nullptr)
        return;

    if (root->left != nullptr && root->right == nullptr)
    {
        cout << root->left->data << "  ";
    }
    if (root->left == nullptr && root->right != nullptr)
    {
        cout << root->right->data << "  ";
    }

    printNoSibling(root->left);
    printNoSibling(root->right);
}

int main(int argc, char *argv[])
{
    // 1 2 3 4 5 6 7 -1 -1 -1 -1 8 9 -1 -1 -1 -1 -1 -1
    BTree<int> *t = new BTree<int>();
    t = takeInput();
    cout << "\n";
    display(t);

    // cout << "Number of nodes in this Binary Tree are: " << countNodes(t) << "\n";
    // cout << "Node Present = " << (isPresent(t, -1) != nullptr) << endl;

    // cout << "Height of tree = " << height(t) << endl;

    // mirrorTree(t);
    // display(t);

    // displayInR(t);

    // int size = 0;
    // cout << "Enter size of array: ";
    // cin >> size;
    // int pre[size], in[size];
    // cout << "Enter preorder traversal :  ";
    // for (int &x : pre)
    //     cin >> x;
    // cout << "Enter inorder traversal :  ";
    // for (int &x : in)
    //     cin >> x;
    // t = makeTree1(pre, in, size);
    // display(t);

    // int size = 0;
    // cout << "Enter size of array: ";
    // cin >> size;
    // int post[size], in[size];
    // cout << "Enter postorder traversal :  ";
    // for (int &x : post)
    //     cin >> x;
    // cout << "Enter inorder traversal :  ";
    // for (int &x : in)
    //     cin >> x;
    // t = makeTree2(post, in, size);
    // display(t);

    // cout << "Max: " << min_max(t)->first << " , Min: " << min_max(t)->second << endl;

    // cout << "sum of nodes is: " << sumOfNode(t) << endl;

    // cout << "Tree is balanced/unbalanced: " << ((balanced(t) == -1) ? "No" : "Yes") << endl;

    // displayNextLine(t);

    // removeLeaves(t);
    // display(t);

    // printLLVector(treeLinkedList(t));

    // zigZagDisplay(t);

    printNoSibling(t);

    return 0;
}