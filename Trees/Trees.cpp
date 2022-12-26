#include <iostream>
#include <vector>
#include <queue>
using namespace std;

template <typename T>
class Tree
{
public:
    // Data Members
    T data;
    vector<Tree<T> *> children;

    // Constructors
    Tree()
    {
        data = 0;
        // children = nullptr;  no need to write
    }
    // Destructor
    ~Tree()
    {
        for (int i = 0; i < children.size(); i++)
            delete children.at(i);
    }
    // Functions

    // Recursive I/O :
    void takeInputR()
    {
        cout << "Enter data: ";
        cin >> data;
        cout << "Enter no. of nodes: ";
        int n;
        cin >> n;
        if (n != 0)
            cout << "Enter nodes: ";
        for (int i = 0; i < n; i++)
        {
            Tree<T> *temp = new Tree<T>;
            temp->takeInputR();
            children.push_back(temp);
        }
    }
    // Pre-order traversal
    void displayPre()
    {
        cout << data << " ";
        for (int i = 0; i < children.size(); i++)
            children.at(i)->displayPre();
    }
    // Post-order traversal
    void displayPost()
    {
        for (int i = 0; i < children.size(); i++)
            children.at(i)->displayPost();
        cout << data << " ";
    }

    // Iterative/Level-wise I/O
    void takeInput()
    {
        queue<Tree<T> *> q;
        cout << "Enter root data: ";
        cin >> this->data;
        q.push(this);

        while (!q.empty())
        {
            Tree<T> *temp = q.front(); // parent node
            q.pop();
            cout << "Enter no. of children of " << temp->data << " : ";
            int l = 0;
            cin >> l;
            for (int i = 0; i < l; i++)
            {
                Tree<T> *child = new Tree<T>; // child node
                cout << "Enter node " << i << " : ";
                cin >> child->data;
                temp->children.push_back(child);
                q.push(child);
            }
        }
    }
    void takeInput1Line()
    {
        queue<Tree<T> *> q;
        // cout << "Enter root data: ";
        cin >> this->data;
        q.push(this);

        while (!q.empty())
        {
            Tree<T> *temp = q.front(); // parent node
            q.pop();
            // cout << "Enter no. of children of " << temp->data << " : ";
            int l = 0;
            cin >> l;
            for (int i = 0; i < l; i++)
            {
                Tree<T> *child = new Tree<T>; // child node
                // cout << "Enter node " << i << " : ";
                cin >> child->data;
                temp->children.push_back(child);
                q.push(child);
            }
        }
    }
    // Iterative/Level-wise display
    void display()
    {
        queue<Tree<T> *> q;
        q.push(this);

        while (!q.empty())
        {
            Tree<T> *temp = q.front();
            q.pop();
            cout << temp->data << " :  ";
            for (int i = 0; i < temp->children.size(); i++)
            {
                Tree<T> *child = temp->children.at(i);
                cout << child->data << " ";
                q.push(child);
            }
            cout << "\n";
        }
    }

    int height()
    {
        int h = 0;
        for (int i = 0; i < children.size(); i++)
        {
            int h2 = children.at(i)->height();
            if (h2 > h)
                h = h2;
        }
        return h + 1;
    }

    void printAtDepth(int k)
    {
        if (k == 0)
        {
            cout << data << "  ";
        }
        else
        {
            for (int i = 0; i < children.size(); i++)
            {
                children.at(i)->printAtDepth(k - 1);
            }
        }
    }

    int leavesCount()
    {
        int n = 0;
        if (children.size() == 0)
            n++;
        else
            for (int i = 0; i < children.size(); i++)
            {
                n += children.at(i)->leavesCount();
            }
        return n;
    }
};

// Count number of nodes in a tree
template <typename T>
int numOfNodes(const Tree<T> *root)
{
    int n = 1;
    for (int i = 0; i < root->children.size(); i++)
    {
        n += numOfNodes(root->children.at(i));
    }
    return n;
}

// Sum of all nodes in a tree
template <typename T>
int sumOfNodes(const Tree<T> *root)
{
    int sum = root->data;
    for (int i = 0; i < root->children.size(); i++)
    {
        sum += sumOfNodes(root->children.at(i));
    }
    return sum;
}

// Node with largest data
template <typename T>
Tree<T> *largestData(Tree<T> *root)
{
    Tree<T> *largest = root;
    for (int i = 0; i < root->children.size(); i++)
    {
        Tree<T> *temp = largestData(root->children.at(i));
        if (temp->data > largest->data)
        {
            largest = temp;
        }
    }
    return largest;
}

class Pair1
{
public:
    Tree<int> *node;
    int max_sum;
    Pair1(Tree<int> *node, int max_sum)
    {
        this->node = node;
        this->max_sum = max_sum;
    }
};
Pair1 *maxNode(Tree<int> *root)
{
    int sum = root->data;
    for (int i = 0; i < root->children.size(); i++)
    {
        sum += root->children.at(i)->data;
    }
    Tree<int> *max = root;
    for (int i = 0; i < root->children.size(); i++)
    {
        Tree<int> *temp = maxNode(root->children.at(i))->node;
        int sumTemp = maxNode(root->children.at(i))->max_sum;
        if (sumTemp > sum)
        {
            sum = sumTemp;
            max = temp;
        }
    }
    Pair1 *p = new Pair1(max, sum);
    return p;
}

bool structurallyIdentical(Tree<int> *root1, Tree<int> *root2)
{
    if (root1->data == root2->data)
    {
        int l1 = root1->children.size();
        int l2 = root2->children.size();
        if (l1 == 0 && l2 == 0)
            return true;
        else
        {
            if (l1 == l2)
            {
                bool c = true;
                for (int i = 0; i < l1; i++)
                {
                    c = c && structurallyIdentical(root1->children.at(i), root2->children.at(i));
                }
                return c;
            }
        }
    }
    return false;
}

// Driver function
Tree<int> *nextInteger(Tree<int> *root, int n)
{
    Tree<int> *next = nullptr;
    if (root->data > n)
        next = root;

    for (int i = 0; i < root->children.size(); i++)
    {
        Tree<int> *temp = nextInteger(root->children.at(i), n);
        if (next == nullptr)
            next = temp;
        else if (temp != nullptr)
        {
            if (next->data > n && temp->data < next->data)
                next = temp;
        }
    }
    return next;
}

class Pair2
{
public:
    Tree<int> *M, *SM;
};
Pair2 *secondLargest(Tree<int> *root)
{
    Pair2 *ans = new Pair2();
    ans->M = root;
    ans->SM = nullptr;

    for (int i = 0; i < root->children.size(); i++)
    {
        Pair2 *temp = secondLargest(root->children.at(i));
        Tree<int> *swap;

        // Cases begin
        if (ans->SM == nullptr && temp->SM == nullptr) // Both SM nullptr
        {
            if (temp->M->data > ans->M->data)
            {
                swap = ans->M;
                ans->M = temp->M;
                ans->SM = swap;
            }
            else if (temp->M->data < ans->M->data)
            {
                ans->SM = temp->M;
            }
        }
        else if (ans->SM == nullptr) // SM of current node nullptr
        {
            if (temp->M->data > ans->M->data)
            {
                swap = ans->M;
                ans->M = temp->M;
                if (swap->data >= temp->SM->data)
                    ans->SM = swap;
                else
                    ans->SM = temp->SM;
            }
            else if (temp->M->data < ans->M->data)
            {
                ans->SM = temp->M;
            }
            else
            {
                ans->SM = temp->SM;
            }
        }
        else if (temp->SM == nullptr) // SM of children node nullptr
        {
            if (ans->M->data > temp->M->data)
            {
                ans->SM = temp->M;
            }
            else if (ans->M->data == temp->M->data)
            {
            }
            else
            {
                swap = ans->M;
                ans->M = temp->M;
                if (swap->data > ans->SM->data)
                {
                    ans->SM = swap;
                }
            }
        }
        else // SM is not nullptr
        {
            if (ans->M->data > temp->M->data)
            {
                ans->SM = temp->M;
            }
            else if (ans->M->data == temp->M->data)
            {
                if (ans->SM->data < temp->SM->data)
                    ans->SM = temp->SM;
            }
            else
            {
                swap = ans->M;
                ans->M = temp->M;

                if (ans->SM->data >= temp->SM->data)
                    ans->SM = swap;
                else
                {
                    if (swap->data >= temp->SM->data)
                        ans->SM = swap;
                    else
                        ans->SM = temp->SM;
                }
            }
        }
        // Cases end
    }
    return ans;
}

void replaceWithDepth(Tree<int> *root, int depth = 0)
{
    root->data = depth;
    for (int i = 0; i < root->children.size(); i++)
    {
        replaceWithDepth(root->children.at(i), depth + 1);
    }
}

int main(int argc, char *argv[])
{
    Tree<int> t;
    t.takeInput1Line();
    t.display();

    // cout << "Number of nodes in tree is : " << numOfNodes<T>(&t) << endl;
    // cout << "Sum of data of nodes in tree is : " << sumOfNodes<T>(&t) << endl;
    // cout << "Largest data in tree is : " << largestData<T>(&t)->data << endl;
    // cout << "Height of tree is : " << t.height() << endl;
    // t.printAtDepth(1);
    // cout << "Number of leaves are : " << t.leavesCount() << endl;
    // t.takeInput1Line();
    // t.displayPre();
    // cout << "\n";
    // t.displayPost();
    // delete &t; // Although we dont't need to write

    // cout << "Node with max child-sum = " << maxNode(&t)->node->data << endl;

    // Tree<int> t2;
    // t2.takeInput1Line();
    // t2.display();
    // cout << endl
    //      << structurallyIdentical(&t, &t2);

    // int c;
    // cin >> c;
    // cout << "The next integer is: " << nextInteger(&t, c)->data << endl;

    // cout << "The second largest integer is: " << secondLargest(&t)->SM->data << endl;

    replaceWithDepth(&t);

    t.display();

    return 0;
}