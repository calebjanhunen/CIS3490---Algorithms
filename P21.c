#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Point {
    float x;
    float y;
} typedef Point;

void convexHullBF(Point *points, int numPoints, Point *hull, int *numHullPoints);

int main(int argc, char **argv) {
    FILE *fp;
    char *filename = "testQ2.txt";
    // char *filename = "data_A2_Q2.txt";
    int fsize;
    Point points[30000];
    char num[20];
    char c;
    clock_t start, end;

    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Could not open\n");
        exit(-1);
    }

    int i = 0;
    while (fscanf(fp, "%f %f", &points[i].x, &points[i].y) == 2) {
        i++;
    }

    Point hull[20];
    int numPoints = 5, numHullPoints = 0;
    start = clock();
    convexHullBF(points, numPoints, hull, &numHullPoints);
    end = clock();

    for (int i = 0; i < numHullPoints; i++) {
        printf("x: %f, y: %f \n", hull[i].x, hull[i].y);
    }
    double duration = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Execution time = %f \n", duration);

    // printf("%d \n", sizeof(hull) / sizeof(Point));

    fclose(fp);
    return 0;
}

void convexHullBF(Point *points, int numPoints, Point *hull, int *numHullPoints) {
    float crossProduct;

    for (int i = 0; i < numPoints; i++) {
        for (int j = i + 1; j < numPoints; j++) {
            for (int k = 0; k < numPoints; k++) {
                printf("%d %d %d\n", i, j, k);
                crossProduct = (points[j].x - points[i].x) * (points[k].y - points[i].y) - (points[k].x - points[i].x) * (points[j].y - points[i].y);
                printf("%f \n", crossProduct);
                printf("(%f, %f), (%f, %f), (%f, %f)\n\n", points[i].x, points[i].y, points[j].x, points[j].y, points[k].x, points[k].y);
                if (crossProduct > 0) {
                    // printf("hull: %d \n", *numHullPoints);
                    hull[*numHullPoints] = points[j];
                    *numHullPoints += 1;
                    // break;
                }
            }
        }
    }
}

// void convexHullBF(Point *points, int numPoints, Point *hull, int *numHullPoints) {
//     float a, b, c, d;
//     int leftSide, rightSide;

//     for (int i = 0; i < numPoints; i++) {

//         for (int j = 0; j < numPoints; j++) {
//             if (j != i) {
//                 a = points[j].y - points[i].y;
//                 b = points[i].x - points[j].x;
//                 c = (points[i].x * points[j].y) - (points[i].y * points[j].x);
//                 leftSide = 0;
//                 rightSide = 0;
//                 for (int k = 0; k < numPoints; k++) {
//                     if (k != j && k != i) {
//                         d = (a * points[k].x) + (b * points[k].y) - c;
//                         printf("LINE SEGMENT x1: %f y1: %f ...... x2L %f y2: %f............ POINT x: %f, y: %f \n", points[i].x, points[i].y, points[j].x, points[j].y, points[k].x, points[k].y);
//                         if (d > 0) {
//                             leftSide++;
//                         } else {
//                             rightSide++;
//                         }
//                     }
//                 }

//                 // printf("x: %f y: %f d: %f c: %f\n", points[k].x, points[k].y, d);

//                 // printf("i: %d, j: %d, k: %d************************** \n", i, j, k);
//                 printf("rs: %d, ls: %d \n", rightSide, leftSide);
//                 if (rightSide == 0 || leftSide == 0) {
//                     // for (int k = 0; k <)

//                     hull[*numHullPoints] = points[i];
//                     hull[*numHullPoints + 1] = points[j];
//                     *numHullPoints += 2;
//                 }
//             }

// printf("LINE SEGMENT x1: %f y1: %f ...... x2L %f y2: %f\n", points[i].x, points[i].y, points[j].x, points[j].y);
// printf("a: %f, b: %f, c: %f \n", a, b, c);

// for (int k = 0; k < numPoints; k++) {
//     if (k != i && k != j) {
//         d = (a * points[k].x) + (b * points[k].y);
//         // printf("c: %f\n", cross_product(points[i], points[j], points[k]));
//         // printf("x: %f y: %f d: %f c: %f\n", points[k].x, points[k].y, d, c);

//         if (d > c) {
//             leftSide++;
//         } else {
//             rightSide++;
//         }
//     }
// }
// printf("rs: %d, ls: %d \n", rightSide, leftSide);
// if (rightSide == 0 || leftSide == 0) {
//     // for (int k = 0; k <)

//     hull[*numHullPoints] = points[i];
//     hull[*numHullPoints + 1] = points[j];
//     *numHullPoints += 2;
// }
// }
// }
// }

/*
#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
  int x;
  int y;
} Point;

int isLeftTurn(Point a, Point b, Point c) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) > 0;
}

Point *convexHull(Point *points, int numPoints, int *numHullPoints) {
  Point *hull = malloc(numPoints * sizeof(Point));
  int hullSize = 0;
  for (int i = 0; i < numPoints; i++) {
    for (int j = i + 1; j < numPoints; j++) {
      for (int k = j + 1; k < numPoints; k++) {
        if (isLeftTurn(points[i], points[j], points[k])) {
          hull[0] = points[i];
          hull[1] = points[j];
          hull[2] = points[k];
          hullSize = 3;
          break;
        }
      }
    }
    for (int j = 0; j < numPoints; j++) {
      if (hullSize == 0 || j == hull[0].x) continue;
      while (hullSize >= 2 && !isLeftTurn(points[i], hull[hullSize - 1], points[j])) {
        hullSize--;
      }
      hull[hullSize++] = points[j];
    }
  }
  *numHullPoints = hullSize;
  return hull;
}

int main() {
  Point points[] = {{0, 0}, {0, 1}, {1, 1}, {1, 0}};
  int numPoints = sizeof(points) / sizeof(Point);
  int numHullPoints;
  Point *hull = convexHull(points, numPoints, &numHullPoints);
  for (int i = 0; i < numHullPoints; i++) {
    printf("(%d, %d)\n", hull[i].x, hull[i].y);
  }
  free(hull);
  return 0;
}
*/