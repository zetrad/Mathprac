#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int check_epsilon(char* eps) {
    char* double_symbols = "1234567890.";
    for (int i = 0; i < strlen(eps); i++) {
        if (strchr(double_symbols, eps[i]) == 0) {
            return 0;
        }
    }
    if (atof(eps) <= 0) {
        return 0;
    }
    return 1;
}

void swap(double* arr, int i, int j) {
    double temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int next_set(double* arr, int n) {
    int j = n - 2;
    while (j != -1 && arr[j] >= arr[j + 1]) j--;
    if (j == -1) {
        return 0;
    }
    int i = n - 1;
    while (arr[j] >= arr[i]) i--;
    swap(arr, j, i);
    int l = j + 1, r = n - 1;
    while (l < r) swap(arr, l++, r--);
    return 1;
}


int get_combinations(int m, double combinations[][m], double* arr) {
    for(int i = 0; i < 3; i++) {
        combinations[0][i] = arr[i];
    }
    int count = 1;
    while (next_set(arr, 3) == 1) {
        for(int i = 0; i < 3; i++) {
            combinations[count][i] = arr[i];
        }
        count++;
    }
    return count;
}

void quadratic_equation( double a, double b, double c, double* solve) {
    double D = b*b - 4.0*a*c;
    if (D > 0.0) {
        solve[0] = (-b + sqrt(D))/2.0*a;
        solve[1] = (-b - sqrt(D))/2.0*a;

    }
    if (D == 0.0) {
        solve[0] = solve[1] = -b/2.0*a;
    }
    if (D < 0.0) {
        solve[0] = solve[1] = 0;
    }
}

int cmpfunc (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

void comparing_numbers(double* arr, int n, double eps) {
    for (int i = 0; i < n-1; i++) {
        if (fabs(arr[i] - arr[i+1]) < eps) {
            arr[i+1] = arr[i];
        }
    }
}

int is_multiple(int a, int b) {
    if (a % b == 0) {
        return 1;
    }
    return 0;
}

int is_triangle(double* arr) {
    if (arr[0] + arr[1] > arr[2] && arr[1] + arr[2] > arr[0] && arr[2] + arr[0] > arr[1]) {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argv[1][0] == '-' || argv[1][0] == '/')
    {
        switch (argv[1][1]) {
            case 'q':
                {
                if ((argc < 6 || argc > 6) && !check_epsilon(argv[2])) {
                    printf("ERROR ERROR ERROR ERROR ERROR ERROR\n");
                    return 0;
                }
                double eps = atof(argv[2]), arr[3];
                for (int i = 0; i < 3; i++) {
                    arr[i] = atof(argv[i + 3]);
                }
                qsort(arr,3,sizeof(double),cmpfunc);
                comparing_numbers(arr, 3, eps);
                double combinations[6][3], solve[2];
                int count = get_combinations(3, combinations, arr);
                for (int i = 0; i < count; i++) {
                    printf("a = %f, b = %f, c = %f\n", combinations[i][0], combinations[i][1], combinations[i][2]);
                    quadratic_equation(combinations[i][0], combinations[i][1], combinations[i][2], solve);
                    double x1 = solve[0], x2 = solve[1];
                    if (x1 == 0 && x2 == 0) printf("There are no roots\n");
                    else printf("Roots of the equation: x1 = %f, x2 = %f\n", x1, x2);
                }
                return 0;
            }
            case 'm':  {
                if (argc < 4 || argc > 4) {
                    printf("ERROR ERROR ERROR ERROR ERROR ERROR\n");
                    return 0;
                }
                int a = atoi(argv[2]), b = atoi(argv[3]);
                if (is_multiple(a, b)) printf("Number is multiple\n");
                else printf("Number is not multiple\n");
                return 0;
            }

            case 't':
            {
                if (argc < 6 || argc > 6) {
                    printf("ERROR ERROR ERROR ERROR ERROR\n");
                    return 0;
                }
                double eps = atof(argv[2]), arr[3];
                for (int i = 0; i < 3; i++) {
                    arr[i] = atof(argv[i + 3]);
                }
                qsort(arr,3,sizeof(double),cmpfunc);
                comparing_numbers(arr, 3, eps);
                if (is_triangle(arr)) printf("It's triangle\n");
                else printf("Is not triangle\n");
                return 0;
            }
            default:
                printf("ERROR ERROR");
                return 0;
        }
    }
}