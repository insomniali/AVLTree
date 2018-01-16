#include"AVLTree.h"


//初始化空树
Status Init_AVLTree(BBSTree* T) {
	*T = NULL;
	return OK;
}

//左旋调整
void L_Rotate(BBSTree* p) {
	BBSTree rc = (*p)->rchild;//rc指向p结点的右孩子
	(*p)->rchild = rc->lchild;//rc结点的左孩子置为p的右孩子
	rc->lchild = (*p);//置p结点为rc结点的左孩子
	(*p) = rc;//p指向新的根结点
}

//右旋调整
void R_Rotate(BBSTree* p) {
	BBSTree lc = (*p)->lchild;//lc指向p结点的左孩子
	(*p)->lchild = lc->rchild;//lc结点的右孩子置为p的左孩子
	lc->rchild = (*p);//置p结点为lc的右孩子
	(*p) = lc;//p指向新的根结点
}

//左平衡处理
void L_Balance(BBSTree* T) {
	BBSTree lc,rd;
	lc = (*T)->lchild;//lc指向T的左孩子
	switch (lc->bf){
	case LH://LL型
		(*T)->bf = lc->bf = EH; R_Rotate(T);break;
	case RH://LR型
		rd = lc->rchild;//rd指向lc的右孩子
		switch (rd->bf) {//修改T及其左孩子的平衡因子
		case LH:(*T)->bf = RH; lc->bf = EH; break;
		case EH:(*T)->bf = lc->bf = EH; break;
		case RH:(*T)->bf = EH; lc->bf = LH; break;
		}
		rd->bf = EH; 
		L_Rotate(&((*T)->lchild));//对T的左子树作左旋调整
		R_Rotate(T);//对T作右旋调整 
		break;
	}
}

//右平衡处理
void R_Balance(BBSTree* T) {
	BBSTree rc, ld;
	rc = (*T)->rchild;//rc指向T的右孩子
	switch (rc->bf) {
	case RH://RR型
		(*T)->bf = rc->bf = EH; L_Rotate(T); break;
	case LH://RL型
		ld = rc->lchild;//ld指向rc的左孩子
		switch (ld->bf) {//修改T及其右孩子的平衡因子
		case LH:(*T)->bf = RH; rc->bf = EH; break;
		case EH:(*T)->bf = rc->bf = EH; break;
		case RH:(*T)->bf = EH; rc->bf = LH; break;
		}
		ld->bf = EH;
		R_Rotate(&((*T)->rchild));//对T的右子树作右旋调整
		L_Rotate(T);//对T作左旋调整 
		break;
	}
}

//插入结点
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

//搜索结点
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

//删除结点
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

//先序遍历
void FirstOrderTraverse(BBSTree T, void (*foo)(int)) {
	foo(T->data);
	if (T->lchild)FirstOrderTraverse(T->lchild, foo);
    if (T->rchild)FirstOrderTraverse(T->rchild, foo);
}

//中序遍历
void MiddleOrderTraverse(BBSTree T, void(*foo)(int)) {
	if (T->lchild)MiddleOrderTraverse(T->lchild, foo);
	foo(T->data); 
	if(T->rchild)MiddleOrderTraverse(T->rchild, foo);
}

//后序遍历
void LateOrderTraverse(BBSTree T, void(*foo)(int)){
	if (T->lchild)LateOrderTraverse(T->lchild, foo);
	if (T->rchild)LateOrderTraverse(T->rchild, foo);
	foo(T->data);
}

//求树深
int TreeDepth(BBSTree T) {
	if (!T)return 0;
	return (TreeDepth(T->lchild) > TreeDepth(T->rchild) ? TreeDepth(T->lchild) : TreeDepth(T->rchild)) + 1;
}

//求叶子数目
int LeaveCount(BBSTree T) {
	if (!T)return 0;
	if (!T->lchild && !T->rchild)return 1;
	int count = 0;
	count += LeaveCount(T->lchild);
	count += LeaveCount(T->rchild);
	return count;
}

//输出数据域
void print(int data){
	printf("%d   ", data);
}

//凹入表打印
void ListPrint(BBSTree T, int count) {
	int i = 0;
	if (T != NULL) {
		ListPrint(T->rchild, count + 5);
		for (i = 0; i < count; i++)printf(" ");
		printf("%d\n", T->data);
		ListPrint(T->lchild, count + 5);
	}
}

//平衡二叉树的合并
void Merge(BBSTree *T1, BBSTree *T2) {
	Status taller = OK;
	BBSTree temp = NULL;
	while (*T2){
		temp = Search_AVLTree((*T2), (*T2)->data);
		Insert_AVLTree(T1, temp->data, &taller);
		(*T2) = Delete_AVLTree((*T2), temp->data);
	}
}

//平衡二叉树的分裂
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

