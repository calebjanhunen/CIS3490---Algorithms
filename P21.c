#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FALSE 0
#define TRUE 1

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

    Point hull[30000];
    int numPoints = 30000, numHullPoints = 0;
    start = clock();
    convexHullBF(points, numPoints, hull, &numHullPoints);
    end = clock();

    for (int i = 0; i < numHullPoints; i++) {
        printf("x: %f, y: %f \n", hull[i].x, hull[i].y);
    }
    printf("Number of points: %d", numHullPoints);
    double duration = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Execution time = %f \n", duration);

    // printf("%d \n", sizeof(hull) / sizeof(Point));

    fclose(fp);
    return 0;
}

void convexHullBF(Point *points, int numPoints, Point *hull, int *numHullPoints) {
    float a, b, c, d, compareVal;
    int onLeft, onRight, i_isUnique, j_isUnique;
    int isExtremePoint;

    for (int i = 0; i < numPoints; i++) {
        printf("%d\n", i);
        for (int j = i + 1; j < numPoints; j++) {
            a = points[j].y - points[i].y;
            b = points[i].x - points[j].x;
            c = (points[i].x * points[j].y) - (points[i].y * points[j].x);
            onRight = 0;
            onLeft = 0;
            if (i > 0) {
                compareVal = (a * points[0].x) + (b * points[0].y) - c;
            } else {
                compareVal = (a * points[3].x) + (b * points[3].y) - c;
            }
            isExtremePoint = TRUE;
            for (int k = 0; k < numPoints; k++) {
                if (k != i && k != j) {
                    // printf("%d %d %d\n", i, j, k);
                    // printf("(%f, %f), (%f, %f), (%f, %f)\n", points[i].x, points[i].y, points[j].x, points[j].y, points[k].x, points[k].y)S
                    d = (a * points[k].x) + (b * points[k].y) - c;
                    if (d > 0) {
                        onLeft++;
                    } else if (d < 0) {
                        onRight++;
                    }

                    if (onLeft > 0 && onRight > 0) {
                        isExtremePoint = FALSE;
                        break;
                    }
                }
            }
            // printf("onLeft: %d onRight: %d\n\n", onLeft, onRight);
            if (isExtremePoint == TRUE) {
                // printf("(%f, %f), (%f, %f), (%f, %f)\n", points[i].x, points[i].y, points[j].x, points[j].y);
                i_isUnique = TRUE;
                j_isUnique = TRUE;
                for (int k = 0; k < *numHullPoints; k++) {
                    // printf("TEST\n");
                    if (hull[k].x == points[i].x && hull[k].y == points[i].y) {
                        i_isUnique = FALSE;
                    }
                    if (hull[k].x == points[j].x && hull[k].y == points[j].y) {
                        j_isUnique = FALSE;
                    }
                }
                // printf("junique: %d, iunique: %d \n", j_isUnique, i_isUnique);
                // printf("hull: %d\n", *numHullPoints);
                if (j_isUnique == TRUE && i_isUnique == TRUE) {
                    hull[*numHullPoints] = points[i];
                    hull[*numHullPoints + 1] = points[j];
                    *numHullPoints += 2;
                } else if (j_isUnique == FALSE && i_isUnique == TRUE) {
                    hull[*numHullPoints] = points[i];
                    *numHullPoints += 1;
                } else if (j_isUnique == TRUE && i_isUnique == FALSE) {
                    hull[*numHullPoints] = points[j];
                    *numHullPoints += 1;
                }
                // printf("hull after adding: %d\n", *numHullPoints);
            }
            // if (isExtreme == TRUE) {

            // }
        }
    }
}

// void convexHullBF(Point *points, int numPoints, Point *hull, int *numHullPoints) {
//     float crossProduct;

//     for (int i = 0; i < numPoints; i++) {
//         for (int j = i + 1; j < numPoints; j++) {
//             for (int k = j + 1; k < numPoints; k++) {
//                 printf("%d %d %d\n", i, j, k);
//                 crossProduct = (points[j].x - points[i].x) * (points[k].y - points[i].y) - (points[k].x - points[i].x) * (points[j].y - points[i].y);
//                 printf("%f \n", crossProduct);
//                 printf("(%f, %f), (%f, %f), (%f, %f)\n\n", points[i].x, points[i].y, points[j].x, points[j].y, points[k].x, points[k].y);
//                 if (crossProduct > 0) {
//                     // printf("hull: %d \n", *numHullPoints);
//                     hull[*numHullPoints] = points[j];
//                     *numHullPoints += 1;
//                     // break;
//                 }
//             }
//         }
//     }
// }

/*
23 -35.2
45 5
2 4
2.4 64
-4.6 22
*/