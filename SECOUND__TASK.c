#include <stdio.h>

// Function declarations
void readMatrix(int m[10][10], int r, int c);
void printMatrix(int m[10][10], int r, int c);
void add(int a[10][10], int b[10][10], int r, int c);
void multiply(int a[10][10], int b[10][10], int r1, int c1, int c2);
void transpose(int a[10][10], int r, int c);

int main() {
    int mat1[10][10], mat2[10][10];
    int r1, c1, r2, c2;

    printf("Enter rows and cols for Matrix 1: ");
    scanf("%d %d", &r1, &c1);

    printf("Enter matrix 1 elements:\n");
    readMatrix(mat1, r1, c1);

    printf("Enter rows and cols for Matrix 2: ");
    scanf("%d %d", &r2, &c2);

    printf("Enter matrix 2 elements:\n");
    readMatrix(mat2, r2, c2);

    // Addition
    if (r1 == r2 && c1 == c2) {
        printf("\nAddition Result:\n");
        add(mat1, mat2, r1, c1);
    } else {
        printf("\nAddition not possible\n");
    }

    // Multiplication
    if (c1 == r2) {
        printf("\nMultiplication Result:\n");
        multiply(mat1, mat2, r1, c1, c2);
    } else {
        printf("\nMultiplication not possible\n");
    }

    // Transpose of first matrix
    printf("\nTranspose of Matrix 1:\n");
    transpose(mat1, r1, c1);

    return 0;
}

void readMatrix(int m[10][10], int r, int c) {
    int i, j;

    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            scanf("%d", &m[i][j]);
        }
    }
}

void printMatrix(int m[10][10], int r, int c) {
    int i, j;

    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            printf("%d\t", m[i][j]);
        }
        printf("\n");
    }
}

void add(int a[10][10], int b[10][10], int r, int c) {
    int i, j, result[10][10];

    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }

    printMatrix(result, r, c);
}

void multiply(int a[10][10], int b[10][10], int r1, int c1, int c2) {
    int i, j, k, result[10][10];

    for (i = 0; i < r1; i++) {
        for (j = 0; j < c2; j++) {
            result[i][j] = 0;

            for (k = 0; k < c1; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    printMatrix(result, r1, c2);
}

void transpose(int a[10][10], int r, int c) {
    int i, j, t[10][10];

    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            t[j][i] = a[i][j];
        }
    }

    printMatrix(t, c, r);
}