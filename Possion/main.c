#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include<stdlib.h>

int* get_bottles();
bool check(int a, int b, int c); //�����������ƿ�������Ƿ����
bool equal(int *iniVolume, int *demandVolume); //����ʼ״̬�Ƿ�������״̬��ͬ��

int amount;//����ƿ������
int *maxVolume, *iniVolume, *demandVolume;

int main() {
	do {
		printf("�������ƿ�����װ������,�ÿո����(����:1 2 3):\n");
		maxVolume = get_bottles();
		printf("�������ƿ�ӳ�ʼװ������,�ÿո����(����:1 2 3):\n");
		iniVolume = get_bottles();
		printf("�������ƿ��Ҫ��װ������,�ÿո����(����:1 2 3):\n");
		demandVolume = get_bottles();
	} while (check(maxVolume[0], iniVolume[0], demandVolume[0]));
	move(iniVolume);
	free(maxVolume);
	free(iniVolume);
	free(demandVolume);
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
		amount = a;
		return false;
	}
	else {
		printf("\n������������,����������\n");
		return true;
	}
}

bool equal(int *iniVolume, int *demandVolume) {
	for (int i = 1; i <= amount; i++) {
		if (iniVolume[i] != demandVolume[i]) {
			return false;
		}
	}
	return true;
}


void move(int *start, int * path, int pathLength) {
	path = (int*)realloc(path, (pathLength+1)*(amount + 2) * sizeof(int));
	
	if (equal(start, demandVolume)) {
		printPath();
	}
	for (int i = 1; i <= amount; i++) {
		for (int j = 1; j <= amount; j++) {
			if (i == j) {
				continue;
			}
			//int* temp = (int*)malloc((amount + 1) * sizeof(int)); //����start����
			//for (int k = 0; k <= amount; k++) {
			//	temp[k] = start[k];
			//}
			if (start[i] == 0 || start[j] == maxVolume[j]) {
				;
			}
			else if ((maxVolume[j] - start[j]) >= start[i]) {
				start[j] += start[i];
				start[i] = 0;
			}
			else {
				start[i] -= maxVolume[j] - start[j];
				start[j] = maxVolume[j];
			}
			if (!equal(demandVolume, start)) {
				move(start);
			}
		}
	}
}

void printPath() {

}

