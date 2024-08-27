#include"List1.h"

void InitList(DLinkNode*& L)	//初始化线性表
{
	L = (DLinkNode*)malloc(sizeof(DLinkNode));  	//创建头结点
	L->prior = L->next = NULL;
}
void DestroyList(DLinkNode*& L)	//销毁线性表
{
	DLinkNode* pre = L, * p = pre->next;
	while (p != NULL)
	{
		free(pre);
		pre = p;					//pre、p同步后移一个结点
		p = pre->next;
	}
	free(p);
}
bool ListInsert(DLinkNode*& L, int i, Course e)	//插入第i个元素
{
	int j = 0;
	DLinkNode* p = L, * s;			//p指向头结点,j设置为0
	if (i <= 0) return false;		//i错误返回假
	while (j < i - 1 && p != NULL)	//查找第i-1个结点p
	{
		j++;
		p = p->next;
	}
	if (p == NULL)				//未找到第i-1个结点
		return false;
	else						//找到第i-1个结点p
	{
		s = (DLinkNode*)malloc(sizeof(DLinkNode));	//创建新结点s
		s->data = e;
		s->next = p->next;		//将结点s插入到结点p之后
		if (p->next != NULL)
			p->next->prior = s;
		s->prior = p;
		p->next = s;
		return true;
	}
}

