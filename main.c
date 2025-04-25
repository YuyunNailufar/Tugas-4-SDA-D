#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bubble_sort.h"
#include "selection_sort.h"
#include "insertion_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "shell_sort.h"

#define MAX_WORD_LENGTH 100
#define MAX_DATA 2000000

// Variabel memori global
size_t mem_data_angka = 0;
size_t mem_data_kata_pointer = 0;
size_t mem_data_kata_isi = 0;

int DATA_UJI[] = {10000, 50000, 100000, 250000, 500000, 1000000, 1500000, 2000000};
int JUMLAH_UJI = sizeof(DATA_UJI) / sizeof(DATA_UJI[0]);

// Generate angka
void generate_numbers_to_file(const char *filename, int jumlah) {
    FILE *fp = fopen(filename, "w");
    if (!fp) { perror("Gagal membuat file angka"); exit(1); }
    for (int i = 0; i < jumlah; i++) {
        fprintf(fp, "%d\n", rand() % 10000000);
    }
    fclose(fp);
}

// Generate kata
void generate_words_to_file(const char *filename, int jumlah) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyz";
    FILE *fp = fopen(filename, "w");
    if (!fp) { perror("Gagal membuat file kata"); exit(1); }

    for (int i = 0; i < jumlah; i++) {
        int len = 3 + rand() % 8;
        for (int j = 0; j < len; j++) {
            fputc(charset[rand() % (sizeof(charset) - 1)], fp);
        }
        fputc('\n', fp);
    }
    fclose(fp);
}

// Baca angka
int read_numbers(const char *filename, int arr[], int n) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { perror("File angka gagal dibuka"); return 0; }
    for (int i = 0; i < n && fscanf(fp, "%d", &arr[i]) != EOF; i++);
    fclose(fp);
    return 1;
}

// Baca kata + ukur memori isi
int read_words(const char *filename, char *arr[], int n) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { perror("File kata gagal dibuka"); return 0; }
    char buffer[MAX_WORD_LENGTH];
    for (int i = 0; i < n && fgets(buffer, MAX_WORD_LENGTH, fp); i++) {
        buffer[strcspn(buffer, "\n")] = 0;
        arr[i] = strdup(buffer);
        if (arr[i]) mem_data_kata_isi += strlen(arr[i]) + 1;
    }
    fclose(fp);
    return 1;
}

// Free kata
void free_words(char *arr[], int n) {
    for (int i = 0; i < n; i++) free(arr[i]);
}

// Cetak tabel
void print_table_header(const char *tipe) {
    printf("\n[%s] Benchmark Sorting:\n", tipe);
    printf("+-------------------+-------------+----------------------------+--------------+\n");
    printf("|     Algoritma     |   Jumlah    |       Waktu Eksekusi       |  Memori(MB)  |\n");
    printf("+-------------------+-------------+----------------------------+--------------+\n");
}

void print_table_row(const char *nama, int jumlah, double waktu, double memori) {
    printf("| %-17s | %11d | %20.3f detik | %12.2f |\n", nama, jumlah, waktu, memori);
}

void print_table_footer() {
    printf("+-------------------+-------------+----------------------------+--------------+\n");
}

// Waktu sorting angka
double time_sort_int(void (*sort)(int[], int), int *data, int n) {
    int *arr = malloc(n * sizeof(int));
    memcpy(arr, data, n * sizeof(int));
    clock_t start = clock();
    sort(arr, n);
    clock_t end = clock();
    free(arr);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Waktu sorting kata
double time_sort_str(void (*sort)(char*[], int), char *data[], int n) {
    char **arr = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) arr[i] = strdup(data[i]);
    clock_t start = clock();
    sort(arr, n);
    clock_t end = clock();
    for (int i = 0; i < n; i++) free(arr[i]);
    free(arr);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Merge/Quick int
double time_merge_quick_int(void (*sort)(int[], int, int), int *data, int n) {
    int *arr = malloc(n * sizeof(int));
    memcpy(arr, data, n * sizeof(int));
    clock_t start = clock();
    sort(arr, 0, n - 1);
    clock_t end = clock();
    free(arr);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Merge/Quick str
double time_merge_quick_str(void (*sort)(char*[], int, int), char *data[], int n) {
    char **arr = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) arr[i] = strdup(data[i]);
    clock_t start = clock();
    sort(arr, 0, n - 1);
    clock_t end = clock();
    for (int i = 0; i < n; i++) free(arr[i]);
    free(arr);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(NULL));

    for (int uji = 0; uji < JUMLAH_UJI; uji++) {
        int jumlah_data = DATA_UJI[uji];
        mem_data_angka = 0;
        mem_data_kata_pointer = 0;
        mem_data_kata_isi = 0;

        generate_numbers_to_file("data_angka.txt", jumlah_data);
        generate_words_to_file("data_kata.txt", jumlah_data);

        int *data_angka = malloc(jumlah_data * sizeof(int));
        mem_data_angka = jumlah_data * sizeof(int);

        char **data_kata = malloc(jumlah_data * sizeof(char *));
        mem_data_kata_pointer = jumlah_data * sizeof(char *);

        if (!read_numbers("data_angka.txt", data_angka, jumlah_data) ||
            !read_words("data_kata.txt", data_kata, jumlah_data)) {
            fprintf(stderr, "Gagal baca data.\n");
            return 1;
        }

        double memori_angka_mb = mem_data_angka / (1024.0 * 1024.0);
        double memori_kata_mb = (mem_data_kata_pointer + mem_data_kata_isi) / (1024.0 * 1024.0);

        printf("\n==== BENCHMARK UNTUK %d DATA ====\n", jumlah_data);

        // === TABEL ANGKA ===
        print_table_header("DATA ANGKA");
        print_table_row("BubbleSort", jumlah_data, time_sort_int(bubble_sort_int, data_angka, jumlah_data), memori_angka_mb);
        print_table_row("SelectionSort", jumlah_data, time_sort_int(selection_sort_int, data_angka, jumlah_data), memori_angka_mb);
        print_table_row("InsertionSort", jumlah_data, time_sort_int(insertion_sort_int, data_angka, jumlah_data), memori_angka_mb);
        print_table_row("MergeSort", jumlah_data, time_merge_quick_int(merge_sort_int, data_angka, jumlah_data), memori_angka_mb);
        print_table_row("QuickSort", jumlah_data, time_merge_quick_int(quick_sort_int, data_angka, jumlah_data), memori_angka_mb);
        print_table_row("ShellSort", jumlah_data, time_sort_int(shell_sort_int, data_angka, jumlah_data), memori_angka_mb);
        print_table_footer();

        // === TABEL KATA ===
        print_table_header("DATA KATA");
        print_table_row("BubbleSort", jumlah_data, time_sort_str(bubble_sort_str, data_kata, jumlah_data), memori_kata_mb);
        print_table_row("SelectionSort", jumlah_data, time_sort_str(selection_sort_str, data_kata, jumlah_data), memori_kata_mb);
        print_table_row("InsertionSort", jumlah_data, time_sort_str(insertion_sort_str, data_kata, jumlah_data), memori_kata_mb);
        print_table_row("MergeSort", jumlah_data, time_merge_quick_str(merge_sort_str, data_kata, jumlah_data), memori_kata_mb);
        print_table_row("QuickSort", jumlah_data, time_merge_quick_str(quick_sort_str, data_kata, jumlah_data), memori_kata_mb);
        print_table_row("ShellSort", jumlah_data, time_sort_str(shell_sort_str, data_kata, jumlah_data), memori_kata_mb);
        print_table_footer();

        // Cleanup
        free(data_angka);
        free_words(data_kata, jumlah_data);
        free(data_kata);
    }

    return 0;
}
