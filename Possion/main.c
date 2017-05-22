#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

void goPath(int *start);
int addPath(int *start, int temp, int number, int length);
int move(int *start, int length,int nownum);
bool contain(int *start, int number, int length);
bool isequal(int *start, int  *end);
void printPath();


int path[1024][1024];
int number = 0;
int *max, *start, *end;

int main() {
	/*do {
	printf("请输入各瓶子最多装酒数量,用空格隔开(例如:1 2 3):\n");
	max = get_bottles();
	printf("请输入各瓶子初始装酒数量,用空格隔开(例如:1 2 3):\n");
	start= get_bottles();
	printf("请输入各瓶子要求装酒数量,用空格隔开(例如:1 2 3):\n");
	end = get_bottles();
	} while (check(maxVolume[0], iniVolume[0], demandVolume[0]));*/
	int maxm[4] = { 3,12,8,5 };
	int ini[4] = { 3,12,0,0 };
	int dem[4] = { 3,6,6,0 };
	max = maxm, start = ini, end = dem;
	goPath(start);
	printPath();
	system("pause");
	return 0;
}

void goPath(int *start) {
	addPath(start, 0, 0, 0);


	/*move(start, 1, 0);
	int ini[4] = { 3,4,8,0 };
	start = ini;
	move(start, 2, 0);
	int ini1[4] = {3,7,0,5 };
	start = ini1;
	move(start, 2, 1);*/

	//int branch=move(start, 1,0);


	for (int i = 0; i <= number; i++) {
		if (i == number) {
			i = 0;
		}
		int length = path[number][0];
		int ini[10];
		start = &path[number][2 + (length - 1)*(*start + 1)];
		memcpy(ini, start, (*start + 1) * sizeof(int));		
		move(ini, length, path[number][1]);
		if (number == 13) {
			break;
		}
	}

	printf("%d\n", number);

}

int move(int *start, int length,int nownum) {
	int branch = 0;

	for (int i = 1; i <= *start; i++) {
		for (int j = 1; j <= *start; j++) {

			int a = start[i], b = start[j];
			if (i == j || start[i] == 0 || start[j] == max[j]) {
				if (isequal(start, end)) {
					printf("\n移动完成\n");
				}
				continue;
			}
			else if (start[i] > max[j] - start[j]) {
				start[i] -= max[j] - start[j];
				start[j] = max[j];
			}
			else {
				start[j] += start[i];
				start[i] = 0;
			}

			if (start[i] != a && !contain(start, nownum, length)) {
				/*printf("%d->%d: ", i, j);
				for (int k = 1; k <= *start; k++) {
					printf("%d ", start[k]);
				}*/
				if (!branch) {
					addPath(start, nownum, nownum, length);
				}
				else {
					number++;
					addPath(start, nownum, number, length);
				}
				branch++;
			}
			//printf("\n");
			start[i] = a;
			start[j] = b;

		}
	}
	return branch;
}

int addPath(int *start, int nownum, int number, int length) {
	path[nownum][0] = length+1;
	if (length&&number != nownum) {
		for (int i = 0; i < (*start + 1)*length + 2; i++) {
			path[number][i] = path[nownum][i];
		}
	}

	for (int i = 0; i <= *start; i++) {
		path[number][1] = number;  //可以放for前面
		path[number][(*start + 1)*length + i + 2] = start[i];
	}
	length++;
	return length;
}

bool contain(int *start, int number, int length) {
	bool mark;
	for (int i = 0; i < length; i++) {
		for (int j = 1; j <= *start; j++) {
			if (path[number][(*start + 1)*i + j+2] == start[j]) {
				mark = true;
			}
			else {
				mark = false;
				break;
			}
		}
		if (mark) {
			return true;
		}
	}
	return false;
}

bool isequal(int *start, int  *end) {
	for (int i = 1; i <= *end; i++) {
		if (start[i] != end[i]) {
			return false;
		}
	}

	return true;
}

void printPath() {
	int numel = path[number][2]; //记录瓶子数
	FILE *fp = fopen("path.txt", "w");
	for (int i = 0; i <= number; i++) {
		for (int j = 0; j < path[i][0]; j++) {
			for (int k = 0; k < numel; k++) {
				printf("%4d ", path[i][(numel + 1)*j + 3+k]);
				fprintf(fp, "%4d ", path[i][(numel + 1)*j + 3 + k]);
			}
			printf("\n");
			fprintf(fp, "\n");
		}
		printf("\n\n");
		fprintf(fp, "\n\n");
	}
	fclose(fp);
}












int * get_bottles() {
	int num = 256; //设置读入数据初始容量
	int *bottles = malloc(num * sizeof(int));
	char ch = getchar();

	int i = 1;  //保留i=0时 设置bottles所含数据数量
	int temp = 0;
	while (ch != '\n') {
		if (i > num) {
			num *= 2;
			bottles = realloc(bottles, num * sizeof(int));
			if (num > 1024) {
				printf("数据量超过上限");
				break;
			}
		}

		if (ch == ' ') {
			temp = 0;
			i++;
		}
		else {
			ch -= '0';
			temp = temp * 10 + ch;
			bottles[i] = temp;
		}

		ch = getchar();
	}
	bottles[0] = i;  //设置bottles数量
	return bottles;
}

bool check(int a, int b, int c) {
	if (a == b&&b == c) {
		return false;
	}
	else {
		printf("\n输入数据有误,请重新输入\n");
		return true;
	}
}