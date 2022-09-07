#include <iostream>
#include <algorithm>
#include<ctime>
using namespace std;
clock_t start, out;

int Puzzle[9] = { 2, 8, 3, 1, 6, 4, 7, 0, 5 };     //初始化八数码
int target[9] = { 1, 2, 3, 8, 0, 4, 7, 6, 5 };

typedef struct status						//描述问题状态
{
	int puzzle[9];							//记录八数码状态
	int white;						    //记录没有数字的那一块
	int Hash;								//为了快速判断结点是否存在引入的哈希值
	int HVal;								//启发函数值
	int depth;						    //记录深度
	struct status* Next = NULL;			//后向结点指针
	struct status* Prev = NULL;			//前驱结点指针
}STATUS;


STATUS* OpenHead = new STATUS;	 //创建Open表,保存所有已生成而未考察的结点
STATUS* CloseHead = NULL;		     //创建Close表,暂为空,保存所有已考察的结点

/*三个主要算法*/
void DFS(STATUS* Node);				 //DFS算法主体
void BFS(STATUS* Node);				 //BFS算法主体
void AStar(STATUS* Node);			 //AStar算法主体
/*自定义满足该题意函数*/
void SwapOpen();						 //从大到小，直接插入排序
void init();							 //初始化
int Hash(STATUS* Node);	   		     //哈希函数
void Reset(STATUS* Node);			 //重置链表
int Heruistic(STATUS* Node, int num);	 //启发函数
int Searchwhite(STATUS* Node);		 //查找没有数字那块的位置
int Issafe(int in, int two);			     //是否越界
void Output(STATUS* Current);			 //遍历输出链表元素（用于Open表、Close表打印）
void ResultOut(STATUS* Current, int num, int right);  //回溯法输出结果
void Showpuzzle(int Puzzle[]);				        //展示八数码
/*以下为基础数据结构链表的操作实现方法*/
void InsertClose(STATUS* Node);			    	//直接插入到CLose链表末尾 
void InsertOpen(STATUS* Node);				//直接插入到Open链表末尾 
void InsertOpenHead(STATUS* Node);			//直接插入到Open链表头部
STATUS* isInClose(STATUS* Node);			//使用哈希值查找指定的结点，下同
STATUS* isInOpen(STATUS* Node);
STATUS* GetLastNodeClose();				//遍历整个链表并返回最后一个元素，下同
STATUS* GetLastNodeOpen();
void RemoveClose(STATUS* Node);		//移除链表指定结点，下同
void RemoveOpen(STATUS* Node);

void AI()
{
	int num = 0;
	STATUS* Current = NULL;
	init();               // 重置Open表和Close表以及当前结点，便于执行下一个算法
	while (OpenHead)						//Open表非空
	{

		num++;
		//cout << num << endl;
		Current = GetLastNodeOpen();		//从Open表中得到启发函数最小的结点作为父节点，并从Open表中删除
		//Output(CloseHead);
		//cout << "-------------------------Close切割线--------------------------" << endl;
		RemoveOpen(Current);
		//Showpuzzle(Current->puzzle);

		if (Current->Hash == 123804765)	//达到目标状态则输出结果，否则继续A*算法
		{

			ResultOut(Current, num, 1);
			break;
		}
		else
			//DFS(Current);              //选择算法
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
	shuffle(Puzzle);                             //自定义随机初始化
	//random_shuffle(Puzzle, Puzzle + 9);         //选择随机初始化
	cout << "初始状态为：" << endl;
	Showpuzzle(Puzzle);
	cout << "目标状态为：" << endl;
	Showpuzzle(target);
	//random_shuffle(Puzzle, Puzzle + 9);
	//Showpuzzle();

	start = clock();
	//DFS();
	AI();
	out = clock();		                          //程序结束用时

	double endtime = (double)(out - start) / CLOCKS_PER_SEC;
	cout << "Total time:" << endtime * 1000 << "ms" << endl;	//ms为单位
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
	do                                                //回溯法
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
	cout << "访问结点总数为：" << num << endl;
	cout << "找到的路线所经过结点数为：" << count + 1 << endl;
}


void Output(STATUS* Current)
{
	while (Current)
	{
		Showpuzzle(Current->puzzle);
		Current = Current->Next;
	}
}


int Issafe(int in, int two)		                               //是否越界
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

int Searchwhite(STATUS* Node)                    //查找没有数字那块的位置
{
	for (int i = 0; i < 9; i++)
		if (Node->puzzle[i] == 0)
			return i;
	return -1;
}

int Heruistic(STATUS* Node, int num)				//启发函数
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

void Reset(STATUS* Node)                        //重置链表
{
	while (Node->Next)
		Reset(Node->Next);
	if (Node == OpenHead)
		return;
	delete(Node);
	Node = NULL;
}

int Hash(STATUS* Node)                         //哈希函数
{
	int sum = 0;
	for (int i = 0; i < 9; i++)
	{
		sum *= 10;
		sum += Node->puzzle[i];
	}
	return sum;
}

void init()			                             //初始化
{
	Reset(OpenHead);                //重置Open表和Close表，便于执行下一个算法
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

	while (Hash(NodeTmp) != Hash(Node))		  //使用哈希值查找指定的结点，下同
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

STATUS* GetLastNodeOpen()				//遍历整个链表并返回最后一个元素，下同
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


STATUS* isInOpen(STATUS* Node)				  //使用哈希值查找指定的结点，下同
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

void InsertOpenHead(STATUS* Node)		            //直接插入到链表头部，下同
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

void InsertOpen(STATUS* Node)					  //直接插入到链表末尾，下同
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

void SwapOpen()										//从大到小，直接插入排序
{
	STATUS* NodeFirst = NULL;
	STATUS* NodeTmp = NULL;
	STATUS* Nodeq = NULL;
	STATUS* Nodep = NULL;

	if (OpenHead == NULL)
		return;

	NodeFirst = OpenHead->Next; 		//原链表剩下用于直接插入排序的节点链表
	OpenHead->Next = NULL; 			//只含有一个节点的链表的有序链表

	while (NodeFirst != NULL) 				//遍历剩下无序的链表
	{
		for (NodeTmp = NodeFirst, Nodeq = OpenHead; ((Nodeq != NULL) && (Nodeq->HVal > NodeTmp->HVal)); \
			Nodep = Nodeq, Nodeq = Nodeq->Next); 			//无序节点在有序链表中找插入的位置

	//找到了插入的位置则退出for循环
		NodeFirst = NodeFirst->Next;       //无序链表中的节点离开，以便它插入到有序链表中

		if (Nodeq == OpenHead) 			 //插在第一个节点之前
		{
			OpenHead = NodeTmp;
		}
		else 										//p是q的前驱
		{
			Nodep->Next = NodeTmp;
		}

		NodeTmp->Next = Nodeq; 					//完成插入动作
	}
}

void AStar(STATUS* Node)
{
	int move[4];                                //设置4种移动算子
	move[0] = -3;                              //向上
	move[1] = 3;                               //向下
	move[2] = -1;                              //向左
	move[3] = 1;                               //向右



	for (int i = 0; i < 4; i++)
	{
		STATUS* Child = new STATUS;
		STATUS* NodeTmp;

		Child->white = Node->white + move[i];
		if (!Issafe(Child->white, Node->white))        //判断是否安全
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



		if (((NodeTmp = isInOpen(Child)) == NULL) && ((NodeTmp = isInClose(Child)) == NULL))			             //若子结点不在Open表和Close表中
		{
			InsertOpen(Child);						 //将子结点插入Open表中
		}
		else if ((NodeTmp = isInOpen(Child)) != NULL)    //若子结点在Open表中
		{
			if (Child->depth < NodeTmp->depth)//子结点的深度小于Open表中的深度
			{
				NodeTmp->HVal = Child->HVal;	    //更新OPEN表中的启发函数
				NodeTmp->Prev = Node;				//重新确定父结点
				NodeTmp->depth = Child->depth;
			}

			Child->Next = NULL;						//删除结点，防止内存泄漏
			delete Child;
			Child = NULL;
		}
		else											//子结点在CLOSE表中
		{
			NodeTmp = isInClose(Child);				//取得该结点

			if (Child->depth < NodeTmp->depth)		//子结点的深度小于Close表中的深度
			{
				NodeTmp->HVal = Child->HVal;		//更新Close表中的启发函数值
				NodeTmp->Prev = Node;				//重新确定父结点
				NodeTmp->depth = Child->depth;

				InsertOpen(NodeTmp);				//将此结点从CLOSE表中移出, 并放入OPEN表中
				RemoveClose(NodeTmp);
			}

			Child->Next = NULL;						//删除结点，防止内存泄漏
			delete Child;
			Child = NULL;
		}
	}
	InsertClose(Node);								//将父节点插入CLOSE表中;
	SwapOpen();										//根据启发函数重排OPEN表。这样循环中每一步只考虑OPEN表中状态最好的结点
}

void BFS(STATUS* Node)
{
	int move[4];                     //设置4种移动算子
	move[0] = -3;                   //向上
	move[1] = 3;                    //向下
	move[2] = -1;                   //向左
	move[3] = 1;                    //向右

	//Showpuzzle(Node->puzzle);
	for (int i = 0; i < 4; i++)
	{
		STATUS* Child = new STATUS;
		STATUS* NodeTmp;

		Child->white = Node->white + move[i];
		if (!Issafe(Child->white, Node->white))              //判断是否安全
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



		if ((NodeTmp = isInClose(Child)) != NULL)		//若子结点在Close表中
			continue;
		InsertOpenHead(Child);						//将子结点插入Open表头中

	}
	InsertClose(Node);								//将父节点插入CLOSE表中;
}

void DFS(STATUS* Node)
{
	int move[4];                  //设置4种移动算子
	move[0] = -3;                //向上
	move[1] = 3;                 //向下
	move[2] = -1;                //向左
	move[3] = 1;                 //向右


	//Showpuzzle(Node->puzzle);
	for (int i = 0; i < 4; i++)
	{
		STATUS* Child = new STATUS;
		STATUS* NodeTmp;

		Child->white = Node->white + move[i];
		if (!Issafe(Child->white, Node->white))              //判断是否安全
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

		if ((NodeTmp = isInClose(Child)) != NULL)			//若子结点在Close表中
			continue;
		InsertOpen(Child);							   //将子结点插入Open表中

	}
	InsertClose(Node);								//将父节点插入CLOSE表中;

}