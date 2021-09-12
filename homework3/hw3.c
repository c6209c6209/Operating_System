#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

typedef struct node {
    int low;
    int high; 
} NODE;

void* merge_sort(void *);
void* merge_final(void *);
void merge(void *);

int input[10005];

int main(int argc, char *argv[]) {
    FILE *fptr1, *fptr2;
    fptr1 = fopen(argv[1],"r");
    fptr2 = fopen(argv[2],"w");
    
    int temp;

    while(fscanf(fptr1, "%d", &temp) != EOF) {
        clock_t start, terminate;
        int num, mid;
        NODE m, n, p;
        pthread_t left, right, merge_thread; 

        char garbage;

        num = 0;
        input[num++] = temp;
        fscanf(fptr1, "%c", &garbage);
        while(garbage != 13) {
            fscanf(fptr1, "%d", &temp);
            input[num++] = temp;
            fscanf(fptr1, "%c", &garbage);
        }
        start = clock();

        mid = (num-1) / 2;
        m.low = 0;
        m.high = mid;
        n.low = mid+1;
        n.high = num-1;
        p.low = 0;
        p.high = num-1;

        pthread_create(&left, NULL, merge_sort, &m);
        pthread_create(&right, NULL, merge_sort, &n);
        
        pthread_join(left, NULL);
        pthread_join(right, NULL);

        pthread_create(&merge_thread, NULL, merge_final, &p);
        pthread_join(merge_thread, NULL);

        terminate = clock();

        for (int i = 0; i < num; i++)
            fprintf(fptr2, "%d ", input[i]);
        fprintf(fptr2, "\n");
        fprintf(fptr2, "duration: %f\n\n", (terminate - start) / (double)CLOCKS_PER_SEC);

        for (int i = 0; i < num; i++)
            input[i] = 0;
    }

    fclose(fptr1);
    fclose(fptr2);

    return 0;
}

void* merge_sort(void *a) {
    NODE *range = (NODE *)a;
    int mid = range->low + (range->high - range->low) / 2;
    NODE left, right, combine;

    left.low = range->low;
    left.high = mid;
    right.low = mid+1;
    right.high = range->high;
    combine.low = range->low;
    combine.high = range->high;

    if (range->low < range->high) {
        merge_sort(&left);
        merge_sort(&right);
        merge(&combine);
    }
}

void merge(void *a) {
    NODE *range = (NODE *)a;
    int mid = range->low + (range->high - range->low) / 2; 
    int left_size = mid-range->low + 1;
    int right_size = range->high - mid;
    int *left, *right;
    int count_left = 0, count_right = 0;
    int pos = range->low;

    left = (int *)malloc(left_size*sizeof(int));
    right = (int *)malloc(right_size*sizeof(int));

    for(int i = 0; i < left_size; i++) {
        left[i] = input[range->low+i];
    }

    for(int i = 0; i < right_size; i++) {
        right[i] = input[mid+1+i];
    }

    while(count_left < left_size && count_right < right_size) {
        if(left[count_left] <= right[count_right])
            input[pos++] = left[count_left++];
        else
            input[pos++] = right[count_right++];
    }

    while(count_left < left_size)
        input[pos++] = left[count_left++];
    while(count_right < right_size)
        input[pos++] = right[count_right++];
}

void* merge_final(void *a) {
    NODE *range = (NODE *)a;
    int mid = range->low + (range->high - range->low) / 2; 
    int left_size = mid-range->low + 1;
    int right_size = range->high - mid;
    int *left, *right;
    int count_left = 0, count_right = 0;
    int pos = range->low;

    left = (int *)malloc(left_size*sizeof(int));
    right = (int *)malloc(right_size*sizeof(int));

    for(int i = 0; i < left_size; i++) {
        left[i] = input[range->low+i];
    }

    for(int i = 0; i < right_size; i++) {
        right[i] = input[mid+1+i];
    }

    while(count_left < left_size && count_right < right_size) {
        if(left[count_left] <= right[count_right])
            input[pos++] = left[count_left++];
        else
            input[pos++] = right[count_right++];
    }

    while(count_left < left_size)
        input[pos++] = left[count_left++];
    while(count_right < right_size)
        input[pos++] = right[count_right++];
}