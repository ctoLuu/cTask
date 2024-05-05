#define _CRT_SECURE_NO_WARNINGS 1
#include "KNN.h"

size_t trainSize = (size_t)(SIZE * TRAIN_RATE);
size_t testSize = (size_t)(SIZE * (1 - TRAIN_RATE));

int main()
{
	Iris* irises, * train;
	irises = (Iris*)malloc(SIZE * sizeof(Iris));
	train = (Iris*)malloc(trainSize * sizeof(Iris));
	Iris test[30];

	if (!readTxt(irises))
		return 0;
	preProcess(irises);
	splitData(irises, train, test);
	// ÊÍ·ÅÄÚ´æ
	free(irises);
	predict(train, test, 100);
	free(train);
}