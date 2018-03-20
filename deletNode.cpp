这里先提供一份只使用一级指针的代码，但是显然是有问题的：
传入一级指针时，只能修改其指向的值，并不能修改自身。
当链表中只有一个节点，要删除该节点，怎么办？
这里传入一级指针后，del函数中维持了一份对main中头指针的拷贝，因此无法完成对自身的删除，即使free对main函数头指针地址也无影响。

#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
struct ListNode
{
	int m_nKey;
	ListNode *m_pNext;
};

//根据头结点打印(不需要修改头结点地址，因此一级指针)
void printNode(ListNode *myhead)
{
	if (myhead == NULL) return;
	while (myhead)
	{
		printf("%d ", myhead->m_nKey);
		myhead = myhead->m_pNext;
	}
	printf("\n");
}
ListNode * findNode(ListNode * myhead, int value)
{
	if (myhead == NULL) return NULL;
	while (myhead != NULL)
	{
		if (myhead->m_nKey == value)
			return myhead;
		myhead = myhead->m_pNext;
	}
	return NULL;
}
void insertNode(ListNode * myhead, int nextValue, int curValue)
{
	if (myhead == NULL) return;
	ListNode *curNode = findNode(myhead, curValue);
	if (curNode != NULL)
	{
		ListNode *myNode = (ListNode *)malloc(sizeof(ListNode));
		assert(myNode != NULL);
		myNode->m_nKey = nextValue;

		myNode->m_pNext = curNode->m_pNext;
		curNode->m_pNext = myNode;
	}
}

//按值删节点，由于findNode返回的是当前节点而不是前驱，故采用覆盖法
void deleteVal(ListNode *myhead, int value)
{
	if (myhead == NULL) return;
	ListNode *curNode = findNode(myhead, value);
	if (curNode != NULL)
	{
		//若删除的节点不是尾结点
		if (curNode->m_pNext != NULL)
		{
			ListNode *pNext = curNode->m_pNext;
			curNode->m_nKey = pNext->m_nKey;
			curNode->m_pNext = pNext->m_pNext;

			free(pNext);
		}
		//是尾结点。若链表只有一个节点，则删除头节点
		else if (curNode == myhead)
		{
			//myhead = myhead->m_pNext;
			//myhead = NULL;
			free(curNode);
			return;
		}
		//是尾结点。若链表有多个节点
		else
		{
			ListNode * pNode = myhead;
			while (pNode->m_pNext != curNode)
			{
				pNode = pNode->m_pNext;
			}
			pNode->m_pNext = NULL;
		}
	}

}
int main()
{
	int num = 0, headVal = 0, delVal = 0;
	int input, indexVal;
	while (cin >> num)     // 不知道为啥还要循环检测，真是坑
	{
		cin >> headVal;
		ListNode* head = new ListNode;
		head->m_nKey = headVal;
		head->m_pNext = NULL;
		for (int i = 0; i < num - 1; i++)
		{
			cin >> input >> indexVal;
			insertNode(head, input, indexVal);

		}
		cin >> delVal;
		deleteVal(head, delVal);
		printNode(head);
	}

	return 0;
}
