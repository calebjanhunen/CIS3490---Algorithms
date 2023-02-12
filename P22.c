#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare_x(const void *a, const void *b);
int compare_y(const void *a, const void *b);
int orientation(Point p, Point q, Point r);
void quick_hull(Point points[], int n, Point *p1, Point *p2, int side);
void find_hull(Point points[], int n);

struct Point {
    int x, y;
} typedef Point;

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

    return 0;
}

int compare_x(const void *a, const void *b) {
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->x - p2->x);
}

int compare_y(const void *a, const void *b) {
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->y - p2->y);
}

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0)
        return 0;
    return (val > 0) ? 1 : 2;
}

void quick_hull(Point points[], int n, Point *p1, Point *p2, int side) {
    int index = -1;
    int dist = 0;

    for (int i = 0; i < n; i++) {
        int temp = orientation(*p1, *p2, points[i]);
        if (temp == 2 && side == 2) {
            int dist_temp = (points[i].x - p1->x) * (p2->y - p1->y) -
                            (points[i].y - p1->y) * (p2->x - p1->x);
            if (dist_temp > dist) {
                index = i;
                dist = dist_temp;
            }
        } else if (temp == 1 && side == 1) {
            int dist_temp = (points[i].x - p1->x) * (p2->y - p1->y) -
                            (points[i].y - p1->y) * (p2->x - p1->x);
            if (dist_temp < dist) {
                index = i;
                dist = dist_temp;
            }
        }
    }

    if (index == -1) {
        printf("(%d, %d) and (%d, %d)\n", p1->x, p1->y, p2->x, p2->y);
        return;
    }

    quick_hull(points, n, p1, &points[index], 2);
    quick_hull(points, n, &points[index], p2, 1);
}

void find_hull(Point points[], int n) {
    qsort(points, n, sizeof(Point), compare_x);
    Point *min_x = &points[0], *max_x = &points[n - 1];
    quick_hull(points, n, min_x, max_x, 2);
    quick_hull(points, n, max_x, min_x, 1);
}