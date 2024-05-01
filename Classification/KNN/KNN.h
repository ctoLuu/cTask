#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define SIZE 150
#define TRAIN_RATE 0.8

typedef struct {
	double feature[4];
	int species;
}Iris;
typedef struct {
	double distance;
	int species;
}Dis;

int readTxt(Iris*);
void preProcess(Iris*);
void getMinMax(Iris*, double*, double*);
void MinMaxScalar(Iris*, double*, double*);
void splitData(Iris*, Iris*, Iris*);
void shuffleData(Iris*);
void swap(Iris*, Iris*);
void swap(Dis*, Dis*);
void predict(Iris*, Iris*);
void quickSort(Dis*, int, int, int);
int getSpecie(int*);

extern size_t trainSize;
extern size_t testSize;