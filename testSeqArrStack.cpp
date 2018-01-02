/*
* 顺序栈的实现（利用数组实现）
* 在数据结构中，栈是一中特殊的ADT（抽象数据类型）。它的特殊性在于它的操作只能在一个位置进行，无论是入栈还是出栈。这个位置是表的末端，也叫做栈顶。
  栈是操作受限的线性表。栈在计算机科学中几乎无处不在，是一中非常重要的数据结构。
* 用数组实现栈代码简单，但是也有缺点，那就是必须提前声明一个数组的大小，并且在程序的运行过程中不能改变，
  这在一定程度上限制了栈的灵活性，但是却带来了更为简洁的代码。数组的下标为0我们表示栈空。
*/

#include <stdio.h> 
#include <string.h>

#define ElemType   char
#define STACK_SIZE 100

//栈的节点声明
typedef struct Stack{
    int top;
    ElemType array[STACK_SIZE];
    }Stack;

Stack S;//定义一个栈

//初始化一个空栈
int Init_Stack(){
    S.top = 0;//top为0表示空栈
    return 1;
    }

//测试是否为空栈
int IsEmpty(){
    if(S.top==0)return 1;
    else return 0;
}

//元素e入栈
int Push(int e){
    S.top++;
    S.array[S.top] = e;
    return S.top;
}

//出栈,并返回该元素值
int Pop(){
    S.top--;
    return S.array[S.top+1];
}

int main(){
    int i,j;
    char str[]="ABC";
    Init_Stack();
    //顺序入栈 
    for(i=0;i<strlen(str);i++){
        Push(str[i]);
    }
    //出栈 
    for(j=0;j<strlen(str);j++){
		printf("%c",Pop());

	}

  
    return 0;
    }
