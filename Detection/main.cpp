#define _CRT_SECURE_NO_WARNINGS 1
#include"LR.h"

size_t trainSize = (size_t)(SIZE * TRAIN_RATE);
size_t testSize = (size_t)(SIZE - trainSize);

int main() {
	Module* Modules, * trainData, * testData;
	Modules = (Module*)malloc(SIZE * sizeof(Module));
	trainData = (Module*)malloc(SIZE * sizeof(Module));
	testData = (Module*)malloc(SIZE * sizeof(Module));
	double** features;
	features = (double**)malloc(K * sizeof(double*)); // 分配行指针
	for (int i = 0; i < K; i++) {
		features[i] = (double*)malloc(SIZE * sizeof(double)); // 为每一行分配内存
	}
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

	preProcess(Modules, features);
	splitData(Modules, trainData, testData);
	free(Modules);
	//double Weight[38] = { 0 }, Bias = 0;
	double Weight[K] = { 0 }, Bias = 0;
	train(trainData, Weight, Bias, features);
	predict(testData, Weight, Bias, features);
	free(trainData);
	free(testData);
}