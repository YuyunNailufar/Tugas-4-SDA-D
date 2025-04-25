#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <string.h>

// Partition untuk integer, pilih elemen terakhir sebagai pivot
int partition_int(int arr[], int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
        }
    }
    int tmp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = tmp;
    return i + 1;
}

// Quick Sort untuk integer (pakai rekursi logis secara iteratif)
void quick_sort_int(int arr[], int low, int high) {
    while (low < high) {
        int pi = partition_int(arr, low, high);
        // Optimisasi rekursi: proses sisi yang lebih kecil dulu
        if (pi - low < high - pi) {
            quick_sort_int(arr, low, pi - 1);
            low = pi + 1;
        } else {
            quick_sort_int(arr, pi + 1, high);
            high = pi - 1;
        }
    }
}

// Partition untuk string, bandingkan pakai strcmp
int partition_str(char *arr[], int low, int high) {
    char *pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (strcmp(arr[j], pivot) < 0) {
            i++;
            char *tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
        }
    }
    char *tmp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = tmp;
    return i + 1;
}

// Quick Sort untuk string (pakai pembagian string dan optimisasi rekursi)
void quick_sort_str(char *arr[], int low, int high) {
    while (low < high) {
        int pi = partition_str(arr, low, high);
        if (pi - low < high - pi) {
            quick_sort_str(arr, low, pi - 1);
            low = pi + 1;
        } else {
            quick_sort_str(arr, pi + 1, high);
            high = pi - 1;
        }
    }
}

#endif
