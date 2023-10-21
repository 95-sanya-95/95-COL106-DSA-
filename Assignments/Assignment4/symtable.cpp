/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

bool is_large(string str1, string str2)
{                                    // str1 is ahead of str2
    int result = str1.compare(str2); // The first string comes before the second string in lexicographic order.
    if (result < 0)
    {
        return false; // str1 << str2
    }
    else if (result > 0)
    {
        return true; // str2 << str1
    }
    else
    {
        return false;
    }
}

void insert_rec(SymEntry *&current, SymEntry *&element)
{
    if (current == nullptr)
    {
        current = element;
        return;
    }
    else if (is_large(element->key, current->key))
    {
        insert_rec(current->right, element);
    }
    else if (!is_large(element->key, current->key))
    {
        insert_rec(current->left, element);
    }
    return;
}

UnlimitedRational *find(SymEntry *current, string k)
{
    // if (current == nullptr)
    // {
    //     return nullptr; // not found case
    // }
    // if (current->key == k)
    // {  // cout<<"sanya"<<endl;
    //     UnlimitedRational* q = current->val;
    //     cout<<q->get_frac_str()<<endl;
    //     return q;
    // }
    // else if (k>current->key) //is_large(k, current->key)
    // {   //cout<<"right"<<endl;
    //     find(current->right, k);
    // }
    // else if (k<current->key)
    // {
    //     find(current->left, k);
    // }
    while (current != nullptr) {
        if (current->key == k) {
            return current->val;  
        } else if (k>current->key) {
            current = current->right;  
        } else {
            current = current->left;   
        }
    }
    return nullptr;
}

SymEntry *findMin(SymEntry *root)
{
    while (root->left != nullptr)
    {
        root = root->left;
    }
    return root;
}

void deleteNode(SymEntry *root, string key, SymEntry *parent)
{
    if (root == nullptr)
    {
        return;
    }
    if (!is_large(key, root->key))
    {
        deleteNode(root->left, key, root);
    }
    else if (is_large(key, root->key))
    {
        deleteNode(root->right, key, root);
    }
    else
    {
        if (root->left == nullptr)
        {
            SymEntry *temp = root->right;
            root->left = nullptr;
            root->right = nullptr;
            delete root;

            if (parent != nullptr)
            {
                if (parent->left == root)
                {
                    parent->left = temp;
                }
                else
                {
                    parent->right = temp;
                }
            }
            return;
        }
        else if (root->right == nullptr)
        {
            SymEntry *temp = root->left;
            root->left = nullptr;
            root->right = nullptr;
            delete root;

            if (parent != nullptr)
            {
                if (parent->left == root)
                {
                    parent->left = temp;
                }
                else
                {
                    parent->right = temp;
                }
            }
            return;
        }

        SymEntry *temp = findMin(root->right);
        root->key = temp->key;
        deleteNode(root->right, temp->key, root);
    }
    return;
}

SymbolTable::SymbolTable()
{   root = nullptr;
    size = 0;
}

SymbolTable::~SymbolTable()
{ 
    delete root;
}

void SymbolTable::insert(string k, UnlimitedRational *v)
{// {   SymEntry *element = new SymEntry(k, v);
    if (root == nullptr) {
        root = new SymEntry(k, v); 
        size++;
    }
    else{
    SymEntry *current = root;
    while (current!=nullptr) {
        if (k < root->key) {
            if (current->left == nullptr) {
                current->left = new SymEntry(k, v); 
                size++;
                break;
            }
            current = current->left;
        } 
        else if (k > root->key){
            if (current->right == nullptr) {
                current->right = new SymEntry(k, v); 
                size++;
                break;
            }
            current = current->right;
        }
        else{
            return;
        }
    }
}
}

void SymbolTable::remove(string k)
{
    SymEntry *parent = nullptr;
    deleteNode(root, k, parent);
    size--;
}

UnlimitedRational *SymbolTable::search(string k)
{   
     SymEntry *current = root;
    while (current != nullptr) {
        if (current->key == k) {
            return current->val;  
        } else if (k>current->key) {
            current = current->right;  
        } else {
            current = current->left;   
        }
    }
    return nullptr;
}

int SymbolTable::get_size()
{
    return size;
}

SymEntry *SymbolTable::get_root()
{
    return root;
}


