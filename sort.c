/*
 * =====================================================================================
 *
 *       Filename:  sort.c
 *
 *    Description:  test sorting algorithm
 *
 *        Version:  1.0
 *        Created:  03/24/2016 05:11:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rex , 
 *        Company:  CIG
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define LEN 15

static int unsorted[LEN] = {3,44,38,5,47,15,36,26,27,2,46,4,19,50,48};

void print_element(int *dest, int len) {
    int i = 0;
    for(i = 0; i < len; i++) {
        printf("%d,", dest[i]);
    }
    printf("\n");
}

void restore_element(int *dest, int len) {
    memset(dest, 0, sizeof(unsorted));
    memcpy(dest, unsorted, sizeof(unsorted));
}

void bubble_sort(int *dest, int len) {
    bool swapped = false;
    int i = 0;
    int temp = 0;
    do {
        swapped = false;
        for(i = 0; i < len-1; i++) {
            if(dest[i] > dest[i+1]) {
                temp = dest[i+1];
                dest[i+1] = dest[i];
                dest[i] = temp;
                swapped = true;
            }
        }
        len--;
    }while(swapped && len > 1);
}

void select_sort(int *dest, int len) {
    int i = 0;
    int j = 0;
    int mindex = 0;
    int temp = 0;
    for(i = 0; i < len -1; i++) {
        mindex = i;
        for(j = i+1; j < len; j++) {
            if(dest[j] < dest[mindex]) {
                mindex = j;
            }
        }
        if(i != mindex) {
            temp = dest[mindex];
            dest[mindex] = dest[i];
            dest[i] = temp;
        }
    }
}

void insert_sort(int *dest, int len) {
    int i = 0;
    int j = 0;
    int insertVal = 0;
    for(i = 1; i < len; i++) {
        insertVal = dest[i];
        for(j = i-1; j >= 0; j--) {
            if(insertVal < dest[j]) {
                dest[j+1] = dest[j];
                if(j == 0) {
                    dest[j] = insertVal;
                }
            }else {
                dest[j+1] = insertVal;
                break;
            }
        }
    }
}

void merge(int *dest, int left, int right) {
    int *temp;
    int i = 0;
    int j = 0;
    int k = 0;
    temp = (int *)malloc(sizeof(int)*(left+right));
    for(k = 0; i < left && j < right; k++) {
        if(dest[i] < dest[left+j]) {
            temp[k] = dest[i];
            i++;
        }else {
            temp[k] = dest[left+j];
            j++;
        }
    }
    if(i == left) {
        while(j < right) {
            temp[k] = dest[left+j];
            j++;
            k++;
        }
    }
    if(j == right) {
        while(i < left) {
            temp[k] = dest[i];
            i++;
            k++;
        }
    }
    
    memcpy(dest, temp, sizeof(int)*(left+right));
    free(temp);
}

void merge_sort(int *dest, int len) {
    if(len == 1) {
        return;
    }
    merge_sort(dest, len/2);
    merge_sort(dest+len/2, len-len/2);
    merge(dest, len/2, len-len/2);
}

int partition(int *dest, int len) {
    int pivot = dest[0];
    int temp = 0;
    int storeIdx = 1;
    int i = 0;
    for(i = 1; i < len; i++) {
        if(dest[i] < pivot) {
            temp = dest[i];
            dest[i] = dest[storeIdx];
            dest[storeIdx] = temp;
            storeIdx++;
        }
    }
    temp = pivot;
    dest[0] = dest[storeIdx -1];
    dest[storeIdx - 1] = temp;
    return storeIdx - 1;
}

void quick_sort(int *dest, int len) {
    int index = 0;

    if(len <= 1) {
        return;
    }
    index = partition(dest, len);
    quick_sort(dest, index);
    quick_sort(dest+index+1, len-index-1);
}

int rpartition(int *dest, int len) {
    int pivot = 0;
    int temp = 0;
    int storeIdx = 1;
    int i = 0;
    int randomIdx = 0;

    srand((unsigned int)time(NULL));
    randomIdx = rand()%len;

    temp = dest[0];
    dest[0] = dest[randomIdx];
    dest[randomIdx] = temp;

    pivot = dest[0];

    for(i = 1; i < len; i++) {
        if(dest[i] < pivot) {
            temp = dest[i];
            dest[i] = dest[storeIdx];
            dest[storeIdx] = temp;
            storeIdx++;
        }
    }
    temp = pivot;
    dest[0] = dest[storeIdx -1];
    dest[storeIdx - 1] = temp;
    return storeIdx - 1;
}

void rquick_sort(int *dest, int len) {
    int index = 0;

    if(len <= 1) {
        return;
    }
    index = rpartition(dest, len);
    rquick_sort(dest, index);
    rquick_sort(dest+index+1, len-index-1);
}

void count_sort(int *dest, int len) {
    int i = 0;
    int j = 0;
    int k = 0;
    int max = dest[0];
    int *temp;

    for(i = 1; i < len; i++) {
        if(dest[i] > max) {
            max = dest[i];
        }
    }
    temp = (int *)malloc((max+1) * sizeof(int));
    memset(temp, 0, (max+1)*sizeof(int));

    for(i = 0; i < len; i++) {
        temp[dest[i]]++;
    }

    for(i = 0; i < max+1; i++) {
        if(temp[i] != 0) {
            for(k = 0; k < temp[i]; k++) {
                dest[j] = i;
                j++;
            }
        }
    }

    free(temp);
}

void radix_sort(int *dest, int len) {
    int *temp;
    int *count;
    int tmp = 0;
    int i = 0;
    int j = 0;
    int max = 0;
    int t = 0;
    int radix = 1;
    int var = 0;

    temp = (int *)malloc(len*sizeof(int));
    count = (int *)malloc(10*sizeof(int));
    for(i = 0; i < len; i++) {
        tmp = dest[i];
        t = 1;
        while(tmp > 10) {
            tmp /= 10;
            t++;
        }
        if(t > max) {
            max = t;
        }
    }

    for(i = 1; i <= max; i++) {
        memset(temp, 0, len*sizeof(int));
        memset(count, 0, 10*sizeof(int));
        for(j = 0; j < len; j++) {
            var = (dest[j]/radix)%10;
            count[var]++;
        }
        for(j = 1; j < 10; j++) {
            count[j] = count[j-1] + count[j];
        }
        for(j = len-1; j >= 0; j--) {
            var = (dest[j]/radix)%10;
            temp[count[var] -1] = dest[j];
            count[var]--;
        }
        for(j = 0; j < len; j++) {
            dest[j] = temp[j];
        }
        radix = radix*10;
    }

    free(temp);
    free(count);
}

void main(void) {
    int *dest;

    dest = (int *)malloc(sizeof(unsorted));

    //bubble
    restore_element(dest, LEN);
    print_element(dest, LEN);
    bubble_sort(dest, LEN);
    printf("bubble sorted done!\n");
    print_element(dest, LEN);

    //select
    restore_element(dest, LEN);
    print_element(dest, LEN);
    select_sort(dest, LEN);
    printf("select sorted done!\n");
    print_element(dest, LEN);

    //insert
    restore_element(dest, LEN);
    print_element(dest, LEN);
    insert_sort(dest, LEN);
    printf("insert sorted done!\n");
    print_element(dest, LEN);

    //merge
    restore_element(dest, LEN);
    print_element(dest, LEN);
    merge_sort(dest, LEN);
    printf("merge sorted done!\n");
    print_element(dest, LEN);

    //quick
    restore_element(dest, LEN);
    print_element(dest, LEN);
    quick_sort(dest, LEN);
    printf("quick sorted done!\n");
    print_element(dest, LEN);

    //rquick
    restore_element(dest, LEN);
    print_element(dest, LEN);
    rquick_sort(dest, LEN);
    printf("r-quick sorted done!\n");
    print_element(dest, LEN);

    //count
    restore_element(dest, LEN);
    print_element(dest, LEN);
    count_sort(dest, LEN);
    printf("count sorted done!\n");
    print_element(dest, LEN);

    //radix
    restore_element(dest, LEN);
    print_element(dest, LEN);
    radix_sort(dest, LEN);
    printf("radix sorted done!\n");
    print_element(dest, LEN);

    free(dest);
}

