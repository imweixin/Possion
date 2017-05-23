#define _CRT_SECURE_NO_WARNINGS
#define MIN_PATH true
#define MAX_PATH false
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

void goPath(int *start);
int addPath(int *start, int temp, int number, int length);
int move(int *start, int length, int nownum);
bool contain(int *start, int number, int length);
void printSinPath(int i, FILE* fp);
void printPath();
void searchPath(bool set);
bool noRepeat();


int path[4096][1024] = { 0 };
bool markEnd[4096] = { false };  //记录达成要求的路径
bool endPath[4096] = { false };  //记录一条路径的结束(达到要求或者不管怎么移动都会重复前面的状态)
int number = 0;                  //记录path的总数
int numel = 3;                   //瓶子总数

int max[3] = { 12,8,5 };
int start[3] = { 12,0,0 };
int end[3] = { 6,6,0 };

int main() {
	goPath(start);
	printPath();
	if (noRepeat()) {
		printf("没有重复\n\n");
	}
	else {
		printf("有重复\n\n");
	}
	searchPath(MIN_PATH);  //选择输出最长或最短路径
	system("pause");
	return 0;
}

void goPath(int *start) {
	addPath(start, 0, 0, 0);
	bool mark = false;

	while (!mark) {
		int temp = number;

		for (int i = 0; i <= temp; i++) {

			int length = path[i][0];
			int ini[10];
			start = &path[i][2 + (length - 1)*numel];
			memcpy(ini, start, numel * sizeof(int));
			int branch = 0;
			int nownum = path[i][1];
			if (endPath[nownum]) {
				continue;
			}
			else {
				branch = move(ini, length, nownum);
			}
			if (!branch) {
				endPath[nownum] = true;
			}

		}

		for (int i = 0; i <= temp; i++) {
			if (endPath[i]) {
				/*int length = path[i][0] - 1;
				if (!memcmp(&path[i][numel*length + 2], end, numel * sizeof(int))) {
					path[i][0] = 0;
				}*/
				mark = true;
			}
			else {
				mark = false;
				break;
			}
		}

	}
}

int move(int *start, int length, int nownum) { //length为当前path的长度,最短为1,nownum为当前path的序号,最小为0
	int branch = 0;

	if (!memcmp(start, end, numel * sizeof(int))) {
		markEnd[nownum] = true;
	}
	else {
		for (int i = 0; i < numel; i++) {
			for (int j = 0; j < numel; j++) {
				//从起始瓶子i倒出到目标瓶子j
				int a = start[i], b = start[j];
				if (i == j || start[i] == 0 || start[j] == max[j]) { //如果i=j,或被倒出瓶子为空或倒往的瓶子为满,则不需要倾倒
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
					if (!branch) {
						addPath(start, nownum, nownum, length);
					}
					else {
						number++;
						addPath(start, nownum, number, length);
					}
					branch++;
				}
				start[i] = a;
				start[j] = b;

			}
		}
	}
	return branch;
}

int addPath(int *start, int nownum, int number, int length) {
	path[nownum][0] = length + 1; //记录路径的长度
	if (length && number != nownum) {
		memcpy(path[number], path[nownum], (numel*length + 2) * sizeof(int));
	}
	path[number][1] = number;     //记录路径编号
	memcpy(&path[number][numel*length + 2], start, numel * sizeof(int));
	length++;
	return length;
}

bool contain(int *start, int number, int length) {
	bool mark;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < numel; j++) {
			if (path[number][numel*i + j + 2] == start[j]) {
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

void printSinPath(int number, FILE* fp) {
	for (int i = 0; i < path[number][0]; i++) {  //路径长度
		for (int j = 0; j < numel; j++) {
			printf("%4d ", path[number][numel*i + 2 + j]);
			fprintf(fp, "%4d ", path[number][numel*i + 2 + j]);
		}
		printf("\n");
		fprintf(fp, "\n");
	}
	printf("\n\n");
	fprintf(fp, "\n\n");
}

void printPath() {
	int numPath = 0;
	FILE *fp = fopen("path.txt", "w");
	for (int i = 0; i <= number; i++) {             //路径数
		if (markEnd[i]) {
			numPath++;
			printf("第%d条完成路径,序号为%d\n步数为%d\n", numPath, path[i][1], path[i][0] - 1);
			fprintf(fp, "第%d条完成路径,序号为%d\n步数为%d\n", numPath, path[i][1], path[i][0] - 1);
			printSinPath(i, fp);
		}
	}
	fclose(fp);
}

void searchPath(bool set) {
	int numPath = 0;                                //记录最短或最长路径的条数
	FILE* fp = fopen("searchPath.txt", "w");

	int n = path[0][0];
	for (int i = 0; i < number; i++) {
		if (set) {
			if (n > path[i][0]) {
				n = path[i][0];
			}
		}
		else {
			if (n < path[i][0]) {
				n = path[i][0];
			}
		}
	}

	if (set) {
		printf("最短路径为:\n");
		fprintf(fp, "最短路径为:\n");
	}
	else {
		printf("最长路径为:\n");
		fprintf(fp, "最长路径为:\n");
	}

	for (int i = 0; i <= number; i++) {
		if (path[i][0] == n) {
			numPath++;
			printf("\n第%d条要求路径,序号为%d\n步数为%d\n", numPath, path[i][1], path[i][0] - 1);
			fprintf(fp, "\n第%d条完成路径,序号为%d\n步数为%d\n", numPath, path[i][1], path[i][0] - 1);
			printSinPath(i, fp);
		}
	}
	fclose(fp);
}

bool noRepeat() {
	bool mark = true;
	for (int i = 0; i <= number; i++) {
		for (int j = 0; j <= number; j++) {
			if (i == j) {
				continue;
			}
			else if (path[i][0] != path[j][0]) {
				continue;
			}
			else {
				int length = path[i][0];
				if (!memcmp(&path[i][2], &path[j][2], numel*length * sizeof(int))) {
					return false;
				}
			}
		}
	}
	return true;
}