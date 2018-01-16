#include"AVLTree.h"
#include<Windows.h>

void main(void) {
	BBSTree T1 = NULL;
	BBSTree T2 = NULL;
	BBSTree T3 = NULL;
	BBSTree T4 = NULL;
	BBSTree T5 = NULL;
	BBSTree T6 = NULL;
	int order = 20;
	int num = 0;
	Status taller1 = OK;
	Status taller2 = OK;
	while (1) {
		system("cls");
		printf("\n\n\n\n\n\n");
		printf("************************************************************************************************************************");
		printf("                                                    平衡二叉树的演绎                                                    ");
		printf("\n\n\n");
		printf("平衡二叉树显示区：\n");
		if (!T1)printf("T1为空树\n");
		else { printf("T1:\n"); ListPrint(T1, 0);
		}
		if (!T2)printf("T2为空树\n");
		else {
			printf("T2:\n"); ListPrint(T2, 0);
		}
		if (!T3)printf("T3为空树\n");
		else {
			printf("T3:\n"); ListPrint(T3, 0);
		}
		if (!T4)printf("T4为空树\n");
		else {
			printf("T4:\n"); ListPrint(T4, 0);
		}
		if (!T5)printf("T5为空树\n");
		else {
			printf("T5:\n"); ListPrint(T5, 0);
		}
		if (!T6)printf("T6为空树\n");
		else {
			printf("T6:\n"); ListPrint(T6, 0);
		}
		printf("\n\n\n");
		printf("************************************************************************************************************************");
		printf("请输入你想要的操作：\n");
		printf("T1操作：   1.初始化  2.插入  3.删除  4.查找  5.分裂\n");
		printf("T2操作：   6.初始化  7.插入  8.删除  9.查找  10.分裂\n");
		printf("0.退出     11.合并\n");
		scanf("%d", &order);
		switch (order) {
		case 0:
			exit(0);
		case 1:
			Init_AVLTree(&T1);
			printf("T1初始化成功\n");
			printf("按任意键返回\n");
			getchar();
			break;
		case 2:
			printf("请输入要插入的数字：\n");
			scanf("%d", &num);
			Insert_AVLTree(&T1, num, &taller1);
			printf("插入成功\n");
			printf("按任意键返回\n");
			getchar();
			break;
		case 3:printf("请输入要删除的数字：\n");
			scanf("%d", &num);
			T1 = Delete_AVLTree(T1, num);
			if (Search_AVLTree(T1, num) != ERROR)printf("删除失败\n");
			else printf("删除成功\n");
			printf("按任意键返回\n");
			getchar();
			break;
		case 4:
			printf("请输入要查找的数字：\n");
			scanf("%d", &num);
			if (Search_AVLTree(T1, num) == ERROR)printf("查找失败\n");
			else printf("查找成功\n");
			printf("按任意键返回\n");
			getchar();
			break;
		case 5:
			printf("请输入中间值：\n");
			scanf("%d", &num);
			Split(&T1, &T3, &T4, num);
			printf("分裂成功\n");
			printf("按任意键返回\n");
			getchar();
			break;
		case 6:
			Init_AVLTree(&T2);
			printf("T2初始化成功\n");
			printf("按任意键返回\n");
			getchar();
			break;
		case 7:
			printf("请输入要插入的数字：\n");
			scanf("%d", &num);
			Insert_AVLTree(&T2, num, &taller2);
			printf("插入成功\n");
			printf("按任意键返回\n");
			getchar();
			break;
		case 8:printf("请输入要删除的数字：\n");
			scanf("%d", &num);
			T1 = Delete_AVLTree(T2, num);
			if (Search_AVLTree(T2, num) != ERROR)printf("删除失败\n");
			else printf("删除成功\n");
			printf("按任意键返回\n");
			getchar();
			break;
		case 9:
			printf("请输入要查找的数字：\n");
			scanf("%d", &num);
			if (Search_AVLTree(T2, num) == ERROR)printf("查找失败\n");
			else printf("查找成功\n");
			printf("按任意键返回\n");
			getchar();
			break;
		case 10:
			printf("请输入中间值：\n");
			scanf("%d", &num);
			Split(&T2, &T5, &T6, num);
			printf("分裂成功\n");
			printf("按任意键返回\n");
			getchar();
			break;
		case 11:
			Merge(&T1, &T2);
			printf("合并成功\n");
			printf("按任意键返回\n");
			getchar();
			break;
		}
	}
	return ;
}