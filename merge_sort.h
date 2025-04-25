#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <string.h>
#include <stdlib.h>

// Fungsi merge untuk integer (gabungkan dua subarray terurut)
void merge_int(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L); free(R); // Bebaskan memori sementara
}

// Merge Sort rekursif untuk integer
void merge_sort_int(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        merge_sort_int(arr, l, m);
        merge_sort_int(arr, m + 1, r);
        merge_int(arr, l, m, r); // Gabungkan hasil kiri dan kanan
    }
}

// Fungsi merge untuk string (pakai strcmp untuk urutan)
void merge_str(char *arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    char **L = malloc(n1 * sizeof(char *));
    char **R = malloc(n2 * sizeof(char *));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (strcmp(L[i], R[j]) <= 0) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L); free(R);
}

// Merge Sort rekursif untuk string
void merge_sort_str(char *arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        merge_sort_str(arr, l, m);
        merge_sort_str(arr, m + 1, r);
        merge_str(arr, l, m, r);
    }
}

#endif
