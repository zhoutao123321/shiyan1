#pragma once
#include <stdio.h>
#include <malloc.h>


// 定义课程结构体
typedef struct {
    char name[50];  //课程名
    char id[10];    //课程编号
    float credits;  //课程学分
    char instructor[50];    //主讲教师姓名
    char location[20];      //上课地点
    char description[100];    //课程描述
} Course;

typedef struct DNode
//定义双链表结点类型
{
    Course data;
	struct DNode* prior; //指向前驱结点
	struct DNode* next;
	//指向后继结点
} DLinkNode;

void InitList(DLinkNode*& L);
void DestroyList(DLinkNode*& L);
bool ListInsert(DLinkNode*& L, int i, Course e);
