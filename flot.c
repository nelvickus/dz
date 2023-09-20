#include <locale.h>
#include <stdio.h>

void main()

{
	setlocale(LC_ALL, "RUS");
	int L = 1323, n = 2;
	float k;
	k = (float)n / L;
	printf("Дано:\n\t%d\n\t%d\n\t_______\n Ответ:\n\t % +05.5f", n, L, k);



}