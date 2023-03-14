#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#define PROB 1 // ������ ������ �����ϰ� �ش� ���� ��ȣ�� �����Ͽ� �׽�Ʈ

int rec_count = 0; //����� �Լ� ȣ�� Ƚ���� �����ϱ� ���� �Լ�

double power_itr(double x, int n)
{
	int i;
	double result = 1.0;
	for (i = 0; i < n; i++)
		result = result * x;
	return(result);
}
double power_rec(double x, int n)
{	
	rec_count++;
	if (n == 0) return 1;
	else if ((n % 2) == 0)
		return power_rec(x * x, n / 2);
	else return x * power_rec(x * x, (n - 1) / 2);
}
void power() {
	double x;
	int n;
	printf("x, n �Է�<x^n> : ");
	scanf("%lf %d", &x, &n);
	printf("ITR: %f^%d = %f\n", x, n, power_itr(x, n));
	printf("REC: %f^%d = %f, �Լ� ȣ�� Ƚ��: %d\n", x, n, power_rec(x, n), rec_count);
}







int fib_itr(int n)
{
	if (n == 0) return 0;
	if (n == 1) return 1;
	int pp = 0;
	int p = 1;
	int result = 0;
	for (int i = 2; i <= n; i++) {
		result = p + pp;
		pp = p;
		p = result;
	}
	return result;
}
int fib_rec(int n)
{
	rec_count++;
	if (n == 0) return 0;
	if (n == 1) return 1;
	return (fib_rec(n - 1) + fib_rec(n - 2));
}
void fib() {
	int n;
	printf("Input �Ǻ���ġ��: ");
	scanf("%d", &n);
	printf("ITR: %d��° ���� �� : %d\n", n, fib_itr(n));
	printf("REC: %d��° ���� �� : %d, �Լ� ȣ�� Ƚ��: %d\n", n, fib_rec(n), rec_count);
}




int main(void) {
	if (PROB == 1) {
		power();
	}
	else if (PROB == 4) {
		fib();
	}
	return 0;
}