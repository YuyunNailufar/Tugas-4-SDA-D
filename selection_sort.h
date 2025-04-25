#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <string.h>

// Selection Sort untuk integer
void selection_sort_int(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        // Cari indeks nilai minimum di sisa array
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx]) min_idx = j;
        // Tukar jika ditemukan nilai lebih kecil
        if (min_idx != i) {
            int tmp = arr[min_idx]; arr[min_idx] = arr[i]; arr[i] = tmp;
        }
    }
}

// Selection Sort untuk string
void selection_sort_str(char *arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        // Cari string terkecil (pakai strcmp)
        for (int j = i + 1; j < n; j++)
            if (strcmp(arr[j], arr[min_idx]) < 0) min_idx = j;
        if (min_idx != i) {
            char *tmp = arr[min_idx]; arr[min_idx] = arr[i]; arr[i] = tmp;
        }
    }
}

#endif
