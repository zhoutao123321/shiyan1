#pragma once
#include <stdio.h>
#include <malloc.h>

// 定义学生结构体
typedef struct {
    char name[50];   //学生姓名
    char id[15];    //学号
    char gender;     //性别
    char major[50];  //专业
    int course_count;  //选课数目
    char course_ids[10][10];   //编号列表
} Student;

typedef struct Node  //定义循环单链表结点类型
{
    Student data;
	struct Node* next;
	//指向后继结点
} CLinkNode;
void InitList(CLinkNode*& L);
void DestroyList(CLinkNode*& L);
bool ListInsert(CLinkNode*& L, int i, Student e);
