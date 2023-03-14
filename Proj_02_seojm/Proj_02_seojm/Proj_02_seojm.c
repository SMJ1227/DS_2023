#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#define PROB 1 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트

int rec_count = 0; //재귀적 함수 호출 횟수를 저장하기 위한 함수

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
	printf("x, n 입력<x^n> : ");
	scanf("%lf %d", &x, &n);
	printf("ITR: %f^%d = %f\n", x, n, power_itr(x, n));
	printf("REC: %f^%d = %f, 함수 호출 횟수: %d\n", x, n, power_rec(x, n), rec_count);
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
	printf("Input 피보나치항: ");
	scanf("%d", &n);
	printf("ITR: %d번째 항의 값 : %d\n", n, fib_itr(n));
	printf("REC: %d번째 항의 값 : %d, 함수 호출 횟수: %d\n", n, fib_rec(n), rec_count);
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