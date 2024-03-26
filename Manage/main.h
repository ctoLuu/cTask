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
	float sum=0;
	float aver=0;
	struct student* next;
}STU;

int Menu_Teacher(void);
int Menu_Student(void);
void SetPosition(int x, int y);
void TidyupRecord(STU* head, int n, int m);
void InputRecord(STU* head, int* n, int* m);
void AppendRecord(STU* head, int* n, int m);
void DeleteRecord(STU* head, int* n, int m);
void SearchbyNum(STU* head, int n, int m);
void SearchbyName(STU* head, int n, int m);
void ModifyRecord(STU* head, int n, int m);
void CalculateScoreOfStudent(STU* head, int n, int m);
void CalculateScoreOfCourse(STU* head, int n, int m);
void SortbyNum(STU* head, int n, int m);
void SortbyName(STU* head, int n, int m);
void SortbyScore(STU* head, int n, int m, int(*compare)(float a, float b));
int Ascending(float a, float b);
int Descending(float a, float b);
void StatisticAnalysis(STU* head, int n, int m);
void PrintRecord(STU* head, int n, int m);
void WritetoFile(int n, int m, STU* head);
int ReadfromFile(int* n, int* m, STU* head, int* first);
int Exchange_identity();