#include"List1.h"

void InitList(DLinkNode*& L)	//��ʼ�����Ա�
{
	L = (DLinkNode*)malloc(sizeof(DLinkNode));  	//����ͷ���
	L->prior = L->next = NULL;
}
void DestroyList(DLinkNode*& L)	//�������Ա�
{
	DLinkNode* pre = L, * p = pre->next;
	while (p != NULL)
	{
		free(pre);
		pre = p;					//pre��pͬ������һ�����
		p = pre->next;
	}
	free(p);
}
bool ListInsert(DLinkNode*& L, int i, Course e)	//�����i��Ԫ��
{
	int j = 0;
	DLinkNode* p = L, * s;			//pָ��ͷ���,j����Ϊ0
	if (i <= 0) return false;		//i���󷵻ؼ�
	while (j < i - 1 && p != NULL)	//���ҵ�i-1�����p
	{
		j++;
		p = p->next;
	}
	if (p == NULL)				//δ�ҵ���i-1�����
		return false;
	else						//�ҵ���i-1�����p
	{
		s = (DLinkNode*)malloc(sizeof(DLinkNode));	//�����½��s
		s->data = e;
		s->next = p->next;		//�����s���뵽���p֮��
		if (p->next != NULL)
			p->next->prior = s;
		s->prior = p;
		p->next = s;
		return true;
	}
}

