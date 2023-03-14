#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#define PROB 5 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
#define SIZE 10000
int rec_count = 0; //재귀적 함수 호출 횟수를 저장하기 위한 함수

double power_itr(double x, int n) {
	double result = 1.0;
	for (int i = 0; i < n; i++)
		result = result * x;
	return(result);
}
double power_rec(double x, int n) {	
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
	time_t t1;
	t1 = time(NULL);
	printf("ITR: %f^%d = %f ", x, n, power_itr(x, n));
	time_t t2;
	t2 = time(NULL);
	printf("수행시간 : %lld초\n", t2 - t1);
	printf("REC: %f^%d = %f 함수 호출 횟수: %d ", x, n, power_rec(x, n), rec_count);
	time_t t3;
	t3 = time(NULL);
	printf("수행시간 : %lld초\n", t3 - t2);
}

int b_c_itr(int n, int k) {
	int bc[100][100];

	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= min(i, k); j++) {
			if (j == 0 || j == i)
				bc[i][j] = 1;
			else
				bc[i][j] = bc[i - 1][j - 1] + bc[i - 1][j];
		}
	}
	return bc[n][k];
}
int b_c_rec(int n, int k) {
	rec_count++;
	if (k == 0 || k == n) {
		return 1;
	}
	else {
		return b_c_rec(n - 1, k - 1) + b_c_rec(n - 1, k);
	}
}
void b_c() {
	int n, k;
	printf("n, k 입력< n=>k > : ");
	scanf("%d %d", &n, &k);
	time_t t1;
	t1 = time(NULL);
	printf("ITR: %dC%d = %d ", n, k, b_c_itr(n, k));
	time_t t2;
	t2 = time(NULL);
	printf("수행시간 : %lld초\n", t2 - t1);
	printf("REC: %dC%d = %d 함수 호출 횟수: %d ", n, k, b_c_rec(n, k), rec_count);
	time_t t3;
	t3 = time(NULL);
	printf("수행시간 : %lld초\n", t3 - t2);
}

int ackerman_itr(int m, int n) {
	int list[100000];
	int arr = 0;
	int count = 0;

	list[arr++] = m;
	list[arr] = n;

	while (1) {
		if (arr == 0) {
			return list[arr];
		}
		else if (list[arr - 1] == 0) {
			count++;
			list[arr - 1] = list[arr] + 1;
			arr = arr - 1;
		}
		else if (list[arr] == 0) {
			count++;
			list[arr - 1] = list[arr - 1] - 1;
			list[arr] = 1;
		}
		else {
			count++;
			list[arr + 1] = list[arr] - 1;
			list[arr] = list[arr - 1];
			list[arr - 1] = list[arr - 1] - 1;

			arr = arr + 1;
		}
	}
}
int ackerman_rec(int m, int n) {
	rec_count++;
	if (m == 0)	{
		return n + 1;
	}
	else if (m != 0 && n == 0) {
		return ackerman_rec(m - 1, 1);
	}
	else {
		return ackerman_rec(m - 1, ackerman_rec(m, n - 1));
	}
}
void ackerman() {
	int m, n;
	printf("m, n 입력< m, n >= 0 > : ");
	scanf("%d %d", &m, &n);
	time_t t1;
	t1 = time(NULL);
	printf("ITR: A<%d,%d> = %d ", m, n, ackerman_itr(m, n));
	time_t t2;
	t2 = time(NULL);
	printf("수행시간 : %lld초\n", t2 - t1);
	printf("REC: A<%d,%d> = %d 함수 호출 횟수: %d ", m, n, ackerman_rec(m, n), rec_count);
	time_t t3;
	t3 = time(NULL);
	printf("수행시간 : %lld초\n", t3 - t2);
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
	time_t t1;
	t1 = time(NULL);
	printf("ITR: %d번째 항의 값 : %d ", n, fib_itr(n));
	time_t t2;
	t2 = time(NULL);
	printf("수행시간 : %lld초\n", t2 - t1);
	printf("REC: %d번째 항의 값 : %d 함수 호출 횟수: %d ", n, fib_rec(n), rec_count);
	time_t t3;
	t3 = time(NULL);
	printf("수행시간 : %lld초\n", t3 - t2);
}

int search_itr(int* data, int first, int last, int target) {
	while (first <= last) {
		int mid = first + (last - first) / 2;
		if (data[mid] == target)
			return mid;
		else if (data[mid] > target)
			last = mid;
		else
			first = mid + 1;
	}
}
int search_rec(int * data, int first, int last, int target) {
	rec_count++;
	int mid = (first + last) / 2;
	if (data[mid] == target) {
		return mid;
	}
	else if (data[mid] > target) {
		return search_rec(data, first, mid, target);
	}
	else {
		return search_rec(data, mid, last, target);
	}
}
void search() {
	int data[SIZE];
	int first = 0;
	int last = SIZE;
	int target;
	for (int idx = 0; idx < SIZE; idx++) {
		data[idx] = idx;
	}
	printf("검색하고자 하는 값: ");
	scanf("%d", &target);
	time_t t1;
	t1 = time(NULL);
	printf("ITR: 목표값 : %d ", search_itr(data, first, last, target));
	time_t t2;
	t2 = time(NULL);
	printf("수행시간 : %lld초\n", t2 - t1);
	printf("REC: 목표값 : %d 함수 호출 횟수: %d ", search_rec(data, first, last, target), rec_count);
	time_t t3;
	t3 = time(NULL);
	printf("수행시간 : %lld초\n", t3 - t2);
}

int main(void) {
	if (PROB == 1) {
		power();
	}
	else if (PROB == 2) {
		b_c();
	}
	else if (PROB == 3) {
		ackerman();
	}
	else if (PROB == 4) {
		fib();
	}
	else if (PROB == 5) {
		search();
	}
	return 0;
}