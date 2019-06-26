#include <iostream>
#include <easyx.h>
#include <stdlib.h>
#include <Windows.h>
#define xleng 640
#define yleng 480
#define disk_length_max 160
#define disk_thickness ((yleng-40)/num)
#define disk_length_min 20
#define x1 ((xleng-disk_length_max)/4)
#define x2 (xleng/2)
#define x3 ((3*xleng+disk_length_max)/4)
//#define disk_length (disk_length_min+(disk_length_max-disk_length_min)*plate[i][j]/num)
using namespace std;

int** plate;
int num;
int pos[3] = { x1,x2,x3 };

int main()
{
	void disk_draw(int x, int y, int type);
	void show();
	void step_move(int s, int d);
	void move(int n, int s, int d, int m);

	plate = (int**)malloc(sizeof(int*)*3);
	cout << "please enter the number of disks:\n";
	cin >> num;
	for (int i = 0; i < 3; i++)
	{
		plate[i] = (int*)malloc(sizeof(int) * num);
		memset(plate[i], 0, sizeof(int) * num);
	}
	for (int i = 0; i < num; i++)
		plate[0][i] = num - i;
	initgraph(xleng, yleng, SHOWCONSOLE);
	setorigin(0, yleng);
	setaspectratio(1, -1);
	show();
	//step_move(0, 1);
	move(num, 0, 1, 2);
	free(plate);
	system("pause");
	return 0;
}

void disk_draw(int x,int y,int type)
{
	setlinecolor(type==0?BLACK:WHITE);
	int leng = disk_length_min+ (disk_length_max-disk_length_min)*plate[x][y]/num;
	line(pos[x]+0.5*leng,11+disk_thickness*y, pos[x] + 0.5 * leng,10+disk_thickness*(y+1));
	line(pos[x] - 0.5 * leng, 11 + disk_thickness * y, pos[x] - 0.5 * leng, 10 + disk_thickness * (y + 1));
	line(pos[x] - 0.5 * leng, 10 + disk_thickness *(y+1), pos[x] + 0.5 * leng, 10 + disk_thickness * (y + 1));
	setlinecolor(WHITE);
	line(pos[x], 10, pos[x], yleng);
}

void show()
{
	cleardevice();
	line(0,10,xleng,10);
	for (int i = 0; i < 3; i++)
	{
		line(pos[i],10,pos[i],yleng);
	}
	for (int i = 0; i <3; i++)
	{
		for (int j = 0; j < num; j++)
		{
			if (plate[i][j] != 0)
			{
				disk_draw(i, j, 1);
			}
		}
	}
}

int find_top(int x)
{
	int i = num - 1;
	for (; i >= 0; i--)
	{
		if (plate[x][i] != 0)
			break;
	}
	return i;
}

void step_move(int s, int d)
{
	disk_draw(s,find_top(s),0);
	plate[d][find_top(d) + 1] = plate[s][find_top(s)];
	plate[s][find_top(s)] = 0;
	disk_draw(d, find_top(d), 1);
	//Sleep(2000);
}                                                                                                                                                                                

void move(int n,int s,int d,int m)
{
	if (n == 2)
	{
		step_move(s, m);
		step_move(s, d);
		step_move(m, d);
	}
	else
	{
		move(n - 1, s, m, d);
		step_move(s, d);
		move(n - 1, m, d, s);
	}
}