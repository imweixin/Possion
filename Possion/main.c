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
bool markEnd[WIDTH] = { false };  //��¼���Ҫ���·��
int mark[WIDTH];                  //��¼���Ҫ��·�����±�
int numel = NUMBER_ELM;           //ƿ������
int minlen = 11;                  //�������10��

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
	int min = 0;//��¼���·��
	bool mark = true;
	while (mark) {
		int branch = 0;

		int tmpnum = 0, tmplen = WIDTH;  //tmpnumΪ���һ��length��Ϊ0��number;tmplenΪ��̲�Ϊ0����û�н�����path��length
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

int move(int *start, int length, int nownum) { //lengthΪ��ǰpath�ĳ���,���Ϊ1,nownumΪ��ǰpath�����,��СΪ0
	int branch = 0;
	if (memcmp(start, end, numel * sizeof(int))) {
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

int findPath() {                     //�ҳ���һ��lengthΪ���path���������path
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

void printPath(int minlen) {
	int numPath = 0;
	//int k = 0; //��¼��Ч·����
	//for (int i = 0; i < WIDTH; i++) {
	//	if (markEnd[i]) {
	//		mark[++k] = i;
	//	}
	//}
	//*mark = k;
	//k = 0;     //��¼���·����

	FILE* fpmin = fopen("minPath.txt", "w");
	/*for (int i = 1; i <= *mark; i++) {
		if (path[mark[i]][0] == minlen) {
			numPath++;
			printf("\n��%d�����·��,����Ϊ%d\n", numPath, path[*(mark + i)][0] - 1);
			fprintf(fpmin, "\n��%d�����·��,����Ϊ%d\n", numPath, path[*(mark + i)][0] - 1);
			printSinPath(mark[i], fpmin);
		}
	}*/
	for (int i = 0; i < WIDTH; i++) {
		if (path[i][0]) {
			numPath++;
			printf("\n��%d�����·��,����Ϊ%d\n", numPath, path[i][0] - 1);
			fprintf(fpmin, "\n��%d�����·��,����Ϊ%d\n", numPath, path[i][0] - 1);
			printSinPath(i, fpmin);
		}
	}
	fclose(fpmin);
}