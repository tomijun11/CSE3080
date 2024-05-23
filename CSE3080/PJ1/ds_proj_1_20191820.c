#include <stdio.h>
#include <stdlib.h>

static int Strptr = 0;
enum paren { L2 = -1, L3 = -2, R2 = -3, R3 = -4 }; // 연산중인 수는 음수가 나올 수 없다.

typedef struct stack* nodeptr;
typedef struct stack{
	int item;
	nodeptr link;
}node;

void Erase(nodeptr top);
void Push(nodeptr* top, int item);
int Pop(nodeptr* top);
int GetToken(int* Token, char Str[]);

int main(void)
{
	char Input[50] = {0};
	int CurToken, Sum, Check, Ret = 0, err = 0;
	nodeptr top = NULL;

	scanf("%s", Input); // Input String
	
	while (!GetToken(&CurToken, Input))
	{
		switch (CurToken)
		{
		case L2: // '('
		case L3: // '['
			Push(&top, CurToken); break;
		case R2: // ')'
			for (Sum = 0, Check = 0; top != NULL && top->item >= 0;)
			{
				int temp = Pop(&top);
				Sum += temp;
				Check = 1;
			}
			if (top == NULL) { err = 1; goto ERR; }
			else if (top->item == L2)
			{
				if (Check == 0)
				{
					Pop(&top); // remove L2
					Push(&top, 2);
				}
				else
				{
					Pop(&top); // remove L2
					Push(&top, Sum * 2);
				}
			}
			else { err = 1; goto ERR; } // top->item == L3
			break;
		case R3: // ']'
			for (Sum = 0, Check = 0; top != NULL && top->item >= 0;)
			{
				int temp = Pop(&top);
				Sum += temp;
				Check = 1;
			}
			if (top == NULL) { err = 1; goto ERR; }
			else if (top->item == L3)
			{
				if (Check == 0)
				{
					Pop(&top); // remove L3
					Push(&top, 3);
				}
				else
				{
					Pop(&top); // remove L3
					Push(&top, Sum * 3);
				}
			}
			else { err = 1; goto ERR; } // top->item == L2
			break;
		}
	}

	if(top == NULL) { err = 1; goto ERR; } // 스택에 Number들만 존재해야함
	else
	{
		for (Ret = 0; top != NULL;)
		{
			if (top->item < 0) { err = 1; goto ERR; }
			int temp = Pop(&top);
			Ret += temp;
		}
	}

ERR:
	if (err == 1) Ret = 0; // 잘못된 문장이면 0을 리턴함
	printf("%d\n", Ret);
	Erase(top); top = NULL;
	return 0;
}

void Erase(nodeptr top)
{
	for (; top != NULL;)
	{
		nodeptr temp = top;
		top = top->link;
		free(temp);
	}
}

void Push(nodeptr* top, int item)
{
	nodeptr temp = (nodeptr)malloc(sizeof(node));
	if (!temp) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	temp->item = item;
	temp->link = *top;
	*top = temp;
}

int Pop(nodeptr* top)
{
	nodeptr temp = *top;
	int item;
	if (!temp) {
		fprintf(stderr, "The stack is empty\n");
		exit(1);
	}
	item = temp->item;
	*top = temp->link;
	free(temp);
	return item;
}

int GetToken(int* Token, char Str[])
{
	char letter = Str[Strptr++];
	int eos = 0;
	switch (letter)
	{
	case '(':
		*Token = L2; break;
	case '[':
		*Token = L3; break;
	case ')':
		*Token = R2; break;
	case ']':
		*Token = R3; break;
	default: // eos 도달시 check
		eos = 1;
	}
	return eos;
}
