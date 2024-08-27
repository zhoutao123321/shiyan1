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
bool ListEmpty(CLinkNode* L)
//�����Ա��Ƿ�Ϊ�ձ�
{
	return(L->next == L);
}
int ListLength(CLinkNode* L)
//�����Ա�ĳ���
{
	CLinkNode* p = L; int i = 0;
	//pָ��ͷ���,n��Ϊ0(��ͷ�������Ϊ0)
	while (p->next != L)
	{
		i++;
		p = p->next;
	}
	return(i);
	//ѭ������,pָ��β���,�����nΪ������
}
void DispList(CLinkNode* L)
//������Ա�
{
	CLinkNode* p = L->next;
	while (p != L)
		//p��ΪL,���p����data��
	{
		printf("%c ", p->data);
		p = p->next;
	}
	printf("\n");
}
bool GetElem(CLinkNode* L, int i, ElemType& e) //�����Ա��е�i��Ԫ��ֵ
{
	int j = 1;
	CLinkNode* p = L->next;
	if (i <= 0 || L->next == L)
		//i������߿ձ��ؼ�
		return false;
	if (i == 1)
		//���1�����ֵ����Ϊ�����������
	{
		e = L->next->data;
		return true;
	}
	else
		//i��Ϊ1ʱ
	{
		while (j <= i - 1 && p != L)
			//�ҵ�i�����p
		{
			j++;
			p = p->next;
		}
		if (p == L)
			//û���ҵ����ؼ�
			return false;
		else
			//�ҵ�����ȡ����ֵ��������
		{
			e = p->data;
			return true;
		}
	}
}
int LocateElem(CLinkNode* L, ElemType e) //���ҵ�һ��ֵ��Ϊe��Ԫ�����
{
	CLinkNode* p = L->next;
	int i = 1;
	while (p != L && p->data != e) //���ҵ�һ��ֵ��Ϊe�Ľ��p
	{
		p = p->next;
		i++;
		//i��Ӧ���p�����
	}
	if (p == L)
		return(0);
	//û���ҵ�����0
	else
		return(i);
	//�ҵ��˷��������
}
bool ListInsert(CLinkNode*& L, int i, ElemType e) //�����i��Ԫ��
{
	int j = 1;
	CLinkNode* p = L, * s;
	if (i <= 0) return false;  //i���󷵻ؼ�
	if (p->next == L || i == 1)   //ԭ������Ϊ�ձ��i=1��Ϊ�����������
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
bool ListDelete(CLinkNode*& L, int i, ElemType& e)  //ɾ����i��Ԫ��
{
	int j = 1;
	CLinkNode* p = L, * q;
	if (i <= 0 || L->next == L)
		return false;  //i������߿ձ��ؼ�
	if (i == 1)  //i=1��Ϊ�����������
	{
		q = L->next;
		//ɾ����1�����
		e = q->data;
		L->next = q->next;
		free(q);
		return true;
	}
	else
		//i��Ϊ1ʱ
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
			q = p->next;
			//qָ��Ҫɾ���Ľ��
			e = q->data;
			p->next = q->next; //�ӵ�������ɾ��q���
			free(q);
			//�ͷ�q���
			return true;
		}
	}
}