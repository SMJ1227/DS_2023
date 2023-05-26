#define PROB 2
#if PROB ==1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000000 // 저장된 데이터의 갯수
#define DATA 586321 // 찾는 키 값

// 순차탐색
int seqsearch(int* list, int low, int high, int key, int* count) {
    int i;
    (*count) = 0;
    list[high + 1] = key;  // 키 값을 찾으면 종료  
    for (i = low; list[i] != key; i++) (*count)++;

    if (i == (high + 1)) return -1;  // 탐색 실패 
    else return i;  // 탐색 성공 
}

// 이진탐색
int binsearch(int* list, int low, int high, int key, int* count) {
    int middle;
    (*count) = 0;
    while (low <= high) { 				// 아직 숫자들이 남아 있으면
        middle = (low + high) / 2;
        if (key == list[middle]) return middle; 	// 탐색 성공
        else if (key > list[middle]) low = middle + 1; 	// 왼쪽 부분리스트 탐색
        else high = middle - 1; 			// 오른쪽 부분리스트 탐색
        (*count)++;
    }
    return -1; 					// 탐색 실패
}

// 보간탐색
int search_interpolation(int* list, int low, int high, int key, int* count) {
    int j;
    (*count) = 0;

    while ((list[high] >= key) && (key > list[low])) {
        j = ((float)(key - list[low]) / (list[high] - list[low]) * (high - low)) + low;
        if (key > list[j]) low = j + 1;
        else if (key < list[j]) high = j - 1;
        else low = j;
        (*count)++;
    }
    if (list[low] == key) return(low);  // 탐색성공
    else return -1;  // 탐색실패
}

int main(void)
{
    int i, s_time, e_time, count, result;
    int* list = (int*)malloc(sizeof(int) * (SIZE + 1));
    if (list == NULL) {
        printf("메모리 할당 오류 \n");
        exit(-1);
    }
    // 오름차순으로 정수 데이터 생성 및 저장
    list[0] = 0;
    for (i = 1; i < SIZE; i++)
        list[i] = list[i - 1] + (rand() % 3);
    printf("Data 크기 : %d, 검색 데이터 : %d \n", SIZE, DATA);
    printf("----------------------------------------------\n");
    s_time = clock();
    result = seqsearch(list, 0, SIZE - 1, DATA, &count); //순차탐색 호출 
    e_time = clock();
    if (result == -1)
        printf("검색 결과 : 검색 데이터 없음 \n");
    else
        printf("검색결과 : %d 위치에서 찾음 \n", result);
    printf("순차탐색 소요시간 %d, 비교횟수 : %d\n\n", e_time - s_time, count);
    s_time = clock();
    result = binsearch(list, 0, SIZE - 1, DATA, &count); //이진탐색 호출 
    e_time = clock();
    if (result == -1) printf("검색 결과 : 검색 데이터 없음 \n");
    else printf("검색결과 : %d 위치에서 찾음 \n", result);
    printf("이진탐색 소요시간 %d, 비교횟수 : %d\n\n", e_time - s_time, count);
	s_time = clock();
	result = search_interpolation(list, 0, SIZE - 1, DATA, &count);//보간탐색 호출 
	e_time = clock();
	if (result == -1) printf("검색 결과 : 검색 데이터 없음 \n");
	else printf("검색결과 : %d 위치에서 찾음 \n", result);
	printf("보간탐색 소요시간 %d, 비교횟수 : %d\n\n", e_time - s_time, count);
    free(list);
    return 0;
}


#elif PROB ==2
#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

#define MAX_SIZE 100

typedef struct {
    AVLNode* data[MAX_SIZE];
    int front;
    int rear;
} Queue;

void initializeQueue(Queue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

int isQueueEmpty(Queue* queue) {
    return (queue->front == -1 && queue->rear == -1);
}

int isQueueFull(Queue* queue) {
    return (queue->rear == MAX_SIZE - 1);
}

void enqueue(Queue* queue, AVLNode* item) {
    if (isQueueFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }

    if (isQueueEmpty(queue))
        queue->front = 0;

    queue->rear++;
    queue->data[queue->rear] = item;
}

AVLNode* dequeue(Queue* queue) {
    AVLNode* item;

    if (isQueueEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return NULL;
    }

    item = queue->data[queue->front];

    if (queue->front == queue->rear)
        initializeQueue(queue);
    else
        queue->front++;

    return item;
}

int getHeight(AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

AVLNode* createNode(int data) {
    AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
    if (newNode == NULL) {
        printf("메모리 할당 오류\n");
        exit(-1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

void updateHeight(AVLNode* node) {
    if (node == NULL)
        return;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

AVLNode* rotateRight(AVLNode* node) {
    AVLNode* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

AVLNode* rotateLeft(AVLNode* node) {
    AVLNode* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

AVLNode* rotateLeftRight(AVLNode* node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

AVLNode* rotateRightLeft(AVLNode* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

AVLNode* insertNode(AVLNode* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insertNode(root->left, data);
    else if (data > root->data)
        root->right = insertNode(root->right, data);
    else
        return root;

    updateHeight(root);

    int balance = getHeight(root->left) - getHeight(root->right);

    if (balance > 1) {
        if (data < root->left->data) {
            printf("LL: %d\n", root->data);
            return rotateRight(root);
        }
        else {
            printf("LR: %d\n", root->data);
            return rotateLeftRight(root);
        }
    }

    if (balance < -1) {
        if (data > root->right->data) {
            printf("RR: %d\n", root->data);
            return rotateLeft(root);
        }
        else {
            printf("RL: %d\n", root->data);
            return rotateRightLeft(root);
        }
    }

    return root;
}

void printLevelOrder(AVLNode* root) {
    if (root == NULL)
        return;

    Queue queue;
    initializeQueue(&queue);
    enqueue(&queue, root);

    int currentLevel = 1;
    int nextLevel = 0;

    printf("Level Order Traversal:\n");

    while (!isQueueEmpty(&queue)) {
        AVLNode* node = dequeue(&queue);
        printf("%d ", node->data);

        if (node->left != NULL) {
            enqueue(&queue, node->left);
            nextLevel++;
        }

        if (node->right != NULL) {
            enqueue(&queue, node->right);
            nextLevel++;
        }

        currentLevel--;

        if (currentLevel == 0) {
            printf("\n");
            currentLevel = nextLevel;
            nextLevel = 0;
        }
    }
    printf("\n");
}

int main(void) {
    AVLNode* root = NULL;

    printf("Insert %d\n", 60); root = insertNode(root, 60);
    printf("Insert %d\n", 50); root = insertNode(root, 50);
    printf("Insert %d\n", 20); root = insertNode(root, 20);
    printLevelOrder(root);
    printf("Insert %d\n", 80); root = insertNode(root, 80);
    printLevelOrder(root);
    printf("Insert %d\n", 90); root = insertNode(root, 90);
    printLevelOrder(root);
    printf("Insert %d\n", 70); root = insertNode(root, 70);
    printLevelOrder(root);
    printf("Insert %d\n", 55); root = insertNode(root, 55);
    printLevelOrder(root);
    printf("Insert %d\n", 10); root = insertNode(root, 10);
    printLevelOrder(root);
    printf("Insert %d\n", 40); root = insertNode(root, 40);
    printLevelOrder(root);
    printf("Insert %d\n", 35); root = insertNode(root, 35);
    printLevelOrder(root);
    /*printf("Remove %d\n", 50); root = AVL_remove(root, 50);
    printLevelOrder(root);
    printf("Remove %d\n", 55); root = AVL_remove(root, 55);
    printLevelOrder(root);*/

    printLevelOrder(root);

    return 0;
}



#endif