#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;
// ���� �ʱ�ȭ �Լ�
void init_stack(StackType* s)
{
	s->top = -1;
}
// ���� ���� ���� �Լ�
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// �����Լ�
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else {
		s->data[++(s->top)] = item; //s->top++; s->data[s->top];
	}
}
// �����Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)--]; //e = s->data[s->top]; s->top--; return e;
}

int num[100];
int count = 0;
int a;

int check_matching(const char* in)
{
	StackType s;
	char ch, open_ch;
	int i, n = strlen(in); // n= ���ڿ��� ����
	
	init_stack(&s); // ������ �ʱ�ȭ
	for (i = 0; i < n; i++) {
		a = i;
		ch = in[i]; // ch = ���� ����
		switch (ch) {
		case '(': case '[': case '{':
			push(&s, ch);
			count++;
			num[count] = i;
			printf("%d, %d/\n", count, num[count]);
			break;

		case ')': case ']': case '}':
			if (is_empty(&s)) return 0;
			else {
				open_ch = pop(&s);
				if ((open_ch == '(' && ch != ')') || (open_ch == '[' && ch != ']') || (open_ch == '{' && ch != '}')) 
				{
					return 0;
				}
				break;
			}
		}
	}
	if (!is_empty(&s)) return 0; // ���ÿ� ���������� ����
	return 1;
}

int main(void)
{
	char* p = "A(x) = 24.5*(x+func(x, y))*(r*r*3.14/[7%10*sqrt(25)];";
	for (int i = 0; i < 10;i++) {
		printf("0123456789");
	}
	if (check_matching(p) == 1)
		printf("%s ��ȣ�˻缺��\n", p);
	else
	{
		printf("%s ��ȣ�˻���� ", p);
		printf("%d ��ġ\n", a);
		printf("%d,%d,%d", count, num[count],a);
	}
	return 0;
}