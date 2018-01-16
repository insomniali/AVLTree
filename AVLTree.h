#pragma once
#include<stdio.h>
#include<malloc.h>

#define LH 1//����������������
#define EH 0//���������ȸ�
#define RH -1//����������������

typedef struct BBSTNode {
	int data;//������
	int bf;//ƽ������
	struct BBSTNode *lchild, *rchild;//��������������
}*BBSTree, BBSTNode;

typedef enum status{
  ERROR,OK
}Status;//״̬ö����

Status Init_AVLTree(BBSTree* T);//��ʼ������

void L_Rotate(BBSTree* p);//��������

void R_Rotate(BBSTree* p);//��������

void L_Balance(BBSTree* T);//��ƽ�⴦��

void R_Balance(BBSTree* T);//��ƽ�⴦��

Status Insert_AVLTree(BBSTree* T, int data,Status* taller);//������

BBSTree Search_AVLTree(BBSTree T,int data);//�������

BBSTree Delete_AVLTree(BBSTree T, int data);//ɾ�����

void FirstOrderTraverse(BBSTree T, void (*foo)(int));//�������

void MiddleOrderTraverse(BBSTree T, void(*foo)(int));//�������

void LateOrderTraverse(BBSTree T, void(*foo)(int));//�������

int TreeDepth(BBSTree T);//������

int LeaveCount(BBSTree T);//��Ҷ����Ŀ

void print(int data);//���������

void Merge(BBSTree *T1,BBSTree *T2);//ƽ��������ĺϲ�

void Split(BBSTree *T, BBSTree *T1, BBSTree *T2, int data);//ƽ��������ķ���

void ListPrint(BBSTree T, int count);//������ӡ