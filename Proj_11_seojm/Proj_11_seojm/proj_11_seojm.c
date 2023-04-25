#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define MAX_STACK_SIZE 100

typedef struct TREENODE {
	int data;
	struct TREENODE* left, * right;
} TreeNode;

int top = -1;
TreeNode* stack[MAX_STACK_SIZE];

void push(TreeNode* root) {
	if (top < MAX_STACK_SIZE - 1) {
		stack[++(top)] = root;
	}
	return root;
}
TreeNode* pop() {
	TreeNode* root = NULL;
	if (top >= 0) {
		root = stack[top--];
	}
	return root;
}

TreeNode n15 = { 15, NULL, NULL };
TreeNode n14 = { 14, NULL, NULL };
TreeNode n13 = { 13, NULL, NULL };
TreeNode n12 = { 12, NULL, NULL };
TreeNode n11 = { 11, NULL, NULL };
TreeNode n10 = { 10, NULL, NULL };
TreeNode n9 = { 9, NULL, NULL };
TreeNode n8 = { 8, NULL, NULL };
TreeNode n7 = { 7, &n14, &n15 };
TreeNode n6 = { 6, &n12, &n13 };
TreeNode n5 = { 5, &n10, &n11 };
TreeNode n4 = { 4, &n8, &n9 };
TreeNode n3 = { 3, &n6, &n7 };
TreeNode n2 = { 2, &n4, &n5 };
TreeNode n1 = { 1, &n2, &n3 };
TreeNode* root = &n1;

// 중위 순회
inorder_rec(TreeNode* root) {
	if (root) {
		inorder_rec(root->left);	// 왼쪽서브트리 순회
		printf("[%d]", root->data); 	// 노드 방문
		inorder_rec(root->right);	// 오른쪽서브트리 순회
	}
}
inorder_iter(TreeNode* root) {
	top = -1;
	TreeNode* current = root;
	while (top >= 0 || current != NULL) {
		if (current != NULL){
			push(current);
			current = current->left;
		}
		else {
			current = pop();
			printf("[%d]", current->data);
			current = current->right;
		}
	}
}
// 전위 순회
preorder_rec(TreeNode* root) {
	if (root) {
		printf("[%d]", root->data); 	// 노드 방문
		preorder_rec(root->left);	// 왼쪽서브트리 순회
		preorder_rec(root->right);	// 오른쪽서브트리 순회
	}
}
preorder_iter(TreeNode* root) {
	push(root);
	while (top >= 0) {
		TreeNode* current = stack[top];
		TreeNode* del = pop();
		printf("[%d]", del->data);
		TreeNode* temp = current->right;
		if (temp != NULL) {
			push(temp);
		}
		temp = current->left;
		if (temp != NULL) {
			push(temp);
		}
	}
}
// 후위 순회
postorder_rec(TreeNode* root) {
	if (root) {
		postorder_rec(root->left);	// 왼쪽 서브 트리 순회
		postorder_rec(root->right);	// 오른쪽 서브 트리 순회
		printf("[%d]", root->data); 	// 노드 방문
	}
}
postorder_iter(TreeNode* root) {
	top = -1;
	int i = 0;
	TreeNode* node;
	TreeNode* output[MAX_STACK_SIZE];
	push(root);
	while (top >= 0) {
		node = pop();
		output[i++] = node;
		if (node->left != NULL) push(node->left);
		if (node->right != NULL) push(node->right);
	}
	for (i = i - 1; i >= 0; i--) {
		printf("[%d]", output[i]->data);
	}
}
typedef struct NODE { int data; int leaf; } node;
// Full Binary Tree node number 1~15(root 1, left child n*2, right child n*2+1
node arr[] = { {0,0}, {1,1}, {2,1}, {3,1}, {4,1}, {5,1}, {6,1}, {7,1}, {8,0}, {9,0}, {10,0}, {11,0},
{12,0}, {13,0}, {14,0}, {15,0} };

int main(void)
{
	printf("중위 순회(rec) =");
	inorder_rec(root);
	printf("\n");
	printf("중위 순회(itr) =");
	inorder_iter(root);
	printf("\n");
	//printf("배열 중위 순회(rec)=");
	//inorder_rec_arr(arr, 1);
	printf("\n\n");
	printf("전위 순회(rec) =");
	preorder_rec(root);
	printf("\n");
	printf("전위 순회(itr) =");
	preorder_iter(root);
	printf("\n");
	//printf("배열 전위 순회(rec)=");
	//preorder_rec_arr(arr, 1);
	printf("\n\n");
	printf("후위 순회(rec) =");
	postorder_rec(root);
	printf("\n");
	printf("후위 순회(itr) =");
	postorder_iter(root);
	printf("\n");
	//printf("배열 후위 순회(rec)=");
	//postorder_rec_arr(arr, 1);
	printf("\n\n");
	return 0;
}
