#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <string.h>

// Bubble Sort untuk integer
void bubble_sort_int(int arr[], int n) {
    int swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            // Tukar jika elemen saat ini lebih besar dari berikutnya
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = tmp;
                swapped = 1; // Menandakan ada penukaran
            }
        }
        if (!swapped) break; // Jika tidak ada penukaran, array sudah urut
    }
}

// Bubble Sort untuk string
void bubble_sort_str(char *arr[], int n) {
    int swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            // Gunakan strcmp untuk membandingkan string
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                char *tmp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

#endif
