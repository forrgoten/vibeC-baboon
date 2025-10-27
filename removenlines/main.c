#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

int main() {
  FILE *input_file, *output_file;
  char line[MAX_LINE_LENGTH];
  int n, line_count = 0, keep_count = 0;
  input_file = fopen("data.dat", "r");
  if (input_file == NULL) {
    printf("Error occured when loading file\n");
    return 1;
  }
  output_file = fopen("dataedit.dat", "w");
  if (output_file == NULL) {
    printf("Error occured when creating dataedit.dat\n");
    fclose(input_file);
    return 1;
  }
  printf("Enter n: ");
  scanf("%d", &n);
  if (n < 2) {
    printf("n must be greater than 2\n");
    fclose(input_file);
    fclose(output_file);
    return 1;
  }
  while (fgets(line, sizeof(line), input_file) != NULL) {
    line_count++;
    line[strcspn(line, "\n")] = 0;
    if (strlen(line) == 0) {
      continue;
    }
    int keep_line = 1;
    for (int i = 2; i <= n; i++) {
      if (line_count % i == 0) {
        keep_line = 0;
        break;
      }
    }
    if (keep_line) {
      fprintf(output_file, "%s\n", line);
      keep_count++;
    }
  }
  fclose(input_file);
  fclose(output_file);
  printf("Done!\n");
  printf("Start: %d\n", line_count);
  printf("Saves: %d\n", keep_count);
  printf("Deletes: %d\n", line_count - keep_count);
  return 0;
}
