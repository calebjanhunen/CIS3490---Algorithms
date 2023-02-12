#include <math.h>
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
void shortestPath(Point *hull, Point *shortestPathArr, int *numPathPoints, int numHullPoints, Point startingPoint, Point endingPoint);

int main(int argc, char **argv) {
    FILE *fp;
    char *filename = "testQ2.txt";
    // char *filename = "data_A2_Q2.txt";
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
    while (fscanf(fp, "%f %f", &points[i].x, &points[i].y) == 2) {
        i++;
    }

    /****************************Finding Convex Hull*************************************/
    Point hull[30000];
    int numPoints = 5, numHullPoints = 0;
    start = clock();
    convexHullBF(points, numPoints, hull, &numHullPoints);
    end = clock();

    for (int i = 0; i < numHullPoints; i++) {
        printf("x: %f, y: %f \n", hull[i].x, hull[i].y);
    }
    printf("Number of points: %d", numHullPoints);
    double duration = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Execution time = %f \n", duration);

    /****************************Finding shortest path given 2 points*************************************/
    Point shortestPathArr[numHullPoints];
    int numPathPoints = 0;
    // Point s1 = {.x = 145.7, .y = 517.0}, s2 = {.x = 5961.6, .y = 6274.5};
    Point s1 = {.x = -2.0, .y = 4.0}, s2 = {.x = 4.0, .y = -16.0};
    shortestPath(hull, shortestPathArr, &numPathPoints, numHullPoints, s1, s2);

    // printf("%d \n", sizeof(hull) / sizeof(Point));

    fclose(fp);
    return 0;
}

void convexHullBF(Point *points, int numPoints, Point *hull, int *numHullPoints) {
    float a, b, c, d, compareVal;
    int onLeft, onRight, i_isUnique, j_isUnique;
    int isExtremePoint;

    for (int i = 0; i < numPoints; i++) {
        // printf("%d\n", i);
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
            if (isExtremePoint == TRUE) {
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
            }
        }
    }
}
float distance(Point p1, Point p2);
Point findClosestPoint(Point point, Point *hull, int numHullPoints);
Point closestIntersectionPoint(Point currPoint, Point closest, Point *hull, int numHullPoints);

void shortestPath(Point *hull, Point *shortestPathArr, int *numPathPoints, int numHullPoints, Point startingPoint, Point endingPoint) {
    Point currentPoint = startingPoint;
    Point closestPoint, nextPoint;

    while (currentPoint.x != endingPoint.x && currentPoint.y != endingPoint.y) {
        printf("current Point(%f, %f) \n", currentPoint.x, currentPoint.y);
        closestPoint = findClosestPoint(currentPoint, hull, numHullPoints);
        printf("closest Point(%f, %f) \n", closestPoint.x, closestPoint.y);
        Point nextPoint = closestIntersectionPoint(currentPoint, closestPoint, hull, numHullPoints);
        shortestPathArr[*numPathPoints++] = nextPoint;
        currentPoint = nextPoint;
    }
}

Point findClosestPoint(Point point, Point *hull, int numHullPoints) {
    // Point closestPoint = hull[0];
    // float minDistance = distance(point, closestPoint), currDistance;
    float minDistance = 1e9, currDistance;
    Point closestPoint;

    for (int i = 0; i < numHullPoints; i++) {
        if (hull[i].x != point.x && hull[i].x != point.x) {
            currDistance = distance(point, hull[i]);
            printf("hull: (%f, %f) point:(%f, %f) distance: %f \n", hull[i].x, hull[i].y, point.x, point.y, currDistance);
            if (currDistance < minDistance) {
                minDistance = currDistance;
                closestPoint = hull[i];
            }
        }
    }

    return closestPoint;
}

Point closestIntersectionPoint(Point currPoint, Point closestPoint, Point *hull, int numHullPoints) {
    double slope = (closestPoint.y - currPoint.y) / (closestPoint.x - currPoint.x);
    double yInt = currPoint.y - (slope * currPoint.x);
    double slope2, yInt2;

    Point closestIntPoint, intPoint;
    double minDistance = 1e9;

    for (int i = 0; i < numHullPoints; i++) {
        printf("%d \n", i);
        if (hull[i].x != closestPoint.x && hull[i].x != closestPoint.x) {
            slope2 = (hull[i].y - closestPoint.y) / (hull[i].x - closestPoint.x);
            yInt2 = hull[i].y - (slope * hull[i].x);

            if (slope != slope2) {
                intPoint.x = (yInt2 - yInt) / (slope - slope2);
                intPoint.y = slope * intPoint.x + yInt;

                double dist = distance(currPoint, intPoint);
                if (dist < minDistance) {
                    closestIntPoint = intPoint;
                    minDistance = dist;
                }
            }
        }
    }

    return closestIntPoint;
}

float distance(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}