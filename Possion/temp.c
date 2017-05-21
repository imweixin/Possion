void move(int *start) {
	int * state = (int*)malloc(amount*(amount - 1)*(amount + 2) * sizeof(int));//记录移动amount*(amount-1)次的状态
	for (int i = 1; i <= amount; i++) {
		for (int j = 1; j <= amount; j++) {
			int *temp = (int*)malloc((amount + 1) * sizeof(int));
			for (int k = 0; k <= amount; k++) {
				temp[k] = start[k];
			}
			if (i == j) {
				continue;
			}
			if (temp[i] == 0 || temp[j] == maxVolume[j]) {
				;
			}
			else if (maxVolume[j] - temp[j] >= temp[i]) {
				temp[j] += temp[i];
				temp[i] = 0;
			}
			else {
				temp[i] -= maxVolume[j] - temp[j];
				temp[j] = maxVolume[j];
			}
			for (int k = 0; k < amount + 2; k++) {
				state[(amount + 2)*i + k] =
			}
			/*printf("%d->%d;现在的状态为:", i, j);
			for (int i = 1; i <= amount; i++) {
			printf("%d ", temp[i]);
			}*/
			free(temp);
			printf("\n");
		}
	}
}

