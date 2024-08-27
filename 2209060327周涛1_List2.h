#pragma once
#include <stdio.h>
#include <malloc.h>
typedef int ElemType;
typedef struct Node
//定义双链表结点类型
{
	ElemType data;
	struct Node* next;
	//指向后继结点
} CLinkNode;
void InitList(CLinkNode*& L);
void DestroyList(CLinkNode*& L);
bool ListEmpty(CLinkNode* L);
int ListLength(CLinkNode* L);
void DispList(CLinkNode* L);
bool GetElem(CLinkNode* L, int i, ElemType& e);
int LocateElem(CLinkNode* L, ElemType e);
bool ListInsert(CLinkNode*& L, int i, ElemType e);
bool ListDelete(CLinkNode*& L, int i, ElemType& e);