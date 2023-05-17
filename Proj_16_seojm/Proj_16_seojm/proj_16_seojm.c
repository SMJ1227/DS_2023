#define PROB 3

#if PROB == 1

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES	   100	
#define INF 1000000	/* 무한대 (연결이 없는 경우) */

typedef struct GraphType {
	int n;	// 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];/* 시작정점으로부터의 최단경로 거리 */
int found[MAX_VERTICES];/* 방문한 정점 표시 */
int path[MAX_VERTICES];/* 경유 노드 */

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
	for (i = 0; i < g->n; i++) /* 초기화 */
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
		path[i] = FALSE;
	}
	found[start] = TRUE;    /* 시작 정점 방문 표시 */
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
	// 방향성 그래프에도 적용 가능
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
	//printf("\n정점 %d에서 정점 %d까지의 경로 : ", 0, end);
	//print_path(0, end); // 정점 0에서 정점 end으로 가는 최단경로 출력
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
#define INF 1000000	/* 무한대 (연결이 없는 경우) */

typedef struct GraphType {
	int n;	// 정점의 개수
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
	//printf("\n정점 %d에서 정점 %d까지의 경로 : ", start, end);
	//
	//print_path(path, start, end); // 정점 start에서 정점 end으로 가는 최단경로 출력
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
	int n; // 정점의 개수
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
		fprintf(stderr,"스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr,"스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
// 그래프 초기화
void init(GraphType* g) {
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++) {
		g->adj_list[v] = NULL;
	}
}
// 정점 삽입 연산. 그래프 g에 정점 v를 삽입하는 연산입니다.
void insert_vertex(GraphType* g, int v) {

	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
		//만약 그래프에 정점을 삽입했을때 최대 사이즈보다 크다면 오류 문구를 프린트합니다.
	}
	g->n++;
	//그렇지 않다면 그래프 정점이 하나 증가시킵니다.
}
//그래프 g에 간선(u,v)를 삽입하는 연산입니다.
void insert_edge(GraphType* g, int u, int v) {
	GraphNode* node;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
		//정점 u 또는 v의 번호가 그래프의 정점 개수보다 크다면 오류 문구를 프린트합니다.
	}
	node = (GraphNode*)malloc(sizeof(GraphNode)); //간선을 나타내는 노드를 생성합니다.
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
	//정점 u의 인접리스트에 node를 삽입합니다.
	//위치는 상관이 없으므로 연결리스트의 맨 처음에 삽입합니다.
}
// 위상정렬을 수행한다.
int topo_sort(GraphType* g)
{
	int i;
	StackType s;
	GraphNode* node;

	// 모든 정점의 진입 차수를 계산
	int* in_degree = (int*)malloc(g->n * sizeof(int));
	for (i = 0; i < g->n; i++)			// 초기화
		in_degree[i] = 0;
	for (i = 0; i < g->n; i++) {
		GraphNode* node = g->adj_list[i];//정점 i에서 나오는 간선들
		while (node != NULL) {
			in_degree[node->vertex]++;
			node = node->link;
		}
	}
	// 진입 차수가 0인 정점을 스택에 삽입
	init(&s);
	for (i = 0; i < g->n; i++) {
		if (in_degree[i] == 0) push(&s, i);
	}
	// 위상 순서를 생성 
	while (!is_empty(&s)) {
		int w;
		w = pop(&s);
		printf("정점 %d ->", w);		//정점 출력
		node = g->adj_list[w];	//각 정점의 진입 차수를 변경
		while (node != NULL) {
			int u = node->vertex;
			in_degree[u]--;			//진입 차수를 감소
			if (in_degree[u] == 0) push(&s, u);
			node = node->link;   // 다음 정점
		}
	}
	free(in_degree);
	printf("\n");
	return (i == g->n);	// 반환값이 1이면 성공, 0이면 실패
}

#endif