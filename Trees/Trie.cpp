#include <iostream>
using namespace std;

// Trie Data Structure
class Trie
{

public:
    char letter;
    Trie **children;
    bool isTerminal;
    // Above members should be private

    Trie()
    {
        letter = 0;
        children = new Trie *[26];
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
        isTerminal = false;
    }

    void insertWord(string word)
    {
        if (word.length() == 0)
        {
            this->isTerminal = true;
            return;
        }
        char ch = word.at(0);
        ch = tolower(ch);

        Trie *child;
        if (children[ch - 'a'] == nullptr)
        {
            child = new Trie();
            children[ch - 'a'] = child;
        }
        else
        {
            child = children[ch - 'a'];
        }

        child->letter = ch;

        child->insertWord(word.substr(1));
        return;
    }

    void display(string word = "")
    {
        if (this->isTerminal == true)
        {
            cout << word + this->letter << "\n";
        }

        word = word + this->letter;
        for (int i = 0; i < 26; i++)
        {
            Trie *child = this->children[i];
            if (child != nullptr)
            {
                child->display(word);
            }
        }
    }

    bool isWordPresent(string word)
    {
        if (word.length() == 0)
        {
            return this->isTerminal;
        }

        char ch = word.at(0);
        ch = tolower(ch);

        Trie *child = this->children[ch - 'a'];
        if (child == nullptr)
            return false;
        else
        {
            return child->isWordPresent(word.substr(1));
        }
    }

private:
    bool hasChildren(Trie *node)
    {
        bool flag = false;
        for (int i = 0; i < 26; i++)
        {
            if (node->children[i] != nullptr)
            {
                flag = true;
                break;
            }
        }
        return flag;
    }

public:
    bool removeWord(string word)
    {
        if (word.length() == 0)
        {
            return true;
        }

        char ch = tolower(word.at(0));
        Trie *child = this->children[ch - 'a'];
        if (child == nullptr)
            return false;
        else
        {
            bool isPresent = child->removeWord(word.substr(1));
            if (isPresent)
            {
                if (word.length() == 1)
                    child->isTerminal = false;
                if (!hasChildren(child) && child->isTerminal == false)
                {
                    delete child;
                    this->children[ch - 'a'] = nullptr;
                }
            }
            return isPresent;
        }
    }

    // Auto-complete
    void autoComplete(string word, string path = "")
    {
        int len = word.length();
        if (this->isTerminal == true && len == 0)
        {
            cout << path << endl;
        }

        if (len == 0)
        {
            for (int i = 0; i < 26; i++)
            {
                if (this->children[i] != nullptr)
                    this->children[i]->autoComplete(word, path + this->children[i]->letter);
            }
            return;
        }
        else
        {
            char ch = word.at(0);
            Trie *child = this->children[ch - 'a'];
            if (child == nullptr)
                return;
            else
            {
                child->autoComplete(word.substr(1), path + ch);
                return;
            }
        }
    }
};

class SuffixTrie
{
    Trie trie;

public:
    void insertWord(string word)
    {
        while (word.length() != 0)
        {
            trie.insertWord(word);
            word = word.substr(1);
        }
    }

    void display()
    {
        trie.display();
    }

private:
    bool patternMatchPrivate(Trie *trie, string pattern)
    {
        if (pattern.length() == 0)
            return true;

        char ch = pattern.at(0);
        Trie *child = trie->children[ch - 'a'];
        if (child == nullptr)
            return false;
        else
            return patternMatchPrivate(child, pattern.substr(1));
    }

public:
    bool patternMatch(string pattern)
    {
        return patternMatchPrivate(&trie, pattern);
    }
};

// Check if there exist a pair which after joining becomes palindrome or is there a plaindrome word in the queries
bool isPalin(string word)
{
    bool palin = true;
    int len = word.length();
    for (int i = 0; i < len / 2; i++)
    {
        if (word.at(i) != word.at(len - i - 1))
        {
            palin = false;
            break;
        }
    }
    return palin;
}
string reverse(string word)
{
    int len = word.length();
    for (int i = 0; i < len / 2; i++)
    {
        word.at(i) = word.at(len - i - 1) ^ word.at(i) ^ (word.at(len - i - 1) = word.at(i));
    }
    return word;
}
void checkPalindrome()
{
    Trie trie;
    bool flag = false;
    int n;
    cin >> n;
    while (n--)
    {
        string word;
        cin >> word;
        trie.insertWord(word);
        if (flag == false)
        {
            if (isPalin(word))
                flag = true;
            else if (trie.isWordPresent(reverse(word)))
                flag = true;
        }
    }
    cout << boolalpha << flag << endl;
}

int main(int argc, char *argv[])
{
    // Trie trie;
    // trie.insertWord("ayush");
    // trie.insertWord("ayu");
    // trie.insertWord("piyush");
    // trie.insertWord("im");
    // trie.display();
    // cout << "\nAfter removing:\n";
    // trie.removeWord("ayush");
    // trie.display();

    // SuffixTrie strie;
    // int len = 0;
    // cin >> len;
    // for (int i = 0; i < len; i++)
    // {
    //     string word;
    //     cin >> word;
    //     strie.insertWord(word);
    // }
    // strie.display();
    // string pattern;
    // cin >> pattern;
    // cout << boolalpha << strie.patternMatch(pattern) << endl;

    // checkPalindrome();

    Trie trie;
    int len;
    cin >> len;
    while (len--)
    {
        string word;
        cin >> word;
        trie.insertWord(word);
    }
    string word;
    cin >> word;
    trie.autoComplete(word);

    return 0;
}