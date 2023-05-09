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
// 인접 행렬로 표현된 그래프에 대한 깊이 우선 탐색
void dfs_mat(GraphType* g, int v) {
	int w;
	visited[v] = TRUE; // 정점 v의 방문 표시
	printf("정점 %d -> ", v); // 방문한 정점 출력
	for (w = 0; w < g->n; w++) // 인접 정점 탐색
		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat(g, w); //정점 w에서 DFS 새로 시작
}
/*
void bfs_mat(GraphType* g, int v)
{
	int w;
	QueueType q;
	queue_init(&q); // 큐 초기화
	visited[v] = TRUE; // 정점 v 방문 표시
	printf("%d 방문 -> ", v);
	enqueue(&q, v); // 시작 정점을 큐에 저장
	while (!is_empty(&q)) {
		v = dequeue(&q); // 큐에 정점 추출
		for (w = 0; w < g->n; w++) // 인접 정점 탐색
			if (g->adj_mat[v][w] && !visited[w]) {
				visited[w] = TRUE; // 방문 표시
				printf("%d 방문 -> ", w);
				enqueue(&q, w); // 방문한 정점을 큐에 저장
			}
	}
}
*/
void bfs_mat(GraphType* g, int v) {
	int w;
	int queue[MAX_VERTICES], front = -1, rear = -1;
	visited[v] = TRUE; // 시작 정점을 방문 표시
	queue[++rear] = v; // 시작 정점을 큐에 저장
	while (front != rear) { // 큐가 공백이 아닐 때까지 반복
		v = queue[++front]; // 큐에서 정점 추출 후 출력
		printf("%d 방문 -> ", v);
		for (w = 0; w < g->n; w++) { // 인접 정점 탐색
			if (g->adj_mat[v][w] && !visited[w]) { // 인접하고 미방문이면 큐에 저장
				visited[w] = TRUE; // 방문 표시
				queue[++rear] = w; // 큐에 저장
			}
		}
	}
}

/*
int main(void) {
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	for (int i = 0; i < 4; i++)
		insert_vertex(g, i);
	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 2, 3);
	printf("깊이 우선 탐색\n");
	dfs_mat(g, 0);
	printf("\n");
	free(g);
	return 0;
}
*/
int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	for (int i = 0; i < 6; i++)
		insert_vertex(g, i);
	insert_edge(g, 0, 2);
	insert_edge(g, 2, 1);
	insert_edge(g, 2, 3);
	insert_edge(g, 0, 4);
	insert_edge(g, 4, 5);
	insert_edge(g, 1, 5);
	printf("너비 우선 탐색\n");
	bfs_mat(g, 0);
	printf("\n");
	free(g);
	return 0;
}

