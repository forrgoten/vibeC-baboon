#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  FILE *output_file = NULL;
  int output_to_file = 0;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-f") == 0) {
      output_to_file = 1;
      if (i + 1 < argc) {
        output_file = fopen(argv[i + 1], "w");
        if (output_file == NULL) {
          printf("Error occured when opening file: %s\n", argv[i + 1]);
          return 1;
        }
        i++;
      } else {
        printf("File does not specified\n");
        return 1;
      }
    }
  }
  int n;
  printf("Input n: ");
  scanf("%d", &n);

  if (output_to_file) {
    fprintf(output_file, "Input n: %d\n", n);
  }

  double *numbers = (double *)malloc(n * sizeof(double));
  if (numbers == NULL) {
    printf("Err1\n");
    if (output_to_file)
      fprintf(output_file, "Err1\n");
    if (output_to_file)
      fclose(output_file);
    return 1;
  }

  printf("Input %d nums:\n", n);
  if (output_to_file) {
    fprintf(output_file, "Input %d nums:\n", n);
  }

  for (int i = 0; i < n; i++) {
    printf("Num %d: ", i + 1);
    scanf("%lf", &numbers[i]);
    if (output_to_file) {
      fprintf(output_file, "Num %d: %.6lf\n", i + 1, numbers[i]);
    }
  }

  printf("\nInput nums: ");
  if (output_to_file) {
    fprintf(output_file, "\nInput nums: ");
  }

  for (int i = 0; i < n; i++) {
    printf("%.6lf ", numbers[i]);
    if (output_to_file) {
      fprintf(output_file, "%.6lf ", numbers[i]);
    }
  }
  printf("\n");
  if (output_to_file) {
    fprintf(output_file, "\n");
  }

  double sum = 0.0;
  for (int i = 0; i < n; i++) {
    sum += numbers[i];
  }
  double average = sum / n;
  printf("Average: %.6lf\n", average);
  if (output_to_file) {
    fprintf(output_file, "Average: %.6lf\n", average);
  }

  double sum_sq_diff = 0.0;
  for (int i = 0; i < n; i++) {
    sum_sq_diff += pow(numbers[i] - average, 2);
  }
  double S_n = sqrt(sum_sq_diff / (n - 1));
  printf("S_n: %.6lf\n", S_n);
  if (output_to_file) {
    fprintf(output_file, "S_n: %.6lf\n", S_n);
  }

  double S = S_n / sqrt(n);
  printf("S: %.6lf\n", S);
  if (output_to_file) {
    fprintf(output_file, "S: %.6lf\n", S);
  }

  double student_coef;
  switch (n) {
  case 2:
    student_coef = 12.71;
    printf("\nt alpha n: %.6lf\n", student_coef);
    break;
  case 3:
    student_coef = 4.3;
    printf("\nt alpha n: %.6lf\n", student_coef);
    break;
  case 4:
    student_coef = 3.188;
    printf("\nt alpha n: %.6lf\n", student_coef);
    break;
  case 5:
    student_coef = 2.77;
    printf("\nt alpha n: %.6lf\n", student_coef);
    break;
  case 6:
    student_coef = 2.57;
    printf("\nt alpha n: %.6lf\n", student_coef);
    break;
  case 7:
    student_coef = 2.45;
    printf("\nt alpha n: %.6lf\n", student_coef);
    break;
  case 8:
    student_coef = 2.36;
    printf("\nt alpha n: %.6lf\n", student_coef);
    break;
  case 9:
    student_coef = 2.31;
    printf("\nt alpha n: %.6lf\n", student_coef);
    break;
  case 10:
    student_coef = 2.26;
    printf("\nt alpha n: %.6lf\n", student_coef);
    break;
  default:
    printf("\nt alpha n: ");
    scanf("%lf", &student_coef);
  }
  if (output_to_file) {
    fprintf(output_file, "\nt alpha n: %.6lf\n", student_coef);
  }

  double random_error = student_coef * S;
  printf("Random error: %.6lf\n", random_error);
  if (output_to_file) {
    fprintf(output_file, "Random error: %.6lf\n", random_error);
  }

  double systematic_error;
  printf("Input system error: ");
  scanf("%lf", &systematic_error);
  if (output_to_file) {
    fprintf(output_file, "Input system error: %.6lf\n", systematic_error);
  }

  double absolute_error = sqrt(pow(random_error, 2) + pow(systematic_error, 2));
  printf("Delta : %.6lf\n", absolute_error);
  if (output_to_file) {
    fprintf(output_file, "Delta : %.6lf\n", absolute_error);
  }

  double relative_error = (absolute_error / fabs(average)) * 100;
  printf("Relative error : %.6lf%%\n", relative_error);
  if (output_to_file) {
    fprintf(output_file, "Relative error : %.6lf%%\n", relative_error);
  }

  free(numbers);

  if (output_to_file) {
    fclose(output_file);
  }

  return 0;
}
