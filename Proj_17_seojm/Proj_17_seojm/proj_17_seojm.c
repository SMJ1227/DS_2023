#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 100 // ������ũ�⸦ �����ϸ� �׽�Ʈ
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define MAX_QUEUE_SIZE 10000
#define BUCKETS 10
#define DIGITS 4

typedef int element;
typedef struct { // ť Ÿ��
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE];
} QueueType;
// ���� �Լ�
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void init(QueueType* q) {
	q->rear = -1;
	q->front = -1;
}
int is_full(QueueType* q) {
	if (q->rear == MAX_QUEUE_SIZE - 1)
		return 1;
	else
		return 0;
}
int is_empty(QueueType* q) {
	if (q->front == q->rear)
		return 1;
	else
		return 0;
}

void enqueue(QueueType* q, int item) {
	if (is_full(q)) {
		error("ť�� ��ȭ�����Դϴ�.");
		return;
	}
	q->data[++(q->rear)] = item;
}
int dequeue(QueueType* q) {
	if (is_empty(q)) {
		error("ť�� ��������Դϴ�.");
		return -1;
	}
	int item = q->data[++(q->front)];
	return item;
}


//��������
void selection_sort(int list[], int n) {
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++) 			// �ּڰ� Ž��
			if (list[j] < list[least]) least = j;
		SWAP(list[i], list[least], temp);
	}
}
//��������
void insertion_sort(int list[], int n) {
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--)
			list[j + 1] = list[j]; 		// ���ڵ��� ������ �̵�
		list[j + 1] = key;
	}
}
//��������
void bubble_sort(int list[], int n) {
	int i, j, temp;
	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++) 	// �յ��� ���ڵ带 ���� �� ��ü
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
	}
}
//������
// gap ��ŭ ������ ��ҵ��� ���� ����
// ������ ������ first���� last
inc_insertion_sort(int list[], int first, int last, int gap) {
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		for (j = i - gap; j >= first && key < list[j]; j = j - gap)
			list[j + gap] = list[j];
		list[j + gap] = key;
	}
}
void shell_sort(int list[], int n) { // n = size
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++)		// �κ� ����Ʈ�� ������ gap
			inc_insertion_sort(list, i, n - 1, gap);
	}
}
//��������
int sorted[SIZE]; // �߰� ������ �ʿ�
// i�� ���ĵ� ���ʸ���Ʈ�� ���� �ε���
// j�� ���ĵ� �����ʸ���Ʈ�� ���� �ε���
// k�� ���ĵ� ����Ʈ�� ���� �ε���

void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left; j = mid + 1; k = left;
	// ���� ���ĵ� list�� �պ�
	while (i <= mid && j <= right) {
		if (list[i] <= list[j]) sorted[k++] = list[i++];
		else sorted[k++] = list[j++];
	}
	if (i > mid) 	// ���� �ִ� ���ڵ��� �ϰ� ����
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else 	// ���� �ִ� ���ڵ��� �ϰ� ����
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	// �迭 sorted[]�� ����Ʈ�� �迭 list[]�� ����
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}
void merge_sort(int list[], int left, int right) {
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;              // ����Ʈ�� �յ����
		merge_sort(list, left, mid);     // �κи���Ʈ ����
		merge_sort(list, mid + 1, right);//�κи���Ʈ ����
		merge(list, left, mid, right);    // �պ�
	}
}
//������
int partition(int list[], int left, int right) {
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];
	do {
		do
			low++;
		while (low <= right && list[low] < pivot);
		do
			high--;
		while (high >= left && list[high] > pivot);
		if (low < high) SWAP(list[low], list[high], temp);
	} while (low < high);

	SWAP(list[left], list[high], temp);
	return high;
}
void quick_sort(int list[], int left, int right) {
	if (left < right) {
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}
//��� ����
void radix_sort(int list[], int n) {
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++) init(&queues[b]);	// ť���� �ʱ�ȭ

	for (d = 0; d < DIGITS; d++) {
		for (i = 0; i < n; i++) { // �������� �ڸ����� ���� ť�� �Է�
			int di = (list[i] / factor) % 10;
			enqueue(&queues[di], list[i]);
		}

		for (b = i = 0; b < BUCKETS; b++)			// ���Ͽ��� ������ list�� ��ģ��.
			while (!is_empty(&queues[b]))
				list[i++] = dequeue(&queues[b]);
		factor *= 10;				// �� ���� �ڸ����� ����.
	}
}
//������
#define MAX_ELEMENT 200
typedef struct {
	int key;
} element_heap;
typedef struct {
	element_heap heap[MAX_ELEMENT];
	int heap_size;
} HeapType;
// ���� �Լ�
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}
// �ʱ�ȭ �Լ�
void init_heap(HeapType* h) {
	h->heap_size = 0;
}
// ���� ����� ������ heap_size�� ���� h�� item�� �����Ѵ�. // ���� �Լ�
void insert_max_heap(HeapType* h, element_heap item) {
	int i;
	i = ++(h->heap_size);
	// Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // ���ο� ��带 ����
}
// ���� �Լ�
element_heap delete_max_heap(HeapType* h) {
	int parent, child;
	element_heap item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ�� �� �� ���� �ڽĳ�带 ã�´�.
		if ((child < h->heap_size) &&
			(h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) break;
		// �� �ܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
// �켱 ���� ť�� ������ �̿��� ����
void heap_sort(element_heap a[], int n) {
	int i;
	HeapType* h;
	h = create();
	init(h);
	for (i = 0; i < n; i++) {
		insert_max_heap(h, a[i]);
	}
	for (i = (n - 1); i >= 0; i--) {
		a[i] = delete_max_heap(h);
	}
	free(h);
}



int main(void)
{
	int i, s_time, e_time;
	int* data = (int*)malloc(sizeof(int) * SIZE); // �� ������ ������ �����ͷ� �׽�Ʈ�ϱ� ���� ��������
	int* list = (int*)malloc(sizeof(int) * SIZE); // �������� -> ���ĵ� ������
	*sorted = (int*)malloc(sizeof(int) * SIZE); //���������� ���� �߰� �޸𸮷� �۷ι������� ����
		if (data == NULL || list == NULL || sorted == NULL) {
			printf("������ ������ ���� �޸� �Ҵ� ����\n"); exit(-1);
		}
	printf("���� ��� �� \n");
	printf("Data ũ�� : %d \n\n", SIZE);
	srand(100);
	for (i = 0; i < SIZE; i++) // ���� ���� �� ��� 
		data[i] = rand(); // ���� �߻�
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	selection_sort(list, SIZE); // �������� ȣ�� 
	e_time = clock();
	printf("�������� �ð� : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	insertion_sort(list, SIZE);
	e_time = clock();
	printf("�������� �ð� : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	bubble_sort(list, SIZE);
	e_time = clock();
	printf("�������� �ð� : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	shell_sort(list, SIZE);
	e_time = clock();
	printf("������ �ð� : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	merge_sort(list, 0, SIZE - 1);
	e_time = clock();
	printf("�������� �ð� : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	quick_sort(list, 0, SIZE - 1);
	e_time = clock();
	printf("������ �ð� : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	//heap_sort(list, SIZE);
	e_time = clock();
	printf("������ �ð� : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	radix_sort(list, SIZE); // ������� ȣ�� 
	e_time = clock();
	printf("������� �ð� : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	free(data); free(list); //free(sorted);
	return 0;
}