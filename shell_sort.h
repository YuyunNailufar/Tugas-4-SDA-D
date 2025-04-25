#ifndef SHELL_SORT_H
#define SHELL_SORT_H

#include <string.h>

// Shell Sort untuk integer
void shell_sort_int(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {           // Atur jarak (gap)
        for (int i = gap; i < n; i++) {
            int temp = arr[i], j = i;
            while (j >= gap && arr[j - gap] > temp) {  // Geser elemen lebih besar ke kanan
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

// Shell Sort untuk string
void shell_sort_str(char *arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            char *temp = arr[i];
            int j = i;
            while (j >= gap && strcmp(arr[j - gap], temp) > 0) { // Bandingkan string pakai strcmp
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

#endif
