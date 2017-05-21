#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

void writePath(int from,int to,int *start) {
	FILE* fp = fopen("path.txt", "w+");
	if (!fp) {
		printf("写文件失败!");
		system("pause");
		exit(1);
	}
	fprintf(fp, "%d->%d: ", from, to);
	for (int i = 1; i <= *start; i++) {
		fprintf(fp, "%d ", start[i]);
	}

	if (fp == NULL) {
		printf("写文件失败!");
		system("pause");
		exit(1);
	}
	
}

void readPath() {

}