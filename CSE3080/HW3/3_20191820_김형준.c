#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row, column, value;
} Term;
#define MAX_TERMS 1024
void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);

int main() {
    Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];
    
    FILE* fp = fopen("A.txt", "r");
    readMatrix(fp, a);
    fclose(fp);
	
    fp = fopen("B.txt", "r");
    readMatrix(fp, b);
    fclose(fp);
    
    matrixAdd(a, b, c);
    printMatrix(c);
    return 0;
}

void matrixAdd(Term a[], Term b[], Term c[])
{
	int Aptr = 1, Bptr = 1, voidptr = 1, count = 0, sum;
	
	// matrix A,B 덧셈
	while (Aptr <= a[0].value && Bptr <= b[0].value)
	{
		if (a[Aptr].row > b[Bptr].row) 
		{
			// Cij = Bij
			c[voidptr].row = b[Bptr].row;
			c[voidptr].column = b[Bptr].column;
			c[voidptr++].value = b[Bptr].value;
			count++;
			Bptr++;
		}
		else if (a[Aptr].row < b[Bptr].row)
		{
			// Cij = Aij
			c[voidptr].row = a[Aptr].row;
			c[voidptr].column = a[Aptr].column;
			c[voidptr++].value = a[Aptr].value;
			count++;
			Aptr++;
		}
		else // a[Aptr].row == b[Bptr].row
		{
			if (a[Aptr].column > b[Bptr].column)
			{
				// Cij = Bij
				c[voidptr].row = b[Bptr].row;
				c[voidptr].column = b[Bptr].column;
				c[voidptr++].value = b[Bptr].value;
				count++;
				Bptr++;
			}
			else if (a[Aptr].column < b[Bptr].column)
			{
				// Cij = Aij
				c[voidptr].row = a[Aptr].row;
				c[voidptr].column = a[Aptr].column;
				c[voidptr++].value = a[Aptr].value;
				count++;
				Aptr++;
			}
			else // a[Aptr].col == b[Bptr].col
			{
				// Cij = Aij+Bij
				sum = a[Aptr].value + b[Bptr].value;
				if (sum != 0)
				{		
					c[voidptr].row = b[Bptr].row; // a[Aptr].row = b[Bptr].row
					c[voidptr].column = b[Bptr].column; // a[Aptr].col = b[Bptr].col
					c[voidptr++].value = sum;
					count++;
				}
				Aptr++;
				Bptr++;
			}
		}
	}

	// matrix A,B중 남은 부분 처리
	while (Aptr <= a[0].value)
	{
		// Cij = Aij
		c[voidptr].row = a[Aptr].row;
		c[voidptr].column = a[Aptr].column;
		c[voidptr++].value = a[Aptr].value;
		count++;
		Aptr++;
	}
	while (Bptr <= b[0].value)
	{
		// Cij = Bij
		c[voidptr].row = b[Bptr].row;
		c[voidptr].column = b[Bptr].column;
		c[voidptr++].value = b[Bptr].value;
		count++;
		Bptr++;
	}

	// fill matrix header
	c[0].row = a[0].row; // a[0].row = b[0].row
	c[0].column = a[0].column; // a[0].col = b[0].col
	c[0].value = count;
}

void readMatrix(FILE* fp, Term a[])
{
	if (fp == 0) // 파일 로드 실패시 예외 처리
		exit(1);

	int row = 0, col = 0, val, count = 0, voidptr = 1;
	
	fscanf(fp, "%d %d", &a[0].row, &a[0].column);

	while (1)
	{
		if (fscanf(fp, "%d", &val) == -1)
			break;
		if (voidptr >= MAX_TERMS)
		{
			fprintf(stderr, "Too many terms in the matrix");
			exit(1);
		}

		if (val != 0)
		{
			a[voidptr].row = row;
			a[voidptr].column = col;
			a[voidptr++].value = val;
			count++;
		}
		col++;
		if (col >= a[0].column)
		{
			col = 0;
			row++;
		}
	}    

	a[0].value = count;
}

void printMatrix(Term a[])
{
    int num = a[0].value, n;
    
    for (n = 0; n <= num; n++)
        printf("%d %d %d\n", a[n].row, a[n].column, a[n].value);
}

