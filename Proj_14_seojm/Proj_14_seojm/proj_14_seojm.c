#define PROB 2

#if PROB == 1

#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50
#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICES];

typedef struct GraphType {
	int n; // 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;
// 그래프 초기화
void init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}
// 정점 삽입 연산
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}
// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}
// 그래프의 행렬 출력
void printf_graph_matrix(GraphType* g) {
	int i, j;
	printf("   : 0  1  2  3  4  5  6  7  8  9 10\n");
	printf("------------------------------------\n");
	for (i = 0; i < g->n; i++) {
		printf("%2d :", i);
		for (j = 0; j < g->n; j++) {
			printf("%2d ", g->adj_mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
// 인접 행렬로 표현된 그래프에 대한 깊이 우선 탐색
void dfs_mat(GraphType* g, int v) {
	int w;
	visited[v] = TRUE; // 정점 v의 방문 표시
	printf("[%d] -> ", v); // 방문한 정점 출력
	for (w = 0; w < g->n; w++) // 인접 정점 탐색
		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat(g, w); //정점 w에서 DFS 새로 시작
}
// 넓이 우선 탐색
void bfs_mat(GraphType* g, int v) {
	int w;
	int queue[MAX_VERTICES], front = -1, rear = -1;
	visited[v] = TRUE; // 시작 정점을 방문 표시
	queue[++rear] = v; // 시작 정점을 큐에 저장
	while (front != rear) { // 큐가 공백이 아닐 때까지 반복
		v = queue[++front]; // 큐에서 정점 추출 후 출력
		printf("[%d] -> ", v);
		for (w = 0; w < g->n; w++) { // 인접 정점 탐색
			if (g->adj_mat[v][w] && !visited[w]) { // 인접하고 미방문이면 큐에 저장
				visited[w] = TRUE; // 방문 표시
				queue[++rear] = w; // 큐에 저장
			}
		}
	}
}

int main(void)
{
	GraphType* g;
	int i;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	//그래프 초기화 및 간선 추가
	for (int i = 0; i < 11; i++) {
		insert_vertex(g, i);
	}
	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 1, 3);
	insert_edge(g, 2, 3);
	insert_edge(g, 2, 4);
	insert_edge(g, 4, 5);
	insert_edge(g, 4, 7);
	insert_edge(g, 4, 8);
	insert_edge(g, 5, 6);
	insert_edge(g, 6, 7);
	insert_edge(g, 6, 10);
	insert_edge(g, 7, 9);
	insert_edge(g, 7, 10);
	insert_edge(g, 8, 9);
	//print matrix of graph
	printf("그래프의 행렬 출력\n");
	printf_graph_matrix(g);
	//깊이 우선 탐색
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("깊이 우선 탐색\n");
	dfs_mat(g, 0);
	printf("\n\n");
	//너비 우선 탐색
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("너비 우선 탐색\n");
	bfs_mat(g, 0);
	printf("\n");
	free(g);
	return 0;
}


#elif PROB == 2

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

int visited[MAX_VERTICES];

typedef int element;
typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
} GraphNode;
typedef struct GraphType {
	int n; // 정점의 개수
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;
typedef struct QueueType {
	element data[MAX_VERTICES];
	int front, rear;
} QueueType;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void queue_init(QueueType* q) {
	q->rear = -1;
	q->front = -1;
}
int is_empty(QueueType* q) {
	if (q->front == NULL) return 1;
	else return 0;
}
void enqueue(QueueType* q, int item) {
	q->data[++(q->rear)] = item;
}
int dequeue(QueueType* q) {
	if (is_empty(q)) {
		error("큐가 공백상태입니다.");
		return -1;
	}
	int item = q->data[++(q->front)];
	return item;
}
void queue_print(QueueType* q)
{
	for (int i = 0; i < MAX_VERTICES; i++) {
		if (i <= q->front || i > q->rear)
			printf("");
		else
			printf("%d ", q->data[i]);
	}
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
//그래프 g의 각 정점에 대한 인접리스트를 출력하는 연산입니다.
void print_adj_list(GraphType* g) {
	printf("그래프 인접리스트\n");
	for (int i = 0; i < g->n; i++) {
		//i가 0부터 정점의 개수만큼 까지 하나씩 증가하는 for문입니다.
		GraphNode* p = g->adj_list[i];
		//i를 그래프의 인접리스트 정점에 대입합니다.
		printf(" %2d : ", i);
		//i에 대한 인접리스트를 출력합니다.)
		while (p != NULL) {
			printf("%d -> ", p->vertex);
			p = p->link;
			//정점을 출력합니다.
		}
		printf("NULL ");
		printf("\n");
	}
	printf("\n");
}
// 인접 리스트로 표현된 그래프에 대한 깊이 우선 탐색
void dfs_list(GraphType* g, int v) {
	GraphNode* w;
	visited[v] = TRUE; // 정점 v의 방문 표시
	printf("[%d] -> ", v); // 방문한 정점 출력
	for (w = g->adj_list[v]; w; w = w->link)// 인접 정점 탐색
		if (!visited[w->vertex])
			dfs_list(g, w->vertex); //정점 w에서 DFS 새로 시작
}
// 인접 리스트 넓이 우선 탐색
void bfs_list(GraphType* g, int v) {
	GraphNode* w;
	QueueType q;
	queue_init(&q); // 큐 초기 화
	visited[v] = TRUE; // 정점 v 방문 표시
	printf("[%d] -> ", v);
	enqueue(&q, v); // 시작정점을 큐에 저장
	while (!is_empty(&q)) {
		v = dequeue(&q); // 큐에 저장된 정점 선택
		for (w = g->adj_list[v]; w; w = w->link) //인접 정점 탐색
			if (!visited[w->vertex]) { // 미방문 정점 탐색
				visited[w->vertex] = TRUE; // 방문 표시
				printf("[%d] -> ", w->vertex);
				enqueue(&q, w->vertex); //정점을 큐에 삽입
				//queue_print(&q);
				//if (is_empty(&q)) printf("@");
			}
	}
}

int main(void)
{
	GraphType* g;
	int i;
	
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	//그래프 초기화 및 간선 추가
	for (i = 0; i < 11; i++) {
		insert_vertex(g, i);
	}
	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 1, 3);
	insert_edge(g, 2, 3);
	insert_edge(g, 2, 4);
	insert_edge(g, 4, 5);
	insert_edge(g, 4, 7);
	insert_edge(g, 4, 8);
	insert_edge(g, 5, 6);
	insert_edge(g, 6, 7);
	insert_edge(g, 6, 10);
	insert_edge(g, 7, 9);
	insert_edge(g, 7, 10);
	insert_edge(g, 8, 9);
	// 그래프 출력
	print_adj_list(g);
	// 깊이 우선 탐색
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = FALSE;
	printf("깊이 우선 탐색\n");
	dfs_list(g, 0);
	printf("\n\n");
	// 너비 우선 탐색
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = FALSE;
	printf("너비 우선 탐색\n");
	bfs_list(g, 0);
	printf("\n");
	free(g);
	return 0;
}

#endif