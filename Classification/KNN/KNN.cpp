#define _CRT_SECURE_NO_WARNINGS 1
#include "KNN.h"

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

	char line[100];
	char species[20];
	for (int i = 0; i < SIZE; i++) {
		if (fgets(line, 100, file) != NULL) {
			sscanf(line, "%f,%f,%f,%f,%s", &irises[i].feature[0], &irises[i].feature[1], &irises[i].feature[2], &irises[i].feature[3], species);

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

	printf("Read File Successfully!");
	fclose(file);
	return 1;
}

void preProcess(Iris* irises)
{
	float MAX[4], MIN[4];
	getMinMax(irises, MAX, MIN);
	MinMaxScalar(irises, MAX, MIN);
	shuffleData(irises);
}

void getMinMax(Iris* irises, float* MAX, float* MIN) {
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

void MinMaxScalar(Iris* irises, float* MAX, float *MIN) {
	float Scalar[4];
	for (int i = 0; i < 4; i++) {
		Scalar[i] = MAX[i] - MIN[i];
	}
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < 4; j++) {
			irises[i].feature[j] = (irises[i].feature[j] - MIN[j]) / Scalar[j];
		}
	}
}

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

void splitData(Iris* irises, Iris* train, Iris* test) {
	for (int i = 0; i < trainSize; i++) {
		train[i] = irises[i];
	}
	for (int i = trainSize; i < SIZE; i++) {
		test[i - trainSize] = irises[i];
	}
}

void predict(Iris* train, Iris* test) {
	Dis distance[120];
	Dis rank[30 * K];
	for (int i = 0; i < testSize; i++) {
		for (int j = 0; j < trainSize; j++) {
			float sum = 0;
			for (int k = 0; k < 4; k++) {
				sum += pow(test[i].feature[k] - train[j].feature[k], 2);
			}
			distance[j].distance = sqrt(sum);
			distance[j].species = train[j].species;
		}
		quickSort(distance, 0, trainSize - 1);
		for (int m = 0; m < K; m++) {
			rank[i * K + m] = distance[m];
		}
	}

	int species[3] = { 0 };
	int trueNum = 0;
	for (int i = 0; i < testSize; i++) {
		for (int j = 0; j < K; j++) {
			species[rank[i * K + j].species]++;
		}
		if (getSpecie(species) == test[i].species)
			trueNum++;
		for (int k = 0; k < 3; k++) {
			species[k] = 0;
		}
	}
	printf("K = %d, precision = %f", K, (float)trueNum / testSize);
}

void quickSort(Dis* arr, int low, int high) {
	int i = low;
	int j = high;
	int temp = arr[low].distance;
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