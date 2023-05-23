#include <stdio.h>
#include <stdlib.h>

// 이진 탐색 트리의 노드 구조체 정의
typedef struct Node {
    int key;        // 상품 식별자
    int quantity;   // 재고 수량
    struct Node* left;
    struct Node* right;
} Node;

// 이진 탐색 트리에 노드를 삽입하는 함수
// 이진 탐색 트리에 노드를 삽입하는 함수 (중복된 식별자 처리 추가)
Node* insertNode(Node* root, int key, int quantity) {
    // 새로운 노드 생성
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->quantity = quantity;
    newNode->left = NULL;
    newNode->right = NULL;

    // 트리가 비어있을 경우 새로운 노드를 루트로 설정
    if (root == NULL) {
        root = newNode;
        return root;
    }

    // 식별자가 이미 존재하는 경우 재고 수량 업데이트
    if (key == root->key) {
        root->quantity = quantity;
        free(newNode);  // 중복된 노드는 삭제
        return root;
    }

    // 상품 식별자를 기준으로 적절한 위치에 노드 삽입
    if (key <= root->key) {
        root->left = insertNode(root->left, key, quantity);
    }
    else {
        root->right = insertNode(root->right, key, quantity);
    }

    return root;
}
// 중위 순회를 통해 재고 수량을 기준으로 정렬된 순서로 노드를 저장하는 함수
void inorderTraversal(Node* root, Node** arr, int* index) {
    if (root == NULL) {
        return;
    }

    inorderTraversal(root->left, arr, index);
    arr[*index] = root;
    (*index)++;
    inorderTraversal(root->right, arr, index);
}

// 재고 수량을 기준으로 노드를 정렬하는 함수
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

// 상품을 식별자 순서로 출력하는 함수
void printSortedById(Node* root) {
    if (root == NULL) {
        return;
    }

    printSortedById(root->left);
    printf("상품 식별자: %d, 재고 수량: %d\n", root->key, root->quantity);
    printSortedById(root->right);
}

// 상품을 재고 수량 순서로 출력하는 함수
void printSortedByQuantity(Node** arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("상품 식별자: %d, 재고 수량: %d\n", arr[i]->key, arr[i]->quantity);
    }
}

int main() {
    // 이진 탐색 트리 생성 및 데이터 추가
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
    // 재고 수량을 기준으로 정렬하기 위한 임시 배열 생성
    int nodeCount = 0;
    Node** tempArr = (Node**)malloc(sizeof(Node*) * nodeCount);

    // 중위 순회를 통해 재고 수량을 기준으로 정렬된 순서로 노드 저장
    inorderTraversal(root, tempArr, &nodeCount);

    // 재고 수량을 기준으로 노드 정렬
    sortByQuantity(tempArr, nodeCount);

    // 상품 식별자 순서로 출력
    printf("정렬된 상품 식별자:\n");
    printSortedById(root);

    // 재고 수량 순서로 출력
    printf("\n정렬된 재고 수량:\n");
    printSortedByQuantity(tempArr, nodeCount);

    free(tempArr);

    return 0;
}
