#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Insertion_sort(int*,int);

int main(void)
{
	clock_t PStart = clock(); // 프로그램 총 실행시간

	// 1. 입력데이터와 정렬 결과를 출력
	FILE* fptr;
	fopen_s(&fptr, "lab1.data", "r");

	if (fptr == 0) // lab1.data 로드 실패시 예외 처리
		return -1;

	int i, Temp, Count = 0;
	int* Data = (int*)malloc(Count * sizeof(int));

	while (1)
	{
		fscanf_s(fptr, "%d", &Temp);
		if (feof(fptr) != 0)
			break;
		Data = realloc(Data, (Count + 1) * sizeof(int));
		Data[Count] = Temp;
		Count++;
	}
	
	printf("Input :");
	for (i = 0; i < Count; i++)
		printf(" %d", Data[i]);
	printf("\n");

	Insertion_sort(Data, Count);

	printf("Sorted :");
	for (i = 0; i < Count; i++)
		printf(" %d", Data[i]);
	printf("\n");

	free(Data);
	fclose(fptr);

	// 2. 프로그램 실행시간을 출력
	printf("    n   repetitions time\n");

	int repetitions, j;
	clock_t start;
	double duration, t;
	for (i = 0; i <= 100; i += 10)
	{
		repetitions = 0;
		Data = (int*)malloc(i * sizeof(int));
		start = clock();
		do 
		{
			for (j = 0; j < i; j++)
				Data[j] = i - j;
			Insertion_sort(Data, i);
			repetitions++;
		} while (clock() - start < 10);
		duration = (double)(clock() - start);
		free(Data);
		t = duration / repetitions;
		printf("%6d   %8d   %.6lf\n", i, repetitions, t);
	}

	printf("[Finished in %.1lfs]\n",((double)(clock()-PStart))/CLOCKS_PER_SEC);
	return 0;
}

void Insertion_sort(int* Arr, int N)
{
	int i, j, key;
	for (i = 1; i < N; i++)
	{
		key = Arr[i];
		for (j = i - 1; j >= 0 && key <= Arr[j] ; j--)
			Arr[j + 1] = Arr[j];
		Arr[j+1] = key;
	}
}

