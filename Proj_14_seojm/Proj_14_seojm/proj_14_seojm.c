#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50
#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICES];

typedef struct GraphType {
	int n; // ������ ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;
// �׷��� �ʱ�ȭ
void init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}
// ���� ���� ����
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}
// ���� ���� ����
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}
// ���� ��ķ� ǥ���� �׷����� ���� ���� �켱 Ž��
void dfs_mat(GraphType* g, int v) {
	int w;
	visited[v] = TRUE; // ���� v�� �湮 ǥ��
	printf("���� %d -> ", v); // �湮�� ���� ���
	for (w = 0; w < g->n; w++) // ���� ���� Ž��
		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat(g, w); //���� w���� DFS ���� ����
}
/*
void bfs_mat(GraphType* g, int v)
{
	int w;
	QueueType q;
	queue_init(&q); // ť �ʱ�ȭ
	visited[v] = TRUE; // ���� v �湮 ǥ��
	printf("%d �湮 -> ", v);
	enqueue(&q, v); // ���� ������ ť�� ����
	while (!is_empty(&q)) {
		v = dequeue(&q); // ť�� ���� ����
		for (w = 0; w < g->n; w++) // ���� ���� Ž��
			if (g->adj_mat[v][w] && !visited[w]) {
				visited[w] = TRUE; // �湮 ǥ��
				printf("%d �湮 -> ", w);
				enqueue(&q, w); // �湮�� ������ ť�� ����
			}
	}
}
*/
void bfs_mat(GraphType* g, int v) {
	int w;
	int queue[MAX_VERTICES], front = -1, rear = -1;
	visited[v] = TRUE; // ���� ������ �湮 ǥ��
	queue[++rear] = v; // ���� ������ ť�� ����
	while (front != rear) { // ť�� ������ �ƴ� ������ �ݺ�
		v = queue[++front]; // ť���� ���� ���� �� ���
		printf("%d �湮 -> ", v);
		for (w = 0; w < g->n; w++) { // ���� ���� Ž��
			if (g->adj_mat[v][w] && !visited[w]) { // �����ϰ� �̹湮�̸� ť�� ����
				visited[w] = TRUE; // �湮 ǥ��
				queue[++rear] = w; // ť�� ����
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
	printf("���� �켱 Ž��\n");
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
	printf("�ʺ� �켱 Ž��\n");
	bfs_mat(g, 0);
	printf("\n");
	free(g);
	return 0;
}

