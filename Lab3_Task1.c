#include <stdio.h>
#include <stdbool.h>

#define SIZE 24         // Max array size
#define nRows 2         // No. of rows for reshaped matrix
#define nCols 3         // No. of columns for reshaped matrix

// FUNCTION PROTOTYPES
void print_array(int array[], int length);                    
void print_matrix(int rows, int cols, int mat[rows][cols]);   
bool isValid(const int arr[], int length, int pos);           
void remove_el(int arr[], int *length, int pos);              
void insert_el(int arr[], int *length, int pos, int value);   
void reshape_mat(const int arr[], int length, int rows, int cols, int arr2d[rows][cols]); 
void transpose_mat(int rows, int cols, const int mat[rows][cols], int mat_transp[cols][rows]);  
bool duplicate(int arr[], int length);          

int main() {
    int arr[SIZE] = {10, 20, 30, 40, 50, 60};     // Initializes array with values
    int length = 6;                               // Only first 6 elements are initialized
    int arr2d[nRows][nCols];                      // 2D array for reshaping
    int mat_transp[nCols][nRows];                 // Array for the transposed matrix

    // Prints original array
    printf("\nThe original array is:\n");
    print_array(arr, length);

    // Removes element at index 2
    remove_el(arr, &length, 2);
    printf("\nArray after removing element at index 2:\n");
    print_array(arr, length);

    // Inserts "80" at index 2
    insert_el(arr, &length, 2, 80);
    printf("\nArray after inserting 80 at index 2:\n");
    print_array(arr, length);

    // Reshapes the array to 2D
    reshape_mat(arr, length, nRows, nCols, arr2d);
    printf("\nThe reshaped array is:\n");
    print_matrix(nRows, nCols, arr2d);

    // Transposes the 2D array
    transpose_mat(nRows, nCols, arr2d, mat_transp);
    printf("\nThe transposed matrix is:\n");
    print_matrix(nCols, nRows, mat_transp);

    // Checks for duplicates
    bool has_duplicate = duplicate(arr, length);
    printf("\nArray has duplicate: %s\n", has_duplicate ? "true" : "false");

    return 0;
}

// Prints elements of a 1D array
void print_array(int array[], int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// Prints elements of a 2D matrix
void print_matrix(int rows, int cols, int mat[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

// Checks if a position is valid in the array
bool isValid(const int arr[], int length, int pos) {
    return (pos >= 0 && pos < length);
}

// Removes an element from the array at the specified position
void remove_el(int arr[], int *length, int pos) {
    if (!isValid(arr, *length, pos)) {        // Checks if position is valid
        printf("Invalid position\n");
        return;
    }
    for (int i = pos; i < *length - 1; i++) { // Shifts elements left
        arr[i] = arr[i + 1];
    }
    (*length)--;                              // Decreases array length
}

// Inserts an element into the array at the specified position
void insert_el(int arr[], int *length, int pos, int value) {
    if (pos < 0 || pos > *length || *length >= SIZE) {  // Checks for valid position and available space
        printf("Invalid position or array full\n");
        return;
    }
    for (int i = *length; i > pos; i--) {               // Shifts elements right
        arr[i] = arr[i - 1];
    }
    arr[pos] = value;                                   // Inserts the value
    (*length)++;                                        // Increases array length
}

// Reshapes a 1D array into a 2D array with specified rows and columns
void reshape_mat(const int arr[], int length, int rows, int cols, int arr2d[rows][cols]) {
    if (length < rows * cols) {                         // Checks if enough elements are available
        printf("Insufficient elements for reshaping\n");
        return;
    }
    int i = 0;
    for (int j = 0; j < rows; j++) {
        for (int k = 0; k < cols; k++) {
            arr2d[j][k] = arr[i++];                     // Fills 2D array with elements from 1D array
        }
    }
}

// Transposes the given 2D matrix
void transpose_mat(int rows, int cols, const int mat[rows][cols], int mat_transp[cols][rows]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mat_transp[j][i] = mat[i][j];               // Transposes elements
        }
    }
}

// Checks for duplicates in the array
bool duplicate(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (arr[i] == arr[j]) {                     // Condition for duplicates found
                return true;
            }
        }
    }
    return false;                                       // No duplicates found
}
