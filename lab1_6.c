#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int check_epsilon_validity(char* eps) {
    char* double_symbols = "1234567890.";
    for (int i = 0; i < strlen(eps); i++) {
        if (strchr(double_symbols, eps[i]) == 0) {
            return 0;
        }
    }
    if (atof(eps) <= 0.0) {
        return 0;
    }
    return 1;
}

double function_a(double x) {
    return log(1.0 + x) / x;
}

double function_b(double x) {
    return exp(- x * x / 2.0);
}

double function_c(double x) {
    return log(1.0 / (1.0 - x));
}

double function_d(double x) {
    return pow(x, x);
}

double calculate_a(double eps) {
    double delta_x = 1.0, step = 1.0, curr = log(2.0), prev;

    do {
        prev = curr;
        curr = 0;
        step /= 2.0;
        delta_x /= 2.0;
        for (double x = 1.0; x > 0; x -= step) {
            curr += function_a(x) * delta_x;
        }
    } while (fabs(curr - prev) > eps);
    return curr;
}

double calculate_b(double eps) {
    double delta_x = 1.0, step = 1.0, prev = function_b(1.0), curr = prev;
    do {
        prev = curr;
        curr = 0;
        step /= 2;
        delta_x /= 2;
        for (double x = 1.0; x > 0; x -= step) {
            curr += function_b(x) * delta_x;
        }
    } while (fabs(curr - prev) > eps);
    return curr;
}

double calculate_c(double eps) {
    double delta_x = 1.0, step = 1.0, prev = function_c(0), curr = prev;

    do {
        prev = curr;
        curr = 0;
        step /= 2.0;
        delta_x /= 2.0;

        for (double x = 0; x < 1.0; x += step) {
            curr += function_c(x) * delta_x;
        }
    } while (fabs(curr - prev) > eps);
    return curr;
}

double calculate_d(double eps) {
    double delta_x = 1.0, step = 1.0, curr = function_d(0), prev;
    do {
        prev = curr;
        curr = 0;
        step /= 2.0;
        delta_x /= 2.0;
        for (double x = 0.0; x <= 1.0; x += step) {
            curr += function_d(x) * delta_x;
        }
    } while (fabs(curr - prev) > eps);
    return curr;
}

int main(int argc, char* argv[]) {
 if (argc != 2) {printf ("Incorrect amount of values"); return 0;}
    if (check_epsilon_validity(argv[1]) == 0) {
        printf("Incorrect epsilon value\n");
        return 0;
    }

    double eps = atof(argv[1]),
           res_a = calculate_a(eps),
           res_b = calculate_b(eps),
           res_c = calculate_c(eps),
           res_d = calculate_d(eps);

    printf("The result of the calculation of a.: %f\n"
           "The result of the calculation of b.: %f\n"
           "The result of the calculation of c.: %f\n"
           "The result of the calculation of d.: %f\n", res_a, res_b, res_c, res_d);
    return 0;
}