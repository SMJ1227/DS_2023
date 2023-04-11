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

void add(SortedList* L, element item) {
	if (L->size >= MAX_LIST_SIZE) {
		error("리스트 오버플로우");
	}
	int temp;
	L->array[L->size++] = item;
	for (int i = 0; i < L->size; i++) {
		for (int j = 0; j < (L->size - 1) - i; j++) {
			if (L->array[j] > L->array[j + 1]) {	// 버블 정렬 사용
				temp = L->array[j];
				L->array[j] = L->array[j + 1];
				L->array[j + 1] = temp;
			}
		}
	}
}
element delete(SortedList* L, int item){
	int i, j;
	for (i = 0; i <= L->size; i++) {
		if (item == L->array[i]) {
			for (j = i; j <= L->size; j++) {
				L->array[j] = L->array[j + 1];
			}
			L->size--;
			return i; //위치 리턴
		}
	}
	return -1;
}
element get_length(SortedList* L) {
	return L->size;
}
void clear(SortedList* L)
{
	if (is_empty(L))
		printf("이미 공백상태입니다.\n");
	L->size = 0;
}
element is_in_list(SortedList* L, int item) {
	int i;
	for (i = 0; i <= L->size; i++) {
		if (item == L->array[i]) {
			return i; //위치 리턴
		}
	}
	return -1;
}
int main(void) {
	SortedList list;
	//필요한 초기화 코드 추가
	int item;
	char ch;
	list.size = 0;

	srand(100); // 동일한 패턴을 찾기 위해 seed 값 100 부여함
	while (1) {
		item = rand();
		add(&list, item);
		display(&list);
		ch = getch();
		if (ch == 'q') break;
	}
	printf("배열을 이용하여 정렬 리스트 만들기\n");
	printf("get_length : %d \n", get_length(&list));
	printf("is_empty : %d, is_full : %d \n",is_empty(&list), is_full(&list));
	printf("get_entry : %d위치의 데이터는 %d\n", 5, get_entry(&list, 5));
	printf("is_in_list : %d의 위치는 %d \n", 5415, is_in_list(&list, 5415));
	printf("is_in_list : %d의 위치는 %d \n", 10, is_in_list(&list, 10));
	printf("delete : %d의 위치는 %d \n", 5415, delete(&list, 5415));
	display(&list);
	printf("call clear\n");
	clear(&list);
	display(&list);
	printf("리스트 길이 %d \n", get_length(&list));
	//종료하기 전에 수행해야 할 코드 추가
	return 0;
}

#elif PROB == 2

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode { // 노드 타입을 구조체로 정의한다.
	element data;
	struct ListNode* link;
} ListNode;
ListNode* head = NULL;

ListNode* insert_first(ListNode* head, int value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));//(1)
	p->data = value; // (2)
	p->link = head; //(3)
	head = p; //(4)
	return head;
}
// 노드 pre 뒤에 새로운 노드 삽입
ListNode* insert(ListNode* head, ListNode* pre, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	//(1)
	p->data = value; //(2)
	p->link = pre->link; //(3)
	pre->link = p; //(4)
	return head; //(5)
}
ListNode* delete_first(ListNode* head)
{
	ListNode* removed;
	if (head == NULL) return NULL;
	removed = head; // (1)
	head = removed->link; // (2)
	free(removed); // (3)
	return head; // (4)
}
// pre가 가리키는 노드의 다음 노드를 삭제한다.
ListNode* delete(ListNode* head, ListNode* pre)
{
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link; // (2)
	free(removed); // (3)
	return head; // (4)
}
void display(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("\n");
}

int main(void) {
	ListNode list;
	int item;
	char ch;
	//필요한 초기화 코드 추가
	srand(100); // 동일한 패턴을 찾기 위해 seed 값 100 부여함

	while (1) {
		item = rand();
		head = insert_first(head, item);
		display(head);
		ch = getch();
		if (ch == 'q') break;
	}
	//printf("get_length : %d \n", get_length(&list));
	//printf("is_empty : %d, is_full : %d \n", is_empty(&list), is_full(&list));
	//printf("get_entry : %d위치의 데이터는 %d\n", 5, get_entry(&list, 5));
	//printf("is_in_list : %d의 위치는 %d \n", 5415, is_in_list(&list, 5415));
	//printf("is_in_list : %d의 위치는 %d \n", 10, is_in_list(&list, 10));
	//printf("delete : %d의 위치는 %d \n", 5415, delete(&list, 5415));
	//display(&list);
	//printf("call clear\n");
	//clear(&list);
	//display(&list);
	//printf("리스트 길이 %d \n", get_length(&list));

	//종료하기 전에 수행해야 할 코드 추가
	return 0;
}


#endif