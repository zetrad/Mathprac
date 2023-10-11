#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill (int *arr, int size, int A, int B)
{
    for (int i = 0; i < size; i++)
    arr[i] = rand() % A - B;
}

void search_and_swap (int *arr, int size, int* max, int *min)
{
    int imin,imax;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] < *min) { *min = arr[i]; imin=  i;}
        if (arr[i] > *max) { *max = arr[i]; imax = i;}
    }
    int tmp = arr[imin];
    arr[imin]=arr[imax];
    arr[imax]=tmp;
}

void print(int *arr, int n)
{
    for (int i=0;i<n;i++)
    {printf ("%d ", arr[i]);}
    printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc != 3) { printf ("ERROR"); return 0;}
    srand(time(NULL));
    int size = 200;
    int arr[size];
    fill (arr, size,atoi(argv[2]), atoi(argv[1]));
    print(arr,size);
    int min = arr[0], max =arr[0];
    search_and_swap (arr, size, &max, &min);
    printf ("\nMax and min values in array are %d and %d\n", max, min);
    print(arr, size);
    printf ("END OF PART 1\n");
    int sizeA = rand()%100+10, sizeB = rand()%100+10;
    int *A = (int*)malloc(sizeA), *B = (int*)malloc(sizeB);
    fill (A, sizeA, 2000, 1000);
    fill (B, sizeB, 2000, 1000);
    printf ("Array A\n");
    print(A,sizeA);
    printf ("Array B\n");
    print(B, sizeB);
    int *C = (int*) malloc(sizeA);
    for (int i = 0; i <sizeA; i++)
    {
        int min = A[i] - B[0], razn, Bindex = 0;
        for (int j = 0; j < sizeB; j++)
        {
            razn = A[i] - B[j];
            if (abs(razn) <= abs(min))
            {
                min = razn;
                Bindex = j;
            }
        }
       // printf ("For %d closest value is %d\n", A[i], B[Bindex]);
        C[i] = A[i] + B[Bindex];
    }
    printf("Array C\n");
    print(C, sizeA);
    free (A);
    free (B);
    free (C);
}
