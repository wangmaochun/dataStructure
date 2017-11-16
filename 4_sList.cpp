说明：这是基于视频教程写的单链表操作版本，该单链表基于改良的数据结构，含有头指针、尾指针

sList.h
------
#ifndef SLIST_H__
#define SLIST_H__

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

typedef int ElemType;

//结点类型
typedef struct Node
{
    ElemType   data;
    struct Node *next;
}Node,*PNode;

//链表类型
typedef struct List
{
    PNode head;
    PNode tail;
    size_t size;
}List;


void InitList(List *list);

void push_back(List *list,ElemType x); //尾插
void push_front(List *list,ElemType x); //头插

void pop_back(List *list); //尾删
void pop_front(List *list); //头删

void insert_val(List *list, ElemType x); //按值插入
Node* find (List *list, ElemType key);//查找某值
int length(List *list); //长度
void delete_val(List *list,ElemType key); //删除值
void sort(List *list);//升序
void reverse(List *list);//反转
void clear(List *list);//清除
void destroy(List *list);//销毁
void show_list(List *list);
#endif // SLIST_H__


sList.cpp
------
#include "sList.h"


void InitList(List *list)
{
    list->head = list->tail = (Node *)malloc(sizeof(Node));
    assert(list->head != NULL);

    list->head->next = NULL; //头结点下一个为空
    list->size = 0;
}

//1.更新新尾结点(一直对尾结点操作，故不需考虑)
void push_back(List *list,ElemType x)
{

    Node *s = (Node *)malloc(sizeof(Node));
    assert (s != NULL);

    s->data = x;

    s->next = list->tail->next;
    list->tail->next = s; //原尾结点指向s

    list->tail = s;//更新为新尾结点

    //由于一直对尾指针考虑，因此这里不需要考虑size=0

    list->size++;
}

//1.在头结点之后插入作为第一个结点(需要考虑尾结点)
void push_front(List *list,ElemType x)
{
    Node *s = (Node *)malloc(sizeof(Node));
    assert (s != NULL);

    s->data = x;
    s->next = list->head->next; //s结点指向第一个结点

    list->head->next = s; //头结点指向第一个结点

    //插入时，如果是第一个结点(size=0)则需修改list->tail指针指向s
    if(list->size == 0)
    {
        list->tail = s;
    }
    list->size++;
}
//1.判断非空 2.使倒数第二个结点为新尾结点(一直对尾结点操作，故不需考虑)
void pop_back(List *list)
{
    if(list->size == 0)
    {
        printf("error: seqList is empty\n");
        return;
    }

    Node *p = list->head;


    while (p->next != list->tail) { p = p->next; }

    free(list->tail);//删除旧尾结点

    list->tail = p;//新尾结点
    list->tail->next = NULL;//新尾结点next为NULL


    list->size--;
}

//1.判断非空 2.删除头结点之后第一个结点 3.需要考虑尾结点
void pop_front(List *list)
{
    if(list->size == 0)
    {
        printf("error: seqList is empty\n");
        return;
    }

    Node *q = list->head->next;
    list->head->next = q->next;
    free(q);
    //删除时，如果只剩第一个结点(size=1)则需修改list->tail指针指向头结点
    if(list->size == 1)
    {
        list->tail = list->head;
    }
    list->size--;
}
//前提：有序。按值插入(考虑插入到尾结点之后情况)
void insert_val(List *list, ElemType x)
{
   Node *s = (Node *)malloc(sizeof(Node));
   assert(s != NULL);

   s->data = x;
   s->next = NULL;

   Node *p = list->head;
   while(p->next != NULL && p->next->data <x)
        p=p->next;

   //若插入到尾结点,则更新尾结点
   if(p->next == NULL)
   {
        list->tail = s;
   }
   //找到该插入位置的前一位
   s->next = p->next;
   p->next = s; //指向新创建的结点

   list->size++;

}

Node* find (List *list, ElemType key)
{
    Node *p = list->head->next;
    //利用短路条件，注意顺序
    while( p!=NULL && p->data != key)  { p = p->next; }

    return p;
}

int length(List *list)
{
    return list->size;
}

void delete_val(List *list,ElemType key)
{
    if(list->size == 0)
        return;
    Node *p = find(list,key);
    if(p == NULL)
    {
        printf("delete val not exist\n");
        return ;
    }
    if(p == list->tail)
    {
        pop_back(list);
    }else
    {
        //将要删除数据的next拿过来替换值,取出next的有用信息后free掉q
        Node *q = p->next;
        p->data = q->data;
        p->next = q->next;
        free(q);

        list->size--;
    }

}

//把整个单链表断开，把剩下链表的结点根据值升序尾插
void sort(List *list)
{
    if(list->size==0 || list->size == 1)
        return ;
    Node *s = list->head->next; //指向第一个结点
    Node *q = s->next;//指向第二个结点

    list->tail = s;
    list->tail->next = NULL; //断开链表
    //按值插入
    while(q!=NULL)
    {
        s = q;
        q = q->next;

       //p指针为已排序指针,s为待排序指针
       Node *p = list->head;
       while(p->next != NULL && p->next->data < s->data)
            p=p->next;

       //若插入到尾结点,则更新尾结点
       if(p->next == NULL)
       {
            list->tail = s;
       }


       //尾插
       s->next = p->next;
       p->next = s; //指向新创建的结点


    }
}
//把整个单链表断开，把剩下链表的结点按值头插
void reverse(List *list)
{
    if(list->size==0 || list->size == 1)
        return ;
    Node *p = list->head; //指向第一个结点
    Node *q = p->next;//指向第二个结点

    list->tail = p;//指向第一个结点
    list->tail->next = NULL; //断开链表


    while(q != NULL)
    {
        p = q;
        q = q->next;

        p->next = list->head->next ;
        list->head->next  = p; //在头结点和第一个结点直接插入



    }
}

void clear(List *list)
{
    if(list->size ==0)
        return ;
    Node *p = list->head->next;
    while(p!=NULL)
    {
        list->head->next = p->next;
        free(p);
        p = list->head->next;
    }
    list->tail = list->head;

    list->size = 0;
}

void destroy(List *list)
{
    clear(list);
    free(list->head);
    list->tail = list->head =NULL;
}
void show_list(List *list)
{
    Node *p = list->head->next;
    while(p)
    {
        printf("%d--->",p->data);
        p = p->next;
    }
    printf("Nul\n");
}

main.cpp
------
#include "sList.h"

/*
break语句通常用在循环语句和开关语句中。
当break用于开关语句switch中时，可使程序跳出switch而执行switch以后的语句；
如果没有break语句，则会从满足条件的地方（即与switch（表达式）括号中表达式匹配的case）开始执行，直到switch结构结束。

当break语句用于do-while、for、while循环语句中时，可使程序终止循环。
而执行循环后面的语句，通常break语句总是与if语句联在一起。即满足条件时便跳出循环。
*/

int main()
{
    List mylist;
    InitList(&mylist);

    int select;
    ElemType num;
    Node *p;
    while(select)
    {
        printf("* [1] push_back                [2] push_front  *\n");
        printf("* [3] show_list                [4] pop_back     *\n");
        printf("* [5] pop_front                [6] insert_val   *\n");
        printf("* [7] find                     [8] length       *\n");
        printf("* [9] delete_val               [10] sort        *\n");
        printf("* [11] reverse                 [12] clear       *\n");
        printf("* [13] destroy                 [0] quit_system  *\n");
        printf("please choose:>");
        scanf("%d",&select);
        if(select == 0)  break;
        switch(select)
        {
            case 1:
                printf("push_back: input numbers(-1 erminate):");
                while(scanf("%d",&num),num != -1)
                {
                    push_back(&mylist,num);  //尾插
                }
                break;
            case 2:
                printf("push_front: input numbers(-1 erminate):");
                while(scanf("%d",&num),num != -1)
                {
                    push_front(&mylist,num);  //头插
                }
                break;
            case 3:
                show_list(&mylist);
                break;
            case 4:
                pop_back(&mylist); //尾删
                break;
            case 5:
                pop_front(&mylist); //头删
                break;
            case 6:
                printf("input inset value:>");
                scanf("%d",&num);
                insert_val(&mylist,num); //升序插值
                break;
            case 7:
                printf("input find value:>");
                scanf("%d",&num);
                p = find(&mylist,num); //查找某值
                if(p == NULL)
                    printf("value %d not exist\n",num);
                break;
            case 8:
                printf("length:%d\n",length(&mylist));  //长度
            case 9:
                printf("input delete value:>");
                scanf("%d",&num);
                delete_val(&mylist,num); //删除值
                break;
            case 10:
                sort(&mylist); //升序
                break;
            case 11:
                reverse(&mylist); //反转
                break;
            case 12:
                clear(&mylist); //清除
                break;
            case 13:
                destroy(&mylist); //销毁
                break;
            default:
                printf("error,choose again\n");
                break;
        }

    }

    printf("Hello world!");
    return 0;
}
