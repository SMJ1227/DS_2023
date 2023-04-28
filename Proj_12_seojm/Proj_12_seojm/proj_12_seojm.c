#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct ELEMENT {
	int id_num;
	char name[10];
}element;
typedef struct TreeNode {
	element std;
	struct TreeNode* left, * right;
} TreeNode;

TreeNode* search(TreeNode* node, int key) {
	while (node != NULL) {
		if (key == node->std.id_num)return node;
		else if (key < node->std.id_num) node = node->left;
		else node = node->right;
	}
	return NULL;
}
TreeNode* insert_node(TreeNode* node, element std) {
	if (node == NULL) {
		node = (TreeNode*)malloc(sizeof(TreeNode));
		node->std = std;
		node->left = node->right = NULL;
	}
	else if (std.id_num < node->std.id_num) {
		node->left = insert_node(node->left, std);
	}
	else if (std.id_num > node->std.id_num) {
		node->right = insert_node(node->right, std);
	}
	// 변경된 루트 포인터를 반환한다.
	return node;
}
TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;
	// 맨 왼쪽 단말 노드를 찾으러 내려감
	while (current->left != NULL)
		current = current->left;
	return current;
}
// 이진 탐색 트리와 키가 주어지면 키가 저장된 노드를 삭제하고
// 새로운 루트 노드를 반환한다. 
TreeNode* delete_node(TreeNode* root, int key) {
	if (root == NULL) return root;
	// 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
	if (key < root->std.id_num)
		root->left = delete_node(root->left, key);
	// 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
	else if (key > root->std.id_num)
		root->right = delete_node(root->right, key);
	// 키가 루트와 같으면 이 노드를 삭제하면 됨
	else {
		// 첫 번째나 두 번째 경우
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		// 세 번째 경우
		TreeNode* temp = min_value_node(root->right);
		// 중외 순회시 후계 노드를 복사한다. 
		root->std.id_num = temp->std.id_num;
		// 중외 순회시 후계 노드를 삭제한다. 
		root->right = delete_node(root->right, temp->std.id_num);
	}
	return root;
}
int get_node_count(TreeNode* root){
	int count = 0;
	if (root != NULL)
		count = 1 + get_node_count(root->left) +
		get_node_count(root->right);
	return count;
}
int get_leaf_count(TreeNode* root){
	int count = 0;
	if (root != NULL) {
		if (root->left == NULL && root->right == NULL)
			return 1;
		else
			count = get_leaf_count(root->left) +
			get_leaf_count(root->right);
	}
	return count;
}
int get_height(TreeNode* root){
	int height = 0;
	if (root != NULL)
		height = 1 + max(get_height(root->left),
			get_height(root->right));
	return height;
}

inorder(TreeNode* root) {
	if (root) {
		inorder(root->left);	// 왼쪽서브트리 순회
		printf("[%d]", root->std.id_num); 	// 노드 방문
		inorder(root->right);	// 오른쪽서브트리 순회
	}
}
TreeNode* delete_tree(TreeNode* root) {
	if (root == NULL) return NULL;
	delete_tree(root->left);
	delete_tree(root->right);
	free(root);
	return NULL;
}
// ================ 원형큐 코드 시작 =================
#define MAX_QUEUE_SIZE 100
//typedef TreeNode* element;
typedef struct { // 큐 타입
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 공백 상태 검출 함수
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}
// 공백 상태 검출 함수
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// 삽입 함수
void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// 삭제 함수
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

void level_order(TreeNode* ptr)
{
	QueueType q;
	init_queue(&q); // 큐 초기화
	if (ptr == NULL) return;
	enqueue(&q, ptr->std);
	while (!is_empty(&q)) {
		ptr->std = dequeue(&q);
		printf(" [%d] ", ptr->std.id_num);
		if (ptr->left)
			enqueue(&q, ptr->left->std);
		if (ptr->right)
			enqueue(&q, ptr->right->std);
	}
}

int main(void)
{
	TreeNode* root = NULL;
	TreeNode* tmp = NULL;
	element item;
	item.id_num = 2021006; strcpy(item.name, "name6");
	root = insert_node(root, item);
	item.id_num = 2021001; strcpy(item.name, "name1");
	root = insert_node(root, item);
	item.id_num = 2021009; strcpy(item.name, "name9");
	root = insert_node(root, item);
	item.id_num = 2021007; strcpy(item.name, "name7");
	root = insert_node(root, item);
	item.id_num = 2021003; strcpy(item.name, "name3");
	root = insert_node(root, item);
	item.id_num = 2021002; strcpy(item.name, "name2");
	root = insert_node(root, item);
	item.id_num = 2021005; strcpy(item.name, "name5");
	root = insert_node(root, item);
	item.id_num = 2021004; strcpy(item.name, "name4");
	root = insert_node(root, item);
	item.id_num = 2021008; strcpy(item.name, "name8");
	root = insert_node(root, item);
	item.id_num = 2021010; strcpy(item.name, "name10");
	root = insert_node(root, item);
	printf("이진 탐색 트리의 노드 수, leaf노드 수, 높이 구하기\n");
	printf("노드 수 = %d \nleaf 노드 수 = %d \n높이 = %d \n\n", get_node_count(root), get_leaf_count(root), get_height(root));
	printf("이진 탐색 트리 레벨 탐색 순회 결과\n");
	level_order(root);
	printf("\n\n");
	printf("이진 탐색 트리 중위 순회 결과 \n");
	inorder(root);
	printf("\n\n이진 탐색 트리에서 2021010 검색\n");
	tmp = search(root, 2021010);
	if (tmp != NULL)
		printf("검색 성공 : 학번 %d, 이름 %s \n", tmp->std.id_num, tmp->std.name);
	else
		printf("이진 탐색 트리에서 검색 학생을 발견못함 \n");
	printf("\n이진 탐색 트리에서 2021006 삭제\n");
	delete_node(root, 2021006);
	printf("\n\n이진 탐색 트리에서 2021006 검색\n");
	tmp = search(root, 2021006);
	if (tmp != NULL)
		printf("검색 성공 : 학번 %d, 이름 %s \n", tmp->std.id_num, tmp->std.name);
	else
		printf("이진 탐색 트리에서 검색 학생을 발견못함 \n");
	printf("\n\n이진 탐색 트리 중위 순회 결과 \n");
	inorder(root);
	printf("\n\n");
	printf("\n\n이진 탐색 트리 전체 삭제 \n");
	root = delete_tree(root);
	printf("\n\n이진 탐색 트리 레벨 탐색 순회 결과\n");
	level_order(root);
	printf("\n\n");
	return 0;
}
