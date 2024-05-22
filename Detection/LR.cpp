#define _CRT_SECURE_NO_WARNINGS 1
#include"LR.h"
//打开文件，输入数据
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
		for (int i = 0; i < DIM; ++i) {
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

//标准化或者归一化数据，并且记录要进行方差过滤的维数
void preProcess(Module* Modules) {
	double MAX[DIM], MIN[DIM];
	double mean[DIM] = { 0 }, deviation[DIM] = { 0 };
	getMinMax(Modules, MAX, MIN);
	getMeanDeviation(Modules, mean, deviation);
	MinMaxScalar(Modules, MAX, MIN);
	minIndices(deviation, del);
	//Standardization(Modules, mean, deviation);
	shuffleData(Modules);
}
// 找到数组中标准差最小的DEL个数的下标，存放在del数组
void minIndices(double* deviation,int* delnum){
	for (int i = 0; i < DEL; i++) {
		delnum[i] = i;
	}
	// 找到数组中最小的DEL个数的下标
	for (int i = DEL; i < DIM; i++) {
		int max_index = 0;
		for (int j = 1; j < DEL; j++) {
			if (deviation[delnum[j]] > deviation[delnum[max_index]]) {
				max_index = j;
			}
		}
		if (deviation[i] < deviation[delnum[max_index]]) {
			delnum[max_index] = i;
		}
	}
}

void getMeanDeviation(Module* Modules, double* mean, double* deviation) {
	//获得平均数
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < SIZE; j++) {
			mean[i] += Modules[j].feature[i];
		}
		mean[i] /= SIZE;
	}
	//求出每一维度数据的标准差
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < SIZE; j++) {
			deviation[i] += (Modules[j].feature[i] - mean[i]) * (Modules[j].feature[i] - mean[i]);
		}
		deviation[i] /= SIZE;
		deviation[i] = sqrt(deviation[i]);
	}
}
//将数据标准化，把每一维度的数据化为正态分布
void Standardization(Module* Modules, double* mean, double* deviation) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < DIM; j++) {
			Modules[i].feature[j] = (Modules[i].feature[j] - mean[j]) / deviation[j];
		}
	}
}
//获得每一个维度的最大值
void getMinMax(Module* Modules, double* MAX, double* MIN) {
	for (int i = 0; i < DIM; i++) {
		MAX[i] = Modules[0].feature[i];
		MIN[i] = Modules[0].feature[i];
	}
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < DIM; j++) {
			if (Modules[i].feature[j] > MAX[j])
				MAX[j] = Modules[i].feature[j];
			if (Modules[i].feature[j] < MIN[j])
				MIN[j] = Modules[i].feature[j];
		}
	}
}
//归一化操作，将数据映射到[0,1]
void MinMaxScalar(Module* Modules, double* MAX, double* MIN) {
	double Scalar[40];
	for (int i = 0; i < DIM; i++) {
		Scalar[i] = MAX[i] - MIN[i];
	}
	for (size_t i = 0; i < SIZE; i++) {
		for (int j = 0; j < DIM; j++) {
			Modules[i].feature[j] = (Modules[i].feature[j] - MIN[j]) / Scalar[j];
		}
	}
}
//将训练模型的数据集进行打乱
void shuffleData(Module* Modules) {
	srand((unsigned int)time(NULL));        //初始化随机数生成器
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
//将数据集分为训练集和测试集
//第k+1折为测试集，testSize为每一折所含数据的数量
void splitData(Module* Modules, Module* train, Module* test,int k) {
	for (size_t i = 0; i < k * testSize; i++)
		train[i] = Modules[i];
	for (size_t i = k * testSize; i < testSize * (k + 1); i++)
		test[i - k * testSize] = Modules[i];
	for (size_t i = testSize * (k + 1); i < testSize * FOLD; i++)
		train[i - testSize] = Modules[i];
}
//用来求出最优权重
void train(Module* trainData, double* Weight, double Bias) {
	//printf("%d", trainSize);
	for (int i = 0; i < EPOCH; i++) {
		double totalLoss = 0;      //总损失
		double regLoss = 0;        //正则化损失
		double z = 0;       //z是预测函数的结果
		double a = 0;		//a是预测函数在sigmoid函数上的映射
		double dz = 0, db = 0, dw[DIM] = { 0 };
		
		for (size_t j = 0; j < trainSize; j++) {
			//regLoss = calculateRegLossL2(Weight);     //L2正则化，防止模型过拟合
			regLoss = calculateRegLossL1(Weight);     //L1正则化，防止模型过拟合
			z = 0;
			// forward propagation
			for (int k = 0; k < DIM && in(k,del)== 0; k++) {
				z += Weight[k] * trainData[j].feature[k];
			}
			z += Bias;
			a = sigmoid(z);
			totalLoss += calculateLogLoss(trainData[j].defective, a) + regLoss;

			// 初始化模型参数
			dz = a - trainData[j].defective;
			db += dz;
			for (int k = 0; k < DIM && in(k, del) == 0; k++) {
				dw[k] += trainData[j].feature[k] * dz + LAMBDA * Weight[k];
			}
		}
		//更新模型参数
		totalLoss /= trainSize;       //均方误差代价函数的结果
		db /= trainSize;
		for (int k = 0; k < DIM && in(k, del) == 0; k++) {
			dw[k] /= trainSize; // 计算平均梯度  
			Weight[k] -= LEARNING_RATE * dw[k];// 更新权重  
		}
		Bias -= LEARNING_RATE * db;// 更新偏置
		//printf("%.4lf\n", totalLoss);
		//每4000次预测，输出一次总损失，理想结果应是越来越小
		if (i % 4000 == 0) {
			printf("epoch : %d , Loss = %lf\n", i, totalLoss);
		}
	}
}

//Sigmoid函数
double sigmoid(double Z) {
	return 1.0 / (1.0 + exp(-Z));
}
//交叉熵损失函数，用来判断模型拟合效果，结果越小，效果越好（单个样本）
double calculateLogLoss(double y, double a) {
	return -y * log(a) - (1 - y) * log(1 - a);
}
//L2正则化，防止模型过拟合
double calculateRegLossL2(double* Weight) {
	double regLoss = 0;
	for (int i = 0; i < DIM && in(i, del) == 0; i++) {
		regLoss += Weight[i] * Weight[i];
	}
	return LAMBDA * regLoss / 2.0;
}
//L1正则化，防止模型过拟合
double calculateRegLossL1(double* Weight) {
	double regLoss = 0;
	for (int i = 0; i < DIM && in(i, del) == 0; i++) {
		regLoss += fabs(Weight[i]);
	}
	return LAMBDA * regLoss / 2.0;
}

//找到最佳二元分类的最佳阈值，并输出f1-socre（度量预测效果）
double predict(Module* testData, double* Weight, double Bias) {
	int trueNum[100] = { 0 };     //存储在不同步长下预测正确的数量。
	double rate = 0.01;
	int TP = 0, FP = 0, TN = 0, FN = 0;
	double maxRate = 0;
	double maxF1 = 0;

	for (int k = 1; k < 100; k++) {              
		double F1 = 0, precision = 0, recall = 0;//precision精确率；recall召回率
		for (int i = 0; i < testSize; i++) {
			double z = 0, a = 0;
			int yhat;
			for (int j = 0; j < DIM && in(j, del) == 0; j++) {
				z += Weight[j] * testData[i].feature[j];
			}
			a = sigmoid(z);
			yhat = inference(a, rate * k);
			if (yhat == testData[i].defective)
				trueNum[k]++;
			if (yhat == 1) {
				if (testData[i].defective == 1)
					TP++;
				else
					FP++;
			}
			else {
				if (testData[i].defective == 0)
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
		//printf("rate = %.2f , TP = %d , FP = %d , TN = %d , FN = %d\nPrecision = %lf , Recall = %lf\nF1 = %lf\n\n",
		  //rate * k, TP, FP, TN, FN, precision, recall, F1);
		if (F1 > maxF1) {
			maxRate = rate * k;
			maxF1 = F1;
		}
		TP = 0;
		FP = 0;
		TN = 0;
		FN = 0;
	}
	printf("\nMax rate : %.2lf , Max F1 : %lf\n", maxRate, maxF1);
	return maxF1;
}

void K_Fold(Module * testData, double* Weight, double Bias) {
	
}

int inference(double a, double rate) {
	if (a >= rate)
		return 1;
	else
		return 0;
}

int in(int k, int* delnum) {
	for (int i = 0; i < DEL; i++)
		if (k == delnum[i]) return 1;
	return 0;
}