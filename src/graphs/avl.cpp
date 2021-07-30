#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Entry
{
public:
    string word;
    string meaning;
    Entry *parent;
    Entry *rightChild;
    Entry *leftChild;
    int height;

    Entry()
    {
        this->height = 0;
        this->word.push_back('\0');
        this->meaning.push_back('\0');
        this->parent = NULL;
        this->rightChild = NULL;
        this->leftChild = NULL;
    }
    Entry(string wordInp, string meaningInp)
    {
        for (int i = 0; i < wordInp.size(); i++)
            this->word.push_back(wordInp[i]);
        for (int i = 0; i < meaningInp.size(); i++)
            this->meaning.push_back(meaningInp[i]);
        this->height = 0;
        this->parent = NULL;
        this->rightChild = NULL;
        this->leftChild = NULL;
    }
};

class AVLtree
{
public:
    Entry *root;
    int size;
    int count;

    AVLtree()
    {
        this->root = NULL;
        this->size = 0;
        this->count = 0;
    }

    ~AVLtree()
    {
        if (root == NULL)
            return;
        queue<Entry *> q;
        q.push(root);
        while (!q.empty())
        {
            if (q.front()->leftChild != NULL)
                q.push(q.front()->leftChild);
            if (q.front()->rightChild != NULL)
                q.push(q.front()->rightChild);
            free(q.front());
            q.pop();
        }
        cout << "\nProgram terminated succesfully.\n";
    }

    int getSize()
    {
        return this->size;
    }

    int max(int a, int b)
    {
        if (a >= b)
            return a;
        else
            return b;
    }

    int getHeightDif(Entry *e)
    {
        if (e == NULL)
            return 0;
        else if (e->leftChild == NULL && e->rightChild == NULL)
            return 0;
        else if (e->leftChild == NULL)
            return (-1 - (e->rightChild->height));
        else if (e->rightChild == NULL)
            return (e->leftChild->height + 1);
        else
            return (e->leftChild->height - e->rightChild->height);
    }

    Entry *getRoot()
    {
        return this->root;
    }

    Entry *newNode(string word, string meaning)
    {
        Entry *ptr = new Entry(word, meaning);
        return ptr;
    }

    Entry *rotateRight(Entry *y)
    {
        Entry *x = y->leftChild;
        Entry *T2 = x->rightChild;

        x->rightChild = y;
        y->leftChild = T2;
        if (T2 != NULL)
            T2->parent = y;
        y->parent = x;

        if (y->leftChild != NULL && y->rightChild != NULL)
            y->height = 1 + max(y->leftChild->height, y->rightChild->height);
        else if (y->leftChild != NULL)
            y->height = 1 + y->leftChild->height;
        else if (y->rightChild != NULL)
            y->height = 1 + y->rightChild->height;
        else
            y->height = 0;
        if (x->leftChild != NULL && x->rightChild != NULL)
            x->height = 1 + max(x->leftChild->height, x->rightChild->height);
        else if (x->leftChild != NULL)
            x->height = 1 + x->leftChild->height;
        else if (x->rightChild != NULL)
            x->height = 1 + x->rightChild->height;
        else
            x->height = 0;

        return x;
    }

    Entry *rotateLeft(Entry *y)
    {
        Entry *x = y->rightChild;
        Entry *T2 = x->leftChild;

        x->leftChild = y;
        y->rightChild = T2;
        if (T2 != NULL)
            T2->parent = y;
        y->parent = x;

        if (y->leftChild != NULL && y->rightChild != NULL)
            y->height = 1 + max(y->leftChild->height, y->rightChild->height);
        else if (y->leftChild != NULL)
            y->height = 1 + y->leftChild->height;
        else if (y->rightChild != NULL)
            y->height = 1 + y->rightChild->height;
        else
            y->height = 0;
        if (x->leftChild != NULL && x->rightChild != NULL)
            x->height = 1 + max(x->leftChild->height, x->rightChild->height);
        else if (x->leftChild != NULL)
            x->height = 1 + x->leftChild->height;
        else if (x->rightChild != NULL)
            x->height = 1 + x->rightChild->height;
        else
            x->height = 0;

        return x;
    }

    void insert(Entry *e)
    {
        Entry *node = root;
        this->size++;

        // Normal BST insertion
        if (root == NULL)
        {
            root = newNode(e->word, e->meaning);
            return;
        }
        int f = 1;
        while (f)
        {
            if (node->word < e->word)
            {
                if (node->rightChild == NULL)
                {
                    e->parent = node;
                    node->rightChild = e;
                    f = 0;
                }
                else
                    node = node->rightChild;
            }
            else if (node->word > e->word)
            {
                if (node->leftChild == NULL)
                {
                    e->parent = node;
                    node->leftChild = e;
                    f = 0;
                }
                else
                    node = node->leftChild;
            }
            else
            {
                node->meaning = e->meaning;
                this->size--;
                return;
            }
        }

        // Incresing Height
        node = e->parent;
        while (node != NULL)
        {
            if (node->leftChild != NULL && node->rightChild != NULL)
                node->height = 1 + max(node->leftChild->height, node->rightChild->height);
            else if (node->leftChild != NULL)
                node->height = 1 + node->leftChild->height;
            else if (node->rightChild != NULL)
                node->height = 1 + node->rightChild->height;
            else
                node->height = 0;
            node = node->parent;
        }

        // Balancing Height
        Entry *z, *y, *x, *p;
        z = e->parent; //temp
        y = e;         //aux1
        x = NULL;      //aux2
        int heightDiff;
        while (z != NULL)
        {
            heightDiff = getHeightDif(z);
            if ((heightDiff > 1) || (heightDiff < (-1)))
            {
                p = z->parent;
                if (z->leftChild == y && y->leftChild == x)
                {
                    node = rotateRight(z);
                }
                else if (z->leftChild == y && y->rightChild == x)
                {
                    node = rotateLeft(y);
                    node->parent = z;
                    z->leftChild = node;
                    node = rotateRight(z);
                }
                else if (z->rightChild == y && y->rightChild == x)
                {
                    node = rotateLeft(z);
                }
                else
                {
                    node = rotateRight(y);
                    node->parent = z;
                    z->rightChild = node;
                    node = rotateLeft(z);
                }
                if (p != NULL)
                {
                    node->parent = p;
                    if (p->rightChild == z)
                        p->rightChild = node;
                    else
                        p->leftChild = node;
                }
                else
                {
                    root = node;
                    node->parent = NULL;
                }
                node = node->parent;
                while (node != NULL)
                {
                    if (node->leftChild != NULL && node->rightChild != NULL)
                        node->height = 1 + max(node->leftChild->height, node->rightChild->height);
                    else if (node->leftChild != NULL)
                        node->height = 1 + node->leftChild->height;
                    else if (node->rightChild != NULL)
                        node->height = 1 + node->rightChild->height;
                    else
                        node->height = 0;
                    node = node->parent;
                }
            }
            x = y;
            y = z;
            z = z->parent;
        }
    }

    Entry *findPreSuc(string word)
    {
        Entry *e = search(word);
        if (e != NULL)
        {
            if (e->leftChild != NULL)
            {
                e = e->leftChild;
                while (e->rightChild != NULL)
                    e = e->rightChild;
                return e;
            }
            else if (e->rightChild != NULL)
            {
                e = e->rightChild;
                while (e->leftChild != NULL)
                    e = e->leftChild;
                return e;
            }
            else
                return e->parent;
        }
        else
            return NULL;
    }

    void remove(string word)
    {
        Entry *p, *e = search(word);
        if (e == NULL)
            cout << "\n No such word found in dictionary !\n";
        else
        {
            this->size--;

            //Deleting Node
            if (e->leftChild == NULL && e->rightChild == NULL)
            {
                p = e->parent;
                if (p != NULL)
                {
                    if (p->leftChild == e)
                        p->leftChild = NULL;
                    else
                        p->rightChild = NULL;
                }
                else
                    root = NULL;
                free(e);
            }
            else if (e->leftChild == NULL)
            {
                p = e->parent;
                if (p != NULL)
                {
                    if (p->leftChild == e)
                        p->leftChild = e->rightChild;
                    else
                        p->rightChild = e->rightChild;
                }
                else
                    root = e->rightChild;
                free(e);
            }
            else if (e->rightChild == NULL)
            {
                p = e->parent;
                if (p != NULL)
                {
                    if (p->leftChild == e)
                        p->leftChild = e->leftChild;
                    else
                        p->rightChild = e->leftChild;
                }
                else
                    root = e->leftChild;
                free(e);
            }
            else
            {
                Entry *temp = findPreSuc(word);
                e->word = temp->word;
                e->meaning = temp->meaning;
                p = temp->parent;
                if (temp->leftChild == NULL && temp->rightChild == NULL)
                {
                    if (p != NULL)
                    {
                        if (p->leftChild == temp)
                            p->leftChild = NULL;
                        else
                            p->rightChild = NULL;
                    }
                    else
                        root = NULL;
                    free(temp);
                }
                else if (temp->leftChild != NULL)
                {
                    if (p != NULL)
                    {
                        if (p->leftChild == temp)
                            p->leftChild = temp->leftChild;
                        else
                            p->rightChild = temp->leftChild;
                    }
                    else
                        root = temp->leftChild;
                    free(temp);
                }
                else if (temp->rightChild != NULL)
                {
                    if (p != NULL)
                    {
                        if (p->leftChild == temp)
                            p->leftChild = temp->rightChild;
                        else
                            p->rightChild = temp->rightChild;
                    }
                    else
                        root = temp->rightChild;
                    free(temp);
                }
            }

            //Balancing Height
            Entry *z, *y, *x;
            int h, hDiff;
            while (p != NULL)
            {
                h = p->height;
                if (p->leftChild != NULL && p->rightChild != NULL)
                    p->height = 1 + max(p->leftChild->height, p->rightChild->height);
                else if (p->leftChild != NULL)
                    p->height = 1 + p->leftChild->height;
                else if (p->rightChild != NULL)
                    p->height = 1 + p->rightChild->height;
                else
                    p->height = 0;
                hDiff = getHeightDif(p);
                if (h == p->height)
                    break;
                else if (hDiff <= 1 && hDiff >= (-1))
                {
                    p = p->parent;
                }
                else
                {
                    z = p;
                    p = p->parent;
                    if (z->leftChild != NULL && z->rightChild != NULL)
                    {
                        if (z->leftChild->height >= z->rightChild->height)
                            y = z->leftChild;
                        else
                            y = z->rightChild;
                    }
                    else if (z->leftChild != NULL)
                        y = z->leftChild;
                    else
                        y = z->rightChild;
                    if (y->leftChild != NULL && y->rightChild != NULL)
                    {
                        if (y->leftChild->height >= y->rightChild->height)
                            x = y->leftChild;
                        else
                            x = y->rightChild;
                    }
                    else if (y->leftChild != NULL)
                        x = y->leftChild;
                    else if (y->rightChild != NULL)
                        x = y->rightChild;
                    else
                        x = NULL;
                    Entry *node;
                    if (z->leftChild == y && y->leftChild == x)
                    {
                        node = rotateRight(z);
                    }
                    else if (z->leftChild == y && y->rightChild == x)
                    {
                        node = rotateLeft(y);
                        node->parent = z;
                        z->leftChild = node;
                        node = rotateRight(z);
                    }
                    else if (z->rightChild == y && y->rightChild == x)
                    {
                        node = rotateLeft(z);
                    }
                    else
                    {
                        node = rotateRight(y);
                        node->parent = z;
                        z->rightChild = node;
                        node = rotateLeft(z);
                    }
                    if (p != NULL)
                    {
                        node->parent = p;
                        if (p->rightChild == z)
                            p->rightChild = node;
                        else
                            p->leftChild = node;
                    }
                    else
                    {
                        root = node;
                        node->parent = NULL;
                    }
                }
            }
            cout << " Word Removed !\n";
        }
    }

    Entry *search(string word)
    {
        if (root == NULL)
            return root;
        Entry *node = root;
        while (1)
        {
            if (node == NULL || node->word == word)
                return node;
            else if (node->word < word)
                node = node->rightChild;
            else if (node->word > word)
                node = node->leftChild;
        }
    }

    void showAllInRange(Entry *e, string w1, string w2)
    {
        if (e == NULL)
            return;
        if (e->word > w1)
            showAllInRange(e->leftChild, w1, w2);
        if ((e->word >= w1) && (e->word <= w2))
        {
            cout << e->word << "  :  " << e->meaning << endl;
            this->count++;
        }
        if (e->word < w2)
            showAllInRange(e->rightChild, w1, w2);
    }

    void printInOrder(Entry *e)
    {
        if (e == NULL)
            return;
        printInOrder(e->leftChild);
        cout << e->word << "  :  " << e->meaning << endl;
        printInOrder(e->rightChild);
    }

    void printInLevel()
    {
        if (root == NULL)
            return;
        queue<Entry *> q;
        q.push(root);
        while (!q.empty())
        {
            int c = q.size();
            while (c--)
            {
                cout << q.front()->word << " ";
                if (q.front()->leftChild != NULL)
                    q.push(q.front()->leftChild);
                if (q.front()->rightChild != NULL)
                    q.push(q.front()->rightChild);
                q.pop();
            }
            cout << endl;
        }
    }
};
