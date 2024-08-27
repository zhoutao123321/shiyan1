#pragma once
#include <stdio.h>
#include <malloc.h>


// ����γ̽ṹ��
typedef struct {
    char name[50];  //�γ���
    char id[10];    //�γ̱��
    float credits;  //�γ�ѧ��
    char instructor[50];    //������ʦ����
    char location[20];      //�Ͽεص�
    char description[100];    //�γ�����
} Course;

typedef struct DNode
//����˫����������
{
    Course data;
	struct DNode* prior; //ָ��ǰ�����
	struct DNode* next;
	//ָ���̽��
} DLinkNode;

void InitList(DLinkNode*& L);
void DestroyList(DLinkNode*& L);
bool ListInsert(DLinkNode*& L, int i, Course e);
