#include <stdio.h>
#include <stdlib.h>

typedef struct vnode* nodeptr;
typedef struct vnode{
	int vertex;
	nodeptr link;
} node;
nodeptr* graph;
int* visited;

typedef struct stack* snodeptr;
typedef struct stack { 
	int cur; 
	int dst;
	snodeptr link;
}snode;
void Push(snodeptr* top, int cur, int dst);
void Pop(snodeptr* top, int* cur, int* dst);
void addEdge(int src, int dst, char dir);

int main(void)
{

	FILE* fptr = fopen("graph.txt", "r");

	if (fptr == 0) // 파일 로드 실패시 예외 처리
		exit(1);

	int n, i;
	fscanf(fptr, "%d", &n); // vertex number 1~n

	graph = (nodeptr*)malloc(sizeof(nodeptr) * (n + 1));
	visited = (int*)malloc(sizeof(int) * (n + 1));
	for (i = 1; i <= n; i++)
	{
		visited[i] = 0;
		graph[i] = NULL;
	}

	int src, dst; // src -> dst
	char dir;
	while (1)
	{
		if (fscanf(fptr, "%d %d %c", &src, &dst, &dir) == -1)
			break;

		addEdge(src, dst, dir);
	}

	fclose(fptr);

	snodeptr top = NULL;
	int input, cur, count, dstcount;
	nodeptr curptr;
	do {
		scanf("%d", &input);
		
		if (input >= 1 && input <= n)
		{
			for (i = 1; i <= n; i++)
				visited[i] = 0;
			printf("%d ", input);
			visited[input] = 1;
			count = 0;

			Push(&top, input, 0);
			while (top)
			{
				Pop(&top, &cur, &dstcount);
				for (count = 0, curptr = graph[cur]; count < dstcount; count++, curptr = curptr->link) {}

				while(curptr)
				{
					if (visited[curptr->vertex] == 0)
					{
						Push(&top, cur, count + 1);
						cur = curptr->vertex;
						curptr = graph[cur];
						
						printf("%d ", cur);
						visited[cur] = 1;
						count = 0;
					}
					else
					{	
						curptr = curptr->link;
						count++;
					}
				}
			}
			printf("\n");
		}
	} while (input != -1);
	return 0;
}


void Push(snodeptr* top, int cur, int dst)
{
	snodeptr temp = (snodeptr)malloc(sizeof(snode));
	if (!temp) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	temp->cur = cur;
	temp->dst = dst;
	temp->link = *top;
	*top = temp;
}

void Pop(snodeptr* top, int* cur, int* dst)
{
	snodeptr temp = *top;
	if (!temp) {
		fprintf(stderr, "The stack is empty\n");
		exit(1);
	}
	*cur = temp->cur;
	*dst = temp->dst;
	*top = temp->link;
	free(temp);
}

void addEdge(int src, int dst, char dir) // sort + insert
{
	if (dir == 'u')
	{
		addEdge(src, dst, 'd');
		addEdge(dst, src, 'd');
	}
	else // src -> dst
	{
		nodeptr temp = NULL, ptr = graph[src];
		if (!ptr)
		{
			temp = (node*)malloc(sizeof(node));
			temp->link = NULL;
			temp->vertex = dst;
			graph[src] = temp;
		}
		else
		{
			for (; ptr && dst > ptr->vertex; ptr = ptr->link) // > : 오름차순 
				temp = ptr;
			if (temp == NULL) // dst > graph[src]->vertex
			{
				temp = (node*)malloc(sizeof(node));
				temp->link = graph[src];
				temp->vertex = dst;
				graph[src] = temp;
			}
			else
			{
				ptr = temp;
				temp = (node*)malloc(sizeof(node));
				temp->link = ptr->link;
				temp->vertex = dst;
				ptr->link = temp;
			}	
		}
	}
}