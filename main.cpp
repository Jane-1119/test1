#include <iostream>
#include <bits/stdc++.h>
#define MAXSIZE 1000
using namespace std;

typedef char  Elemtype;
typedef struct BiTNode
{
    Elemtype data;
    BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

void CreateBiTree(BiTree &T)
{
    Elemtype ch;
    cin >> ch;
    if(ch == '@')
    {
        T = NULL;
        return ;
    }
    else
    {
        T = new BiTNode;
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

//先序
void PreOrderTraverse(BiTree T)
{
    if(T == NULL)
    {
        return ;
    }
    else
    {
        cout << T->data;
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

//中序
void InOrderTraverse(BiTree T)
{
    if(T == NULL)
    {
        return ;
    }
    else
    {
        InOrderTraverse(T->lchild);
        cout <<T->data;
        InOrderTraverse(T->rchild);
    }
}

void PostOrderTraverse(BiTree T)
{
    if(T == NULL)
    {
        return ;
    }
    else
    {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        cout << T->data;
    }
}

//高度
int Depth(BiTree T)
{
    int m,n;
    if(T == NULL)
    {
        return 0;
    }
    else
    {
        m = Depth(T->lchild);
        n = Depth(T->rchild) ;
        if(m > n)
        {
            return m+1;
        }
        else
        {
            return n+1;
        }
    }
}

//树叶
int leaf_num = 0;
void Leaf(BiTree T)
{
    if(T == NULL)
    {
        return ;
    }
    if(T != NULL && T->lchild == NULL && T->rchild == NULL)
    {
        leaf_num++;
    }
    else
    {
        Leaf(T->lchild);
        Leaf(T->rchild);
    }
}

//非递归
typedef struct StackNode
{
    BiTree data;
    StackNode *next;
}StackNode,*SNode;

void Init(SNode &S)
{
    S = NULL;
}

void Push(SNode &S,BiTree p)
{
    SNode r = new StackNode;
    r->data = p;
    r->next = S;
    S = r;
}

void Pop(SNode &S,BiTree &p)
{
    p = S->data;
    SNode r = S;
    S = S->next;
    delete r;
}

//中序
void InOrderStackTraverse(BiTree T)
{
    if(T == NULL)
    {
        return ;
    }
    else
    {
        BiTree p = T;
        SNode S;
        Init(S);
        while(p || S)
        {
            if(p != NULL)
            {
                Push(S,p);
                p = p->lchild;
            }
            else
            {
                Pop(S,p);
                cout << p->data;
                p = p->rchild;
            }
        }
    }
}

//层次遍历
typedef struct SqQueue
{
    BiTree data[MAXSIZE];
    int front,rear;
}SqQueue;

void LevelTraverse(BiTree T)
{
    if(T == NULL)
    {
        return ;
    }
    else
    {
        BiTree p = T;
        SqQueue S;
        S.front = S.rear = 0;
        S.data[S.rear] = p;
        S.rear = (S.rear + 1)%MAXSIZE;
        while(S.rear != S.front)
        {
            p = S.data[S.front];
            cout << p->data;
            S.front = (S.front + 1)%MAXSIZE;
            if(p->lchild)
            {
                S.data[S.rear] = p->lchild;
                S.rear = (S.rear + 1)%MAXSIZE;
            }
             if(p->rchild)
            {
                S.data[S.rear] = p->rchild;
                S.rear = (S.rear + 1)%MAXSIZE;
            }
        }
    }
}

//求祖先
BiTree FindParent(BiTree T,char ch)
{
    if(T == NULL)
    {
        return NULL;
    }
    if(T->lchild && T->lchild->data == ch || T->rchild && T->rchild->data == ch)
    {
        return T;
    }
    else
    {
        BiTree left = FindParent(T->lchild,ch);
        if(left)
        {
            return left;
        }
        else
            return FindParent(T->rchild,ch);
    }
}

void FindAncestor(BiTree T)
{
    char ch;
    cin >> ch;
    if(T == NULL)
    {
        cout << "树为空" << endl;
        return ;
    }
    if(T->data == ch)
    {
        cout << "根节点为所求节点" << endl;
        return ;
    }
    else
    {
        BiTree parent = FindParent(T,ch);
        if(parent == NULL)
        {
            cout << "该节点不存在"  << endl;
            return ;
        }
        while(parent)
        {
            cout << parent->data;
            parent = FindParent(T,parent->data);
        }
    }

}

int cnt = 0;
void ForestLeaf(BiTree T)
{
    if(T == NULL)
    {
        return ;
    }
    if(T->lchild == NULL)
        cnt++;
    else
    {
        ForestLeaf(T->lchild);
    }
    ForestLeaf(T->rchild);
}

int main()
{
    BiTree T;
    CreateBiTree(T);
    ForestLeaf(T);
    cout << cnt;
    /*
    cout << endl;
    PreOrderTraverse(T);
    cout << endl;
    InOrderTraverse(T);
    cout << endl;
    PostOrderTraverse(T);
    cout << endl;
    cout << "高度：" << Depth(T);
    Leaf(T);
    cout << "树叶：" << leaf_num;
    cout << endl;
    cout << "非递归中序：" ;
    InOrderStackTraverse(T);
    cout << endl << "层次遍历：" ;
    LevelTraverse(T);
    */
    return 0;
}
