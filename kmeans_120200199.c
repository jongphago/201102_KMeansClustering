#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int dataCount = 0;
int featureCount = 0;
int K = 0;
int scanfCount = 0;

void scanfException(int scanfReturn, int scanfAnswer)
{
	if (scanfReturn != scanfAnswer)
	{
		printf("SCANF ERROR iS OCCURED.");
		exit(-1);
	}
	return;
}
void dataToArray(FILE** inputFile, float*** dataArray);
void printFloat2DArray(float** dataArray, int firstIndexCount, int secondIndexCount);



void main(void) {
	FILE* inputFile;
	float** dataArray;

	dataToArray(&inputFile, &dataArray);
	//printf("%d %d %d\n", dataCount, featureCount, K);
	//printFloat2DArray(dataArray, dataCount, featureCount);



	return;
}

/*
함수 [dataToArray]는 "input.txt" 파일을 읽어서 점 데이터를
float형 2차원 배열(변수명:dataArray)에 저장합니다.
*/
void dataToArray(FILE** inputFile, float*** dataArray) {
	*inputFile = fopen("input.txt", "r");
	if ((*inputFile) == NULL)
	{
		printf("File Open Error");
		exit(-1);
	}
	scanfCount = fscanf(*inputFile, "%d %d %d", &dataCount, &featureCount, &K);
	if (scanfCount != 3)
	{
		printf("fscanf Error");
		exit(-1);
	}

	*dataArray = malloc(dataCount * sizeof(float*));
	for (int i = 0; i < dataCount; i++)
	{
		(*dataArray)[i] = malloc(featureCount * sizeof(float));
		if ((*dataArray)[i] == NULL)
		{
			printf("MEMORY ALLOCATION ERROR.");
			exit(-1);
		}
		for (int j = 0; j < featureCount; j++)
		{
			scanfCount = fscanf(*inputFile, "%f", &((*dataArray)[i][j]));
			if (scanfCount != 1) {
				exit(-1);
			}
			scanfException(scanfCount, 1);
		}
	}
}

/*
함수 [printFloat2DArray]는 float type의 2차원 배열을 받아서 
index:		data1		data2		...		dataK 형태로 출력합니다.
행의 수는 firstIndexCount, 열의 수는 secondIndexCount와 같습니다.
*/
void printFloat2DArray(float** dataArray, int firstIndexCount, int secondIndexCount) {
	for (int i = 0; i < firstIndexCount; i++)
	{
		printf("%3d:\t", i);
		for (int j = 0; j < secondIndexCount; j++)
		{
			printf("%.3f\t", dataArray[i][j]);
		}
		printf("\n");
	}
}