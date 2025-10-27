#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_POINTS 1000

typedef struct {
  double x;
  double y;
} Point;

int read_data(const char *filename, Point points[]) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error: cannot open file %s\n", filename);
    return -1;
  }

  int count = 0;
  while (count < MAX_POINTS &&
         fscanf(file, "%lf %lf", &points[count].x, &points[count].y) == 2) {
    count++;
  }

  fclose(file);
  return count;
}

void sort_points(Point points[], int left, int right) {
  if (left >= right)
    return;

  Point pivot = points[(left + right) / 2];
  int i = left, j = right;

  while (i <= j) {
    while (points[i].x < pivot.x)
      i++;
    while (points[j].x > pivot.x)
      j--;

    if (i <= j) {
      Point temp = points[i];
      points[i] = points[j];
      points[j] = temp;
      i++;
      j--;
    }
  }

  sort_points(points, left, j);
  sort_points(points, i, right);
}

double interpolate(Point p1, Point p2, double x) {
  if (fabs(p2.x - p1.x) < 1e-10) {
    return (p1.y + p2.y) / 2.0;
  }
  return p1.y + (p2.y - p1.y) * (x - p1.x) / (p2.x - p1.x);
}

double calculate_area(Point points[], int n, double a, double b) {
  double area = 0.0;

  for (int i = 0; i < n - 1; i++) {
    double x1 = points[i].x;
    double x2 = points[i + 1].x;
    double y1 = points[i].y;
    double y2 = points[i + 1].y;

    if (x1 >= a && x2 <= b) {
      area += (y1 + y2) * (x2 - x1) / 2.0;
    } else if (x1 < a && x2 > a) {
      double y_at_a = interpolate(points[i], points[i + 1], a);
      if (x2 <= b) {
        area += (y_at_a + y2) * (x2 - a) / 2.0;
      } else {
        double y_at_b = interpolate(points[i], points[i + 1], b);
        area += (y_at_a + y_at_b) * (b - a) / 2.0;
      }
    } else if (x1 < b && x2 > b) {
      double y_at_b = interpolate(points[i], points[i + 1], b);
      if (x1 >= a) {
        area += (y1 + y_at_b) * (b - x1) / 2.0;
      }
    } else if (x1 <= a && x2 >= b) {
      double y_at_a = interpolate(points[i], points[i + 1], a);
      double y_at_b = interpolate(points[i], points[i + 1], b);
      area += (y_at_a + y_at_b) * (b - a) / 2.0;
    }
  }

  return area;
}

int main() {
  Point points[MAX_POINTS];
  char filename[100];
  double a, b;

  printf("Enter data file name: ");
  scanf("%s", filename);

  int n = read_data(filename, points);
  if (n <= 0) {
    printf("Failed to read data from file.\n");
    return 1;
  }

  sort_points(points, 0, n - 1);

  printf("Data range: x ∈ [%.2f, %.2f]\n", points[0].x, points[n - 1].x);

  printf("Enter lower integration limit: ");
  scanf("%lf", &a);
  printf("Enter upper integration limit: ");
  scanf("%lf", &b);

  if (a > b) {
    printf("Error: lower limit cannot be greater than upper limit.\n");
    return 1;
  }

  if (a < points[0].x || b > points[n - 1].x) {
    printf("Warning: integration limits outside data range.\n");
    printf("Area will be calculated only for available range.\n");
  }

  double area = calculate_area(points, n, a, b);

  printf("\nResult:\n");
  printf("Area under graph on interval [%.2f, %.2f] = %.6f\n", a, b, area);

  return 0;
}
