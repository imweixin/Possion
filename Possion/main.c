#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

bool check(int a, int b, int c);
int * get_bottles();
void move(int *start,int count);
void addPath(int *from);
bool contain(int *get);

int *max, *start, *end;
int *path;
int length=0; //定义路径长度

FILE * fp;

int main() {
	do {
	printf("请输入各瓶子最多装酒数量,用空格隔开(例如:1 2 3):\n");
	max = get_bottles();
	printf("请输入各瓶子初始装酒数量,用空格隔开(例如:1 2 3):\n");
	start = get_bottles();
	printf("请输入各瓶子要求装酒数量,用空格隔开(例如:1 2 3):\n");
	end = get_bottles();
	} while (check(*max, *start, *end));

	fp = fopen("path.txt", "w+");
	if (!fp) {
		printf("打开文件失败");
	}
	fclose(fp);
	/*int max[4] = { 3,12,8,5 };
	int start[4] = { 3,12,0,0 };
	int end[4] = { 3,6,6,0 };*/

	move(start,0);
	free(max);
	free(start);
	free(end);
	system("pause");
	return 0;
}

void move(int *start ,int count) {
	bool isMoved=false;
	path = (int *)realloc(path,(*start + 1)*(length+1) *sizeof(int));    //*start+3
	

	addPath(start);

	for (int i = 1; i <= *start; i++) {
		for (int j = 1; j <= *start; j++) {
			int a = start[i], b = start[j];      //临时变量,用于存储start[i]和start[j]的值
			if (i == j) {
				isMoved = false;
				continue;
			}
			if (start[i] == 0 || start[j] == max[j]) {
				isMoved = false;
				continue;
			}
			else if(start[i]>=max[j]-start[j]){
				start[i] -= max[j] - start[j];
				start[j] = max[j];
				if (contain(start)) {
					start[i] = a, start[j] = b;
					isMoved = false;
					continue;
				}
				else {
					isMoved = true;
				}
			}
			else {
				start[j] += start[i];
				start[i] = 0;
				if (contain(start)) {
					start[i] = a, start[j] = b;
					isMoved = false;
					continue;
				}
				else {
					isMoved = true;
				}
			}
			if (isMoved) {
				printf("%d->%d: ", i, j);
				for (int k = 1; k <= *start; k++) {
					printf("%d ", start[k]);
				}
				printf("\n");
			}

			fp = fopen("path.txt", "a+");
			fprintf(fp ,"%d->%d: ", i, j);
			for (int i = 1; i <= *start; i++) {
				fprintf(fp, "%d ", start[i]);
			}
			fprintf(fp, "\n");
			fclose(fp);

		}
	}
	
	printf("\n\n\n");
	/*free(path);
	path = (int*)malloc(sizeof(int));
	move(start, 0);
	count++;

	printf("%d\n",length);*/

}

void addPath(int *from) {
	for (int i = 0; i <= *from; i++) {
		path[(*start + 1)*length + i] = from[i];
	}
	length++;
}

bool contain(int *get) {
	bool mark;
	for (int i = 0; i < length; i++) {
		mark = true;
		for (int j = 1; j <= *get; j++) {
			if (path[i*(*get + 1) + j] != get[j]) {
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