#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable: 4996)
#include"main.h"

int Menu_Teacher(void)
{
	int posy = 5;
	int option;
	int i, j;
	SetPosition(POS_X3, posy);
	printf("学生成绩管理系统\n");
	for (i = 0; i < 2; i++)
	{
		SetPosition(POS_X1, ++posy);
		for (j = 0; j < 55; j++)
		{
			printf("-");
		}
	}
	SetPosition(POS_X1, ++posy);
	printf("1.输入学生信息");
	SetPosition(POS_X4, posy);
	printf("2.增加学生信息");
	SetPosition(POS_X1, posy += 2);
	printf("3.删除学生信息");
	SetPosition(POS_X4, posy);
	printf("4.按学号查找记录");
	SetPosition(POS_X1, posy += 2);
	printf("5.按姓名查找记录");
	SetPosition(POS_X4, posy);
	printf("6.修改学生信息");
	SetPosition(POS_X1, posy += 2);
	printf("7.计算学生成绩");
	SetPosition(POS_X4, posy);
	printf("8.计算课程成绩");
	SetPosition(POS_X1, posy += 2);
	printf("9.按学号排序");
	SetPosition(POS_X4, posy);
	printf("10.按姓名排序");
	SetPosition(POS_X1, posy += 2);
	printf("11.按总成绩升序排列");
	SetPosition(POS_X4, posy);
	printf("12.按总成绩降序排名");
	SetPosition(POS_X1, posy += 2);
	printf("13.学生成绩统计");
	SetPosition(POS_X4, posy);
	printf("14.打印学生记录");
	SetPosition(POS_X1, posy += 2);
	printf("15.学生记录存盘");
	SetPosition(POS_X4, posy);
	printf("16.从磁盘读取学生记录");
	SetPosition(POS_X1, posy += 2);
	printf("17.切换身份");
	SetPosition(POS_X4, posy);
	printf("0.退出");
	for (i = 0; i < 2; i++)
	{
		SetPosition(POS_X1, ++posy);
		for (j = 0; j < 55; j++)
		{
			printf("-");
		}
	}
	SetPosition(POS_X1, ++posy);
	printf("请选择你想要进行的操作[0~16]:[  ]\b\b\b");
	scanf("%d", &option);
	return option;
}

int Menu_Student(void)
{
	int posy = 2;
	int option;
	int i, j;
	SetPosition(POS_X3, posy);
	printf("学生成绩管理系统\n");
	for (i = 0; i < 2; i++)
	{
		SetPosition(POS_X1, ++posy);
		for (j = 0; j < 55; j++)
		{
			printf("-");
		}
	}
	SetPosition(POS_X2, ++posy);
	printf("1.按学号查找记录");
	SetPosition(POS_X2, posy += 2);
	printf("2.按姓名查找记录");
	SetPosition(POS_X2, posy += 2);
	printf("3.按学号排序");
	SetPosition(POS_X2, posy += 2);
	printf("4.按姓名排序");
	SetPosition(POS_X2, posy += 2);
	printf("5.按总成绩升序排列");
	SetPosition(POS_X2, posy += 2);
	printf("6.按总成绩降序排名");
	SetPosition(POS_X2, posy += 2);
	printf("7.打印学生记录");
	SetPosition(POS_X2, posy += 2);
	printf("8.从磁盘读取学生记录");
	SetPosition(POS_X2, posy += 2);
	printf("9.切换身份");
	SetPosition(POS_X2, posy += 2);
	printf("0.退出");
	for (i = 0; i < 2; i++)
	{
		SetPosition(POS_X1, ++posy);
		for (j = 0; j < 55; j++)
		{
			printf("-");
		}
	}
	SetPosition(POS_X1, ++posy);
	printf("请选择你想要进行的操作[0~16]:[  ]\b\b\b");
	scanf("%d", &option);
	if (option == 1)option = 4;
	else if (option == 2)option = 5;
	else if (option == 3)option = 9;
	else if (option == 4)option = 10;
	else if (option == 5)option = 11;
	else if (option == 6)option = 12;
	else if (option == 7)option = 14;
	else if (option == 8)option = 16;
	else if (option == 9)option = 17;
	else option = -1;
	return option;
}

void SetPosition(int x, int y)
{
	HANDLE hOut;
	COORD pos;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);
}

void InputRecord(STU* head, int* n, int* m)
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
	STU* current = NULL;
	STU* pre = NULL;
	for (i = 0; i < *n; i++)
	{
		current = (STU*)malloc(sizeof(STU));
		if (head->next == NULL)
			head->next = current;
		else
			pre->next = current;
		current->next = NULL;
		SetPosition(POS_X2, ++posy);
		printf("输入第%d个学生信息：\t", i + 1);
		scanf("%ld%s", &current->num, current->name);
		for (j = 0; j < *m; j++)
		{
			scanf("%f", &current->score[j]);
		}
		pre = current;
	}
}
void AppendRecord(STU* head, int* n, int m)
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
	STU* current = head;
	STU* pre = NULL;
	while (current != NULL)
		current = current->next;
	for (i = *n; i < *n + num_record; i++)
	{
		current = (STU*)malloc(sizeof(STU));
		if (pre != NULL)
			pre->next = current;
		current->next = NULL;
		printf("输入第%d个学生信息：\t", i + 1);
		scanf("%ld%s", &current->num, current->name);
		for (j = 0; j < m; j++)
		{
			scanf("%f", &current->score[j]);
		}
		pre = current;
	}
	*n = *n + num_record;
	printf("添加完毕！\n");
}
void DeleteRecord(STU* head, int* n, int m)
{
	int i, j;
	long id;
	char ch;
	printf("请输入你要删除学生信息对应的学号：");
	scanf("%ld", &id);
	STU* current = head->next;
	STU* pre = NULL;
	for (i = 0; i < *n; i++)
	{
		if (current->num == id)
		{
			printf("找到了该生记录，信息为:\n");
			printf("%10ld%15s", current->num, current->name);
			for (j = 0; j < m; j++)
			{
				printf("%10.2f", current->score[j]);
			}
			printf("%10.2f%10.2f\n", current->sum, current->name);
			printf("请确认是否需要删除这条记录？（Y/y或N/n）：");
			getchar();
			scanf("%c", &ch);
			if (ch == 'Y' || ch == 'y')
			{
				pre->next = current->next;
				current = current->next;
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
		else {
			pre = current;
			current = current->next;
		}
	}
	printf("未找到该生记录！\n");

}
void SearchbyNum(STU* head, int n, int m)
{
	long id;
	int i, j;
	flag = 1;
	printf("请输入你要查找的学生的学号：");
	scanf("%ld", &id);
	STU* current = head->next;
	for (i = 0; i < n; i++)
	{
		if (current->num == id)
		{
			printf("找到了，该学生对应的学生信息为:\n");
			printf("%10ld%15s", current->num, current->name);
			for (j = 0; j < m; j++)
			{
				printf("%10.2f", current->score[j]);
			}
			printf("%10.2f%10.2f", current->sum, current->aver);
			flag = 0;
			break;
		}
		else
		{
			current = current->next;
		}
	}
	if(flag)
		printf("未找到这个学号对应的学生记录\n");
}
void SearchbyName(STU* head, int n, int m)
{
	int flag = 1;
	int i, j;
	int k = 0;
	char name[NAME_LEN];
	printf("请输入你要查找的学生的姓名：");
	scanf("%s", name);
	STU* current = head->next;
	for (i = 0; i < n; i++)
	{
		if (strcmp(current->name, name) == 0)
		{
			printf("找到了，第%d学生信息为:\n", ++k);
			printf("%10ld%15s", current->num, current->name);
			for (j = 0; j < m; j++)
			{
				printf("%10.2f", current->score[j]);
			}
			printf("%10.2f%10.2f\n", current->sum, current->aver);
			flag = 0;
			break;
		}
		else
			current = current->next;
	}
	if (flag)
	{
		printf("未找到这个姓名对应的学生记录\n");
	}
}
void ModifyRecord(STU* head, int n, int m)
{
	int i, j;
	long id;
	char ch;
	printf("请输入需要修改信息对应的学号：");
	scanf("%ld", &id);
	STU* current = head->next;
	for (i = 0; i < n; i++)
	{
		if (current->num == id)
		{
			printf("找到了该生记录，信息为:\n");
			printf("%10ld%15s", current->num, current->name);
			for (j = 0; j < m; j++)
			{
				printf("%10.2f", current->score[j]);
			}
			printf("%10.2f%10.2f\n", current->sum, current->aver);
			printf("请确认是否需要修改？（Y/y或N/n）：");
			getchar();
			scanf("%c", &ch);
			if (ch == 'Y' || ch == 'y')
			{
				printf("请输入要修改的学生信息：");
				scanf("%ld%s", &current->num, current->name);
				current->sum = 0;
				for (j = 0; j < m; j++)
				{
					scanf("%f", &current->score[j]);
					current->sum += current->score[j];
				}
				current->aver = current->sum / m;
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
void CalculateScoreOfStudent(STU* head, int n, int m)
{
	int i, j;
	STU* current = head->next;
	printf("每个学生各门课程的总分和平均分为：\n");
	for (i = 0; i < n; i++)
	{
		current->sum = 0;
		for (j = 0; j < m; j++)
		{
			current->sum += current->score[j];
		}
		current->aver = current->sum / m;
		printf("第%d个学生：总分=%.2f，平均分=%.2f\n", i + 1, current->sum, current->aver);
		current = current->next;
	}
}

void CalculateScoreOfCourse(STU* head, int n, int m)
{
	int i, j;
	float sum[COURSE_NUM], aver[COURSE_NUM];
	int posy = 7;
	SetPosition(POS_X1, posy);
	printf("各门课程的总分和平均分的计算结果为：");
	STU* current = head->next;
	for (j = 0; j < m; j++)
	{
		current = head->next;
		sum[j] = 0;
		for (i = 0; i < n; i++) {
			sum[j] += current->score[j];
			current = current->next;
		}
		aver[j] = sum[j] / n;
		SetPosition(POS_X1, ++posy);
		printf("第%d门课程：总分=%.2f，平均分=%.2f\n", j + 1, sum[j], aver[j]);
	}
}

void SortbyNum( STU* head, int n, int m) {
	int i, j;
	STU* temp, * current;
	for (i = 0; i < n; i++) {
		current = head->next;
		temp = head->next;
		for (j = 0; j < n - i - 1; j++) {
			if (current->num > current->next->num) {
				if (current == head->next) {
					head->next = current->next;
					temp = current->next;
					current->next = temp->next;
					temp->next = current;
				}
				else {
					temp->next = current->next;
					current->next = current->next->next;
					temp->next->next = current;
					temp = temp->next;
				}
			}
			else {
				temp = current;
				current = current->next;
			}
		}
	}
	printf("按学号从小到大对学生记录排序完毕");
}


int Descending(float a, float b) {
	return a > b;
}

int Ascending(float a, float b) {
	return a < b;
}

void SortbyScore(STU* head, int n, int m, int(*compare)(float a, float b)) {
	int i, j;
	STU* temp, * current;

	for (i = 0; i < n; i++) {
		current = head->next;
		temp = head->next;
		for (j = 0; j < n - i - 1; j++) {
			if ((*compare)(current->sum, current->next->sum)) {
				if (current == head->next) {
					head->next = current->next;
					temp = current->next;
					current->next = temp->next;
					temp->next = current;
				}
				else {
					temp->next = current->next;
					current->next = current->next->next;
					temp->next->next = current;
					temp = temp->next;
				}
			}
			else {
				temp = current;
				current = current->next;
			}
		}
	}
	printf("按学生成绩总分对学生记录排序完毕\n");
}

void SortbyName(STU* head, int n, int m) {
	int i, j;
	STU* temp, * current;

	for (i = 0; i < n; i++) {
		current = head->next;
		temp = head->next;
		for (j = 0; j < n - i - 1; j++) {
			if (strcmp(current->name, current->next->name) > 0) {
				if (current == head->next) {
					head->next = current->next;
					temp = current->next;
					current->next = temp->next;
					temp->next = current;
				}
				else {
					temp->next = current->next;
					current->next = current->next->next;
					temp->next->next = current;
					temp = temp->next;
				}
			}
			else {
				temp = current;
				current = current->next;
			}
		}
	}
	printf("按姓名字典对学生记录排序完毕\n");
}

void StatisticAnalysis(STU* head, int n, int m)
{
	int i, j, t[6];
	STU* current = head->next;
	for (j = 0; j < m; j++)
	{
		printf("\n课程%d成绩统计结果为：\n", j + 1);
		printf("分数段\t人数\t占比\n");

		memset(t, 0, sizeof(t));
		for (i = 0; i < n; i++)
		{
			if (current->score[j] >= 0 && current->score[j] < 60)
				t[0]++;
			else if (current->score[j] < 70)
				t[1]++;
			else if (current->score[j] < 80)
				t[2]++;
			else if (current->score[j] < 90)
				t[3]++;
			else if (current->score[j] < 100)
				t[4]++;
			else if (current->score[j] == 100)
				t[5]++;
			current = current->next;
		}
		current = head->next;
		for (i = 0; i < 6; i++)
		{
			if (i == 0)
				printf("<60\t%d\t%.2f%%\n", t[i], (float)t[i] / n * 100);
			else if (i == 5)
				printf("100\t%d\t%.2f%%\n", t[i], (float)t[i] / n * 100);
			else
				printf("%d-%d\t%d\t%.2f%%\n", (i + 5) * 10, (i + 5) * 10 + 9, t[i], (float)t[i] / n * 100);
		}
	}
	printf("\n学生成绩平均分统计结果为：\n");
	printf("分数段\t人数\t占比\n");
	memset(t, 0, sizeof(t));
	current = head->next;
	for (i = 0; i < n; i++)
	{
		if (current->aver >= 0 && current->aver < 60)
			t[0]++;
		else if (current->aver < 70)
			t[1]++;
		else if (current->aver < 80)
			t[2]++;
		else if (current->aver < 90)
			t[3]++;
		else if (current->aver < 100)
			t[4]++;
		else if (current->aver == 100)
			t[5]++;
		current = current->next;
	}
	for (i = 0; i < 6; i++)
	{
		if (i == 0)
			printf("<60\t%d\t%.2f%%\n", t[i], (float)t[i] / n * 100);
		else if (i == 5)
			printf("100\t%d\t%.2f%%\n", t[i], (float)t[i] / n * 100);
		else
			printf("%d-%d\t%d\t%.2f%%\n", (i + 5) * 10, (i + 5) * 10 + 9, t[i], (float)t[i] / n * 100);
	}
}


void WritetoFile(int n, int m, STU* head)
{
	int i, j;
	FILE* fp; 
	STU* current = head->next;
	if ((fp = fopen("./student.txt", "w")) == NULL)
	{
		printf("磁盘文件student.txt无法打开");
		return;
	}
	fprintf(fp, "%10d%10d\n", n, m);
	for (i = 0; i < n; i++)
	{
		fprintf(fp, "%10ld%10s\n", current->num, current->name);
		for (j = 0; j < m; j++)
		{
			fprintf(fp, "%10.2f", current->score[j]);
		}
		fprintf(fp, "%10.2f%10.2f\n", current->sum, current->aver);
		current = current->next;
	}
	fclose(fp);
	printf("存盘完毕!\n");
}


int ReadfromFile(int* n, int* m, STU* head, int* first)
{
	FILE* fp;
	int i, j;
	int posy = 8;
	STU* current = head;
	SetPosition(POS_X1, posy);
	if ((fp = fopen("./student.txt", "r")) == NULL)
	{
		printf("磁盘文件student.txt无法打开");
		return 1;
	}
	fscanf(fp, "%10d%10d", n, m);
	for (i = 0; i < *n; i++)
	{
		current->next = (STU*)malloc(sizeof(STU));
		current = current->next;
		fscanf(fp, "%10ld", &(current->num));
		fscanf(fp, "%10s", current->name);
		for (j = 0; j < *m; j++)
		{
			fscanf(fp, "%f", &(current->score[j]));
		}
		fscanf(fp, "%f%f", &(current->sum), &(current->aver));
	}
	*first = 0;
	fclose(fp);
	printf("数据从磁盘读取完毕！");
	return 0;
}

void PrintRecord(STU* head, int n, int m)
{
	int i, j;
	STU* current = head->next;
	printf("学号\t\t姓名\t\t");
	for (j = 0; j < m; j++)
	{
		printf("课程%d\t\t", j + 1);
	}
	printf("总分\t\t平均分\n");

	for (i = 0; i < n; i++)
	{
		printf("%-16ld%-16s", current->num, current->name);
		for (j = 0; j < m; j++)
		{
			printf("%-16.2lf", current->score[j]);
		}
		printf("%-16.2lf%-16.2lf\n", current->sum, current->aver);
		current = current->next;
	}
	return;
}

void TidyupRecord(STU* head, int n, int m)
{
	int i, j;
	STU* current = head->next;
	for (i = 0; i < n; i++)
	{
		current->sum = 0;
		for (j = 0; j < m; j++)
		{
			current->sum += current->score[j];
		}
		current->aver = current->sum / (float)m;
		current = current->next;
	}
}

int Exchange_identity()
{
	int identity;
	SetPosition(POS_X2, 15);
	printf("1.老师");
	SetPosition(POS_X2, 17);
	printf("2.学生");
	SetPosition(POS_X2, 23);
	printf("请选择你想要选择的身份:[  ]\b\b\b");
	scanf("%d", &identity);
	if (identity == 1)
	{
		system("cls");
		printf("成功选择身份：老师");
	}
	else if (identity == 2)
	{
		system("cls");
		printf("成功选择身份：学生");
	}
	else
	{
		system("cls");
		printf("选择身份失败");
	}
	return identity;
}