#include <stdio.h>
#include <stdlib.h>
#define NUMBER 50000
#define SEED 800

int main(void) {
	int *arr = (int*)malloc(sizeof(int) * NUMBER);
    srand(SEED);
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
    for (int i = 0; i < NUMBER; i++) {
        printf("arr[%5d] : %5d  ", i, arr[i]);
        if (i % 5 == 0) {
            printf("\n");
        }
    }
    free(arr); //메모리 해제
    return 0;
}