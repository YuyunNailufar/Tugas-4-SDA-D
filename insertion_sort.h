#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <string.h>

// Insertion Sort untuk integer
void insertion_sort_int(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        // Geser elemen yang lebih besar dari key ke kanan
        while (j >= 0 && arr[j] > key)
            arr[j + 1] = arr[j--];
        arr[j + 1] = key; // Sisipkan key di posisi yang benar
    }
}

// Insertion Sort untuk string
void insertion_sort_str(char *arr[], int n) {
    for (int i = 1; i < n; i++) {
        char *key = arr[i];
        int j = i - 1;
        // Bandingkan string pakai strcmp
        while (j >= 0 && strcmp(arr[j], key) > 0)
            arr[j + 1] = arr[j--];
        arr[j + 1] = key;
    }
}

#endif
