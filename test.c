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
		printf("                                                    ƽ�������������                                                    ");
		printf("\n\n\n");
		printf("ƽ���������ʾ����\n");
		if (!T1)printf("T1Ϊ����\n");
		else { printf("T1:\n"); ListPrint(T1, 0);
		}
		if (!T2)printf("T2Ϊ����\n");
		else {
			printf("T2:\n"); ListPrint(T2, 0);
		}
		if (!T3)printf("T3Ϊ����\n");
		else {
			printf("T3:\n"); ListPrint(T3, 0);
		}
		if (!T4)printf("T4Ϊ����\n");
		else {
			printf("T4:\n"); ListPrint(T4, 0);
		}
		if (!T5)printf("T5Ϊ����\n");
		else {
			printf("T5:\n"); ListPrint(T5, 0);
		}
		if (!T6)printf("T6Ϊ����\n");
		else {
			printf("T6:\n"); ListPrint(T6, 0);
		}
		printf("\n\n\n");
		printf("************************************************************************************************************************");
		printf("����������Ҫ�Ĳ�����\n");
		printf("T1������   1.��ʼ��  2.����  3.ɾ��  4.����  5.����\n");
		printf("T2������   6.��ʼ��  7.����  8.ɾ��  9.����  10.����\n");
		printf("0.�˳�     11.�ϲ�\n");
		scanf("%d", &order);
		switch (order) {
		case 0:
			exit(0);
		case 1:
			Init_AVLTree(&T1);
			printf("T1��ʼ���ɹ�\n");
			printf("�����������\n");
			getchar();
			break;
		case 2:
			printf("������Ҫ��������֣�\n");
			scanf("%d", &num);
			Insert_AVLTree(&T1, num, &taller1);
			printf("����ɹ�\n");
			printf("�����������\n");
			getchar();
			break;
		case 3:printf("������Ҫɾ�������֣�\n");
			scanf("%d", &num);
			T1 = Delete_AVLTree(T1, num);
			if (Search_AVLTree(T1, num) != ERROR)printf("ɾ��ʧ��\n");
			else printf("ɾ���ɹ�\n");
			printf("�����������\n");
			getchar();
			break;
		case 4:
			printf("������Ҫ���ҵ����֣�\n");
			scanf("%d", &num);
			if (Search_AVLTree(T1, num) == ERROR)printf("����ʧ��\n");
			else printf("���ҳɹ�\n");
			printf("�����������\n");
			getchar();
			break;
		case 5:
			printf("�������м�ֵ��\n");
			scanf("%d", &num);
			Split(&T1, &T3, &T4, num);
			printf("���ѳɹ�\n");
			printf("�����������\n");
			getchar();
			break;
		case 6:
			Init_AVLTree(&T2);
			printf("T2��ʼ���ɹ�\n");
			printf("�����������\n");
			getchar();
			break;
		case 7:
			printf("������Ҫ��������֣�\n");
			scanf("%d", &num);
			Insert_AVLTree(&T2, num, &taller2);
			printf("����ɹ�\n");
			printf("�����������\n");
			getchar();
			break;
		case 8:printf("������Ҫɾ�������֣�\n");
			scanf("%d", &num);
			T1 = Delete_AVLTree(T2, num);
			if (Search_AVLTree(T2, num) != ERROR)printf("ɾ��ʧ��\n");
			else printf("ɾ���ɹ�\n");
			printf("�����������\n");
			getchar();
			break;
		case 9:
			printf("������Ҫ���ҵ����֣�\n");
			scanf("%d", &num);
			if (Search_AVLTree(T2, num) == ERROR)printf("����ʧ��\n");
			else printf("���ҳɹ�\n");
			printf("�����������\n");
			getchar();
			break;
		case 10:
			printf("�������м�ֵ��\n");
			scanf("%d", &num);
			Split(&T2, &T5, &T6, num);
			printf("���ѳɹ�\n");
			printf("�����������\n");
			getchar();
			break;
		case 11:
			Merge(&T1, &T2);
			printf("�ϲ��ɹ�\n");
			printf("�����������\n");
			getchar();
			break;
		}
	}
	return ;
}