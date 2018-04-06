#include "stdafx.h"
#include <iostream>
using namespace std;

typedef int elemType;
typedef struct Lnode {
	elemType data1;    //data1为系数
	elemType data2;    //data2为指数
	Lnode *next;
}Lnode, *LinkList;

LinkList _L1, _L2, _L;   //分别为L1、L2、L的一个副本
LinkList a, b;  //a为第一个比L中最大元素大的那个节点位置,b为a前面一个节点

//创建链式表
void Create_list(LinkList &L, int n)
{
	L = (LinkList)malloc(sizeof(Lnode));
	L->next = NULL;
	for (int i = 0; i < n; i++)
	{
		LinkList p;
		p = (LinkList)malloc(sizeof(Lnode));
		cin >> p->data1 >> p->data2;
		p->next = L->next;
		L->next = p;
	}
}

//讨论若L2中还有元素，则它们与L中元素的关系。其中，有小有大返回0，都大于L返回1，都小于返回-1
int discuss(LinkList L, LinkList L2)
{
	L = _L, L2 = _L2;
	if (L2->next->data2 < L->next->data2)
	{
		int i;
		for (int j = 0;; j++)
		{
			L2 = L2->next;
			if (L2->data2 > L->data2)
			{
				i = j;
				a = L2;
				L2 = _L2;
				for (int k = 0; k < i; k++)
				{
					L2 = L2->next;
					if (k == 4)
					{
						b = L2;
					}
				}
				return 0;
			}
			else if (!L2)
			{
				return -1;
			}
		}
	}
	else
		return 1;
}

//将两个有序链表连接为一个有序链表
void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc)
{
	LinkList pa = La->next, pb = Lb->next;  //pa为La的头结点，pb为Lb的头结点
	LinkList pc;
	Lc = pc = La;
	while (pa&&pb)
	{
		if (pa->data2 < pb->data2)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
		pc->next = pa ? pa : pb;
	}
}

//将L2中剩下的元素加到L中
void lianjie(LinkList &L2, LinkList &_L, LinkList &L, LinkList &LL, int len1, int len2)
{
	L2 = _L2;
	_L = L;
	LinkList mL;  //mL为暂时储存L2剩下的元素的链表
	mL = (LinkList)malloc(sizeof(Lnode));
	mL->next = NULL;
	LinkList p;
	int j;
	for (int i = 0; i < len2; i++)
	{
		for (j = 0; j < len1; j++)
		{
			if (L2->next->data2 == _L->next->data2)
			{
				break;
			}
			_L = _L->next;
		}
		if (j == len1)
		{
			p = (LinkList)malloc(sizeof(Lnode));
			p->data1 = L2->next->data1;
			p->data2 = L2->next->data2;
			p->next = mL->next;
			mL->next = p;
		}
		_L = L;
		L2 = L2->next;
	}
	MergeList_L(mL, L, LL);
}

//比较两个表的长度
bool Maxlen_list(LinkList &L1, LinkList &L2, int &len1, int &len2)
{
	for (;; len1++)
	{
		if (L1->next)
		{
			L1 = L1->next;
		}
		else
			break;
	}
	for (;; len2++)
	{
		if (L2->next)
		{
			L2 = L2->next;
		}
		else
			break;
	}
	if (len1 >= len2)
		return true;
	else
		return false;
}

//将两个表连接成一个表的总函数
void New_list(LinkList &L1, LinkList &L2, LinkList &L, LinkList &_L, LinkList &LL, int len1, int len2)
{
	LinkList mL;  //此处mL为往L链表插入元素的中间量
	if (Maxlen_list(L1, L2, len1, len2))
	{
		L1 = _L1, L2 = _L2;
		int j;
		L1 = L1->next;
		for (int i = 0; i < len1; i++)  //经历这个嵌套循环后所有L1、L2共有的以及仅L1有的元素都将被添加到L中
		{
			LinkList p;
			p = (LinkList)malloc(sizeof(Lnode));
			p->data1 = L1->data1, p->data2 = L1->data2;
			for (j = 0; j < len2; j++)
			{
				if (L2->next->data2 == p->data2)
				{
					mL = (LinkList)malloc(sizeof(Lnode));
					mL->data1 = p->data1 + L2->next->data1;
					mL->data2 = p->data2;
					mL->next = L->next;
					L->next = mL;
					break;
				}
				L2 = L2->next;
			}
			for (;;)
			{
				if (j<len2)
				{
					break;
				}
				if (j == len2 || i >= len2)
				{
					//if (L1->next == NULL)
					//	break;
					mL = (LinkList)malloc(sizeof(Lnode));
					mL->data1 = p->data1;
					mL->data2 = p->data2;
					mL->next = L->next;
					L->next = mL;
					free(p);
					break;
				}
			}
			L1 = L1->next;
			L2 = _L2;
		}
	}
	else
	{
		LinkList L0;
		L0 = (LinkList)malloc(sizeof(Lnode));
		L0 = L1;
		L1 = L2;
		L2 = L0;
		int j;
		for (int i = 0; i < len1; i++)  //经历这个嵌套循环后所有L1、L2共有的以及仅L1有的元素都将被添加到L中
		{
			LinkList p;
			p = (LinkList)malloc(sizeof(Lnode));
			p->data1 = L1->data1, p->data2 = L1->data2;
			for (j = 0; j < len2; j++)
			{
				if (L2->next->data2 == p->data2)
				{
					mL = (LinkList)malloc(sizeof(Lnode));
					mL->data1 = p->data1 + L2->next->data1;
					mL->data2 = p->data2;
					mL->next = L->next;
					L->next = mL;
					break;
				}
				L2 = L2->next;
			}
			for (;;)
			{
				if (j<len2)
				{
					break;
				}
				if (j == len2 || i >= len2)
				{
					//if (L1->next == NULL)
					//	break;
					mL = (LinkList)malloc(sizeof(Lnode));
					mL->data1 = p->data1;
					mL->data2 = p->data2;
					mL->next = L->next;
					L->next = mL;
					free(p);
					break;
				}
			}
			L1 = L1->next;
			L2 = _L2;
		}
	}
	_L = L;                              //保留L的头指针
	lianjie(L2, _L, L, LL, len1, len2);
}

int main()
{
	int len1 = 0, len2 = 0;
	LinkList L1, L2, L, LL;
	L = (LinkList)malloc(sizeof(Lnode));
	L->next = NULL;
	LL = (LinkList)malloc(sizeof(Lnode));
	LL->next = NULL;
	_L1 = (LinkList)malloc(sizeof(Lnode));
	_L2 = (LinkList)malloc(sizeof(Lnode));
	_L = (LinkList)malloc(sizeof(Lnode));
	a = (LinkList)malloc(sizeof(Lnode));
	b = (LinkList)malloc(sizeof(Lnode));
	Create_list(L1, 4);
	Create_list(L2, 3);
	_L1 = L1, _L2 = L2;
	New_list(L1, L2, L, _L, LL, len1, len2);

	cout << "\n";
	for (;;)
	{
		if (LL->next)
		{
			cout << LL->next->data1 << " " << LL->next->data2 << "\n";
		}
		LL = LL->next;
		if (!LL)
		{
			break;
		}
	}
	system("pause");
	return 0;
}