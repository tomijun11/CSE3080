#include <stdio.h>
#include <stdlib.h>

typedef struct BSTree* Treeptr;
typedef struct BSTree {
	Treeptr lchild;
	int data;
	Treeptr rchild;
}Treenode;

typedef struct LChildlist* Llistptr;
typedef struct LChildlist {
	Treeptr node;
	Llistptr link;
}Llistnode;

void erase(Llistptr lptr);
void attach(Llistptr* lptr, Treeptr addr);
Treeptr findptr(Llistptr lptr, int key, Treeptr newaddr);
void preorder(Treeptr tptr, int level);

int main(void) 
{
	int input, ret;
	Treeptr CurNode, NextNode, tptr = NULL;
	Llistptr lptr = NULL;

	scanf("%d", &input);
	ret = getc(stdin);
	CurNode = (Treeptr)malloc(sizeof(Treenode));
	CurNode->data = input;
	CurNode->lchild = NULL;
	CurNode->rchild = NULL;

	if (!(ret == '\n' || ret == EOF))
	{
		while (1) // input next node
		{
			scanf("%d", &input);
			ret = getc(stdin);

			NextNode = (Treeptr)malloc(sizeof(Treenode));
			NextNode->data = input;
			NextNode->lchild = NULL;
			NextNode->rchild = NULL;

			if (NextNode->data > CurNode->data) // Cur = LChild
			{
				NextNode->lchild = CurNode;
				attach(&lptr, NextNode);
			}
			else
			{
				NextNode->rchild = CurNode;
				if (lptr != NULL)
				{
					Treeptr temp = findptr(lptr, NextNode->data, NextNode);
					if (temp)
					{
						NextNode->lchild = temp->lchild;
						temp->lchild = NULL;
					}
				}
			}

			if ((ret == '\n' || ret == EOF))
				break;

			CurNode = NextNode;
		}
	}
	erase(lptr); 
	lptr = NULL;
	tptr = NextNode;

	preorder(tptr, 1);
	printf("\n");

	return 0;
}

void preorder(Treeptr tptr, int level)
{
	if (tptr) 
	{
		printf("%d(%d) ", tptr->data, level);
		preorder(tptr->lchild, level+1);
		preorder(tptr->rchild, level+1);
	}
}


Treeptr findptr(Llistptr lptr, int key, Treeptr newaddr)
{
	if (lptr)
	{
		for (; lptr; lptr = lptr->link)
		{
			if (lptr->node->lchild->data < key) // found
			{
				Treeptr temp = lptr->node;
				lptr->node = newaddr;
				return temp;
			}
		}
	}
	return NULL;
}

void attach(Llistptr* lptr, Treeptr addr)
{
	Llistptr temp = (Llistptr)malloc(sizeof(Llistnode));
	if (!temp)
	{
		printf("메모리가 부족합니다.\n");
		exit(1);
	}
	temp->node = addr;

	if (*lptr)
	{
		temp->link = *lptr;
		*lptr = temp;
	}
	else // *lptr == NULL
	{
		temp->link = NULL;
		*lptr = temp;
	}
}

void erase(Llistptr lptr)
{
	for (; lptr;)
	{
		Llistptr temp = lptr;
		lptr = lptr->link;
		free(temp);
	}
}