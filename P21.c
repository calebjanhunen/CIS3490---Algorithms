#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FALSE 0
#define TRUE 1

struct Point {
    double x;
    double y;
} typedef Point;

void convexHullBF(Point *points, int numPoints, Point *hull, int *numHullPoints);
void sortConvexHull(Point *hull, int numHullPoints, Point *sortedHull);
int compareXVals(const void *a, const void *b);
void findShortestPath(Point *sortedHull, int numHullPoints, Point s1, Point s2);
double distance(Point p1, Point p2);

int main(int argc, char **argv) {
    FILE *fp;
    // char *filename = "testQ2.txt";
    char *filename = "data_A2_Q2.txt";
    int fsize;
    Point points[30000];
    char num[20];
    char c;
    clock_t start, end;

    /****************************Opening and reading file*************************************/
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Could not open\n");
        exit(-1);
    }

    int i = 0;
    while (fscanf(fp, "%lf %lf", &points[i].x, &points[i].y) == 2) {
        i++;
    }

    /****************************Finding Convex Hull*************************************/
    Point hull[30000];
    int numPoints = 30000, numHullPoints = 0;
    start = clock();
    convexHullBF(points, numPoints, hull, &numHullPoints);
    end = clock();

    Point sortedHull[numHullPoints];
    sortConvexHull(hull, numHullPoints, sortedHull);

    printf("A Brute force algorithm for the shortest path around\n");
    for (int i = 0; i < numHullPoints; i++) {
        printf("x: %.1lf, y: %.1lf \n", sortedHull[i].x, sortedHull[i].y);
    }
    // printf("Number of points: %d\n", numHullPoints);
    double duration = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Time for computing hull: %f \n", duration);

    /****************************Finding shortest path given 2 points*************************************/
    Point shortestPathArr[numHullPoints];
    int numPathPoints = 0;
    // Point s1 = {.x = 145.7, .y = 517.0}, s2 = {.x = 5961.6, .y = 6274.5};
    Point s1 = {.x = 5616.9, .y = 37.6}, s2 = {.x = 5961.6, .y = 6274.5};
    // Point s1 = {.x = -2.0, .y = 4.0}, s2 = {.x = 4.0, .y = -16.0};
    findShortestPath(sortedHull, numHullPoints, s1, s2);

    fclose(fp);
    return 0;
}

void findShortestPath(Point *sortedHull, int numHullPoints, Point s1, Point s2) {
    int startingIndex, endingIndex;
    Point path1[numHullPoints], path2[numHullPoints];

    for (int i = 0; i < numHullPoints; i++) {
        if (sortedHull[i].x == s1.x && sortedHull[i].y == s1.y) {
            startingIndex = i;
        }
        if (sortedHull[i].x == s2.x && sortedHull[i].y == s2.y) {
            endingIndex = i;
        }
    }

    int i = startingIndex, path1Index = 0, path2Index = 0;
    double distance1 = 0, distance2 = 0;

    // incrementing through array
    while (i != endingIndex) {
        if (i == numHullPoints - 1) {

            distance1 += distance(sortedHull[i], sortedHull[0]);
        } else {

            distance1 += distance(sortedHull[i], sortedHull[i + 1]);
        }
        path1[path1Index++] = sortedHull[i];
        i++;
        if (i == numHullPoints) {
            i = 0;
        }
    }
    path1[path1Index++] = sortedHull[endingIndex];

    // decrementing through array
    i = startingIndex;
    while (i != endingIndex) {
        if (i == 0) {
            distance2 += distance(sortedHull[i], sortedHull[numHullPoints - 1]);
        } else {
            distance2 += distance(sortedHull[i], sortedHull[i - 1]);
        }
        path2[path2Index++] = sortedHull[i];
        i--;
        if (i == 0) {
            i = numHullPoints - 1;
        }
    }
    path2[path2Index++] = sortedHull[endingIndex];

    printf("The shortest path around: \n");
    if (distance1 < distance2) {
        for (int j = 0; j < path1Index; j++) {
            printf("x: %.1lf, y: %.1lf \n", path1[j].x, path1[j].y);
        }
        printf("The number of points: %d \n", path1Index);
        printf("The distance: %.1f \n", distance1);
    } else {
        for (int j = 0; j < path2Index; j++) {
            printf("x: %.1lf, y: %.1lf \n", path2[j].x, path2[j].y);
        }
        printf("The number of points: %d \n", path2Index);
        printf("The distance %.1f \n", distance2);
    }
}

double distance(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void convexHullBF(Point *points, int numPoints, Point *hull, int *numHullPoints) {
    float a, b, c, d, compareVal;
    int onLeft, onRight;
    int isExtremePoint;

    for (int i = 0; i < numPoints; i++) {
        printf("%d\n", i);
        for (int j = 0; j < numPoints; j++) {
            if (j != i) {
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
                        d = (a * points[k].x) + (b * points[k].y) - c;
                        if (d > 0) {
                            onLeft++;
                        } else if (d < 0) {
                            onRight++;
                        }

                        if (onLeft > 0 && onRight > 0 || d == 0) {
                            isExtremePoint = FALSE;
                            break;
                        }
                    }
                }
                if (isExtremePoint == TRUE) {
                    hull[*numHullPoints] = points[i];
                    *numHullPoints += 1;
                    break;
                }
            }
        }
    }
}

// Sorts the convex hull in a clockwise direction
void sortConvexHull(Point *hull, int numHullPoints, Point *sortedHull) {
    double minYVal;

    qsort(hull, numHullPoints, sizeof(struct Point), compareXVals);

    if (hull[0].y < hull[numHullPoints - 1].y) {
        minYVal = hull[0].y;
    } else {
        minYVal = hull[numHullPoints - 1].y;
    }

    int i = 0, j = 0, k = numHullPoints - 1;
    while (i < numHullPoints) {
        if (hull[i].y > minYVal) {
            sortedHull[j] = hull[i];
            j++;
        } else {
            sortedHull[k] = hull[i];
            k--;
        }
        i++;
    }
}

int compareXVals(const void *a, const void *b) {
    Point p1 = *((Point *)a);
    Point p2 = *((Point *)b);

    if (p2.x < p1.x) {
        return 1;
    } else if (p1.x < p2.x) {
        return -1;
    }
    return 0;
}