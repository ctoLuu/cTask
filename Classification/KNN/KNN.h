#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define SIZE 150             // 数据集大小
#define TRAIN_RATE 0.8       // 训练集比例
#// define K 68

typedef struct {             // 结构体存放鸢尾花特征
	double feature[4];
	int species;
}Iris;
typedef struct {             // 结构体存放测试集与训练集计算的举例
	double distance;
	int species;
}Dis;

int readTxt(Iris*);          // 读取数据集 
void preProcess(Iris*);      // 数据集预处理
void getMinMax(Iris*, double*, double*);       // 找到特征的最大最小值   
void MinMaxScalar(Iris*, double*, double*);    // 标准化
void shuffleData(Iris*);      // 随机打乱数据集
void splitData(Iris*, Iris*, Iris*);      // 划分数据集
void swap(Iris*, Iris*);      // 交换数据
void swap(Dis*, Dis*);        // 排序的交换函数
void quickSort(Dis*, int, int);   // 对到每一个训练集的距离排序
void predict(Iris*, Iris*, int);     // 核心算法
void getRank(Dis*, Iris*, Iris*, int, int);    // 获得K以内的种类
// void getPrecision(double*, Iris*, Dis*, int);     // 计算准确率
int getSpecie(int*);        // 获取预测的种类

extern size_t trainSize;    // 训练集大小
extern size_t testSize;     // 测试集大小