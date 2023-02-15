#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Point {
    float x;
    float y;
} typedef Point;

void quickHull(Point *hull, int *numHullPoints, Point *points, int numPoints);
void findHull(Point *hull, int *numHullPoints, Point *subArr, int subArrSize, Point p1, Point p2);
double findSide(Point linePoint1, Point linePoint2, Point c);
double findDistance(Point a, Point b, Point c);
void sortConvexHull(Point *hull, int numHullPoints, Point *sortedHull);
int compareXVals(const void *a, const void *b);
void findShortestPath(Point *sortedHull, int numHullPoints, Point s1, Point s2);
double distance(Point p1, Point p2);

int main(int argc, char **argv) {
    FILE *fp;
    char *filename = "data_A2_Q2.txt";
    int i;
    Point points[30000];
    clock_t start, end;

    /****************************Opening and reading file*************************************/
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Could not open\n");
        exit(-1);
    }

    i = 0;
    while (fscanf(fp, "%f %f", &points[i].x, &points[i].y) == 2) {
        i++;
    }

    /****************************Finding Convex Hull*************************************/
    Point hull[30000];
    int numPoints = 30000, numHullPoints = 0;
    start = clock();
    quickHull(hull, &numHullPoints, points, numPoints);
    end = clock();

    Point sortedHull[numHullPoints];
    sortConvexHull(hull, numHullPoints, sortedHull);

    printf("A divide and conquer program for the shortest path around\n");
    for (int i = 0; i < numHullPoints; i++) {
        printf("x: %.1lf, y: %.1lf \n", sortedHull[i].x, sortedHull[i].y);
    }
    double duration = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Time for computing hull: %.0f ms\n", duration * 1000);

    /****************************Finding shortest path given 2 points*************************************/
    Point s1, s2;
    double x, y;
    printf("Enter the x and y coordinates of s1: ");
    scanf("%lf %lf", &x, &y);
    s1.x = x;
    s1.y = y;
    printf("Enter the x and y coordinates of s2: ");
    scanf("%lf %lf", &x, &y);
    s2.x = x;
    s2.y = y;

    findShortestPath(sortedHull, numHullPoints, s1, s2);

    fclose(fp);
    return 0;
}

// Finds the shortest path in the convex hull between 2 inputted points
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

// Calculates distance between 2 points
double distance(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
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

// sorting function for qsort
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

// Quickhull driver function
void quickHull(Point *hull, int *numHullPoints, Point *points, int numPoints) {
    Point minX = points[0], maxX = points[0], s1[numPoints], s2[numPoints];

    for (int i = 0; i < numPoints; i++) {
        if (minX.x > points[i].x) {
            minX = points[i];
        }

        if (maxX.x < points[i].x) {
            maxX = points[i];
        }
    }

    hull[0] = minX;
    hull[1] = maxX;
    *numHullPoints += 2;
    // find all points to the left of minX->maxX, store in s1 arr
    // find all points to the left of maxX->minX, store in s2 arr
    int s1Size = 0, s2Size = 0;
    for (int i = 0; i < numPoints; i++) {
        double side = findSide(minX, maxX, points[i]);
        // printf("%f \n", side);
        if (side > 0) { // on the left
            s1[s1Size++] = points[i];
        } else if (side < 0) { // on the right
            s2[s2Size++] = points[i];
        }
    }

    findHull(hull, numHullPoints, s1, s1Size, minX, maxX);
    findHull(hull, numHullPoints, s2, s2Size, maxX, minX);
}

// recursive function for finding the convex hull
void findHull(Point *hull, int *numHullPoints, Point *subArr, int subArrSize, Point p1, Point p2) {
    // if subArr is empty:
    // return
    if (subArrSize == 0) {
        return;
    }

    // find point with largest distance from p1 and p2
    // assign to point c
    // add c to hull
    // numHullPOints++
    double maxDistance = 0;
    Point c;
    for (int i = 0; i < subArrSize; i++) {
        double d = findDistance(p1, p2, subArr[i]);
        if (d > maxDistance) {
            maxDistance = d;
            c = subArr[i];
        }
    }
    hull[*numHullPoints] = c;
    *numHullPoints += 1;

    // find all points to left of p1->c, assign to s1
    // find all points to left of c->p1, assign to s2
    Point s1[subArrSize], s2[subArrSize];
    int s1Size = 0, s2Size = 0;
    for (int i = 0; i < subArrSize; i++) {
        if (findSide(p1, c, subArr[i]) > 0) {
            s1[s1Size++] = subArr[i];
        }
    }

    for (int i = 0; i < subArrSize; i++) {
        double side = findSide(c, p2, subArr[i]);
        if (side > 0) {
            s2[s2Size++] = subArr[i];
        }
    }

    findHull(hull, numHullPoints, s1, s1Size, p1, c);
    findHull(hull, numHullPoints, s2, s2Size, c, p2);
}

// find side that pooint is on relative to the line segment (<0: Rightside, >0: LeftShave)
double findSide(Point linePoint1, Point linePoint2, Point c) {
    return (linePoint2.x - linePoint1.x) * (c.y - linePoint1.y) - (linePoint2.y - linePoint1.y) * (c.x - linePoint1.x);
}

// Calculates distance from line to point
double findDistance(Point a, Point b, Point c) {
    return abs((b.x - a.x) * (a.y - c.y) - (a.x - c.x) * (b.y - a.y)) / sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}