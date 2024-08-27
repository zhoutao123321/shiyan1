#include"List2.h"

void InitList(CLinkNode*& L) //��ʼ�����Ա�
{
	L = (CLinkNode*)malloc(sizeof(CLinkNode)); //����ͷ���
	L->next = L;
}
void DestroyList(CLinkNode*& L) //�������Ա�
{
	CLinkNode* pre = L, * p = pre->next;
	while (p != L)
	{
		free(pre);
		pre = p;
		//pre��pͬ������һ�����
		p = pre->next;
	}
	free(pre);
	//��ʱp=L,preָ��β���,�ͷ���
}

bool ListInsert(CLinkNode*& L, int i, Student e) //�����i��Ԫ��
{
	int j = 1;
	CLinkNode* p = L, * s;
	if (i <= 0) return false;
	//i���󷵻ؼ�
	if (p->next == L || i == 1)
		//ԭ������Ϊ�ձ��i=1��Ϊ�����������
	{
		s = (CLinkNode*)malloc(sizeof(CLinkNode)); //�����½��s
		s->data = e;
		s->next = p->next;
		//�����s���뵽���p֮��
		p->next = s;
		return true;
	}
	else
	{
		p = L->next;
		while (j <= i - 2 && p != L)
			//�ҵ�i-1�����p
		{
			j++;
			p = p->next;
		}
		if (p == L)
			//δ�ҵ���i-1�����
			return false;
		else
			//�ҵ���i-1�����p
		{
			s = (CLinkNode*)malloc(sizeof(CLinkNode)); //�����½��s
			s->data = e;
			s->next = p->next;
			//�����s���뵽���p֮��
			p->next = s;
			return true;
		}
	}
}
