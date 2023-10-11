#include <stdio.h>
#include <stdlib.h>

void multiples_numbers(int* multiples_array, int number, int count) {
    multiples_array[0] = number;
    for (int i = 1; i < count; i++) {
        multiples_array[i] = multiples_array[i-1] + number;
    }
}

int is_prime(int number) {
    for (int i = 2; i*i <= number; i++) {
        if (number % i == 0) {
            return 1;
        }
    }
    return 0;
}

void power(int n, int m, long long powers[][m]) {
    for (int i = 1; i <= n; i++) {
        long long res = i;
        for (int j = 0; j < m; j++) {
            powers[i-1][j] = res;
            res *= i;
        }
    }
}

unsigned int sum_of_numbers(int number) {
   unsigned int result = 0;
    for(int i = 1; i <= number; i++) {
        result += i;
    }
    return result;
}

unsigned int factorial(int number) {
    if (number == 0) {
        return 0;
    }
    unsigned int result = 1;
    for (int i = 1; i <= number; i++) {
        result *= i;
    }
    return result;
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("Not enough values to unpack\n");
        return 0;
    }
    else
    if (argv[1][0] == '-' || argv[1][0] == '/')
    {
        int number = atoi(argv[2]);
        switch (argv[1][1])
        {
            case 'h':
            {
                if (number <= 0) {printf ("Wrong value\n"); break;}
                int count = 100 / number;
                if (count < 2) { printf ("No multiples\n"); break;}
                else
                {
                int result[count];
                multiples_numbers(result, number, count);
                for (int i = 0; i < count; i++)
                {
                    printf ("%d ", result[i]);
                }
                printf ("\n");
                }
                break;
            }
            case 'p':
            {
                (is_prime(number) == 0) ? printf("The number is prime\n")
                                        : printf("The number is composite\n");
                break;
            }
            case 's':
            {
                for (int i = 0; argv[2][i] != '\0'; i++) {
                    printf("%c ", argv[2][i]);
                }
                printf ("\n");
                break;
            }
            case 'e':
            {
                if (number > 10) { printf ("VALUE IS TOO HIGH "); break; }
                else
                {
                    long long result[10][number];
                    power(10, number, result);
                    for (int i = 0; i < 10; i++) {
                        for (int j = 0; j < number; j++) {
                            printf("%lld ", result[i][j]);
                        }
                        printf("\n");
                    }
                }
            break;
            }
            case 'a':
            {
                unsigned int sum = sum_of_numbers(number);
                printf("The sum of numbers is %d\n", sum);
                break;
            }
            case 'f':
            {
                printf("The factorial of %d is %d\n", number, factorial(number));
                break;
            }
            default: printf("ERROR ERROR ERROR ERROR"); break;
        }
    } else printf("ERROR ERROR ERROR ERROR ERROR\nNO FLAG\n");
    return 0;
}
