#include<stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
	int data;                            //数据域
	struct Node* next;           //指针域
}Node;
typedef struct Node* LinkList;

/*------------------------获取第i个节点的data------------------------*/
int GetElem(LinkList L, int i) {
	int j=0, error = 0, ok = 1;
	LinkList p;
	p = L->next;
	while (p && j < i) {
		p = p->next;
		j++;
	}
	if (!p || j > i) {
		return error;
	}
	else {
		return p->data;
	}
	return ok;
}

/*--------------------------------插入-------------------------------*/
int InsertList(LinkList L, int i, int e) {
	int j = 0, error=0, ok=1;
	LinkList p, s;
	p = L->next;
	while (p && j < i) {
		p = p->next;
		j++;
	}
	if (!p || j > i) {
		return error;
	}
	s = (LinkList)malloc(sizeof(Node));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return ok;
}

/*--------------------------------删除-------------------------------*/
int deleteList(LinkList L, int i, int *e) {
	int j = 0, error=0, ok=1;
	LinkList p,q;
	L=p->next;
	while (p && j < i) {
		p = p -> next;
		j++;
	}
	if (!p || j > i) return error;
	q= p->next;
	p->next = q->next;
	*e = q->data;
	free(q);
	return ok;
}

/*--------------------------------创建-------------------------------*/
void createListHead(LinkList* L, int n) {
	int i = 0;
	LinkList p;
	srand(time(0));
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;
	for (i = 0;i < n;i++) {
		p = (LinkList)malloc(sizeof(Node));
		p->data = rand() % 100 + 1;
		p->next = (*L)->next;
		(*L)->next = p;
	}
}
void main() {

}