#include"stdio.h"
#include"malloc.h"
#include"stdlib.h"
#include"string.h"

//通用状态码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -3
#define INFEASTABLE -1
#define OVERFLOW -2

#define LIST_NUMBER 10
#define maxleng 100

typedef int status;
/*基本元素*/
typedef struct ElemType{
    char name[10];
    char StudentID[10];
    int class1;
}ElemType;
/*结点结构*/
typedef struct BiTNode{
    struct BiTNode *lchild;
    ElemType student;
    struct BiTNode *rchild;
}BiTNode;

/*头结点*/
typedef struct{
	BiTNode *root;
}HNode;

/*二叉树结构*/
typedef struct{
	HNode *head;
}BiTree;

/*多树结构*/
typedef struct{
    BiTree *elem;
}BITREES;

/*函数声明*/
status InitBiTrees(BITREES *T);
status DestroyBiTrees(BITREES *T);
status ChooseTree(BiTree *T);
status TREESEmpty(BITREES *T);
status InitBiTree(BiTree *T);
status DestroyBiTree(BiTree *T);
status ClearBiTree(BiTree *T);
status BiTreeEmpty(BiTree *T);
void CreateBiTree1(BiTNode **T);
status CreateBiTree2(BiTNode **T);
int BiTreeDepth(BiTNode *T);
status Root(BiTree *T);
status Value(BiTree *T, char *ID, BiTNode *e, int *flag);
status Assign(BiTree *T, char *ID, int *flag);
status Parent(BiTree *T, char *ID, BiTNode *e, int *flag);
status LeftChild(BiTree *T, char *ID, BiTNode *e, int *flag);
status RightChild(BiTree *T, char *ID, BiTNode *e, int *flag);
status LeftSibling(BiTree *T, char *ID, BiTNode *e, int *flag);
status RightSibling(BiTree *T, char *ID, BiTNode *e, int *flag);
void PreOrderTraverse(BiTNode *N);
void InOrderTraverse(BiTNode *N);
void PostOrderTraverse(BiTNode *N);
status LevelOrderTraverse(BiTree *T);
void ReadFiles(BiTNode **root, FILE *fp, char *filename);
void WriteFiles(BiTNode *T, FILE *fp, char *filename);
void ShowMenu(void);
void ChooseOperation(BiTree *T, char *ID, int option, BiTNode *child, int *flag);
void ChooseOperation1(BiTree *T, BiTNode *e , char *ID ,int option, int*flag);
status InsertChild(BiTree **T, BiTNode *p, int LR, int *flag);
status DeleteChild(BiTree *T, BiTNode *p, int LR, int *flag);

int main(void)
{
    BITREES TREES;
    int op1 = 1;
    int status_1;
	int i_choose;
    while(op1)
    {
        system("cls");	printf("\n\n");
		ShowMenu();
		scanf("%d", &op1);
        switch(op1){
            case 1:
                status_1 = InitBiTrees(&TREES);
                if(status_1 == OK)
                    printf("多树初始化成功！\n");
                else{
                    if(status_1 == OVERFLOW)
                        printf("多树初始化失败！\n");
                    else
                        printf("多树已存在，操作错误！\n");
                }
                system("pause");
                break;
            case 3:
                if(TREESEmpty(&TREES) == TRUE){
                    printf("多树不存在！\n");
                    system("pause");
                    break;
                }
                printf("请输入你选择的树序号[1-10]：");
                scanf("%d", &i_choose);
				if(i_choose < 1 || i_choose > LIST_NUMBER)
                {
                    printf("序号不合法，操作失败！\n");
                    system("pause");
                    break;
                }
                status_1 = ChooseTree(&(TREES.elem[i_choose - 1]));
                system("pause");
                break;
            case 2:
                status_1 = DestroyBiTrees(&TREES);
                if(status_1 == OK)
                    printf("销毁成功！");
                else
                    printf("当前多树不存在，销毁失败！\n");
                system("pause");
                break;
            case 0:
                break;

        }
    }
}
//函数名：InitBiTrees
//形参列表:多树指针
//用户输入：无
//返回参数：int（状态指示量）
//函数功能：初始化多表
status InitBiTrees(BITREES *T){
    T->elem = (BiTree *)malloc(LIST_NUMBER*sizeof(BiTree));
    if(T->elem == NULL)
        return OVERFLOW;
    for(int i = 0; i < LIST_NUMBER; ++i)
        (T->elem[i]).head = NULL;
    return OK;
}
//函数名：TREESEmpty
//形参列表:树指针
//用户输入：无
//返回参数：int（状态指示量）
//函数功能：判断多树是否存在
status TREESEmpty(BITREES *T){
    if(T->elem == NULL)
        return TRUE;
    else
        return FALSE;
}
//函数名：DestroyBiTrees
//形参列表:多树指针
//用户输入：无
//返回参数：int（状态指示量）
//函数功能：销毁多表
status DestroyBiTrees(BITREES *T){
    if(TREESEmpty(T) == OK)
        return ERROR;
    free((*T).elem);
    T->elem = NULL;
    return OK;
}
//函数名：ChooseTree
//形参列表:多树指针
//用户输入：无
//返回参数：int（状态指示量）
//函数功能：对单个树进行操作
status ChooseTree(BiTree *T){
int op = 1, flag;
int status1, op1;
BiTNode e;
char filename[10], ID[10];
FILE *fp;
    while(op)
    {
		system("cls");	printf("\n\n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitBiTree       	12.RightChild\n");
		printf("    	  2. DestroyBiTree      13.LeftSibling\n");
		printf("    	  3. CreateBiTree       14.RightSibling\n");
		printf("    	  4. ClearBiTree     	15.InsertChild\n");
		printf("    	  5. BiTreeEmpty    	16.DeleteChild\n");
		printf("          6. BiTreeDepth        17.PrerderTraverse\n");
		printf("          7. Root               18.InOrderTraverse\n");
		printf("          8. Value              19.PostOrderTraverse\n");
		printf("          9. Assign             20.LevelOrderTraverse\n");
		printf("          10.Parent             21.ReadFile\n");
		printf("          11.LeftChild          22.WriteFile\n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你对当前二叉树的操作[0~22]:");
		scanf("%d", &op);
		switch (op) {
		case 1:
		    status1 = InitBiTree(T);
			if (status1 == ERROR) printf("二叉树已存在，创建失败！\n");
			else printf("二叉树创建成功！\n");
			system("pause");
			break;
		case 2:
		    status1 = DestroyBiTree(T);
			if (status1 == ERROR)
				printf("二叉树不存在，销毁失败！ \n");
			else
				printf("二叉树销毁成功！\n");
			system("pause");
			break;
		case 3:
			if(T->head == NULL)
				printf("二叉树不存在！\n");
			else
				{
					printf("请输入数据：\n");
					CreateBiTree1(&(T->head->root));
					printf("二叉树创建成功！\n");
				}
			system("pause");
			break;
		case 4:
		    if(ClearBiTree(T) == ERROR)
                printf("二叉树不存在，清除失败！\n");
            else if(status1 == OK)
                printf("二叉树清除成功！\n");
			else
				printf("二叉树为空！\n");
			system("pause");
			break;
		case 5:
			status1 = BiTreeEmpty(T);
		    if(status1 == ERROR)
                printf("二叉树不存在，判断出错！\n");
            else if(status1 == TRUE)
                    printf("二叉树为空！\n");
                else
                    printf("二叉树不为空！\n");
			system("pause");
			break;
		case 6:
			if(T->head == NULL)
					printf("二叉树不存在！\n");
			else{
				status1 = BiTreeDepth(T->head->root);
				printf("当前二叉树的深度为%d!\n", status1);
			}
			system("pause");
			break;
		case 7:
			status1 = Root(T);
			if(status1 == ERROR)
				printf("二叉树不存在，操作失败！");
			else if(status1 == OK)
					{
						printf("当前二叉树的根节点为：\n");
						printf("name:%s		StudentID:%s	class:%d", T->head->root->student.name, T->head->root->student.StudentID, T->head->root->student.class1);
					}
			else
				printf("当前二叉树为空树! \n");
			system("pause");
			break;
		case 8:
			flag = 1;
		    printf("请输入想查找同学的学号：");
		    scanf("%s", ID);
		    status1 = Value(T, ID, &e, &flag);
		    if(status1 == ERROR)
                printf("二叉树不存在，操作错误！\n");
            else if(status1 == FALSE)
                    printf("当前二叉树为空树！\n");
			else if(flag == 1)
					printf("当前二叉树没有学号为%s的同学！\n", ID);
				else
					printf("找到了！\nname:%s	StudentID:%s	class:%d\n", e.student.name, e.student.StudentID, e.student.class1);
			system("pause");
			break;
		case 9:
			flag = 1;
		    printf("请输入想修改同学的学号：");
		    scanf("%s", ID);
		    status1 = Assign(T, ID, &flag);
		    if(status1 == ERROR)
                printf("二叉树不存在！\n");
            else if(flag == 1)
                    printf("当前二叉树中不存在该学号！\n");
			else if(status1 == FALSE)
					printf("当前二叉树为空树！\n");
			else printf("操作成功！\n");
			system("pause");
			break;
		case 10:
			flag = 1;
		    printf("请输入想查询双亲的孩子的学号：");
		    scanf("%s", ID);
		    status1 = Parent(T, ID, &e, &flag);
		 	if(status1 == ERROR)
				printf("二叉树不存在！\n");
			else if(status1 == FALSE)
					printf("当前树为空树！\n");
			else if(flag == 1)
					printf("当前二叉树中不存在该学号的同学！\n");
			else
				printf("查询成功！\nname:%s	ID:%s	class:%d\n", e.student.name, e.student.StudentID, e.student.class1);
			system("pause");
			break;
		case 11:
			flag = 1;
		    printf("请输入想操作同学的学号：");
		    scanf("%s", ID);
            status1 = LeftChild(T, ID, &e, &flag);
            if(status1 == ERROR)
                printf("二叉树不存在！\n");
            else if(flag == 1)
				printf("当前二叉树不存在该学号！\n");
			else if(!(strcmp(e.student.name, "~")))
					printf("当前二叉树不存在该学号的左孩子！\n");
			else if(status1 == FALSE)
				printf("当前二叉树为空树！\n");
			else
			    printf("操作成功，左孩子是name:%s\tstudentID:%s\tClass:%d \n", e.student.name, e.student.StudentID, e.student.class1);
			system("pause");
			break;
		case 12:
			flag = 1;
			printf("请输入想操作同学的学号：");
		    scanf("%s", ID);
            status1 = RightChild(T, ID, &e, &flag);
            if(status1 == ERROR)
                printf("二叉树不存在！\n");
            else if(flag == 1)
					printf("当前二叉树不存在该学号！\n");
			else if(!(strcmp(e.student.name, "~")))
					printf("当前二叉树不存在该学号的右孩子！\n");
			else if(status1 == FALSE)
					printf("当前二叉树为空树！\n");
			else printf("操作成功，右孩子是name:%s\tstudentID:%s\tClass:%d \n", e.student.name, e.student.StudentID, e.student.class1);
			system("pause");
			break;
        case 13:
			flag = 1;
   			printf("请输入想操作同学的学号：");
		    scanf("%s", ID);
            status1 = LeftSibling(T, ID, &e, &flag);
            if(status1 == ERROR)
                printf("二叉树不存在！\n");
            else if(flag == 1)
					printf("当前二叉树不存在该节点或者该节点没有左兄弟！\n");
			else if(status1 == FALSE)
					printf("当前二叉树为空树！\n");
			else if(!strcmp(e.student.name, "~"))
					printf("该结点不存在左兄弟！\n");
			else
                printf("操作成功，左兄弟是name:%s\tstudentID:%s\tClass:%d \n", e.student.name, e.student.StudentID, e.student.class1);
			system("pause");
            break;
        case 14:
			flag = 1;
			printf("请输入想操作同学的学号：");
		    scanf("%s", ID);
            status1 = RightSibling(T, ID, &e, &flag);
             if(status1 == ERROR)
                printf("二叉树不存在！\n");
            else if(flag == 1)
					printf("当前二叉树不存在该节点或者该节点没有右兄弟！\n");
			else if(status1 == FALSE)
					printf("当前二叉树为空树！\n");
			else if(!strcmp(e.student.name, "~"))
					printf("该结点不存在右兄弟！\n");
			else
                printf("操作成功，右兄弟是name:%s\tstudentID:%s\tClass:%d \n", e.student.name, e.student.StudentID, e.student.class1);
            system("pause");
            break;
		case 15:
			flag = 1;
			printf("请输入要插入结点的学号和序号（0左1右）：");
			scanf("%s%d", e.student.StudentID, &op1);
			status1 = InsertChild(&T, &e, op1, &flag);
			if(status1 == ERROR)
				printf("当前二叉树不存在！\n");
			else if(status1 == FALSE)
					printf("当前二叉树为空树！\n");
			else if(flag == 1)
					printf("当前二叉树不存在该节点！\n");
			else 	printf("插入成功！\n");
            system("pause");
            break;
		case 16:
			flag = 1;
			printf("请输入要删除结点的学号和序号（0左1右）：");
			scanf("%s%d", e.student.StudentID, &op1);
			status1 = DeleteChild(T, &e, op1, &flag);
			if(status1 == ERROR)
				printf("当前二叉树不存在！\n");
			else if(status1 == FALSE)
					printf("当前二叉树为空树！\n");
			else if(flag == 1)
					printf("当前二叉树不存在该节点！\n");
			else 	printf("删除成功！\n");
			system("pause");
			break;
		case 17:
			if(T->head == NULL)
				printf("当前二叉树不存在！\n");
			else{
				PreOrderTraverse(T->head->root);
				printf("遍历成功！\n");
			}
			system("pause");
			break;
		case 18:
			if(T->head == NULL)
				printf("当前二叉树不存在！\n");
			else{
				InOrderTraverse(T->head->root);
				printf("遍历成功！\n");
			}
			system("pause");
			break;
		case 19:
			if(T->head == NULL)
				printf("当前二叉树不存在！\n");
			else{
				PostOrderTraverse(T->head->root);
				printf("遍历成功！\n");
			}
			system("pause");
			break;
		case 20:
			status1 = LevelOrderTraverse(T);
		 	if(status1 == ERROR)
				printf("二叉树不存在！\n");
			else if(status1 == FALSE)
					printf("当前树为空树！\n");
			else if(status1 == OK)
					printf("遍历成功！\n");
			system("pause");
			break;
		case 21:
			printf("请输入要读入的文件名：");
			scanf("%s", filename);
			if((fp = fopen(filename, "rb")) == NULL)
				printf("Files open error!\n");
			else if(T->head == NULL)
				printf("当前二叉树不存在！\n");
			else
			{
				ReadFiles(&(T->head->root), fp, filename);
				printf("写入成功！\n");
			}
			fclose(fp);
			system("pause");
			break;
		case 22:
			printf("请输入要写入的文件名：");
			scanf("%s", filename);
			if((fp = fopen(filename, "wb")) == NULL)
				printf("Files open error!\n");
			else if(T->head == NULL)
				printf("当前二叉树不存在！\n");
			else
			{
				WriteFiles(T->head->root, fp, filename);
				printf("写入成功！\n");
			}
			fclose(fp);
			system("pause");
			break;
		case 0:
			break;
		}//end of switch
	}//end of while
}
//函数名：InitBiTree
//形参列表:树指针
//用户输入：无
//返回参数：int（状态指示量）
//函数功能：初始化树
status InitBiTree(BiTree *T) {
	if (T->head)
		return ERROR;
	T->head = (HNode *)malloc(sizeof(HNode));//带头结点的二叉树
	T->head->root = NULL;
	return OK;
}
//函数名：DestroyBiTree
//形参列表:树指针
//用户输入：无
//返回参数：int（状态指示量）
//函数功能：摧毁当前树
status DestroyBiTree(BiTree *T) {
	if(T->head == NULL)
		return ERROR;
	free(T->head); //释放头结点
	T->head = NULL;
	return OK;
}
//函数名：ClearBiTree
//形参列表:树指针
//用户输入：无
//返回参数：int（状态指示量）
//函数功能：清空当前树
status ClearBiTree(BiTree *T) {
	if(T->head == NULL)
		return ERROR;
	free(T->head->root);	//将头结点指针域中的root指针指向的二叉树释放掉
	T->head->root = NULL;
	return OK;
}
//函数名：BiTreeEmpty
//形参列表:树指针
//用户输入：无
//返回参数：int（状态指示量）
//函数功能：判断树是否为空
status BiTreeEmpty(BiTree *T) {
	if(T->head == NULL)
		return ERROR;
	if(!(T->head->root))	//若头结点指针域中的root指针指向空，则为空树
		return OK;
	else return FALSE;
}

//函数名：ShowMenu
//形参列表:无
//用户输入：无
//返回参数：无
//函数功能：输出Menu
void ShowMenu(void){
        printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. IntiaTable       3.ChooseList\n");
		printf("    	  2. DestroyTable     \n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
        printf("  请选择你的操作[0-3]:");
}
//函数名：CreateBiTree1
//形参列表: 指向结点指针的指针
//用户输入：无
//返回参数：int（状态参数）
//函数功能：创建二叉树
void CreateBiTree1(BiTNode **T)
{

	ElemType e;
	scanf("%s%s%d", e.name, e.StudentID, &(e.class1));
	if(!strcmp(e.name,"~"))	(*T) = NULL;
	else
	{
		(*T) = (BiTNode *)malloc(sizeof(BiTNode));
		(*T)->student = e;
		CreateBiTree1(&((*T)->lchild));
		CreateBiTree1(&((*T)->rchild));
	}
	return;

}
//函数名：CreateBiTree2
//形参列表: 结点指针
//用户输入：无
//返回参数：int（状态参数）
//函数功能：创建二叉树
status CreateBiTree2(BiTNode **T)
{
	ElemType e;
	int i;
	BiTNode *s[maxleng + 1], *root, *t;
	scanf("%s%s%d%d", e.name, e.StudentID, e.class1, i);

}
//函数名：BiTreeDepth
//形参列表: 树指针
//用户输入：无
//返回参数：int
//函数功能：求树的深度
int BiTreeDepth(BiTNode *T)
{
	int i, j;
	if(!T) return 0;
	i = BiTreeDepth(T->lchild);
	j = BiTreeDepth(T->rchild);
	return i>j ? (i+1) : (j+1);
}
//函数名：Root
//形参列表: 树指针
//用户输入：无
//返回参数：int（状态参数）
//函数功能：返回根指针
status Root(BiTree *T)
{
	if(!(T->head))
		return ERROR;
	if(!(T->head->root))
		return FALSE;
	return OK;
}
//函数名：Value
//形参列表: 树指针、要查找的学号
//用户输入：无
//返回参数：int（状态参数）
//函数功能：返回结点值
status Value(BiTree *T, char *ID, BiTNode *e, int *flag)
{
	if(T->head == NULL)
		return ERROR;
	if(T->head->root == NULL)
		return FALSE;
	ChooseOperation(T, ID, 2, e, flag); 	//查找
	return OK;
}
//函数名：Assign
//形参列表: 树指针
//用户输入：要修改同学的姓名和班级
//返回参数：int（状态参数）
//函数功能：修改结点的值
status Assign(BiTree *T, char *ID, int *flag)
{
	BiTNode child;
	if(!(T->head))	return ERROR;
	if(!(T->head->root))	return FALSE;
	ChooseOperation(T, ID, 3, &child, flag);
	return OK;
}
//函数名：LeftChild
//形参列表: 树指针、学号、接收孩子指针
//用户输入：要查找左孩子的结点
//返回参数：int（状态参数）
//函数功能：查找结点的左孩子
status LeftChild(BiTree *T, char *ID, BiTNode *lchild, int *flag)
{
	if(!(T->head))	return ERROR;
	if(BiTreeEmpty(T))	return FALSE;
	ChooseOperation(T, ID, 4, lchild, flag);
	return OK;
}
//形参列表: 树指针、学号、接收孩子指针
//用户输入：要查找右孩子的结点
//返回参数：int（状态参数）
//函数功能：查找结点的右孩子
status RightChild(BiTree *T, char *ID, BiTNode *rchild, int *flag)
{
	if(!(T->head))	return ERROR;
	if(BiTreeEmpty(T))	return FALSE;
	ChooseOperation(T, ID, 5, rchild, flag);
	return OK;
}
//函数名：ChooseOperation
//形参列表: 树指针、要查找的学号、int（选择的操作）
//用户输入：无
//返回参数：无
//函数功能：非递归遍历二叉树并选择在遍历过程中的操作
void ChooseOperation(BiTree *T, char *ID, int option, BiTNode *child, int *flag)
{
        BiTNode *s[maxleng+1], *t = T->head->root, *Pre = NULL;
		int top = 0;

		do{
			while(t)
			{
				if(top == maxleng) exit(OVERFLOW);
				s[top++] = t;
				t = t->lchild;
			}
			if(top)
			{
				t = s[--top];
				if(option == 0) ;//空语句
				else
				{
					if(option == 1)
						printf("name:%s StudentID:%s class:%d\n",t->student.name, t->student.StudentID, t->student.class1);
					else if(option == 2)
						{
							if(!(strcmp(ID, t->student.StudentID)))
							{
								*child = *t;
								*flag = 0;
								break;
							}
						}
					else if (option == 3)
					{
								if(!(strcmp(ID, t->student.StudentID)))
								{
									printf("请输入该学号为%s的同学最新的姓名和班级:\n");

									if(scanf("%s%d", t->student.name, &(t->student.class1)) == 2)
										printf("修改成功！\n");
									printf("当前该同学的信息为：name:%s StudentID:%s Class:%d",t->student.name, t->student.StudentID, t->student.class1);
									*flag = 0;
									break;
								}
					}
					else if(option == 4)
                        {
                            if(!(strcmp(ID, t->student.StudentID)))
							{
                                if(t->lchild == NULL)
								{
									strcpy(child->student.name,"~");
									*flag = 0;
									break;
								}
								*child = *(t->lchild);
								*flag = 0;
								break;
							}
                        }
					else if(option == 5)
                            if(!(strcmp(ID, t->student.StudentID)))
                            {
                                if(t->rchild == NULL)
                                {
                                    strcpy(child->student.name,"~");
                                    *flag = 0;
                                    break;
                                }
                                *child = *(t->rchild);
                                *flag = 0;
                                break;
                            }
						t = t->rchild;
				}
			}
		}while(top || t);
}
//函数名：Parent
//形参列表: 树指针、char数组（学号）
//用户输入：要查找的学号
//返回参数：int（状态参量）
//函数功能：寻找孩子的双亲
status Parent(BiTree *T, char *ID, BiTNode *e, int *flag)
{
	if(T->head == NULL)	return ERROR;
	if(T->head->root == NULL)	return FALSE;
	ChooseOperation1(T, e, ID, 1, flag);
	return OK;
}
//函数名：LeftSibling
//形参列表: 树指针、结点学号
//用户输入：学号
//返回参数：int（状态参量）
//函数功能：非递归遍历二叉树并选择在遍历过程中的操作
status LeftSibling(BiTree *T, char *ID, BiTNode *e, int *flag)
{
	if(T->head == NULL)	return ERROR;
	if(T->head->root == NULL)	return FALSE;
	ChooseOperation1(T, e, ID, 2, flag);
	return OK;
}
//函数名：RightSibling
//形参列表: 树指针、结点学号
//用户输入：学号
//返回参数：int（状态参量）
//函数功能：非递归遍历二叉树并选择在遍历过程中的操作
status RightSibling(BiTree *T, char *ID, BiTNode *e, int* flag)
{
	if(T->head == NULL)	return ERROR;
	if(T->head->root == NULL)	return FALSE;
	ChooseOperation1(T, e, ID, 3, flag);
	return OK;
}
//函数名：ChooseOperation1
//形参列表: 树指针、返回的结点、int（选择的操作）
//用户输入：无
//返回参数：无
//函数功能：非递归遍历二叉树并选择在遍历过程中的操作
void ChooseOperation1(BiTree *T, BiTNode *e , char *ID ,int option, int *flag)
{
	BiTNode *s[maxleng+1], *t = T->head->root;
	int top = 0;
	do{
		while(t)
		{
			if(top == maxleng)	exit(OVERFLOW);
			s[top++] = t;
			t = t->lchild;
		}
		if(top)
		{
			t = s[--top];
			if(option == 1)
			{
				if(t->lchild == NULL)	;//空语句
				else if(!strcmp(t->lchild->student.StudentID, ID))
					{
						*e = *t;
						*flag = 0;
						break;
					}
				if(t->rchild == NULL)	;//空语句
				else if(!strcmp(t->rchild->student.StudentID, ID))
					{
						*e = *t;
						*flag = 0;
						break;
					}
			}
			else if(option == 2)
			{
				
				if(t->rchild == NULL)	;//空语句
				else if(!strcmp(t->rchild->student.StudentID, ID))
					{
						if(t->lchild == NULL)
						{
							strcpy(e->student.name, "~");
							*flag = 0;
							break;
						}
						else
						{
							*e = *(t->lchild);
							*flag = 0;
							break;
						}
					}
			}
			else if(option == 3)
			{
				if(t->lchild == NULL)	;//空语句
				else if(!strcmp(t->lchild->student.StudentID, ID))
					{
						if(t->rchild == NULL)
						{
							strcpy(e->student.name, "~");
							*flag = 0;
							break;
						}
						else{
							*e = *(t->rchild);
							*flag = 0;
							break;
						}
					}
			}
			t = t->rchild;
		}
	}while(t || top);
}
//函数名：PreOrderTraverse
//形参列表: 树指针
//用户输入：无
//返回参数：无
//函数功能：前序遍历二叉树
void PreOrderTraverse(BiTNode *N)
{
	if(N)
	{
		printf("name:%s	StudentID:%s Class:%d\n",N->student.name, N->student.StudentID, N->student.class1);
		PreOrderTraverse(N->lchild);
		PreOrderTraverse(N->rchild);
	}
	return;
}
//函数名：InOrderTraverse
//形参列表: 树指针
//用户输入：无
//返回参数：无
//函数功能：中序遍历二叉树
void InOrderTraverse(BiTNode *N)
{
	if(N)
	{
		InOrderTraverse(N->lchild);
		printf("name:%s	StudentID:%s Class:%d\n",N->student.name, N->student.StudentID, N->student.class1);
		InOrderTraverse(N->rchild);
	}
	return;
}
//函数名：PostOrderTraverse
//形参列表: 树指针
//用户输入：无
//返回参数：无
//函数功能：后序遍历二叉树
void PostOrderTraverse(BiTNode *N)
{
	if(N)
	{
		PostOrderTraverse(N->lchild);
		PostOrderTraverse(N->rchild);
		printf("name:%s	StudentID:%s Class:%d\n",N->student.name, N->student.StudentID, N->student.class1);
	}
	return;
}
//函数名：WriteFiles
//形参列表: 结点变量，文件指针，字符串（文件的名字）
//用户输入：要写入二进制文件的名字
//返回参数：无
//函数功能：将当二叉树结点的元素写入二进制文件
void WriteFiles(BiTNode *T, FILE *fp, char *filename)
{
   ElemType e;
   if(!T)
   {
	   strcpy(e.name, "~");
	   strcpy(e.StudentID, "~");
	   e.class1 = 0;
	   fwrite(&e, sizeof(ElemType), 1, fp);
   }
   else{
	   e = T->student;
	   fwrite(&e, sizeof(ElemType), 1, fp);
	   WriteFiles(T->lchild, fp, filename);
	   WriteFiles(T->rchild, fp, filename);
   }
   return;
}
//函数名：ReadFiles
//形参列表: 结点变量，文件指针，字符串（文件的名字）
//用户输入：要写入二进制文件的名字
//返回参数：无
//函数功能：将当二叉树结点的元素读入到二进制文件
void ReadFiles(BiTNode **root, FILE *fp, char *filename)
{
   ElemType e;
   fread(&e, sizeof(ElemType), 1, fp);
   if(!(strcmp(e.name, "~")))	(*root) = NULL;
   else
   {
	   (*root) = (BiTNode *)malloc(sizeof(BiTNode));
	   (*root)->student = e;
	   ReadFiles(&((*root)->lchild), fp, filename);
	   ReadFiles(&((*root)->rchild), fp, filename);
   }
}
//函数名：InsertChild
//形参列表: 结点变量，结点指针，int选择项，int指针
//用户输入：插入的树，选择插入位置
//返回参数：int（状态参数）
//函数功能：选择性的插入子树
status InsertChild(BiTree **T, BiTNode *p, int LR, int *flag)
{
	if((*T)->head == NULL)
		return ERROR;
	else if((*T)->head->root ==NULL)
			return FALSE;
	BiTNode *s[maxleng+1], *t = (*T)->head->root;
	BiTNode *oNode, *In_root;//In_root 指向要插入树的根， oNode用指向要修改的结点
	BiTNode *iNode;
	int top = 0;

	do
	{
		while(t)
		{
			if(top == maxleng)	exit(OVERFLOW);
			s[top++] = t;
			t = t->lchild;
		}
		if(top)
		{
			t = s[--top];
			if(!strcmp(p->student.StudentID, t->student.name))
			{
				printf("请输入子树信息：\n");
				CreateBiTree1(&In_root);
				if(LR == 1)
				{
					oNode = t;
					iNode = t->rchild;
					oNode->rchild = In_root;
					In_root->rchild = iNode;
					*flag = 0;
					break;
				}
				else if(LR == 0)
				{
					oNode = t;
					iNode = t->lchild;
					oNode->lchild = In_root;
					In_root->lchild = iNode;
					*flag = 0;
					break;
				}

			}
			t = t->rchild;
		}
	}while(top || t);
		return OK;
}
//函数名：Deletechild
//形参列表: 结点变量，结点指针，int选择项，int指针
//用户输入：要写入二进制文件的名字
//返回参数：无
//函数功能：选择性的插入子树
status DeleteChild(BiTree *T, BiTNode *p, int LR, int *flag)
{
	if(T->head == NULL)
		return ERROR;
	else if(T->head->root ==NULL)
			return FALSE;
	BiTNode *s[maxleng+1], *t = T->head->root;
	BiTNode *iNode;
	int top = 0;
	do
	{
		while(t)
		{
			if(top == maxleng)	exit(OVERFLOW);
			s[top++] = t;
			t = t->lchild;
		}
		if(top)
		{
			t = s[--top];
			if(!strcmp(p->student.StudentID, t->student.name))
			{
				if(LR == 1)
				{
					free(t->rchild);
					t->rchild = NULL;
					*flag = 0;
					break;
				}
				else if(LR == 0)
				{
					free(t->lchild);
					t->lchild = NULL;
					*flag = 0;
					break;
				}

			}
			t = t->rchild;
		}
	}while(top || t);
		return OK;
}
//函数名：LevelOrderTraverse
//形参列表: 二叉树指针
//用户输入：无
//返回参数：int(状态参量)
//函数功能：按层遍历二叉树
status LevelOrderTraverse(BiTree *T)
{
	if(T->head == NULL)
		return ERROR;
	else if(T->head->root == NULL)
			return FALSE;
	int pre = 0, rear = 0;
	BiTNode *Queue[10], *t;
	Queue[rear++] = T->head->root;
	while(rear != pre)
	{
		t = Queue[(pre++)%10];
		if(t->lchild)	Queue[(rear++)%10] = t->lchild;
		if(t->rchild)	Queue[(rear++)%10] = t->rchild;
		printf("Name:%s  ID:%s  Class:%d\n", t->student.name, t->student.StudentID, t->student.class1);
	}
	return OK;
}