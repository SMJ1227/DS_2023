#define _CRT_SECURE_NO_WARNINGS
#define PROB 1 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성
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
// 생성 함수
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}
// 초기화 함수
void init(HeapType* h) {
	h->heap_size = 0;
}
// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다. // 삽입 함수
void insert_max_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size);
	// 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // 새로운 노드를 삽입
}
// 삭제 함수
element delete_max_heap(HeapType* h) {
	int parent, child;
	element item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드중 더 큰 자식노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) break;
		// 한단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child; //인덱스변경
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
	element* list, * sorted_list; //원데이터와 정렬된 데이터 각각 저장용
	int s_time, e_time;
	srand(100);
	list = (element*)malloc(sizeof(element) * SIZE);
	sorted_list = (element*)malloc(sizeof(element) * SIZE);
	for (int i = 0; i < SIZE; i++) list[i].key = rand();
	printf("정수형 데이터 %d개 정렬 \n", SIZE);
	if (SIZE < 100) {
		for (int i = 0; i < SIZE; i++) printf("%d ", list[i].key);
		printf("\n\n");
	}
	s_time = clock();
	heap_sort(list, SIZE);
	for (int i = 0; i < SIZE; i++) sorted_list[i] = list[i];
	e_time = clock();
	printf("Heap Sort 걸린 시간 : %d msec\n", e_time - s_time);
	if (SIZE < 100) {
		for (int i = 0; i < SIZE; i++) printf("%d ", sorted_list[i].key);
		printf("\n\n");
	}
	s_time = clock();
	//selection_sort(list, sorted_list, SIZE);
	e_time = clock();
	printf("Selection Sort 걸린 시간 : %d msec\n", e_time - s_time);
	if (SIZE < 100) {
		for (int i = 0; i < SIZE; i++) printf("%d ", sorted_list[i].key);
		printf("\n");
	}
	return 0;
	}

#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성
#endif