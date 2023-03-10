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
    printf("�迭�� �̿��� ��� �ҿ� �ð� : %lld��\n", t2-t1);

    int count = 0;
    for (int i = 0; i < 100; i++) {
        printf("arr[%-5d] : %-5d | ", i, arr[i]);
        count++;
        if (count % 5 == 0 ) {
            printf("\n");
        }
    }
    free(arr); //�޸� ����
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

        if (head == NULL) // ù�����, 
        {
            head = tmp;
        }
        else
        {
            if (x < head->data) // �����Ͱ� head�� ���� ������ �۴ٸ� 
            {
                tmp->link = head;
                head = tmp; // ���ε��� ��尡 head�� �ȴ�. 
            }
            else
            {
                p = head;
                while (p != NULL && x > p->data)// ���� ������ ū���� ���� ��带 ã�´�. 

                {
                    prev = p; // ���� ��带 ���� 
                    p = p->link;
                }
                // �˻��� �Ϸ�� ���� prev�� n���� ���� ���� 
                // ������ prev->link ���� n���� ū���� ������. 
                tmp->link = prev->link;
                prev->link = tmp; // ����  
            }
        }
    }
    p = head;

    time_t t4;
    t4 = time(NULL);
    printf("���Ḯ��Ʈ�� �̿��� ��� �ҿ� �ð� : %lld��\n", t4 - t3);

    int count_list = 0;
    while (1)//p != NULL) //��ü ��� 
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

    while (head != NULL) // �޸� ���� 
    {
        p = head->link;
        free(head);
        head = p;
    }
    return 0;
}
