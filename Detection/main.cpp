#define _CRT_SECURE_NO_WARNINGS 1
#include"LR.h"

size_t trainSize = (size_t)(SIZE * TRAIN_RATE);
size_t testSize = (size_t)(SIZE - trainSize);

int main() {
	Module* Modules, * train, * test;
	Modules = (Module*)malloc(SIZE * sizeof(Module));
	train = (Module*)malloc(SIZE * sizeof(Module));
	test = (Module*)malloc(SIZE * sizeof(Module));

	if (!readTxt(Modules)) {
		free(Modules);
		return 0;
	}
	if (Modules!=NULL)
		for (int i = 0; i < 17001; i++) {
			printf("%d ", i);
			for (int j = 0; j < 38; j++) {
				printf("%.2lf ", Modules[i].feature[j]);
			}
			printf("%d\n", Modules[i].defective);
		}
	preProcess(Modules);
	splitData(Modules, train, test);
	//predict(train, test);
	free(Modules);
	free(train);
	free(test);
}