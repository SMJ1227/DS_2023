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
	// ����� ��Ʈ �����͸� ��ȯ�Ѵ�.
	return node;
}
TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;
	// �� ���� �ܸ� ��带 ã���� ������
	while (current->left != NULL)
		current = current->left;
	return current;
}
// ���� Ž�� Ʈ���� Ű�� �־����� Ű�� ����� ��带 �����ϰ�
// ���ο� ��Ʈ ��带 ��ȯ�Ѵ�. 
TreeNode* delete_node(TreeNode* root, int key) {
	if (root == NULL) return root;
	// ���� Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� �ִ� ����
	if (key < root->std.id_num)
		root->left = delete_node(root->left, key);
	// ���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� �ִ� ����
	else if (key > root->std.id_num)
		root->right = delete_node(root->right, key);
	// Ű�� ��Ʈ�� ������ �� ��带 �����ϸ� ��
	else {
		// ù ��°�� �� ��° ���
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
		// �� ��° ���
		TreeNode* temp = min_value_node(root->right);
		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�. 
		root->std.id_num = temp->std.id_num;
		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�. 
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
		inorder(root->left);	// ���ʼ���Ʈ�� ��ȸ
		printf("[%d]", root->std.id_num); 	// ��� �湮
		inorder(root->right);	// �����ʼ���Ʈ�� ��ȸ
	}
}
TreeNode* delete_tree(TreeNode* root) {
	if (root == NULL) return NULL;
	delete_tree(root->left);
	delete_tree(root->right);
	free(root);
	return NULL;
}
// ================ ����ť �ڵ� ���� =================
#define MAX_QUEUE_SIZE 100
//typedef TreeNode* element;
typedef struct { // ť Ÿ��
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// ���� ���� ���� �Լ�
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}
// ���� ���� ���� �Լ�
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// ���� �Լ�
void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// ���� �Լ�
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

void level_order(TreeNode* ptr)
{
	QueueType q;
	init_queue(&q); // ť �ʱ�ȭ
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
	printf("���� Ž�� Ʈ���� ��� ��, leaf��� ��, ���� ���ϱ�\n");
	printf("��� �� = %d \nleaf ��� �� = %d \n���� = %d \n\n", get_node_count(root), get_leaf_count(root), get_height(root));
	printf("���� Ž�� Ʈ�� ���� Ž�� ��ȸ ���\n");
	level_order(root);
	printf("\n\n");
	printf("���� Ž�� Ʈ�� ���� ��ȸ ��� \n");
	inorder(root);
	printf("\n\n���� Ž�� Ʈ������ 2021010 �˻�\n");
	tmp = search(root, 2021010);
	if (tmp != NULL)
		printf("�˻� ���� : �й� %d, �̸� %s \n", tmp->std.id_num, tmp->std.name);
	else
		printf("���� Ž�� Ʈ������ �˻� �л��� �߰߸��� \n");
	printf("\n���� Ž�� Ʈ������ 2021006 ����\n");
	delete_node(root, 2021006);
	printf("\n\n���� Ž�� Ʈ������ 2021006 �˻�\n");
	tmp = search(root, 2021006);
	if (tmp != NULL)
		printf("�˻� ���� : �й� %d, �̸� %s \n", tmp->std.id_num, tmp->std.name);
	else
		printf("���� Ž�� Ʈ������ �˻� �л��� �߰߸��� \n");
	printf("\n\n���� Ž�� Ʈ�� ���� ��ȸ ��� \n");
	inorder(root);
	printf("\n\n");
	printf("\n\n���� Ž�� Ʈ�� ��ü ���� \n");
	root = delete_tree(root);
	printf("\n\n���� Ž�� Ʈ�� ���� Ž�� ��ȸ ���\n");
	level_order(root);
	printf("\n\n");
	return 0;
}
