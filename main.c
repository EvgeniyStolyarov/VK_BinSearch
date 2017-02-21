//
//  main.c
//  VK_BinSearch
//
//  Created by Stolyarov on 21.02.17.
//  Copyright © 2017 temp. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NOT_FOUND -1

int binSearch(int* a, int size, int x)
{
    if (size <= 0)
       return NOT_FOUND;
    int l = 0, r = size;
    while (r != l) {
        int mid = (r + l) / 2;
        if (a[mid] > x) {
            r = mid;
        } else {
            l = mid+1;
        }
    }
    return (l < size && a[l] > x) ? l : NOT_FOUND;
}

static inline size_t minSize(size_t a, size_t b)
{
    return a < b ? a : b;
}

void mergeSort(int* a, size_t size)
{
    int* b = malloc(size * sizeof(int));
    for (size_t len = 1; len < size; len *= 2 ) {
        for (size_t st = 0; st + len < size; st += len * 2 ) {
            size_t r = st + len;
            size_t l = st;
            size_t rEnd = minSize(r + len, size);
            size_t bIdx = l;
            while (l < st + len && r < rEnd) {
                if (a[l] <= a[r]) {
                    b[bIdx] = a[l++];
                } else {
                    b[bIdx] = a[r++];
                }
                bIdx++;
            }
            while (l < st+len) {
                b[bIdx++] = a[l++];
            }
            while (r < rEnd) {
                b[bIdx++] = a[r++];
            }
            memcpy(a+st, b+st, (rEnd - st) * sizeof(int));
        }
    }
    free(b);
}

void test()
{
    srand(time(NULL));
    int size = rand() % 20;
    int* a = calloc(size, sizeof(int));
    for (int i = 0; i < size; ++i) {
        a[i] = (rand() % 20) * (rand()%2 ? -1 : 1);
    }
    int x = (rand() % 20) * (rand()%2 ? -1 : 1);
    int expectedRes = NOT_FOUND;
    mergeSort(a, size);
    printf("Search index of first element greater then %d in array:\n", x);
    for (size_t i = 0; i < size; ++i) {
        printf("%d ", a[i]);
        if (expectedRes == NOT_FOUND && a[i] > x) {
            expectedRes = (int)i;
        }
    }
    puts("");
    if (expectedRes == NOT_FOUND) {
        puts("Expected: Not found");
    } else {
        printf("Expected: %d\n", expectedRes);
    }
    int res = binSearch(a, size, x);
    if (res == NOT_FOUND) {
        puts("Result: Not found");
    } else {
        printf("Result %d\n", res);
    }
    free(a);
}

int main() {
    test();
    return 0;
}

