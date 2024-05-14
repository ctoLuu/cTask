#define _CRT_SECURE_NO_WARNINGS 1
#include"LR.h"

size_t trainSize = (size_t)(SIZE * TRAIN_RATE);
size_t testSize = (size_t)(SIZE - trainSize);

int main() {
	Module* Modules, * trainData, * testData;
	Modules = (Module*)malloc(SIZE * sizeof(Module));
	trainData = (Module*)malloc(SIZE * sizeof(Module));
	testData = (Module*)malloc(SIZE * sizeof(Module));

	if (!readTxt(Modules)) {
		free(Modules);
		return 0;
	}
	/*if (Modules != NULL) {
		for (int i = 0; i < 17001; i++) {
			printf("%d ", i);
			for (int j = 0; j < 38; j++) {
				printf("%.2lf ", Modules[i].feature[j]);
			}
			printf("%d\n", Modules[i].defective);
		}
	}*/

	preProcess(Modules);
	splitData(Modules, trainData, testData);
	free(Modules);
	
	double Weight[38] = { 0 }, Bias = 0, lambda = 0.01;
	train(trainData, Weight, Bias, lambda);
	predict(testData, Weight, Bias);
	free(trainData);
	free(testData);
}