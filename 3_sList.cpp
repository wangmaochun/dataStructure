说明：这是单向链表的一个测试版本，基于头结点，结合网上各种单向链表操作编写的

main.cpp
------
#include <stdio.h>
#include <assert.h>
#include <malloc.h>

#define ElemType int

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode;

typedef LNode* LinkList;

//创建一个头结点
void InitList(LinkList *head)
{
    *head = (LNode *)malloc(sizeof(LNode));
    assert(*head != NULL);

    (*head)->next = NULL;
}

//头插法建立单链表
void createListH(LinkList *head)
{
    for(int i=1;i<=10;i++)
    {
        LNode *s = (LNode *)malloc(sizeof(LNode));  //s为新创建结点
        assert(s!=NULL);

        s->data = i;
        s->next = (*head)->next;

        (*head)->next = s;
    }

}

//尾插法建立单链表
void createListrR(LinkList *head)
{
    LNode *p = *head;

    for(int i=1;i<=10;i++)
    {
        LNode *s = (LNode *)malloc(sizeof(LNode));  //s为新创建结点
        assert(s!=NULL);

        s->data = i;
        s->next = p->next;
        p->next = s;

        p = s; //指向最后一个结点地址
    }


}

//单链表中数据节点的个数
int listLength(LinkList *head)
{
    LNode *p = *head;

    int count=0;

    while(p->next != NULL)
    {
        p = p->next;
        count ++;
    }

    return count;
}

//链表是否为空
bool is_empty(LinkList *head)
{
    return ((*head)->next == NULL);
}
//升序排序
void sort(LinkList *head)
{
    LNode *p,*q;
    ElemType temp;

    for (p =(*head)->next; p != NULL; p = p->next)
    {
         for (q = p->next; q != NULL; q = q->next)
        {
           if (p->data > q->data)
            {
                temp = q->data;
                q->data = p->data;
                p->data = temp;
            }
        }
    }
}

//特定下标处插入值
bool insert(LinkList *head, int pos, ElemType val)
{
    int n = 0;
    LNode *p = *head;
    while (n < pos && p != NULL)
    {
        n++;
        p = p->next;
    }
    if (n != pos || NULL == p)
    {
        return false;
    }

    LNode *pNew = (LNode *)malloc(sizeof(LNode));
    if (NULL == pNew)
    {
        printf("Error in dynamic allocating memory!");
    }
    pNew->data = val;
    pNew->next = p->next;
    p->next = pNew;
    return true;
}

// 删除某个节点
bool listDelete(LinkList *head, int pos)
{
    int n = 0;
    LNode *p = *head;


    while (n < pos && p != NULL)
    {
        n++;
        p = p->next;
    }
    if (n != pos || NULL == p)
    {
        return false;
    }
    //判断位置合法
    if(p->next == NULL)
    {
        return false;
    }
    LNode *q = p->next;
    p->next = p->next->next;
    free(q);

    return true;
}

LNode* find(LinkList *head, ElemType key)
{
    LNode *p = *head;
    //为NULL或找到p
    while (p != NULL && p->data != key) { p= p->next; }

    return p;
}

//1.判断非空 2.删除头结点之后第一个结点
void pop_front(LinkList *head)
{
    if((*head)->next == NULL)
    {
        printf("error: seqList is empty\n");
        return;
    }

    LNode *q = (*head)->next;

    (*head)->next = q->next;
    free(q);
}
//1.判断非空 2.删除倒数第一个结点
void pop_back(LinkList *head)
{
    if((*head)->next == NULL)
    {
        printf("error: seqList is empty\n");
        return;
    }


    LNode *p = *head;
    LNode *prev = NULL;//存p结点之前的结点
    while (p->next != NULL)
    {
        prev = p;
        p = p->next;
    }
    //prev为倒数第二个结点
    //p为倒数第一个结点
    prev->next = p->next;
    free(p);

}



//仅显示，不修改
void showList(LinkList head)
{


    LNode *p = head->next;

    while(p != NULL)
    {
        printf("%d---->",p->data);
        p = p->next;
    }
    printf("Nul\n");

}
int main()
{
    LinkList mylist;
    InitList(&mylist);
    printf("create node in the head:\n");
    createListH(&mylist);
    //尾插
    //createListrR(&mylist);
    //打印显示
    showList(mylist);

    //插入值
    insert(&mylist,2,88);
    printf("insert 88 at pos 2:\n");
    //打印显示
    showList(mylist);

    //查找
    if(!find(&mylist,3))
    printf("value 3 not found\n");
    //长度
    printf("length:%d\n", listLength(&mylist));

    //头删
    pop_front(&mylist);
    //打印显示
    printf("delete head element:\n");
    showList(mylist);

    //尾删
    pop_back(&mylist);
    //打印显示
    printf("delete tail element:\n");
    showList(mylist);

    //删除下标为2
    if(listDelete(&mylist,2)) printf("delete success\n");
    else printf("delete failed\n");
    //打印显示
    printf("delete value at pos 10:\n");
    showList(mylist);

    //升序排序
    sort(&mylist);
    printf("sort ascend:\n");
    //打印显示
    showList(mylist);

    //判断是否为空
    if(is_empty(&mylist)) printf("linklist is empty\n");
    else  printf("linklist is not empty\n");

    return 0;
}
