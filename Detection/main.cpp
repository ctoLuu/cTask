#define _CRT_SECURE_NO_WARNINGS 1
#include"LR.h"

size_t trainSize = (size_t)(SIZE - SIZE / FOLD);     //训练集数据数
size_t testSize = (size_t)(SIZE - trainSize);        //测试集数据数，每一折的数据数

//需要去除方差最小的DEL个特征
//这里用这个数组存放被去除的数据在feature的下标
int del[DEL];

int main() {
	Module* Modules, * trainData, * testData;
	Modules = (Module*)malloc(SIZE * sizeof(Module));
	trainData = (Module*)malloc(SIZE * sizeof(Module));
	testData = (Module*)malloc(SIZE * sizeof(Module));
	//容错处理
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
	double sum = 0;
	for (int i = 0; i < FOLD; i++) 
	{
		splitData(Modules, trainData, testData, i);
		double Weight[DIM] = { 0 }, Bias = 0;
		train(trainData, Weight, Bias);
		sum += predict(testData, Weight, Bias);
	}
	printf("conclusion:%.4lf",sum / FOLD);
	free(Modules);
	free(trainData);
	free(testData);

}