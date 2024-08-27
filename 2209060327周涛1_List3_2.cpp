#include"List2.h"

void InitList(CLinkNode*& L) //初始化线性表
{
	L = (CLinkNode*)malloc(sizeof(CLinkNode)); //创建头结点
	L->next = L;
}
void DestroyList(CLinkNode*& L) //销毁线性表
{
	CLinkNode* pre = L, * p = pre->next;
	while (p != L)
	{
		free(pre);
		pre = p;
		//pre、p同步后移一个结点
		p = pre->next;
	}
	free(pre);
	//此时p=L,pre指向尾结点,释放它
}

bool ListInsert(CLinkNode*& L, int i, Student e) //插入第i个元素
{
	int j = 1;
	CLinkNode* p = L, * s;
	if (i <= 0) return false;
	//i错误返回假
	if (p->next == L || i == 1)
		//原单链表为空表或i=1作为特殊情况处理
	{
		s = (CLinkNode*)malloc(sizeof(CLinkNode)); //创建新结点s
		s->data = e;
		s->next = p->next;
		//将结点s插入到结点p之后
		p->next = s;
		return true;
	}
	else
	{
		p = L->next;
		while (j <= i - 2 && p != L)
			//找第i-1个结点p
		{
			j++;
			p = p->next;
		}
		if (p == L)
			//未找到第i-1个结点
			return false;
		else
			//找到第i-1个结点p
		{
			s = (CLinkNode*)malloc(sizeof(CLinkNode)); //创建新结点s
			s->data = e;
			s->next = p->next;
			//将结点s插入到结点p之后
			p->next = s;
			return true;
		}
	}
}
