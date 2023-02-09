#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Point {
    float x;
    float y;
} typedef Point;

Point *convexHullBF(Point *points, int numPoints, Point *hull);
int cross_product(struct Point a, struct Point b, struct Point c);

int main(int argc, char **argv) {
    FILE *fp;
    char *filename = "testQ2.txt";
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
    int numPoints = 5;
    convexHullBF(points, numPoints, hull);

    for (int i = 0; i < sizeof(hull) / sizeof(Point); i++) {
        printf("x: %f, y: %f \n", hull[i].x, hull[i].y);
    }

    // printf("%d \n", sizeof(hull) / sizeof(Point));

    fclose(fp);
    return 0;
}

Point *convexHullBF(Point *points, int numPoints, Point *hull) {
    int hullIndex = 0;
    float a, b, c, d;
    int leftSide, rightSide;

    for (int i = 0; i < numPoints; i++) {
        for (int j = i + 1; j <= numPoints; j++) {
            a = points[j].y - points[i].y;
            b = points[j].x - points[i].x;
            c = (points[i].x * points[j].y) - (points[i].y * points[j].x);
            leftSide = 0;
            rightSide = 0;
            // printf("x: %f y:")
            printf("a: %f, b: %f, c: %f \n", a, b, c);

            for (int k = 0; k < numPoints; k++) {
                if (k != i && k != j) {
                    d = (a * points[k].x) + (b * points[k].y);
                    // printf("c: %f\n", cross_product(points[i], points[j], points[k]));
                    printf("d: %f, c: %f \n", d, c);

                    if (d > c) {
                        leftSide++;
                    } else {
                        rightSide++;
                    }
                }
            }
            printf("rs: %d, ls: %d \n", rightSide, leftSide);
            if (rightSide == 0 || leftSide == 0) {
                hull[hullIndex] = points[i];
                hull[hullIndex + 1] = points[j];
                hullIndex++;
            }
        }
    }

    return hull;
}

int cross_product(struct Point a, struct Point b, struct Point c) {
    int y1 = b.y - a.y;
    int y2 = c.y - a.y;
    int x1 = b.x - a.x;
    int x2 = c.x - a.x;
    return y2 * x1 - y1 * x2;
}