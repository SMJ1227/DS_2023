#define _CRT_SECURE_NO_WARNINGS
#define PROB 1

#if PROB == 1

#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5

typedef struct {
	char name[10]; // �����
	char teacher[10]; // ������
	struct info {
		int score; // ����
		struct time {
			char day[3];
			int time;
		};
	};
}element;

typedef struct { // ��ť Ÿ��
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} DequeType;

// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// �ʱ�ȭ
void init_deque(DequeType* q)
{
	q->front = q->rear = 0;
}
// ���� ���� ���� �Լ�
int is_empty(DequeType* q)
{
	return (q->front == q->rear);
}
// ��ȭ ���� ���� �Լ�
int is_full(DequeType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// ������ť ��� �Լ�
void deque_print(DequeType* q)
{
	element elem;
	printf("DEQUE<front=%d rear=%d> :\n", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			elem = q->data[i];
			printf("������� : %s, ��米�� : %s, �����ð�: %s���� %d����\n", elem.name, elem.teacher, elem.day, elem.time);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	else {
		printf("��ť�� �����\n");
	}
	printf("\n");
}
// ���� �Լ�
void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// ���� �Լ�
element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
// ���� �Լ�
element get_front(DequeType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
void add_front(DequeType* q, element val)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}
element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}
element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[q->rear];
}

int main(void)
{
	DequeType queue;
	element data1 = { "�ڷᱸ��","��Ȳ��" ,{4, {"ȭ", 1}} };//, "ȭ", 2, "��", 1, "��", 2}} };
	element data2 = { "��ǻ�ͱ���","���ö",{4, {"��", 3}} };//, "��", 4, "��", 6, "��", 7}} };
	element data3 = { "�������","�̿���",{3, {"��", 8}} };//, "��", 9, "��", 3}} };
	init_deque(&queue);
	deque_print(&queue);
	add_front(&queue, data1);
	deque_print(&queue);
	add_rear(&queue, data2);
	deque_print(&queue);
	add_front(&queue, data3);
	deque_print(&queue);
	delete_rear(&queue);
	deque_print(&queue);
	delete_front(&queue);
	deque_print(&queue);
	delete_front(&queue);
	deque_print(&queue);
	delete_rear(&queue);
	deque_print(&queue);
	return 0;
}

#elif PROB == 2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_QUEUE_SIZE 10

int count = 0;

typedef struct { // ��� Ÿ��
	int id;
	int arrival_time;
	int service_time;
} element;

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
	{
		count++;
		return 0;
	}
		//error("ť�� ��ȭ�����Դϴ�");
	else {
		q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
		q->data[q->rear] = item;
	}
}
// ���� �Լ�
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

int main(void)
{
	int minutes = 10000;
	int total_wait = 0;
	int total_customers = 0;
	int service_time = 0;
	int service_customer;

	int num[5] = { 0 };
	int wait_time[5] = { 0 };
	
	QueueType queue;
	init_queue(&queue);

	srand(time(NULL));
	for (int clock = 0; clock < minutes; clock++) {
		//printf("����ð�=%d\n", clock);
		if ((rand() % 10) < 3) {
			element customer;
			customer.id = total_customers++;
			customer.arrival_time = clock;
			customer.service_time = (rand() % 5 + 1) * 5;
			enqueue(&queue, customer);
			switch (customer.service_time)
			{
			case 5:
				num[0]++;
				break;
			case 10:
				num[1]++;
				break;
			case 15:
				num[2]++;
				break;
			case 20:
				num[3]++;
				break;
			case 25:
				num[4]++;
				break;
			}
			//printf("�� %d�� %d�п� ���ɴϴ�. ����ó���ð�= %d��\n", customer.id, customer.arrival_time, customer.service_time);
		}
		if (service_time > 0) {
			//printf("�� %d ����ó�����Դϴ�. \n", service_customer);
			service_time--;
		}
		else {
			if (!is_empty(&queue)) {
				element customer = dequeue(&queue);
				service_customer = customer.id;
				service_time = customer.service_time;
				//printf("�� %d�� %d�п� ������ �����մϴ�. ���ð��� %d���̾����ϴ�.\n", customer.id, clock, clock - customer.arrival_time);
				total_wait += clock - customer.arrival_time;
				switch (customer.service_time)
				{
				case 5:
					wait_time[0] += clock - customer.arrival_time;
					break;
				case 10:
					wait_time[1] += clock - customer.arrival_time;
					break;
				case 15:
					wait_time[2] += clock - customer.arrival_time;
					break;
				case 20:
					wait_time[3] += clock - customer.arrival_time;
					break;
				case 25:
					wait_time[4] += clock - customer.arrival_time;
					break;
				}
			}
		}
	}
	printf("========== RESULTS ==========\n");
	printf("ť�� ����: %d��\n", MAX_QUEUE_SIZE);
	for (int i = 0; i < 5; i++) {
		printf("Menu %d %d�� ����, �������ð�: %d, ��ռ��񽺽ð�: %lf\n", i, num[i], wait_time[i], (double)wait_time[i] / num[i]);
	}
	printf("��ҵ� �ֹ� : %d��\n", count);
	printf("=============================\n");
	return 0;
}

#endif
