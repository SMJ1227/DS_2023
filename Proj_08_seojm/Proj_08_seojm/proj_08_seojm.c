#define _CRT_SEUCURE_NO_WARNIKNGS
#define PROB 1

#if PROB == 1

#include <stdio.h>
#include <stdlib.h>
#define MAX_LIST_SIZE 100 // ����Ʈ�� �ִ�ũ��

typedef int element; // �׸��� ����
typedef struct {
	element array[MAX_LIST_SIZE]; // �迭 ����
	int size; // ���� ����Ʈ�� ����� �׸���� ����
} SortedList;
// ���� ó�� �Լ�
void error(char* message) {
	fprintf	(stderr,"%s\n", message);
	exit(1);
}
// ����Ʈ �ʱ�ȭ �Լ�
void init(SortedList* L){
	L->size	= 0;
}
// ����Ʈ�� ��� ������ 1�� ��ȯ// �׷��� ������0�� ��ȯ
int is_empty(SortedList * L){
	return L->size == 0;
}
// ����Ʈ�� ������ ������ 1�� ��ȯ// �׷��� ������ 1�� ��ȯ
int is_full(SortedList * L){
	return L->size == MAX_LIST_SIZE;
}
element get_entry(SortedList* L, int pos)
{
	if (pos < 0 || pos >= L->size)
		error("��ġ ����");
	return L->array[pos];
}
// ����Ʈ ���
void display(SortedList* L)
{
	int i;
	for (i = 0; i < L->size; i++)
		printf("%d->", L->array[i]);
	printf("\n");
}

void add(SortedList* L, element item) {
	if (L->size >= MAX_LIST_SIZE) {
		error("����Ʈ �����÷ο�");
	}
	int temp;
	L->array[L->size++] = item;
	for (int i = 0; i < L->size; i++) {
		for (int j = 0; j < (L->size - 1) - i; j++) {
			if (L->array[j] > L->array[j + 1]) {	// ���� ���� ���
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
			return i; //��ġ ����
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
		printf("�̹� ��������Դϴ�.\n");
	L->size = 0;
}
element is_in_list(SortedList* L, int item) {
	int i;
	for (i = 0; i <= L->size; i++) {
		if (item == L->array[i]) {
			return i; //��ġ ����
		}
	}
	return -1;
}
int main(void) {
	SortedList list;
	//�ʿ��� �ʱ�ȭ �ڵ� �߰�
	int item;
	char ch;
	list.size = 0;

	srand(100); // ������ ������ ã�� ���� seed �� 100 �ο���
	while (1) {
		item = rand();
		add(&list, item);
		display(&list);
		ch = getch();
		if (ch == 'q') break;
	}
	printf("�迭�� �̿��Ͽ� ���� ����Ʈ �����\n");
	printf("get_length : %d \n", get_length(&list));
	printf("is_empty : %d, is_full : %d \n",is_empty(&list), is_full(&list));
	printf("get_entry : %d��ġ�� �����ʹ� %d\n", 5, get_entry(&list, 5));
	printf("is_in_list : %d�� ��ġ�� %d \n", 5415, is_in_list(&list, 5415));
	printf("is_in_list : %d�� ��ġ�� %d \n", 10, is_in_list(&list, 10));
	printf("delete : %d�� ��ġ�� %d \n", 5415, delete(&list, 5415));
	display(&list);
	printf("call clear\n");
	clear(&list);
	display(&list);
	printf("����Ʈ ���� %d \n", get_length(&list));
	//�����ϱ� ���� �����ؾ� �� �ڵ� �߰�
	return 0;
}

#elif PROB == 2

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode { // ��� Ÿ���� ����ü�� �����Ѵ�.
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
// ��� pre �ڿ� ���ο� ��� ����
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
// pre�� ����Ű�� ����� ���� ��带 �����Ѵ�.
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
	//�ʿ��� �ʱ�ȭ �ڵ� �߰�
	srand(100); // ������ ������ ã�� ���� seed �� 100 �ο���

	while (1) {
		item = rand();
		head = insert_first(head, item);
		display(head);
		ch = getch();
		if (ch == 'q') break;
	}
	//printf("get_length : %d \n", get_length(&list));
	//printf("is_empty : %d, is_full : %d \n", is_empty(&list), is_full(&list));
	//printf("get_entry : %d��ġ�� �����ʹ� %d\n", 5, get_entry(&list, 5));
	//printf("is_in_list : %d�� ��ġ�� %d \n", 5415, is_in_list(&list, 5415));
	//printf("is_in_list : %d�� ��ġ�� %d \n", 10, is_in_list(&list, 10));
	//printf("delete : %d�� ��ġ�� %d \n", 5415, delete(&list, 5415));
	//display(&list);
	//printf("call clear\n");
	//clear(&list);
	//display(&list);
	//printf("����Ʈ ���� %d \n", get_length(&list));

	//�����ϱ� ���� �����ؾ� �� �ڵ� �߰�
	return 0;
}


#endif