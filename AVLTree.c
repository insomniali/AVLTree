#include"AVLTree.h"


//��ʼ������
Status Init_AVLTree(BBSTree* T) {
	*T = NULL;
	return OK;
}

//��������
void L_Rotate(BBSTree* p) {
	BBSTree rc = (*p)->rchild;//rcָ��p�����Һ���
	(*p)->rchild = rc->lchild;//rc����������Ϊp���Һ���
	rc->lchild = (*p);//��p���Ϊrc��������
	(*p) = rc;//pָ���µĸ����
}

//��������
void R_Rotate(BBSTree* p) {
	BBSTree lc = (*p)->lchild;//lcָ��p��������
	(*p)->lchild = lc->rchild;//lc�����Һ�����Ϊp������
	lc->rchild = (*p);//��p���Ϊlc���Һ���
	(*p) = lc;//pָ���µĸ����
}

//��ƽ�⴦��
void L_Balance(BBSTree* T) {
	BBSTree lc,rd;
	lc = (*T)->lchild;//lcָ��T������
	switch (lc->bf){
	case LH://LL��
		(*T)->bf = lc->bf = EH; R_Rotate(T);break;
	case RH://LR��
		rd = lc->rchild;//rdָ��lc���Һ���
		switch (rd->bf) {//�޸�T�������ӵ�ƽ������
		case LH:(*T)->bf = RH; lc->bf = EH; break;
		case EH:(*T)->bf = lc->bf = EH; break;
		case RH:(*T)->bf = EH; lc->bf = LH; break;
		}
		rd->bf = EH; 
		L_Rotate(&((*T)->lchild));//��T������������������
		R_Rotate(T);//��T���������� 
		break;
	}
}

//��ƽ�⴦��
void R_Balance(BBSTree* T) {
	BBSTree rc, ld;
	rc = (*T)->rchild;//rcָ��T���Һ���
	switch (rc->bf) {
	case RH://RR��
		(*T)->bf = rc->bf = EH; L_Rotate(T); break;
	case LH://RL��
		ld = rc->lchild;//ldָ��rc������
		switch (ld->bf) {//�޸�T�����Һ��ӵ�ƽ������
		case LH:(*T)->bf = RH; rc->bf = EH; break;
		case EH:(*T)->bf = rc->bf = EH; break;
		case RH:(*T)->bf = EH; rc->bf = LH; break;
		}
		ld->bf = EH;
		R_Rotate(&((*T)->rchild));//��T������������������
		L_Rotate(T);//��T���������� 
		break;
	}
}

//������
Status Insert_AVLTree(BBSTree *T, int data ,Status *taller) {
	if (!(*T)) {
		(*T) = (BBSTree)malloc(sizeof(BBSTNode));
		(*T)->bf = EH;
		(*T)->lchild = NULL;
		(*T)->rchild = NULL;
		(*T)->data = data;
		*taller = OK;
		return OK;
	}
    if (data == (*T)->data) {
		*taller = ERROR;
		return ERROR;
	}
    if(data<(*T)->data){
		if (ERROR == Insert_AVLTree(&((*T)->lchild), data, taller))return ERROR;
		if (OK == *taller) {
			switch ((*T)->bf){
			case LH:L_Balance(T); *taller = ERROR; break;
			case EH:(*T)->bf = LH; *taller = OK; break;
			case RH:(*T)->bf = EH; *taller = ERROR; break;
			}
		}
	}
	else{
		if (ERROR == Insert_AVLTree(&((*T)->rchild), data, taller))return ERROR;
		if (OK == *taller) {
			switch ((*T)->bf) {
			case LH:(*T)->bf = EH; *taller = ERROR; break;
			case EH:(*T)->bf = RH; *taller = OK; break;
			case RH:R_Balance(T); *taller = ERROR; break;
			}
		}
	}
	return *taller;
}

//�������
BBSTree Search_AVLTree(BBSTree T,int data) {
	if (!T)return NULL;
	if (T->data == data)return T;
	BBSTree L = Search_AVLTree(T->lchild, data);
	if (L != NULL)return L;
	else {
		BBSTree R = Search_AVLTree(T->rchild, data);
		if (R)return R;
	}
	return NULL;
}

//ɾ�����
BBSTree Delete_AVLTree(BBSTree T, int data){
	if (T == NULL)return NULL;
	else if (data < T->data) {
		T->lchild = Delete_AVLTree(T->lchild,data);
		if (TreeDepth(T->lchild) - TreeDepth(T->rchild) == -2) {
			if (TreeDepth(T->rchild->rchild) > TreeDepth(T->rchild->lchild)) {
				T->bf = EH;
				T->rchild->bf = EH;
				L_Rotate(&T);
			}
			else {
				T->rchild->bf = LH;
				R_Balance(&T);
				T->rchild->bf = RH;
			}
		}
		else {
			T->bf = RH;
		}
	}
	else if (data > T->data) {
		T->rchild = Delete_AVLTree(T->rchild, data);
		if (TreeDepth(T->lchild) - TreeDepth(T->rchild)==2) {
			if (TreeDepth(T->lchild->lchild) > TreeDepth(T->lchild->rchild)) {
				T->bf = EH;
				T->lchild ->bf= EH;
				R_Rotate(&T);
			}
			else {
				T->lchild->bf = RH;
				L_Balance(&T);
				T->lchild->bf = LH;
			}
		}	
		else {
			T->bf = LH;
		}
	}
	else if (!T->lchild && !T->rchild) {
		free(T);
		return NULL;
	}
	else {
		if (T->lchild&&T->rchild) {
		BBSTree ptr = T->lchild;
		while (ptr->rchild) {
			ptr = ptr->rchild;
		}
		T->data = ptr->data;
		T->lchild = Delete_AVLTree(T->lchild, ptr->data);
		if (TreeDepth(T->lchild) - TreeDepth(T->rchild) == -2) {
			if (TreeDepth(T->rchild->rchild) > TreeDepth(T->rchild->lchild)) {
				T->bf = EH;
				T->rchild->bf = EH;
				L_Rotate(&T);
			}
			else {
				T->rchild->bf = LH;
				R_Balance(&T);
				T->rchild->bf = RH;
			}
		}
		else {
			T->bf = RH;
		}
	    }
		else if (T->lchild) {
			BBSTree ptr = T->lchild;
			T->data = ptr ->data;
			T->lchild = Delete_AVLTree(T->lchild, ptr->data);
			if (TreeDepth(T->lchild) - TreeDepth(T->rchild) == -2) {
				if (TreeDepth(T->rchild->rchild) > TreeDepth(T->rchild->lchild)) {
					T->bf = EH;
					T->rchild->bf = EH;
					L_Rotate(&T);
				}
				else {
					T->rchild->bf = LH;
					R_Balance(&T);
					T->rchild->bf = RH;
				}
			}
			else {
				T->bf = RH;
			}
		}
		else if (T->rchild) {
			BBSTree ptr = T->rchild;
			T->data = ptr->data;
			T->rchild = Delete_AVLTree(T->rchild, ptr->data);
			if (TreeDepth(T->lchild) - TreeDepth(T->rchild) == 2) {
				if (TreeDepth(T->lchild->lchild) > TreeDepth(T->lchild->rchild)) {
					T->bf = EH;
					T->lchild->bf = EH;
					R_Rotate(&T);
				}
				else {
					T->lchild->bf = RH;
					L_Balance(&T);
					T->lchild->bf = LH;
				}
			}
			else {
				T->bf = LH;
			}
		}
	}
	return T;
}

//�������
void FirstOrderTraverse(BBSTree T, void (*foo)(int)) {
	foo(T->data);
	if (T->lchild)FirstOrderTraverse(T->lchild, foo);
    if (T->rchild)FirstOrderTraverse(T->rchild, foo);
}

//�������
void MiddleOrderTraverse(BBSTree T, void(*foo)(int)) {
	if (T->lchild)MiddleOrderTraverse(T->lchild, foo);
	foo(T->data); 
	if(T->rchild)MiddleOrderTraverse(T->rchild, foo);
}

//�������
void LateOrderTraverse(BBSTree T, void(*foo)(int)){
	if (T->lchild)LateOrderTraverse(T->lchild, foo);
	if (T->rchild)LateOrderTraverse(T->rchild, foo);
	foo(T->data);
}

//������
int TreeDepth(BBSTree T) {
	if (!T)return 0;
	return (TreeDepth(T->lchild) > TreeDepth(T->rchild) ? TreeDepth(T->lchild) : TreeDepth(T->rchild)) + 1;
}

//��Ҷ����Ŀ
int LeaveCount(BBSTree T) {
	if (!T)return 0;
	if (!T->lchild && !T->rchild)return 1;
	int count = 0;
	count += LeaveCount(T->lchild);
	count += LeaveCount(T->rchild);
	return count;
}

//���������
void print(int data){
	printf("%d   ", data);
}

//������ӡ
void ListPrint(BBSTree T, int count) {
	int i = 0;
	if (T != NULL) {
		ListPrint(T->rchild, count + 5);
		for (i = 0; i < count; i++)printf(" ");
		printf("%d\n", T->data);
		ListPrint(T->lchild, count + 5);
	}
}

//ƽ��������ĺϲ�
void Merge(BBSTree *T1, BBSTree *T2) {
	Status taller = OK;
	BBSTree temp = NULL;
	while (*T2){
		temp = Search_AVLTree((*T2), (*T2)->data);
		Insert_AVLTree(T1, temp->data, &taller);
		(*T2) = Delete_AVLTree((*T2), temp->data);
	}
}

//ƽ��������ķ���
void Split(BBSTree *T, BBSTree *T1, BBSTree *T2, int data) {
	Status taller1 = OK;
	Status taller2 = OK;
	while ((*T)) {
		if ((*T)->data > data) {
			Insert_AVLTree(T1, (*T)->data, &taller1);
		}
		else Insert_AVLTree(T2, (*T)->data, &taller2);
		(*T) = Delete_AVLTree((*T), (*T)->data);
	}
}

