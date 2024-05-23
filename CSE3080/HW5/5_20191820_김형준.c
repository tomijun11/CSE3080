#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100
typedef struct treeNode* treePtr;
typedef struct treeNode {
	treePtr lchild;
	int data;
	treePtr rchild;
};
void inorder(treePtr);
void preorder(treePtr);
void insert(treePtr*, int);
treePtr modifiedSearch(treePtr, int);
void readfile(const char* FileName, int Arr[], int* n);

void main()
{
	int i, n, A[MAX_TERMS];
	treePtr tree = NULL;

	readfile("input.txt", A, &n);

	for (i = 0; i < n; i++)
		insert(&tree, A[i]);

	inorder(tree); printf("\n");
	preorder(tree); printf("\n");
	return;
}

void insert(treePtr* node, int num) 
{
	treePtr ptr, temp = modifiedSearch(*node, num);
	if (temp || !(*node)) {
		ptr = (treePtr)malloc(sizeof(node));
		if (!ptr) {
			fprintf(stderr, "The memory is full");
			exit(1);
		}
		ptr->data = num;
		ptr->lchild = ptr->rchild = NULL;
		if (*node)
			if (num < temp->data)
				temp->lchild = ptr;
			else temp->rchild = ptr;
		else *node = ptr;
	}
}

treePtr modifiedSearch(treePtr root, int key)
{
	treePtr temp = root;
	if (!root) 
		return NULL;

	while (temp)
	{
		if (key == temp->data) return NULL; // found
		if (key < temp->data)
		{
			if (!temp->lchild)
				return temp;  // not found -> return ptr
			temp = temp->lchild;
		}
		else
		{
			if (!temp->rchild)
				return temp;  // not found -> return ptr
			temp = temp->rchild;
		}
	}
	return NULL;
}

void preorder(treePtr ptr) // VLR
{
	if (ptr) {
		printf("%d ", ptr->data);
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}

void inorder(treePtr ptr) // LVR
{
	if (ptr) {
		inorder(ptr->lchild);
		printf("%d ", ptr->data);
		inorder(ptr->rchild);
	}
}

void readfile(const char* FileName, int Arr[], int* n)
{
	FILE* fptr = fopen(FileName, "r");

	if (fptr == 0) // 파일 로드 실패시 예외 처리
		exit(1);

	int i;
	fscanf(fptr, "%d", n);
	if (*n > MAX_TERMS)
	{
		fprintf(stderr, "Too many terms in the file");
		exit(1);
	}
	for (i = 0; i < *n; i++)
		fscanf(fptr, "%d", &Arr[i]);
		
	fclose(fptr);
}
