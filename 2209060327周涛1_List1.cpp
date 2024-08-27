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
	free(pre);
}
bool ListEmpty(DLinkNode* L)	//�����Ա��Ƿ�Ϊ�ձ�
{
	return(L->next == NULL);
}
int ListLength(DLinkNode* L)	//�����Ա�ĳ���
{
	DLinkNode* p = L;
	int i = 0;					//pָ��ͷ���,i����Ϊ0
	while (p->next != NULL)		//��β���p
	{
		i++;					//i��Ӧ���p�����
		p = p->next;
	}
	return(i);
}
void DispList(DLinkNode* L)		//������Ա�
{
	DLinkNode* p = L->next;
	while (p != NULL)
	{
		printf("%c ", p->data);
		p = p->next;
	}
	printf("\n");
}
bool GetElem(DLinkNode* L, int i, ElemType& e)	//�����Ա��е�i��Ԫ��ֵ
{
	int j = 0;
	DLinkNode* p = L;
	if (i <= 0) return false;		//i���󷵻ؼ�
	while (j < i && p != NULL)		//���ҵ�i�����p
	{
		j++;
		p = p->next;
	}
	if (p == NULL)				//û���ҵ����ؼ�			
		return false;
	else						//�ҵ�����ȡֵ��������
	{
		e = p->data;
		return true;
	}
}
int LocateElem(DLinkNode* L, ElemType e)	//���ҵ�һ��ֵ��Ϊe��Ԫ�����
{
	int i = 1;
	DLinkNode* p = L->next;
	while (p != NULL && p->data != e)	//���ҵ�һ��ֵ��Ϊe�Ľ��p
	{
		i++;						//i��Ӧ���p�����
		p = p->next;
	}
	if (p == NULL)					//û���ҵ�����0
		return(0);
	else							//�ҵ��˷��������
		return(i);
}
bool ListInsert(DLinkNode*& L, int i, ElemType e)	//�����i��Ԫ��
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
bool ListDelete(DLinkNode*& L, int i, ElemType& e)  //ɾ����i��Ԫ��
{
	int j = 0;
	DLinkNode* p = L, * q;			//pָ��ͷ���,j����Ϊ0
	if (i <= 0) return false;		//i���󷵻ؼ�
	while (j < i - 1 && p != NULL)	//���ҵ�i-1�����p
	{
		j++;
		p = p->next;
	}
	if (p == NULL)				//δ�ҵ���i-1�����
		return false;
	else						//�ҵ���i-1����p
	{
		q = p->next;				//qָ���i�����
		if (q == NULL)			//�������ڵ�i�����ʱ����false
			return false;
		e = q->data;
		p->next = q->next;		//��˫������ɾ�����q
		if (p->next != NULL)		//��p�����ں�̽��,�޸���ǰ��ָ��
			p->next->prior = p;
		free(q);				//�ͷ�q���
		return true;
	}
}
