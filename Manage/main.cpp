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
	int identity = 2;
	//STU stu[STU_NUM];
	STU* Head;
	Head = (STU*)malloc(sizeof(STU));
	Head->next = NULL;
	system("mode con cols=130 Lines=60");
	system("color 0E");
	while (1)
	{
		system("cls");
		if (identity==1)
		{
			ch = Menu_Teacher();
		}
		else if(identity == 2)
		{
			ch = Menu_Student();
		}
		TidyupRecord(Head, n, m);
		switch (ch) {
		case 1:
			system("cls");
			InputRecord(Head, &n, &m);
			break;
		case 2:
			system("cls");
			if (first)
			{
				printf("系统中尚无学生成绩信息，请先输入！\n");
				system("pause");
				break;
			}
			AppendRecord(Head, &n, m);
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
			DeleteRecord(Head, &n, m);
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
			SearchbyNum(Head, n, m);
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
			SearchbyName(Head, n, m);
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
			ModifyRecord(Head, n, m);
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
			CalculateScoreOfStudent(Head, n, m);
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
			CalculateScoreOfCourse(Head, n, m);
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
			SortbyNum(Head, n, m);
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
			SortbyName(Head, n, m);
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
			SortbyScore(Head, n, m, Descending);
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
			SortbyScore(Head, n, m, Ascending);
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
			StatisticAnalysis(Head, n, m);
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
			PrintRecord(Head, n, m);
			getch();
			break;
		case 15:
			system("cls");
			WritetoFile(n, m, Head);
			getch();
			break;
		case 16:
			system("cls");
			if (ReadfromFile(&n, &m, Head, &first) || first)
			{
				SetPosition(POS_X3, POS_Y);
				printf("尚未输入学生信息或文件打开失败，请先检查！\n");
				getch();
				break;
			}
			getch();
			break;
		case 17:
			system("cls");
			identity=Exchange_identity();
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