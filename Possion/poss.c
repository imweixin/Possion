#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include"func.h"

bool equal(int *start, int *end); //检测初始状态是否与最终状态相同了
bool contain(int *start, int pathLength);
void move(int* start, int* end, int pathLength);

int *maxVolume, *iniVolume, *demandVolume;

int main() {
	/*do {
	printf("请输入各瓶子最多装酒数量,用空格隔开(例如:1 2 3):\n");
	maxVolume = get_bottles();
	printf("请输入各瓶子初始装酒数量,用空格隔开(例如:1 2 3):\n");
	iniVolume = get_bottles();
	printf("请输入各瓶子要求装酒数量,用空格隔开(例如:1 2 3):\n");
	demandVolume = get_bottles();
	} while (check(maxVolume[0], iniVolume[0], demandVolume[0]));*/
	int max[4] = { 3,12,8,5 };
	int ini[4] = { 3,12,0,0 };
	int dem[4] = { 3,6,6,0 };
	maxVolume = max, iniVolume = ini, demandVolume = dem;

	move(iniVolume, demandVolume, 0);
	/*free(maxVolume);
	free(iniVolume);
	free(demandVolume);*/
	system("pause");
	return 0;
}

bool equal(int *start, int *end) {
	for (int i = 1; i <= *start; i++) {
		if (start[i] != end[i]) {
			return false;
		}
	}
	return true;
}

bool contain(int *start, int pathLength) {
	bool mark;
	FILE* fp = fopen("path.txt", "r");
	if (!fp) {
		printf("打开文件失败!");
		system("pause");
		exit(1);
	}
	
	int from, to, amount;
	for (int i = 0; i < pathLength; i++) {
		fscanf(fp, "%d->%d: ", &from, &to);
		mark = true;
		for (int j = 0; j <= *start; j++) {
			fscanf(fp, "%d ", &amount);
			if (amount != start[j]) {
				mark = false;
				break;
			}
		}
		if (mark) {
			fclose(fp);
			return true;
		}
	}
	fclose(fp);
	return false;
}

void move(int* start, int* end, int pathLength) {
	bool isMoved = false;

	for (int i = 1; i <= *start; i++) {
		for (int j = 1; j <= *start; j++) {
			if (i == j) {
				if (equal(start, end)) {
					;
				}
				continue;
			}
			if (start[i] == 0 || start[j] == maxVolume[j]) {
				isMoved = false;
			}
			else if (start[i] > maxVolume[j] - start[j]) {
				start[i] -= maxVolume[j] - start[j];
				start[j] = maxVolume[j];
				isMoved = true;
			}
			else {
				start[j] += start[i];
				start[i] = 0;
				isMoved = true;
			}
			if (isMoved && !contain(start, pathLength)) {
				writePath(i,j,start);
				move(start, end, pathLength);
			}
		}
	}
}