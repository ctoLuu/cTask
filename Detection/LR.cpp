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