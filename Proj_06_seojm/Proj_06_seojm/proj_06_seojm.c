# define _CRT_SECURE_NO_WARNINGS
# define PROB 1

#if PROB == 1

#include <stdio.h>
#include <stdlib.h>

// ===== ����ť �ڵ� ���� ======
#define MAX_QUEUE_SIZE 1000000

typedef struct {
	int n;
	int t;
}element;
typedef struct { // ť Ÿ��
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;
// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// ���� ���� ���� �Լ�
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}
// ���� ���� ���� �Լ�
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}
// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// ���� �Լ�
void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// ���� �Լ�
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
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

	printf("���� ���̷��� �� �Է� : ");
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