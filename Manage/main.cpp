#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable: 4996)
#include"main.h"

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
		TidyupRecord(stu, n, m);
		switch (ch) {
		case 1:
			system("cls");
			InputRecord(stu, &n, &m);
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
			SearchbyNum(stu, n, m);
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
			system("cls");
			if (first)
			{
				SetPosition(POS_X3, POS_Y);
				printf("系统中尚无学生成绩信息，请先输入！\n");
				getch();
				break;
			}
			SortbyNum(stu, n, m);
			getch();
			break;
		case 10:
			system("cls");
			if (first)
			{
				SetPosition(POS_X3, POS_Y);
				printf("系统中尚无学生成绩信息，请先输入！\n");
				getch();
				break;
			}
			SortbyName(stu, n, m);
			getch();
			break;
		case 11:
			system("cls");
			if (first)
			{
				SetPosition(POS_X3, POS_Y);
				printf("系统中尚无学生成绩信息，请先输入！\n");
				getch();
				break;
			}
			SortbyScore(stu, n, m, Descending);
			getch();
			break;
		case 12:
			system("cls");
			if (first)
			{
				SetPosition(POS_X3, POS_Y);
				printf("系统中尚无学生成绩信息，请先输入！\n");
				getch();
				break;
			}
			SortbyScore(stu, n, m, Ascending);
			getch();
			break;
		case 13:
			system("cls");
			if (first)
			{
				SetPosition(POS_X3, POS_Y);
				printf("系统中尚无学生成绩信息，请先输入！\n");
				getch();
				break;
			}
			StatisticAnalysis(stu, n, m);
			getch();
			break;
		case 14:
			system("cls");
			if (first)
			{
				SetPosition(POS_X3, POS_Y);
				printf("尚未输入学生信息或文件打开失败，请先检查！\n");
				getch();
				break;
			}
			PrintRecord(stu, n, m);
			getch();
			break;
		case 15:
			system("cls");
			WritetoFile(n, m, stu);
			getch();
			break;
		case 16:
			system("cls");
			if (ReadfromFile(&n, &m, stu, &first) || first)
			{
				SetPosition(POS_X3, POS_Y);
				printf("尚未输入学生信息或文件打开失败，请先检查！\n");
				getch();
				break;
			}
			getch();
			break;
		case 0:
			system("cls");
			printf("退出系统！\n");
			exit(0);
		default:
			system("cls");
			printf("输入出错，请重新选择操作！\n");
			system("pause");
		}
	}
	return 0;
}