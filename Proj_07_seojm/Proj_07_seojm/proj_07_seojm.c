#define _CRT_SECURE_NO_WARNINGS
#define PROB 1

#if PROB == 1

#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5

typedef struct {
	char name[10]; // 과목명
	char teacher[10]; // 교수님
	struct info {
		int score; // 학점
		struct time {
			char day[3];
			int time;
		};
	};
}element;

typedef struct { // 데큐 타입
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} DequeType;

// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 초기화
void init_deque(DequeType* q)
{
	q->front = q->rear = 0;
}
// 공백 상태 검출 함수
int is_empty(DequeType* q)
{
	return (q->front == q->rear);
}
// 포화 상태 검출 함수
int is_full(DequeType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// 원형데큐 출력 함수
void deque_print(DequeType* q)
{
	element elem;
	printf("DEQUE<front=%d rear=%d> :\n", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			elem = q->data[i];
			printf("교과목명 : %s, 담당교수 : %s, 수업시간: %s요일 %d교시\n", elem.name, elem.teacher, elem.day, elem.time);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	else {
		printf("데큐가 비었음\n");
	}
	printf("\n");
}
// 삽입 함수
void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// 삭제 함수
element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
// 삭제 함수
element get_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
void add_front(DequeType* q, element val)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}
element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}
element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[q->rear];
}

int main(void)
{
	DequeType queue;
	element data1 = { "자료구조","오황석" ,{4, {"화", 1}} };//, "화", 2, "수", 1, "수", 2}} };
	element data2 = { "컴퓨터구조","김경철",{4, {"월", 3}} };//, "월", 4, "목", 6, "목", 7}} };
	element data3 = { "선형대수","이용희",{3, {"월", 8}} };//, "월", 9, "금", 3}} };
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

typedef struct { // 요소 타입
	int id;
	int arrival_time;
	int service_time;
} element;

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
	{
		count++;
		return 0;
	}
		//error("큐가 포화상태입니다");
	else {
		q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
		q->data[q->rear] = item;
	}
}
// 삭제 함수
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
		//printf("현재시각=%d\n", clock);
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
			//printf("고객 %d이 %d분에 들어옵니다. 업무처리시간= %d분\n", customer.id, customer.arrival_time, customer.service_time);
		}
		if (service_time > 0) {
			//printf("고객 %d 업무처리중입니다. \n", service_customer);
			service_time--;
		}
		else {
			if (!is_empty(&queue)) {
				element customer = dequeue(&queue);
				service_customer = customer.id;
				service_time = customer.service_time;
				//printf("고객 %d이 %d분에 업무를 시작합니다. 대기시간은 %d분이었습니다.\n", customer.id, clock, clock - customer.arrival_time);
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
	printf("큐의 갯수: %d개\n", MAX_QUEUE_SIZE);
	for (int i = 0; i < 5; i++) {
		printf("Menu %d %d개 서비스, 누적대기시간: %d, 평균서비스시간: %lf\n", i, num[i], wait_time[i], (double)wait_time[i] / num[i]);
	}
	printf("취소된 주문 : %d개\n", count);
	printf("=============================\n");
	return 0;
}

#endif
