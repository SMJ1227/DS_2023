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
void insert_last(SortedList* L, element item)
{
	if (L->size >= MAX_LIST_SIZE) {
		error("����Ʈ �����÷ο�");
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
	//	error("��ġ ����");
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
	//�ʿ��� �ʱ�ȭ �ڵ� �߰�
	int item;
	char ch;

	srand(100); // ������ ������ ã�� ���� seed �� 100 �ο���
	while (1) {
		item = rand();
		insert_last(&list, item);
		display(&list);
		ch = getch();
		if (ch == 'q') break;
	}
	printf("get_length : %d \n", get_length(&list));
	printf("is_empty : %d, is_full : %d \n",is_empty(&list), is_full(&list));
	printf("get_entry : %d��ġ�� �����ʹ� %d\n", 5, get_entry(&list, 5));
	//printf("is_in_list : %d�� ��ġ�� %d \n", 5415, is_in_list(&list, 5415));
	//printf("is_in_list : %d�� ��ġ�� %d \n", 10, is_in_list(&list, 10));
	printf("delete : %d�� ��ġ�� %d \n", 5415, delete(&list, 5415));
	//display(&list);
	//printf("call clear\n");
	//clear(&list);
	//display(&list);
	//printf("����Ʈ ���� %d \n", get_length(&list));

	//�����ϱ� ���� �����ؾ� �� �ڵ� �߰�
	return 0;
}



#elif PROB == 2

#endif