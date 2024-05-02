#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define SIZE 150
#define TRAIN_RATE 0.8
#define K 10

typedef struct {
	float feature[4];
	int species;
}Iris;
typedef struct {
	float distance;
	int species;
}Dis;

int readTxt(Iris*);
void preProcess(Iris*);
void getMinMax(Iris*, float*, float*);
void MinMaxScalar(Iris*, float*, float*);
void splitData(Iris*, Iris*, Iris*);
void shuffleData(Iris*);
void swap(Iris*, Iris*);
void swap(Dis*, Dis*);
void predict(Iris*, Iris*);
void quickSort(Dis*, int, int);
int getSpecie(int*);

extern size_t trainSize;
extern size_t testSize;