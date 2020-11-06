#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int dataCount = 0;		
int featureCount = 0;	
int numberK = 0;			
int scanfCount = 0;		

typedef struct Node {
	float* featureArray;
	struct Node* next;
} Node;

typedef  struct Stack {
	Node* top;
} Stack;

Stack* makeStack()
{
	Stack* stack = malloc(sizeof(stack));
	stack->top = NULL;
}

void pushAfterFirst(Stack* stack, Node* node)
{
	Node* firstNode = stack->top;
	node->next = firstNode->next;
	firstNode->next = node;
}

void showStack(Stack* stack)
{
	Node* currentNode = stack->top;
	int index = 0;
	while (currentNode != NULL)
	{
		printf("%3d\t", index++);
		for (int i = 0; i < featureCount; i++)
		{
			printf("%f\t", currentNode->featureArray[i]);
		}
		printf("\n");
		currentNode = currentNode->next;
	}
}

void showStackArray(Stack** stackArray)
{
	printf("#################################\n");
	for (int i = 0; i < numberK; i++)
	{
		printf("<<<<<<<<<< %d 번째 원소 >>>>>>>>>>\n", i);
		showStack(stackArray[i]);
	}
	printf("#################################\n");

}

float nodeDistance(Node* firstNode, Node* testNode)
{
	float sum = 0, deviation = 0;
	for (int i = 0; i < featureCount; i++)
	{
		deviation = (firstNode->featureArray[i]) - (testNode->featureArray[i]);
		deviation *= deviation;
		sum += deviation;
	}
	return sum;
}

Stack** makeSampleArray()
{
	FILE* fileInput = fopen("input.txt", "r");
	fscanf(fileInput, "%d %d %d", &dataCount, & featureCount, &numberK);
	//printf("dataCount: %d\nfeatureCount: %d\nnumberK: %d", dataCount, featureCount, numberK);

	Stack** sampleArray = malloc(numberK * sizeof(Stack*));

	for (int i = 0; i < numberK; i++)
	{
		sampleArray[i] = makeStack();
		Node* firstNode = malloc(sizeof(Node));
		firstNode->featureArray = malloc(featureCount * sizeof(float));
		for (int j = 0; j < featureCount; j++) 
		{
			firstNode->featureArray[j] = 1/(float)rand()*1000;
		}
		firstNode->next = sampleArray[i]->top;
		sampleArray[i]->top = firstNode;
	}

	for (int i = 0; i < dataCount; i++)
	{
		int shortestIndex;
		float shortestDistance = 3.4028234664e+38;

		Node* dataNode = malloc(sizeof(Node));
		dataNode->featureArray = malloc(featureCount * sizeof(float));
		for (int j = 0; j < featureCount; j++)
		{
			fscanf(fileInput, "%f", &(dataNode->featureArray[j]));
		}
		
		shortestIndex = 0;
		for (int i = 0; i < numberK; i++)
		{
			float tempDistance = nodeDistance(sampleArray[i]->top, dataNode);
			if (shortestDistance > tempDistance)
			{
				shortestDistance = tempDistance;
				shortestIndex = i;
			}
		}
		pushAfterFirst(sampleArray[shortestIndex], dataNode);
	}
	return sampleArray;
}


void main(void)
{
	srand(1000);
	Stack** sampleArray = makeSampleArray();
	showStackArray(sampleArray);
}
