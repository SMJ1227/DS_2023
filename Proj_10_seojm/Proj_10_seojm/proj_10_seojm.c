#define _CRT_SECURE_NO_WARNINGS
#define PROB 2

#if PROB == 1

#include <stdio.h>
#include <malloc.h>
#include <limits.h>

typedef struct WORLD_COORDINATE {
	int x;
	int y;
	int z;
} element;
typedef struct StackNode{
	element data;
	struct StackNode* link;
} StackNode;
typedef struct{
	StackNode* top;
} LinkedStackType;
// �ʱ�ȭ �Լ�
void init(LinkedStackType* s){
	s->top = NULL;
}
// ���� ���� ���� �Լ�
int is_empty(LinkedStackType* s)
{
	return (s->top == NULL);
}
// ��ȭ ���� ���� �Լ�
int is_full(LinkedStackType* s)
{
	return 0;
}
// ���� �Լ�
void push(LinkedStackType* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}
void print_stack(LinkedStackType* s)
{
	printf("========���� ����========\n");
	StackNode* p = s->top;
	if (p == NULL) {
		printf("< NULL > <--- TOP\n");
	}
	for (p = s->top; p != NULL; p = p->link) {
		if (p == s->top) {
			printf("<%d, %d, %d> <--- TOP\n", p->data.x, p->data.y, p->data.z);
		}
		else {
			printf("<%d, %d, %d>\n", p->data.x, p->data.y, p->data.z);
		}
	}
	printf("=========================\n");
}
// ���� �Լ�
element pop(LinkedStackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "������ �������\n");
		element e = { INT_MIN, INT_MIN, INT_MIN };
		return e;
	}
	else {
		StackNode* temp = s->top;
		element data = temp->data;
		s->top = s->top->link;
		free(temp);
		return data;
	}
}
//�� �Լ�
int main(void) {
	LinkedStackType	s;
	element item;
	init(&s);
	print_stack(&s);
	item.x = 1; item.y = 1; item.z = 1;
	printf("Push item\n");
	push(&s, item); print_stack(&s);
	item.x = 2; item.y = 2; item.z = 2;
	printf("Push item\n");
	push(&s, item); print_stack(&s);
	item.x = 3; item.y = 3; item.z = 3;
	printf("Push item\n");
	push(&s, item); print_stack(&s);
	item.x = 4; item.y = 4; item.z = 4;
	printf("Push item\n");
	push(&s, item); print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	return 0;
}

#elif PROB == 2

#include <stdio.h>
#include <malloc.h>
#include <limits.h>

typedef struct WORLD_COORDINATE {
	int x;
	int y;
	int z;
}element;

typedef struct QueueNode { // ť�� ����� Ÿ��
	element data;
	struct QueueNode* link;
} QueueNode;
typedef struct {
	QueueNode* front, * rear;
} LinkedlistQueue;
// �ʱ�ȭ �Լ�
void init(LinkedlistQueue* q) {
	q->front = q->rear = NULL;
}
// ���� ���� ���� �Լ�
int is_empty(LinkedlistQueue* q)
{
	return (q->rear == NULL);
}
// ��ȭ ���� ���� �Լ�
int is_full(LinkedlistQueue* q)
{
	return 0;
}
// ���� �Լ�
void enqueue(LinkedlistQueue* q, element item)
{
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	temp->data = item; // ������ ����
	temp->link = NULL; // ��ũ �ʵ带 NULL
	if (is_empty(q)) { // ť�� �����̸�
		q->front = temp;
		q->rear = temp;
	}
	else { // ť�� ������ �ƴϸ�
		q->rear->link = temp; // ������ �߿�
		q->rear = temp;
	}
}
// ���� �Լ�
element dequeue(LinkedlistQueue* q)
{
	QueueNode* temp = q->front;
	element data;
	if (is_empty(q)) { // �������
		fprintf(stderr, "������ �������\n");
		element e = { INT_MIN, INT_MIN, INT_MIN };
		return e;
	}
	else {
		data = temp->data; // �����͸� ������.
		q->front = q->front->link; // front�� �������
		if (q->front == NULL) // ���� ����
			q->rear = NULL;
		free(temp); // �����޸� ����
		return data; // ������ ��ȯ
	}
}
void print_queue(LinkedlistQueue* q)
{
	printf("=========ť ����=========\n");
	QueueNode* p = q->front;
	if (p == NULL) {
		printf("< NULL > <--- Front, Rear\n");
	}
	else {
		for (p = q->front; p != NULL; p = p->link) {
			if (p == q->front) {
				if (q->front == q->rear) {
					printf("<%d, %d, %d> <--- Front, Rear\n", p->data.x, p->data.y, p->data.z);
				}
				else {
					printf("<%d, %d, %d> <--- Front\n", p->data.x, p->data.y, p->data.z);
				}
			}
			else if (p == q->rear) {
				printf("<%d, %d, %d> <--- Rear\n", p->data.x, p->data.y, p->data.z);
			}
			else {
				printf("<%d, %d, %d>\n", p->data.x, p->data.y, p->data.z);
			}
		}
	}
	printf("=========================\n");
}
int main(void)
{
	LinkedlistQueue* queue = (LinkedlistQueue*)malloc(sizeof(LinkedlistQueue));
	element item;
	init(queue); // ť �ʱ�ȭ
	print_queue(queue);
	printf("enqueue item \n");
	item.x = 1, item.y = 1, item.z = 1;
	enqueue(queue, item); print_queue(queue);
	printf("enqueue item \n");
	item.x = 2, item.y = 2, item.z = 2;
	enqueue(queue, item); print_queue(queue);
	printf("enqueue item \n");
	item.x = 3, item.y = 3, item.z = 3;
	enqueue(queue, item); print_queue(queue);
	printf("enqueue item \n");
	item.x = 4, item.y = 4, item.z = 4;
	enqueue(queue, item); print_queue(queue);
	printf("enqueue item \n");
	item.x = 5, item.y = 5, item.z = 5;
	enqueue(queue, item); print_queue(queue);
	printf("dequeue item\n");
	item = dequeue(queue);
	printf("Dequeue�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(queue);
	printf("dequeue item\n");
	item = dequeue(queue);
	printf("Dequeue�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(queue);
	printf("dequeue item\n");
	item = dequeue(queue);
	printf("Dequeue�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(queue);
	printf("dequeue item\n");
	item = dequeue(queue);
	printf("Dequeue�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(queue);
	printf("dequeue item\n");
	item = dequeue(queue);
	printf("Dequeue�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(queue);
	printf("dequeue item\n");
	item = dequeue(queue);
	printf("Dequeue�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(queue);
}

#endif