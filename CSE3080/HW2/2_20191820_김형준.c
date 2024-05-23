#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TERMS 100
typedef struct {
	int coef;
	int expon;
} Poly;
Poly terms[MAX_TERMS];
int avail = 0;

int COMPARE(int a, int b);
void attach(int c, int e);
void padd(int starta, int finisha, int startb, int finishb, int* startd, int* finishd);
void readPoly(const char* FileName, int* starta, int* finisha);
void printPoly(int starta, int finisha);

int main(void)
{
	clock_t PStart = clock(); // 프로그램 총 실행시간
	int startA, startB, startC, startD, startRet, finishA, finishB, finishC, finishD, finishRet;
	
	readPoly("A.txt", &startA, &finishA);
	readPoly("B.txt", &startB, &finishB);
	readPoly("C.txt", &startC, &finishC);
	
	padd(startA, finishA, startB, finishB, &startD, &finishD);
	padd(startD, finishD, startC, finishC, &startRet, &finishRet);

	printPoly(startRet, finishRet);

	printf("[Finished in %.1lfs]\n", ((double)(clock() - PStart)) / CLOCKS_PER_SEC);
	return 0;
}

int COMPARE(int a, int b)
{
	if (a < b)
		return -1;
	else if (a == b)
		return 0;
	else
		return 1;
}

void attach(int c, int e)
{
	if (avail < MAX_TERMS)
	{
		terms[avail].coef = c;
		terms[avail].expon = e;
		avail++;
	}
	else
	{
		fprintf(stderr, "Too many terms in the polynomial");
		exit(1);
	}
}

void readPoly(const char* FileName,int* starta, int* finisha) 
{
	FILE* fptr;
	fopen_s(&fptr, FileName, "r");

	if (fptr == 0) // 파일 로드 실패시 예외 처리
		exit(1);

	int c;
	int e;
	*starta = avail;
	*finisha = avail - 1;
	while (1)
	{	
		if (fscanf_s(fptr, "%d %d", &c, &e) == -1)
			break;
		if (avail >= MAX_TERMS)
		{
			fprintf(stderr, "Too many terms in the polynomial");
			exit(1);
		}
		terms[avail].coef = c;
		terms[avail].expon = e;
		(*finisha)++;
		avail++;
	}

	fclose(fptr);
}

void printPoly(int starta, int finisha)
{
	int i;
	for (i = starta; i <= finisha; i++)
	{
		printf("(%d,%d)", terms[i].coef, terms[i].expon);
		if (i != finisha)
			printf(", ");
	}
	printf("\n");
}

void padd(int starta, int finisha, int startb, int finishb, int* startd, int* finishd)
{
	int coefficient;
	*startd = avail;
	while (starta <= finisha && startb <= finishb)
		switch (COMPARE(terms[starta].expon, terms[startb].expon)) {
		case -1:
			attach(terms[startb].coef, terms[startb].expon);
			startb++;
			break;
		case 0: 
			coefficient = terms[starta].coef + terms[startb].coef;
			if (coefficient)
				attach(coefficient, terms[starta].expon);
			starta++; startb++;
			break;
		case 1:
			attach(terms[starta].coef, terms[starta].expon);
			starta++;
		}

	for (; starta <= finisha; starta++)
		attach(terms[starta].coef, terms[starta].expon);

	for (; startb <= finishb; startb++)
		attach(terms[startb].coef, terms[startb].expon);
	*finishd = avail - 1;
}