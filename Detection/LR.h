#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

#define DEL 1               //去除特征的个数
#define SIZE 17001          //每个维度包含的数据总个数
#define TRAIN_RATE 0.8      //训练集比例
#define LEARNING_RATE 0.01 //学习率（步长）
#define LAMBDA 0.01        //正则化参数
#define EPOCH 30000         //训练迭代最大次数
#define DIM 38              //维度数
#define FOLD 3              //折数

extern size_t trainSize;
extern size_t testSize;
extern int del[];

typedef struct
{
	double feature[DIM];
	int defective;
}Module;  

int readTxt(Module*);
void preProcess(Module*);
void getMeanDeviation(Module*, double*, double*);
void Standardization(Module*, double*, double*);
void getMinMax(Module*, double*, double*);
void MinMaxScalar(Module*, double*, double*);
void minIndices(double*,int*);
int in(int k, int* delnum);
void shuffleData(Module*);
void swap(Module*, Module*);
void splitData(Module*, Module*, Module*, int);
void train(Module*, double*, double);
double predict(Module*, double*, double);
double sigmoid(double);
double calculateLogLoss(double, double);
int inference(double, double);
double calculateRegLossL1(double*);
double calculateRegLossL2(double*);