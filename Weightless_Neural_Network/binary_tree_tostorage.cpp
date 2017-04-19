#include "binary_tree_tostorage.h"

Binary_tree_ToStorage::Binary_tree_ToStorage(unsigned int numBits)
{
    this->root = NULL;
    this ->numberOfBits = numBits;
}

void Binary_tree_ToStorage::insertTree(vector<bool> &elements)
{
    Ttree *auxTree;
    for(auto const &element: elements){
        auxTree = (element==0)?this->root->left:this->root->right; //zero to left, one to right
        if(auxTree==NULL){
            Ttree *newBit = new Ttree();
            this->startNo(&auxTree, element);
            auxTree = newBit;
        }
    }
}

bool *Binary_tree_ToStorage::searchTree(vector<bool> &elements)
{
    Ttree *auxTree;
    int i=0;
    for(auto const &element: elements){
        auxTree = (element==0)?this->root->left:this->root->right; //zero to left, one to right
        if(auxTree==NULL && i!=(this->numberOfBits-1)) return 0;
        i++;
    }
}


void Binary_tree_ToStorage::startNo(Ttree **root, bool bit)
{
    (*root)->left = NULL;
    (*root)->right = NULL;
    (*root)->bit = bit;
}
