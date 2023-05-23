#include <stdio.h>
#include <stdlib.h>

// ���� Ž�� Ʈ���� ��� ����ü ����
typedef struct Node {
    int key;        // ��ǰ �ĺ���
    int quantity;   // ��� ����
    struct Node* left;
    struct Node* right;
} Node;

// ���� Ž�� Ʈ���� ��带 �����ϴ� �Լ�
// ���� Ž�� Ʈ���� ��带 �����ϴ� �Լ� (�ߺ��� �ĺ��� ó�� �߰�)
Node* insertNode(Node* root, int key, int quantity) {
    // ���ο� ��� ����
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->quantity = quantity;
    newNode->left = NULL;
    newNode->right = NULL;

    // Ʈ���� ������� ��� ���ο� ��带 ��Ʈ�� ����
    if (root == NULL) {
        root = newNode;
        return root;
    }

    // �ĺ��ڰ� �̹� �����ϴ� ��� ��� ���� ������Ʈ
    if (key == root->key) {
        root->quantity = quantity;
        free(newNode);  // �ߺ��� ���� ����
        return root;
    }

    // ��ǰ �ĺ��ڸ� �������� ������ ��ġ�� ��� ����
    if (key <= root->key) {
        root->left = insertNode(root->left, key, quantity);
    }
    else {
        root->right = insertNode(root->right, key, quantity);
    }

    return root;
}
// ���� ��ȸ�� ���� ��� ������ �������� ���ĵ� ������ ��带 �����ϴ� �Լ�
void inorderTraversal(Node* root, Node** arr, int* index) {
    if (root == NULL) {
        return;
    }

    inorderTraversal(root->left, arr, index);
    arr[*index] = root;
    (*index)++;
    inorderTraversal(root->right, arr, index);
}

// ��� ������ �������� ��带 �����ϴ� �Լ�
void sortByQuantity(Node** arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j]->quantity > arr[j + 1]->quantity) {
                Node* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// ��ǰ�� �ĺ��� ������ ����ϴ� �Լ�
void printSortedById(Node* root) {
    if (root == NULL) {
        return;
    }

    printSortedById(root->left);
    printf("��ǰ �ĺ���: %d, ��� ����: %d\n", root->key, root->quantity);
    printSortedById(root->right);
}

// ��ǰ�� ��� ���� ������ ����ϴ� �Լ�
void printSortedByQuantity(Node** arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("��ǰ �ĺ���: %d, ��� ����: %d\n", arr[i]->key, arr[i]->quantity);
    }
}

int main() {
    // ���� Ž�� Ʈ�� ���� �� ������ �߰�
    Node* root = NULL;
    root = insertNode(root, 5, 10);
    root = insertNode(root, 3, 5);
    root = insertNode(root, 7, 7);
    root = insertNode(root, 2, 8);
    root = insertNode(root, 4, 3);
    root = insertNode(root, 5, 11);
    root = insertNode(root, 3, 2);
    root = insertNode(root, 7, 7);
    root = insertNode(root, 2, 1);
    root = insertNode(root, 4, 3);
    // ��� ������ �������� �����ϱ� ���� �ӽ� �迭 ����
    int nodeCount = 0;
    Node** tempArr = (Node**)malloc(sizeof(Node*) * nodeCount);

    // ���� ��ȸ�� ���� ��� ������ �������� ���ĵ� ������ ��� ����
    inorderTraversal(root, tempArr, &nodeCount);

    // ��� ������ �������� ��� ����
    sortByQuantity(tempArr, nodeCount);

    // ��ǰ �ĺ��� ������ ���
    printf("���ĵ� ��ǰ �ĺ���:\n");
    printSortedById(root);

    // ��� ���� ������ ���
    printf("\n���ĵ� ��� ����:\n");
    printSortedByQuantity(tempArr, nodeCount);

    free(tempArr);

    return 0;
}
