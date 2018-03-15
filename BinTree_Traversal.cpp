//代码已测试，只是没有创建二叉树的函数，后面在看懂的基础上加上。

//二叉树的遍历大致可分为先序遍历、中序遍历、后序遍历和层次遍历四种。
//具体的实现原理都比较简单，这里不再描述，现在给出具体的遍历算法。
//本文给出了二叉树遍历的递归算法和非递归算法，这样有助于对照了解。

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <stack>
#include <queue>
#include <cstdio>
using namespace std;

typedef struct BinTreeNode
{  
    int data;  // 默认结点中存储整型数据
    struct BinTreeNode* lchild;  
    struct BinTreeNode* rchild;  
}BinTreeNode;

//前序递归
void PreOrder(BinTreeNode *root)   
{
    if(root!=NULL)
    {
        cout<<root->data<<" ";
        PreOrder(root->lchild);
        PreOrder(root->rchild);
    }
}
// 前序非递归
void PreOrderNoRecur(BinTreeNode *root)  
{
    stack<BinTreeNode*> s;
    BinTreeNode *p = root;
    while(p!=NULL||!s.empty())
    {
        while(p!=NULL)
        {
            cout<<p->data<<" ";
            s.push(p);
            p=p->lchild;
        }
        if(!s.empty())
        {
            p = s.top();
            s.pop();
            p = p->rchild;
        }
    }
}
// 中序递归
void InOrder(BinTreeNode *root)  
{
    if(root!=NULL)
    {
        InOrder(root->lchild);
        cout<<root->data<<" ";
        InOrder(root->rchild);
    }
} 
// 中序非递归
void InOrderNoRecur(BinTreeNode *root)  
{
    stack<BinTreeNode*> s;
    BinTreeNode *p = root;
    while(p!=NULL||!s.empty())
    {
        while(p!=NULL)
        {
            s.push(p);
            p = p->lchild;
        }
        if(!s.empty())
        {
            p = s.top();
            cout<<p->data<<" ";
            s.pop();
            p = p->rchild;
        }
    }    
} 
// 后序递归
void PostOrder(BinTreeNode *root)  
{
    if(root!=NULL)
    {
        PostOrder(root->lchild);
        PostOrder(root->rchild);
        cout<<root->data<<" ";
    }    
}
// 后序非递归
void PostOrderNoRecur(BinTreeNode *root)  
{
    stack<BinTreeNode*> s;
    BinTreeNode *p = root, *r = NULL;
    while(p||!s.empty())
    {
        if(p)  // 走到最左边
        {
            s.push(p);
            p=p->lchild;
        }
        else  // 向右
        {
            p = s.top();
            if(p->rchild&&p->rchild!=r)  // 右子树存在且未被访问
            {
                p = p->rchild;
                s.push(p);
                p = p->lchild;
            }
            else  // 否则，弹出结点并访问
            {
                p = s.top();
                s.pop();
                cout<<p->data<<" ";
                r = p;
                p =NULL;
            }
        }  // else
    }  // while  
} 
// 层次非递归
void LevelOrder(BinTreeNode* root)  
{  
    queue<BinTreeNode*> q;
    BinTreeNode* p = root;    
    q.push(p);  

    while(!q.empty())
    {  
        p = q.front();  
        cout<<p->data<<" ";  
        q.pop();  

        if(p->lchild != NULL)
        {  
            q.push(p->lchild);  
        }  

        if(p->rchild != NULL)
        {  
            q.push(p->rchild);  
        }  
    }  
} 

int main(void)
{
	
	return 0;
}
