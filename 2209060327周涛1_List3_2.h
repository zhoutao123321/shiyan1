#pragma once
#include <stdio.h>
#include <malloc.h>

// ����ѧ���ṹ��
typedef struct {
    char name[50];   //ѧ������
    char id[15];    //ѧ��
    char gender;     //�Ա�
    char major[50];  //רҵ
    int course_count;  //ѡ����Ŀ
    char course_ids[10][10];   //����б�
} Student;

typedef struct Node  //����ѭ��������������
{
    Student data;
	struct Node* next;
	//ָ���̽��
} CLinkNode;
void InitList(CLinkNode*& L);
void DestroyList(CLinkNode*& L);
bool ListInsert(CLinkNode*& L, int i, Student e);
