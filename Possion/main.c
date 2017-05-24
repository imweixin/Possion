#define _CRT_SECURE_NO_WARNINGS
#define NUMBER_ELM 4
#define WIDTH 4096
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

int goPath(int *start);
int findPath();
int addPath(int *start, int temp, int number, int length);
int move(int *start, int length, int nownum);
bool contain(int *start, int number, int length);
void printSinPath(int i, FILE* fp);
void printPath(int minlen);


int path[WIDTH][512] = { 0 };
bool markEnd[WIDTH] = { false };  //记录达成要求的路径
int mark[WIDTH];                  //记录达成要求路径的下标
int numel = NUMBER_ELM;           //瓶子总数
int minlen = 11;                  //设置最多10步

int max[NUMBER_ELM] = { 12,10,6,3};
int start[NUMBER_ELM] = { 12,0,0 ,0};
int end[NUMBER_ELM] = { 3,3,3,3 };
//int end[NUMBER_ELM] = {4,4,0 };

int main() {
	int minlen = goPath(start);
	printPath(minlen);
	system("pause");
	return 0;
}

void findtmp(int *tmpnum, int* tmplen) {
	for (int i = 0; i < WIDTH; i++) {
		if (path[i][0]) {
			if (path[i][0] > minlen) {
				path[i][0] = 0;
				markEnd[i] = false;
			}
			else {
				*tmpnum = path[i][1];
				if (!markEnd[i] && path[i][0] < *tmplen) {
					*tmplen = path[i][0];
				}
			}
		}
	}
}

int goPath(int *start) {
	addPath(start, 0, 0, 0);
	int min = 0;//记录最短路径
	bool mark = true;
	while (mark) {
		int branch = 0;

		int tmpnum = 0, tmplen = WIDTH;  //tmpnum为最后一个length不为0的number;tmplen为最短不为0的且没有结束的path的length
		findtmp(&tmpnum, &tmplen);

		for (int i = 0; i <= tmpnum; i++) {
			int length = path[i][0];
			if (length == tmplen && !markEnd[i]) {
				int ini[10];
				memcpy(ini, &path[i][(length - 1)*numel + 2], numel * sizeof(int));
				branch = move(ini, length, i);
			}

			if (!branch) {
				markEnd[i] = true;
				if (memcmp(&path[i][(length - 1)*numel + 2], end, numel * sizeof(int))) {
					path[i][0] = 0;
					markEnd[i] = false;
				}
				else {
					min++;
					if (min == 1) {
						minlen = path[i][0];
					}
				}
			}

		}

		mark = false;
		for (int i = 0; i <= tmpnum; i++) {
			if (path[i][0]) {
				if (!markEnd[i]) {
					mark = true;
					break;
				}
			}
		}
	}
	return minlen;
}

int move(int *start, int length, int nownum) { //length为当前path的长度,最短为1,nownum为当前path的序号,最小为0
	int branch = 0;
	if (memcmp(start, end, numel * sizeof(int))) {
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
						int number = findPath();
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

int findPath() {                     //找出第一个length为零的path用来添加新path
	int number = 0;
	for (int i = 0; i < WIDTH; i++) {
		if (!path[i][0]) {
			number = i;
			break;
		}
	}
	return number;
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
	for (int i = 0; i <= number; i++) {
		for (int j = 0; j < length; j++) {
			if (!memcmp(&path[number][numel*j + 2], start, numel * sizeof(int))) {
				return true;
			}
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

void printPath(int minlen) {
	int numPath = 0;
	//int k = 0; //记录有效路径数
	//for (int i = 0; i < WIDTH; i++) {
	//	if (markEnd[i]) {
	//		mark[++k] = i;
	//	}
	//}
	//*mark = k;
	//k = 0;     //记录最短路径数

	FILE* fpmin = fopen("minPath.txt", "w");
	/*for (int i = 1; i <= *mark; i++) {
		if (path[mark[i]][0] == minlen) {
			numPath++;
			printf("\n第%d条最短路径,步数为%d\n", numPath, path[*(mark + i)][0] - 1);
			fprintf(fpmin, "\n第%d条最短路径,步数为%d\n", numPath, path[*(mark + i)][0] - 1);
			printSinPath(mark[i], fpmin);
		}
	}*/
	for (int i = 0; i < WIDTH; i++) {
		if (path[i][0]) {
			numPath++;
			printf("\n第%d条最短路径,步数为%d\n", numPath, path[i][0] - 1);
			fprintf(fpmin, "\n第%d条最短路径,步数为%d\n", numPath, path[i][0] - 1);
			printSinPath(i, fpmin);
		}
	}
	fclose(fpmin);
}