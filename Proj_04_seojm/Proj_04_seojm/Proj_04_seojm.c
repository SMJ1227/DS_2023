#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;
// 스택 초기화 함수
void init_stack(StackType* s)
{
	s->top = -1;
}
// 공백 상태 검출 함수
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입함수
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else {
		s->data[++(s->top)] = item; //s->top++; s->data[s->top];
	}
}
// 삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
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
	int i, n = strlen(in); // n= 문자열의 길이
	
	init_stack(&s); // 스택의 초기화
	for (i = 0; i < n; i++) {
		a = i;
		ch = in[i]; // ch = 다음 문자
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
	if (!is_empty(&s)) return 0; // 스택에 남아있으면 오류
	return 1;
}

int main(void)
{
	char* p = "A(x) = 24.5*(x+func(x, y))*(r*r*3.14/[7%10*sqrt(25)];";
	for (int i = 0; i < 10;i++) {
		printf("0123456789");
	}
	if (check_matching(p) == 1)
		printf("%s 괄호검사성공\n", p);
	else
	{
		printf("%s 괄호검사실패 ", p);
		printf("%d 위치\n", a);
		printf("%d,%d,%d", count, num[count],a);
	}
	return 0;
}