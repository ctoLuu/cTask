#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define SIZE 17001
#define TRAIN_RATE 0.8

extern size_t trainSize;
extern size_t testSize;

typedef struct
{
	double feature[38];
	int defective;
}Module;

int readTxt(Module*);
void preProcess(Module*);
void getMinMax(Module*, double*, double*);
void MinMaxScalar(Module*, double*, double*);
void splitData(Module*, Module*, Module*);
void shuffleData(Module*);
void swap(Module*, Module*);
void splitData(Module*, Module*, Module*);

