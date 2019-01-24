#include <stdio.h>

// func prototypes
void read_input(int [], int);
void print_int_arr(int [], int);
void swap(int *, int *);
int partition (int [], int, int);
void quick_sort(int [], int, int);
int get_median(int [], int);

int main(void) {
    //To use this program, you should call it like this:
    // ./analyse_passwords < file.txt
    int NUM_PASSWORDS = 1000;
    int passwords[NUM_PASSWORDS];
    int n = 0;
    int highest = 0;
    int lowest = 0;
    int range = 0;
    int median = 0;

    // Read 1000 passwords from stdin
    read_input(passwords, NUM_PASSWORDS);

    // Sort the hex passwords
    n = sizeof(passwords)/sizeof(passwords[0]);
    quick_sort(passwords, 0, n-1);
    
    // Caclulate some potentially interesting values
    highest = passwords[NUM_PASSWORDS-1];
    lowest = passwords[0];
    range = highest - lowest;
    median = get_median(passwords, NUM_PASSWORDS);

    // Print these values
    printf("Highest generated hex value: %06X\n", highest);
    printf("Lowest generated hex value: %06X\n", lowest);
    printf("Range of generated values: %06X\n", range);
    printf("Median of generated hex values: %06X\n", median);
    return 0;
}

// Returns the integer median of an array with n elements
int get_median(int arr[], int n) {
    int mindex = (n+1) / 2;

    if(n%2 == 0) {
        return (arr[mindex-1] + arr[mindex]) / 2;
    } else {
        return arr[mindex];
    }
}

// Repeatedly scans values from stdin and assigns to array up to n
void read_input(int arr[], int n) {
    for(int i=0 ; i<n ; i++) {
        scanf("%X", &arr[i]);
    }
}

// Prints values in a given array from 0...n
void print_int_arr(int arr[], int n) {
    for(int i=0 ; i<n ; i++) {
        printf("%06X\n", arr[i]);
    }
}

// A utility function to swap two elements
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (int arr[], int low, int high) {
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++) {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot) {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
} 

