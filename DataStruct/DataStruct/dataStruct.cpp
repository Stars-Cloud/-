#include<stdio.h>

#define MAXSIZE 20

typedef struct {
	int data[MAXSIZE];
	int Length;
}SqList;

/*-----------------初始化----------------------*/
void InitList(SqList *L){
		L->Length = 0;
}

/*-----------------获取----------------------*/
int GetElem(SqList *L, int i) {
	int error = 0, ok = 1;
	if (L->Length == 0 || i<0 || i>L->Length)
		return error;
	else
		return L->data[i];
}

/*-----------------查找----------------------*/
int LocateElem(SqList* L, int e) {
	int error = 0, ok = 1;
	if (L->Length == 0) return error;
	for (int i = 0;i <= L->Length;i++) {
		if (L->data[i] == e) {
			return i;
		}
	}
	return ok;
}
/*-----------------插入----------------------*/
int Insert(SqList *L, int i, int e) {
	int error = 0, ok = 1, k;

	if (L->Length == MAXSIZE-1) return error;

	if (i<0 || i>L->Length) return error;

	if (i <= L->Length) {
		for (k = L->Length;k >= i;k--) {
			L->data[k + 1] = L->data[k];
		}
	}

	L->data[i] = e;
	L->Length++;
	return ok;
}

/*-----------------删除----------------------*/
int Delete(SqList* L, int i, int e) {
	int error = 0, ok = 1, k;
	if (L->Length == 0) return error;
	if (i<0 || i>L->Length + 1) return error;
	e = L->data[i];
	if (i <= L->Length) {
		for (k = i;k < L->Length;k++) {
			L->data[k] = L->data[k+1];
		}
	}
	L->Length--;
	return e;
}


void main()
{
	int e = 0, findSum;
	SqList *Sq, L;
	Sq = &L;
	InitList(Sq);
	Insert(Sq, 0, 5);
	Insert(Sq, 1, 10);
	Insert(Sq, 2, 6);
	Insert(Sq, 3, 8);
	Insert(Sq, 4, 2);
	printf("%d\n", Sq->data[1]);
	printf("%d\n", Sq->Length);

	Delete(Sq, 1, e);
	printf("\n%d\n", Sq->data[1]);
	printf("%d\n", Sq->Length);

	printf("\n%d\n", GetElem(Sq, 1));

	findSum = LocateElem(Sq, 8);
	printf("\n所查找的数的下标为:%d\n",findSum);
	printf("所查找的数为:%d\n", Sq->data[findSum]);

	printf("\n该顺序线性表的长度为：%d\n", Sq->Length);
}