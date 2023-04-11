#define _CRT_SEUCURE_NO_WARNIKNGS
#define PROB 1

#if PROB == 1

#include <stdio.h>
#include <stdlib.h>
#define MAX_LIST_SIZE 100 // 리스트의 최대크기

typedef int element; // 항목의 정의
typedef struct {
	element array[MAX_LIST_SIZE]; // 배열 정의
	int size; // 현재 리스트에 저장된 항목들의 개수
} SortedList;
// 오류 처리 함수
void error(char* message) {
	fprintf	(stderr,"%s\n", message);
	exit(1);
}
// 리스트 초기화 함수
void init(SortedList* L){
	L->size	= 0;
}
// 리스트가 비어 있으면 1을 반환// 그렇지 않으면0을 반환
int is_empty(SortedList * L){
	return L->size == 0;
}
// 리스트가 가득차 있으면 1을 반환// 그렇지 많으면 1을 반환
int is_full(SortedList * L){
	return L->size == MAX_LIST_SIZE;
}
element get_entry(SortedList* L, int pos)
{
	if (pos < 0 || pos >= L->size)
		error("위치 오류");
	return L->array[pos];
}
// 리스트 출력
void display(SortedList* L)
{
	int i;
	for (i = 0; i < L->size; i++)
		printf("%d->", L->array[i]);
	printf("\n");
}
void insert_last(SortedList* L, element item)
{
	if (L->size >= MAX_LIST_SIZE) {
		error("리스트 오버플로우");
	}
	L->array[L->size++] = item;
}
void insert(SortedList* L, int pos, element item)
{
	if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
		for (int i = (L->size - 1); i >= pos; i--)
			L->array[i + 1] = L->array[i];
		L->array[pos] = item;
		L->size++;
	}
}
element delete(SortedList* L, int item)
{
	//element item;
	int i = 0;
	for (i; i <= L->size; i++) {
		if (item == L->array[i]) {
			break;
		}
	}
	//if (pos < 0 || pos >= L->size)
	//	error("위치 오류");
	//item = L->array[pos];
	for (i; i < (L->size - 1); i++)
		L->array[i] = L->array[i + 1];
	L->size--;
	return i;
}
element get_length(SortedList* L) {
	return L->size;
}

int main(void) {
	SortedList list;
	//필요한 초기화 코드 추가
	int item;
	char ch;

	srand(100); // 동일한 패턴을 찾기 위해 seed 값 100 부여함
	while (1) {
		item = rand();
		insert_last(&list, item);
		display(&list);
		ch = getch();
		if (ch == 'q') break;
	}
	printf("get_length : %d \n", get_length(&list));
	printf("is_empty : %d, is_full : %d \n",is_empty(&list), is_full(&list));
	printf("get_entry : %d위치의 데이터는 %d\n", 5, get_entry(&list, 5));
	//printf("is_in_list : %d의 위치는 %d \n", 5415, is_in_list(&list, 5415));
	//printf("is_in_list : %d의 위치는 %d \n", 10, is_in_list(&list, 10));
	printf("delete : %d의 위치는 %d \n", 5415, delete(&list, 5415));
	//display(&list);
	//printf("call clear\n");
	//clear(&list);
	//display(&list);
	//printf("리스트 길이 %d \n", get_length(&list));

	//종료하기 전에 수행해야 할 코드 추가
	return 0;
}



#elif PROB == 2

#endif