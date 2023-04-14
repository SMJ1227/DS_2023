#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];
typedef struct DSongNode { // ���߿��� ��� Ÿ��
	element data;
	struct DSongNode* llink;
	struct DSongNode* rlink;
} DSongNode;
DSongNode* current;
// ���� ���� ����Ʈ�� �ʱ�ȭ
void init(DSongNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}
// ���ο� �����͸� ��� before�� �����ʿ� �����Ѵ�.
void dinsert(DSongNode* before, element data)
{
	DSongNode* newnode = (DSongNode*)malloc(sizeof(DSongNode));
	strcpy(newnode->data, data);
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}
// ��� removed�� �����Ѵ�.
void ddelete(DSongNode* head, DSongNode* removed)
{
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}
// ���� ���� ����Ʈ�� ��带 ���
void print_dlist(DSongNode* phead)
{
	DSongNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		if (p == current) {
			printf("<-| |*%s*| |-> ", p->data);
		}
		else {
			printf("<-| |%s| |-> ", p->data);
		}
	}
	printf("\n");
}
int main(void)
{
	char ch;
	DSongNode* head = (DSongNode*)malloc(sizeof(DSongNode));
	init(head);
	dinsert(head, "Mamamia");
	dinsert(head, "Dancing Queen");
	dinsert(head, "Fernando");
	current = head->rlink;
	print_dlist(head);
	do {
		printf("\n��ɾ �Է��Ͻÿ�(<, >, q): ");
		ch = getchar();
		if (ch == '<') {
			current = current->llink;
			if (current == head)
				current = current->llink;
		}
		else if (ch == '>') {
			current = current->rlink;
			if (current == head)
				current = current->rlink;
		}
		print_dlist(head);
		getchar();
	} while (ch != 'q');
	// ���� �޸� ���� �ڵ带 ���⿡
	for (int i = 0; i < 5; i++) {
		print_dlist(head);
		ddelete(head, head->rlink);
	}
	free(head);
	return 0;
}