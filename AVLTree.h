#pragma once
#include<stdio.h>
#include<malloc.h>

#define LH 1//左子树比右子树高
#define EH 0//左右子树等高
#define RH -1//右子树比左子树高

typedef struct BBSTNode {
	int data;//数据域
	int bf;//平衡因子
	struct BBSTNode *lchild, *rchild;//左子树，右子树
}*BBSTree, BBSTNode;

typedef enum status{
  ERROR,OK
}Status;//状态枚举体

Status Init_AVLTree(BBSTree* T);//初始化空树

void L_Rotate(BBSTree* p);//左旋调整

void R_Rotate(BBSTree* p);//右旋调整

void L_Balance(BBSTree* T);//左平衡处理

void R_Balance(BBSTree* T);//右平衡处理

Status Insert_AVLTree(BBSTree* T, int data,Status* taller);//插入结点

BBSTree Search_AVLTree(BBSTree T,int data);//搜索结点

BBSTree Delete_AVLTree(BBSTree T, int data);//删除结点

void FirstOrderTraverse(BBSTree T, void (*foo)(int));//先序遍历

void MiddleOrderTraverse(BBSTree T, void(*foo)(int));//中序遍历

void LateOrderTraverse(BBSTree T, void(*foo)(int));//后序遍历

int TreeDepth(BBSTree T);//求树深

int LeaveCount(BBSTree T);//求叶子数目

void print(int data);//输出数据域

void Merge(BBSTree *T1,BBSTree *T2);//平衡二叉树的合并

void Split(BBSTree *T, BBSTree *T1, BBSTree *T2, int data);//平衡二叉树的分裂

void ListPrint(BBSTree T, int count);//凹入表打印