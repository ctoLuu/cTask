#define _CRT_SECURE_NO_WARNINGS 1
#include"main.h"
int Menu(void);
void SetPosition(int x, int t);
void InputRecord(STU stu[], int* n, int* m)
{
	int i, j;
	int posy = 6;
	SetPosition(POS_X2, posy);
	printf("输入学生人数(n<%d): ", STU_NUM);
	scanf("%d", n);
	SetPosition(POS_X2, posy += 2);
	printf("输入课程门数(m<%d): ", COURSE_NUM);
	scanf("%d", m);
	for (i = 0; i < 2; i++)
	{
		SetPosition(POS_X1, ++posy);
		for (j = 0; j < 55; j++)
		{
			printf("-");
		}
	}
	SetPosition(POS_X2, ++posy);
	printf("输入学生的学号、姓名和各门课程成绩：");
	for (i = 0; i < *n; i++)
	{
		SetPosition(POS_X2, ++posy);
		printf("输入第%d个学生信息：\t", i + 1);
		scanf("%ls%s", &stu[i].num, stu[i].name);
		for (j = 0; j < *m; j++)
		{
			scanf("%f", &stu[i].score[j]);
		}
	}
}
void AppendRecord(STU stu[], int* n, int m)
{
	int i, j;
	int num_record;
	printf("请输入需要增加的学生记录条数：");
	scanf("%d", &num_record);
	while (*n + num_record > STU_NUM)
	{
		printf("要增加的记录条数太多，请重新输入：");
		scanf("%d", &num_record);
	}
	for (i = *n; i < *n + num_record; i++)
	{
		printf("输入第%d个学生信息：\t", i + 1);
		scanf("%ld%s",&stu[i].num, stu[i].name);
		for (j = 0; j < m; j++)
		{
			scanf("%f", &stu[i].score[j]);
		}
	}
	*n = *n + num_record;
	printf("添加完毕！\n");
}
void DeleteRecord(STU stu[], int* n, int m)
{
	int i, j;
	long id;
	char ch;
	printf("请输入你要删除学生信息对应的学号：");
	scanf("%ld", &id);
	for (i = 0; i < *n; i++)
	{
		if (stu[i].num == id)
		{
			printf("找到了该生记录，信息为:\n");
			printf("%10ld%15s", stu[i].num, stu[i].name);
			for (j = 0; j < m; j++)
			{
				printf("%10.2f", stu[i].score[j]);
			}
			printf("%10.2f%10.2f\n", stu[i].sum, stu[i].name);
			printf("请确认是否需要删除这条记录？（Y/y或N/n）：");
			getchar();
			scanf("%c", &ch);
			if (ch == 'Y' || ch == 'y')
			{
				for (j = i; j < *n - 1; j++)
				{
					stu[j] = stu[j + 1];
				}
				(*n)--;
				printf("删除完毕\n");
				
			}
			else if (ch == 'N' || ch == 'n')
			{
				printf("找到了该学生记录，但不能删除\n");

			}
			else {
				printf("输入错误！\n");
			}
		}
	}
	printf("未找到该生记录！\n");

}
void SearchbyNumber(STU stu[], int n, int m)
{
	long id;
	int i, j;
	printf("请输入你要查找的学生的学号：");
	scanf("%ld", &id);
	for (i = 0; i < n; i++)
	{
		if (stu[i].num == id)
		{
			printf("找到了，该学生对应的学生信息为:\n");
			printf("%10ld%15s", stu[i].num, stu[i].name);
			for (j = 0; j < m; j++)
			{
				printf("%10.2f", stu[i].score[j]);
			}
			printf("%10.2f%10.2f", stu[i].sum, stu[i].aver);
		}
	}
	printf("未找到这个学号对应的学生记录\n");
}
void SearchbyName(STU stu[], int n, int m)
{
	int flag = 1;
	int i, j;
	int k = 0;
	char name[NAME_LEN];
	printf("请输入你要查找的学生的姓名：");
	scanf("%s", name);
	for (i = 0; i < n; i++)
	{
		if (strcmp(stu[i].name, name) == 0)
		{
			printf("找到了，第%d学生信息为:\n", ++k);
			printf("%10ld%15s", stu[i].num, stu[i].name);
			for (j = 0; j < m; j++)
			{
				printf("%10.2f", stu[i].score[j]);
			}
			printf("%10.2f%10.2f\n", stu[i].sum, stu[i].aver);
			flag = 0;
		}
	}
	if (flag)
	{
		printf("未找到这个姓名对应的学生记录\n");
	}
}
void ModifyRecord(STU stu[], int n, int m)
{
	int i, j;
	long id;
	char ch;
	printf("请输入需要修改信息对应的学号：");
	scanf("%ld", &id);
	for (i = 0; i < n; i++)
	{
		if (stu[i].num == id)
		{
			printf("找到了该生记录，信息为:\n");
			printf("%10ld%15s", stu[i].num, stu[i].name);
			for (j = 0; j < m; j++)
			{
				printf("%10.2f", stu[i].score[j]);
			}
			printf("%10.2f%10.2f\n", stu[i].sum, stu[i].aver);
			printf("请确认是否需要修改？（Y/y或N/n）：");
			getchar();
			scanf("%c", &ch);
			if (ch == 'Y' || ch == 'y')
			{
				printf("请输入要修改的学生信息：");
				scanf("%ld%s", &stu[i].num, stu[i].name);
				stu[i].sum = 0;
				for (j = 0; j < m; j++)
				{
					scanf("%f", &stu[i].score[j]);
					stu[i].sum += stu[i].score[j];
				}
				stu[i].aver = stu[i].sum / m;
				printf("修改完毕\n");


			}
			else if (ch == 'N' || ch == 'n')
			{
				printf("找到了该学生记录，但不能修改\n");

			}
			else {
				printf("输入错误！\n");
			}
		}
	}
	printf("未找到该生记录！\n");
}
void CalculateScoreOfStudent(STU stu[], int n, int m)
{
	int i, j;
	printf("每个学生各门课程的总分和平均分为：\n");
	for (i = 0; i < n; i++)
	{
		stu[i].sum = 0;
		for (j = 0; j < m; j++)
		{
			stu[i].sum += stu[i].score[j];
		}
		stu[i].aver = stu[i].sum / m;
		printf("第%d个学生：总分=%.2f，平均分=%.2f\n", i + 1, stu[i].sum, stu[i].aver);
	}
}
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
int main()
{
	int n = 0;
	int m = 0;
	int i, j;
	char ch;
	int first = 1;
	STU stu[STU_NUM];
	system("mode con cols=130 Lines=60");
	system("color 0E");
	while (1)
	{
		system("cls");
		ch = Menu();
		switch (ch) {
		case 1:
			system("cls");
			InputRecord(stu,&n, &m);
			break;
		case 2:
			system("cls");
			if (first)
			{
				printf("系统中尚无学生成绩信息，请先输入！\n");
				system("pause");
				break;
			}
			AppendRecord(stu, &n, m);
			system("pause");
			break;
		case 3:
			system("cls");
			if (first)
			{
				printf("系统中尚无学生成绩信息，请先输入！\n");
				system("pause");
				break;
			}
			DeleteRecord(stu, &n, m);
			system("pause");
			break;
			break;
		case 4:
			system("cls");
			if (first)
			{
				printf("系统中尚无学生成绩信息，请先输入！\n");
				system("pause");
				break;
			}
			SearchbyNumber(stu, n, m);
			system("pause");
			break;
		case 5:
			system("cls");
			if (first)
			{
				printf("系统中尚无学生成绩信息，请先输入！\n");
				system("pause");
				break;
			}
			SearchbyName(stu, n, m);
			system("pause");
			break;
		case 6:
			system("cls");
			if (first)
			{
				printf("系统中尚无学生成绩信息，请先输入！\n");
				system("pause");
				break;
			}
			ModifyRecord(stu, n, m);
			system("pause");
			break;
		case 7:
			system("cls");
			if (first)
			{
				printf("系统中尚无学生成绩信息，请先输入！\n");
				system("pause");
				break;
			}
			CalculateScoreOfStudent(stu, n, m);
			system("pause");
			break;
		case 8:
			system("cls");
			if (first)
			{
				SetPosition(POS_X3, POS_Y);
				printf("系统中尚无学生成绩信息，请先输入！\n");
				getch();
				break;
			}
			CalculateScoreOfCourse(stu, n, m);
			getch();
			break;
		case 9:
			break;
		case 10:
			break;
		case 11:
			break;
		case 12:
			break;
		case 13:
			break;
		case 14:
			break;
		case 15:
			break;
		case 16:
			break;
		case 0:
			break;
		default:
			break;
		}
	}
}