#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))
#define MAX_DEGREE 101 // ���׽��� �ִ����� + 1

typedef struct {
	int degree;
	float coef[MAX_DEGREE];
} polynomial;
polynomial a = { 5, {10, 0, 0, 0, 6, 3} };

// C = A+B ���⼭ A�� B�� ���׽��̴�. ����ü�� ��ȯ�ȴ�.
polynomial poly_add1(polynomial A, polynomial B) {
	polynomial C; // ��� ���׽�
	int Apos = 0, Bpos = 0, Cpos = 0; // �迭 �ε��� ����
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = MAX(A.degree, B.degree); // ��� ���׽� ����
	while (Apos <= A.degree && Bpos <= B.degree) {
		if (degree_a > degree_b) { // A�� > B��
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}
		else if (degree_a == degree_b) { // A�� == B��
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
			degree_a--; degree_b--;
		}
		else { // B�� > A��
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}
	return C;
}

polynomial poly_mul1(polynomial A, polynomial B) {
	polynomial C; // ��� ���׽�
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = A.degree + B.degree; // ��� ���׽� ����
	for (int i = 0; i < degree_a + degree_b + 1; i++)              //�迭 �ʱ�ȭ
		C.coef[i] = 0;
	for (int i = 0; i < degree_a + 1; i++) {
		for (int j = 0; j < degree_b + 1; j++) {
			C.coef[i + j] += A.coef[i] * B.coef[j];
		}
	}
	return C;
}

void print_poly(polynomial p)
{
	for (int i = p.degree; i > 0; i--)
		printf("%3.1fx^%d + ", p.coef[p.degree - i], i);
	printf("%3.1f \n", p.coef[p.degree]);
}

// ���Լ�
int main(void)
{
	polynomial a = { 5,{ 3, 6, 0, 0, 0, 10 } };
	polynomial b = { 4,{ 7, 0, 5, 0, 1 } };
	polynomial c;
	polynomial d;
	print_poly(a);
	print_poly(b);
	//c = poly_add1(a, b);
	d = poly_mul1(a, b);
	printf("-------------------------------------------------------------------- -		--------\n");
	//print_poly(c);
	print_poly(d);
	return 0;
}
