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
bool markEnd[4096] = { false };  //��¼���Ҫ���·��
bool endPath[4096] = { false };  //��¼һ��·���Ľ���(�ﵽҪ����߲�����ô�ƶ������ظ�ǰ���״̬)
int number = 0;                  //��¼path������
int numel = 3;                   //ƿ������

int max[3] = { 12,8,5 };
int start[3] = { 12,0,0 };
int end[3] = { 6,6,0 };

int main() {
	goPath(start);
	printPath();
	if (noRepeat()) {
		printf("û���ظ�\n\n");
	}
	else {
		printf("���ظ�\n\n");
	}
	searchPath(MIN_PATH);  //ѡ�����������·��
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

int move(int *start, int length, int nownum) { //lengthΪ��ǰpath�ĳ���,���Ϊ1,nownumΪ��ǰpath�����,��СΪ0
	int branch = 0;

	if (!memcmp(start, end, numel * sizeof(int))) {
		markEnd[nownum] = true;
	}
	else {
		for (int i = 0; i < numel; i++) {
			for (int j = 0; j < numel; j++) {
				//����ʼƿ��i������Ŀ��ƿ��j
				int a = start[i], b = start[j];
				if (i == j || start[i] == 0 || start[j] == max[j]) { //���i=j,�򱻵���ƿ��Ϊ�ջ�����ƿ��Ϊ��,����Ҫ�㵹
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
	path[nownum][0] = length + 1; //��¼·���ĳ���
	if (length && number != nownum) {
		memcpy(path[number], path[nownum], (numel*length + 2) * sizeof(int));
	}
	path[number][1] = number;     //��¼·�����
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
	for (int i = 0; i < path[number][0]; i++) {  //·������
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
	for (int i = 0; i <= number; i++) {             //·����
		if (markEnd[i]) {
			numPath++;
			printf("��%d�����·��,���Ϊ%d\n����Ϊ%d\n", numPath, path[i][1], path[i][0] - 1);
			fprintf(fp, "��%d�����·��,���Ϊ%d\n����Ϊ%d\n", numPath, path[i][1], path[i][0] - 1);
			printSinPath(i, fp);
		}
	}
	fclose(fp);
}

void searchPath(bool set) {
	int numPath = 0;                                //��¼��̻��·��������
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
		printf("���·��Ϊ:\n");
		fprintf(fp, "���·��Ϊ:\n");
	}
	else {
		printf("�·��Ϊ:\n");
		fprintf(fp, "�·��Ϊ:\n");
	}

	for (int i = 0; i <= number; i++) {
		if (path[i][0] == n) {
			numPath++;
			printf("\n��%d��Ҫ��·��,���Ϊ%d\n����Ϊ%d\n", numPath, path[i][1], path[i][0] - 1);
			fprintf(fp, "\n��%d�����·��,���Ϊ%d\n����Ϊ%d\n", numPath, path[i][1], path[i][0] - 1);
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