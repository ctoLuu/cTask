#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define SIZE 17001
#define TRAIN_RATE 0.8
#define LEARNING_RATE 0.02
#define LAMBDA 0.01
#define K_EPOCH 50
#define EPOCH 30000
#define K 4
extern size_t trainSize;
extern size_t testSize;

typedef struct
{
	double feature[38];
	int defective;
}Module;

int readTxt(Module*);
void preProcess(Module*, double**);
void getFeature(Module*, double**);
void Kmeans(Module*, double**);
void featureScalar(double**, double*, double*);
void featureStandard(double**);
void getMeanDeviation(Module*, double*, double*);
void Standardization(Module*, double*, double*);
void getMinMax(Module*, double*, double*);
void MinMaxScalar(Module*, double*, double*);
void splitData(Module*, Module*, Module*);
void shuffleData(Module*);
void swap(Module*, Module*);
void splitData(Module*, Module*, Module*);
void train(Module*, double*, double, double**);
void predict(Module*, double*, double, double**);
double sigmoid(double);
double calculateLogLoss(double, double);
int inference(double, double);
double calculateRegLoss(double*);
double calculateDistance(double*, Module*, int);