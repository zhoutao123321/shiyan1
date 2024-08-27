#pragma once
#include <stdio.h>
#include <malloc.h>
typedef int ElemType;

typedef struct DNode
//定义双链表结点类型
{
	ElemType data;
	struct DNode* prior; //指向前驱结点
	struct DNode* next;  //指向后继结点
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