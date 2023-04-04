# define _CRT_SECURE_NO_WARNINGS
# define PROB 1

#if PROB == 1

#include <stdio.h>
#include <stdlib.h>

// ===== 원형큐 코드 시작 ======
#define MAX_QUEUE_SIZE 1000000

typedef struct {
	int n;
	int t;
}element;
typedef struct { // 큐 타입
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;
// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 공백 상태 검출 함수
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}
// 공백 상태 검출 함수
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}
// 포화 상태 검출 함수
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// 삽입 함수
void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// 삭제 함수
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

int main(void)
{
	//QueueType queue;
	element x;
	QueueType* queue = (QueueType*)malloc(sizeof(QueueType));
	init_queue(&queue);
	x.n = 1;
	x.t = 0;
	enqueue(&queue, x);

	printf("현재 바이러스 수 입력 : ");
	scanf("%d", &x.n);
	x.t++;
	enqueue(&queue, x);
	printf("%d, %d", x.n, x.t);
	return 0;
}


#elif PROB == 2

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	return 0;
}
#endif