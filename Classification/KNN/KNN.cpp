#define _CRT_SECURE_NO_WARNINGS 1
#include "KNN.h"

// 读取
int readTxt(Iris* irises)
{
	FILE* file;
	file = fopen("data.txt", "r");
	if (file == NULL) {
		printf("Fail To Open File!\n");
		return 0;
	}
	else {
		printf("Open File Successfully!\n");	}

	// 读取每一行进入 line 再写入结构体数组
	char line[100];
	char species[20];
	for (int i = 0; i < SIZE; i++) {
		if (fgets(line, 100, file) != NULL) {
			sscanf(line, "%lf,%lf,%lf,%lf,%s", &irises[i].feature[0], &irises[i].feature[1], &irises[i].feature[2], &irises[i].feature[3], species);

			if (strcmp(species, "Iris-setosa") == 0)
				irises[i].species = 0;
			else if (strcmp(species, "Iris-versicolor") == 0)
				irises[i].species = 1;
			else
				irises[i].species = 2;

		}
		else {
			printf("Fail To Read File");
			return 0;
		}
	}

	printf("Read File Successfully!\n");
	fclose(file);
	return 1;
}


// 数据预处理
void preProcess(Iris* irises)
{
	double MAX[4], MIN[4];
	getMinMax(irises, MAX, MIN);
	MinMaxScalar(irises, MAX, MIN);
	shuffleData(irises);
}

// 获取最大最小值，用于数据标准化
void getMinMax(Iris* irises, double* MAX, double* MIN) {
	for (int i = 0; i < 4; i++) {
		MAX[i] = irises[0].feature[i];
		MIN[i] = irises[0].feature[i];
	}

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < 4; j++) {
			if (irises[i].feature[j] > MAX[j])
				MAX[j] = irises[i].feature[j];
			if (irises[i].feature[j] < MIN[j])
				MIN[j] = irises[i].feature[j];
		}
	}
}

// 数据标准化，避免数据量纲影响结果
void MinMaxScalar(Iris* irises, double* MAX, double *MIN) {
	double Scalar[4];
	for (int i = 0; i < 4; i++) {
		Scalar[i] = MAX[i] - MIN[i];
	}
	for (size_t i = 0; i < SIZE; i++) {
		for (int j = 0; j < 4; j++) {
			irises[i].feature[j] = (irises[i].feature[j] - MIN[j]) / Scalar[j];
		}
	}
}

// 随机打乱数据
void shuffleData(Iris* irises) {
	for (int i = SIZE - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		swap(&irises[i], &irises[j]);
	}
}

void swap(Iris* a, Iris* b) {
	Iris temp = *a;
	*a = *b;
	*b = temp;
}
void swap(Dis* a, Dis* b) {
	Dis temp = *a;
	*a = *b;
	*b = temp;
}

// 划分数据集
void splitData(Iris* irises, Iris* train, Iris* test) {
	for (int i = 0; i < trainSize; i++) {
		train[i] = irises[i];
	}
	for (int i = trainSize; i < SIZE; i++) {
		test[i - trainSize] = irises[i];
	}
}

//// 核心算法
//void predict(Iris* train, Iris* test, int end_K) {
//	Dis rank[30 * 100];
//	double prenum[500];
//	int K;
//	for (K = 1; K < end_K; K++) {     // 循环不同 K， 寻找最大准确率
//		getRank(rank, train, test, K);
//		getPrecision(prenum, test, rank, K);
//	}
//	int max_K = 0;
//	for (int s = 1; s < end_K; s++) {
//		if (prenum[max_K] < prenum[s]) {
//			max_K = s;
//		}
//	}
//	printf("\nmax_K is %d", max_K + 1);
//}
//
//
//// 获得距离的排序
//void getRank(Dis* rank, Iris* train, Iris* test, int K) {
//	Dis distance[120];
//	for (int i = 0; i < testSize; i++) {
//		for (int j = 0; j < trainSize; j++) {
//			double sum = 0;
//			for (int k = 0; k < 4; k++) {
//				// 计算每一个测试集到每一个训练集的欧氏距离
//				sum += pow(test[i].feature[k] - train[j].feature[k], 2);
//			}
//			distance[j].distance = sqrt(sum);
//			distance[j].species = train[j].species;
//		}
//		// 对一个测试集样本进行排序
//		quickSort(distance, 0, trainSize - 1);
//		// 将小于 K 值的写入rank
//		for (int m = 0; m < K; m++) {
//			rank[i * K + m] = distance[m];
//		}
//	}
//
//}
//
//// 获得准确度
//void getPrecision(double* prenum, Iris* test, Dis* rank, int K) {
//	int species[3] = { 0 };
//	int trueNum = 0;
//	for (int i = 0; i < testSize; i++) {
//		for (int j = 0; j < K; j++) {
//			species[rank[i * K + j].species]++;
//		}
//		// 如果预测的种类与实际相同，则正确种类 + 1
//		if (getSpecie(species) == test[i].species)
//			trueNum++;
//		for (int k = 0; k < 3; k++) {
//			species[k] = 0;
//		}
//	}
//	printf("K = %d, precision = %f\n", K, (double)trueNum / testSize);
//	prenum[K - 1] = (double)trueNum / testSize;
//}

// 核心算法
void predict(Iris* train, Iris* test, int end_K) {
	double allPrec[100];
	
	for (int K = 1; K < end_K; K++) {
		int trueNum = 0;
		int species[3] = { 0 };
		for (int i = 0; i < testSize; i++) {
			Dis rank[100];
			getRank(rank, train, test, K, i);
			for (int j = 0; j < K; j++) {
				species[rank[j].species]++;
			}
			if (getSpecie(species) == test[i].species)
				trueNum++;
			for (int k = 0; k < 3; k++) {
				species[k] = 0;
			}
		}
		printf("K = %d, precision = %f\n", K, (double)trueNum / testSize);
		allPrec[K - 1] = (double)trueNum / testSize;
	}

	int max_k = 0;
	for (int s = 1; s < end_K; s++) {
		if (allPrec[max_k] < allPrec[s]) {
			max_k = s;
		}
	}
	printf("\nmax_k is %d", max_k + 1);
}

// K以内的距离排序
void getRank(Dis* rank, Iris* train, Iris* test, int K, int i) {
	Dis distance[120];
	for (int j = 0; j < trainSize; j++) {
		double sum = 0;
		for (int k = 0; k < 4; k++) {
			sum += pow(test[i].feature[k] - train[j].feature[k], 2);
		}
		distance[j].distance = sqrt(sum);
		distance[j].species = train[j].species;
	}
	quickSort(distance, 0, trainSize - 1);

	for (int m = 0; m < K; m++) {
		rank[m] = distance[m];
	}
}

// 对距离排序
void quickSort(Dis* arr, int low, int high) {
	int i = low;
	int j = high;
	double temp = arr[low].distance;
	if (i >= j)
		return;
	while (i != j) {
		while (i < j && arr[j].distance >= temp)
			j--;
		while (i < j && arr[i].distance <= temp)
			i++;
		if (i < j)
			swap(&arr[i], &arr[j]);
	}
	swap(&arr[low], &arr[i]);
	quickSort(arr, i + 1, high);
	quickSort(arr, low, i - 1);
}

// 预测种类
int getSpecie(int* species) {
	int flag = 0;
	int max = species[0];
	for (int i = 1; i < 3; i++) {
		if (species[i] > max) {
			max = species[i];
			flag = i;
		}
	}
	return flag;
}