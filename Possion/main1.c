#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

int* get_bottles();
bool check(int a, int b, int c); //�����������ƿ�������Ƿ����
bool equal(int *iniVolume, int *demandVolume); //����ʼ״̬�Ƿ�������״̬��ͬ��
bool contain(int* start, int* path, int pathLength); //����·���Ƿ��Ѿ��߹�
void move(int *start, int * path, int pathLength);
void printPath(int* path, int pathLength);
void addPath(int *start, int *path, int pathLength, int i, int j);

int *maxVolume, *iniVolume, *demandVolume;
static int *path;

int main() {
	/*do {
		printf("�������ƿ�����װ������,�ÿո����(����:1 2 3):\n");
		maxVolume = get_bottles();
		printf("�������ƿ�ӳ�ʼװ������,�ÿո����(����:1 2 3):\n");
		iniVolume = get_bottles();
		printf("�������ƿ��Ҫ��װ������,�ÿո����(����:1 2 3):\n");
		demandVolume = get_bottles();
	} while (check(maxVolume[0], iniVolume[0], demandVolume[0]));*/
	int max[4] = { 3,12,8,5 };
	int ini[4] = { 3,12,0,0 };
	int dem[4] = { 3,6,6,0 };
	maxVolume = max, iniVolume = ini, demandVolume = dem;
	move(iniVolume, path, 0);
	/*free(maxVolume);
	free(iniVolume);
	free(demandVolume);*/
	system("pause");
	return 0;
}

int * get_bottles() {
	int num = 256; //���ö������ݳ�ʼ����
	int *bottles = malloc(num * sizeof(int));
	char ch = getchar();

	int i = 1;  //����i=0ʱ ����bottles������������
	int temp = 0;
	while (ch != '\n') {
		if (i > num) {
			num *= 2;
			bottles = realloc(bottles, num * sizeof(int));
			if (num > 1024) {
				printf("��������������");
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
	bottles[0] = i;  //����bottles����
	return bottles;
}

bool check(int a, int b, int c) {
	if (a == b&&b == c) {
		return false;
	}
	else {
		printf("\n������������,����������\n");
		return true;
	}
}

bool equal(int *iniVolume, int *demandVolume) {
	for (int i = 1; i <= *iniVolume; i++) {
		if (iniVolume[i] != demandVolume[i]) {
			return false;
		}
	}
	return true;
}

bool contain(int* start, int* path, int pathLength) {
	bool mark ;

	for (int i = 0; i < pathLength; i++) {
		mark = true;
		int num = i*(*start + 3);
		for (int j = 1; j <= *start; j++) {
			if (start[j] != path[num + 1 + j]) {
				mark= false;
				break;
			}
		}
		if (mark) {
			return true;
		}
	}

	return false;
}

void move(int *start, int * path, int pathLength) {
	/*if (pathLength == 0) {
		path = (int *)calloc((*start + 3) , sizeof(int));
		for (int i = 1; i <= *start; i++) {
			path[i + 1] = start[i];
		}
		pathLength++;
	}
	else {
		path = (int*)realloc(path, (pathLength + 1)*(*start + 3) * sizeof(int));
		if (!path) {
			printf("�����ڴ�ʧ��!");
			system("pause");
			exit(1);
		}
	}*/
	path = (int*)realloc(path, (pathLength + 1)*(*start + 3) * sizeof(int));

	bool isMoved = true;  //����Ƿ��ƶ���

	for (int i = 1; i <= *start; i++) {
		for (int j = 1; j <= *start; j++) {

			int *temp = malloc((*start+1) * sizeof(int));  //����start����
			for (int k = 0; k <= *start; k++) {
				temp[k] = start[k];
			}

			if (i == j) {
				if (equal(temp, demandVolume)) {
					printPath(path, pathLength);
				}
				continue;
			}
			if (temp[i] == 0 || temp[j] == maxVolume[j]) {
				isMoved = false;  //û���ƶ�
			}
			else if ((maxVolume[j] - temp[j]) >= temp[i]) {
				temp[j] += temp[i];
				temp[i] = 0;
				isMoved = true;
			}
			else {
				temp[i] -= maxVolume[j] - temp[j];
				temp[j] = maxVolume[j];
				isMoved = true;
			}

			if (isMoved && !contain(temp, path, pathLength)) {
				for (int k = 0; k <= *start; k++) {
					start[k]=temp[k];
				}
				addPath(start, path, pathLength, i, j);
			}
			else {
				break;
			}
			free(temp);
		}
	}
}


void printPath(int* path, int pathLength) {
	if (pathLength == 0) {
		printf("����Ҫ�ƶ�!\n");
	}
	else {
		for (int i = 0; i < pathLength; i++) {
			int num = i*(*iniVolume + 3);
			printf("%d->%d:", path[num], path[num + 1]);
			for (int j = 1; j <= *iniVolume; j++) {
				printf("%d ", path[num + 1 + j]);
			}
		}
	}
}

void addPath(int *start, int *path, int pathLength,int i,int j) {
	int num = pathLength*(*start + 3);
	path[num] = i;      //����·����ǰ��λΪ���ƶ���ƿ��
	path[num + 1] = j;
	printf("%d->%d: ", i, j);
	for (int k = 1; k <= *start; k++) {
		path[num + 1 + k] = start[k];
		printf("%d ", start[k]);
	}
	printf("\n");
	pathLength++;
	move(start, path, pathLength);
}

