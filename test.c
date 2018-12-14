#include"stdio.h"
#include"malloc.h"
#include"stdlib.h"
#include"string.h"

//ͨ��״̬��
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -3
#define INFEASTABLE -1
#define OVERFLOW -2

#define LIST_NUMBER 10
#define maxleng 100

typedef int status;
/*����Ԫ��*/
typedef struct ElemType{
    char name[10];
    char StudentID[10];
    int class1;
}ElemType;
/*���ṹ*/
typedef struct BiTNode{
    struct BiTNode *lchild;
    ElemType student;
    struct BiTNode *rchild;
}BiTNode;

/*ͷ���*/
typedef struct{
	BiTNode *root;
}HNode;

/*�������ṹ*/
typedef struct{
	HNode *head;
}BiTree;

/*�����ṹ*/
typedef struct{
    BiTree *elem;
}BITREES;

/*��������*/
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
                    printf("������ʼ���ɹ���\n");
                else{
                    if(status_1 == OVERFLOW)
                        printf("������ʼ��ʧ�ܣ�\n");
                    else
                        printf("�����Ѵ��ڣ���������\n");
                }
                system("pause");
                break;
            case 3:
                if(TREESEmpty(&TREES) == TRUE){
                    printf("���������ڣ�\n");
                    system("pause");
                    break;
                }
                printf("��������ѡ��������[1-10]��");
                scanf("%d", &i_choose);
				if(i_choose < 1 || i_choose > LIST_NUMBER)
                {
                    printf("��Ų��Ϸ�������ʧ�ܣ�\n");
                    system("pause");
                    break;
                }
                status_1 = ChooseTree(&(TREES.elem[i_choose - 1]));
                system("pause");
                break;
            case 2:
                status_1 = DestroyBiTrees(&TREES);
                if(status_1 == OK)
                    printf("���ٳɹ���");
                else
                    printf("��ǰ���������ڣ�����ʧ�ܣ�\n");
                system("pause");
                break;
            case 0:
                break;

        }
    }
}
//��������InitBiTrees
//�β��б�:����ָ��
//�û����룺��
//���ز�����int��״ָ̬ʾ����
//�������ܣ���ʼ�����
status InitBiTrees(BITREES *T){
    T->elem = (BiTree *)malloc(LIST_NUMBER*sizeof(BiTree));
    if(T->elem == NULL)
        return OVERFLOW;
    for(int i = 0; i < LIST_NUMBER; ++i)
        (T->elem[i]).head = NULL;
    return OK;
}
//��������TREESEmpty
//�β��б�:��ָ��
//�û����룺��
//���ز�����int��״ָ̬ʾ����
//�������ܣ��ж϶����Ƿ����
status TREESEmpty(BITREES *T){
    if(T->elem == NULL)
        return TRUE;
    else
        return FALSE;
}
//��������DestroyBiTrees
//�β��б�:����ָ��
//�û����룺��
//���ز�����int��״ָ̬ʾ����
//�������ܣ����ٶ��
status DestroyBiTrees(BITREES *T){
    if(TREESEmpty(T) == OK)
        return ERROR;
    free((*T).elem);
    T->elem = NULL;
    return OK;
}
//��������ChooseTree
//�β��б�:����ָ��
//�û����룺��
//���ز�����int��״ָ̬ʾ����
//�������ܣ��Ե��������в���
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
		printf("    ��ѡ����Ե�ǰ�������Ĳ���[0~22]:");
		scanf("%d", &op);
		switch (op) {
		case 1:
		    status1 = InitBiTree(T);
			if (status1 == ERROR) printf("�������Ѵ��ڣ�����ʧ�ܣ�\n");
			else printf("�����������ɹ���\n");
			system("pause");
			break;
		case 2:
		    status1 = DestroyBiTree(T);
			if (status1 == ERROR)
				printf("�����������ڣ�����ʧ�ܣ� \n");
			else
				printf("���������ٳɹ���\n");
			system("pause");
			break;
		case 3:
			if(T->head == NULL)
				printf("�����������ڣ�\n");
			else
				{
					printf("���������ݣ�\n");
					CreateBiTree1(&(T->head->root));
					printf("�����������ɹ���\n");
				}
			system("pause");
			break;
		case 4:
		    if(ClearBiTree(T) == ERROR)
                printf("�����������ڣ����ʧ�ܣ�\n");
            else if(status1 == OK)
                printf("����������ɹ���\n");
			else
				printf("������Ϊ�գ�\n");
			system("pause");
			break;
		case 5:
			status1 = BiTreeEmpty(T);
		    if(status1 == ERROR)
                printf("�����������ڣ��жϳ���\n");
            else if(status1 == TRUE)
                    printf("������Ϊ�գ�\n");
                else
                    printf("��������Ϊ�գ�\n");
			system("pause");
			break;
		case 6:
			if(T->head == NULL)
					printf("�����������ڣ�\n");
			else{
				status1 = BiTreeDepth(T->head->root);
				printf("��ǰ�����������Ϊ%d!\n", status1);
			}
			system("pause");
			break;
		case 7:
			status1 = Root(T);
			if(status1 == ERROR)
				printf("�����������ڣ�����ʧ�ܣ�");
			else if(status1 == OK)
					{
						printf("��ǰ�������ĸ��ڵ�Ϊ��\n");
						printf("name:%s		StudentID:%s	class:%d", T->head->root->student.name, T->head->root->student.StudentID, T->head->root->student.class1);
					}
			else
				printf("��ǰ������Ϊ����! \n");
			system("pause");
			break;
		case 8:
			flag = 1;
		    printf("�����������ͬѧ��ѧ�ţ�");
		    scanf("%s", ID);
		    status1 = Value(T, ID, &e, &flag);
		    if(status1 == ERROR)
                printf("�����������ڣ���������\n");
            else if(status1 == FALSE)
                    printf("��ǰ������Ϊ������\n");
			else if(flag == 1)
					printf("��ǰ������û��ѧ��Ϊ%s��ͬѧ��\n", ID);
				else
					printf("�ҵ��ˣ�\nname:%s	StudentID:%s	class:%d\n", e.student.name, e.student.StudentID, e.student.class1);
			system("pause");
			break;
		case 9:
			flag = 1;
		    printf("���������޸�ͬѧ��ѧ�ţ�");
		    scanf("%s", ID);
		    status1 = Assign(T, ID, &flag);
		    if(status1 == ERROR)
                printf("�����������ڣ�\n");
            else if(flag == 1)
                    printf("��ǰ�������в����ڸ�ѧ�ţ�\n");
			else if(status1 == FALSE)
					printf("��ǰ������Ϊ������\n");
			else printf("�����ɹ���\n");
			system("pause");
			break;
		case 10:
			flag = 1;
		    printf("���������ѯ˫�׵ĺ��ӵ�ѧ�ţ�");
		    scanf("%s", ID);
		    status1 = Parent(T, ID, &e, &flag);
		 	if(status1 == ERROR)
				printf("�����������ڣ�\n");
			else if(status1 == FALSE)
					printf("��ǰ��Ϊ������\n");
			else if(flag == 1)
					printf("��ǰ�������в����ڸ�ѧ�ŵ�ͬѧ��\n");
			else
				printf("��ѯ�ɹ���\nname:%s	ID:%s	class:%d\n", e.student.name, e.student.StudentID, e.student.class1);
			system("pause");
			break;
		case 11:
			flag = 1;
		    printf("�����������ͬѧ��ѧ�ţ�");
		    scanf("%s", ID);
            status1 = LeftChild(T, ID, &e, &flag);
            if(status1 == ERROR)
                printf("�����������ڣ�\n");
            else if(flag == 1)
				printf("��ǰ�����������ڸ�ѧ�ţ�\n");
			else if(!(strcmp(e.student.name, "~")))
					printf("��ǰ�����������ڸ�ѧ�ŵ����ӣ�\n");
			else if(status1 == FALSE)
				printf("��ǰ������Ϊ������\n");
			else
			    printf("�����ɹ���������name:%s\tstudentID:%s\tClass:%d \n", e.student.name, e.student.StudentID, e.student.class1);
			system("pause");
			break;
		case 12:
			flag = 1;
			printf("�����������ͬѧ��ѧ�ţ�");
		    scanf("%s", ID);
            status1 = RightChild(T, ID, &e, &flag);
            if(status1 == ERROR)
                printf("�����������ڣ�\n");
            else if(flag == 1)
					printf("��ǰ�����������ڸ�ѧ�ţ�\n");
			else if(!(strcmp(e.student.name, "~")))
					printf("��ǰ�����������ڸ�ѧ�ŵ��Һ��ӣ�\n");
			else if(status1 == FALSE)
					printf("��ǰ������Ϊ������\n");
			else printf("�����ɹ����Һ�����name:%s\tstudentID:%s\tClass:%d \n", e.student.name, e.student.StudentID, e.student.class1);
			system("pause");
			break;
        case 13:
			flag = 1;
   			printf("�����������ͬѧ��ѧ�ţ�");
		    scanf("%s", ID);
            status1 = LeftSibling(T, ID, &e, &flag);
            if(status1 == ERROR)
                printf("�����������ڣ�\n");
            else if(flag == 1)
					printf("��ǰ�����������ڸýڵ���߸ýڵ�û�����ֵܣ�\n");
			else if(status1 == FALSE)
					printf("��ǰ������Ϊ������\n");
			else if(!strcmp(e.student.name, "~"))
					printf("�ý�㲻�������ֵܣ�\n");
			else
                printf("�����ɹ������ֵ���name:%s\tstudentID:%s\tClass:%d \n", e.student.name, e.student.StudentID, e.student.class1);
			system("pause");
            break;
        case 14:
			flag = 1;
			printf("�����������ͬѧ��ѧ�ţ�");
		    scanf("%s", ID);
            status1 = RightSibling(T, ID, &e, &flag);
             if(status1 == ERROR)
                printf("�����������ڣ�\n");
            else if(flag == 1)
					printf("��ǰ�����������ڸýڵ���߸ýڵ�û�����ֵܣ�\n");
			else if(status1 == FALSE)
					printf("��ǰ������Ϊ������\n");
			else if(!strcmp(e.student.name, "~"))
					printf("�ý�㲻�������ֵܣ�\n");
			else
                printf("�����ɹ������ֵ���name:%s\tstudentID:%s\tClass:%d \n", e.student.name, e.student.StudentID, e.student.class1);
            system("pause");
            break;
		case 15:
			flag = 1;
			printf("������Ҫ�������ѧ�ź���ţ�0��1�ң���");
			scanf("%s%d", e.student.StudentID, &op1);
			status1 = InsertChild(&T, &e, op1, &flag);
			if(status1 == ERROR)
				printf("��ǰ�����������ڣ�\n");
			else if(status1 == FALSE)
					printf("��ǰ������Ϊ������\n");
			else if(flag == 1)
					printf("��ǰ�����������ڸýڵ㣡\n");
			else 	printf("����ɹ���\n");
            system("pause");
            break;
		case 16:
			flag = 1;
			printf("������Ҫɾ������ѧ�ź���ţ�0��1�ң���");
			scanf("%s%d", e.student.StudentID, &op1);
			status1 = DeleteChild(T, &e, op1, &flag);
			if(status1 == ERROR)
				printf("��ǰ�����������ڣ�\n");
			else if(status1 == FALSE)
					printf("��ǰ������Ϊ������\n");
			else if(flag == 1)
					printf("��ǰ�����������ڸýڵ㣡\n");
			else 	printf("ɾ���ɹ���\n");
			system("pause");
			break;
		case 17:
			if(T->head == NULL)
				printf("��ǰ�����������ڣ�\n");
			else{
				PreOrderTraverse(T->head->root);
				printf("�����ɹ���\n");
			}
			system("pause");
			break;
		case 18:
			if(T->head == NULL)
				printf("��ǰ�����������ڣ�\n");
			else{
				InOrderTraverse(T->head->root);
				printf("�����ɹ���\n");
			}
			system("pause");
			break;
		case 19:
			if(T->head == NULL)
				printf("��ǰ�����������ڣ�\n");
			else{
				PostOrderTraverse(T->head->root);
				printf("�����ɹ���\n");
			}
			system("pause");
			break;
		case 20:
			status1 = LevelOrderTraverse(T);
		 	if(status1 == ERROR)
				printf("�����������ڣ�\n");
			else if(status1 == FALSE)
					printf("��ǰ��Ϊ������\n");
			else if(status1 == OK)
					printf("�����ɹ���\n");
			system("pause");
			break;
		case 21:
			printf("������Ҫ������ļ�����");
			scanf("%s", filename);
			if((fp = fopen(filename, "rb")) == NULL)
				printf("Files open error!\n");
			else if(T->head == NULL)
				printf("��ǰ�����������ڣ�\n");
			else
			{
				ReadFiles(&(T->head->root), fp, filename);
				printf("д��ɹ���\n");
			}
			fclose(fp);
			system("pause");
			break;
		case 22:
			printf("������Ҫд����ļ�����");
			scanf("%s", filename);
			if((fp = fopen(filename, "wb")) == NULL)
				printf("Files open error!\n");
			else if(T->head == NULL)
				printf("��ǰ�����������ڣ�\n");
			else
			{
				WriteFiles(T->head->root, fp, filename);
				printf("д��ɹ���\n");
			}
			fclose(fp);
			system("pause");
			break;
		case 0:
			break;
		}//end of switch
	}//end of while
}
//��������InitBiTree
//�β��б�:��ָ��
//�û����룺��
//���ز�����int��״ָ̬ʾ����
//�������ܣ���ʼ����
status InitBiTree(BiTree *T) {
	if (T->head)
		return ERROR;
	T->head = (HNode *)malloc(sizeof(HNode));//��ͷ���Ķ�����
	T->head->root = NULL;
	return OK;
}
//��������DestroyBiTree
//�β��б�:��ָ��
//�û����룺��
//���ز�����int��״ָ̬ʾ����
//�������ܣ��ݻٵ�ǰ��
status DestroyBiTree(BiTree *T) {
	if(T->head == NULL)
		return ERROR;
	free(T->head); //�ͷ�ͷ���
	T->head = NULL;
	return OK;
}
//��������ClearBiTree
//�β��б�:��ָ��
//�û����룺��
//���ز�����int��״ָ̬ʾ����
//�������ܣ���յ�ǰ��
status ClearBiTree(BiTree *T) {
	if(T->head == NULL)
		return ERROR;
	free(T->head->root);	//��ͷ���ָ�����е�rootָ��ָ��Ķ������ͷŵ�
	T->head->root = NULL;
	return OK;
}
//��������BiTreeEmpty
//�β��б�:��ָ��
//�û����룺��
//���ز�����int��״ָ̬ʾ����
//�������ܣ��ж����Ƿ�Ϊ��
status BiTreeEmpty(BiTree *T) {
	if(T->head == NULL)
		return ERROR;
	if(!(T->head->root))	//��ͷ���ָ�����е�rootָ��ָ��գ���Ϊ����
		return OK;
	else return FALSE;
}

//��������ShowMenu
//�β��б�:��
//�û����룺��
//���ز�������
//�������ܣ����Menu
void ShowMenu(void){
        printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. IntiaTable       3.ChooseList\n");
		printf("    	  2. DestroyTable     \n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
        printf("  ��ѡ����Ĳ���[0-3]:");
}
//��������CreateBiTree1
//�β��б�: ָ����ָ���ָ��
//�û����룺��
//���ز�����int��״̬������
//�������ܣ�����������
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
//��������CreateBiTree2
//�β��б�: ���ָ��
//�û����룺��
//���ز�����int��״̬������
//�������ܣ�����������
status CreateBiTree2(BiTNode **T)
{
	ElemType e;
	int i;
	BiTNode *s[maxleng + 1], *root, *t;
	scanf("%s%s%d%d", e.name, e.StudentID, e.class1, i);

}
//��������BiTreeDepth
//�β��б�: ��ָ��
//�û����룺��
//���ز�����int
//�������ܣ����������
int BiTreeDepth(BiTNode *T)
{
	int i, j;
	if(!T) return 0;
	i = BiTreeDepth(T->lchild);
	j = BiTreeDepth(T->rchild);
	return i>j ? (i+1) : (j+1);
}
//��������Root
//�β��б�: ��ָ��
//�û����룺��
//���ز�����int��״̬������
//�������ܣ����ظ�ָ��
status Root(BiTree *T)
{
	if(!(T->head))
		return ERROR;
	if(!(T->head->root))
		return FALSE;
	return OK;
}
//��������Value
//�β��б�: ��ָ�롢Ҫ���ҵ�ѧ��
//�û����룺��
//���ز�����int��״̬������
//�������ܣ����ؽ��ֵ
status Value(BiTree *T, char *ID, BiTNode *e, int *flag)
{
	if(T->head == NULL)
		return ERROR;
	if(T->head->root == NULL)
		return FALSE;
	ChooseOperation(T, ID, 2, e, flag); 	//����
	return OK;
}
//��������Assign
//�β��б�: ��ָ��
//�û����룺Ҫ�޸�ͬѧ�������Ͱ༶
//���ز�����int��״̬������
//�������ܣ��޸Ľ���ֵ
status Assign(BiTree *T, char *ID, int *flag)
{
	BiTNode child;
	if(!(T->head))	return ERROR;
	if(!(T->head->root))	return FALSE;
	ChooseOperation(T, ID, 3, &child, flag);
	return OK;
}
//��������LeftChild
//�β��б�: ��ָ�롢ѧ�š����պ���ָ��
//�û����룺Ҫ�������ӵĽ��
//���ز�����int��״̬������
//�������ܣ����ҽ�������
status LeftChild(BiTree *T, char *ID, BiTNode *lchild, int *flag)
{
	if(!(T->head))	return ERROR;
	if(BiTreeEmpty(T))	return FALSE;
	ChooseOperation(T, ID, 4, lchild, flag);
	return OK;
}
//�β��б�: ��ָ�롢ѧ�š����պ���ָ��
//�û����룺Ҫ�����Һ��ӵĽ��
//���ز�����int��״̬������
//�������ܣ����ҽ����Һ���
status RightChild(BiTree *T, char *ID, BiTNode *rchild, int *flag)
{
	if(!(T->head))	return ERROR;
	if(BiTreeEmpty(T))	return FALSE;
	ChooseOperation(T, ID, 5, rchild, flag);
	return OK;
}
//��������ChooseOperation
//�β��б�: ��ָ�롢Ҫ���ҵ�ѧ�š�int��ѡ��Ĳ�����
//�û����룺��
//���ز�������
//�������ܣ��ǵݹ������������ѡ���ڱ��������еĲ���
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
				if(option == 0) ;//�����
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
									printf("�������ѧ��Ϊ%s��ͬѧ���µ������Ͱ༶:\n");

									if(scanf("%s%d", t->student.name, &(t->student.class1)) == 2)
										printf("�޸ĳɹ���\n");
									printf("��ǰ��ͬѧ����ϢΪ��name:%s StudentID:%s Class:%d",t->student.name, t->student.StudentID, t->student.class1);
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
//��������Parent
//�β��б�: ��ָ�롢char���飨ѧ�ţ�
//�û����룺Ҫ���ҵ�ѧ��
//���ز�����int��״̬������
//�������ܣ�Ѱ�Һ��ӵ�˫��
status Parent(BiTree *T, char *ID, BiTNode *e, int *flag)
{
	if(T->head == NULL)	return ERROR;
	if(T->head->root == NULL)	return FALSE;
	ChooseOperation1(T, e, ID, 1, flag);
	return OK;
}
//��������LeftSibling
//�β��б�: ��ָ�롢���ѧ��
//�û����룺ѧ��
//���ز�����int��״̬������
//�������ܣ��ǵݹ������������ѡ���ڱ��������еĲ���
status LeftSibling(BiTree *T, char *ID, BiTNode *e, int *flag)
{
	if(T->head == NULL)	return ERROR;
	if(T->head->root == NULL)	return FALSE;
	ChooseOperation1(T, e, ID, 2, flag);
	return OK;
}
//��������RightSibling
//�β��б�: ��ָ�롢���ѧ��
//�û����룺ѧ��
//���ز�����int��״̬������
//�������ܣ��ǵݹ������������ѡ���ڱ��������еĲ���
status RightSibling(BiTree *T, char *ID, BiTNode *e, int* flag)
{
	if(T->head == NULL)	return ERROR;
	if(T->head->root == NULL)	return FALSE;
	ChooseOperation1(T, e, ID, 3, flag);
	return OK;
}
//��������ChooseOperation1
//�β��б�: ��ָ�롢���صĽ�㡢int��ѡ��Ĳ�����
//�û����룺��
//���ز�������
//�������ܣ��ǵݹ������������ѡ���ڱ��������еĲ���
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
				if(t->lchild == NULL)	;//�����
				else if(!strcmp(t->lchild->student.StudentID, ID))
					{
						*e = *t;
						*flag = 0;
						break;
					}
				if(t->rchild == NULL)	;//�����
				else if(!strcmp(t->rchild->student.StudentID, ID))
					{
						*e = *t;
						*flag = 0;
						break;
					}
			}
			else if(option == 2)
			{
				
				if(t->rchild == NULL)	;//�����
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
				if(t->lchild == NULL)	;//�����
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
//��������PreOrderTraverse
//�β��б�: ��ָ��
//�û����룺��
//���ز�������
//�������ܣ�ǰ�����������
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
//��������InOrderTraverse
//�β��б�: ��ָ��
//�û����룺��
//���ز�������
//�������ܣ��������������
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
//��������PostOrderTraverse
//�β��б�: ��ָ��
//�û����룺��
//���ز�������
//�������ܣ��������������
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
//��������WriteFiles
//�β��б�: ���������ļ�ָ�룬�ַ������ļ������֣�
//�û����룺Ҫд��������ļ�������
//���ز�������
//�������ܣ���������������Ԫ��д��������ļ�
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
//��������ReadFiles
//�β��б�: ���������ļ�ָ�룬�ַ������ļ������֣�
//�û����룺Ҫд��������ļ�������
//���ز�������
//�������ܣ���������������Ԫ�ض��뵽�������ļ�
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
//��������InsertChild
//�β��б�: �����������ָ�룬intѡ���intָ��
//�û����룺���������ѡ�����λ��
//���ز�����int��״̬������
//�������ܣ�ѡ���ԵĲ�������
status InsertChild(BiTree **T, BiTNode *p, int LR, int *flag)
{
	if((*T)->head == NULL)
		return ERROR;
	else if((*T)->head->root ==NULL)
			return FALSE;
	BiTNode *s[maxleng+1], *t = (*T)->head->root;
	BiTNode *oNode, *In_root;//In_root ָ��Ҫ�������ĸ��� oNode��ָ��Ҫ�޸ĵĽ��
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
				printf("������������Ϣ��\n");
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
//��������Deletechild
//�β��б�: �����������ָ�룬intѡ���intָ��
//�û����룺Ҫд��������ļ�������
//���ز�������
//�������ܣ�ѡ���ԵĲ�������
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
//��������LevelOrderTraverse
//�β��б�: ������ָ��
//�û����룺��
//���ز�����int(״̬����)
//�������ܣ��������������
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