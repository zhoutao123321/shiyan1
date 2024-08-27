#pragma once
#include <stdio.h>
#include <malloc.h>
typedef int ElemType;

typedef struct DNode
//����˫����������
{
	ElemType data;
	struct DNode* prior; //ָ��ǰ�����
	struct DNode* next;  //ָ���̽��
} DLinkNode;
void InitList(DLinkNode*& L);
void DestroyList(DLinkNode*& L);
bool ListEmpty(DLinkNode* L);
int ListLength(DLinkNode* L);
void DispList(DLinkNode* L);
bool GetElem(DLinkNode* L, int i, ElemType& e);
int LocateElem(DLinkNode* L, ElemType e);
bool ListInsert(DLinkNode*& L, int i, ElemType e);
bool ListDelete(DLinkNode*& L, int i, ElemType& e);