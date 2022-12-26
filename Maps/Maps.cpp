#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
using namespace std;

void unorderedMapTesting()
{
    unordered_map<string, int> m1;
    pair<string, int> p("Ayush", 7);

    // for (int i = 1; i <= 11; i++)
    // {
    //     p.second = i;
    //     m1.insert(p);
    // }

    cout << m1.bucket_count() << ", " << m1.size() << ",  " << m1.empty() << endl;

    m1["Aditya"] = 12;
    m1.insert(p);
    p = make_pair("Arpit", 1);
    m1.insert(p);
    m1.insert(make_pair("Vishal", 2));

    cout << "Number of \"Ayush\" keys in unordered_map are: " << m1.count("Ayush") << endl;

    unordered_map<string, int>::iterator i = m1.begin();
    cout << "Size of map is: " << m1.size() << endl;
    // Displaying unordered_map using iterators
    for (int i = 0; i < 3; i++)
    {
        // at() function returns the value for the key
        cout << m1.at("Ayush") << ",  ";
    }
    cout << endl;
    while (i != m1.end())
    {
        // elements in map are stored as pairs
        cout << "(" << i->first << "," << i->second << ")   ";
        i++;
    }
    cout << endl;

    m1["a"] = 1;
    m1["b"] = 1;
    m1["c"] = 1;
    m1["d"] = 1;
    m1["e"] = 1;
    m1["f"] = 1;
    m1["g"] = 1;
    m1["h"] = 1;
    m1["i"] = 1;
    m1["j"] = 1;
    cout << m1.bucket_count() << ", " << m1.size() << ",  " << m1.empty() << endl;
}

void removeDuplicates()
{
    int num = 0;
    cout << "Enter the size of the array: ";
    cin >> num;
    int arr[num];
    cout << "Enter the array elements: " << endl;
    for (int &x : arr)
        cin >> x;

    // Remove duplicates using unordered_map
    unordered_map<int, bool> m1;
    vector<int> v;
    for (int x : arr)
    {
        if (m1.count(x) == 0)
        {
            m1[x] = true;
            v.push_back(x);
        }
    }

    cout << "\nUnique elements are: ";
    // Displaying the unique elements only
    for (vector<int>::iterator i = v.begin(); i < v.end(); i++)
    {
        cout << *i << "  ";
    }
    cout << "\n";
}

template <typename T>
T maximumFrequencyNum(T *arr, int len)
{
    unordered_map<T, int> m1;
    for (int i = 0; i < len; i++)
    {
        if (m1.count(*(arr + i)) == 1)
        {
            m1[*(arr + i)]++;
        }
        else
        {
            m1.insert(make_pair(*(arr + i), 1));
        }
    }

    int freq = 0;
    T num;
    for (auto i = m1.begin(); i != m1.end(); i++)
    {
        if (i->second > freq)
        {
            freq = i->second;
            num = i->first;
        }
    }

    return num;
}

template <typename T>
void printIntersection(T *arr1, int len1, T *arr2, int len2)
{
    unordered_map<T, int> m;
    len1--;
    len2--;
    while (len1 >= 0)
    {
        if (m.count(*(arr1 + len1)) == 0)
        {
            m[*(arr1 + len1)] = 0;
        }
        len1--;
    }
    while (len2 >= 0)
    {
        if (m.count(*(arr2 + len2)) == 1)
        {
            m[*(arr2 + len2)] = 1;
        }
        len2--;
    }
    auto i = m.begin();
    vector<T> v;
    while (i != m.end())
    {
        if (i->second == 0)
        {
            v.push_back(i->first);
        }
        i++;
    }
    for (auto i : v)
    {
        m.erase(i);
    }
    cout << "Array intersection is : ";
    for (auto i = m.begin(); i != m.end(); i++)
    {
        cout << i->first << "  ";
    }
    cout << endl;
}

template <typename T>
int countPairSums(T *arr, int len)
{
    unordered_map<T, int> m;
    int cnt = 0;
    for (int i = 0; i < len; i++)
    {
        if (m.count(*(arr + i)) == 0)
        {
            m[*(arr + i)] = 1;
        }
        else
        {
            m[*(arr + i)]++;
        }
        if (m.count(-*(arr + i)) == 1)
        {
            cnt += m[-*(arr + i)];
        }
    }

    return cnt;
}

template <typename Q>
class CustMap
{
private:
    class list
    {
    public:
        string key;
        Q value;
        list *next;
        list(string key, Q value)
        {
            this->key = key;
            this->value = value;
            next = nullptr;
        }
        ~list()
        {
            delete next;
        }
    };
    int bucket_size = 11;
    list **bucket_array;
    int cnt = 0;

private:
    int getBucketIndex(string key)
    {
        int hashcode = 0;
        int currCoeff = 1;
        for (int i = 0; i < key.length(); i++)
        {
            hashcode += key.at(i) * currCoeff;
            currCoeff *= 37;
            hashcode %= bucket_size;
            currCoeff %= bucket_size;
        }
        return hashcode % bucket_size;
    }
    void rehash()
    {
        bucket_size *= 2;
        list **newBucketArray = new list *[bucket_size];
        for (int i = 0; i < bucket_size; i++)
            newBucketArray[i] = nullptr;

        list **temp = bucket_array;
        bucket_array = newBucketArray;
        newBucketArray = temp;

        for (int i = 0; i < bucket_size / 2; i++)
        {
            list *head = newBucketArray[i];
            while (head != nullptr)
            {
                insert(head->key, head->value);
                head = head->next;
            }
        }

        for (int i = 0; i < bucket_size / 2; i++)
        {
            list *head = newBucketArray[i];
            delete head;
        }
        delete[] newBucketArray;
    }

public:
    CustMap()
    {
        bucket_array = new list *[bucket_size];
        for (int i = 0; i < bucket_size; i++)
            *(bucket_array + i) = nullptr;
    }
    ~CustMap()
    {
        for (int i = 0; i < bucket_size; i++)
        {
            delete bucket_array[i];
        }
        delete[] bucket_array;
    }
    double getLoadFactor()
    {
        return cnt * 1.0 / bucket_size;
    }
    int size()
    {
        return cnt;
    }
    void insert(string key, Q value)
    {
        double loadFactor = 1.0 * cnt / bucket_size;
        if (loadFactor > 0.7)
            rehash();
        int index = getBucketIndex(key);
        list *head = bucket_array[index];
        while (head != nullptr)
        {
            if (head->key == key)
            {
                head->value = value;
                cnt++;
                return;
            }
            head = head->next;
        }
        head = bucket_array[index];
        list *newNode = new list(key, value);
        newNode->next = head;
        bucket_array[index] = newNode;
        cnt++;
    }
    Q getValue(string key)
    {
        Q value;
        int index = getBucketIndex(key);
        list *head = bucket_array[index];
        while (head != nullptr)
        {
            if (head->key == key)
            {
                value = head->value;
                return value;
            }
            head = head->next;
        }
        return 0;
    }
    Q remove(string key)
    {
        Q value;
        int index = getBucketIndex(key);
        list *head = bucket_array[index];
        list *prev = nullptr;
        while (head != nullptr)
        {
            if (head->key == key)
            {
                list *next = head->next;
                if (prev != nullptr)
                    prev->next = next;
                else
                    bucket_array[index] = next;

                head->next = nullptr;
                value = head->value;
                cnt--;
                delete head;
                return value;
            }
            prev = head;
            head = head->next;
        }
        return 0;
    }
};

void printUniqueChars(string st)
{
    unordered_map<char, int> m;
    string s = "";
    for (int i = 0; i < st.length(); i++)
    {
        char ch = st.at(i);
        if (m.count(ch) == 0)
            s = s + ch;
        m.insert({ch, 1});
    }
    cout << s << endl;
}

void longestConsecutiveSequence(int *arr, int len)
{
    unordered_map<int, bool> m;
    for (int i = 0; i < len; i++)
        m.insert({*(arr + i), false});
    int longest = 0, start;
    for (auto i = m.begin(); i != m.end(); i++)
    {
        if (i->second == false)
        {
            int l = 0, s = i->first;
            while (m.count(s) == 1)
            {
                l++;
                m[s++] = true;
            }
            s = i->first;
            while (m.count(--s) == 1)
            {
                l++;
                m[s] = true;
            }
            s++;
            if (l > longest)
            {
                longest = l;
                start = s;
            }
        }
    }
    cout << start << "  " << longest << endl;
}

int kDifferencePairs(int *arr, int len, int K)
{
    unordered_map<int, int> m;
    int cnt = 0;
    for (int i = 0; i < len; i++)
        if (m.count(*(arr + i)) == 1)
            m[*(arr + i)]++;
        else
            m.insert({*(arr + i), 1});

    if (K != 0)
    {
        for (auto x : m)
        {
            if (m.count(x.first - K) == 1)
                cnt += x.second * m.at(x.first - K);
        }
    }
    else
    {
        for (auto x : m)
            cnt += x.second * (x.second - 1) / 2;
    }
    return cnt;
}

void longestSubsetZero(int *arr, int len)
{
    unordered_map<int, int> m;
    m.insert({0, -1});
    int longest = 0, start = -1;

    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum += *(arr + i);
        if (m.count(sum) == 0)
            m.insert({sum, i});
        else
        {
            if (i - m[sum] > longest)
            {
                longest = i - m[sum];
                start = m[sum] + 1;
            }
        }
    }
    cout << longest << "  " << start << endl;
}

int main(void)
{
    // unorderedMapTesting();

    // removeDuplicates();

    // int arr[] = {3, 5, 3, 7, 8, 4, 7, 8, 37,  6, 4, 8, 4, 3, 5, 8, 6, 4};
    // cout << maximumFrequencyNum<int>(arr, sizeof(arr) / 4);

    // int arr[] = {3, 5, 16, 5};
    // int arrr[] = {7, 3, 11, 5};
    // printIntersection<int>(arr, sizeof(arr) / 4, arrr, sizeof(arrr) / 4);

    // int arr[] = {2, 2, -1, -2, 2, -2};
    // cout << countPairSums(arr, sizeof(arr) / 4);

    // CustMap<int> m;
    // m.insert("abc", 2);
    // m.insert("bcd", 5);
    // m.remove("abc");
    // string x = "";
    // for (int i = 1; i <= 9; i++)
    // {
    //     m.insert(x + (char)(i + '0'), i);
    // }
    // cout << m.size() << "  " << m.getLoadFactor() << endl;
    // cout << m.getValue("5") << endl;
    // cout << m.getValue("abc") << "  " << m.getValue("bcd") << endl;

    // printUniqueChars("abbacsabcssal");

    // int arr[] = {2, 12, 9, 16, 10, 5, 3, 20, 25, 11, 1, 8, 6};
    // longestConsecutiveSequence(arr, sizeof(arr) / 4);

    // int arr[] = {4, 4, 4, 4};
    // cout << kDifferencePairs(arr, sizeof(arr) / 4, 0);

    int arr[] = {95, -97, -387, -435, -5, -70, 897, 127, 23, 284};
    longestSubsetZero(arr, sizeof(arr) / 4);
    return 0;
}