#include <iostream>
#include <algorithm>
#include<ctime>
using namespace std;
clock_t start, out;

int Puzzle[9] = { 2, 8, 3, 1, 6, 4, 7, 0, 5 };     //��ʼ��������
int target[9] = { 1, 2, 3, 8, 0, 4, 7, 6, 5 };

typedef struct status						//��������״̬
{
	int puzzle[9];							//��¼������״̬
	int white;						    //��¼û�����ֵ���һ��
	int Hash;								//Ϊ�˿����жϽ���Ƿ��������Ĺ�ϣֵ
	int HVal;								//��������ֵ
	int depth;						    //��¼���
	struct status* Next = NULL;			//������ָ��
	struct status* Prev = NULL;			//ǰ�����ָ��
}STATUS;


STATUS* OpenHead = new STATUS;	 //����Open��,�������������ɶ�δ����Ľ��
STATUS* CloseHead = NULL;		     //����Close��,��Ϊ��,���������ѿ���Ľ��

/*������Ҫ�㷨*/
void DFS(STATUS* Node);				 //DFS�㷨����
void BFS(STATUS* Node);				 //BFS�㷨����
void AStar(STATUS* Node);			 //AStar�㷨����
/*�Զ�����������⺯��*/
void SwapOpen();						 //�Ӵ�С��ֱ�Ӳ�������
void init();							 //��ʼ��
int Hash(STATUS* Node);	   		     //��ϣ����
void Reset(STATUS* Node);			 //��������
int Heruistic(STATUS* Node, int num);	 //��������
int Searchwhite(STATUS* Node);		 //����û�������ǿ��λ��
int Issafe(int in, int two);			     //�Ƿ�Խ��
void Output(STATUS* Current);			 //�����������Ԫ�أ�����Open��Close���ӡ��
void ResultOut(STATUS* Current, int num, int right);  //���ݷ�������
void Showpuzzle(int Puzzle[]);				        //չʾ������
/*����Ϊ�������ݽṹ����Ĳ���ʵ�ַ���*/
void InsertClose(STATUS* Node);			    	//ֱ�Ӳ��뵽CLose����ĩβ 
void InsertOpen(STATUS* Node);				//ֱ�Ӳ��뵽Open����ĩβ 
void InsertOpenHead(STATUS* Node);			//ֱ�Ӳ��뵽Open����ͷ��
STATUS* isInClose(STATUS* Node);			//ʹ�ù�ϣֵ����ָ���Ľ�㣬��ͬ
STATUS* isInOpen(STATUS* Node);
STATUS* GetLastNodeClose();				//�������������������һ��Ԫ�أ���ͬ
STATUS* GetLastNodeOpen();
void RemoveClose(STATUS* Node);		//�Ƴ�����ָ����㣬��ͬ
void RemoveOpen(STATUS* Node);

void AI()
{
	int num = 0;
	STATUS* Current = NULL;
	init();               // ����Open���Close���Լ���ǰ��㣬����ִ����һ���㷨
	while (OpenHead)						//Open��ǿ�
	{

		num++;
		//cout << num << endl;
		Current = GetLastNodeOpen();		//��Open���еõ�����������С�Ľ����Ϊ���ڵ㣬����Open����ɾ��
		//Output(CloseHead);
		//cout << "-------------------------Close�и���--------------------------" << endl;
		RemoveOpen(Current);
		//Showpuzzle(Current->puzzle);

		if (Current->Hash == 123804765)	//�ﵽĿ��״̬�����������������A*�㷨
		{

			ResultOut(Current, num, 1);
			break;
		}
		else
			//DFS(Current);              //ѡ���㷨
			//BFS(Current);
			AStar(Current);
	}
	printf("Successed");

}
void shuffle(int Puzzle[])
{
	int ini[9] = { 0 };
	int num;
	for (int i = 0; i < 9; i++)
	{
		while ((num = rand() % 9) != -1)
		{
			if (ini[num] == 0)
			{
				Puzzle[i] = num;
				ini[num] = 1;
				break;
			}
		}
	}
}
int main()
{
	srand(time(NULL));
	shuffle(Puzzle);                             //�Զ��������ʼ��
	//random_shuffle(Puzzle, Puzzle + 9);         //ѡ�������ʼ��
	cout << "��ʼ״̬Ϊ��" << endl;
	Showpuzzle(Puzzle);
	cout << "Ŀ��״̬Ϊ��" << endl;
	Showpuzzle(target);
	//random_shuffle(Puzzle, Puzzle + 9);
	//Showpuzzle();

	start = clock();
	//DFS();
	AI();
	out = clock();		                          //���������ʱ

	double endtime = (double)(out - start) / CLOCKS_PER_SEC;
	cout << "Total time:" << endtime * 1000 << "ms" << endl;	//msΪ��λ
}
void Showpuzzle(int Puzzle[])
{
	for (int i = 0; i < 9; i++)
	{
		cout << Puzzle[i];
		if ((i + 1) % 3 == 0)
			cout << endl;
	}
	cout << "___________" << endl;
}

void ResultOut(STATUS* Current, int num, int right)
{

	Current->Next = NULL;
	int count = 0;
	do                                                //���ݷ�
	{
		count++;
		Current->Prev->Next = Current;
		Current = Current->Prev;
	} while (Current->Prev != NULL);

	if (right)
	{
		while (Current != NULL)
		{
			Showpuzzle(Current->puzzle);
			Current = Current->Next;
		}
	}
	cout << "���ʽ������Ϊ��" << num << endl;
	cout << "�ҵ���·�������������Ϊ��" << count + 1 << endl;
}


void Output(STATUS* Current)
{
	while (Current)
	{
		Showpuzzle(Current->puzzle);
		Current = Current->Next;
	}
}


int Issafe(int in, int two)		                               //�Ƿ�Խ��
{
	if (in < 0 || in>8)
		return 0;
	if (two == 0 || two == 3 || two == 6)
		if (in == two - 1)
			return 0;
	if (two == 2 || two == 5 || two == 8)
		if (in == two + 1)
			return 0;
	return 1;
}

int Searchwhite(STATUS* Node)                    //����û�������ǿ��λ��
{
	for (int i = 0; i < 9; i++)
		if (Node->puzzle[i] == 0)
			return i;
	return -1;
}

int Heruistic(STATUS* Node, int num)				//��������
{
	int result = 0;
	for (int i = 0; i < 9; i++)
		if (Node->puzzle[i] != target[i])
			result++;
	/*
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (Node->puzzle[j] == target[i])
			{
				result += int(j / 3);
			}
	*/
	return result + num;
}

void Reset(STATUS* Node)                        //��������
{
	while (Node->Next)
		Reset(Node->Next);
	if (Node == OpenHead)
		return;
	delete(Node);
	Node = NULL;
}

int Hash(STATUS* Node)                         //��ϣ����
{
	int sum = 0;
	for (int i = 0; i < 9; i++)
	{
		sum *= 10;
		sum += Node->puzzle[i];
	}
	return sum;
}

void init()			                             //��ʼ��
{
	Reset(OpenHead);                //����Open���Close������ִ����һ���㷨
	if (CloseHead)
		Reset(CloseHead);
	for (int i = 0; i < 9; i++)
		OpenHead->puzzle[i] = Puzzle[i];
	OpenHead->depth = 0;
	OpenHead->HVal = Heruistic(OpenHead, OpenHead->depth);
	OpenHead->Hash = Hash(OpenHead);
	OpenHead->white = Searchwhite(OpenHead);

}



void RemoveOpen(STATUS* Node)
{
	STATUS* NodeTmp = NULL;
	STATUS* NodeTmp2 = NULL;

	NodeTmp = OpenHead;

	while (Hash(NodeTmp) != Hash(Node))		  //ʹ�ù�ϣֵ����ָ���Ľ�㣬��ͬ
	{
		NodeTmp2 = NodeTmp;
		NodeTmp = NodeTmp->Next;
	}

	if (NodeTmp == OpenHead)
	{
		OpenHead = NodeTmp->Next;
		NodeTmp = OpenHead;
	}
	else
		NodeTmp2->Next = NodeTmp->Next;
}

void RemoveClose(STATUS* Node)
{
	STATUS* NodeTmp = NULL;
	STATUS* NodeTmp2 = NULL;

	NodeTmp = CloseHead;

	while (Hash(NodeTmp) != Hash(Node))
	{
		NodeTmp2 = NodeTmp;
		NodeTmp = NodeTmp->Next;
	}

	if (NodeTmp == CloseHead)
	{
		OpenHead = NodeTmp->Next;
		NodeTmp = CloseHead;
	}
	else
		NodeTmp2->Next = NodeTmp->Next;
}

STATUS* GetLastNodeOpen()				//�������������������һ��Ԫ�أ���ͬ
{
	STATUS* NodeTmp = OpenHead;

	if (NodeTmp == NULL)
		return NULL;
	else
	{
		while (NodeTmp->Next != NULL)
		{
			NodeTmp = NodeTmp->Next;
		}

		return NodeTmp;
	}
}


STATUS* GetLastNodeClose()
{
	STATUS* NodeTmp = CloseHead;

	if (NodeTmp == NULL)
		return NULL;
	else
	{
		while (NodeTmp->Next != NULL)
		{
			NodeTmp = NodeTmp->Next;
		}

		return NodeTmp;
	}
}


STATUS* isInOpen(STATUS* Node)				  //ʹ�ù�ϣֵ����ָ���Ľ�㣬��ͬ
{
	STATUS* NodeTmp = OpenHead;

	if (OpenHead == NULL)
		return NULL;

	do
	{
		if (Hash(NodeTmp) == Hash(Node))
			return NodeTmp;
		else
			NodeTmp = NodeTmp->Next;
	} while (NodeTmp != NULL);

	return NULL;
}

STATUS* isInClose(STATUS* Node)
{
	STATUS* NodeTmp = CloseHead;

	if (CloseHead == NULL)
		return NULL;

	do
	{
		if (Hash(NodeTmp) == Hash(Node))
			return NodeTmp;
		else
			NodeTmp = NodeTmp->Next;
	} while (NodeTmp != NULL);

	return NULL;
}

void InsertOpenHead(STATUS* Node)		            //ֱ�Ӳ��뵽����ͷ������ͬ
{
	STATUS* NodeTmp;

	if (OpenHead == NULL)
	{
		OpenHead = Node;
		return;
	}
	else
	{
		NodeTmp = OpenHead;
		OpenHead = Node;
		OpenHead->Next = NodeTmp;

	}
	return;
}

void InsertOpen(STATUS* Node)					  //ֱ�Ӳ��뵽����ĩβ����ͬ
{
	STATUS* NodeTmp;

	if (OpenHead == NULL)
	{
		OpenHead = Node;
		return;
	}
	else
	{
		NodeTmp = GetLastNodeOpen();
		NodeTmp->Next = Node;
		Node->Next = NULL;
	}
	return;
}

void InsertClose(STATUS* Node)
{
	STATUS* NodeTmp;

	if (CloseHead == NULL)
	{
		CloseHead = Node;
		return;
	}
	else
	{
		NodeTmp = GetLastNodeClose();
		NodeTmp->Next = Node;
		Node->Next = NULL;
	}
	return;
}

void SwapOpen()										//�Ӵ�С��ֱ�Ӳ�������
{
	STATUS* NodeFirst = NULL;
	STATUS* NodeTmp = NULL;
	STATUS* Nodeq = NULL;
	STATUS* Nodep = NULL;

	if (OpenHead == NULL)
		return;

	NodeFirst = OpenHead->Next; 		//ԭ����ʣ������ֱ�Ӳ�������Ľڵ�����
	OpenHead->Next = NULL; 			//ֻ����һ���ڵ���������������

	while (NodeFirst != NULL) 				//����ʣ�����������
	{
		for (NodeTmp = NodeFirst, Nodeq = OpenHead; ((Nodeq != NULL) && (Nodeq->HVal > NodeTmp->HVal)); \
			Nodep = Nodeq, Nodeq = Nodeq->Next); 			//����ڵ��������������Ҳ����λ��

	//�ҵ��˲����λ�����˳�forѭ��
		NodeFirst = NodeFirst->Next;       //���������еĽڵ��뿪���Ա������뵽����������

		if (Nodeq == OpenHead) 			 //���ڵ�һ���ڵ�֮ǰ
		{
			OpenHead = NodeTmp;
		}
		else 										//p��q��ǰ��
		{
			Nodep->Next = NodeTmp;
		}

		NodeTmp->Next = Nodeq; 					//��ɲ��붯��
	}
}

void AStar(STATUS* Node)
{
	int move[4];                                //����4���ƶ�����
	move[0] = -3;                              //����
	move[1] = 3;                               //����
	move[2] = -1;                              //����
	move[3] = 1;                               //����



	for (int i = 0; i < 4; i++)
	{
		STATUS* Child = new STATUS;
		STATUS* NodeTmp;

		Child->white = Node->white + move[i];
		if (!Issafe(Child->white, Node->white))        //�ж��Ƿ�ȫ
		{
			delete Child;
			Child = NULL;
			continue;
		}

		for (int j = 0; j < 9; j++)
			Child->puzzle[j] = Node->puzzle[j];
		Child->puzzle[Node->white] = Child->puzzle[Child->white];
		Child->puzzle[Child->white] = 0;
		Child->depth = Node->depth + 1;
		Child->HVal = Heruistic(Child, Child->depth);
		Child->Hash = Hash(Child);
		Child->Prev = Node;
		Child->Next = NULL;



		if (((NodeTmp = isInOpen(Child)) == NULL) && ((NodeTmp = isInClose(Child)) == NULL))			             //���ӽ�㲻��Open���Close����
		{
			InsertOpen(Child);						 //���ӽ�����Open����
		}
		else if ((NodeTmp = isInOpen(Child)) != NULL)    //���ӽ����Open����
		{
			if (Child->depth < NodeTmp->depth)//�ӽ������С��Open���е����
			{
				NodeTmp->HVal = Child->HVal;	    //����OPEN���е���������
				NodeTmp->Prev = Node;				//����ȷ�������
				NodeTmp->depth = Child->depth;
			}

			Child->Next = NULL;						//ɾ����㣬��ֹ�ڴ�й©
			delete Child;
			Child = NULL;
		}
		else											//�ӽ����CLOSE����
		{
			NodeTmp = isInClose(Child);				//ȡ�øý��

			if (Child->depth < NodeTmp->depth)		//�ӽ������С��Close���е����
			{
				NodeTmp->HVal = Child->HVal;		//����Close���е���������ֵ
				NodeTmp->Prev = Node;				//����ȷ�������
				NodeTmp->depth = Child->depth;

				InsertOpen(NodeTmp);				//���˽���CLOSE�����Ƴ�, ������OPEN����
				RemoveClose(NodeTmp);
			}

			Child->Next = NULL;						//ɾ����㣬��ֹ�ڴ�й©
			delete Child;
			Child = NULL;
		}
	}
	InsertClose(Node);								//�����ڵ����CLOSE����;
	SwapOpen();										//����������������OPEN������ѭ����ÿһ��ֻ����OPEN����״̬��õĽ��
}

void BFS(STATUS* Node)
{
	int move[4];                     //����4���ƶ�����
	move[0] = -3;                   //����
	move[1] = 3;                    //����
	move[2] = -1;                   //����
	move[3] = 1;                    //����

	//Showpuzzle(Node->puzzle);
	for (int i = 0; i < 4; i++)
	{
		STATUS* Child = new STATUS;
		STATUS* NodeTmp;

		Child->white = Node->white + move[i];
		if (!Issafe(Child->white, Node->white))              //�ж��Ƿ�ȫ
		{
			delete Child;
			Child = NULL;
			continue;
		}

		for (int j = 0; j < 9; j++)
			Child->puzzle[j] = Node->puzzle[j];
		Child->puzzle[Node->white] = Child->puzzle[Child->white];
		Child->puzzle[Child->white] = 0;
		Child->depth = Node->depth + 1;
		Child->HVal = Heruistic(Child, Child->depth);
		Child->Hash = Hash(Child);
		Child->Prev = Node;
		Child->Next = NULL;



		if ((NodeTmp = isInClose(Child)) != NULL)		//���ӽ����Close����
			continue;
		InsertOpenHead(Child);						//���ӽ�����Open��ͷ��

	}
	InsertClose(Node);								//�����ڵ����CLOSE����;
}

void DFS(STATUS* Node)
{
	int move[4];                  //����4���ƶ�����
	move[0] = -3;                //����
	move[1] = 3;                 //����
	move[2] = -1;                //����
	move[3] = 1;                 //����


	//Showpuzzle(Node->puzzle);
	for (int i = 0; i < 4; i++)
	{
		STATUS* Child = new STATUS;
		STATUS* NodeTmp;

		Child->white = Node->white + move[i];
		if (!Issafe(Child->white, Node->white))              //�ж��Ƿ�ȫ
		{
			delete Child;
			Child = NULL;
			continue;
		}

		for (int j = 0; j < 9; j++)
			Child->puzzle[j] = Node->puzzle[j];
		Child->puzzle[Node->white] = Child->puzzle[Child->white];
		Child->puzzle[Child->white] = 0;
		Child->depth = Node->depth + 1;
		Child->HVal = Heruistic(Child, Child->depth);
		Child->Hash = Hash(Child);
		Child->Prev = Node;
		Child->Next = NULL;

		if ((NodeTmp = isInClose(Child)) != NULL)			//���ӽ����Close����
			continue;
		InsertOpen(Child);							   //���ӽ�����Open����

	}
	InsertClose(Node);								//�����ڵ����CLOSE����;

}