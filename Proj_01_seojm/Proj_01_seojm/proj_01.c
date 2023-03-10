#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER 150000
#define SEED 30

typedef struct NODE {
    int data;
    struct NODE* link;
}NODE;

int main(void) {
    srand(SEED);
    int* arr = (int*)malloc(sizeof(int) * NUMBER);

    time_t t1;
    t1 = time(NULL);     
    //printf("%lld\n", t1);
  
    int i, j, k, num;
    for (i = 0; i < NUMBER; i++) {
        num = rand();
        for (j = 0; j < i; j++) {
            if (arr[j] > num) {
                for (k = i; k >= j; k--) {
                    arr[k] = arr[k - 1];
                }
                arr[j] = num;
                break;
            }
        }
        if (j == i) arr[i] = num;
    }

    time_t t2;
    t2 = time(NULL);
    printf("배열을 이용한 경우 소요 시간 : %lld초\n", t2-t1);

    int count = 0;
    for (int i = 0; i < 100; i++) {
        printf("arr[%-5d] : %-5d | ", i, arr[i]);
        count++;
        if (count % 5 == 0 ) {
            printf("\n");
        }
    }
    free(arr); //메모리 해제
    printf("\n");
    

    NODE* head = NULL;
    NODE* prev= NULL, * p = NULL, * tmp = NULL;
    int x;

    time_t t3;
    t3 = time(NULL);

    for (int i = 0; i < NUMBER; i++)
    {
        x = rand();
        tmp = (NODE*)malloc(sizeof(NODE));
        tmp->data = x;
        tmp->link = NULL;

        if (head == NULL) // 첫노드라면, 
        {
            head = tmp;
        }
        else
        {
            if (x < head->data) // 데이터가 head가 가진 값보다 작다면 
            {
                tmp->link = head;
                head = tmp; // 새로들어온 노드가 head가 된다. 
            }
            else
            {
                p = head;
                while (p != NULL && x > p->data)// 현재 값보다 큰값을 가진 노드를 찾는다. 

                {
                    prev = p; // 현재 노드를 저장 
                    p = p->link;
                }
                // 검색이 완료된 이후 prev는 n보다 작은 값을 
                // 가지고 prev->link 값은 n보다 큰값을 가진다. 
                tmp->link = prev->link;
                prev->link = tmp; // 연결  
            }
        }
    }
    p = head;

    time_t t4;
    t4 = time(NULL);
    printf("연결리스트을 이용한 경우 소요 시간 : %lld초\n", t4 - t3);

    int count_list = 0;
    while (1)//p != NULL) //전체 출력 
    {
        printf("%-5d -> %-5d | ",count_list, p->data);
        p = p->link;
        count_list++;
        if (count_list % 5 == 0) {
            printf("\n");
        }
        if (count_list == 100) {
            break;
        }
    }

    while (head != NULL) // 메모리 해제 
    {
        p = head->link;
        free(head);
        head = p;
    }
    return 0;
}
