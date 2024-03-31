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

	
	printf("\n�������� ������ = ");
	
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
	
		printf("1. ���� �� ��, ���� � ������� 1 �������\n������ = {1}");
		int m = 1;
		int* a = malloc(m * sizeof(int));
		a[0] = 1;
		SearchSequence(a, m);
		free(a);
		printf("\n");

		printf("\n2. ���� �� ��, ���� � ������� �������� ���� ����\n");
		m = 5;
		a = malloc(m * sizeof(int));
		printf("������ = ");
		for (int i = 0;i < m; i++)
		{
			a[i] = 0;
			printf("%d ", a[i]);
		}
		
		SearchSequence(a, m);
		free(a);
		printf("\n");

		printf("3. ���� �� ��, ���� ������ ������������������ �� �����+ ������� ������������������ ����� � ����� ����� �������\n");
		m = 12;
		int c[12] = {1,2,4,5,6,48,96,2,4,8,16,32};
		printf("������ = {1,2,4,5,6,48,96,2,4,8,16,32}\n");
		SearchSequence(c, m);
		printf("\n");
		

		printf("4. ���� �� ��, ���� ���� ���� � ����� �������\n");
		m = 10;
		int d[10] = {1,0,4,5,6,48,96,2,0,8};
		printf("������ = { 1,0,4,5,6,48,96,2,0,8 }\n");
		SearchSequence(d, m);
		printf("\n");
	
}

int main()
{
	int n, k = 0;
	setlocale(LC_CTYPE, "Rus");
	Tests();
	printf("������� ����� �������\n\n");
	scanf("%d", &n);
	printf("\n");

	if (n == 0) {
		printf("������� ������ ���������\n");
		exit(1);
	}
	printf("������� ������\n\n");
	int* a = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
		if (a[i] == " " || a[i] == "\0") {
			printf("������");
			exit(5);

		}
		if (a[i] == 0)
		{
			k++;
		}
	}
	if (k == n)
	{
		printf("\n������ ��������� ������� �� �����\n������");
	}
	else
	{
		printf("\n");
		SearchSequence(a, n);
	}
	free(a);
	return 0;
}