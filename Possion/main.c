#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

void addPath(int *start, int number,int length);
int* move(int *start,int length);
bool contain(int *start);


int ** path;
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
	move(start,0);
	
	system("pause");
	return 0;
}

void goPath() {

	for (int i = 0; i < number; i++) {
		
		while (true) {
			move(start,0);
		}
	}

}

int* move(int *start,int length) {
	int number = 0;
	for (int i = 1; i <= *start; i++) {
		for (int j = 1; j <= *start; j++) {

			int a = start[i], b = start[j];
			if (i == j || start[i] == 0 || start[j] == max[j]) {
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

			if (start[i] != a && !contain(start)) {
				printf("%d->%d: ", i, j);
				for (int k = 1; k <= *start; k++) {
					printf("%d ", start[k]);
				}
				addPath(start,number,length);
				number++;
			}
			printf("\n");
			start[i] = a;
			start[j] = b;

		}
	}
	return start;
}

void addPath(int *start,int number,int length) {
	length++;
	path = (int **)realloc(path,number * sizeof(int *));
	for (int i = 0; i < length; i++) {
		path[i] = (int *)realloc(path[i], (*start + 1)*length * sizeof(int));
	}

	//path[number] = (int *)realloc(path[number],(*start+1)*length*sizeof(int));
	for (int i = 0; i <= *start; i++) {
		path[number][(*start + 1)*length + i] = start[i];
	}

}

bool contain(int *start) {
	return false;
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