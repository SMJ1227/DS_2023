#define _CRT_SECURE_NO_WARNINGS
#define PROB 1 // ������ ������ �����ϰ� �ش� ���� ��ȣ�� �����Ͽ� �׽�Ʈ
#if PROB == 1
// 1�� ������ �ذ��ϱ� ���� ���α׷� �ۼ�
#include <stdio.h>
#include <stdlib.h>
#define SIZE 8
typedef struct {
	int key;
} element;
typedef struct {
	element heap[SIZE];
	int heap_size;
} HeapType;
// ���� �Լ�
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}
// �ʱ�ȭ �Լ�
void init(HeapType* h) {
	h->heap_size = 0;
}
// ���� ����� ������ heap_size�� ���� h�� item�� �����Ѵ�. // ���� �Լ�
void insert_max_heap(HeapType* h, element item) {
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
element delete_max_heap(HeapType* h) {
	int parent, child;
	element item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ���� �� ū �ڽĳ�带 ã�´�.
		if ((child < h->heap_size) &&
			(h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) break;
		// �Ѵܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child; //�ε�������
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
void heap_sort(element a[], int n) {
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
	element* list, * sorted_list; //�������Ϳ� ���ĵ� ������ ���� �����
	int s_time, e_time;
	srand(100);
	list = (element*)malloc(sizeof(element) * SIZE);
	sorted_list = (element*)malloc(sizeof(element) * SIZE);
	for (int i = 0; i < SIZE; i++) list[i].key = rand();
	printf("������ ������ %d�� ���� \n", SIZE);
	if (SIZE < 100) {
		for (int i = 0; i < SIZE; i++) printf("%d ", list[i].key);
		printf("\n\n");
	}
	s_time = clock();
	heap_sort(list, SIZE);
	for (int i = 0; i < SIZE; i++) sorted_list[i] = list[i];
	e_time = clock();
	printf("Heap Sort �ɸ� �ð� : %d msec\n", e_time - s_time);
	if (SIZE < 100) {
		for (int i = 0; i < SIZE; i++) printf("%d ", sorted_list[i].key);
		printf("\n\n");
	}
	s_time = clock();
	//selection_sort(list, sorted_list, SIZE);
	e_time = clock();
	printf("Selection Sort �ɸ� �ð� : %d msec\n", e_time - s_time);
	if (SIZE < 100) {
		for (int i = 0; i < SIZE; i++) printf("%d ", sorted_list[i].key);
		printf("\n");
	}
	return 0;
	}

#elif PROB == 2
// 2�� ������ �ذ��ϱ� ���� ���α׷� �ۼ�
#endif