#include <locale.h>
#include <stdio.h>
#define      M       1.852
#define      S       1.609
#define      R       1475
#define      C       7.468
#define      G       7412,6
void main()
{
	setlocale(LC_ALL, "RUS");
	int nm;
	float result;
	puts("���� ��������:");
	scanf(" %d", &nm);
	result = M * nm;
	printf(" %d ������� ���� - ��� %.2f � ", nm, result);
	puts("\n ���� ��������:");
	scanf(" %d", &nm);
	result = S * nm;
	printf(" %d ���������� ���� - ��� %.2f � ", nm, result);
	puts("\n ���� ��������:");
	scanf(" %d", &nm);
	result = R * nm;
	printf(" %d ������� ���� - ��� %.2f � ", nm, result);
	puts("\n ���� ��������:");
	scanf(" %d", &nm);
	result = C * nm;
	printf(" %d ����������� ���� - ��� %.2f � ", nm, result);
	puts("\n ���� ��������:");
	scanf(" %d", &nm);
	result = G * nm;
	printf(" %d �������������� ���� - ��� %.2f � ", nm, result);
	getchar();
	return nm;
}