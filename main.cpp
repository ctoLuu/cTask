#define _CRT_SECURE_NO_WARNINGS 1
#include"snake.h"
Snake snake;
Food food, junk_food[5], all_junk_food[1000];
Obstacle row_obstacle[5], col_obstacle[5], all_obstacle[40];
char now_Dir = RIGHT;
char direction = RIGHT;
int obs_num = 0;
int junk_food_num = 0;

int Menu()
{
	GotoXY(40, 12);
	printf("欢迎来到贪吃蛇小游戏");
	GotoXY(43, 14);
	printf("1、开始游戏");
	GotoXY(43, 16);
	printf("2、帮助");
	GotoXY(43, 18);
	printf("3、关于");
	GotoXY(43, 20);
	printf("其他任意键退出游戏");
	Hide();
	char ch;
	int result = 0;
	ch = _getch();
	switch (ch)
	{
	case '1':
		result = 1;
		break;
	case '2':
		result = 2;
		break;
	case '3':
		result = 3;
		break;

	}
	system("cls");
	return result;
}
void GotoXY(int x, int y)
{
	HANDLE hout;
	COORD cor;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	cor.X = x;
	cor.Y = y;
	SetConsoleCursorPosition(hout, cor);
}
void Hide()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cor_info = { 1, 0 };
	SetConsoleCursorInfo(hout, &cor_info);
}
void About()
{
	GotoXY(30, 12);
	printf("综合实践案例");
	GotoXY(43, 14);
	printf("贪吃蛇游戏");
	GotoXY(43, 16);
	printf("按任意键返回上级目录");
	Hide();
	char ch = _getch();
	system("cls");
}
void Help()
{
	GotoXY(40, 12);
	printf("w 上");
	GotoXY(40, 14);
	printf("s 下");
	GotoXY(40, 16);
	printf("a 左");
	GotoXY(40, 18);
	printf("d 右");
	GotoXY(40, 20);
	printf("当蛇撞到障碍物时游戏结束");
	GotoXY(45, 22);
	printf("按任意键返回上级目录");
	Hide();
	char ch = _getch();
	system("cls");
}
void InitMap()
{
	Hide();
	snake.snakeNode[0].x = MAP_WIDTH / 2 - 1;
	snake.snakeNode[0].y = MAP_HEIGHT / 2 - 1;
	GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);
	printf("@");
	snake.length = 3;
	snake.speed = 150;
	now_Dir = RIGHT;
	for (int i = 1; i < snake.length; i++) {
		snake.snakeNode[i].y = snake.snakeNode[i - 1].y;
		snake.snakeNode[i].x = snake.snakeNode[i - 1].x - 1;
		GotoXY(snake.snakeNode[i].x, snake.snakeNode[i].y);
		printf("o");
	}
	for (int i = 0; i < MAP_HEIGHT; i++) {
		GotoXY(0, i);
		printf("|");
		GotoXY(MAP_WIDTH - 1, i);
		printf("|");
	}
	for (int i = 1; i < MAP_WIDTH - 1; i++)
	{
		GotoXY(i, 0);
		printf("—");
		GotoXY(i, MAP_HEIGHT - 1);
		printf("—");
	}
	PrintObstacle();
	PrintFood();
	GotoXY(105, 5);
	printf("当前得分：00");
}
void PrintObstacle()
{
	int flag = 1;
	while (flag)
	{
		flag = 0;
		for (int i = 0; i < 5; i++) {
			row_obstacle[i].x = rand() % (MAP_WIDTH - 2) + 1;
			row_obstacle[i].y = rand() % (MAP_HEIGHT - 2) + 1;
		}
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k <= snake.length - 1; k++) {
				if (snake.snakeNode[k].y == row_obstacle[j].y && (snake.snakeNode[k].x == row_obstacle[j].x || snake.snakeNode[k].x == row_obstacle[j].x+1 || snake.snakeNode[k].x == row_obstacle[j].x+2 || snake.snakeNode[k].x == row_obstacle[j].x+3) || row_obstacle[j].x+4 >= MAP_WIDTH)
				{
					flag = 1;
					break;
				}
			}
			if (flag)
				break;
		}
	}
	for (int j = 0; j < 5; j++) {
		GotoXY(row_obstacle[j].x, row_obstacle[j].y);
		printf("####");
		
		for (int i = 0; i < 4; i++) {
			all_obstacle[obs_num].x = row_obstacle[j].x+i;
			all_obstacle[obs_num].y = row_obstacle[j].y;
			obs_num++;
		}
		
	}
	flag = 1;
	while (flag)
	{
		flag = 0;
		for (int i = 0; i < 5; i++) {
			col_obstacle[i].x = rand() % (MAP_WIDTH - 2) + 1;
			col_obstacle[i].y = rand() % (MAP_HEIGHT - 2) + 1;
		}
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k <= snake.length - 1; k++) {
				if (snake.snakeNode[k].x == col_obstacle[j].x &&( snake.snakeNode[k].y == col_obstacle[j].y || snake.snakeNode[k].y == col_obstacle[j].y + 1 || snake.snakeNode[k].y == col_obstacle[j].y + 2 || snake.snakeNode[k].y == col_obstacle[j].y + 3) || col_obstacle[j].y + 4 >= MAP_HEIGHT)
				{
					flag = 1;
					break;
				}
			}
			if (flag)
				break;
		}
	}
	for (int j = 0; j < 5; j++) {
		for (int k = 0; k < 4; k++) {
			GotoXY(col_obstacle[j].x, col_obstacle[j].y + k);
			printf("#");
			all_obstacle[obs_num].x = col_obstacle[j].x;
			all_obstacle[obs_num].y = col_obstacle[j].y+k;
			obs_num++;
		}
	}
}
void PrintFood() {
	int flag = 1;
	while (flag)
	{
		flag = 0;
		for (int i = 0; i < 4; i++) {
			while (!flag) {
				flag = 1;
				junk_food[i].x = rand() % (MAP_WIDTH - 2) + 1;
				junk_food[i].y = rand() % (MAP_HEIGHT - 2) + 1;
				for (int j = 0; j < obs_num; j++) {
					if (junk_food[i].x == all_obstacle[j].x && junk_food[i].y == all_obstacle[j].y) {
						flag = 0;
						break;
					}
				}
			}
			flag = 0;
			all_junk_food[junk_food_num].x = junk_food[i].x;
			all_junk_food[junk_food_num].y = junk_food[i].y;
			junk_food_num++;
		}
		
		for (int j = 0; j < 4; j++) {
			flag = 0;
			for (int k = 0; k <= snake.length - 1; k++) {
				if (snake.snakeNode[k].x == junk_food[j].x && snake.snakeNode[k].y == junk_food[j].y)
				{
					flag = 1;
					break;
				}
			}
			if (!flag) {
				GotoXY(junk_food[j].x, junk_food[j].y);
				printf("=");
			}
		}
	}

	flag = 1;
	while (flag)
	{
		flag = 0;
		while (!flag) {
			flag = 1;
			food.x = rand() % (MAP_WIDTH - 2) + 1;
			food.y = rand() % (MAP_HEIGHT - 2) + 1;
			for (int j = 0; j < junk_food_num; j++) {
				if (food.x == all_junk_food[j].x && food.y == all_junk_food[j].y) {
					flag = 0;
					break;
				}
			}
			for (int j = 0; j < obs_num; j++) {
				if (food.x == all_obstacle[j].x && food.y == all_obstacle[j].y) {
					flag = 0;
					break;
				}
			}
		}
		flag = 0;
		for (int k = 0; k <= snake.length - 1; k++)
		{
			if (snake.snakeNode[k].x == food.x && snake.snakeNode[k].y == food.y)
			{
				flag = 1;
				break;
			}
		}
	}
	GotoXY(food.x, food.y);
	printf("$");
}
int MoveSnake()
{
	Snakenode temp;
	int flag = 0;
	temp = snake.snakeNode[snake.length - 1];
	for (int i = snake.length - 1; i >= 1; i--)
	{
		snake.snakeNode[i] = snake.snakeNode[i - 1];
	}
	if (snake.length != 1) {
		GotoXY(snake.snakeNode[1].x, snake.snakeNode[1].y);
		printf("o");
	}
	if (_kbhit())
	{
		direction = _getch();
		switch (direction)
		{
		case UP:
			if (now_Dir != DOWN)
				now_Dir = direction;
			break;
		case DOWN:
			if (now_Dir != UP)
				now_Dir = direction;
			break;
		case LEFT:
			if (now_Dir != RIGHT)
				now_Dir = direction;
			break;
		case RIGHT:
			if (now_Dir != LEFT)
				now_Dir = direction;
			break;

		}
	}
	switch (now_Dir) {
	case UP:
		snake.snakeNode[0].y--;
		break;
	case DOWN:
		snake.snakeNode[0].y++;
		break;
	case LEFT:
		snake.snakeNode[0].x--;
		break;
	case RIGHT:
		snake.snakeNode[0].x++;
		break;

	}
	GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);
	printf("@");
	if (snake.snakeNode[0].x == food.x && snake.snakeNode[0].y == food.y) {
		snake.length++;
		flag = 1;
		snake.snakeNode[snake.length - 1] = temp;
	}
	
	if (!flag)
	{
		GotoXY(temp.x, temp.y);
		printf(" ");
		for (int i = 0; i < junk_food_num; i++) {
			if (snake.snakeNode[0].x == all_junk_food[i].x && snake.snakeNode[0].y == all_junk_food[i].y) {
				
				temp = snake.snakeNode[snake.length - 1];
				GotoXY(temp.x, temp.y);
				printf(" ");
				
				snake.length--;

				GotoXY(105, 5);
				if (snake.length - 3 < 10) {
					if (snake.length - 3 < 0) {
						if (snake.length -3 == -2)
						{
							obs_num = 0;
							junk_food_num = 0;
							system("cls");
							GotoXY(45, 14);
							printf("最终得分：%d", snake.length - 3);
							GotoXY(45, 16);
							printf("Your Snake Died！");
							GotoXY(45, 18);
							printf("按任意键返回主菜单");
							char c = _getch();
							system("cls");
							return 0;
						}
						printf("当前得分：%d", snake.length - 3);
					}
					else
						printf("当前得分：0%d", snake.length - 3);
				}
				else {
					printf("当前得分：%d", snake.length - 3);
				}
				break;
				
			}
		}
	}
	else {
		PrintFood();
		GotoXY(105, 5);
		if (snake.length - 3 < 10) {
			printf("当前得分：0%d", snake.length - 3);
		}
		else
			printf("当前得分：%d", snake.length - 3);
	}
	if (!IsCorrect())
	{
		obs_num = 0;
		junk_food_num = 0;
		system("cls");
		GotoXY(45, 14);
		printf("最终得分：%d", snake.length - 3);
		GotoXY(45, 16);
		printf("你输了！");
		GotoXY(45, 18);
		printf("按任意键返回主菜单");
		char c = _getch();
		system("cls");
		return 0;
	}
	SpeedControl();
	Sleep(snake.speed);
	return 1;
}
int IsCorrect()
{
	if (snake.snakeNode[0].x == 0 || snake.snakeNode[0].y == 0 || snake.snakeNode[0].x == MAP_WIDTH - 1 || snake.snakeNode[0].y == MAP_HEIGHT - 1)
		return 0;
	for (int i = 0; i < obs_num; i++) {
		if (snake.snakeNode[0].x == all_obstacle[i].x && snake.snakeNode[0].y == all_obstacle[i].y)
			return 0;
	}
	for (int i = 1; i < snake.length; i++)
	{
		if (snake.snakeNode[0].x == snake.snakeNode[i].x && snake.snakeNode[0].y == snake.snakeNode[i].y)
		{
			for (int j = i; j < snake.length; j++)
			{
				GotoXY(snake.snakeNode[j].x, snake.snakeNode[j].y);
				printf(" ");
			}
			snake.length = i;
			GotoXY(105, 5);
			if (snake.length - 3 < 10) {
				printf("当前得分：0%d", snake.length - 3);
			}
			else
				printf("当前得分：%d", snake.length - 3);
			return 1;
		}

	}
	return 1;
} 
void SpeedControl()
{
	switch (snake.length)
	{
	case 6:
		snake.speed = 130;
		break;
	case 9:
		snake.speed = 110;
		break;
	case 12:
		snake.speed = 90;
		break;
	case 15:
		snake.speed = 70;
		break;
	case 18:
		snake.speed = 50;
		break;
	case 21:
		snake.speed = 40;
		break;
	case 24:
		snake.speed = 30;
		break;
	case 27:
		snake.speed = 20;
		break;
	case 30:
		snake.speed = 10;
		break;
	}
}
int main()
{
	srand((unsigned int)time(0));
	int end = 1, result;
	while (end) {
		result = Menu();
		switch (result) {
		case 1:
			InitMap();
			while (MoveSnake());
			break;
		case 2:
			Help();
			break;
		case 3:
			About();
			break;
		case 0:
			end = 0;
			break;
		}
	}
	return 0;
}