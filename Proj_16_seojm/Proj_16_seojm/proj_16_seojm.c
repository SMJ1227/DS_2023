#define PROB 3

#if PROB == 1

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES	   100	
#define INF 1000000	/* ���Ѵ� (������ ���� ���) */

typedef struct GraphType {
	int n;	// ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];/* �����������κ����� �ִܰ�� �Ÿ� */
int found[MAX_VERTICES];/* �湮�� ���� ǥ�� */
int path[MAX_VERTICES];/* ���� ��� */

int choose(int distance[], int n, int found[]) {
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
void print_status(GraphType* g) {
	printf("distance:");
	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF) {
			printf("  *");
		}
		else {
			printf(" %2d", distance[i]);
		}
	}
	printf("\n\tfound:   ");
	for (int i = 0; i < g->n; i++) {
		printf(" %2d", found[i]);
	}	
	printf("\n");
}
void shortest_path(GraphType* g, int start) {
	int i, u, w;
	for (i = 0; i < g->n; i++) /* �ʱ�ȭ */
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
		path[i] = FALSE;
	}
	found[start] = TRUE;    /* ���� ���� �湮 ǥ�� */
	distance[start] = 0;
	for (i = 1; i <= g->n; i++) {
		printf("STEP %d: ", i);
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		for (w = 0; w < g->n; w++)
			if (!found[w])
				if (distance[u] + g->weight[u][w] < distance[w])
					distance[w] = distance[u] + g->weight[u][w];
	}
	/*printf("\nPrint Path Array\n");
	printf("Index  :");
	for (i = 0; i < g->n; i++) {
		printf(" %2d", i);
	}
	printf("\nPath[i]:");
	for (i = 0; i < g->n; i++) {
		printf(" %2d", path[i]);
	}*/
}

int main(void) {
	// test data 1
	/*
	GraphType g = { 7,
	{{ 0, 7, INF, INF, 3, 10, INF },
	{ 7, 0, 4, 10, 2, 6, INF },
	{ INF, 4, 0, 2, INF, INF, INF },
	{ INF, 10, 2, 0, 11, 9, 4 },
	{ 3, 2, INF, 11, 0, INF, 5 },
	{ 10, 6, INF, 9, INF, 0, INF },
	{ INF, INF, INF, 4, 5, INF, 0 } }
	};
	*/
	// ���⼺ �׷������� ���� ����
	// test data 2
	/*
	GraphType g = {6,
	{{ 0, 50, 45, 10, INF, INF},
	{ INF, 0, 10, 15, INF, INF},
	{ INF, INF, 0, INF, 30, INF},
	{ 20, INF, INF, 0, 15, INF},
	{ INF, 20, 35, INF, 0, INF},
	{ INF, INF, INF, INF, 3, 0}}
	};
	*/	
	// test data 3
	///*
	GraphType g = { 7,
	{{ 0,  7,  INF, INF,   3,  10, INF },
	{ 7,  0,    4,  10,   2,   6, INF },
	{ INF,  4,    0,   2, INF, INF, INF },
	{ INF, 10,    2,   0,  11,   9,   4 },
	{ 3,  2,  INF,  11,   0, INF,   5 },
	{ 10,  6,  INF,   9, INF,   0, INF },
	{ INF, INF, INF,   4,   5, INF,   0 } }
};
	//*/
	shortest_path(&g, 0);
	//int end = 6;
	//printf("\n���� %d���� ���� %d������ ��� : ", 0, end);
	//print_path(0, end); // ���� 0���� ���� end���� ���� �ִܰ�� ���
	printf("\n");
	return 0;
}

#elif PROB == 2

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES	   100	
#define INF 1000000	/* ���Ѵ� (������ ���� ���) */

typedef struct GraphType {
	int n;	// ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int A[MAX_VERTICES][MAX_VERTICES];
int path[MAX_VERTICES][MAX_VERTICES];

void printA(GraphType* g) {
	int i, j;
	printf("     ");
	for (i = 0; i < g->n; i++) {
		printf(" %3d", i);
	}
	printf("\n==================================\n");
	for (i = 0; i < g->n; i++) {
		printf("%3d |", i);
		for (j = 0; j < g->n; j++) {
			if (A[i][j] == INF)
				printf("   *");
			else
				printf(" %3d", A[i][j]);
		}
		printf("\n");
	}
	printf("==================================\n\n");
}

void floyd(GraphType* g)
{

	int i, j, k;
	for (i = 0; i < g->n; i++)
		for (j = 0; j < g->n; j++)
			A[i][j] = g->weight[i][j];
	printA(g);

	for (k = 0; k < g->n; k++) {
		for (i = 0; i < g->n; i++)
			for (j = 0; j < g->n; j++)
				if (A[i][k] + A[k][j] < A[i][j])
					A[i][j] = A[i][k] + A[k][j];
		printA(g);
	}
}

int main(void) {
	int start, end;
	// test data 1
	GraphType g = { 7,
	{{ 0, 7, INF, INF, 3, 10, INF },
	{ 7, 0, 4, 10, 2, 6, INF },
	{ INF, 4, 0, 2, INF, INF, INF },
	{ INF, 10, 2, 0, 11, 9, 4 },
	{ 3, 2, INF, 11, 0, INF, 5 },
	{ 10, 6, INF, 9, INF, 0, INF },
	{ INF, INF, INF, 4, 5, INF, 0 } }
	};
	/*
	// test data 2
	GraphType g = { 7,
	{{ 0, 7, INF, 5,INF, INF, INF},
	{ 7, 0, 8, 9, 7, INF, INF},
	{ INF, 8, 0, INF, 5, INF, INF},
	{ 5, 9, INF, 0, 15, 6, INF },
	{ INF, 7, 5, 15, 0, 8, 9},
	{ INF, INF, INF, 6, 8, 0, 11 },
	{ INF, INF, INF, INF, 9, 11, 0 } }
	};
	*/
	floyd(&g);
	//start = 0; end = 3;
	//printf("\n���� %d���� ���� %d������ ��� : ", start, end);
	//
	//print_path(path, start, end); // ���� start���� ���� end���� ���� �ִܰ�� ���
	printf("\n");
	return 0;
}

#elif PROB == 3
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

int visited[MAX_VERTICES];

typedef int element;
typedef struct {
	element data[MAX_VERTICES];
	int top;
} StackType;
typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
} GraphNode;
typedef struct GraphType {
	int n; // ������ ����
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;
void init_stack(StackType* s) {
	s->top = -1;
}
int is_empty(StackType* s) {
	return (s->top == -1);
}
int is_full(StackType* s) {
	return (s->top == (MAX_VERTICES - 1));
}
void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr,"���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr,"���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
// �׷��� �ʱ�ȭ
void init(GraphType* g) {
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++) {
		g->adj_list[v] = NULL;
	}
}
// ���� ���� ����. �׷��� g�� ���� v�� �����ϴ� �����Դϴ�.
void insert_vertex(GraphType* g, int v) {

	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
		//���� �׷����� ������ ���������� �ִ� ������� ũ�ٸ� ���� ������ ����Ʈ�մϴ�.
	}
	g->n++;
	//�׷��� �ʴٸ� �׷��� ������ �ϳ� ������ŵ�ϴ�.
}
//�׷��� g�� ����(u,v)�� �����ϴ� �����Դϴ�.
void insert_edge(GraphType* g, int u, int v) {
	GraphNode* node;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
		//���� u �Ǵ� v�� ��ȣ�� �׷����� ���� �������� ũ�ٸ� ���� ������ ����Ʈ�մϴ�.
	}
	node = (GraphNode*)malloc(sizeof(GraphNode)); //������ ��Ÿ���� ��带 �����մϴ�.
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
	//���� u�� ��������Ʈ�� node�� �����մϴ�.
	//��ġ�� ����� �����Ƿ� ���Ḯ��Ʈ�� �� ó���� �����մϴ�.
}
// ���������� �����Ѵ�.
int topo_sort(GraphType* g)
{
	int i;
	StackType s;
	GraphNode* node;

	// ��� ������ ���� ������ ���
	int* in_degree = (int*)malloc(g->n * sizeof(int));
	for (i = 0; i < g->n; i++)			// �ʱ�ȭ
		in_degree[i] = 0;
	for (i = 0; i < g->n; i++) {
		GraphNode* node = g->adj_list[i];//���� i���� ������ ������
		while (node != NULL) {
			in_degree[node->vertex]++;
			node = node->link;
		}
	}
	// ���� ������ 0�� ������ ���ÿ� ����
	init(&s);
	for (i = 0; i < g->n; i++) {
		if (in_degree[i] == 0) push(&s, i);
	}
	// ���� ������ ���� 
	while (!is_empty(&s)) {
		int w;
		w = pop(&s);
		printf("���� %d ->", w);		//���� ���
		node = g->adj_list[w];	//�� ������ ���� ������ ����
		while (node != NULL) {
			int u = node->vertex;
			in_degree[u]--;			//���� ������ ����
			if (in_degree[u] == 0) push(&s, u);
			node = node->link;   // ���� ����
		}
	}
	free(in_degree);
	printf("\n");
	return (i == g->n);	// ��ȯ���� 1�̸� ����, 0�̸� ����
}

#endif