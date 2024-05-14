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
	const int line_count = 17001;
	char buffer[300];
	char* ptrBuf = buffer;
	while (index < line_count && fgets(buffer, sizeof(buffer), file)) {
		ptrBuf = buffer;
		int parased_items;
		for (int i = 0; i < 38; ++i) {
			parased_items = sscanf(ptrBuf, "%lf", &Modules[index].feature[i]);
			if (parased_items != 1) {
				fprintf(stderr, "Error reading data at line %ld, dimension %d\n", index + 1, i);
				return 0;
			}
			char* ptr = ptrBuf;
			while (*ptr != ',' && *ptr != '\0')
				ptr++;
			while (*ptr == ',')
				ptr++;
			ptrBuf = ptr;
		}
		parased_items = sscanf(ptrBuf, "%d", &Modules[index].defective);
		if (parased_items != 1) {
			fprintf(stderr, "Error reading data at line %ld, dimension 39\n", index + 1);
			return 0;
		}
		index++;
	}

	fclose(file);
	return 1;
}

void preProcess(Module* Modules) {
	double MAX[38], MIN[38];
	getMinMax(Modules, MAX, MIN);
	MinMaxScalar(Modules, MAX, MIN);
	//shuffleData(Modules);
}

void getMinMax(Module* Modules, double* MAX, double* MIN) {
	for (int i = 0; i < 38; i++) {
		MAX[i] = Modules[0].feature[i];
		MIN[i] = Modules[0].feature[i];
	}
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < 38; j++) {
			if (Modules[i].feature[j] > MAX[j])
				MAX[j] = Modules[i].feature[j];
			if (Modules[i].feature[j] < MIN[j])
				MIN[j] = Modules[i].feature[j];
		}
	}
}

void MinMaxScalar(Module* Modules, double* MAX, double* MIN) {
	double Scalar[40];
	for (int i = 0; i < 38; i++) {
		Scalar[i] = MAX[i] - MIN[i];
	}
	for (size_t i = 0; i < SIZE; i++) {
		for (int j = 0; j < 38; j++) {
			Modules[i].feature[j] = (Modules[i].feature[j] - MIN[j]) / Scalar[j];
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

void train(Module* trainData, double* Weight, double& Bias, double lambda) {
	for (int i = 0; i < EPOCH; i++) {
		double totalLoss = 0; // 用于累计总损失
		double regLoss = 0; // 用于累计正则化损失

		for (size_t j = 0; j < trainSize; j++) {
			double z = 0; // 线性组合结果
			for (int k = 0; k < 38; k++) {
				z += Weight[k] * trainData[j].feature[k];
			}
			double a = sigmoid(z); // 应用sigmoid函数
			double loss = calculateLogLoss(trainData[j].defective, a); // 计算单个样本的损失

			totalLoss += loss; // 累计损失

			// 反向传播，计算梯度
			double dz = a - trainData[j].defective;
			for (int k = 0; k < 38; k++) {
				Weight[k] -= LEARNING_RATE * (trainData[j].feature[k] * dz); // 更新权重
			}
		}

		// 计算L2正则化项
		for (int k = 0; k < 38; k++) {
			regLoss += Weight[k] * Weight[k];
		}
		regLoss *= lambda / (2.0 * trainSize); // 正则化损失

		totalLoss += regLoss; // 将正则化损失加到总损失中
		totalLoss /= trainSize; // 计算平均损失

		// 输出损失信息，可以用于监控训练过程
		if (i % 1000 == 0) {
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

void predict(Module* testData, double* Weight, double Bias) {
	int trueNum[101] = { 0 };
	double rate = 0.01;
	for (int k = 1; k < 100; k++) {//test best rate;
		for (int i = 0; i < testSize; i++) {
			double z = 0, a = 0;
			int yhat;
			for (int j = 0; j < 38; j++) {
				z += Weight[j] * testData[i].feature[j];
			}
			a = sigmoid(z);
			if (k == 1)
				yhat = inference(a, rate * k, 1);
			else
				yhat = inference(a, rate * k, 0);
			if (yhat == testData[i].defective)
				trueNum[k]++;
		}
	}
	int maxratei = 0;
	for (int k = 1; k < 100; k++) {
		printf("rete = %.2lf , Accuracy = %lf\n", rate * k, trueNum[k] * 1.0 / testSize);
		if (trueNum[k] * 1.0 / testSize > trueNum[maxratei] * 1.0 / testSize) {
			maxratei = k;
		}
	}
	printf("\nMax rate : %.2lf , Max Accuracy:%lf", rate * maxratei, trueNum[maxratei] * 1.0 / testSize);

}

int inference(double a, double rate, int flag) {
	if (flag)	printf("%.4lf  ", a);
	if (a >= rate)
		return 1;
	else
		return 0;
}

