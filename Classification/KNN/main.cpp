#define _CRT_SECURE_NO_WARNINGS 1
#include "KNN.h"

size_t trainSize = (size_t)(SIZE * TRAIN_RATE);
size_t testSize = (size_t)(SIZE * (1 - TRAIN_RATE));

int main()
{
	Iris* irises, * train, * test;
	irises = (Iris*)malloc(SIZE * sizeof(Iris));
	train = (Iris*)malloc(trainSize * sizeof(Iris));
	test = (Iris*)malloc(testSize * sizeof(Iris));

	if (!readTxt(irises))
		return 0;
	preProcess(irises);
	splitData(irises, train, test);
	free(irises);
	predict(train, test);
}