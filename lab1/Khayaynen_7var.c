#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>




void SearchSequence(int* a, int n)
{

	int max = -10, MaxIndex = 0;
	int* b = (int*)malloc(sizeof(int) * (n));
	for (int i = 0; i < n; i++) {
		b[i] = 1;
		
	}
	if (n != 1) {
		int i = n - 1;
		while(i>=0)  {
			int j = i, flag = 1;
			while ((j >= 0) && (flag == 1))
			{
				if (a[j] == 0)
				{
					flag = 0;
				}
				else
				{

					if (a[j - 1] != 0 && a[j] % a[j - 1] == 0)
					{
						b[i]++;
						
					}
					else flag = 0;
					if (b[i] > max) {
						max = b[i];
						MaxIndex = i;
					}

					j--;
				}
			}

			i=i-b[i];
		}

	}

	
	printf("\nИтоговый массив = ");
	
	/*for (int i = 0;i <= n;i++)
	{
		printf("%d ", b[i]);
	}
	printf("\n\n");*/


	//printf("\nmax = %d\nMaxInd = %d\n", max, MaxIndex);
	if (n == 1) 
	{
		printf("%d", a[0]);
	}
	else 
	{
		for (int i = MaxIndex - max + 1;i <= MaxIndex;i++)
		{
			printf("%d ", a[i]);
		}

		printf("\n");
	}
	free(b);
}

void Tests()
{
	
		printf("1. Тест на то, если в массиве 1 элемент\nМассив = {1}");
		int m = 1;
		int* a = malloc(m * sizeof(int));
		a[0] = 1;
		SearchSequence(a, m);
		free(a);
		printf("\n");

		printf("\n2. Тест на то, если в массиве элементы одни нули\n");
		m = 5;
		a = malloc(m * sizeof(int));
		printf("Массив = ");
		for (int i = 0;i < m; i++)
		{
			a[i] = 0;
			printf("%d ", a[i]);
		}
		
		SearchSequence(a, m);
		free(a);
		printf("\n");

		printf("3. Тест на то, если разные последовательности по длине+ искомая последовательность стоит в самом конце массива\n");
		m = 12;
		int c[12] = {1,2,4,5,6,48,96,2,4,8,16,32};
		printf("Массив = {1,2,4,5,6,48,96,2,4,8,16,32}\n");
		SearchSequence(c, m);
		printf("\n");
		

		printf("4. Тест на то, если есть нули в самом массиве\n");
		m = 10;
		int d[10] = {1,0,4,5,6,48,96,2,0,8};
		printf("Массив = { 1,0,4,5,6,48,96,2,0,8 }\n");
		SearchSequence(d, m);
		printf("\n");
	
}

int main()
{
	int n, k = 0;
	setlocale(LC_CTYPE, "Rus");
	Tests();
	printf("Введите длину массива\n\n");
	scanf("%d", &n);
	printf("\n");

	if (n == 0) {
		printf("Введите больше элементов\n");
		exit(1);
	}
	printf("Введите массив\n\n");
	int* a = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
		if (a[i] == " " || a[i] == "\0") {
			printf("Ошибка");
			exit(5);

		}
		if (a[i] == 0)
		{
			k++;
		}
	}
	if (k == n)
	{
		printf("\nМассив полностью состоит из нулей\nОшибка");
	}
	else
	{
		printf("\n");
		SearchSequence(a, n);
	}
	free(a);
	return 0;
}