#ifndef BINARY_TREE_TOSTORAGE_H
#define BINARY_TREE_TOSTORAGE_H

#include <iostream>
#include <vector>

using namespace std;

typedef struct tree{
    bool bit;
    struct tree *left;
    struct tree *right;
}Ttree;

class Binary_tree_ToStorage
{
public:
    Binary_tree_ToStorage(unsigned int numBits);
    void insertTree(vector<bool> &elements);
    bool *searchTree(vector<bool> &elements);

private:
    void startNo(Ttree **root, bool bit);
    Ttree *root;
    unsigned int numberOfBits;
};

#endif // BINARY_TREE_TOSTORAGE_H
