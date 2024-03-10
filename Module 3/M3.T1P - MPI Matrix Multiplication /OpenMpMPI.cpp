
#include <mpi.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#define N 800

void initializeArray(int array[N][N]); // Function to initialize the array with random values
void printArrays(int array[N][N]);      // Function to print arrays to the console
void matrixMultiplication(int np, int rank, int inputArray1[N][N], int inputArray2[N][N], int outputArray[N][N]); // Function to perform matrix multiplication
void printOutput(int outputArray[N]);

struct timeval timecheck;

int main() {
    MPI_Init(NULL, NULL);

    int np = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int inputArray1[N][N], inputArray2[N][N];
    int outputArray[N][N] = {{0}};

    if (rank == 0) {
        initializeArray(inputArray1); // Initialize inputArray1 on the root process
        initializeArray(inputArray2); // Initialize inputArray2 on the root process
    }

    if (rank == 0) {
        printf("MPI Matrix Multiplication.\n");
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(&inputArray1, N * N, MPI_INT, 0, MPI_COMM_WORLD); // Broadcast inputArray1 to all processes
    MPI_Bcast(&inputArray2, N * N, MPI_INT, 0, MPI_COMM_WORLD); // Broadcast inputArray2 to all processes

    MPI_Barrier(MPI_COMM_WORLD);
    matrixMultiplication(np, rank, inputArray1, inputArray2, outputArray); // Perform matrix multiplication
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Finalize();

    if (rank == 0) {
        printf("\nResultant Matrix:\n");
        printArrays(outputArray); // Print the result on the root process
    }

    return 0;
}

void initializeArray(int array[N][N]) {
    printf("Initializing array... ");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            array[i][j] = rand() % ((10 - 1) + 1) + 1; // Assign random values to the array elements
        }
    }
    printf("complete\n");
}

void printArrays(int array[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", array[i][j]); // Print array element
        }
        printf("\n");
    }
}

void matrixMultiplication(int np, int rank, int inputArray1[N][N], int inputArray2[N][N], int outputArray[N][N]) {
    int range = N / np; // Determine the range of rows each process will handle
    int start = rank * range; // Determine the starting row for the current process
    int end = start + range; // Determine the ending row for the current process

    for (int i = start; i < end; i++) {
        for (int j = 0; j < N; j++) {
            int value = 0;
            for (int k = 0; k < N; k++) {
                value += inputArray1[i][k] * inputArray2[k][j]; // Perform matrix multiplication
            }
            outputArray[i][j] = value; // Store the result in the outputArray
        }
    }
}
