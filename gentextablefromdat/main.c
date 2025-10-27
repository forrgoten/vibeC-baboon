#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *inputFile, *outputFile;
  double point1, point2;
  int lineCount = 0;
  inputFile = fopen("data.dat", "r");
  if (inputFile == NULL) {
    printf("Error when loading data.dat\n");
    return 1;
  }
  outputFile = fopen("res.txt", "w");
  if (outputFile == NULL) {
    printf("error when creating res.txt\n");
    fclose(inputFile);
    return 1;
  }
  while (fscanf(inputFile, "%lf %lf", &point1, &point2) == 2) {
    lineCount++;
  }
  rewind(inputFile);
  fprintf(outputFile, "\\begin{table}[h]\n");
  fprintf(outputFile, "\\centering\n");
  fprintf(outputFile, "\\begin{tabular}{|c|c|}\n");
  fprintf(outputFile, "\\hline\n");
  fprintf(outputFile, "&\\\\\n");
  fprintf(outputFile, "\\hline\n");
  int currentLine = 0;
  while (fscanf(inputFile, "%lf %lf", &point1, &point2) == 2) {
    fprintf(outputFile, "%.2f & %.0f \\\\\n", point1, point2);
    currentLine++;
    if (currentLine < lineCount) {
      fprintf(outputFile, "\\hline\n");
    }
  }
  fprintf(outputFile, "\\hline\n");
  fprintf(outputFile, "\\end{tabular}\n");
  fprintf(outputFile, "\\end{table}\n\n");
  fprintf(outputFile, "\\end{document}\n");
  fclose(inputFile);
  fclose(outputFile);
  printf("LaTeX in res.txt\n");
  printf("Lines: %d\n", lineCount);
  return 0;
}
