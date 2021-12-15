#include <stdio.h>
#include <stdlib.h>
#include "primitiveDefs.h"

struct avlNode
{
    int32 val;
    avlNode *p;
    avlNode *l;
    avlNode *r;
};

#if 0
void avl_leftRotate(avlNode **root)
{
    //Still need to do rebalancing

    avlNode *oldRoot = *root;
    avlNode *newRoot = oldRoot->r;
    newRoot->p = oldRoot->p;
    oldRoot->p = newRoot;
    oldRoot->r = newRoot->l;
    newRoot->l = oldRoot;
    *root = newRoot;

#if 0    
    
    int32 temp = root->val;
    root->val = root->l->val;
    root->l->val = root->l->l->val;
    root->l->l->val = temp;
    
    avlNode* tempPtr = root->l->l;
    root->l->l = NULL;
    root->r = tempPtr;

#endif
}

void avl_rightRotate(avlNode **root)
{
    //TODO: Still need to do rebalancing

    avlNode *oldRoot = *root;
    avlNode *newRoot = oldRoot->l;
    newRoot->p = oldRoot->p;
    oldRoot->p = newRoot;
    oldRoot->l = newRoot->r;
    newRoot->r = oldRoot;
    *root = newRoot;

#if 0    
    int32 temp = root->val;
    root->val = root->r->val;
    root->r->val = root->r->r->val;
    root->r->r->val = temp;
    
    avlNode* tempPtr = root->r->r;
    root->r->r = NULL;
    root->l= tempPtr;
#endif
}

void avl_rebalance(avlNode *root)
{

    avlNode *oldRoot = root;
    //do rebalancing here
    int32 temp = root->bal;
    int32 mask = temp >> 31;
    temp ^= mask;
    temp += mask & 1;

    //TODO: research https://graphics.stanford.edu/~seander/bithacks.html#IntegerAbs and other bitwise tricks

    if (temp > 1) //unbalanced
    {
        if (root->bal > 0)
        {                         //LL or LR
            if (root->l->bal > 0) //LL
            {
                avl_rightRotate(&root);
                if(!root->p)
                {
                    root->r->bal -= 2;
                }
            }
            else // LR
            {
                avl_leftRotate(&root->l);
                avl_rightRotate(&root);
            }
            root->bal = 0;
            if (root->p)
            {
                root->p->bal++;
                root->p->l = root;
            }
        }
        else
        {                         //RL or RR
            if (root->r->bal < 0) // RR
            {
                avl_leftRotate(&root);
                if(!root->p)
                {
                    root->l->bal += 2;
                }
            }
            else
            {
                avl_rightRotate(&root->r);
                avl_leftRotate(&root);
            }

            root->bal = 0;
            if (root->p)
            {
                root->p->bal++;
                oldRoot->bal = 0;
                root->p->r = root;
            }
        }
    }
    else
    {
        if (root->p)
            avl_rebalance(root->p);
    }
}

//Ensure that tree is balanced before insertion
void avl_insert(avlNode **rootptr, int32 val)
{
    avlNode *root = *rootptr;
    if (!(root->l || root->r))
    {
        avlNode *node = (avlNode *)calloc(1, sizeof(*node));
        node->val = val;
        node->p = root;
        if (val >= root->val)
        {
            root->r = node;
            root->bal--;
        }
        else
        {
            root->l = node;
            root->bal++;
        }

        avl_rebalance(root);
        *rootptr = root;
        return;
    }

    if (val >= root->val)
    {
        if (root->r)
        {
            root->bal--;
            avlNode* right = root->r;
            avl_insert(&right, val);
            if(!(right->r || right->l))
            {
                *rootptr = right->p;
            }
            else if(right != root->r)
            {
                *rootptr = right;
            }
            return;
        }

        avlNode *node = (avlNode *)calloc(1, sizeof(*node));
        node->val = val;
        node->p = root;
        root->r = node;
        root->bal--;
    }
    else
    {
        if (root->l)
        {
            root->bal++;
            avlNode* left = root->l;
            avl_insert(&left, val);
            if(!(left->r || left->r))
            {
                *rootptr = left->p;
            }
            else if(left != root->l)
            {
                *rootptr = left;
            }
            return;
        }

        avlNode *node = (avlNode *)calloc(1, sizeof(*node));
        node->val = val;
        node->p = root;
        root->l = node;
        root->bal++;
    }

    avl_rebalance(root);
    *rootptr = root;
}
//preorder
void avl_print(avlNode *root)
{
    if (root->l)
        avl_print(root->l);
    printf("%d\n", root->val);
    if (root->r)
        avl_print(root->r);
}

avlNode *avl_create()
{
    return (avlNode *)calloc(1, sizeof(avlNode));
}

int main()
{
    avlNode *tree = avl_create();
    tree->val = 2;
    avl_insert(&tree, 1);
    avl_insert(&tree, 0);
    avl_insert(&tree, 2);
    avl_insert(&tree, 3);
    avl_insert(&tree, 4);
    avl_insert(&tree, 3);
    avl_insert(&tree, 3);
    avl_print(tree);

    return 0;
}

//TODO: node 4 still has balance issues
#endif




avlNode* createAVL()
{
    return (avlNode*)calloc(1, sizeof(avlNode));
}
