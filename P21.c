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
    // char *filename = "testQ2.txt";
    char *filename = "data_A2_Q2.txt";
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
    int numPoints = 30000, numHullPoints = 0;
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
    float a, b, c, d;
    int leftSide, rightSide;

    for (int i = 0; i < numPoints; i++) {
        printf("%d \n", i);

        for (int j = i + 1; j < numPoints; j++) {
            a = points[j].y - points[i].y;
            b = points[i].x - points[j].x;
            c = (points[i].x * points[j].y) - (points[i].y * points[j].x);
            leftSide = 0;
            rightSide = 0;
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
        }
    }
}