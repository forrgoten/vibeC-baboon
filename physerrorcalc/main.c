#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int n;
    printf("Input n: ");
    scanf("%d", &n);
    double *numbers = (double*)malloc(n * sizeof(double));
    if (numbers == NULL) {
        printf("Err1\n");
        return 1;
    }
    printf("Input %d nums:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Num %d: ", i + 1);
        scanf("%lf", &numbers[i]);
    }
    printf("\nInput nums: ");
    for (int i = 0; i < n; i++) {
        printf("%.6lf ", numbers[i]);
    }
    printf("\n");
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += numbers[i];
    }
    double average = sum / n;
    printf("Average: %.6lf\n", average);
    double sum_sq_diff = 0.0;
    for (int i = 0; i < n; i++) {
        sum_sq_diff += pow(numbers[i] - average, 2);
    }
    double S_n = sqrt(sum_sq_diff / (n - 1));
    printf("S_n: %.6lf\n", S_n);
    double S = S_n / sqrt(n);
    printf("S: %.6lf\n", S);
    double student_coef;
    printf("\nt alpha n: ");
    scanf("%lf", &student_coef);
    double random_error = student_coef * S;
    printf("Random error: %.6lf\n", random_error);
    double systematic_error;
    printf("Input system error: ");
    scanf("%lf", &systematic_error);
    double absolute_error = sqrt(pow(random_error, 2) + pow(systematic_error, 2));
    printf("Delta : %.6lf\n", absolute_error);
    double relative_error = (absolute_error / fabs(average)) * 100;
    printf("Relative error : %.6lf%%\n", relative_error);
    free(numbers);
    return 0;
}
