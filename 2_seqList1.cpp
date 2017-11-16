说明：这是线性表顺序表的第二个版本：存储空间初始分配+分配增量。


SeqList.h
---------

#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#include <stdio.h>
#include <malloc.h>
#include <assert.h>


#define SEQLIST_INIT_SIZE 8
#define INC_SIZE          3

typedef int ElemType;


typedef struct SeqList
{
    ElemType * base;     //存储空间基址
    int        capacity; //当前分配的存储容量(以sizeof(ElemType)为单位)
    int        size;     // 实际长度
}SeqList;


//function declaration
void InitSeqList(SeqList *list); //initiation
bool IncSeqList(SeqList *list);  //increase

void push_back(SeqList *List,ElemType item); //tail insert
void show_list(SeqList *List); //show
void push_front(SeqList *List,ElemType item); //head insert
void pop_back(SeqList *List); //pop tail
void pop_front(SeqList *List); //pop head

void insert_pos(SeqList *List,int pos,ElemType item); //insert value at pos
int  find_val(SeqList *List,ElemType item); //find the pos of value
int  length(SeqList * List); //the length of SeqList
void delete_pos(SeqList *List,int pos); //delete value at pos
void delete_val(SeqList *List,ElemType item); //delete value

void sort(SeqList *List); //Ascend sort
void reverse(SeqList *List); //reverse
void clear(SeqList *List); //clear
void destroy(SeqList *List); //destroy

void mergeList(SeqList *La,SeqList *Lb,SeqList *Lc);
#endif // __SEQLIST_H__

SeqList.cpp
---------
#include "SeqList.h"

void InitSeqList(SeqList *list)
{
    list->base = (ElemType*)malloc(sizeof(ElemType)*SEQLIST_INIT_SIZE);
    assert(list->base != NULL);

    list->capacity = SEQLIST_INIT_SIZE;
    list->size =0;
}

//success: true
bool IncSeqList(SeqList *list)
{
    ElemType *newbase = (ElemType*)realloc(list->base,sizeof(ElemType)*(SEQLIST_INIT_SIZE+INC_SIZE));
    if(newbase == NULL)
    {
        printf("Insufficient memory space allocation\n");
        return false;
    }

    list->base = newbase;
    list->capacity = SEQLIST_INIT_SIZE + INC_SIZE;

    return true;
}

//insert
void push_back(SeqList *List,ElemType item)
{

    //原分配空间已满，且增配空间失败
    if(List->size >= List->capacity && !IncSeqList(List))
    {
        printf("SeqList has full,value %d can't insert tail\n",item);
        return ;
    }
    List->base[List->size] = item;

    List->size++;

}
void push_front(SeqList *List,ElemType item)
{
    //原分配空间已满，且增配空间失败
    if(List->size >= List->capacity && !IncSeqList(List))
    {
        printf("SeqList has full,value %d can't insert head\n",item);
        return ;
    }

    //从0开始全部右移1位(如果没有元素,不进入循环)
    for(int i=List->size;i >0; i--)
    {
        List->base[i] = List->base[i-1];
    }

    //坐标为0，插入新元素
    List->base[0] = item;

    //添加了新元素，当前计数+1
    List->size++;
    //printf("hello world \n");
}

void pop_back(SeqList *List)
{
    //如果没有元素
    if(List->size == 0)
    {
        printf("no element,can not delete\n");
        return ;
    }
    printf("delete tail value:%d\n",List->base[List->size-1]);

    //删除(最后)一个元素，当前计数自减
    List->size--;
}
void pop_front(SeqList *List)
{
    //如果没有元素
    if(List->size == 0)
    {
        printf("no element,can not delete\n");
        return ;
    }
    printf("delete head value:%d\n",List->base[0]);

    //从下标1开始全部左移
    for(int i=0;i<List->size-1;i++)
    {
        List->base[i] = List->base[i+1] ;
    }
    //删除(第)一个元素，当前计数自减
    List->size--;
}

void insert_pos(SeqList *List,int pos,ElemType item)
{
    //判断位置是否合法(为0,即头插; 为size即尾插)
    if(pos<0 || pos>List->size)
    {
        printf("insert pos illegal,can't insert\n");
        return ;
    }

    //原分配空间已满，且增配空间失败
    if(List->size >= List->capacity && !IncSeqList(List) )
    {
        printf("SeqList has full,value %d can't insert at pos \n",item);
        return ;
    }

    //size为即将插入位置,全部左移，留出pos
    for(int i=List->size; i>pos; i--)
    {
        List->base[i] = List->base[i-1];
    }

    List->base[pos] = item;

    List->size++;
}

int find_val(SeqList *List,ElemType item)
{
   //找到第一个匹配值的坐标
   for(int i=0;i<List->size;i++)
   {
       if(item == List->base[i])
       {
           return i;
       }
   }

   return -1;
}

int  length(SeqList * List)
{
    return List->size;
}

void  delete_pos(SeqList *List,int pos)
{
    if(pos <0 || pos >= List->size)
    {
        printf("delete pos illegal,can't delete\n");
        return ;
    }

    //从pos+1处全部左移
    for(int i=pos; i<List->size-1;i++)
    {
        List->base[i] = List->base[i+1];
    }

    List->size--;
}

void delete_val(SeqList *List,ElemType item)
{
    int pos;
    pos = find_val(List,item);

    if(pos < 0 )
    {
        printf("value %d not found!\n",item);
        return ;
    }
    delete_pos(List,pos);
}
/*选择排序:每次在无序队列中"选择"出最小值，放到有序队列的最前*/
void sort(SeqList *List)
{
    if(List->size == 0 || List->size ==1)
        return;

    int temp;
    int min;
    for(int i=0; i<List->size; i++)
    {
        min = i;
        for(int j= i+1;j<List->size;j++)
        {
            if (List->base[j] < List->base[min])
                min=j;
        }

        //交换最小数
        if(min != i)
        {
            temp =  List->base[min];
            List->base[min] =  List->base[i];
            List->base[i] = temp;
        }

    }

}

void reverse(SeqList *List)
{
    int temp;
    for(int i=0; i<List->size/2; i++)
    {
        temp =  List->base[i];
        List->base[i] =  List->base[List->size-1-i];
        List->base[List->size-1-i] = temp;
    }

}

void clear(SeqList *List)
{
    List->size = 0;
}

void destroy(SeqList *List)
{
    free(List->base);
    List->base = NULL;
    List ->capacity = 0;
    List ->size = 0;

    return ;
}
void show_list(SeqList *List)
{
    for(int i=0;i<List->size;i++)
    {
        printf("%d  ",List->base[i]);
    }

    printf("\n");
}


void mergeList(SeqList *La,SeqList *Lb,SeqList *Lc)
{
    Lc->capacity = La->size + Lb->size;
    Lc->base = (ElemType *)malloc(Lc->capacity*sizeof(ElemType));
    assert(Lc->base != NULL);

    int ia=0;
    int ib=0;
    int ic=0;

    while(ia <La->size && ib< Lb->size)
    {
        if(La->base[ia] <= Lb->base[ib]) Lc->base[ic++] = La->base[ia++];
        else Lc->base[ic++] = Lb->base[ib++];
    }

    while(ia <La->size) Lc->base[ic++] = La->base[ia++];   //插入La的剩余元素
    while(ib <Lb->size) Lc->base[ic++] = Lb->base[ib++];   //插入Lb的剩余元素

    Lc->size = ic;
}

main.cpp
---------
#include "SeqList.h"

int main()
{
    ElemType item;
    SeqList myList;
    InitSeqList(&myList);

    int select = 1;
    int pos=0;
    //int res =0;
    while (select)
    {
        printf("*******************************************\n");
        printf("* [1] push_back             [2] push_front \n");
        printf("* [3] show_list             [4] pop_back   \n");
        printf("* [5] pop_front             [6] insert_pos \n");
        printf("* [7] find_value            [8] length     \n");
        printf("* [9] delete_pos            [10] delete_val\n");
        printf("* [11] sort                 [12] reverse \n"  );
        printf("* [13] clear                [14*] destroy \n" );
        printf("* [0] quit_system                          \n");
        printf("*******************************************\n");
        printf("do some choice:");
        scanf("%d",&select);
        if(select == 0)
            break;
        switch(select)
        {

            case 1:
                printf("tail insert:");
                while(scanf("%d",&item),item != -1)
                {
                    push_back(&myList,item);//尾插
                }
                break;
            case 2:
                printf("head insert:");
                while(scanf("%d",&item),item != -1)
                {
                    push_front(&myList,item);//头插
                }
                break;
            case 3:
                show_list(&myList); //显示
                break;
            case 4:
                pop_back(&myList); //删除最后一个元素(如果有)
                break;
            case 5:
                pop_front(&myList); //删除第一个元素(如果有)
                break;
            case 6:
                 printf("input insert pos>");
                 scanf("%d",&pos);
                 printf("input value>");
                 scanf("%d",&item);
                 //printf("%d %d",pos,item);
                 insert_pos(&myList,pos,item);//在特定下标处插值
                break;
            case 7:
                printf("input find value>");
                scanf("%d",&item);
                pos=find_val(&myList,item);//查找值的下标
                if(pos <0)
                    printf("can not find %d\n",item);
                else
                    printf("find %d at pos %d\n",item,pos);
                break;
            case 8:
                printf("the length of SeqList is %d\n",length(&myList)); //当前长度
                break;
            case 9:
                printf("input delete pos>");
                scanf("%d",&pos);
                delete_pos(&myList,pos); //删除特定下标处值
                break;
            case 10:
                printf("input delete value>");
                scanf("%d",&item);
                delete_val(&myList,item); //删除特定值(找不到值时不会报错)
                break;
            case 11:
                sort(&myList); //升序(选择排序法)
                printf("has ascended sort\n");
                break;
            case 12:
                reverse(&myList);//反转
                printf("has reversed \n");
                break;
            case 13:
                clear(&myList); //清除
                printf("has cleared\n");
                break;
            case 14:
                destroy(&myList);//销毁
                printf("has destroyed\n");
                break;
            default:
                printf("not exist,input again!\n");
                break;

        }

    }

    destroy(&myList);//销毁(程序退出前)

    return 0;
}

