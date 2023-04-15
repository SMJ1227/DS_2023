#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];
typedef struct DSongNode { // 이중연결 노드 타입
	element data;
	struct DSongNode* llink;
	struct DSongNode* rlink;
} DSongNode;
DSongNode* current;
// 이중 연결 리스트를 초기화
void init(DSongNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}
// 새로운 데이터를 노드 before의 오른쪽에 삽입한다.
void dinsert(DSongNode* before, element data)
{
	DSongNode* newnode = (DSongNode*)malloc(sizeof(DSongNode));
	strcpy(newnode->data, data);
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
	current = newnode;
}
// 노드 removed를 삭제한다.
void ddelete(DSongNode* head, DSongNode* removed)
{
	current = current->rlink;
	if (current == head)
		current = current->rlink;
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}
// 이중 연결 리스트의 노드를 출력
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
void print_song_menu(void)
{
	printf("\n\n---- Song Menu ---- \n");
	printf(" a : print all songs \n");
	printf(" c : print current song\n");
	printf(" n : add new song in playlist \n");
	printf(" d : delete current song \n");
	printf(" > : next song \n");
	printf(" < : previous song \n");
	printf(" q : quit \n");
	return;
}

int main(void)
{
	char sub_menu;
	char songname[100];
	DSongNode* head = (DSongNode*)malloc(sizeof(DSongNode));
	init(head);
	current = head->rlink;
	do {
		print_song_menu();
		printf("\n명령어를 입력하시오(a, c, n, d, <, >, q): ");
		scanf(" %c", &sub_menu);
		printf("Selected song menu : %c \n", sub_menu);
		switch (sub_menu) {
		case 'a':
			print_dlist(head);
			break;
		case 'c':
			printf("current song : %s\n", current->data);
			break;
		case 'n':
			printf("Song name : ");
			scanf("%s", songname);
			dinsert(head, songname);
			print_dlist(head);
			break;
		case 'd':
			ddelete(head, current->data);
			print_dlist(head);
			break;
		case '<':
			current = current->llink;
			if (current == head)
				current = current->llink;
			break;
		case '>':
			current = current->rlink;
			if (current == head)
				current = current->rlink;
			break;
		}
	} while (sub_menu != 'q');
	// 동적 메모리 해제 코드를 여기에
	for (int i = 0; i < 5; i++) {
		print_dlist(head);
		ddelete(head, head->rlink);
	}
	free(head);
	return 0;
}