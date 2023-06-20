#define PROB 2

#if PROB == 1

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct element {
	int name;
	int fish; 
	int shell;
	int squid; // 10���� �ø���
} element;

typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;

ListNode* insert(ListNode* head, ListNode* pre, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = NULL;
	if (pre == NULL) {
		if (head == NULL) {
			head = p;
		}
		else {
			ListNode* last = head;
			while (last->link != NULL) {
				last = last->link;
			}
			last->link = p;
		}
	}
	else {
		p->link = pre->link;
		pre->link = p;
	}
	return head;
}

void add_value(ListNode* head, int position, int field, int value) {
	ListNode* current = head;
	int count = 0;
	while (current != NULL && count < position) {
		current = current->link;
		count++;
	}
	if (current != NULL) {
		switch (field) {
		case 1:
			current->data.fish += value;
			break;
		case 2:
			current->data.shell += value;
			break;
		case 3:
			current->data.squid += value;
			break;
		default:
			printf("��ȿ���� ���� �ʵ��Դϴ�.\n");
			break;
		}
	}
	else {
		printf("�ش� ��ġ�� ������Ʈ�� ã�� �� �����ϴ�.\n");
	}
}

ListNode* delete_first(ListNode* head) {
	if (head == NULL)
		return NULL;

	ListNode* removed = head;
	head = removed->link;
	free(removed);
	return head;
}

ListNode* delete(ListNode* head, int position) {
	if (head == NULL)
		return NULL;
	if (position == 0) {
		ListNode* removed = head;
		head = head->link;
		free(removed);
		return head;
	}
	ListNode* pre = head;
	ListNode* target = head->link;
	int count = 1;
	while (target != NULL && count < position) {
		pre = pre->link;
		target = target->link;
		count++;
	}
	if (target != NULL) {
		pre->link = target->link;
		free(target);
	}

	return head;
}

void delete_value(ListNode* head, int position, int field, int value) {
	ListNode* current = head;
	int count = 0;
	while (current != NULL && count < position) {
		current = current->link;
		count++;
	}
	if (current != NULL) {
		switch (field) {
		case 0:
			current->data.fish -= value;
			break;
		case 1:
			current->data.shell -= value;
			break;
		case 2:
			current->data.squid -= value;
			break;
		default:
			printf("��ȿ���� ���� �ʵ��Դϴ�.\n");
			break;
		}
	}
	else {
		printf("�ش� ��ġ�� ������Ʈ�� ã�� �� �����ϴ�.\n");
	}
}

void print_list(ListNode* head) {
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("(Position%d, Fish: %d, Shell: %d, Squid: %d)\n", p->data.name, p->data.fish, p->data.shell, p->data.squid);
	printf("\n");
}

ListNode* search_list(ListNode* head, element x) {
	ListNode* p = head;
	while (p != NULL) {
		if (p->data.fish == x.fish && p->data.shell == x.shell && p->data.squid == x.squid)
			return p;
		p = p->link;
	}
	return NULL; // Ž�� ����
}

int get_value(ListNode* head, int position, int field) {
	ListNode* current = head;
	int count = 0;
	while (current != NULL && count < position) {
		current = current->link;
		count++;
	}
	if (current != NULL) {
		switch (field) {
		case 0:
			return current->data.fish;
		case 1:
			return current->data.shell;
		case 2:
			return current->data.squid;
		default:
			printf("��ȿ���� ���� �ʵ��Դϴ�.\n");
			break;
		}
	}
	else {
		printf("�ش� ��ġ�� ������Ʈ�� ã�� �� �����ϴ�.\n");
	}
	return -1; // ���� �߻� �� -1 ��ȯ
}
ListNode* sort_value_up(ListNode* head, int position) {
	int swapped;
	ListNode* ptr1;
	ListNode* lptr = NULL;
	if (head == NULL)
		return NULL;
	do {
		swapped = 0;
		ptr1 = head;
		while (ptr1->link != lptr) {
			int current_field;
			int next_field;
			switch (position) {
			case 1:
				current_field = ptr1->data.fish;
				next_field = ptr1->link->data.fish;
				break;
			case 2:
				current_field = ptr1->data.shell;
				next_field = ptr1->link->data.shell;
				break;
			case 3:
				current_field = ptr1->data.squid;
				next_field = ptr1->link->data.squid;
				break;
			default:
				printf("��ȿ���� ���� �ʵ��Դϴ�.\n");
				return head;
			}
			if (current_field > next_field) {
				element temp = ptr1->data;
				ptr1->data = ptr1->link->data;
				ptr1->link->data = temp;
				swapped = 1;
			}
			ptr1 = ptr1->link;
		}
		lptr = ptr1;
	} while (swapped);
	return head;
}

ListNode* sort_value_down(ListNode* head, int position) {
	int swapped;
	ListNode* ptr1;
	ListNode* lptr = NULL;
	if (head == NULL)
		return NULL;
	do {
		swapped = 0;
		ptr1 = head;

		while (ptr1->link != lptr) {
			int current_field;
			int next_field;

			switch (position) {
			case 1:
				current_field = ptr1->data.fish;
				next_field = ptr1->link->data.fish;
				break;
			case 2:
				current_field = ptr1->data.shell;
				next_field = ptr1->link->data.shell;
				break;
			case 3:
				current_field = ptr1->data.squid;
				next_field = ptr1->link->data.squid;
				break;
			default:
				printf("��ȿ���� ���� �ʵ��Դϴ�.\n");
				return head;
			}
			if (current_field < next_field) {  // ������������ ����
				element temp = ptr1->data;
				ptr1->data = ptr1->link->data;
				ptr1->link->data = temp;
				swapped = 1;
			}
			ptr1 = ptr1->link;
		}
		lptr = ptr1;
	} while (swapped);
	return head;
}

int main(void) {
	int randomNumber;
	srand(time(NULL));
	int position = 0; //����
	int field = 0; //ǰ��
	int thing = 0; // �մ��� �簣 ����

	ListNode* head = NULL;
	element e;
	for (int i = 0; i < 7; i++) {
		e.name = i;
		e.fish = 10; // 500
		e.shell = 10; // 600
		e.squid = 10; // 700
		head = insert(head, NULL, e);
	}
	printf("===========================�ùķ��̼� ����=========================\n");
	print_list(head);
	printf("\n");
	int miss_man = 0; //��ģ �մ�
	int miss_num = 0; //��ģ ����
	
	for (int j = 0; j < 30; j++) {
		position = rand() % 7;
		field = rand() % 3;
		thing = (rand() % 10) + 1;
		printf("================================%dȸ��=============================\n", j+1);
		if (get_value(head, position, field) < thing) {
			miss_man++;
			miss_num += thing;
			printf("�ֹ� ���� / position:%d / field:%d / thing:%d / ������ �մ�:%d / ���� ���� �ֹ�:%d\n", position, field, thing, miss_man, miss_num);
		}
		else {
			delete_value(head, position, field, thing);
			printf("�ֹ� ���� / position:%d / field:%d / thing:%d / ������ �մ�:%d / ���� ���� �ֹ�:%d\n", position, field, thing, miss_man, miss_num);
		}
		print_list(head);
		printf("\n");
	}
	return 0;
}

#elif PROB == 2

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES	   100	
#define INF 	   1000000	/* ���Ѵ� (������ ���� ���) */

typedef struct element {
	int name;
	int field0;
	int field1;
	int field2; // 10���� �ø���
} element;

typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;

ListNode* insert(ListNode* head, ListNode* pre, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = NULL;
	if (pre == NULL) {
		if (head == NULL) {
			head = p;
		}
		else {
			ListNode* last = head;
			while (last->link != NULL) {
				last = last->link;
			}
			last->link = p;
		}
	}
	else {
		p->link = pre->link;
		pre->link = p;
	}
	return head;
}

void add_value(ListNode* head, int position, int field, int value) {
	ListNode* current = head;
	int count = 0;
	while (current != NULL && count < position) {
		current = current->link;
		count++;
	}
	if (current != NULL) {
		switch (field) {
		case 0:
			current->data.field0 += value;
			break;
		case 1:
			current->data.field1 += value;
			break;
		case 2:
			current->data.field2 += value;
			break;
		default:
			printf("��ȿ���� ���� �ʵ��Դϴ�.\n");
			break;
		}
	}
	else {
		printf("�ش� ��ġ�� ������Ʈ�� ã�� �� �����ϴ�.\n");
	}
}

ListNode* delete_first(ListNode* head) {
	if (head == NULL)
		return NULL;

	ListNode* removed = head;
	head = removed->link;
	free(removed);
	return head;
}

ListNode* delete(ListNode* head, int position) {
	if (head == NULL)
		return NULL;
	if (position == 0) {
		ListNode* removed = head;
		head = head->link;
		free(removed);
		return head;
	}
	ListNode* pre = head;
	ListNode* target = head->link;
	int count = 1;
	while (target != NULL && count < position) {
		pre = pre->link;
		target = target->link;
		count++;
	}
	if (target != NULL) {
		pre->link = target->link;
		free(target);
	}

	return head;
}

void delete_value(ListNode* head, int position, int field, int value) {
	ListNode* current = head;
	int count = 0;
	while (current != NULL && count < position) {
		current = current->link;
		count++;
	}
	if (current != NULL) {
		switch (field) {
		case 0:
			current->data.field0 -= value;
			break;
		case 1:
			current->data.field1 -= value;
			break;
		case 2:
			current->data.field2 -= value;
			break;
		default:
			printf("��ȿ���� ���� �ʵ��Դϴ�.\n");
			break;
		}
	}
	else {
		printf("�ش� ��ġ�� ������Ʈ�� ã�� �� �����ϴ�.\n");
	}
}

void print_list(ListNode* head) {
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("(Position%d, Field0: %d, field1: %d, field2: %d)\n", p->data.name, p->data.field0, p->data.field1, p->data.field2);
	printf("\n");
}

ListNode* search_list(ListNode* head, element x) {
	ListNode* p = head;
	while (p != NULL) {
		if (p->data.field0 == x.field0 && p->data.field1 == x.field1 && p->data.field2 == x.field2)
			return p;
		p = p->link;
	}
	return NULL; // Ž�� ����
}

int get_value(ListNode* head, int position, int field) {
	ListNode* current = head;
	int count = 0;
	while (current != NULL && count < position) {
		current = current->link;
		count++;
	}
	if (current != NULL) {
		switch (field) {
		case 0:
			return current->data.field0;
		case 1:
			return current->data.field1;
		case 2:
			return current->data.field2;
		default:
			printf("��ȿ���� ���� �ʵ��Դϴ�.\n");
			break;
		}
	}
	else {
		printf("�ش� ��ġ�� ������Ʈ�� ã�� �� �����ϴ�.\n");
	}
	return -1; // ���� �߻� �� -1 ��ȯ
}
ListNode* sort_value_up(ListNode* head, int position) {
	int swapped;
	ListNode* ptr1;
	ListNode* lptr = NULL;
	if (head == NULL)
		return NULL;
	do {
		swapped = 0;
		ptr1 = head;
		while (ptr1->link != lptr) {
			int current_field;
			int next_field;
			switch (position) {
			case 1:
				current_field = ptr1->data.field0;
				next_field = ptr1->link->data.field0;
				break;
			case 2:
				current_field = ptr1->data.field1;
				next_field = ptr1->link->data.field1;
				break;
			case 3:
				current_field = ptr1->data.field2;
				next_field = ptr1->link->data.field2;
				break;
			default:
				printf("��ȿ���� ���� �ʵ��Դϴ�.\n");
				return head;
			}
			if (current_field > next_field) {
				element temp = ptr1->data;
				ptr1->data = ptr1->link->data;
				ptr1->link->data = temp;
				swapped = 1;
			}
			ptr1 = ptr1->link;
		}
		lptr = ptr1;
	} while (swapped);
	return head;
}

ListNode* sort_value_down(ListNode* head, int position) {
	int swapped;
	ListNode* ptr1;
	ListNode* lptr = NULL;
	if (head == NULL)
		return NULL;
	do {
		swapped = 0;
		ptr1 = head;

		while (ptr1->link != lptr) {
			int current_field;
			int next_field;

			switch (position) {
			case 1:
				current_field = ptr1->data.field0;
				next_field = ptr1->link->data.field0;
				break;
			case 2:
				current_field = ptr1->data.field1;
				next_field = ptr1->link->data.field1;
				break;
			case 3:
				current_field = ptr1->data.field2;
				next_field = ptr1->link->data.field2;
				break;
			default:
				printf("��ȿ���� ���� �ʵ��Դϴ�.\n");
				return head;
			}
			if (current_field < next_field) {  // ������������ ����
				element temp = ptr1->data;
				ptr1->data = ptr1->link->data;
				ptr1->link->data = temp;
				swapped = 1;
			}
			ptr1 = ptr1->link;
		}
		lptr = ptr1;
	} while (swapped);
	return head;
}

//�׷��� �ڵ� ����
typedef struct GraphType {
	int n;	// ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];/* �����������κ����� �ִܰ�� �Ÿ� */
int found[MAX_VERTICES];		/* �湮�� ���� ǥ�� */

int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}
//
void shortest_path(GraphType* g, int start)
{
	int i, u, w;
	for (i = 0; i < g->n; i++) /* �ʱ�ȭ */
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE;    /* ���� ���� �湮 ǥ�� */
	distance[start] = 0;
	for (i = 0; i < g->n - 1; i++) {
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		for (w = 0; w < g->n; w++)
			if (!found[w])
				if (distance[u] + g->weight[u][w] < distance[w])
					distance[w] = distance[u] + g->weight[u][w];
	}
	printf("���� ���� �ִ� �Ÿ�(distance):\n");
	for (i = 0; i < g->n; i++) {
		printf("%d -> %d: %d\n", start, i, distance[i]);
	}
}
int search_shortest(GraphType* g, int start) {
	shortest_path(g, start);

	int nearestVertex = -1;
	int shortestDistance = INT_MAX;

	for (int i = 0; i < g->n; i++) {
		if (i != start) {
			if (distance[i] < shortestDistance) {
				nearestVertex = i;
				shortestDistance = distance[i];
			}
		}
	}
	return nearestVertex;
}

#define MAX_N 10
int search_nth_shortest(GraphType* g, int start, int n) {
	shortest_path(g, start);

	int nearestVertices[MAX_N];
	int shortestDistances[MAX_N];

	for (int i = 0; i < n; i++) {
		nearestVertices[i] = -1;
		shortestDistances[i] = INT_MAX;
	}
	for (int i = 0; i < g->n; i++) {
		if (i != start) {
			for (int j = 0; j < n; j++) {
				if (distance[i] < shortestDistances[j]) {
					for (int k = n - 1; k > j; k--) {
						nearestVertices[k] = nearestVertices[k - 1];
						shortestDistances[k] = shortestDistances[k - 1];
					}
					nearestVertices[j] = i;
					shortestDistances[j] = distance[i];
					break;
				}
			}
		}
	}
	return nearestVertices[n - 1];
}

int main(void) {
	GraphType g = { 7,
	{{ 0,  7,  INF, INF,   3,  10, INF },
	{ 7,  0,    4,  10,   2,   6, INF },
	{ INF,  4,    0,   2, INF, INF, INF },
	{ INF, 10,    2,   0,  11,   9,   4 },
	{ 3,  2,  INF,  11,   0, INF,   5 },
	{ 10,  6,  INF,   9, INF,   0, INF },
	{ INF, INF, INF,   4,   5, INF,   0 } }
	};

	int randomNumber;
	srand(time(NULL));
	int position = 0; //����
	int field = 0; //ǰ��
	int thing = 0; // �մ��� �簣 ����

	ListNode* head = NULL;
	element e;
	for (int i = 0; i < 7; i++) {
		e.name = i;
		e.field0 = 10; // 500
		e.field1 = 10; // 600
		e.field2 = 10; // 700
		head = insert(head, NULL, e);
	}

	printf("===========================�ùķ��̼� ����=========================\n");
	print_list(head);
	printf("\n");
	int n = 1;
	int miss_man = 0; //��ģ �մ�
	int miss_num = 0; //��ģ ����
	int nearestNthVertex;
	for (int j = 0; j < 30; j++) {
		position = rand() % 7;
		field = rand() % 3;
		thing = (rand() % 10) + 1;
		printf("================================%dȸ��=============================\n", j + 1);
		if (get_value(head, position, field) < thing) { // �ֹ� ������ �� ������
			for (int n = 1; n <= 7; n++) {
				if (n == 7) {
					if (get_value(head, nearestNthVertex, field) < thing) { // �ֹ� ������ �� ������
						miss_man++;
						miss_num += thing;
						printf("�ֹ� ���� / position:%d / field:%d / thing:%d / ������ �մ�:%d / ���� ���� �ֹ�:%d\n", position, field, thing, miss_man, miss_num);
					}
					else {
						delete_value(head, nearestNthVertex, field, thing);
						printf("�ֹ� ���� / position:%d / field:%d / thing:%d / �����ߴ� ����:%d / ����� ����:%d\n", position, field, thing, position, nearestNthVertex);
						break;
					}
				}
				else {
					nearestNthVertex = search_nth_shortest(&g, position, n);
					if (get_value(head, nearestNthVertex, field) < thing) { continue; } // �ֹ� ������ �� ������ ����n��° ����� ����
					else {
						delete_value(head, nearestNthVertex, field, thing);
						printf("�ֹ� ���� / position:%d / field:%d / thing:%d / �����ߴ� ����:%d / ����� ����:%d\n", position, field, thing, position, nearestNthVertex);
						break;
					}
				}
			}	
		}
		else {
			delete_value(head, position, field, thing);
			printf("�ֹ� ���� / position:%d / field:%d / thing:%d / ������ �մ�:%d / ���� ���� �ֹ�:%d\n", position, field, thing, miss_man, miss_num);
		}
		print_list(head);
		printf("\n");
	}
	return 0;
}

#endif
