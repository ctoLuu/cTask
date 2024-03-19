#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#define STU_NUM 50
#define COURSE_NUM 10
#define NAME_LEN 10
#define POS_X1 35
#define POS_X2 40
#define POS_X3 50
#define POS_X4 65
#define POS_Y 3
typedef struct student
{
	long num;
	char name[NAME_LEN];
	float score[COURSE_NUM];
	float sum;
	float aver;

}STU;

int MENU(void);
void SetPosition(int x, int t);
void InputRecord(STU stu[], int* n, int* m);
void AppendRecord(STU stu[], int* n, int* m);
void DeleteRecord(STU stu[], int* n, int* m);
void SearchbyNum(STU stu[], int n, int* m);
void SearchbyName(STU stu[], int n, int* m);
void ModifyRecord(STU stu[], int n, int* m);
void CalculateScoreOfStudent(STU stu[], int n, int m);
void CalculateScoreOfCourse(STU stu[], int n, int m);
void SortbyNum(STU stu[], int n, int m);
void SortbyName(STU stu[], int n, int m);
void SortbyScore(STU stu[], int n, int m, int(*compare)(float a, float b));
int Ascending(float a, float b);
int Descending(float a, float b);
void StatisticAnalysis(STU stu[], int n, int m);
void PrintRecord(STU stu[], int n, int m);
void WritetoFile(STU stu[], int n, int m);
int ReadfromFile(STU stu[], int* n, int* m, int* first);