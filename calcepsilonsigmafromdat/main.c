#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *input_file, *output_file;
  double point1, point2;
  double L, S;
  char input_filename[] = "data.dat";
  char output_filename[] = "dataedit.dat";
  printf("L: ");
  if (scanf("%lf", &L) != 1 || L == 0) {
    printf("Invalid L\n");
    return 1;
  }
  printf("S: ");
  if (scanf("%lf", &S) != 1 || S == 0) {
    printf("Invalid S\n");
    return 1;
  }
  input_file = fopen(input_filename, "r");
  if (input_file == NULL) {
    printf("Error open %s\n", input_filename);
    return 1;
  }
  output_file = fopen(output_filename, "w");
  if (output_file == NULL) {
    printf("Error creating %s\n", output_filename);
    fclose(input_file);
    return 1;
  }
  while (fscanf(input_file, "%lf %lf", &point1, &point2) == 2) {
    double new_point1 = point1 / L;
    double new_point2 = point2 / S;
    fprintf(output_file, "%.3lf %.0lf\n", new_point1, new_point2);
  }
  fclose(input_file);
  fclose(output_file);
  printf("Done!\n");
  return 0;
}
