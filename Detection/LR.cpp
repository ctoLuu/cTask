#define _CRT_SECURE_NO_WARNINGS 1
#include"LR.h"

int readTxt(Module* Modules) {
	FILE* file;
	file = fopen("data.txt", "r");
	if (file == NULL) {
		printf("Fail To Open File!\n");
		return 0;
	}
	else {
		printf("Open File Successfully!\n");
	}

	int index = 0;
	int total_lines = 0; // 用于统计总行数
	int zeroes_count = 0; // 0的个数
	int ones_count = 0; // 1的个数

	char buffer[300];
	while (fgets(buffer, sizeof(buffer), file) && index < 17001) {
		total_lines++; // 增加行数计数
		char* ptrBuf = buffer;
		int parsed_items;
		for (int i = 0; i < 38; ++i) {
			parsed_items = sscanf(ptrBuf, "%lf", &Modules[index].feature[i]);
			if (parsed_items != 1) {
				fprintf(stderr, "Error reading data at line %d, dimension %d\n", total_lines, i);
				fclose(file);
				return 0;
			}
			while (*ptrBuf != ',' && *ptrBuf != '\0') ptrBuf++;
			while (*ptrBuf == ',') ptrBuf++;
		}
		parsed_items = sscanf(ptrBuf, "%d", &Modules[index].defective);
		if (parsed_items != 1) {
			fprintf(stderr, "Error reading data at line %d, dimension 39\n", total_lines);
			fclose(file);
			return 0;
		}
		// 统计最后一个数据是0还是1
		if (Modules[index].defective == 0) {
			zeroes_count++;
		}
		else if (Modules[index].defective == 1) {
			ones_count++;
		}
		index++;
	}
	fclose(file);

	// 输出统计结果
	printf("Total lines read: %d\n", total_lines);
	printf("Number of 0 is: %d\n", zeroes_count);
	printf("Number of 1 is: %d\n", ones_count);

	return 1;
}

void preProcess(Module* Modules, double** features) {
	double MAX[38], MIN[38];
	double mean[38] = { 0 }, deviation[38] = { 0 };
	getFeature(Modules, features);
	featureStandard(features);
	//getMinMax(Modules, MAX, MIN);
	//getMeanDeviation(Modules, mean, deviation);
	//MinMaxScalar(Modules, MAX, MIN);
	//Standardization(Modules, mean, deviation);
	//shuffleData(Modules);
}

void getFeature(Module* Modules, double** features) {
	double* MAX, * MIN;
	MAX = (double*)malloc(sizeof(double) * SIZE);
	MIN = (double*)malloc(sizeof(double) * SIZE);
	getMinMax(Modules, MAX, MIN);
	MinMaxScalar(Modules, MAX, MIN);
	Kmeans(Modules, features);
	featureScalar(features, MAX, MIN);
	free(MAX);
	free(MIN);
}

void getMinMax(Module* Modules, double* MAX, double* MIN) {
	for (int i = 0; i < SIZE; i++) {
		MAX[i] = Modules[i].feature[0];
		MIN[i] = Modules[i].feature[0];
	}
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < 38; j++) {
			if (Modules[i].feature[j] > MAX[i])
				MAX[i] = Modules[i].feature[j];
			if (Modules[i].feature[j] < MIN[i])
				MIN[i] = Modules[i].feature[j];
		}
	}
}

void MinMaxScalar(Module* Modules, double* MAX, double* MIN) {
	double* Scalar;
	Scalar = (double*)malloc(sizeof(double) * SIZE);
	for (int i = 0; i < SIZE; i++) {
		Scalar[i] = MAX[i] - MIN[i];
	}
	for (size_t i = 0; i < SIZE; i++) {
		for (int j = 0; j < 38; j++) {
			Modules[i].feature[j] = (Modules[i].feature[j] - MIN[i]) / Scalar[i];
		}
	}
	free(Scalar);
}

void Kmeans(Module* Modules, double** features) {
	int dim[K];
	int cluster[K + 1][38] = { 0 };
	srand(51);
	for (int i = 0; i < K; i++) {
		dim[i] = rand() % 38;
		for (int j = 0; j < SIZE; j++) {
			features[i][j] = Modules[j].feature[dim[i]];
		}
	}
	for (int i = 0; i < K_EPOCH; i++) {
		for (int j = 0; j < 38; j++) {
			double min = calculateDistance(features[0], Modules, j);
			int flag = 0;
			for (int k = 1; k < K; k++) {
				double distance = calculateDistance(features[k], Modules, j);
				if (distance < min) {
					min = distance;
					flag = k;
				}
			}
			cluster[K][flag]++;
			cluster[flag][cluster[K][flag]-1] = j;
		}
		for (int j = 0; j < K; j++) {
			for (int k = 0; k < SIZE; k++) {
				features[j][k] = 0;
			}
			for (int k = 0; k < cluster[K][j]; k++) {
				for (int m = 0; m < SIZE; m++) {
					features[j][m] += Modules[m].feature[cluster[j][k]];
				}
			}
			for (int k = 0; k < SIZE; k++) {
				features[j][k] /= cluster[K][j];
			}
		}
		for (int j = 0; j < 38; j++)
			cluster[K][j] = 0;
	}
}

void featureScalar(double** features, double* MAX, double* MIN) {
	double* Scalar;
	Scalar = (double*)malloc(sizeof(double) * SIZE);
	for (int i = 0; i < SIZE; i++) {
		Scalar[i] = MAX[i] - MIN[i];
	}
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < SIZE; j++) {
			features[i][j] = features[i][j] * Scalar[j] + MIN[j];
		}
	}
	free(Scalar);
}

void featureStandard(double** features) {
	double mean[K] = { 0 }, deviation[K] = { 0 };
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < SIZE; j++) {
			mean[i] += features[i][j];
		}
		mean[i] /= SIZE;
	}
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < SIZE; j++) {
			deviation[i] += (features[i][j] - mean[i]) * (features[i][j] - mean[i]);
		}
		deviation[i] /= SIZE;
		deviation[i] = sqrt(deviation[i]);
	}
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < K; j++) {
			features[j][i] = (features[j][i] - mean[j]) / deviation[j];
		}
	}
}

double calculateDistance(double* feature, Module* Modules, int flag) {
	double distance = 0;
	for (int i = 0; i < SIZE; i++) {
		distance += pow(feature[i] - Modules[i].feature[flag], 2);
	}
	distance = sqrt(distance);
	return distance;
}

void getMeanDeviation(Module* Modules, double* mean, double* deviation) {
	for (int i = 0; i < 38; i++) {
		for (int j = 0; j < SIZE; j++) {
			mean[i] += Modules[j].feature[i];
		}
		mean[i] /= SIZE;
	}
	for (int i = 0; i < 38; i++) {
		for (int j = 0; j < SIZE; j++) {
			deviation[i] += (Modules[j].feature[i] - mean[i]) * (Modules[j].feature[i] - mean[i]);
		}
		deviation[i] /= SIZE;
		deviation[i] = sqrt(deviation[i]);
	}
}

void Standardization(Module* Modules, double* mean, double* deviation) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < 38; j++) {
			Modules[i].feature[j] = (Modules[i].feature[j] - mean[j]) / deviation[j];
		}
	}
}

void shuffleData(Module* Modules) {
	for (int i = SIZE - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		swap(&Modules[i], &Modules[j]);
	}
}

void swap(Module* a, Module* b) {
	Module temp = *a;
	*a = *b;
	*b = temp;
}

void splitData(Module* Modules, Module* train, Module* test) {
	for (size_t i = 0; i < trainSize; i++)
		train[i] = Modules[i];
	for (size_t i = trainSize; i < SIZE; i++)
		test[i - trainSize] = Modules[i];
}

void train(Module* trainData, double* Weight, double Bias, double** features) {
	for (int i = 0; i < EPOCH; i++) {
		double totalLoss = 0;
		double regLoss = 0;
		double z = 0, a = 0;
		//double dz = 0, db = 0, dw[38] = { 0 };
		double dz = 0, db = 0, dw[K] = { 0 };
		for (size_t j = 0; j < trainSize; j++) {
			//regLoss = calculateRegLoss(Weight);
			z = 0;
			// forward propagation
			for (int k = 0; k < K; k++) {
				z += Weight[k] * features[k][j];
			}
			z += Bias;
			a = sigmoid(z);
			totalLoss += calculateLogLoss(trainData[j].defective, a) + regLoss;

			// backward propagation
			dz = a - trainData[j].defective;
			db += dz;
			for (int k = 0; k < K; k++) {
				dw[k] += features[k][j] * dz;
			}
		}

		totalLoss /= trainSize; 
		db /= trainSize;
		for (int k = 0; k < K; k++) {
			dw[k] /= trainSize;
			Weight[k] -= LEARNING_RATE * dw[k];
		}
		Bias -= LEARNING_RATE * db;
		if (i % 4000 == 0) {
			printf("epoch : %d , Loss = %lf\n", i, totalLoss);
		}
	}
}


double sigmoid(double Z) {
	return 1.0 / (1.0 + exp(-Z));
}

double calculateLogLoss(double y, double a) {
	return -y * log(a) - (1 - y) * log(1 - a);
}

double calculateRegLoss(double* Weight) {
	double regLoss = 0;
	for (int i = 0; i < K; i++) {
		regLoss += Weight[i] * Weight[i];
	}
	return LAMBDA * regLoss / 2.0;
}

void predict(Module* testData, double* Weight, double Bias, double** features) {
	int trueNum[100] = { 0 };
	double rate = 0.01;
	int TP = 0, FP = 0, TN = 0, FN = 0;
	double maxRate = 0;
	double maxF1 = 0;

	for (int k = 1; k < 100; k++) {
		double F1 = 0, precision = 0, recall = 0;
		//for (int i = 0; i < testSize; i++) {
		for (int i = trainSize; i < SIZE; i++) {
			double z = 0, a = 0;
			int yhat;
			for (int j = 0; j < K; j++) {
				z += Weight[j] * features[j][i];
			}
			z += Bias;
			a = sigmoid(z);
			yhat = inference(a, rate * k);
			if (yhat == testData[i - trainSize].defective)
				trueNum[k]++;
			if (yhat == 1) {
				if (testData[i - trainSize].defective == 1)
					TP++;
				else
					FP++;
			}
			else {
				if (testData[i - trainSize].defective == 0)
					TN++;
				else
					FN++;
			}
		}
		if (FP + TP != 0)
			precision = 1.0 * TP / (TP + FP);
		recall = 1.0 * TP / (TP + FN);
		if (precision + recall != 0)
			F1 = 2 * precision * recall / (precision + recall);
		else
			F1 = 0;
		printf("rate = %.2f , TP = %d , FP = %d , TN = %d , FN = %d\nPrecision = %lf , Recall = %lf\nF1 = %lf\n\n", rate * k, TP, FP, TN, FN, precision, recall, F1);
		if (F1 > maxF1) {
			maxRate = rate * k;
			maxF1 = F1;
		}
		TP = 0;
		FP = 0;
		TN = 0;
		FN = 0;
	}
	printf("\nMax rate : %.2lf , Max F1 : %lf", maxRate, maxF1);
}

int inference(double a, double rate) {
	if (a >= rate)
		return 1;
	else
		return 0;
}

