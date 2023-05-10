#define PROB 2

#if PROB == 1

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
// �׷����� ��� ���
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
// ���� ��ķ� ǥ���� �׷����� ���� ���� �켱 Ž��
void dfs_mat(GraphType* g, int v) {
	int w;
	visited[v] = TRUE; // ���� v�� �湮 ǥ��
	printf("[%d] -> ", v); // �湮�� ���� ���
	for (w = 0; w < g->n; w++) // ���� ���� Ž��
		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat(g, w); //���� w���� DFS ���� ����
}
// ���� �켱 Ž��
void bfs_mat(GraphType* g, int v) {
	int w;
	int queue[MAX_VERTICES], front = -1, rear = -1;
	visited[v] = TRUE; // ���� ������ �湮 ǥ��
	queue[++rear] = v; // ���� ������ ť�� ����
	while (front != rear) { // ť�� ������ �ƴ� ������ �ݺ�
		v = queue[++front]; // ť���� ���� ���� �� ���
		printf("[%d] -> ", v);
		for (w = 0; w < g->n; w++) { // ���� ���� Ž��
			if (g->adj_mat[v][w] && !visited[w]) { // �����ϰ� �̹湮�̸� ť�� ����
				visited[w] = TRUE; // �湮 ǥ��
				queue[++rear] = w; // ť�� ����
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
	//�׷��� �ʱ�ȭ �� ���� �߰�
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
	printf("�׷����� ��� ���\n");
	printf_graph_matrix(g);
	//���� �켱 Ž��
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("���� �켱 Ž��\n");
	dfs_mat(g, 0);
	printf("\n\n");
	//�ʺ� �켱 Ž��
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("�ʺ� �켱 Ž��\n");
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
	int n; // ������ ����
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
		error("ť�� ��������Դϴ�.");
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
//�׷��� g�� �� ������ ���� ��������Ʈ�� ����ϴ� �����Դϴ�.
void print_adj_list(GraphType* g) {
	printf("�׷��� ��������Ʈ\n");
	for (int i = 0; i < g->n; i++) {
		//i�� 0���� ������ ������ŭ ���� �ϳ��� �����ϴ� for���Դϴ�.
		GraphNode* p = g->adj_list[i];
		//i�� �׷����� ��������Ʈ ������ �����մϴ�.
		printf(" %2d : ", i);
		//i�� ���� ��������Ʈ�� ����մϴ�.)
		while (p != NULL) {
			printf("%d -> ", p->vertex);
			p = p->link;
			//������ ����մϴ�.
		}
		printf("NULL ");
		printf("\n");
	}
	printf("\n");
}
// ���� ����Ʈ�� ǥ���� �׷����� ���� ���� �켱 Ž��
void dfs_list(GraphType* g, int v) {
	GraphNode* w;
	visited[v] = TRUE; // ���� v�� �湮 ǥ��
	printf("[%d] -> ", v); // �湮�� ���� ���
	for (w = g->adj_list[v]; w; w = w->link)// ���� ���� Ž��
		if (!visited[w->vertex])
			dfs_list(g, w->vertex); //���� w���� DFS ���� ����
}
// ���� ����Ʈ ���� �켱 Ž��
void bfs_list(GraphType* g, int v) {
	GraphNode* w;
	QueueType q;
	queue_init(&q); // ť �ʱ� ȭ
	visited[v] = TRUE; // ���� v �湮 ǥ��
	printf("[%d] -> ", v);
	enqueue(&q, v); // ���������� ť�� ����
	while (!is_empty(&q)) {
		v = dequeue(&q); // ť�� ����� ���� ����
		for (w = g->adj_list[v]; w; w = w->link) //���� ���� Ž��
			if (!visited[w->vertex]) { // �̹湮 ���� Ž��
				visited[w->vertex] = TRUE; // �湮 ǥ��
				printf("[%d] -> ", w->vertex);
				enqueue(&q, w->vertex); //������ ť�� ����
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
	//�׷��� �ʱ�ȭ �� ���� �߰�
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
	// �׷��� ���
	print_adj_list(g);
	// ���� �켱 Ž��
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = FALSE;
	printf("���� �켱 Ž��\n");
	dfs_list(g, 0);
	printf("\n\n");
	// �ʺ� �켱 Ž��
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = FALSE;
	printf("�ʺ� �켱 Ž��\n");
	bfs_list(g, 0);
	printf("\n");
	free(g);
	return 0;
}

#endif